#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <stdio.h>  
#include "rot13Messenger_main.c"
  
int main() 
{ 
    // ftok to generate unique key 
    key_t key = ftok("shmfile",65); 

    printf("%d\n", IPC_CREAT);
    // shmget returns an identifier in shmid 
    int shmid = shmget(key,1024,0666|IPC_CREAT); 

    /*
    0666 | 512 = MASKING
    1010011010
    1000000000
    1010011010 = 66610
    */

  
    // shmat to attach to shared memory 
    char* str = (char*) shmat(shmid,(void*)0,0);
    //char* myvar; 
    char* s = str;
    printf("Write Data : \n"); 
    scanf("%s", s);
    sprintf(str, "%s", encodeRot13String(str));
    printf("Data written in memory: %s\n",str); 
      
    //detach from shared memory  
    shmdt(str); 
  
    return 0; 
}
