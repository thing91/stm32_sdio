/*
 * ftos.c
 *
 *  Created on: Apr 14, 2018
 *      Author: krzysiek
 */

#include "../inc/ftos.h"


void FloatToString(float float_val, char dest_string[100], uint8_t dec_precision) {
	uint32_t whole, divider, temp;
	float decimal;
	uint8_t  decimal_dig, whole_dig, iter1 = 0, iter2 = 0, whole_precision = 0;
	if (float_val < 0.0) {
		dest_string[iter1++] = '-';
		float_val *= -1;
	}

	whole = float_val;
	decimal = float_val - whole;
	temp = whole;
	while(temp>0){
		whole_precision++;
		temp/=10;
	}

	// number of digits in whole number are k+1

	/*
	 extracting most significant digit i.e. right most digit , and concatenating to string
	 obtained as quotient by dividing number by 10^k where k = (number of digit -1)
	 */

	for (iter2 = whole_precision; iter2 > 0; iter2--) {
		divider = pow(10, iter2 - 1);
		whole_dig = whole / divider;
		dest_string[iter1++] = whole_dig + 48;
		whole %= divider;
	}
	dest_string[iter1++] = '.';

	/* extracting decimal digits till precision */

	for (iter2 = 0; iter2 < dec_precision; iter2++) {
		decimal *= 10.0;
		decimal_dig = decimal;
		dest_string[iter1++] = decimal_dig + 48;
		decimal -= decimal_dig;
	}

	dest_string[iter1] = '\0';

//	printf("\n orignal printf %f\n", float_val);
//	printf("\n float string %s\n", dest_string);

}
