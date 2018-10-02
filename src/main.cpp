#include <thread>
#include <iostream>
#include <vector>
#include <chrono>
using namespace std;
int usr1Happened = 1;

void SIGUSR1Handler(int);


int main(){
	pid_t pid;
	short numChildren;
	cout << "Parent PID: " << getpid() << endl;
	cout << "Enter the number of children(1-255): ";
	do{
		cin.clear();
		cin >> numChildren;
		cin.ignore(256, '\n');
	}while(cin.fail());

	for(int i = 0; i < numChildren; i++){
		if(pid == 0) break;
		pid = fork();


	}

	switch(pid){
		case -1:
			exit(-1);
			break;

		case 0:
			struct sigaction event;
			event.sa_flags = 0;
			event.sa_handler = SIGUSR1Handler;

			sigemptyset(&event.sa_mask);

			if(sigaction(SIGUSR1, &event, NULL) == -1){
				perror("sigaction");
				exit(1);
			}

			while(usr1Happened != 0);
			cout << "Child died." << endl;
			exit(-1);
			break;

		default:
			for(;numChildren;numChildren--)wait(NULL);
			cout << "All children died. Exiting." << endl;
			exit(0);
			break;

	}
}

void SIGUSR1Handler(int sig){
	cout << "SIGUSR1 processed on " << getpid() << endl;
	usr1Happened = 0;
}

