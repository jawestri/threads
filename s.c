#include <pthread.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
const int max = 10;
pthread_mutex_t m1;


/*
Case Study by: Jamie Westrick
This program incorporates the usage of threads, files, and IPC for 
random data generation and logging.  Random temperature values stored in
sensordata2.txt with timestamp
*/


/** Thread 1 */

void* thread1_body(void* args) {
  srand(time(NULL));
  int i;
  int r;
  char buffer[200];
  printf("ThreadA--welcome\n");
  pthread_mutex_lock(&m1);
  

/* Use of System calls to create/open file*/
  int fd = open("sensordata2.txt",O_WRONLY | O_CREAT | O_APPEND, 0666);
  if(fd < 0){
	perror("r1");
        exit(1);
  }
  for (i = 1; i <= max; i++) {
   time_t ltime = time(NULL);
   struct tm *ptm = localtime(&ltime);
   r = rand()%100;
/** Format string and write to txt file using system call */
   int len = sprintf(buffer,"temperature | %d | %02d:%02d:%02d \n", r, ptm->tm_hour,ptm->tm_min,ptm->tm_sec);
  write(fd,buffer,len);
  sleep(1);
  }
  close(fd);
  pthread_mutex_unlock(&m1);
  pthread_exit(NULL);
}





/** Thread 2 ==> concurrency
Both threads writing to same file ==> race conditions
Race conditions controlled using ==> MUTEX*/


void* thread2_body(void* args) {
  srand(time(NULL));
  int i;
  int r;
  char buffer[200];
  printf("ThreadB--welcome\n");
  pthread_mutex_lock(&m1);


/* Use of System calls to create/open file*/
  int fd = open("sensordata2.txt",O_WRONLY | O_CREAT | O_APPEND, 0666);
  if(fd < 0){
	perror("r1");
        exit(1);
  }
  for (i = 1; i <= max; i++) {
  time_t ltime = time(NULL); 
  struct tm *ptm = localtime(&ltime);
  r = rand()%100;
/** Format string and write to txt file using system call */
  int len = sprintf(buffer,"temperature | %d | %02d:%02d:%02d \n", r, ptm->tm_hour,ptm->tm_min,ptm->tm_sec);
  write(fd,buffer,len);
  sleep(1);

  }
  close(fd);
  pthread_mutex_unlock(&m1);
  pthread_exit(NULL);
}


int main() {
  pthread_t pt1, pt2;
  pthread_mutex_init(&m1,NULL);
  pthread_create(&pt1, NULL, thread1_body, NULL);
  pthread_create(&pt2, NULL, thread2_body, NULL);
  pthread_join(pt1, NULL);
  pthread_join(pt2, NULL);
  pthread_mutex_destroy(&m1);
  return 0;
}
