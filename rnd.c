/* rnd.c -- program to generate a random sequence.
 * Author: Luis Colorado <luiscoloradourcola@gmail.com>
 * Date: Mon Nov 25 09:06:22 EET 2019
 * Copyright: (C) 2019 LUIS COLORADO.  All rights reserved.
 * License: BSD.
 */

#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

unsigned N = 100;
int *array;
int seed;
int flags;

#define F(_f) __FILE__":%d: " _f, __LINE__

#define FLAG_SETSEED	(1 << 0)
#define FLAG_SHOWSEED	(1 << 1)
#define FLAG_SETRNDSEED	(1 << 2)

int getuint(const char *val, unsigned def)
{
	unsigned res = def;
	if (sscanf(val, "%u", &res) != 1) {
		fprintf(stderr,
			F("%s: not a number, setting to %u\n"),
			val, def);
	}
	return res;
} /* getuint */

int main(int argc, char **argv)
{
	int opt;

	while((opt = getopt(argc, argv, "n:rs:v")) != EOF) {
		switch(opt) {
		case 'n':
			N = getuint(optarg, N);
			break;
		case 'r':
			flags |= FLAG_SETRNDSEED;
			break;
		case 's':
			flags |= FLAG_SETSEED;
			seed = getuint(optarg, seed);
			break;
		case 'v':
			flags |= FLAG_SHOWSEED;
			break;
		} /* switch */
	} /* while */

	if (flags & FLAG_SETRNDSEED) {
		struct timespec now;
		int res = clock_gettime(CLOCK_REALTIME, &now);
		if (res < 0) {
			fprintf(stderr,
				F("clock_gettime: %s (errno = %d)\n"),
				strerror(errno), errno);
			exit(EXIT_FAILURE);
		}
		seed = now.tv_sec ^ now.tv_nsec;
	}

	srandom(seed);

	if (flags & FLAG_SHOWSEED) {
		fprintf(stderr,
			F("seed: %i\n"),
			seed);
	}

	int i;
	array = malloc(N*sizeof(*array));

	for (i = 0; i < N; i++)
		array[i] = i;

	char *sep = "";
	int col = 0;

	for (i = 0; i < N; i++) {
		int j = i + random() % (N - i);
		if (i != j) {
			int z = array[i];
			array[i] = array[j];
			array[j] = z;
		}
		col += printf("%s", sep);
		if (col >= 70) {
			col = 0;
			printf("\n");
		}
		col += printf("%u", array[i]);
		sep = " ";
	}

	if (col)
		printf("\n");
	exit(EXIT_SUCCESS);
}	
