#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>

void converIPToHostname();
void convertHostnameToIP();

void converIPToHostname(char *ip)
{
  struct in_addr addr;
  inet_aton(ip, &addr);
  struct hostent *host = gethostbyaddr(&addr, sizeof(addr), AF_INET);

  if (host == NULL)
  {
    printf("Not found information\n");
  }
  else
  {
    printf("Official name: %s\n", host->h_name);
    printf("Alias name: \n");
    if (host->h_aliases[0] == NULL)
    {
      printf("NULL\n");
    }
    else
    {
      for (int i = 0; host->h_aliases[i] != NULL; i++)
      {
        printf("\t%s\n", host->h_aliases[i]);
      }
    }
  }
}

void convertHostnameToIP(char *hostname)
{
  struct hostent *host;
  struct in_addr **addr_list;

  if ((host = gethostbyname(hostname)) == NULL)
  {
    printf("Not found information\n");
    return;
  }

  // Print out all alias
  addr_list = (struct in_addr **)host->h_addr_list;
  printf("Official IP: %s \n", inet_ntoa(*addr_list[0]));
  printf("Alias IP: \n");

  // If have NO aliases
  if (addr_list[1] == NULL)
  {
    printf("NULL\n");
    return;
  }

  // Else print out aliases
  for (int i = 1; addr_list[i] != NULL; i++)
  {
    printf("%s \n", inet_ntoa(*addr_list[i]));
  }
}

int main(int argc, char *argv[])
{
  if (argc != 3 || atoi(argv[1]) < 1 || atoi(argv[1]) > 2)
  {
    printf("Invalid input!");
    return 1;
  }

  // parameter1 = 1 -> get input ip
  if (atoi(argv[1]) == 1)
  {
    // Get ip address from input
    char ipAddr[20];
    strcpy(ipAddr, argv[2]);

    // Check valid ip address
    if (inet_addr(ipAddr) == -1)
    {
      printf("Wrong parameter");
      return 0;
    }

    // Convert IP to Hostname
    converIPToHostname(argv[2]);
  }

  // parameter1 =2 -> get input domain name
  if (atoi(argv[1]) == 2)
  {
    char hostname[50];
    strcpy(hostname, argv[2]);

    // Check valid ip address
    if (inet_addr(hostname) != -1)
    {
      printf("Wrong parameter");
      return 0;
    }

    convertHostnameToIP(argv[2]);
  }
  return 0;
}