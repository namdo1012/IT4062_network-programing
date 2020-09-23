// /* BINARY FILE */

// void readBinaryFileToList(linkedList *list)
// {
//   int i;
//   nodeValType node;

//   // Open account file for reading
//   FILE *file;
//   if ((file = fopen("account.bin", "rb+")) == NULL)
//   {
//     printf("File not found!\n");
//     return;
//   }

//   // Read to list
//   while (!feof(file))
//   {
//     fread(&node, sizeof(nodeValType), 1, file);
//     printf("%d\n", i++);
//     // printf("%s %s %d", node.username, node.password, node.status);
//     // fscanf(file, "%s %s %d", node.username, node.password, &node.status);
//     if (feof(file))
//       break;
//     insertEnd(list, node);
//   }

//   printf("At last: i = %d", i);
//   // Close file
//   fclose(file);
// }

// void appendDataToBinaryFile(FILE *file, nodeValType val)
// {
//   printf("writting:..");
//   fwrite(&val, sizeof(nodeValType), 1, file);

//   // fprintf(file, "%s %s %d\n", val.username, val.password, val.status);
// }

// void writeListToBinaryFile(linkedList *list)
// {
//   // Open account file for reading
//   FILE *file;
//   if ((file = fopen("account.bin", "ab")) == NULL)
//   {
//     printf("File not found!\n");
//     return;
//   }

//   // Loop for list to write node to file
//   Node *tmp = list->root;
//   while (tmp != NULL)
//   {
//     appendDataToBinaryFile(file, tmp->val);
//     tmp = tmp->next;
//   }

//   // Close file
//   fclose(file);
// }