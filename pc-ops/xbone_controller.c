//             ██████╗  ██████╗ ██████╗  █████╗ ███████╗██╗███████╗
//             ██╔══██╗██╔═══██╗██╔══██╗██╔══██╗██╔════╝██║██╔════╝
//             ██████╔╝██║   ██║██████╔╝███████║█████╗  ██║███████╗
//             ██╔══██╗██║   ██║██╔══██╗██╔══██║██╔══╝  ██║╚════██║
//             ██║  ██║╚██████╔╝██████╔╝██║  ██║██║     ██║███████║
//             ╚═╝  ╚═╝ ╚═════╝ ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝

#include <linux/input.h> // struct input_event
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

// id xbone controller ~ LOUIS COLLIN :
// /dev/input/by-id/usb-Microsoft_Controller_7EED87356C04-event-joystick

// Controller events documentation =============================================

// type 1 :
// ~ A | B | X | Y | L1 | R1 | START | SELECT | HOME ~
// A          -> code  304
//   (binary) -> value 0 | 1
// B          -> code  305
//   (binary) -> value 0 | 1
// X          -> code  307
//   (binary) -> value 0 | 1
// Y          -> code  308
//   (binary) -> value 0 | 1
// L1         -> code  310
//   (binary) -> value 0 | 1
// R1         -> code  311
//   (binary) -> value 0 | 1
// JSR BUTTON -> code  317
//   (binary) -> value 0 | 1
// JSL BUTTON -> code  318
//   (binary) -> value 0 | 1
// SELECT     -> code  314
//   (binary) -> value 0 | 1
// START      -> code  315
//   (binary) -> value 0 | 1
// HOME       -> code  316
//   (binary) -> value 0 | 1

// type 3:
// ~ JSR | JSL | R2 | L2 | DPAD ~
// JSL HORIZONTAL  -> code  0
//       (16 bits) -> value LEFT -32768 | 32767 RIGHT
// JSL VERTICAL    -> code  1
//       (16 bits) -> value UP   -32768 | 32767 DOWN
// JSR HORIZONTAL  -> code  3
//       (16 bits) -> value LEFT -32768 | 32767 RIGHT
// JSR VERTICAL    -> code  4
//       (16 bits) -> value UP   -32768 | 32767 DOWN
// L2              -> code  2
//       (10 bits) -> value 0 | 1023
// R2              -> code  5
//       (10 bits) -> value 0 | 1023
// DPAD HORIZONTAL -> code  16
//                 -> value LEFT -1 | 1 RIGHT
// DPAD VERTICAL   -> code  17
//                 -> value UP   -1 | 1 DOWN

// Controller struct ===========================================================

struct controller {
  int A;
  int B;
  int X;
  int Y;
  int R1;
  int L1;
  int JSR_B;
  int JSL_B;
  int SELECT;
  int START;
  int HOME;

  int JSL_X;
  int JSL_Y;
  int JSR_X;
  int JSR_Y;
  int L2;
  int R2;
  int DPAD_H;
  int DPAD_V;
};

// Main ========================================================================

int main(int argc, char **argv) {

  int fd;
  fd = open(argv[1], O_RDONLY);
  struct input_event ev;

  while (1) {
    read(fd, &ev, sizeof(struct input_event));
    printf("type: %i | code : %i | value : %i\n", ev.type, ev.code, ev.value);
  }

}
