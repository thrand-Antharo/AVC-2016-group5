
#include <string.h>
#include<stdio.h>
//space?
extern "C" int init_hardware();
extern "C" int init(int d_lev);

extern "C" int connect_to_server( char server_addr[15],int port);         
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);

/*int open_gate() {       //to open gate - call/class thingy
//initialising variables
  char ip[15] = "130.195.6.196";      //address
  int port = 1024;  //port
for (){
  char request [24] = "Please";     //password/message 
  char password [24];  //message
  connect_to_server(ip, port); //char server_addr[15], int port
  send_to_server(request); //to open - char message[24]
  receive_from_server(password);     //char message[24]
  send_to_server(password);
  return 0;
}


//networking to open gate 
// i think this code may possibly work, tried to make it more understandable 
//basically got this from looking at the code we already had

//BELOW IS CODE WE HAD AT FIRST  
//however it is long and partially copied from the example so not 100% if its a go


*/

int  doGate (){
  
init(1);
 connect_to_server("130.195.6.196", 1024); // port number ???? pos not right 
 send_to_server("Please");
for (){
 char request [24] = "Please";     //password/message 
 char password [24];  //message
 char message[24];
 receive_from_server(message);
}
sleep (0,1000);
 printf("%s", message);
 return 0;} 

int main(){
  for(int num=0,num <= 10, num++){
  doGate(); 
  }
}

