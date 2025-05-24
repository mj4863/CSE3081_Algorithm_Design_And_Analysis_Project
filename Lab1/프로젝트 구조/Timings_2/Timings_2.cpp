#include <stdio.h>
#include "measure_cpu_time.h"
#include "test.h"

#define CMAX 1000000000 

void test0(int N, unsigned int *x, unsigned int *xx) {
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= i; j++)
			for (int k = 1; k <= j; k++) {
				(*x)++; // how many times?
				if (*x == CMAX) {
					(*xx)++;
					*x = 0;
				}
			}
}

void main(void) {
	unsigned int n, count, count2;

	fprintf(stdout, "************* test0 ****************\n");

	n = 512;
	count = count2 = 0;
	CHECK_TIME_START(_start, _freq);
	test0(n, &count, &count2);
	CHECK_TIME_END(_start, _end, _freq, _compute_time);
	fprintf(stdout, "*** n = %u --> count2 = %u, count = %u\n", n, count2, count);
	fprintf(stdout, "    run time = %.3fms \n", _compute_time);

	n = 2048;
	count = count2 = 0;
	CHECK_TIME_START(_start, _freq);
	test0(n, &count, &count2);
	CHECK_TIME_END(_start, _end, _freq, _compute_time);
	fprintf(stdout, "*** n = %u --> count2 = %u, count = %u\n", n, count2, count);
	fprintf(stdout, "    run time %.3fms \n", _compute_time);

	n = 4096;
	count = count2 = 0;
	CHECK_TIME_START(_start, _freq);
	test0(n, &count, &count2);
	CHECK_TIME_END(_start, _end, _freq, _compute_time);
	fprintf(stdout, "*** n = %u --> count2 = %u, count = %u\n", n, count2, count);
	fprintf(stdout, "    run time %.3fms \n", _compute_time);

	print_test();
}