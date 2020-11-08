#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	// catch wrong input
	if (argc != 2)
	{
		printf("Please input port number\n");
		return 0;
	}
	//Receive port number
	int port = atoi(argv[1]);
	char username[BUFLEN], pass[BUFLEN], new_pass[BUFLEN], buf[BUFLEN], number[BUFLEN], string[BUFLEN];
	FILE *fp;
	fp = fopen("nguoidung.txt", "r");
	createSingleList(&list);
	readDataFromFile(&list);
	//Create Server Socket
	int sockfd, ret;
	struct sockaddr_in serverAddr;

	int newSocket;
	struct sockaddr_in newAddr;

	socklen_t addr_size;

	pid_t childpid;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		printf("[-]Error in connection.\n");
		exit(1);
	}
	printf("[+]Server Socket is created.\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(port);
	serverAddr.sin_addr.s_addr = INADDR_ANY; //ip server

	ret = bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
	if (ret < 0)
	{
		printf("[-]Error in binding.\n");
		exit(1);
	}
	printf("[+]Bind to port %d\n", port);

	if (listen(sockfd, 10) == 0)
	{
		printf("[+]Listening....\n");
	}
	else
	{
		printf("[-]Error in binding.\n");
	}

	while (1)
	{
		newSocket = accept(sockfd, (struct sockaddr *)&newAddr, &addr_size);
		if (newSocket < 0)
		{
			exit(1);
		}
		printf("Connection accepted from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));

		if ((childpid = fork()) == 0)
		{
			close(sockfd);

			while (1)
			{
				memset(username, '\0', BUFLEN);
				memset(pass, '\0', BUFLEN);
				memset(number, '\0', BUFLEN);
				memset(string, '\0', BUFLEN);
				memset(new_pass, '\0', BUFLEN);
				//read data from socket
				recv(newSocket, username, BUFLEN, 0);
				if (strcmp(username, "\n") == 0)
				{
					printf("Disconnected from %s:%d\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));
					break;
				}
				else
				{
					printf("Received username: %s\n", username);
					if (searchAccount(list, username))
					{ //check if account exist ?
						//write data via socket
						memset(buf, '\0', BUFLEN);
						strcpy(buf, "Insert password\n");
						//buf[strlen(buf) - 1] = '\0';
						send(newSocket, buf, strlen(buf), 0);
						bzero(buf, sizeof(buf)); //buf can receive message from another client
						int wrong_pass_count = 0;
						while (1)
						{
							//read data from socket
							recv(newSocket, pass, BUFLEN, 0);
							printf("Received pass: %s\n", pass);
							if (checkCorrectPassword(list, username, pass))
							{ //check if pass is correct?
								if (checkBlocked(list, username) != 1)
								{ //check if account is blocked?
									//write data via socket
									memset(buf, '\0', BUFLEN);
									strcpy(buf, "OK\nEnter new password or 'bye' to sign out\n");
									send(newSocket, buf, strlen(buf), 0);
									bzero(buf, sizeof(buf));
									//read data from socket
									recv(newSocket, new_pass, BUFLEN, 0);
									printf("Received new pass: %s\n", new_pass);
									if (strcmp(new_pass, "bye") == 0)
									{
										//write data via socket
										memset(buf, '\0', BUFLEN);
										strcpy(buf, "Goodbye ");
										strcat(buf, username);
										send(newSocket, buf, strlen(buf), 0);
										bzero(buf, sizeof(buf));
										break;
									}
									if (split_number_and_string(new_pass, number, string))
									{
										//write data via socket
										memset(buf, '\0', BUFLEN);
										strcpy(buf, number);
										strcat(buf, string);
										send(newSocket, buf, strlen(buf), 0);
										bzero(buf, sizeof(buf));
										changePass(list, username, pass, new_pass);
										alterDataOfFile(list);
									}
									else
									{ //wrong format
										//write data via socket
										memset(buf, '\0', BUFLEN);
										strcpy(buf, "Error");
										send(newSocket, buf, strlen(buf), 0);
										bzero(buf, sizeof(buf));
									}
									break;
								}
								else
								{
									//write data via socket
									memset(buf, '\0', BUFLEN);
									strcpy(buf, "Account not ready\n");
									//buf[strlen(buf) - 1] = '\0';
									send(newSocket, buf, strlen(buf), 0);
									bzero(buf, sizeof(buf));
									break;
								}
							}
							else
							{
								if (wrong_pass_count == 3)
								{
									break;
								}
								//write data via socket
								memset(buf, '\0', BUFLEN);
								strcpy(buf, "Not OK\n");
								send(newSocket, buf, strlen(buf), 0);
								bzero(buf, sizeof(buf));
								wrong_pass_count++;
							}
						}
						if (wrong_pass_count == 3)
						{
							//write data via socket
							memset(buf, '\0', BUFLEN);
							strcpy(buf, "Account is blocked\n");
							//buf[strlen(buf) - 1] = '\0';
							send(newSocket, buf, strlen(buf), 0);
							bzero(buf, sizeof(buf));
							blockAccount(list, username);
							alterDataOfFile(list);
							continue;
						}
					}
					else
					{
						memset(buf, '\0', BUFLEN);
						strcpy(buf, "Wrong account\n");
						send(newSocket, buf, strlen(buf), 0);
						bzero(buf, sizeof(buf));
						continue;
					}
				}
			}
		}
	}
	close(newSocket);
	return 0;
}