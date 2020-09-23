#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"

/* GLOBAL VAR*/
Node *currentSignInUser = NULL;

void readFileToList(linkedList *list);
void appendDataToFile(FILE *file, nodeValType val);
void writeListToFile(linkedList *list);

// Node *getUser(linkedList *list, nodeValType user);
Node *getUser(linkedList *list, char username[20]);
void updateUser(linkedList *list, nodeValType user, char option[10]);

void handleRegister(linkedList *list);
void handleSignIn(linkedList *list);

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

// Return signin successfully user
Node *userAuth(linkedList *list)
{
  int inputTime = 0;
  char username[20];
  char password[20];
  Node *user;

  // GET user's username
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
    // BLOCK USER
    user->val.status = 0;
    updateUser(list, user->val, "status");
    return NULL;
  }

  // Check if user is BLOCKED or NOT
  if (user->val.status == 0)
  {
    printf("Account is blocked\n");
    return NULL;
  }

  // Return signed in user
  currentSignInUser = user;
  return user;
}

// Handle file
void handleSignIn(linkedList *list)
{
  printf("\n---------Sign in---------\n");

  // user authentication
  Node *signedInUser = userAuth(list);

  // After all, Hello User!
  if (signedInUser != NULL)
    printf("Hello %s\n", signedInUser->val.username);
}

// Handle file
void handleActivate(linkedList *list)
{
  int inputTime = 0;
  char inputCode[10];

  printf("\n---------Activate account---------\n");

  // user authentication
  Node *signedInUser = userAuth(list);
  if (signedInUser == NULL)
    return;

  // GET user's inputted code
  while (inputTime < 5)
  {
    printf("Code: ");
    scanf("%s", inputCode);

    // If activate code is NOT wrong
    if (strcmp("LTM121216", inputCode) == 0)
    {
      printf("Account is activated");
      signedInUser->val.status = 1;
      updateUser(list, signedInUser->val, "status");
      return;
    }

    // Else if password IS WRONG
    printf("Activation code is incorrect\n");
    inputTime++;
  }

  // Block user if 5 times wrong
  if (inputTime == 5)
  {
    printf("Activation code is incorrect. Account is blocked\n");
    // BLOCK USER
    signedInUser->val.status = 0;
    updateUser(list, signedInUser->val, "status");
    return;
  }
}

// Handle file
void handleSearch(linkedList *list)
{
  char username[20];

  // Check if user is signed in or not
  if (currentSignInUser == NULL)
  {
    printf("Account is not sign in");
    return;
  }

  // Get user's input
  printf("\n---------Search---------\n");
  printf("Username: ");
  scanf("%s", username);

  // Check account exist
  Node *user = getUser(list, username);
  if (user == NULL)
  {
    printf("Cannot find account");
    return;
  }

  // Log to user account's status
  switch (user->val.status)
  {
  case 0:
    printf("Account is blocked");
    break;
  case 1:
    printf("Account is active");
    break;
  case 2:
    printf("Account is not activated");
    break;
  default:
    break;
  }
}

// Handle file
void handleChangePassword(linkedList *list)
{
  char newPassword[20];
  nodeValType user;

  // Check current user is signed in or NOT
  if (currentSignInUser == NULL)
  {
    printf("Account is not sign in");
    return;
  }

  // Get user's input
  printf("\n---------Change password---------\n");
  printf("Username: ");
  scanf("%s", user.username);
  printf("Password: ");
  scanf("%s", user.password);
  printf("NewPassword: ");
  scanf("%s", newPassword);

  // Check current password is NOT WRONG
  if (strcmp(currentSignInUser->val.password, user.password) != 0)
  {
    printf("Current password is incorrect. Please try again");
    return;
  }

  // Change password and save
  strcpy(user.password, newPassword);
  updateUser(list, user, "password");
  printf("Password is changed");
}

void handleLogOut(linkedList *list)
{
  char username[20];

  // Get user's input
  printf("\n---------Logging out---------\n");
  printf("Username: ");
  scanf("%s", username);

  // Check current user is signed in or NOT
  if (currentSignInUser == NULL || strcmp(currentSignInUser->val.username, username) != 0)
  {
    printf("Account is not sign in");
    return;
  }

  // Check user's account is exist
  if (getUser(list, username) == NULL)
  {
    printf("Cannot find account");
    return;
  }

  // Logging out user
  currentSignInUser = NULL;
  printf("Goodbye %s", username);
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

// Option is: "password", "name", "status"
void updateUser(linkedList *list, nodeValType user, char option[10])
{
  // Find user based on name
  Node *updateUser = getUser(list, user.username);

  // Update user's password and/or status
  if (strcmp(option, "password") == 0)
  {
    strcpy(updateUser->val.password, user.password);
  }
  if (strcmp(option, "status") == 0)
  {
    updateUser->val.status = user.status;
  }

  // Write to file
  writeListToFile(list);
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
    insertEnd(list, node);
  }

  // Close file
  fclose(file);
}

void appendDataToFile(FILE *file, nodeValType val)
{
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