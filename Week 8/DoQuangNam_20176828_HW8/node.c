#include <stdio.h> 
#include <stdlib.h> 
#include <strings.h> 

#define SA struct sockaddr 
#define BUFF_SIZE 1024
typedef struct acc_node
{
  char username[20];
  char password[20];
  int status;
  struct acc_node *next;
}acc_node;

acc_node *head = NULL;
acc_node *login= NULL;

typedef struct users{
  char username[max];
  char password[max];
  int status;
  struct users *next;
}users;

users *head = NULL;
char onlineUser[max];
int isOnline = 0;
int number = 0;
pthread_mutex_t mutex;

users *CreateNode(){
    users *tmp = (users*)malloc(sizeof(users)); // Cấp phát vùng nhớ dùng malloc()
    tmp->next = NULL;// Cho next trỏ tới NULL
    return tmp;//Trả về node mới đã có giá trị
}


void AddNewUser(char un[max], char pw[max], int st){
    users *newuser = CreateNode(); // Khởi tạo node temp với data = value
    strcpy(newuser->username,un);
    strcpy(newuser->password,pw);
    newuser->status=st;

    if(head == NULL){
        head = newuser; //Nếu linked list đang trống thì Node temp là head luôn
    }else{
      users *tmp = head;
      while (tmp->next !=NULL) tmp = tmp->next;
      tmp->next = newuser; 
    }
}

//-----------------

void freeNode(){
  while (head) {  
        users *tmp = head;
        head = head->next;
        free(tmp);
  }
}
//==========================================
void readFile(){
    FILE *f;
    char str[100];
    char un[max];
    char pw[max];
    int status1;
    f = fopen("nguoidung.txt","r");
    if(f == NULL){
      printf("file not exit!");
      exit(1);
    }
    while(!feof(f)){
      fscanf(f, "%s",un);
      fscanf(f, "%s",pw);
      fscanf(f, "%d",&status1);
      AddNewUser(un,pw,status1);
    }
    fclose(f);
  }
//=======================================

void rewriteFile(){
  users *p;
  FILE *f;
  f = fopen("nguoidung.txt","w");
  for(p = head; p != NULL; p = p->next){
    if (p == head) fprintf(f,"%s %s %d", p->username, p->password, p->status);
    else fprintf(f,"\n%s %s %d", p->username, p->password, p->status);
  }
  fclose(f);
}

//========================================
void printNode(){
  users *p;
  printf("\n\n");
  for(p = head; p != NULL; p = p->next){
      printf("%s %s %d\n", p->username, p->password, p->status);
  }
  printf("----------------\n");
}

//==========================================
int CheckUserName(char un[max]){
    users *tmp;
    for(tmp = head; tmp != NULL; tmp = tmp->next){
        if(strcmp(tmp->username, un) == 0){
          return 1;
        }
    }
    return 0;
}
int CheckPassword(char un[max],char pw[max]){
    users *tmp;
    for(tmp = head; tmp != NULL; tmp = tmp->next){
        if (strcmp(tmp->username, un) == 0) {
            if(strcmp(tmp->password, pw) == 0)
                return 1;
            else return 0;
        }
    }
    return -1;
}

void checkStatus(char un[max],char pw[max], int st){
  users *tmp;
  for(tmp = head; tmp != NULL; tmp =  tmp->next){
      if(strcmp(tmp->username,un) == 0){
        if(CheckPassword(un,pw) == 1){
            //printf("...\n");
            tmp->status = st;
        }else tmp->status = st;
      }
    }
}
//================================================
int checkString(char tmp1[max], char str[max]){
    char tmp2[max];
    int j = 0, k =0;
    for(int i = 0; i< strlen(str); i++){
        if(isdigit(str[i])){
            tmp1[j] = str[i];
            j++;
        }else if(((int)str[i] >= 65 && (int)str[i] <= 90) || ((int)str[i] >= 97 && (int)str[i] <= 122)){
            tmp2[k] = str[i];
            k++;
        }else {
            return 0;
        }
    }
    tmp1[j] = '\0';
    tmp2[k] = '\0';
    strcat(tmp1,tmp2);
    return 1;
}