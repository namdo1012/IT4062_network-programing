#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "handle.h"
#include "linkedlist.h"
#include "file.h"

/* GLOBAL VAR*/
// Node *currentSignInUser = NULL;

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

// // Option is: "password", "name", "status"
// void updateUser(linkedList *list, nodeValType user, char option[10])
// {
//   // Find user based on name
//   Node *updateUser = getUser(list, user.username);

//   // Update user's password and/or status
//   if (strcmp(option, "password") == 0)
//   {
//     strcpy(updateUser->val.password, user.password);
//   }
//   if (strcmp(option, "status") == 0)
//   {
//     updateUser->val.status = user.status;
//   }

//   // Write to file
//   writeListToFile(list);
// }

// Return signin successfully user
Node *userAuth(linkedList *list, char username[1024])
{
  int inputTime = 0;
  Node *user;

  // Get user based on username
  user = getUser(list, username);
  if (user == NULL)
    return NULL;

  return user;
}

// void handleRegister(linkedList *list)
// {
//   nodeValType newUser;

//   // GET user's inputted info
//   printf("\n---------Register---------\n");
//   printf("Username: ");
//   scanf("%s", newUser.username);
//   printf("Password: ");
//   scanf("%s", newUser.password);

//   // Initial user's state = idle (2)
//   newUser.status = 2;

//   // Check if user is exist or not
//   if (getUser(list, newUser.username) != NULL)
//   {
//     printf("Account existed");
//     return;
//   }

//   // Insert new user to list
//   insertEnd(list, newUser);

//   // Update file
//   writeListToFile(list);

//   // After all, tell the user
//   printf("Successful registration. Activation required.");
// }

// void handleSignIn(linkedList *list)
// {
//   printf("\n---------Sign in---------\n");

//   // user authentication
//   Node *signedInUser = userAuth(list);

//   // After all, Hello User!
//   if (signedInUser != NULL)
//     printf("Hello %s\n", signedInUser->val.username);
// }

// // Handle file
// void handleActivate(linkedList *list)
// {
//   int inputTime = 0;
//   char inputCode[10];

//   printf("\n---------Activate account---------\n");

//   // user authentication
//   Node *signedInUser = userAuth(list);
//   if (signedInUser == NULL)
//     return;

//   // GET user's inputted code
//   while (inputTime < 5)
//   {
//     printf("Code: ");
//     scanf("%s", inputCode);

//     // If activate code is NOT wrong
//     if (strcmp("LTM121216", inputCode) == 0)
//     {
//       printf("Account is activated");
//       signedInUser->val.status = 1;
//       updateUser(list, signedInUser->val, "status");
//       return;
//     }

//     // Else if password IS WRONG
//     printf("Activation code is incorrect\n");
//     inputTime++;
//   }

//   // Block user if 5 times wrong
//   if (inputTime == 5)
//   {
//     printf("Activation code is incorrect. Account is blocked\n");
//     // BLOCK USER
//     signedInUser->val.status = 0;
//     updateUser(list, signedInUser->val, "status");
//     return;
//   }
// }

// // Handle file
// void handleSearch(linkedList *list)
// {
//   char username[20];

//   // Check if user is signed in or not
//   if (currentSignInUser == NULL)
//   {
//     printf("Account is not sign in");
//     return;
//   }

//   // Get user's input
//   printf("\n---------Search---------\n");
//   printf("Username: ");
//   scanf("%s", username);

//   // Check account exist
//   Node *user = getUser(list, username);
//   if (user == NULL)
//   {
//     printf("Cannot find account");
//     return;
//   }

//   // Log to user account's status
//   switch (user->val.status)
//   {
//   case 0:
//     printf("Account is blocked");
//     break;
//   case 1:
//     printf("Account is active");
//     break;
//   case 2:
//     printf("Account is not activated");
//     break;
//   default:
//     break;
//   }
// }

// // Handle file
// void handleChangePassword(linkedList *list)
// {
//   char newPassword[20];
//   nodeValType user;

//   // Check current user is signed in or NOT
//   if (currentSignInUser == NULL)
//   {
//     printf("Account is not sign in");
//     return;
//   }

//   // Get user's input
//   printf("\n---------Change password---------\n");
//   printf("Username: ");
//   scanf("%s", user.username);
//   printf("Password: ");
//   scanf("%s", user.password);
//   printf("NewPassword: ");
//   scanf("%s", newPassword);

//   // Check current password is NOT WRONG
//   if (strcmp(currentSignInUser->val.password, user.password) != 0)
//   {
//     printf("Current password is incorrect. Please try again");
//     return;
//   }

//   // Change password and save
//   strcpy(user.password, newPassword);
//   updateUser(list, user, "password");
//   printf("Password is changed");
// }

// void handleLogOut(linkedList *list)
// {
//   char username[20];

//   // Get user's input
//   printf("\n---------Logging out---------\n");
//   printf("Username: ");
//   scanf("%s", username);

//   // Check current user is signed in or NOT
//   if (currentSignInUser == NULL || strcmp(currentSignInUser->val.username, username) != 0)
//   {
//     printf("Account is not sign in");
//     return;
//   }

//   // Check user's account is exist
//   if (getUser(list, username) == NULL)
//   {
//     printf("Cannot find account");
//     return;
//   }

//   // Logging out user
//   currentSignInUser = NULL;
//   printf("Goodbye %s", username);
// }