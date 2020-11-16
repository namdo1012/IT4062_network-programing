#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#define BUFF_SIZE 1024
#define SA struct sockaddr 
int main(int argc, char *argv[]) {
  int tcp_socket;
  int port_number, count = 0;
  char ip[BUFF_SIZE];
  char buff[BUFF_SIZE];
  int n, m, len;
  struct sockaddr_in server;

  if (argc != 3) {
    puts("Wrong parameter");
  } else {
    // Check if argument is ipv4
    strcpy(ip, argv[1]);
    for (int i = 0; i < strlen(ip); i++) {
      if (ip[i] == '.') {
        count++;
      }
    }
    if (inet_addr(ip) == -1 || count != 3) {
      puts("Invalid IP address");
      exit(0);
    }

    port_number = atoi(argv[2]);
    if (port_number == 0) {
      puts("Invalid port_number number");
      exit(0);
    }

    // Creating socket file descriptor
    if ((tcp_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) { 
      perror("Socket failed");
      exit(0);
    }else{
      printf("Create successfully\n");
    }
    bzero(&server,sizeof(server));
    // Filling server information
    server.sin_family = AF_INET;
    server.sin_port = htons(port_number);
    server.sin_addr.s_addr = inet_addr(ip);
    len = sizeof(server);
    if (connect(tcp_socket, (SA*)&server, sizeof(server)) != 0) { 
        printf("connection with the server failed...\n"); 
        exit(0); 
    } 
    else{
        printf("connected to the server..\n"); 
    }
            // Communicate with server

    while (1) {
      bzero(buff, sizeof(buff)); 
      gets(buff);
      if(strcmp(buff,"")!=0){
      send(tcp_socket, buff, sizeof(buff),0);
      bzero(buff, sizeof(buff));
      recv(tcp_socket,buff,sizeof(buff),0);
      printf("%s\n", buff);
      } 
    }
    close(tcp_socket);
  }
  return 0;
}