/* C library */
#include <stdio.h>
#include <string.h>
/* POSIX */
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int
main(int argc, char **argv)
{
	char *key;
	unsigned char byte;
	int key_i, key_len, i;

	if (argc < 2) {
		fprintf(stderr, "usage: %s key", argv[0]);
		return 0;
	}

	key = argv[1];
	key_i = 0;
	key_len = strlen(key);

	while (read(STDIN_FILENO, &byte, 1)) {
		byte ^= key[key_i++];
		write(STDOUT_FILENO, &byte, 1);
		if (key_i >= key_len) {
			key_i -= key_len;
		}
	}

	return 0;
}

