#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define MAXSIZE 3

/* variables */
int fd[2];		// pipe ends
pid_t pid;		// child process pid
ssize_t chars_read;		// number of chars read
char buff[MAXSIZE];		// buffer for chars required modification
char* key_str = "catCAT";		// substring to be replaced
char* new_str = "dogDOG";		// substring actually outputted

/* function: replace a specific string */
static void str_replace(const char* old, const char* new) {
	for (int i = 0; i < (int)strlen(buff) - 2; i++) {
		if (buff[i] == old[0] || buff[i] == old[3]) {
			if (buff[i + 1] == old[1] || buff[i + 1] == old[4]) {
				if (buff[i + 2] == old[2] || buff[i + 2] == old[5]) {
					buff[i] = new[0];
					buff[i + 1] = new[1];
					buff[i + 2] = new[2];
				}
			}
		}
	}
}

/* function: handle signals */
static void signal_handler(int sig) {
	if (sig == SIGUSR1) {
		key_str = "dogDOG";
		new_str = "catCAT";
	} else if (sig == SIGUSR2) {
		key_str = "catCAT";
		new_str = "dogDOG";
	} else if (sig == SIGALRM) {
		key_str = "";
		new_str = "";
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
	if (signal(SIGALRM, signal_handler) == SIG_ERR) {
		perror("SIGALRM error!\n");
		exit(1);
	}
}

/* function: main */
int main(int argc, char *argv[]) {
	/* must pass 1 argument */
	if (argc < 2) {
		perror("usage: ./a2q1 <executable>\n");
		exit(1);
	}

	/* create a pipe */
	if (pipe(fd) < 0) {
		perror("pipe error!\n");
		exit(1);
	}

	/* fork off a process */
	if ((pid = fork()) < 0) {
		perror("fork error!\n");
		exit(1);
	} else if (pid == 0) {
		/* child process, its stdout is the write end */
		close(fd[0]);	// no need the read end of pipe
		dup2(fd[1], STDOUT_FILENO);	// let the write end of pipe be stdout
		close(fd[1]);	// no need the write end after dup2

		/* execute argv[1] in the child process */
		if (execvp(argv[1], argv+1) < 0) {
			perror("exec error!\n");
			exit(1);
		}
	} else {
		/* parent process, takes input from read end */
		close(fd[1]);	// no need the write end of pipe

		/* register handlers */
		handler_reg();

		/* read and write through the pipe */
		while ((chars_read = read(fd[0], buff, MAXSIZE)) > 0) {
			buff[chars_read] = '\0';	// ensure stdout appears no strange symbols
			str_replace(key_str, new_str);	// default behavior of the parent process
			write(STDOUT_FILENO, buff, strlen(buff)+1);	// write to stdout
		}
	}
	return 0;
}
