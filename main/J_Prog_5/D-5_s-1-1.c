#include <stdio.h>
#include <stdlib.h>
#include "wave.h"

#ifndef UTILS_H_
#include "utils.h"
#endif

///////////////////////////////
//
// protos
//
 ///////////////////////////////
void ex_1_1(char[]);


int main(int argc, char *argv[])
//int main(void)
{

	char fname_In[30];

	///////////////////////////////
	//
	// file name
	//
	 ///////////////////////////////
	if (argc > 1) {

		//REF http://www.tutorialspoint.com/c_standard_library/c_function_sprintf.htm
		sprintf(fname_In, "%s", argv[1]);

	} else {

		sprintf(fname_In, "%s", "a.wav");

	}

	printf("[%s:%d] input file => %s\n", __FILE__, __LINE__, fname_In);

	///////////////////////////////
	//
	// ex1_1: copy file
	//
	 ///////////////////////////////
	ex_1_1(fname_In);

	///////////////////////////////
	//
	// report
	//
	///////////////////////////////
	printf("[%s:%d] all done\n", __FILE__, __LINE__);


	return 0;
}

void ex_1_1(char fname_In[]) {

	MONO_PCM pcm0, pcm1;
	int n;

	char fname_out[30];

	mono_wave_read(&pcm0, fname_In); /* WAVE�t�@�C�����烂�m�����̉��f�[�^���͂��� */
//	mono_wave_read(&pcm0, "a.wav"); /* WAVE�t�@�C�����烂�m�����̉��f�[�^���͂��� */

	pcm1.fs = pcm0.fs; /* �W�{����g�� */
	pcm1.bits = pcm0.bits; /* �ʎq�����x */
	pcm1.length = pcm0.length; /* ���f�[�^�̒��� */
	pcm1.s = calloc(pcm1.length, sizeof(double)); /* �������̊m�� */
	for (n = 0; n < pcm1.length; n++)
	{
	  pcm1.s[n] = pcm0.s[n]; /* ���f�[�^�̃R�s�[ */
	}

	//debug
	printf("[%s:%d] pcm0.fs = %d / pcm1.fs = %d\n", __FILE__, __LINE__, pcm0.fs, pcm1.fs);
	printf("[%s:%d] pcm0.bits = %d / pcm1.bits = %d\n", __FILE__, __LINE__, pcm0.bits, pcm1.bits);
	printf("[%s:%d] pcm0.length = %d / pcm1.length = %d\n", __FILE__, __LINE__, pcm0.length, pcm1.length);


	// output file name
	sprintf(fname_out, "b_%s.wav", get_Time_Label__Now());

	//debug
	printf("[%s:%d] fname_out => %s\n", __FILE__, __LINE__, fname_out);


	mono_wave_write(&pcm1, fname_out); /* WAVE�t�@�C���Ƀ��m�����̉��f�[�^���o�͂��� */
//	mono_wave_write(&pcm1, "b.wav"); /* WAVE�t�@�C���Ƀ��m�����̉��f�[�^���o�͂��� */

	//debug
	printf("[%s:%d] pcm1.length => %d\n", __FILE__, __LINE__, pcm1.length);

	//debug
	int i;

	printf("[%s:%d] pcm0.s[100] => %d\n", __FILE__, __LINE__, pcm0.s[100]);
	printf("[%s:%d] pcm1.s[100] => %d\n", __FILE__, __LINE__, pcm1.s[100]);


//	for (i = 90; i < 100; ++i) {
//
////		printf("[%s:%d] pcm0.s[%d] = %f\n",
////		printf("[%s:%d] pcm0.s[%d] = %d\n",
//		printf("[%s:%d] pcm0.s[%d] = %f / pcm1.s[%d] = %f\n",
////		printf("[%s:%d] pcm0.s[%d] = %d / pcm1.s[%d] = %d\n",
//				__FILE__, __LINE__,
////				i, pcm0.s[i]);
////				i, *(pcm0.s[i]),
////				i, *pcm1.s[i]);
//				i, pcm0.s[i],
//				i, pcm1.s[i]);
//
//	}

	free(pcm0.s); /* �������̉�� */
	free(pcm1.s); /* �������̉�� */

}
