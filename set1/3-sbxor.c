/* C library */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

#define ABS(n)		((n) < 0 ? -(n) : (n))
#define MAX(a, b)	((a) > (b) ? (a) : (b))

int
htoi(char ch)
{
	ch = tolower(ch);
	return ch >= '0' && ch <= '9' ? ch - '0' : ch - 'a' + 10;
}

int
score_str(char *str)
{
	int curr_siz, letter_cnt, word_cnt;

	curr_siz = letter_cnt = word_cnt = 0;
	do {
		if (isblank(*str) || *str == '\0') {
			if (curr_siz > 0) {
				letter_cnt += curr_siz;
				curr_siz = 0;
				++word_cnt;
			}

		} else if (isalpha(*str)) {
			++curr_siz;
		}
	} while (*str++);

	return MAX(0, 10 - ABS(5 - (letter_cnt / word_cnt)));
}

int
main(int argc, char **argv)
{
	char str[] = { "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736" };
	char *buf;
	int i, j, k, ch, max_score, key, score;
	uint8_t byte;

	buf = malloc((sizeof str - 1) / 2 + 1);
	max_score = key = 0;

	printf("Printing possible answers:\n");
	for (i = 0; i != 0x100; ++i) {
		for (j = k = 0; j < sizeof str - 1; j += 2, ++k) {
			byte = ((htoi(str[j]) << 4) + htoi(str[j + 1])) ^ i;
			if (!(byte >= ' ' && byte <= '~')) {
				break;
			}

			buf[k] = byte;
		}

		buf[k] = '\0';
		if (j == sizeof str - 1) {
			score = score_str(buf);
			if (score > max_score) {
				max_score = score;
				key = i;
			}

			printf("0x%x  [%d]: %s\n", i, score, buf);
		}
	}

	for (i = j; i != sizeof str - 1; i += 2, ++j) {
		buf[j] = (htoi(str[i]) << 4) + htoi(str[i + 1]) ^ key;
	}
	printf("\nThe correct key is most likey [0x%x] which produces the string\n\"%s\"\n", key, buf);

	return 0;
}
