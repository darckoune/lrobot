//             ██████╗  ██████╗ ██████╗  █████╗ ███████╗██╗███████╗
//             ██╔══██╗██╔═══██╗██╔══██╗██╔══██╗██╔════╝██║██╔════╝
//             ██████╔╝██║   ██║██████╔╝███████║█████╗  ██║███████╗
//             ██╔══██╗██║   ██║██╔══██╗██╔══██║██╔══╝  ██║╚════██║
//             ██║  ██║╚██████╔╝██████╔╝██║  ██║██║     ██║███████║
//             ╚═╝  ╚═╝ ╚═════╝ ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝

#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

#include "Controller.h"
#include "server_ws.hpp"

using namespace std;

using WsServer = SimpleWeb::SocketServer<SimpleWeb::WS>;

shared_ptr<WsServer::Connection> websocketConnection;

ofstream bluetooth;

int phase = 0;

void sendMessageToIHM(string type, string message){
  if(websocketConnection){
    string jsonMessage = "{\"type\":\"" + type + "\",\"message\":\"" + message + "\"}";
    cout << "Sending to websocket : " << jsonMessage << endl;

    auto send_stream = make_shared<WsServer::SendStream>();
    *send_stream << jsonMessage;

    websocketConnection->send(send_stream, [](const SimpleWeb::error_code &ec) {
      if(ec) {
        cout << "Server: Error sending message. " <<
            // See http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/reference.html, Error Codes for error code meanings
            "Error: " << ec << ", error message: " << ec.message() << endl;
      }
    });
  } else {
    cout << "No IHM connected to send the message \"" << message << "\" to." << endl;
  }
}

void sendMessageToRobot(string message){
  cout << "Sending to robot : " << message << endl;
  bluetooth << message << endl;
  if (!bluetooth){
    cout << "Error while sending to bluetooth" << endl;
  }
}


void listenToBluetooth(){
  string data;
  ifstream bluetoothReciever ("/dev/rfcomm0", ifstream::binary); // changer pour /dev/rfcomm0 pour écouter le vrai bluetooth
  if (!bluetoothReciever){
    sendMessageToIHM("LOG", "Error while opening bluetooth serial file");
  }
  while(1){
    getline(bluetoothReciever, data);
    // if (data.size() && data[0] != 'Z'){
    //   data[data.size() - 1] = '\0'; 
    //   sendMessageToIHM("LOG", data);
    // }
    if (data[0] == 'S'){
      sendMessageToIHM("robot", "SPEED:" + to_string(data[1] - 1));
    } else if (data[0] == 'L'){
      bool right = (data[1] & 1) > 0;
      bool left = (data[1] & 2) > 0;
      sendMessageToIHM("robot", "LINE:" + to_string(left) + ":" + to_string(right));
    } else if (data[0] == 'C'){
      if (data[1] < 32){
        string colorCommand = "COLOR:";
        if((data[1] & 1) > 0){
          sendMessageToIHM("robot", colorCommand + "YELLOW");
        } else if((data[1] & 2) > 0){
          sendMessageToIHM("robot", colorCommand + "RED");
        } else if((data[1] & 4) > 0){
          sendMessageToIHM("robot", colorCommand + "GREEN");
        }
      }
    } else if (data[0] == 'A'){
      if (data[1] != 13){
        bool autopilot = (data[1] & 1) > 0;
        sendMessageToIHM("robot", "AUTOPILOT:" + to_string(autopilot));
      }
    } else if (data[0] == 'N' && data[1] == 'P'){
      phase++;
      sendMessageToIHM("robot", "STEP:" + to_string(phase));
    } else if (data[0] == 'Z'){
      sendMessageToIHM("robot", "ALIVE");
    }
    
  }
}

void openBrowser(int argc, char* argv[]){
  struct stat sb;
    char *linkname;
    ssize_t r;

   linkname = (char*) malloc(500);
   r = readlink("/proc/self/exe", linkname, 500);

   printf("'%s'\n", linkname);
   string path = string(linkname);

   size_t i = path.rfind('/', path.length());
   if (i != string::npos) {
      path = path.substr(0, i);
   }

   cout << path << endl;
  //system(("firefox file://" + path + "/ROBAFIS_UI/home.html 2>>/dev/null").c_str());
}

int main(int argc, char* argv[]) {
  openBrowser(argc, argv);

  cout << "Waiting for inputs . . ." << endl;

  Controller c1;

  int fd;

  fd = open("/dev/input/by-id/usb-©Microsoft_Corporation_Controller_0E82AD6-event-joystick", O_RDONLY);
  struct input_event ev;

  cout << "Trying to open bluetooth file" << endl;

  bluetooth.open("/dev/rfcomm0");
  if (!bluetooth){
    cout << "Error while opening bluetooth serial file" << endl;
  }

  cout << "Opened bluetooth serial file" << endl;

  WsServer server;
  server.config.port = 8080;
  auto &echo = server.endpoint["^/?$"];

  echo.on_open = [](shared_ptr<WsServer::Connection> connection) {
    cout << "Server: Opened connection " << connection.get() << endl;
    websocketConnection = connection;
  };

  // See RFC 6455 7.4.1. for status codes
  echo.on_close = [](shared_ptr<WsServer::Connection> connection, int status, const string & /*reason*/) {
    cout << "Server: Closed connection " << connection.get() << " with status code " << status << endl;
    //connections.erase(std::remove(connections.begin(), connections.end(), connection), connections.end());
  };

  thread server_thread([&server]() {
    // Start WS-server
    server.start();
  });

  echo.on_message = [](shared_ptr<WsServer::Connection> connection, shared_ptr<WsServer::Message> message) {
    auto message_str = message->string();

    cout << "Server: Message received: \"" << message_str << "\" from " << connection.get() << endl;

    if (message_str == "STEP"){
      sendMessageToIHM("robot","STEP:" + to_string(phase));
    }

  };

  std::thread t{listenToBluetooth};

  //////////////////////////////////////////////
  //////////////// MAIN LOOP ///////////////////
  //////////////////////////////////////////////

  while (1) {
    read(fd, &ev, sizeof(struct input_event));
    c1.update(ev);
    controllerEvent cevent = c1.getLastEvent();
    if (cevent.ihmMessage == "STEP:0"){
      phase = 0;
      sendMessageToIHM("robot", "STEP:0");
    }
    if (cevent.ihmMessage == "SHUTDOWN"){
      cout << "Shutting down server" << endl;
      exit(1);
    }
    if (cevent.ihmMessage == "NEXT:STEP"){
      phase++;
      sendMessageToIHM("robot", "STEP:" + to_string(phase));
    }
    if (cevent.robotMessage == "B" && phase == 2){
      sendMessageToRobot("BS");
    }
    if (cevent.robotMessage != "" && !(cevent.robotMessage == "A" && phase == 2)){
      sendMessageToRobot(cevent.robotMessage);
    }
    if (cevent.ihmMessage != ""){
      sendMessageToIHM("controller", cevent.ihmMessage);
    }
  }

  return 0;
}
