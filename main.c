#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"

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

int getUserChoice()
{
  int choice = 0;

  displayMenu();
  scanf("%d", &choice);
  return choice;
}

/* BINARY FILE */

void readBinaryFileToList(linkedList *list)
{
  nodeValType node;

  // Open account file for reading
  FILE *file;
  if ((file = fopen("account.bin", "rb+")) == NULL)
  {
    printf("File not found!\n");
    return;
  }

  // Read to list
  while (!feof(file))
  {
    fscanf(file, "%s %s %d", node.username, node.password, &node.status);
    if (feof(file))
      break;
    insertEnd(list, node);
  }

  // Close file
  fclose(file);
}

void appendDataToBinaryFile(FILE *file, nodeValType val)
{
  printf("writting:..");
  fprintf(file, "%s %s %d\n", val.username, val.password, val.status);
}

void writeListToBinaryFile(linkedList *list)
{
  // Open account file for reading
  FILE *file;
  if ((file = fopen("account.bin", "ab")) == NULL)
  {
    printf("File not found!\n");
    return;
  }

  // Loop for list to write node to file
  Node *tmp = list->root;
  while (tmp != NULL)
  {
    appendDataToBinaryFile(file, tmp->val);
    tmp = tmp->next;
  }

  // Close file
  fclose(file);
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
    fscanf(file, "%s %s %d", node.username, node.password, &node.status);
    if (feof(file))
      break;
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
  if ((file = fopen("account2.txt", "a")) == NULL)
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
  // do
  // {
  //   // Display menu and get user's choice
  //   int choice = getUserChoice();

  //   // Do task
  //   switch (choice)
  //   {
  //   case 1:
  //     printf("Choice 1");
  //     // Handle register
  //     break;
  //   case 2:
  //     printf("Choice 2");
  //     // Handle signIn
  //     break;
  //   case 3:
  //     printf("Choice 3");
  //     // Handle search
  //     break;
  //   case 4:
  //     printf("Choice 4");
  //     // Handle signOut
  //     break;
  //   default:
  //     // Exit program
  //     return 0;
  //   }

  // } while (1);

  // displayMenu();
  // nodeValType newVal;
  // nodeValType newVal2;
  // nodeValType newVal3;
  // strcpy(newVal.username, "do quang nam");
  // strcpy(newVal.password, "12345");
  // newVal.status = 1;

  // strcpy(newVal2.username, "do quang nam");
  // strcpy(newVal2.password, "12345");
  // newVal2.status = 2;
  // strcpy(newVal3.username, "do quang nam");
  // strcpy(newVal3.password, "12345");
  // newVal3.status = 2;

  // // strcpy(newVal.username, "do quang nam");
  // // strcpy(newVal.password, "12345");
  // // newVal.status = 1;

  linkedList *list = createSingleList();
  readFileToList(list);

  // printf("Programing...");
  // insertBegin(list, newVal);
  // insertEnd(list, newVal2);
  // insertBegin(list, newVal3);
  // insertBegin(list, newVal2);
  // insertBegin(list, 1);
  // insertBegin(list, 4);
  // printSingleList(list);
  writeListToBinaryFile(list);

  linkedList *list_bin = createSingleList();
  readBinaryFileToList(list_bin);

  printSingleList(list_bin);
  return 0;
}