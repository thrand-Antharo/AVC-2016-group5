# include <stdio.h>
# include <time.h>

extern "C" int init(int d_lev);
extern "C" int connect_to_server( char server_addr[15],int port);
extern "C" int send_to_server(char message[24]);
extern "C" int receive_from_server(char message[24]);

char ip[15] = "130.195.6.196";
int port = 1024;
char request[24] = "Please";
char password[24];

void main(){

    // Establishes a connection to the gate's server
    connect_to_server(ip, port);
    // Sends the request to open the gate
    send_to_server(request);
    // Receives the password from the server
    receive_from_server(password);
    // Sends the password to the gates ip
    send_to_server(password);
}
