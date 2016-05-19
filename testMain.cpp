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


int line(int row) {
  int sum = 0;
  int kp = 1; //example value, testing needed
  int w, s;
  int proportional_signal;
  take_picture();      // take camera shot
  for(int num=0; num < 320; num++){
    w=get_pixel(num, row, 3);
    if(w>127){s=1;}//if it's closer to white
    else{s=0;}
    sum = sum + (num-160)*s;
  }
  update_screen();
  proportional_signal = sum*kp;
  printf ("Proportional_signal:"+proportional_signal);
  return proportional_signal;
}

int motorControl(float error_signal)
{
  printf("Average error signal: %f\n",error_signal);
  int SPEED = 50;
    float change = (error_signal/SPEED)/10;
    //if too far left
    if(error_signal < 0){
      set_motor(1,(SPEED/2));//right motor
      set_motor(2,SPEED);//left motor
      printf("Too far left!\n");
      printf("Left motor: %d Right motor %d\n",SPEED,(SPEED/2));
    }
    //if too far right
    else if(error_signal > 0){
      set_motor(1,SPEED);
      set_motor(2,(SPEED/2));
      printf("Too far right!\n");
      printf("Left motor: %d Right motor %d\n", (SPEED/2), SPEED);
    }
    //if centered
    else{
      set_motor(1,SPEED);
      set_motor(2,SPEED);
      printf("Going straight\n");
    }
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
      int s1 = line (110);
      int s2 = line (120);
      int s3 = line (130);
      float AvgSignal = (s1+s2+s3)/3;
      motorControl(AvgSignal);
     }

   // terminate hardware
    close_screen_stream();
    set_motor(1,0);
    set_motor(2,0);

    return 0;


}
