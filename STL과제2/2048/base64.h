#ifndef _BASE64_H_
#define _BASE64_H_
#include <string>
std::string base64e(char *src, int length);
std::string base64d(char *src, int *length);
#endif 