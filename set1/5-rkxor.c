/* C library */
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

#define BUF_SIZ	256

#define INVALID	-1
#define ENCODE	0
#define DECODE	1

int
htoi(char ch)
{
	ch = tolower(ch);
	return ch >= '0' && ch <= '9' ? ch - '0' : ch - 'a' + 10;
}

int
main(int argc, char **argv)
{
	char *key;
	int ch, ch2, key_i, key_len, i, mode;
	uint8_t byte;

	key = NULL;
	mode = INVALID;
	for (i = 1; i != argc; ++i) {
		if (argv[i][0] == '-') {
			switch (argv[i][1]) {
			case 'd':
				mode = DECODE;
				break;

			case 'e':
				mode = ENCODE;
				break;
			}

		} else {
			key = argv[i];
		}
	}
	
	if (key == NULL) {
		fprintf(stderr, "Error: Expected key; not given\n");
		return 1;
	}

	key_i = 0;
	key_len = strlen(key);

	if (mode == ENCODE) {
		while ((ch = getchar()) != EOF) {
			printf("%02x", ch ^ key[key_i++]);
			if (key_i >= key_len) {
				key_i = 0;
			}
		}

	} else if (mode == DECODE) {
		/* Can be done with just a single 'ch' variable, but this might be more readable */
		while (isxdigit(ch = getchar()) && isxdigit(ch2 = getchar())) {
			putchar((htoi(ch) << 4) + htoi(ch2) ^ key[key_i++]);
			if (key_i >= key_len) {
				key_i = 0;
			}
		}

	} else {
		fprintf(stderr, "Error: Wrong program mode [%d] (not encoding nor decoding); what happened?\n", mode);
	}

	putchar('\n');

	return 0;
}

