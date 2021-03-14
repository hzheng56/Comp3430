#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

/* variables */
pid_t pid;		// child process pid

/* function: handle signals */
void signal_handler(int sig) {
	if (sig == SIGUSR1) {
		char* rec1 = "SIGUSR1 handled.\n";
		write(STDOUT_FILENO, rec1, strlen(rec1)+1);
	} else if (sig == SIGUSR2) {
		char* rec2 = "SIGUSR2 handled.\n";
		write(STDOUT_FILENO, rec2, strlen(rec2)+1);
	}
}

/* function: register signal handlers */
static void handler_reg() {
	if (signal(SIGUSR1, signal_handler) == SIG_ERR) {
		perror("SIGUSR1 error!\n");
		exit(1);
	}
	if (signal(SIGUSR2, signal_handler) == SIG_ERR) {
		perror("SIGUSR2 error!\n");
		exit(1);
	}
}

/* function: main */
int main(int argc, char *argv[]) {
	/* must pass 1 argument */
	if (argc < 2) {
		perror("usage: ./a2q2 <executable>\n");
		exit(1);
	}

	/* fork off a process */
	if ((pid = fork()) < 0) {
		perror("fork error!\n");
		exit(1);
	} else if (pid == 0) {
		/* child process, register signal handlers */
		handler_reg();

		/* signals test */
		for (int i = 0; i < 6; i++) {
			fflush(stdout);
			sleep(1);
			printf("child counted %d...\n", i+1);
		}
	} else {
		/* parent process, send 2 same/different signals */
		if (atoi(argv[1]) == 1) {
			sleep(3);
			kill(pid, SIGUSR1);
			kill(pid, SIGUSR1);
		} else if (atoi(argv[1]) == 2) {
			sleep(3);
			kill(pid, SIGUSR1);
			kill(pid, SIGUSR2);
		}
	}
	return 0;
}
