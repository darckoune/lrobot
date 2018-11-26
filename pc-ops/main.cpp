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

shared_ptr<WsServer::Connection> clientConnection;

ofstream bluetooth;

void sendMessageToIHM(string type, string message){
  if(clientConnection){
    string jsonMessage = "{\"type\":\"" + type + "\",\"message\":\"" + message + "\"}";
    cout << "Sending to websocket : " << jsonMessage << endl;
    auto send_stream = make_shared<WsServer::SendStream>();
    *send_stream << jsonMessage;
    clientConnection->send(send_stream, [](const SimpleWeb::error_code &ec) {
      if(ec) {
        cout << "Server: Error sending message. " <<
            // See http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/reference.html, Error Codes for error code meanings
            "Error: " << ec << ", error message: " << ec.message() << endl;
      }
    });
  }
}

void sendMessageToRobot(string message){
  cout << "Sending to robot : " << message << endl;
  bluetooth << message << endl;
}


void listenToBluetooth(){
  string data;
  ifstream bluetoothReciever ("/dev/rfcomm0", ifstream::binary);
  while(1){
    getline(bluetoothReciever, data);
    sendMessageToIHM("robot", "SPEED:" + data);
  }
}

int main() {
  cout << "Waiting for inputs . . ." << endl;

  Controller c1;

  int fd;
  fd = open("/dev/input/by-id/usb-Microsoft_Controller_7EED87356C04-event-joystick", O_RDONLY);
  struct input_event ev;

  bluetooth.open("/dev/rfcomm0");

  WsServer server;
  server.config.port = 8080;
  auto &echo = server.endpoint["^/?$"];

  echo.on_open = [](shared_ptr<WsServer::Connection> connection) {
    cout << "Server: Opened connection " << connection.get() << endl;
    clientConnection = connection;
  };

  // See RFC 6455 7.4.1. for status codes
  echo.on_close = [](shared_ptr<WsServer::Connection> connection, int status, const string & /*reason*/) {
    cout << "Server: Closed connection " << connection.get() << " with status code " << status << endl;
  };

  thread server_thread([&server]() {
    // Start WS-server
    server.start();
  });

  echo.on_message = [](shared_ptr<WsServer::Connection> connection, shared_ptr<WsServer::Message> message) {
    auto message_str = message->string();

    cout << "Server: Message received: \"" << message_str << "\" from " << connection.get() << endl;

  };

  std::thread t{listenToBluetooth};

  //////////////////////////////////////////////
  //////////////// MAIN LOOP ///////////////////
  //////////////////////////////////////////////

  while (1) {
    read(fd, &ev, sizeof(struct input_event));
    c1.update(ev);
    controllerEvent cevent = c1.getLastEvent();
    if (cevent.robotMessage != ""){
      sendMessageToIHM("controller", cevent.ihmMessage);
      sendMessageToRobot(cevent.robotMessage);
    }
  }

  return 0;
}