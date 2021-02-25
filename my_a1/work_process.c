#include <stdio.h>
#include <stdlib.h>
#include <sys/errno.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int c = 1; // constant for hard_work()

/* the given function */
static void *hard_work(void *work) {
	int *amount = (int*) work;
	struct timespec t = {
			.tv_sec = 0,
			.tv_nsec = *amount *100000
	};
	nanosleep( &t, NULL ); // **Really** hard work
	return NULL;
}

/* calculate execution time */
struct timespec diff(struct timespec start, struct timespec end) {
	struct timespec temp;
	if ((end.tv_nsec-start.tv_nsec)<0) {
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	} else {
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}

/* launch child processes */
void child_launch(pid_t *pids, int limit) {
	for (int i = 0; i < limit; i++) {
		if ((pids[i] = fork()) == 0) {
			if (pids[i] < 0) {
				printf("fork create error: error_code = %d\n", getpid());
			} else if (pids[i] == 0) {
				hard_work(&c);
				exit(0);
			}
		}
	}
}

/* parent wait for children */
void parent_wait(pid_t const *pids, int limit) {
	for (int i = 0; i < limit; i++) {
		wait((pid_t *)&pids[i]);
	}
}

/* run_threads running all processes */
void run_processes(pid_t *pids, int num_runs, int num_processes) {
	for (int i = 0; i < num_processes / num_runs; i++) {
		child_launch(pids, num_runs);
		parent_wait(pids, num_runs);
	}

	// if argv[1] is not divisible by argv[2]
	int left = num_processes % num_runs;
	if (left != 0) {
		child_launch(pids, left);
		parent_wait(pids, left);
	}
}

/* exit parent after all children ends, remove zombies */
void remove_zombies() {
	while (1) {
		int flag = wait(NULL);
		if (flag == -1) {
			if (errno == EINTR) { // no more child
				continue;
			}
			break;
		}
	}
}

/* main function */
int main(int argc, char *argv[]) {
	// ensure correct input parameters
	if (argc < 2) {
		fprintf(stderr, "usage: ./process <#processes> <#processes per time>\n");
		exit(1);
	}

	// count time begins
	struct timespec time1, time2;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time1);

	// run functions
	int num_processes = atoi(argv[1]);
	int num_runs = atoi(argv[2]);
	pid_t pids[num_processes];
	run_processes(tids, num_runs, num_processes);
	remove_zombies();
	
	// count time ends
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time2);
	printf("\nRun experiment with %s processes, %s of them at a time.\n", argv[1], argv[2]);
	printf("Executing all processes costs %ld microseconds.\n\n", diff(time1,time2).tv_nsec/1000);

	return 0;
}
