/*
 * http_Utilities.h
 *
 * Created: 23/12/2012 03:09:21 م
 *  Author: Ahmed Emad Morsy
 */ 

#include "stdint.h"
#ifndef HTTP_UTILITIES_H_
#define HTTP_UTILITIES_H_

char* http_extract_host(char* URI);
//char* http_extract_relativeAddress(char* URI);
char* http_extract_relativeAddress(char* URI,int startIndex);
char* http_create_request(char* method,char* relativeAddress,char* htttpVersion,char* host);


#endif /* HTTP_UTILITIES_H_ */