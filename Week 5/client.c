#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main()
{

  // Create a socket
  int network_socket;
  network_socket = socket(AF_INET, SOCK_STREAM, 0);

  // Specify an address for the socket
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(9002); // NOT DONE!
  server_addr.sin_addr.s_addr = INADDR_ANY;

  int connection_status = connect(network_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));

  // Check for error with connection
  if (connection_status == -1)
  {
    printf("Connection fail!");
  }

  // Receive data from server
  char server_response[256];
  recv(network_socket, &server_response, sizeof(server_response), 0);

  // Print out the server response
  printf("From server: %s\n", server_response);

  // and then close socket
  close(network_socket);

  return 0;
}
