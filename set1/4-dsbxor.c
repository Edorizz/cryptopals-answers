/* C library */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define BUF_SIZ	256

int
htoi(char ch)
{
	ch = tolower(ch);
	return ch >= '0' && ch <= '9' ? ch - '0' : ch - 'a' + 10;
}

int
main(int argc, char **argv)
{
	char buf[BUF_SIZ], encrypted[BUF_SIZ], *nl;
	int i, j, score, max_score, best_score, key, best_key, byte;

	best_score = best_key = 0;

	while (fgets(buf, BUF_SIZ, stdin)) {
		if ((nl = strchr(buf, '\n')) == NULL) {
			fprintf(stderr, "Error: input too large (max %d)\n", BUF_SIZ - 1);
			break;
		}

		*nl = '\0';
		for (i = max_score = key = 0; i != 0x100; ++i) {
			for (j = score = 0; j != strlen(buf); j += 2) {
				byte = (htoi(buf[j]) << 4) + htoi(buf[j + 1]) ^ i;
				if ((byte < ' ' || byte > '~') && byte != '\t' && byte != '\n') {
					score = 0;
					break;

				} else {
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
			}

			if (score > max_score) {
				max_score = score;
				key = i;
			}
		}

		if (max_score > best_score) {
			strcpy(encrypted, buf);
			best_score = max_score;
			best_key = key;
		}
	}

	printf("%d = ", best_key);
	for (i = 0; i != strlen(encrypted); i += 2) {
		putchar((htoi(encrypted[i]) << 4) + htoi(encrypted[i + 1]) ^ best_key);
	}
	putchar('\n');

	return 0;
}

