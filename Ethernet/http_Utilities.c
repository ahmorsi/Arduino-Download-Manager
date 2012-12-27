/*
 * http_Utilities.c
 *
 * Created: 23/12/2012 03:10:04 م
 *  Author: Ahmed Emad Morsy
 */ 
#include "http_Utilities.h"
char* http_extract_host(char* URI)
{
	char* host=malloc(strlen(URI)*sizeof(char));
	int i=0;
	while(URI[i]!='/')
	{
		host[i]=URI[i];
		++i;
	}
	host[i]='\0';
	
	return host;
}
char* http_extract_relativeAddress(char* URI,int startIndex)
{
	int relativeAddressLength = strlen(URI)-startIndex;
	char* relativeAddress = malloc(relativeAddressLength + 1);
	int index,i=0;
	for(index=startIndex;index<relativeAddressLength;++index,++i)
		relativeAddress[i]=URI[index];
	relativeAddress[relativeAddressLength]='\0';
	
	return relativeAddress;	
}
char* http_create_request(char* method,char* relativeAddress,char* htttpVersion,char* host)
{
	/*	Request-Line   = Method SP Request-URI SP HTTP-Version CRLF
		Header Format => "attribute" + ':' + SP + "Value" + CRLF
		.
		.
		Blank-line
		Content if needed 
	*/
	int size_method=strlen(method),size_relativeAddress = strlen(relativeAddress),size_httpV = strlen(htttpVersion),size_host=strlen(host);
	char* request = malloc(size_method + size_relativeAddress + size_httpV + size_host + 6);
	
	int cur_index=0,i=0;
	/* Copying the Method in the Request */
	for(;i<size_method;++i)
		request[cur_index++]=method[i];
	
	request[cur_index++]=' ';	//SP
	i=0;
	/* Copying in the Relative Address in the Request */
	for(;i<size_relativeAddress;++i)
		request[cur_index++]=relativeAddress[i];	
	
	request[cur_index++]=' '; //SP
	i=0;
	
	/* Copying in the HTTP Version in the Request */
	for(;i<size_httpV;++i)
		request[cur_index++]=htttpVersion[i];
	
	request[cur_index++]='\r';request[cur_index++]='\n';	//CRLF
	
	//Here Add all the desired headers
	// Host: Absolute URI;
	
	request[cur_index++]='H';request[cur_index++]='o';request[cur_index++]='s';request[cur_index++]='t';request[cur_index++]=':';
	request[cur_index++]=' ';	//SP
	
	i=0;
	/* Copying in the Absolute URI in the Request(attribute=>Host) */
	for(;i<size_host;++i)
		request[cur_index++]=host[i];
		
	request[cur_index++]='\r';request[cur_index++]='\n';	//CRLF
	request[cur_index++]='\n';//Blank-line
	
	request[cur_index]='\0';
	
}