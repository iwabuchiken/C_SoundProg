/*
 *	file: C:\WORKS_2\WS\Eclipse_Luna\C_SoundProg\main\D-6\main.c
 *
 *  Created on: 2017/03/03 19:59:13
 *
 *	<usage>
pushd C:\WORKS_2\WS\Eclipse_Luna\C_SoundProg\main\D-6\
gcc main.c


 *
 */

//#ifndef UTILS_H_
//#define UTILS_H_
#include "../../utils/utils.h"

#include "../../utils/wave.h"



///////////////////////

// protos

///////////////////////
//void get_random_integer(int);

int main() {

//	FILE	*fp;

	int max = 10;

	int random = get_random_integer(max);

	printf("[%s:%d] random => %d\n", __FILE__, __LINE__, random);

	printf("[%s:%d] RAND_MAX => %d\n", __FILE__, __LINE__, RAND_MAX);

	printf("[%s:%d] INT_MAX => %d\n", __FILE__, __LINE__, INT_MAX);


	printf("done!!!");

	return 0;

}
