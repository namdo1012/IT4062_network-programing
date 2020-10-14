#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main()
{

  char server_mesg[256] = "Server connected successfully!\n";

  // Create the server socket
  int server_socket;
  server_socket = socket(AF_INET, SOCK_STREAM, 0);

  // Define the server address
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(9002);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  // Bind the socket to specified IP and port
  bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));

  listen(server_socket, 5);

  int client_socket;
  client_socket = accept(server_socket, NULL, NULL);

  // Send message to client
  send(client_socket, server_mesg, sizeof(server_mesg), 0);

  // Close the socket
  close(server_socket);
}