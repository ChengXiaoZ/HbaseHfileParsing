
#include "snappy-c.h"
#include <stdio.h>
#include <malloc.h>

int main(int argc, char** argv)
{
	//size_t	output_length;
	//char*	input;
	//size_t	input_length;
	FILE* 	compressed_file;
	FILE*	uncompressed_file;
	char*	com_buffer;
	int		com_buffer_len = 0;
	size_t	com_data_len = 0;
	char*	uncom_buffer = 0;
	size_t	uncom_data_len;
	int 	ret = -1;
	int 	start;
	int 	read_size = 0;

	com_buffer_len = 100*1024*1024;
	com_buffer = malloc(com_buffer_len);

	if(4!=argc)
	{
		printf("arg error\n");
		return 0;
	}
	printf("file = %s\n", argv[1]);
	printf("start pos = %s\n", argv[2]);
	printf("len = %s\n", argv[3]);
	
	start = atoi(argv[2]);
	com_data_len = atoi(argv[3]);

	if((compressed_file = fopen(argv[1], "rb"))==NULL)
	{
		printf("The file can not be opened.\n");
		return 0;
	}

	if(0==com_data_len)
	{
		fseek(compressed_file ,0L,SEEK_END);
		com_data_len=ftell(compressed_file);
		fseek(compressed_file, 0L, SEEK_SET);
	}
	
	fseek(compressed_file, start,SEEK_SET);	
	read_size = fread(com_buffer, sizeof(char), com_data_len, compressed_file);


	/*	
	if (snappy_uncompressed_length(com_buffer, com_data_len, &uncom_data_len) != SNAPPY_OK) 
	{
		printf("not enough memory\n");
		return 0;
	}

	uncom_buffer = (char*)malloc(uncom_data_len);
	
	*/

	char destname[100];
	sprintf(destname, "%s-%s-%d-%d", argv[1], "cut", start, com_data_len);

	uncompressed_file = fopen(destname, "wr");
	fwrite(com_buffer,sizeof(char),com_data_len,uncompressed_file);

	free(uncom_buffer);
	return 0;
}
