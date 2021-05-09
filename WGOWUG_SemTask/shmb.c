#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int argc, char*argv[]) {
	
	if (argc == 2) {
		int shmid = atoi(argv[1]);
		int shmflg;
		FILE * filePointer;
		
		struct segmStruct {
			int  textLength;
			char text[512-sizeof(int)];
		} *segm;		

		// attach
		shmflg = 00666 | SHM_RND;
		segm = (struct segmStruct *)shmat(shmid, NULL, shmflg); 

		if (segm == (void *)-1) {
			perror("Attach failed!\n");
			exit (-1);
		}
		
		segm->textLength=strlen(segm->text);

		if (segm->textLength > 0) {
			printf("\nThe text in the shared memory: %s (on %d length\n)",segm->text,segm->textLength);
		} else {
			printf("There is no text in the shared memory!");
			exit(-1);
		}

		filePointer = fopen("masikFajl.txt", "w");
		if (fputs(segm->text, filePointer) == EOF) {
			printf("Unsuccesful writing to file!\n");
		} else {
			printf("Successful writing to file!\n");
		}
		fclose(filePointer);
		
		
		shmdt(segm);
		
		
		shmctl(shmid,IPC_RMID,NULL);

		exit(0);

	} else { printf("Tul sok vagy tul keves parametert adott meg!");
		exit(-1);
	}
}