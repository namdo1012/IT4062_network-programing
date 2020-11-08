#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strcicmp(char const *a, char const *b);
int searchAccount(singleList list, char username[BUFLEN]);
void blockAccount(singleList list, char username[BUFLEN]);
int checkBlocked(singleList list, char username[BUFLEN]); //if blocked, return 1
int checkCorrectPassword(singleList list, char username[BUFLEN], char pass[BUFLEN]);
int changePass(singleList accountList, char username[BUFLEN], char pass[BUFLEN], char new_pass[BUFLEN]);
int strcicmp(char const *a, char const *b);
int split_number_and_string(char *input, char *number, char *string);

int changePass(singleList accountList, char username[BUFLEN], char pass[BUFLEN], char new_pass[BUFLEN])
{
  accountList.cur = accountList.root;
  while (accountList.cur != NULL)
  {
    if ((strcicmp(accountList.cur->element.user_name, username) == 0) && (strcicmp(accountList.cur->element.password, pass) == 0))
    {
      strcpy(accountList.cur->element.password, new_pass);
      return 1;
    }
    accountList.cur = accountList.cur->next;
  }
  return 0;
}

int searchAccount(singleList list, char username[512])
{
  list.cur = list.root;
  // if existed , return 1
  // else return 0
  while (list.cur != NULL)
  {
    if (strcicmp(list.cur->element.user_name, username) == 0)
      return 1;
    list.cur = list.cur->next;
  }
  return 0;
}

int checkBlocked(singleList list, char username[512])
{
  list.cur = list.root;
  while (list.cur != NULL)
  {
    if (strcicmp(list.cur->element.user_name, username) == 0)
    {
      if (list.cur->element.status == 0)
      {
        return 1;
      }
      else
      {
        return 0;
      }
    }
    list.cur = list.cur->next;
  }
}

void blockAccount(singleList list, char username[512])
{
  list.cur = list.root;
  while (list.cur != NULL)
  {
    if (strcicmp(list.cur->element.user_name, username) == 0)
    {
      list.cur->element.status = 0;
      return;
    }
    list.cur = list.cur->next;
  }
}

int checkCorrectPassword(singleList list, char username[512], char pass[512])
{
  list.cur = list.root;
  while (list.cur != NULL)
  {
    if ((strcicmp(list.cur->element.user_name, username) == 0) && (strcicmp(list.cur->element.password, pass) == 0))
    {
      return 1;
    }
    list.cur = list.cur->next;
  }
  return 0;
}

int strcicmp(char const *a, char const *b)
{
  for (;; a++, b++)
  {
    int d = tolower((unsigned char)*a) - tolower((unsigned char)*b);
    if (d != 0 || !*a)
      return d;
  }
}

int split_number_and_string(char *input, char *number, char *string)
{
  // if number, copy to number
  // if character, copy to string
  int x = 0, y = 0;

  for (int i = 0; i < strlen(input); i++)
  {
    if (input[i] == '\0')
      break;
    if (input[i] >= '0' && input[i] <= '9')
    {
      number[x] = input[i];
      x++;
    }
    else if ((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z'))
    {
      string[y] = input[i];
      y++;
    }
    else
    {
      return 0;
    }
  }
  number[x] = '\0';
  string[y] = '\0';
  return 1;
}
