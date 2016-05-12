#ifndef STDIO_H_
#define STDIO_H_
#include <stdio.h>
#endif

#ifndef STDLIB_H_
#define STDLIB_H_
#include <stdlib.h>
#endif

typedef struct
{
	int fs; /* �W�{����g�� */
	int bits; /* �ʎq�����x */
	int length; /* ���f�[�^�̒��� */
	double *s; /* ���f�[�^ */
} MONO_PCM;

typedef struct
{
	int fs; /* �W�{����g�� */
	int bits; /* �ʎq�����x */
	int length; /* ���f�[�^�̒��� */
	double *sL; /* ���f�[�^�iL�`�����l���j */
	double *sR; /* ���f�[�^�iR�`�����l���j */
} STEREO_PCM;

void mono_wave_read(MONO_PCM *pcm, char *file_name)
{
	FILE *fp;
	int n;
	char riff_chunk_ID[4];
	long riff_chunk_size;
	char riff_form_type[4];
	char fmt_chunk_ID[4];
	long fmt_chunk_size;
	short fmt_wave_format_type;
	short fmt_channel;
	long fmt_samples_per_sec;
	long fmt_bytes_per_sec;
	short fmt_block_size;
	short fmt_bits_per_sample;
	char data_chunk_ID[4];
	long data_chunk_size;
	short data;

	fp = fopen(file_name, "rb");

//	/****************************
//	 * validate
//	 *****************************/
//	if (fp == NULL) {
//
//		printf("[%s:%d] fp => null\n", __FILE__, __LINE__);
//
//		return;
//
//	}

	fread(riff_chunk_ID, 1, 4, fp);
	fread(&riff_chunk_size, 4, 1, fp);
	fread(riff_form_type, 1, 4, fp);
	fread(fmt_chunk_ID, 1, 4, fp);
	fread(&fmt_chunk_size, 4, 1, fp);
	fread(&fmt_wave_format_type, 2, 1, fp);
	fread(&fmt_channel, 2, 1, fp);
	fread(&fmt_samples_per_sec, 4, 1, fp);
	fread(&fmt_bytes_per_sec, 4, 1, fp);
	fread(&fmt_block_size, 2, 1, fp);
	fread(&fmt_bits_per_sample, 2, 1, fp);
	fread(data_chunk_ID, 1, 4, fp);
	fread(&data_chunk_size, 4, 1, fp);

	pcm->fs = fmt_samples_per_sec; /* �W�{����g�� */
	pcm->bits = fmt_bits_per_sample; /* �ʎq�����x */
	pcm->length = data_chunk_size / 2; /* ���f�[�^�̒��� */
	pcm->s = calloc(pcm->length, sizeof(double)); /* �������̊m�� */

	for (n = 0; n < pcm->length; n++)
	{
	  fread(&data, 2, 1, fp); /* ���f�[�^�̓ǂݎ�� */
	  pcm->s[n] = (double)data / 32768.0; /* ���f�[�^��-1�ȏ�1�����͈̔͂ɐ��K������ */
	}

	fclose(fp);
}

void mono_wave_write(MONO_PCM *pcm, char *file_name)
{
	FILE *fp;
	int n;
	char riff_chunk_ID[4];
	long riff_chunk_size;
	char riff_form_type[4];
	char fmt_chunk_ID[4];
	long fmt_chunk_size;
	short fmt_wave_format_type;
	short fmt_channel;
	long fmt_samples_per_sec;
	long fmt_bytes_per_sec;
	short fmt_block_size;
	short fmt_bits_per_sample;
	char data_chunk_ID[4];
	long data_chunk_size;
	short data;
	double s;

	riff_chunk_ID[0] = 'R';
	riff_chunk_ID[1] = 'I';
	riff_chunk_ID[2] = 'F';
	riff_chunk_ID[3] = 'F';
	riff_chunk_size = 36 + pcm->length * 2;
	riff_form_type[0] = 'W';
	riff_form_type[1] = 'A';
	riff_form_type[2] = 'V';
	riff_form_type[3] = 'E';

	fmt_chunk_ID[0] = 'f';
	fmt_chunk_ID[1] = 'm';
	fmt_chunk_ID[2] = 't';
	fmt_chunk_ID[3] = ' ';
	fmt_chunk_size = 16;
	fmt_wave_format_type = 1;
	fmt_channel = 1;
	fmt_samples_per_sec = pcm->fs; /* �W�{����g�� */
	fmt_bytes_per_sec = pcm->fs * pcm->bits / 8;
	fmt_block_size = pcm->bits / 8;
	fmt_bits_per_sample = pcm->bits; /* �ʎq�����x */

	data_chunk_ID[0] = 'd';
	data_chunk_ID[1] = 'a';
	data_chunk_ID[2] = 't';
	data_chunk_ID[3] = 'a';
	data_chunk_size = pcm->length * 2;

	fp = fopen(file_name, "wb");

	fwrite(riff_chunk_ID, 1, 4, fp);
	fwrite(&riff_chunk_size, 4, 1, fp);
	fwrite(riff_form_type, 1, 4, fp);
	fwrite(fmt_chunk_ID, 1, 4, fp);
	fwrite(&fmt_chunk_size, 4, 1, fp);
	fwrite(&fmt_wave_format_type, 2, 1, fp);
	fwrite(&fmt_channel, 2, 1, fp);
	fwrite(&fmt_samples_per_sec, 4, 1, fp);
	fwrite(&fmt_bytes_per_sec, 4, 1, fp);
	fwrite(&fmt_block_size, 2, 1, fp);
	fwrite(&fmt_bits_per_sample, 2, 1, fp);
	fwrite(data_chunk_ID, 1, 4, fp);
	fwrite(&data_chunk_size, 4, 1, fp);

	for (n = 0; n < pcm->length; n++)
	{
	  s = (pcm->s[n] + 1.0) / 2.0 * 65536.0;

	  if (s > 65535.0)
	  {
	    s = 65535.0; /* �N���b�s���O */
	  }
	  else if (s < 0.0)
	  {
	    s = 0.0; /* �N���b�s���O */
	  }

	  data = (short)(s + 0.5) - 32768; /* �l�̌ܓ�ƃI�t�Z�b�g�̒��� */
	  fwrite(&data, 2, 1, fp); /* ���f�[�^�̏����o�� */
	}

	fclose(fp);
}

void stereo_wave_read(STEREO_PCM *pcm, char *file_name)
{
	FILE *fp;
	int n;
	char riff_chunk_ID[4];
	long riff_chunk_size;
	char riff_form_type[4];
	char fmt_chunk_ID[4];
	long fmt_chunk_size;
	short fmt_wave_format_type;
	short fmt_channel;
	long fmt_samples_per_sec;
	long fmt_bytes_per_sec;
	short fmt_block_size;
	short fmt_bits_per_sample;
	char data_chunk_ID[4];
	long data_chunk_size;
	short data;

<<<<<<< HEAD
	char tmp[10];	// display data_chunk_ID
//	char tmp[5];	// display data_chunk_ID

	fp = fopen(file_name, "rb");

	printf("[%s:%d] stereo_wave_read: file opened => %s\n", __FILE__, __LINE__, file_name);


=======
	fp = fopen(file_name, "rb");

>>>>>>> D-3_first
	fread(riff_chunk_ID, 1, 4, fp);
	fread(&riff_chunk_size, 4, 1, fp);
	fread(riff_form_type, 1, 4, fp);
	fread(fmt_chunk_ID, 1, 4, fp);
	fread(&fmt_chunk_size, 4, 1, fp);
	fread(&fmt_wave_format_type, 2, 1, fp);
	fread(&fmt_channel, 2, 1, fp);
	fread(&fmt_samples_per_sec, 4, 1, fp);
	fread(&fmt_bytes_per_sec, 4, 1, fp);
	fread(&fmt_block_size, 2, 1, fp);
	fread(&fmt_bits_per_sample, 2, 1, fp);
	fread(data_chunk_ID, 1, 4, fp);
	fread(&data_chunk_size, 4, 1, fp);

<<<<<<< HEAD
	//debug: riff_chunk_ID
	printf("[%s:%d] riff_chunk_ID[0] => %c (%d)\n", __FILE__, __LINE__, riff_chunk_ID[0], riff_chunk_ID[0]);
	printf("[%s:%d] riff_chunk_ID[1] => %c (%d)\n", __FILE__, __LINE__, riff_chunk_ID[1], riff_chunk_ID[1]);
	printf("[%s:%d] riff_chunk_ID[2] => %c (%d)\n", __FILE__, __LINE__, riff_chunk_ID[2], riff_chunk_ID[2]);
	printf("[%s:%d] riff_chunk_ID[3] => %c (%d)\n", __FILE__, __LINE__, riff_chunk_ID[3], riff_chunk_ID[3]);
//	printf("[%s:%d] riff_chunk_ID[4] => %c (%d)\n", __FILE__, __LINE__, riff_chunk_ID[4], riff_chunk_ID[4]);

	printf("[%s:%d] riff_chunk_size => %l\n", __FILE__, __LINE__, riff_chunk_size);
//	printf("[%s:%d] riff_chunk_size => %d\n", __FILE__, __LINE__, riff_chunk_size);
//	printf("[%s:%d] riff_chunk_size => %d\n", __FILE__, __LINE__, riff_chunk_size);


	printf("[%s:%d] riff_form_type[0] => %c (%d)\n", __FILE__, __LINE__, riff_form_type[0], riff_form_type[0]);
	printf("[%s:%d] riff_form_type[1] => %c (%d)\n", __FILE__, __LINE__, riff_form_type[1], riff_form_type[1]);
	printf("[%s:%d] riff_form_type[2] => %c (%d)\n", __FILE__, __LINE__, riff_form_type[2], riff_form_type[2]);
	printf("[%s:%d] riff_form_type[3] => %c (%d)\n", __FILE__, __LINE__, riff_form_type[3], riff_form_type[3]);

	printf("[%s:%d] fmt_chunk_ID[0] => %c (%d)\n", __FILE__, __LINE__, fmt_chunk_ID[0], fmt_chunk_ID[0]);
	printf("[%s:%d] fmt_chunk_ID[1] => %c (%d)\n", __FILE__, __LINE__, fmt_chunk_ID[1], fmt_chunk_ID[1]);
	printf("[%s:%d] fmt_chunk_ID[2] => %c (%d)\n", __FILE__, __LINE__, fmt_chunk_ID[2], fmt_chunk_ID[2]);
	printf("[%s:%d] fmt_chunk_ID[3] => %c (%d)\n", __FILE__, __LINE__, fmt_chunk_ID[3], fmt_chunk_ID[3]);

//	sprintf(tmp, "%s", riff_chunk_ID);
//	sprintf(tmp, "%s\n", data_chunk_ID);

//	tmp[4] = '\0';
//	tmp[4] = '\n';

//	printf("[%s:%d] riff_chunk_ID => %s\n", __FILE__, __LINE__, tmp);

//	//debug: data_chunk_ID
//	sprintf(tmp, "%s", data_chunk_ID);
////	sprintf(tmp, "%s\n", data_chunk_ID);
//
//	tmp[4] = '\n';
//
//	printf("[%s:%d] data_chunk_ID => %s\n", __FILE__, __LINE__, tmp);


	printf("[%s:%d] fread => done\n", __FILE__, __LINE__);


	pcm->fs = fmt_samples_per_sec; /* �W�{����g�� */

	printf("[%s:%d] pcm->fs => set\n", __FILE__, __LINE__);


	pcm->bits = fmt_bits_per_sample; /* �ʎq�����x */

	printf("[%s:%d] pcm->bits => set\n", __FILE__, __LINE__);

	pcm->length = data_chunk_size / 4; /* ���f�[�^�̒��� */

	printf("[%s:%d] pcm->length => set: %d\n", __FILE__, __LINE__, pcm->length);

	pcm->sL = calloc(pcm->length, sizeof(double)); /* �������̊m�� */

	printf("[%s:%d] pcm->sL => calloc --> done\n", __FILE__, __LINE__);

	pcm->sR = calloc(pcm->length, sizeof(double)); /* �������̊m�� */

	printf("[%s:%d] pcm->sR => calloc --> done\n", __FILE__, __LINE__);

=======
	pcm->fs = fmt_samples_per_sec; /* �W�{����g�� */
	pcm->bits = fmt_bits_per_sample; /* �ʎq�����x */
	pcm->length = data_chunk_size / 4; /* ���f�[�^�̒��� */
	pcm->sL = calloc(pcm->length, sizeof(double)); /* �������̊m�� */
	pcm->sR = calloc(pcm->length, sizeof(double)); /* �������̊m�� */

>>>>>>> D-3_first
	for (n = 0; n < pcm->length; n++)
	{
	  fread(&data, 2, 1, fp); /* ���f�[�^�iL�`�����l���j�̓ǂݎ�� */
	  pcm->sL[n] = (double)data / 32768.0; /* ���f�[�^��-1�ȏ�1�����͈̔͂ɐ��K������ */

<<<<<<< HEAD


=======
>>>>>>> D-3_first
	  fread(&data, 2, 1, fp); /* ���f�[�^�iR�`�����l���j�̓ǂݎ�� */
	  pcm->sR[n] = (double)data / 32768.0; /* ���f�[�^��-1�ȏ�1�����͈̔͂ɐ��K������ */
	}

	fclose(fp);
}

void stereo_wave_write(STEREO_PCM *pcm, char *file_name)
{
	FILE *fp;
	int n;
	char riff_chunk_ID[4];
	long riff_chunk_size;
	char riff_form_type[4];
	char fmt_chunk_ID[4];
	long fmt_chunk_size;
	short fmt_wave_format_type;
	short fmt_channel;
	long fmt_samples_per_sec;
	long fmt_bytes_per_sec;
	short fmt_block_size;
	short fmt_bits_per_sample;
	char data_chunk_ID[4];
	long data_chunk_size;
	short data;
	double s;

	riff_chunk_ID[0] = 'R';
	riff_chunk_ID[1] = 'I';
	riff_chunk_ID[2] = 'F';
	riff_chunk_ID[3] = 'F';
	riff_chunk_size = 36 + pcm->length * 4;
	riff_form_type[0] = 'W';
	riff_form_type[1] = 'A';
	riff_form_type[2] = 'V';
	riff_form_type[3] = 'E';

	fmt_chunk_ID[0] = 'f';
	fmt_chunk_ID[1] = 'm';
	fmt_chunk_ID[2] = 't';
	fmt_chunk_ID[3] = ' ';
	fmt_chunk_size = 16;
	fmt_wave_format_type = 1;
	fmt_channel = 2;
	fmt_samples_per_sec = pcm->fs; /* �W�{����g�� */
	fmt_bytes_per_sec = pcm->fs * pcm->bits / 8 * 2;
	fmt_block_size = pcm->bits / 8 * 2;
	fmt_bits_per_sample = pcm->bits; /* �ʎq�����x */

	data_chunk_ID[0] = 'd';
	data_chunk_ID[1] = 'a';
	data_chunk_ID[2] = 't';
	data_chunk_ID[3] = 'a';
	data_chunk_size = pcm->length * 4;

	fp = fopen(file_name, "wb");

	fwrite(riff_chunk_ID, 1, 4, fp);
	fwrite(&riff_chunk_size, 4, 1, fp);
	fwrite(riff_form_type, 1, 4, fp);
	fwrite(fmt_chunk_ID, 1, 4, fp);
	fwrite(&fmt_chunk_size, 4, 1, fp);
	fwrite(&fmt_wave_format_type, 2, 1, fp);
	fwrite(&fmt_channel, 2, 1, fp);
	fwrite(&fmt_samples_per_sec, 4, 1, fp);
	fwrite(&fmt_bytes_per_sec, 4, 1, fp);
	fwrite(&fmt_block_size, 2, 1, fp);
	fwrite(&fmt_bits_per_sample, 2, 1, fp);
	fwrite(data_chunk_ID, 1, 4, fp);
	fwrite(&data_chunk_size, 4, 1, fp);

	for (n = 0; n < pcm->length; n++)
	{
	  s = (pcm->sL[n] + 1.0) / 2.0 * 65536.0;

	  if (s > 65535.0)
	  {
	    s = 65535.0; /* �N���b�s���O */
	  }
	  else if (s < 0.0)
	  {
	    s = 0.0; /* �N���b�s���O */
	  }

	  data = (short)(s + 0.5) - 32768; /* �l�̌ܓ�ƃI�t�Z�b�g�̒��� */
	  fwrite(&data, 2, 1, fp); /* ���f�[�^�iL�`�����l���j�̏����o�� */

	  s = (pcm->sR[n] + 1.0) / 2.0 * 65536.0;

	  if (s > 65535.0)
	  {
	    s = 65535.0; /* �N���b�s���O */
	  }
	  else if (s < 0.0)
	  {
	    s = 0.0; /* �N���b�s���O */
	  }

	  data = (short)(s + 0.5) - 32768; /* �l�̌ܓ�ƃI�t�Z�b�g�̒��� */
	  fwrite(&data, 2, 1, fp); /* ���f�[�^�iR�`�����l���j�̏����o�� */
	}

	fclose(fp);
}
