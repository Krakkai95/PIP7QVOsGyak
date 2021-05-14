#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
	printf("[fo process] pid: %d\n", getpid());

	pid_t firstChild = fork(); 
	pid_t secondChild = fork();

	if((firstChild == 0 || secondChild == 0) && (firstChild != 0 || secondChild != 0) )  // fork succeeded 
	{   
		printf("[gyerek] pid: %d, [szulo] pid: %d\n", getpid(), getppid());
		int status;
		pid_t children[3];
		for (int i = 0; i < 3; i++ ) {
			children[i] = fork();

			if (!(children[0] != 0 && children[1] != 0 && children[2] != 0)) // ha nem fo process
			{
				printf("[unoka] pid: %d, [szulo] pid: %d\n", getpid(), getppid());
				sleep(3);
				exit(0);
			} 
		}
		waitpid(children[0], &status, 0);
	    waitpid(children[1], &status, 0);
		waitpid(children[2], &status, 0); 

		exit(0);
	}
	else if (firstChild != 0 && secondChild != 0)  // Main (parent) process after fork succeeds 
	{    
	    int firstChildReturnStatus;    
	    int secondChildReturnStatus;    

	    waitpid(firstChild, &firstChildReturnStatus, 0);  // Parent process waits here for child to terminate.
	    waitpid(secondChild, &secondChildReturnStatus, 0);  // Parent process waits here for child to terminate.

	    if (firstChildReturnStatus == 0 && secondChildReturnStatus == 0)  // Verify child process terminated without error.  
	    {
	       printf("A gyerek processek vartak 3 masodpercet, majd sikeresen befejezodtek.\n");    
	    }
	    else
	    {
	    	printf("A gyerekek hibaval fejeleződtek be.\n");
	    }
	}
}