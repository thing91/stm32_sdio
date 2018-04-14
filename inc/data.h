/*
 * data.h
 *
 *  Created on: Apr 7, 2018
 *      Author: krzysiek
 */

#ifndef DATA_H_
#define DATA_H_
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 512
#define DATA_STRING_SIZE 256

struct data {
	char* date;
	char* hour;
	float data1;
	float data2;
};

struct data2 {
	float data1;
	float data2;
	float data3;
	float data4;
};

enum bufferFlag {
	BUFFER_1,
	BUFFER_2
};

void TurnDataIntoString(char string[], struct data *new_measurements, uint8_t number_of_elements);
void AppendToBuffer(char* pointer_to_current_buffer, uint16_t* data_in_buffer);
void FillBuffer(char date[], char hour[], struct data2 *new_measurements, uint8_t number_of_elements);

#endif /* DATA_H_ */
