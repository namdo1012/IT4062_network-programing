#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"

void readFileToList(linkedList *list);
void appendDataToFile(FILE *file, nodeValType val);
void writeListToFile(linkedList *list);

// Node *getUser(linkedList *list, nodeValType user);
Node *getUser(linkedList *list, char username[20]);

void handleRegister(linkedList *list);
void handleSignIn(linkedList *list);

void displayMenu()
{
  printf("\n \n---------------------------------------\n");
  printf("USER MANAGEMENT PROGRAM\n");
  printf("---------------------------------------\n");
  printf("1. Register\n");
  printf("2. Sign in\n");
  printf("3. Search\n");
  printf("4. Sign out\n");
  printf("Your choice (1-4), other to quit: \n");
}

// Handle file
void handleRegister(linkedList *list)
{
  nodeValType newUser;

  // GET user's inputted info
  printf("\n---------Register---------\n");
  printf("Username: ");
  scanf("%s", newUser.username);
  printf("Password: ");
  scanf("%s", newUser.password);

  // Initial user's state = idle (2)
  newUser.status = 2;

  // Check if user is exist or not
  if (getUser(list, newUser.username) != NULL)
  {
    printf("Account existed");
    return;
  }

  // Insert new user to list
  insertEnd(list, newUser);

  // Update file
  writeListToFile(list);

  // After all, tell the user
  printf("Successful registration. Activation required.");
}

// Handle file
void handleSignIn(linkedList *list)
{
  int inputTime = 0;
  char username[20];
  char password[20];
  Node *user;

  // GET user's username
  printf("\n---------Sign in---------\n");
  printf("Username: ");
  scanf("%s", username);

  // Get user based on username
  user = getUser(list, username);
  if (user == NULL)
  {
    printf("Cannot find account\n");
  }

  // Get user's password
  while (inputTime < 3)
  {
    printf("Password: ");
    scanf("%s", password);

    // If password is NOT wrong
    if (strcmp(user->val.password, password) == 0)
      break;

    // Else if password IS WRONG
    printf("Password is incorrect\n");
    inputTime++;
  }

  if (inputTime == 3)
  {
    printf("Password is incorrect. Account is blocked\n");
    return;
  }

  // Check if user is BLOCKED or NOT
  if (user->val.status == 0)
  {
    printf("Account is blocked\n");
    return;
  }

  // After all, Hello User!
  printf("Hello %s\n", username);
}

// Utils file
Node *getUser(linkedList *list, char username[20])
{
  Node *tmp = list->root;
  while (tmp != NULL)
  {
    if (strcmp(tmp->val.username, username) == 0)
      return tmp;
    tmp = tmp->next;
  }
  return NULL;
}

int getUserChoice()
{
  int choice = 0;

  displayMenu();
  scanf("%d", &choice);
  return choice;
}

/* PLAIN TEXT FILE */
void readFileToList(linkedList *list)
{
  nodeValType node;

  // Open account file for reading
  FILE *file;
  if ((file = fopen("account.txt", "r+")) == NULL)
  {
    printf("File not found!\n");
    return;
  }

  // Read to list
  while (!feof(file))
  {
    int scan = fscanf(file, "%s %s %d\n", node.username, node.password, &node.status);
    printf("Scan: %d\n", scan);
    printf("Pos: %d\n", ftell(file));

    // if (feof(file))
    //   break;
    insertEnd(list, node);
  }

  // Close file
  fclose(file);
}

void appendDataToFile(FILE *file, nodeValType val)
{
  printf("writting:..");
  fprintf(file, "%s %s %d\n", val.username, val.password, val.status);
}

void writeListToFile(linkedList *list)
{
  // Open account file for reading
  FILE *file;
  if ((file = fopen("account.txt", "w")) == NULL)
  {
    printf("File not found!\n");
    return;
  }

  // Loop for list to write node to file
  Node *tmp = list->root;
  while (tmp != NULL)
  {
    appendDataToFile(file, tmp->val);
    tmp = tmp->next;
  }

  // Close file
  fclose(file);
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

    // Do task
    switch (choice)
    {
    case 1:
      // Handle register
      handleRegister(&list);
      break;
    case 2:
      handleSignIn(&list);
      // Handle signIn
      break;
    case 3:
      printf("Choice 3");
      // Handle search
      break;
    case 4:
      printf("Choice 4");
      // Handle signOut
      break;
    default:
      // Exit program
      return 0;
    }

  } while (1);

  printSingleList(&list);
  // printSingleList(&list_bin);

  // writeListToFile(&list_bin);
  return 0;
}