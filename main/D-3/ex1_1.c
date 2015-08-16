#include <stdio.h>
#include <stdlib.h>
#include "wave.h"

int main(void)
{
	MONO_PCM pcm0, pcm1;
	int n;

	mono_wave_read(&pcm0, "a.wav"); /* WAVE�t�@�C�����烂�m�����̉��f�[�^���͂��� */

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


	mono_wave_write(&pcm1, "b.wav"); /* WAVE�t�@�C���Ƀ��m�����̉��f�[�^���o�͂��� */

	//debug
	printf("[%s:%d] pcm1.length => %d\n", __FILE__, __LINE__, pcm1.length);

	//debug
	int i;

	printf("[%s:%d] pcm0.s[100] => %d\n", __FILE__, __LINE__, pcm0.s[100]);
	printf("[%s:%d] pcm1.s[100] => %d\n", __FILE__, __LINE__, pcm1.s[100]);


	for (i = 90; i < 100; ++i) {

//		printf("[%s:%d] pcm0.s[%d] = %f\n",
//		printf("[%s:%d] pcm0.s[%d] = %d\n",
		printf("[%s:%d] pcm0.s[%d] = %f / pcm1.s[%d] = %f\n",
//		printf("[%s:%d] pcm0.s[%d] = %d / pcm1.s[%d] = %d\n",
				__FILE__, __LINE__,
//				i, pcm0.s[i]);
//				i, *(pcm0.s[i]),
//				i, *pcm1.s[i]);
				i, pcm0.s[i],
				i, pcm1.s[i]);

	}

	free(pcm0.s); /* �������̉�� */
	free(pcm1.s); /* �������̉�� */

	///////////////////////////////
	//
	// report
	//
	///////////////////////////////
	printf("[%s:%d] all done\n", __FILE__, __LINE__);


	return 0;
}
