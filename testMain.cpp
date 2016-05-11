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

extern "C" int read_analog(int ch_adc);
extern "C" int Sleep(int sec, int usec);
extern "C" int select_IO(int chan, int direct);
extern "C" int write_digital(int chan,char level);
extern "C" int read_digital(int chan);
extern "C" int set_PWM(int chan, int value);

extern "C" int connect_to_server( char server_addr[15],int port);
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);


int normalSpeed = 135;
int v_left = normalSpeed;
int v_right = normalSpeed;



int line() {
  int num = -160; //keeps track of column
  int sum;
  float ki = 0;
  float kd = 0;
  int w, s;
  int integral_signal = 0;
  int derivative_signal = 0;
  int previous_error = 0;
  int error_period = 1; //placeholder value - don't know how to get it
  take_picture();      // take camera shot
    for(num=-160; num <= 160; num++){
      w=get_pixel(120, num, 3);
      if(w>127){s=1;}
      else{s=0;}
      sum = sum + num*s;
      int error_diff = sum-previous_error;
      integral_signal = sum*ki;
      derivative_signal = (error_diff/error_period)*kd;
      previous_error = sum;
    }
      update_screen();
      return sum;
}

int motorControl()
{
    int error_signal = line();
    if(error_signal< 0){
        v_right =0 - (normalSpeed/2);
        v_left= normalSpeed;
    }
    else if(error_signal> 0){
        v_left =0 - (normalSpeed/2);
        v_right = normalSpeed;
    }
    else{
        v_left= normalSpeed;
        v_right = normalSpeed;
    }
    set_motor(1,v_right);
    set_motor(2,v_left);
    return 0;
}

int main()
{
    int i;
    init(0);
    // connect camera to the screen
    open_screen_stream();
    // set all didgital outputs to +5V
    for (i = 0; i < 8; i++)
    {
      // set all digital channels as outputs
      select_IO(i,0);
      write_digital(i,1);
    }
    while(1)
    {
      motorControl();
     }

   // terminate hardware
    close_screen_stream();
    set_motor(1,0);
    set_motor(2,0);

    return 0;


}
