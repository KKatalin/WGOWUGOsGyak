#include <stdio.h>

#include <unistd.h>

#include <stdlib.h>

#include <sys/file.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <fcntl.h>

#include <string.h>

#include <sys/wait.h>



int main()

{

	pid_t cpid;	

	int fd, ret;

	char buf[32];



	buf[0] = 0;



	

	cpid = fork();

     	if (cpid == -1) {

	   perror("fork");

	   exit(-1);

     	}



	if (cpid == 0) {    

		 printf("%d: gyerek vagyok\n", getpid());

	

		fd = open("WGOWUG", O_RDWR);	

		if (fd == -1) {

	   		perror("open() hiba!");

	    		exit(-1);

		}

		

		strcpy(buf, "Kocsis Katalin");

		printf("irok a fifoba: %s:%ld\n", buf, strlen(buf));

		write(fd, buf, strlen(buf)); 

		

	} else {	

		printf("%d: szulo vagyok\n", getpid());

		

		ret = mkfifo("WGOWUG", 00666);	

		if (ret == -1) {

	    		perror("mkfifo() hiba!");

	    	exit(-1);

		}

		

		ret = read(fd, buf, 32); 

		printf("read() olvasott %d byteot, ami a kovetkezo: %s\n", ret, buf);

		wait(NULL);    

	   

		exit(0);

	}



	close(fd);



	unlink("WGOWUG");	

}



