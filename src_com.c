
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
	FILE*	fd;
	char*	com_buffer;
	int	com_buffer_len = 0;
	size_t	com_data_len = 0;
	char*	uncom_buffer = 0;
	size_t	uncom_data_len;
	int 	ret = -1;
	int 	start;
	int 	read_size = 0;
	
	if(2!=argc)
	{
		printf("arg error\n");
		return 0;
	}
	printf("file name is %s\n", argv[1]);

	com_buffer_len = 50*1024*1024;
	com_buffer = malloc(com_buffer_len);

	uncom_buffer = malloc(50*1024*1024);


	if((fd = fopen(argv[1], "rb"))==NULL)
	{
		printf("The file can not be opened.\n");
		return 0;
	}

	fseek(fd ,0L,SEEK_END);
	int size=ftell(fd);


	fseek(fd, 0L, SEEK_SET);
	read_size = fread(uncom_buffer, sizeof(char), size, fd);


	uncom_data_len = read_size;
	com_data_len = 50*1024*1024;
	ret = snappy_compress(uncom_buffer, uncom_data_len, com_buffer, &com_data_len);

	//start = 0x18;
	//com_data_len = 0x0D7880;
	
	//start = 0x0d78b0;
	//com_data_len = 0x0E33A1;
	//fseek(compressed_file, start,SEEK_SET);	
	//read_size = fread(com_buffer, sizeof(char), com_data_len, compressed_file);

	ret = snappy_validate_compressed_buffer(com_buffer, com_data_len);
 
	/*	
	if (snappy_uncompressed_length(com_buffer, com_data_len, &uncom_data_len) != SNAPPY_OK) 
	{
		printf("not enough memory\n");
		return 0;
	}

	uncom_buffer = (char*)malloc(uncom_data_len);
	
	*/

	char destname[100];
	sprintf(destname, "%s-%s-%d", argv[1], "compress", size);
	
	compressed_file = fopen(destname, "wr");
	fwrite(com_buffer,sizeof(char),com_data_len,compressed_file);

	free(uncom_buffer);
	return 0;
}
