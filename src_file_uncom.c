#include "snappy-c.h"
#include <stdio.h>
#include <malloc.h>
#include <assert.h>

#define MAGIC "BLOCKBLK"

/*
 * input : file whick contain hfile datablock.
 * output : uncompressed file, name formate input file name plus uncompress  
 */
int main(int argc, char** argv)
{
	FILE* 	cfile;
	int	cfile_size;
	char* 	cfile_name;
	char*	file_buffer;
	int 	read_size;

	if(2!=argc)
	{
		printf("arg number is error\n");
		return -1;
	}
	cfile_name = argv[1];
	printf("input compressed file is = %s\n", cfile_name);

	//1.read full file into memory
	if((cfile = fopen(cfile_name, "rb"))==NULL)
	{
		printf("input commpressed file can not be opened.\n");
		return -1;
	}

	fseek(cfile ,0L,SEEK_END);
	cfile_size=ftell(cfile);
	fseek(cfile, 0L, SEEK_SET);

	file_buffer = malloc(cfile_size);	
	read_size = fread(file_buffer, sizeof(char), cfile_size, cfile);
	
	assert(read_size==cfile_size);
	
	//2.search magic
	
	//3.parse
	
	free(file_buffer);
	return 0;
}
