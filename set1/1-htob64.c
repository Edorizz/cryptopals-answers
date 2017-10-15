/* C library */
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <ctype.h>

/* Might be better to use a switch statement */
const char base64[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
			'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
			'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
			'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
			'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
			'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
			'w', 'x', 'y', 'z', '0', '1', '2', '3',
			'4', '5', '6', '7', '8', '9', '+', '/' };
int
htoi(char c)
{
	c = tolower(c);
	return c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10;
}

int
is_b64(char c)
{
	c = tolower(c);
	return c >= 'a' && c <= 'z' || c >= '0' && c <= '9' || c == '+' || c == '/';
}

int
main(int argc, char **argv)
{
	char hex[3], b64[3];
	int i, ch;
	uint8_t byte;

	b64[2] = '\0';
	do {
		memset(hex, '0', 3);

		for (i = 0; i != 3 && is_b64(ch = getchar()); ++i) {
			hex[i] = ch;
		}

		if (i > 0) {
			byte = (htoi(hex[0]) << 4) + htoi(hex[1]);
			putchar(base64[byte >> 2]);
			
			if (i > 1) {
				byte &= 0x3;
				byte = (byte << 4) + htoi(hex[2]);
				ch = base64[byte];

			} else {
				ch = '=';
			}

			putchar(ch);
		}
	} while (i == 3);

	putchar('\n');

	return 0;
}

