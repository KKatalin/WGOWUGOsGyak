#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>

int main (int argc, char *argv[],char *env[])
{
	int status, pid, ppid, gpid;
	
	ppid = getpid();       

	if ((pid = fork()) == 0)   
	{ 	
		printf("\n A gyermek pid = %d \n", getpid());
		status = execl(strcat(env[0]+5, "/home/osboxes/OS feladatok"), "child", (char *)0);
		if (status == -1)
		{	perror("parent execl failed");
			exit (0);
		}
	}

	
	
	printf("\n %d.sz. szulo var a %d.sz. gyermekre.\n ", ppid,pid);
	if (pid != wait(&status)) perror(" Szulo - varakozas hiba ");
}
