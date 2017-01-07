#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define BYTES_PER_BLOCK  3
#define BASE64_PER_BLOCK 4

const char *lookup = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void dump_base64_block(const unsigned char *data, size_t len, FILE* stream)
{
	char out_block[BASE64_PER_BLOCK+1];

	memset(out_block, '=', sizeof(out_block));
	out_block[4] = '\0';

	switch(len) {
	case 3:
		out_block[3] = lookup[data[2] & 0x3F];
	case 2:
		out_block[2] = lookup[(data[1] & 0x0F) << 2 | data[2] >> 6];
	case 1:
		out_block[1] = lookup[(data[0] & 0x03) << 4 | (data[1] & 0xF0) >> 4];
		out_block[0] = lookup[data[0] >> 2];
		fputs(out_block, stream);
		break;
	default:
		break;
	}
}

void dump_base64(FILE* in, FILE* out)
{
	size_t nread = 0;
	char buffer[BYTES_PER_BLOCK+1];

	while (!feof(in)) {
		nread = fread(buffer, 1, BYTES_PER_BLOCK, in);
		buffer[nread] = '\0';
		dump_base64_block(buffer, nread, out);
	}
}

int main(void)
{
	dump_base64(stdin, stdout);
	fputc('\n', stdout);
}
