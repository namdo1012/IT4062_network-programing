#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readDataFromFile(singleList *list);
void alterDataOfFile(singleList list);

void readDataFromFile(singleList *list)
{
  elementtype element;
  FILE *fp;
  fp = fopen("nguoidung.txt", "r");
  char chr = getc(fp);
  int count_lines = 0;
  while (chr != EOF)
  {
    //Count whenever new line is encountered
    if (chr == '\n')
    {
      count_lines = count_lines + 1;
    }
    //take next character from file.
    chr = getc(fp);
  }
  fseek(fp, 0, SEEK_SET);
  for (int i = 0; i < count_lines; i++)
  {
    fscanf(fp, "%s %s %d", element.user_name, element.password, &element.status);
    insertEnd(list, element);
  }
  fclose(fp);
}

void alterDataOfFile(singleList list)
{
  FILE *fp;
  fp = fopen("nguoidung.txt", "w");
  if (fp == NULL)
  {
    printf("No file input\n");
    return;
  }
  list.cur = list.root;
  while (list.cur != NULL)
  {
    fputs(list.cur->element.user_name, fp);
    fputs(" ", fp);
    fputs(list.cur->element.password, fp);
    fputs(" ", fp);
    fprintf(fp, "%d", list.cur->element.status);
    fputs("\n", fp);
    list.cur = list.cur->next;
  }
  fclose(fp);
  return;
}
