#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

// the given function
static void *hard_work(void *work) {
	int *amount = (int*) work;
	struct timespec t = {
			.tv_sec = 0,
			.tv_nsec = *amount *100000
	};
	nanosleep( &t, NULL ); // **Really** hard work
	return NULL;
}

// calculate execution time
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

// launch threads
void thread_launch(pthread_t const *tids, int limit) {
	for (int i = 0; i < limit; i++) {
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		int flag = pthread_create((pthread_t *)&tids[i], &attr, hard_work, (void *) &i);
		if (flag != 0) {
			printf("pthread_create error: error_code = %d\n", flag);
			exit(1);
		}
	}
}

// wait until a thread finish its work
void thread_wait(pthread_t const *tids, int limit) {
	for (int i = 0; i < limit; i++) {
		int flag = pthread_join(tids[i], NULL);
		if (flag != 0) {
			printf("pthread_join error: error_code = %d\n", flag);
			exit(1);
		}
	}
}

// run_threads running all threads
void run_threads(int num_threads, int num_runs, pthread_t *tids) {
	for (int i = 0; i < num_threads/num_runs; i++) {
		thread_launch(tids, num_runs);
		printf("Thread #%d-#%d are launched.\n", num_runs*i+1, num_runs*(i+1));
		thread_wait(tids, num_runs);
		printf("Thread #%d-#%d are on hold.\n", num_runs*i+1, num_runs*(i+1));
	}
	int left = num_threads % num_runs;
	if (left == 1) {
		thread_launch(tids, left);
		printf("Thread #%d is launched.\n", num_threads);
		thread_wait(tids, left);
		printf("Thread #%d is on hold.\n", num_threads);
	} else if (left != 0) {
		thread_launch(tids, left);
		printf("Thread #%d-#%d are launched.\n", num_threads - left+1, num_threads);
		thread_wait(tids, left);
		printf("Thread #%d-#%d are on hold.\n", num_threads - left+1, num_threads);
	}
}

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
	run_threads(num_threads, num_runs, tids);

	// count time ends
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &time2);
	printf("\nExecuting all threads costs %ld micro seconds.\n", diff(time1,time2).tv_nsec/1000);

	// ensure all threads are ended
	pthread_exit(NULL);
}
