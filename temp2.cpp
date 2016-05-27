#include <stdio.h>
#include <time.h>
#include <string.h>

extern "C" int init_hardware();
extern "C" int init(int d_lev);

extern "C" int take_picture();
extern "C" char get_pixel(int row, int col, int color);
extern "C" void set_pixel(int col, int row, char red,char green,char blue);

extern "C" int open_screen_stream();
extern "C" int close_screen_stream();
extern "C" int update_screen();
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

bool lose_line(){
  int white=0;
  for(int num=0;num<320;num++){
    int value=get_pixel(num, 160, 3);
    if(value>110){
      white+=1;
      if(white>=10){
        return false;
      }
    }
    else{white=0;}
  }
  return true;
}

double line(){
  int sum = 0;
  double kp = 0.20; 
  int colourVal, s;
  double proportional_signal;
  take_picture(); // take camera shot
  for(int col=0; col < 320; col++){
    colourVal=get_pixel(col, 120, 3);
    if(colourVal>127){s=1;} //if it's closer to white
    else{s=0;}
    sum = sum + (col-160)*s;
  }
  update_screen();
  proportional_signal = sum*kp;
  return proportional_signal;
}

double speedCheck(int min, int max, double val){
  if(val<min){val = min;}
  if(val>max){val = max;}
  return val;
}

int motorControl(double error_signal){
  printf(" error signal: %f\n",error_signal);
  int SPEED = 80;
  double modSpeed;
    if(!lose_line()){ //If a line is detected
      if(error_signal < -200){ //if too far left
        modSpeed = speedCheck(0, SPEED, SPEED+(error_signal/4));
        set_motor(2,SPEED-70);//right motor
        set_motor(1,SPEED);//left motor
        printf("Too far left!\n");
        printf("Left motor: %d Right motor %d\n",SPEED, SPEED*modSpeed);
      }
      else if(error_signal > 200){ //if too far right
        modSpeed = speedCheck(0, SPEED, SPEED-(error_signal/4));
        set_motor(2,SPEED);
        set_motor(1,SPEED-70);
        printf("Too far right!\n");
        printf("Left motor: %d Right motor %d\n", SPEED*modSpeed, SPEED);
      }
    else{ //if centered
      set_motor(1,SPEED);
      set_motor(2,SPEED);
      printf("Going straight\n");
    }
  }
  else if(lose_line()){ //If no line is detected
    set_motor(1,-SPEED);
    set_motor(2,-SPEED);
    printf("Lost line\n");
  }
  return 0;
}

int main() {
  //char ip[15] = "130.195.6.196";
  int port = 1024;
  char request[24] = "Please";
  char password[24];
  int i;
  init(0);
  // connect camera to the screen
  open_screen_stream();
  // set all didgital outputs to +5V
  for (i = 0; i < 8; i++){ // set all digital channels as outputs
    select_IO(i,0);
    write_digital(i,1);
  }
  //connect_to_server(ip, port); // Establishes a connection to the gate's server
  //send_to_server(request); // Sends the request to open the gate
  //receive_from_server(password); // Receives the password from the server
  //send_to_server(password); // Sends the password to the gates ip
  
  while(1){
    motorControl(line());
  }
  // terminate hardware
  close_screen_stream();
  set_motor(1,0);
  set_motor(2,0);
  return 0;
}
