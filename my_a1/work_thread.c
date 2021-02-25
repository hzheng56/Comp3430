#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

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

/* launch threads */
void thread_launch(pthread_t const *tids, int limit) {
	for (int i = 0; i < limit; i++) {
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		int flag = pthread_create((pthread_t *)&tids[i], &attr, hard_work, &c);
		if (flag != 0) {
			printf("pthread_create error: error_code = %d\n", flag);
			exit(1);
		}
	}
}

/* wait until a thread finish its work */
void thread_wait(pthread_t const *tids, int limit) {
	for (int i = 0; i < limit; i++) {
		int flag = pthread_join((pthread_t)tids[i], NULL);
		if (flag != 0) {
			printf("pthread_join error: error_code = %d\n", flag);
			exit(1);
		}
	}
}

/* run_threads running all threads */
void run_threads(pthread_t *tids, int num_runs, int num_threads) {
	for (int i = 0; i < num_threads/num_runs; i++) {
		thread_launch(tids, num_runs);
		thread_wait(tids, num_runs);
	}
	int left = num_threads % num_runs;
	if (left != 0) {
		thread_launch(tids, left);
		thread_wait(tids, left);
	}
}

/* main function */
int main(int argc, char *argv[]) {
	// ensure correct input parameters
	if (argc < 2) {
		fprintf(stderr, "usage: ./thread <#threads> <#threads per time>\n");
		exit(1);
	}

	// count time begins
	struct timespec time1, time2;
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &time1);

	// run functions
	int num_threads = atoi(argv[1]);
	int num_runs = atoi(argv[2]);
	pthread_t tids[num_threads];	// declare all threads
	run_threads(tids, num_runs, num_threads);
	
	// count time ends
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &time2);
	printf("\nRun experiment with %s threads, %s of them at a time.\n", argv[1], argv[2]);
	printf("Executing all threads costs %ld microseconds.\n\n", diff(time1,time2).tv_nsec/1000);

	// ensure all threads are ended
	pthread_exit(NULL);
}
