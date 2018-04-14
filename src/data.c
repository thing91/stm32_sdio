/*
 * data.c
 *
 *  Created on: Apr 7, 2018
 *      Author: krzysiek
 */

#include <stdlib.h>
#include "../inc/data.h"
#include "../inc/ftos.h"
#define DECIMAL_PRECISION 4

enum bufferFlag currentBuffer = BUFFER_1;

char data_buffer_1[BUFFER_SIZE];
char data_buffer_2[BUFFER_SIZE];
char* buffer_pointer = data_buffer_1;


static uint16_t data_in_current_buffer;
static char stringifiedData[DATA_STRING_SIZE];
static uint8_t next_data_chunk_size = 0;

void BufferInit(){
	memset((void*)data_buffer_1,0, DATA_STRING_SIZE );
	memset((void*)data_buffer_2,0, DATA_STRING_SIZE );
}

static void WriteDataToString(char string[], char date[], char hour[], struct data2 *new_measurements, uint8_t number_of_elements) {
	char temp[50];
	strcat(string, date);
	strcat(string, ";");
	strcat(string, hour);
	strcat(string, ";");
	float* ptr = (float*) new_measurements;
	uint8_t iter;
	for(iter = 0; iter < number_of_elements; iter++){
		FloatToString(*(ptr+iter), temp, DECIMAL_PRECISION);
		strcat(string, temp);
		strcat(string, ";");
	}
	strcat(string, "\n");
}
void AppendToBuffer(char* pointer_to_current_buffer, uint16_t* data_in_buffer) {
	uint8_t iter;
	for (iter = 0; iter < next_data_chunk_size; iter++) {
		uint16_t position_to_write = *data_in_buffer + iter;
		*(pointer_to_current_buffer + position_to_write) = stringifiedData[iter];
	}
	*data_in_buffer += (uint16_t)next_data_chunk_size;
	memset((void*)stringifiedData,0, DATA_STRING_SIZE );
}

void FillBuffer(char date[], char hour[], struct data2 *new_measurements, uint8_t number_of_elements) {
	WriteDataToString(stringifiedData, date, hour, new_measurements, number_of_elements);
//	printf("data to be added: %s\n", stringifiedData);
	next_data_chunk_size = strlen(stringifiedData);
//	printf("data in curr buff: %d\n", data_in_current_buffer);
	uint16_t space_left_in_buffer = BUFFER_SIZE - data_in_current_buffer;
	if (space_left_in_buffer < (next_data_chunk_size + 1)) {
//		printf("place in buffer is end\n");
		switch (currentBuffer) {
		case BUFFER_1:
			currentBuffer = BUFFER_2;
			buffer_pointer = data_buffer_2;
//			printf("buffer pointer %p\n", buffer_pointer);
//			printf("\ndata_buffer_1:\n%s\n", data_buffer_1);
			memset((void*)data_buffer_1,0, BUFFER_SIZE );
			data_in_current_buffer = 0;
			break;
		case BUFFER_2:
			currentBuffer = BUFFER_1;
			buffer_pointer = data_buffer_1;
//			printf("buffer pointer %p\n", buffer_pointer);
//			printf("\ndata_buffer_2:\n%s\n", data_buffer_2);
			memset((void*)data_buffer_2,0, BUFFER_SIZE );
			data_in_current_buffer = 0;
		}
	} else {
		AppendToBuffer(buffer_pointer, &data_in_current_buffer);
//		printf("current buff: %d\n", currentBuffer);

	}
}

