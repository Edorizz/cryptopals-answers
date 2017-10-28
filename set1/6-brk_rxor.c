/* C library */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
/* POSIX */
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define KEY_SIZ_RANGE_LO	2
#define KEY_SIZ_RANGE_HI	40

int
hamming(const unsigned char *s1, const unsigned char *s2, int cnt)
{
	unsigned char byte;
	int h;

	h = 0;
	while (cnt--) {
		for (byte = *s1++ ^ *s2++; byte; byte >>= 1) {
			if (byte & 0x1) {
				++h;
			}
		}
	}

	return h;
}

int
htoi(int ch)
{
	ch = tolower(ch);
	return ch >= '0' && ch <= '9' ? ch - '0' : ch - 'a' + 10;
}

int
main(int argc, char **argv)
{
	unsigned char *data, byte;
	int i, j, k, score, best_score, best_key, best_siz, data_siz, fd;
	float curr_hamming, best_hamming;

	if (argc < 2) {
		fprintf(stderr, "usage: %s binary_input\n", argv[0]);
		return 0;
	}

	if ((fd = open(argv[1], O_RDONLY)) < 0) {
		perror("open");
		return 1;
	}

	data_siz = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);

	data = malloc(data_siz);
	read(fd, data, data_siz);

	best_hamming = INFINITY;
	for (i = KEY_SIZ_RANGE_LO; i <= KEY_SIZ_RANGE_HI; ++i) {
		for (j = curr_hamming = 0; i * (j + 2) <= data_siz; ++j) {
			curr_hamming += hamming(data + j * i, data + i + j * i, i);
		}

		if ((curr_hamming /= j * i) < best_hamming) {
			best_hamming = curr_hamming;
			best_siz = i;
		}
	}

	for (i = 0; i != best_siz; ++i) {
		for (j = best_score = best_key = 0; j != 0xff; ++j) {
			for (k = i, score = 0; k < data_siz; k += best_siz) {
				byte = data[k] ^ j;
				if ((byte < ' ' || byte > '~') && byte != '\n' && byte != '\t' && byte != '\t') {
					score = 0;
					break;
				}

				switch (byte) {
				case 'e':	++score;
				case 't':	++score;
				case 'a':	++score;
				case 'o':	++score;
				case 'i':	++score;
				case 'n':	++score;
				case ' ':	++score;
				case 's':	++score;
				case 'h':	++score;
				case 'r':	++score;
				case 'd':	++score;
				case 'l':	++score;
				case 'u':	++score;
				}
			}

			if (score > best_score) {
				best_score = score;
				best_key = j;
			}
		}

		putchar(best_key);
	}

	return 0;
}

