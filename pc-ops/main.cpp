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

using namespace std;

int main() {
  cout << "Waiting for inputs . . ." << endl;

  Controller c1;

  int fd;
  fd = open("/dev/input/by-id/usb-Microsoft_Controller_7EED87356C04-event-joystick", O_RDONLY);
  struct input_event ev;

  ofstream bluetooth;
  bluetooth.open("/dev/rfcomm0");

  while (1) {
    read(fd, &ev, sizeof(struct input_event));
    c1.update(ev);
    if (c1.getA()){
      bluetooth << "A" << endl;
    }
    if (c1.getB()){
      bluetooth << "B" << endl;
    }
    c1.getLastEvents();
  }

  return 0;
}
