#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "linkedlist.h"
#include "file.h"
#include "handle.h"

void sendMesgToClient(int client_socket, char mesg[1024])
{
}

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

  printf("Server is running on port 9002\n");

  listen(server_socket, 5);

  // Connect to DB
  linkedList list;
  createSingleList(&list);
  readFileToList(&list);
  printSingleList(&list);

  // Waiting request from client
  int client_socket;
  client_socket = accept(server_socket, NULL, NULL);

  // Send message to client
  send(client_socket, server_mesg, sizeof(server_mesg), 0);

  // Sign in
  int isAuth = 0;
  char buffer[1024];
  int inputTime = 1;

  while (isAuth == 0)
  {
    if (inputTime == 3)
      break;

    listen(server_socket, 5);

    read(client_socket, buffer, 1024);
    printf("From client: %s\n", buffer);
    if (sizeof(buffer) > 0)
    {
      if (userAuth(&list, buffer) != NULL)
      {
        strcpy(server_mesg, "User signed in!\n");
        send(client_socket, server_mesg, sizeof(server_mesg), 0);
        isAuth = 1;
      }
      else
      {
        strcpy(server_mesg, "Wrong password, input again\n");
        send(client_socket, server_mesg, sizeof(server_mesg), 0);
        inputTime++;
      }
    }
  }

  if (inputTime == 3)
  {
    strcpy(server_mesg, "Wrong password 3 times\n");
    send(client_socket, server_mesg, sizeof(server_mesg), 0);
  }

  while (1)
  {
    listen(server_socket, 5);

    read(client_socket, buffer, 1024);
    printf("From client: %s\n", buffer);

    // if (strcmp(buffer, "bye\n") == 0)
    // {
    //   strcpy(server_mesg, "Goodbye user!\n");
    //   send(client_socket, server_mesg, sizeof(server_mesg), 0);
    // }
  }
  return 0;
  // Close the socket
  // close(server_socket);
}