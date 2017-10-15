/* C library */
#include <stdio.h>
#include <ctype.h>

int
htoi(char c)
{
	c = tolower(c);
	return c >= '0' && c <= '9' ? c - '0' : c - 'a' + 10;
}

char
itoh(int n)
{
	return n < 10 ? '0' + n : 'a' + n - 10;
}

char *
encode_fxor(char *str, const char *key)
{
	while (*str) {
		*str = itoh(htoi(*str) ^ htoi(*key++));
		++key;
	}
}

int
main(int argc, char **argv)
{
	char str[] = { "1c0111001f010100061a024b53535009181c" },
		key[] = { "686974207468652062756c6c277320657965" };

	encode_fxor(str, key);
	printf("%s\n", str);

	return 0;
}

