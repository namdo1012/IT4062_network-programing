#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"
#include "file.h"
#include "handle.h"

void displayMenu()
{
  printf("\n \n---------------------------------------\n");
  printf("USER MANAGEMENT PROGRAM\n");
  printf("---------------------------------------\n");
  printf("1. Register\n");
  printf("2. Activate\n");
  printf("3. Sign in\n");
  printf("4. Search\n");
  printf("5. Change password\n");
  printf("6. Sign out\n");
  printf("Your choice (1-4), other to quit: \n");
}

int getUserChoice()
{
  int choice = 0;

  displayMenu();
  scanf("%d", &choice);
  return choice;
}

int main()
{
  linkedList list;
  createSingleList(&list);
  readFileToList(&list);

  do
  {
    // Display menu and get user's choice
    int choice = getUserChoice();

    // Do tasks
    switch (choice)
    {
    case 1:
      // Handle register
      handleRegister(&list);
      break;
    case 2:
      // Handle active account
      handleActivate(&list);
      break;
    case 3:
      // Handle signIn
      handleSignIn(&list);
      break;
    case 4:
      // Handle search
      handleSearch(&list);
      break;
    case 5:
      // Handle change password
      handleChangePassword(&list);
      break;
    case 6:
      // Handle logging out
      handleLogOut(&list);
      break;
    default:
      // Exit program
      return 0;
    }
  } while (1);

  // printSingleList(&list);
  return 0;
}