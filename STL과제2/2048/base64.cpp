#include "base64.h"

static const char MimeBase64[] = {
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
	'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
	'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
	'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
	'w', 'x', 'y', 'z', '0', '1', '2', '3',
	'4', '5', '6', '7', '8', '9', '+', '/'
};

static int DecodeMimeBase64[256] = {
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,62,-1,-1,-1,63,
	52,53,54,55,56,57,58,59,60,61,-1,-1,-1,-1,-1,-1,
	-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,
	15,16,17,18,19,20,21,22,23,24,25,-1,-1,-1,-1,-1,
	-1,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,
	41,42,43,44,45,46,47,48,49,50,51,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
	-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
};

typedef union {
	struct {
		unsigned char c1, c2, c3;
	};
	struct {
		unsigned int e1 : 6, e2 : 6, e3 : 6, e4 : 6;
	};
} BF;

std::string base64e(char *src, int length) {
	int i, j = 0;
	BF temp;
	std::string tempdata;

	for (i = 0; i < length; i = i + 3, j = j + 4) {
		temp.c3 = src[i];
		if ((i + 1) > length) temp.c2 = 0;
		else temp.c2 = src[i + 1];
		if ((i + 2) > length) temp.c1 = 0;
		else temp.c1 = src[i + 2];

		tempdata += MimeBase64[temp.e4];
		tempdata += MimeBase64[temp.e3];
		tempdata += MimeBase64[temp.e2];
		tempdata += MimeBase64[temp.e1];

		if ((i + 2) > length) tempdata[j + 2] = '=';
		if ((i + 3) > length) tempdata[j + 3] = '=';
	}
	return tempdata;
}

std::string base64d(char *src, int *length) {
	int i, j = 0, src_length, blank = 0;
	BF temp;
	std::string tempdata = "                                                 ";

	src_length = strlen(src);

	for (i = 0; i < src_length; i = i + 4, j = j + 3) {
		temp.e4 = DecodeMimeBase64[src[i]];
		temp.e3 = DecodeMimeBase64[src[i + 1]];
		if (src[i + 2] == '=') {
			temp.e2 = 0;
			blank++;
		}
		else temp.e2 = DecodeMimeBase64[src[i + 2]];
		if (src[i + 3] == '=') {
			temp.e1 = 0;
			blank++;
		}
		else temp.e1 = DecodeMimeBase64[src[i + 3]];

		tempdata[j] = temp.c3;
		tempdata[j + 1] = temp.c2;
		tempdata[j + 2] = temp.c1;
	}
	*length = j - blank;


	return tempdata;
}


/*
��ó : https://kldp.org/node/109436
*/