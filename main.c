#include <stdio.h>
#include <stdlib.h>
// #include "handle.h"

void handleIP();
void handleDomainName();

void handleIP()
{
  printf("Handle IP");
}

void handleDomainName()
{
  printf("Handle Domain Name");
}

int main(int argc, char *argv[])
{
  if (argc != 3 || atoi(argv[1]) != 1 || atoi(argv[1]) != 2)
  {
    printf("Invalid input!");
    return 1;
  }

  // parameter1 = 1 -> get input ip
  if (atoi(argv[1]) == 1)
  {
    handleIP();
  }

  // parameter1 =2 -> get input domain name
  if (atoi(argv[1]) == 2)
  {
    handleDomainName();
  }
  return 0;
}