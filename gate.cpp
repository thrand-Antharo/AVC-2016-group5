
#include <string.h>
#include<studio.h>

#include "extern.h"
#include "gate.h" 

char ip[15] = "130.195.6.196";      //IP
int port = 1024;
char request [24] = "Please";     //password 
char passord [24];



void.open_gate()        //to open gate 
{
connect_to_server(ip, port);

send_to_server(request);


recieve_from_server(password);      

send_to_server(password);
}


//networking to open gate 
// i think this code may possibly work from research seems more understandable 
//need to test/compare to the code written in test.cpp and it.cpp
//
