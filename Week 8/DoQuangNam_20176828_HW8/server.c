#include <arpa/inet.h> 
#include <errno.h> 
#include <netinet/in.h> 
#include <signal.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <strings.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <unistd.h>

int main(int argc, char *argv[]) {
  int tcp_socket,connfd,len,nready;
  int port_number;
  char user[20] = "@", pass[20] = "@", message[BUFF_SIZE];
  char buffer[BUFF_SIZE];
  int s;  // send bytes
  struct sockaddr_in server, client[3];
  int count_client=0;
  pid_t pid;
  fd_set rset; 
  ssize_t n; 
  if (argc != 2) {
    puts("Wrong parameter");
  } else {
    port_number = atoi(argv[1]);
    if (port_number == 0) {
      puts("Invalid port number");
      exit(0);
    }

    // Creating socket file descriptor
    tcp_socket = socket(AF_INET,SOCK_STREAM,0);
    if (tcp_socket == -1) {
      printf("socket creation failed...\n");
      exit(0);
    }else{
      printf("socket successfully created...\n");
    }
    bzero(&server,sizeof(server));

    // Filling server information
    int n;
    server.sin_family = AF_INET;
    server.sin_port = htons(port_number);
    server.sin_addr.s_addr = INADDR_ANY;
    
    // Bind address to socket
    if (bind(tcp_socket, (SA*)&server, sizeof(server)) != 0) {
        printf("socket bind failed ...\n");
        exit(0);
    }else{
      printf("Socket successfully binded..\n"); 
    }
    if ((listen(tcp_socket, 10)) != 0) { 
        printf("Listen failed...\n"); 
        exit(0); 
    } 
    else
        printf("Server listening..\n");

    len = sizeof(client);
    openFile();
    FD_ZERO(&rset);
    while(1){
    FD_SET(tcp_socket, &rset);
    nready = select(tcp_socket+1, &rset, NULL, NULL, NULL); 
    if(nready == -1){
      printf("Error\n");
    }else{
      printf("select-ok\n");
    }
    if (FD_ISSET(tcp_socket, &rset)){
      connfd = accept(tcp_socket, (SA*)&client[count_client], &len);
    count_client++;
    if (connfd < 0) { 
        printf("server acccept failed...\n"); 
        exit(0); 
    } 
    else{
        printf("server acccept the client...\n");
        printf("Connection accepted from %s:%d\n", inet_ntoa(client[count_client].sin_addr), ntohs(client[count_client].sin_port)); 
    }
    if ((pid = fork())==0){
    close(tcp_socket);
    while (1) {
      bzero(buffer,sizeof(buffer));
      int rbytes=recv(connfd,&buffer,sizeof(buffer),0);
      printf("%d\n",rbytes );
      if(rbytes<=0){
        printf("Receive Error\n");
        exit(1);
      }
      printf("%s\n",buffer);
      if (!checkString(buffer)) {
        strcpy(message, "Error");
      } else {
        if (isSignIn==0) {
          if (strcmp(user, "@") == 0) {
            if(find(buffer)==NULL){
              strcpy(message,"Wrong account");
            }else{
              strcpy(user, buffer);
              strcpy(message, "Insert password");
            }
          } else {
            strcpy(pass, buffer);
            strcpy(message, signin(user, pass));
            strcpy(user, "@");
            strcpy(pass, "@");
            printf("Trang thai cua bien isSignIn: %d\n",isSignIn );
            printacc(head);
          }
        } else if(isSignIn==1){
          if (strncmp("bye",buffer,3) == 0) {
            strcpy(message, signout());
          } else {
            changePass(buffer);
            strcpy(message,result);
            strcpy(result,"");
          }
        }
      }
      if (strcmp(message,"")!=0)
        send(connfd,&message,sizeof(message),0);
    }
  }
  }
}
}
close(connfd);
  return 0;
}
