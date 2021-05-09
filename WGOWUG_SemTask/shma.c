#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHMKEY 123456L

int main() {

	int shmid;		
	key_t key;		
	int size = 512;		
	int shmflg;		
	char readData[512-sizeof(int)];
	FILE * filePointer;
	
	struct segmStruct {
		int  textLength;
		char text[512-sizeof(int)];
	} *segm;		
	
	
	filePointer = fopen("nagyFajl.txt", "r");
	printf("Content of the read file:\n");
	while(fgets(readData, 512-sizeof(int), filePointer) != NULL) {
		printf("%s", readData);
	}
	fclose(filePointer);
	printf("Data successfully read from file nagyFajl.txt\n");
        printf("The file is now closed.");
	//size = sizeof(readData);

	
	key = SHMKEY;
	shmflg = 0;
	if ((shmid = shmget(key, size, shmflg)) < 0) {
		printf("\n Such a segment doesn't exist yet! Let's create it!");
		shmflg = 00666 | IPC_CREAT; 
		
	
		if ((shmid=shmget(key, size, shmflg)) < 0) {
	      perror("\nThe shmget system-call failed!");
	      exit(-1);
		}
	} else printf("The segment already exists!\n!");

	printf("ID of the shared memory: %d \n", shmid);
	
	// attach: hogy tudjak a szegmensbe irni, rácsatlakozok ezzel a processzel
	shmflg = 00666 | SHM_RND;
	segm = (struct segmStruct *)shmat(shmid, NULL, shmflg); 

	if (segm == (void *)-1) {
		perror(" Sikertelen attach");
		exit (-1);
	}
	
	strcpy(segm->text, readData);
	
	
	shmdt(segm);

	printf("ID of the shared memory segment, call the other process with this: %d\n", shmid);
	
	exit(0);
}