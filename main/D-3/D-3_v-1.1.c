#ifndef STDIO_H_
#define STDIO_H_
#include <stdio.h>
#endif

#ifndef STDLIB_H_
#define STDLIB_H_
#include <stdlib.h>
#endif

#include "wave.h"

#include "../../utils/utils.h"

int main(int argc, char *argv[])
//int main(void)
{

	char fname_In[30];
	char fname_Out[30];

	///////////////////////////////
	//
	// file name
	//
	 ///////////////////////////////
//	printf("[%s:%d] argc = %d\n", __FILE__, __LINE__, argc);
//	printf("[%s:%d] argv[0] = %s\n", __FILE__, __LINE__, argv[0]);

	if (argc > 1) {

		sprintf(fname_In, "%s.wav", argv[1]);
//		sprintf(fname_Out, "%s.out.%s.wav", argv[1], get_Time_Label());
//		sprintf(fname_In, "%s", argv[1]);

	} else {

		sprintf(fname_In, "%s", "c.wav");

	}

	printf("[%s:%d] input file => %s\n", __FILE__, __LINE__, fname_In);


	STEREO_PCM pcm0, pcm1;
	int n;

	stereo_wave_read(&pcm0, fname_In); /* WAVE�t�@�C������X�e���I�̉��f�[�^���͂��� */
//	stereo_wave_read(&pcm0, "c.wav"); /* WAVE�t�@�C������X�e���I�̉��f�[�^���͂��� */

	printf("[%s:%d] pcm0.length => %d\n", __FILE__, __LINE__, pcm0.length);


	  pcm1.fs = pcm0.fs; /* �W�{����g�� */
	  pcm1.bits = pcm0.bits; /* �ʎq�����x */
	  pcm1.length = pcm0.length; /* ���f�[�^�̒��� */
	  pcm1.sL = calloc(pcm1.length, sizeof(double)); /* �������̊m�� */
	  pcm1.sR = calloc(pcm1.length, sizeof(double)); /* �������̊m�� */
	  for (n = 0; n < pcm1.length; n++)
	  {
	    pcm1.sL[n] = pcm0.sL[n]; /* ���f�[�^�̃R�s�[ */
	    pcm1.sR[n] = pcm0.sR[n]; /* ���f�[�^�̃R�s�[ */
	  }

	  printf("[%s:%d] pcm1.length => %d\n", __FILE__, __LINE__, pcm1.length);


	  stereo_wave_write(&pcm1, "d.wav"); /* WAVE�t�@�C���ɃX�e���I�̉��f�[�^���o�͂��� */

	  free(pcm0.sL); /* �������̉�� */
	  free(pcm0.sR); /* �������̉�� */
	  free(pcm1.sL); /* �������̉�� */
	  free(pcm1.sR); /* �������̉�� */

	///////////////////////////////
	//
	// report
	//
	///////////////////////////////
	printf("[%s:%d] all done\n", __FILE__, __LINE__);


	return 0;
}
