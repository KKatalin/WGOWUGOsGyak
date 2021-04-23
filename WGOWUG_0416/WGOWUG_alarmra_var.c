#include <unistd.h>
#include <signal.h>
#include<stdio.h>



void do_nothing();


int main ()
{


	signal(SIGALRM, do_nothing);
	printf( "varok de meddig?\n");
	pause();
    	printf("  Vegre, itt az alarm \n");
}	
void do_nothing(){ ;}