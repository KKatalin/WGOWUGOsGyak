#include <sys/wait.h>

#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <string.h>



int main() {

     int pipefd[2];	

     pid_t cpid;	

     char buf;		

     char szoveg[32];	

     int ret;

     

     cpid = fork();

     if (cpid == -1) {

	   perror("fork");

	   exit(-1);

     }



     if (cpid == 0) {   

	   printf("%d: gyerek vagyok\n", getpid());

	   close(pipefd[0]);    



	   strcpy(szoveg, "KK WGOWUG");   

	   printf("%d: kuldom a szoveget: %s (%ld db. karakter)\n", getpid(), szoveg, strlen(szoveg));



	   write(pipefd[1], szoveg, strlen(szoveg));	



	   close(pipefd[1]);    

	   

	   exit(0);



     } else {	

	   printf("%d: szulo vagyok\n", getpid());

	   

	   if (pipe(pipefd) == -1) {	

	   	perror("pipe");

	   	exit(-1);

     	   }

     	   printf("%d: fd1: %d, fd2: %d\n", getpid(), pipefd[0], pipefd[1]);



   	   close(pipefd[1]);    

	   printf("%d: megnezem mi van a csoben\n%d: ", getpid(), getpid());

	   while (read(pipefd[0], &buf, 1) > 0) {	

		 printf("%c", buf);

	   }

	   printf("\n%d: lezartak a cso masik oldalat\n", getpid());



	   close(pipefd[0]);	

	

	   wait(NULL);    



   	   exit(0);	



     }

}