#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>

#include "network.h"

void serveHomepageDomainName(char domainName[30])
{
  struct in_addr addr;

  // If user's homepage is ip address form -> convert to domain name
  if (inet_addr(domainName) != -1)
  {
    inet_aton(domainName, &addr);
    struct hostent *host = gethostbyaddr(&addr, sizeof(addr), AF_INET);

    if (host == NULL)
    {
      printf("Not found information\n");
      return;
    }
    else
    {
      printf("Official name: %s\n", host->h_name);
      return;
    }
  }
  // Print out domain name
  printf("Home page with domain name: %s\n", domainName);
}

void serveHomepageIP(char ipAddr[30])
{
  struct hostent *host;
  struct in_addr **addr_list;

  // If user's homepage is a domain name -> convert to ip address
  if (inet_addr(ipAddr) == -1)
  {
    if ((host = gethostbyname(ipAddr)) == NULL)
    {
      printf("Not found infomation\n");
      return;
    }

    addr_list = (struct in_addr **)host->h_addr_list;
    printf("Home page with ip address: %s\n", inet_ntoa(*addr_list[0]));
    return;
  }

  else
  {
    printf("Home page with ip address: %s\n", ipAddr);
    return;
  }
}
