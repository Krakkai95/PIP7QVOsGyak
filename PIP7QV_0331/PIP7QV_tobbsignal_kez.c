#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

void handleSignal();

int main(){
signal(SIGINT, handleSignal); 
signal(SIGQUIT, handleSignal);
for (int i=0; i<10; i++){ 
	printf("Varakozunk...\n");
	pause();
}
return 0;
}

void handleSignal(int sig){
char desc[50];
switch(sig){
	case 1: {
	strcpy(desc, "Hangup Signal");
	break;
	}

	case 2: {
	strcpy(desc, "Interrupt Signal");
	signal(SIGINT, SIG_DFL);
	printf("\nA CTRL + C be fogja zarni a programot!");
	break;
	}

	case 3: {
	strcpy(desc, "Quit Signal");
	break;
	}

	case 4: {
	strcpy(desc, "Illegal Instruction Signal");
	break;
	}

	case 5: {
	strcpy(desc, "Trace Trap Signal");
	break;
	}

	case 6: {
	strcpy(desc, "Abort Signal");
	break;
	}
}//Switch
printf("\nAz elkapott jel: %s\n", desc); 