/* C library */
#include <stdio.h>
/* POSIX */
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int
b64toi(int ch)
{
	if (ch >= 'A' && ch <= 'Z') {
		return ch - 'A';

	} else if (ch >= 'a' && ch <= 'z') {
		return ch - 'a' + 26;

	} else if (ch >= '0' && ch <= '9') {
		return ch - '0' + 52;

	} else if (ch == '+') {
		return 62;

	} else if (ch == '/') {
		return 63;

	} else if (ch == '=') {
		return -1;
	}

	return -2;
}

int
main(int argc, char **argv)
{
	int byte, oct_bits, ch;

	byte = oct_bits = 0;
	while ((ch = getchar()) != EOF) {
		if ((ch = b64toi(ch)) >= 0) {
			if (oct_bits >= 8) {
				oct_bits -= 8;
			}
			
			if (oct_bits > 0) {
				byte = (byte << oct_bits) | (ch >> (6 - oct_bits));
				write(STDOUT_FILENO, &byte, 1);
			}
			
			byte = ch;
			oct_bits += 2;

		} else if (ch == -1) {
			break;
		}
	}

	return 0;
}
  
