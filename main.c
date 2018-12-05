#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <unistd.h>
int main(){
  key_t key;
  int shmid;
  char * data;
  if(key = ftok("main.c",'R') == -1){
    perror("ftok ERROR");
    exit(1);
  }
  //Making our segment
  if((shmid = shmget(key,250,IPC_CREAT|0666)) ==-1 ){
    perror("shmget ERROR");
    exit(1);
  }
  //Attaching to pointer of segment
  data = shmat(shmid, (void *)0, 0);
  //char * input = malloc(200);
  printf("Segment just created and currently holds nothing\n");
  printf("Would you like to change the data? y/n\n");
  while(!fgets(data,250, stdin)){
  }
  data[strlen(data)-1] = '\0';
  if (strcmp(data,"y") == 0){
    printf("Please type what you want to change to: \n");
    fgets(data,250,stdin);
  }
  else if (strcmp(data,"n") == 0){
    printf("Nothing has been done\n");
  }
  else{
    printf("String was not either a y or a n\n");
  }

  printf("Here are my current contents: %s \n", data);
  char * input = malloc(100);
  printf("Would you like to delete segment? y/n\n");
  while(!fgets(input,100,stdin)){
  }

  input[strlen(input) - 1] = '\0';

  if (strcmp(input,"y") == 0){
    shmctl(shmid,IPC_RMID, NULL);
    printf("Segment Deleted. \n");
    exit(0);

  }
  else if (strcmp(input,"n") == 0){
    printf("Nothing has been done.\n");
    printf("Here are my current contents: %s \n", data);
    exit(0);
  }
  else{
    printf("String was not either a y or a n\n");
    printf("Here are my current contents: %s \n", data);
    exit(1);
  }

  return 0;
}
