#include <stdio.h>

//#include <pthread.h>
#include <time.h>
#include <string.h>

// sudo gcc -Wall
extern "C" int init_hardware();
extern "C" int init(int d_lev);

extern "C" int take_picture();
extern "C" char get_pixel(int row, int col, int color);
extern "C" void set_pixel(int col, int row, char red,char green,char blue);

extern "C" int open_screen_stream();
extern "C" int close_screen_stream();
extern "C" int update_screen();
//extern "C" void GetLine(int row,int threshold);
extern "C" int display_picture(int delay_sec,int delay_usec);
extern "C" int save_picture(char filename[5]);

extern "C" int set_motor(int motor,int speed);

extern "C" int connect_to_server( char server_addr[15],int port);
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);

int line() {
  take_picture();      // take camera shot
       get_pixel(100, 55 ,255,0,0);
       // display picture
       update_screen();
}
//What I want it to do:
//The robot will know its in the correct direction if there is a certain amount of white pixels in center of the image.
//If there isn't a certain amount it will take smaller rectangle of the sampled area and count the white pixels again.
//Depending on these values it will know where there are less white pixels so it will know what way it needs to turn
//It will keep turning until there is a certain amount of white pixels in the frame.

//Read the image and read the amount of white/semi white pixels in the center of the image and add each white pixel to variable count.
//Count will have the total amount of white/semi white pixels.

//If count is above a certain amount the robot will keep moving forward.
//If there is not it will take count the amount of white pixels in smaller portions of the image (Left and right of center)
//If the left side has less pixels then the robot will know to turn left, and it will keep moving left until there is a certain amount of pixles in the frame.
//Same for the right side.

//Will return the value to the moving class whether to turn left, right or keep moving forward. 0 for left 1 for right.

//camera size 160x160??????  25600 pixles???

