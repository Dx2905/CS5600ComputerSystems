#ifndef POLYBIUS_H
#define POLYBIUS_H

struct polybius{
	char chartable[7][6];

};

void pbEncode(const char *plaintext, struct polybius table);

void pbDecode(const char *encodedtext, struct polybius table);

#endif
