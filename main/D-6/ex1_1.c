#include <stdio.h>
#include <stdlib.h>
//#include <cstdio>

#ifndef MATH_H_
#define MATH_H_
#include <math.h>
#endif

//#include "wave.h"
#include "../../utils/utils.h"

#include "../../utils/wave.h"

/********************************************************
 *
 * protos
 *
*********************************************************/
int write_PCMData_to_File(void);
//int write_PCMData_to_File(MONO_PCM pcm);
void absolutize_Sound_Data();
void sine_Squared();
void sine_Squared__V2();
void sine_P4();
void volume_Down_By_Percent(int nominator);
int volume_Down_PCMData_By_Percent(MONO_PCM* pcm0, int nominator);
void absolutize_MONO_PCM(MONO_PCM* pcm);
int absolutize_MONO_PCM__2PCMs(MONO_PCM* pcm1, MONO_PCM* pcm2);

void show_Basic_PCM_Data(MONO_PCM* pcm0);

/********************************************************
 *
 * functions
 *
*********************************************************/
int write_PCMData_to_File() {

	printf("[%s:%d] writing...\n", basename(__FILE__, '\\'), __LINE__);

	MONO_PCM pcm0, pcm1;
	int n;

	//  mono_wave_read(&pcm0, "a.wav"); /* WAVEファイルからモノラルの音データを入力する */
	mono_wave_read(&pcm0, "C:\\WORKS_2\\WS\\Eclipse_Luna\\C_SoundProg\\main\\D-6\\a.wav");	//=> working

	pcm1.fs = pcm0.fs; /* 標本化周波数 */
	pcm1.bits = pcm0.bits; /* 量子化精度 */
	pcm1.length = pcm0.length; /* 音データの長さ */
	pcm1.s = calloc(pcm1.length, sizeof(double)); /* メモリの確保 */
	for (n = 0; n < pcm1.length; n++)
	{
	  pcm1.s[n] = pcm0.s[n]; /* 音データのコピー */
	}

	char fname_dst[100];

	//  char* fname_trunk = "b";
	char* fname_trunk = "main\\D-6\\b";	//=> file WAS generated (in this directory)
	//  char* fname_trunk = "\\main\\D-6\\b";	//=> file not generated (in this directory)
	//  char* fname_trunk = "..\\main\\D-6\\b";	//=> file not generated (in this directory)

	char* fname_ext = "wav";

	 get_file_name_with_time_label(fname_dst, fname_trunk, fname_ext);

	 printf("[%s:%d] fname_dst => '%s'\n", basename(__FILE__, '\\'), __LINE__, fname_dst);

	 /**********************

		get: dirname

		**********************/
	 char* dpath = dirname(__FILE__, '\\');

	 printf("[%s:%d] dpath => '%s'\n", basename(__FILE__, '\\'), __LINE__, dpath);



//	mono_wave_write(&pcm1, fname_dst); /* WAVEファイルにモノラルの音データを出力する */
	//  mono_wave_write(&pcm1, "b.wav"); /* WAVEファイルにモノラルの音データを出力する */
	//=> with "b.wav" ---> the file gets created at "C:\WORKS_2\WS\Eclipse_Luna\C_SoundProg"

	/**********************

		TINK-1

	**********************/
	printf("[%s:%d] pcm0.fs => %d\n", basename(__FILE__, '\\'), __LINE__, pcm0.fs);

	char fname_dst_2[100];

//	get_file_name_with_time_label(fname_dst_2, "pcm_data", "dat");	//=> file will be created at C:\WORKS_2\WS\Eclipse_Luna\C_SoundProg
	get_file_name_with_time_label(fname_dst_2, "main\\D-6\\data\\pcm_data", "dat");
//	get_file_name_with_time_label(fname_dst_2, "pcm_data", "dat");

	printf("[%s:%d] fname_dst => '%s'\n", basename(__FILE__, '\\'), __LINE__, fname_dst_2);

	FILE* f = fopen(fname_dst_2, "w");

	fprintf(f, "# pcm data will be written here\n");

	printf("[%s:%d] length => %d\n", basename(__FILE__, '\\'), __LINE__, pcm0.length);

	/**********************

		write : sound data

	**********************/
	int i;

	for (i = 0; i < pcm0.length; ++i) {

		fprintf(f, "%f\n", pcm0.s[i]);

	}//for (i = 0; i < pcm0.length; ++i)


	fclose(f);

	printf("[%s:%d] file => closed\n", basename(__FILE__, '\\'), __LINE__);




	/********************************************************
	 *
	 * free
	 *
	*********************************************************/
	free(pcm0.s); /* メモリの解放 */
	free(pcm1.s); /* メモリの解放 */


	return 0;

}//int write_PCMData_to_File(MONO_PCM pcm)

void test_ex1_x() {

	  MONO_PCM pcm0, pcm1;
	  int n;

	//  mono_wave_read(&pcm0, "a.wav"); /* WAVEファイルからモノラルの音データを入力する */
	  mono_wave_read(&pcm0, "C:\\WORKS_2\\WS\\Eclipse_Luna\\C_SoundProg\\main\\D-6\\a.wav");	//=> working

	  pcm1.fs = pcm0.fs; /* 標本化周波数 */
	  pcm1.bits = pcm0.bits; /* 量子化精度 */
	  pcm1.length = pcm0.length; /* 音データの長さ */
	  pcm1.s = calloc(pcm1.length, sizeof(double)); /* メモリの確保 */
	  for (n = 0; n < pcm1.length; n++)
	  {
	    pcm1.s[n] = pcm0.s[n]; /* 音データのコピー */
	  }

	  char fname_dst[100];

	//  char* fname_trunk = "b";
	  char* fname_trunk = "main\\D-6\\b";	//=> file WAS generated (in this directory)
	//  char* fname_trunk = "\\main\\D-6\\b";	//=> file not generated (in this directory)
	//  char* fname_trunk = "..\\main\\D-6\\b";	//=> file not generated (in this directory)

	  char* fname_ext = "wav";

	   get_file_name_with_time_label(fname_dst, fname_trunk, fname_ext);

	   printf("[%s:%d] fname_dst => '%s'\n", basename(__FILE__, '\\'), __LINE__, fname_dst);

	   /**********************

		get: dirname

		**********************/
	   char* dpath = dirname(__FILE__, '\\');

	   printf("[%s:%d] dpath => '%s'\n", basename(__FILE__, '\\'), __LINE__, dpath);



	  mono_wave_write(&pcm1, fname_dst); /* WAVEファイルにモノラルの音データを出力する */
	//  mono_wave_write(&pcm1, "b.wav"); /* WAVEファイルにモノラルの音データを出力する */
	  //=> with "b.wav" ---> the file gets created at "C:\WORKS_2\WS\Eclipse_Luna\C_SoundProg"

	  free(pcm0.s); /* メモリの解放 */
	  free(pcm1.s); /* メモリの解放 */

}//test_ex1_x()

/**********************

	@return
		-1		=> Nominator larger than 1000
		1		=> Done

	@param
		nominator	=> 0 ~ 1000 (0.0% ~ 100.0%)

**********************/
int volume_Down_PCMData_By_Percent(MONO_PCM* pcm0, int nominator) {

	/**********************

		validate

	**********************/
	if (nominator > 1000) {

		printf("[%s:%d] nominator > 1000 ---> needs to be <= 1000\n",
				basename(__FILE__, '\\'), __LINE__);

		return -1;

	}//if (nominator > 100)

	/**********************

		Operatons

	**********************/
	int len = pcm0->length;

	int n;

	for (n = 0; n < len; n++)
	{

		//ref fabs https://stackoverflow.com/questions/20956352/how-to-get-absolute-value-from-double-c-language "answered Jan 6 '14 at 18:08"
		pcm0->s[n] = pcm0->s[n] * (nominator / 1000.0);

	}

	return 1;

}//int volume_Down_PCMData_By_Percent(MONO_PCM* pcm0, int nominator)

/**********************

	<process>
		1. Destructive

**********************/
void absolutize_MONO_PCM(MONO_PCM* pcm) {

	int len = pcm->length;

	int n;

	for (n = 0; n < len; n++)
	{

		//ref fabs https://stackoverflow.com/questions/20956352/how-to-get-absolute-value-from-double-c-language "answered Jan 6 '14 at 18:08"
		pcm->s[n] = fabs(pcm->s[n]);

	}

	return;

}//MONO_PCM* absolutize_MONO_PCM(MONO_PCM* pcm)

/**********************

	@return
		1. 1	=> Done
		2. -1	=> Lengths don't match to each other

	@param
	pcm1		=> Source
	pcm2		=> Dest

**********************/
int absolutize_MONO_PCM__2PCMs(MONO_PCM* pcm1, MONO_PCM* pcm2) {

	/**********************

		validate

	**********************/
	if (pcm1->length != pcm2->length) {

		printf("[%s:%d] lengths don't match ==> %d and %d\n",
				basename(__FILE__, '\\'), __LINE__,
				pcm1->length, pcm2->length);

		return -1;

	}//if (pcm1.length != pcm2.length)

	/**********************

		operations

	**********************/
	int len = pcm1->length;

	int n;

	for (n = 0; n < len; n++)
	{

		//ref fabs https://stackoverflow.com/questions/20956352/how-to-get-absolute-value-from-double-c-language "answered Jan 6 '14 at 18:08"
		pcm2->s[n] = pcm1->s[n];

	}

	return 1;

}//MONO_PCM* absolutize_MONO_PCM(MONO_PCM* pcm)

/********************************************************
 *
 * void volume_Down_By_Percent(int nominator)
 *
 *	@ job
 *		1. (original volume) * (nominator / 100) ---> scale down
 *
*********************************************************/
void volume_Down_By_Percent(int nominator) {

	/**********************

		validate

	**********************/
	int nominator_max = 1000;

	if (nominator > nominator_max) {
//	if (nominator > 100) {

		printf("[%s:%d] nominator > %d (is %d) ---> needs to be <= %d\n",
				basename(__FILE__, '\\'), __LINE__, nominator_max, nominator, nominator_max);

		return;

	}//if (nominator > 100)


	MONO_PCM pcm0, pcm1;
	int n;

	int power = 4;	// powl(X, power)

	//  mono_wave_read(&pcm0, "a.wav"); /* WAVEファイルからモノラルの音データを入力する */
	mono_wave_read(&pcm0, "C:\\WORKS_2\\WS\\Eclipse_Luna\\C_SoundProg\\main\\D-6\\a.wav");	//=> working

	pcm1.fs = pcm0.fs; /* 標本化周波数 */
	pcm1.bits = pcm0.bits; /* 量子化精度 */
	pcm1.length = pcm0.length; /* 音データの長さ */
	pcm1.s = calloc(pcm1.length, sizeof(double)); /* メモリの確保 */

	/**********************
		Volume down
	**********************/
	volume_Down_PCMData_By_Percent(&pcm0, nominator);
//	volume_Down_PCMData_By_Percent(pcm0, nominator);


	/**********************
		copy : pcm data
	**********************/
	for (n = 0; n < pcm1.length; n++)
	{

		//ref fabs https://stackoverflow.com/questions/20956352/how-to-get-absolute-value-from-double-c-language "answered Jan 6 '14 at 18:08"
		pcm1.s[n] = powl(pcm0.s[n], power);
//		pcm1.s[n] = powl(pcm0.s[n] * (nominator / 100.0), power);
//		pcm1.s[n] = powl(pcm0.s[n] * (nominator / 100.0), 4);
//		pcm1.s[n] = pcm0.s[n] * (nominator / 100.0);
//		pcm1.s[n] = powl(pcm0.s[n], 4);

	}

	char fname_dst[100];

	char fname_trunk_full[50];

	//  char* fname_trunk = "b";
	char* fname_trunk = "SEG-1_volume-down";	// 14 chars	//=> file WAS generated (in this directory)
//	char* fname_trunk = "main\\D-6\\tink-2";	//=> file WAS generated (in this directory)
	//  char* fname_trunk = "\\main\\D-6\\b";	//=> file not generated (in this directory)
	//  char* fname_trunk = "..\\main\\D-6\\b";	//=> file not generated (in this directory)

	char* dirpath = "main\\D-6\\sound";	// 14 chars

	sprintf(fname_trunk_full,
			"%s\\%s_nomi-%d+Power-%d",
			dirpath, fname_trunk, nominator, power);
//	sprintf(fname_trunk_full, "%s\\%s", dirpath, fname_trunk);

	char* fname_ext = "wav";

	 get_file_name_with_time_label(fname_dst, fname_trunk_full, fname_ext);
//	 get_file_name_with_time_label(fname_dst, fname_trunk, fname_ext);

	 printf("[%s:%d] fname_dst => '%s'\n", basename(__FILE__, '\\'), __LINE__, fname_dst);

	 /**********************

		get: dirname

		**********************/
	 char* dpath = dirname(__FILE__, '\\');

	 printf("[%s:%d] dpath => '%s'\n", basename(__FILE__, '\\'), __LINE__, dpath);



	mono_wave_write(&pcm1, fname_dst); /* WAVEファイルにモノラルの音データを出力する */
	//  mono_wave_write(&pcm1, "b.wav"); /* WAVEファイルにモノラルの音データを出力する */
	//=> with "b.wav" ---> the file gets created at "C:\WORKS_2\WS\Eclipse_Luna\C_SoundProg"

	/**********************

		TINK-2

	**********************/

	/********************************************************
	 *
	 * free
	 *
	*********************************************************/
	free(pcm0.s); /* メモリの解放 */
	free(pcm1.s); /* メモリの解放 */

	/**********************

		report

	**********************/
	printf("[%s:%d] volume_Down_By_Percent(int nominator) => done\n", basename(__FILE__, '\\'), __LINE__);


}//void volume_Down_By_Percent(int nominator)

void sine_P4() {

	MONO_PCM pcm0, pcm1;
	int n;

	//  mono_wave_read(&pcm0, "a.wav"); /* WAVEファイルからモノラルの音データを入力する */
	mono_wave_read(&pcm0, "C:\\WORKS_2\\WS\\Eclipse_Luna\\C_SoundProg\\main\\D-6\\a.wav");	//=> working

	pcm1.fs = pcm0.fs; /* 標本化周波数 */
	pcm1.bits = pcm0.bits; /* 量子化精度 */
	pcm1.length = pcm0.length; /* 音データの長さ */
	pcm1.s = calloc(pcm1.length, sizeof(double)); /* メモリの確保 */
	for (n = 0; n < pcm1.length; n++)
	{

		//ref fabs https://stackoverflow.com/questions/20956352/how-to-get-absolute-value-from-double-c-language "answered Jan 6 '14 at 18:08"
		pcm1.s[n] = powl(pcm0.s[n], 4);
//		pcm1.s[n] = pcm0.s[n] * pcm0.s[n] * pcm0.s[n];	// sin^2
//		pcm1.s[n] = pcm0.s[n] * pcm0.s[n];	// sin^2
//		pcm1.s[n] = fabs(pcm0.s[n]); /* 音データのコピー */
//	  pcm1.s[n] = pcm0.s[n]; /* 音データのコピー */

	}

	char fname_dst[100];

	char fname_trunk_full[50];

	//  char* fname_trunk = "b";
	char* fname_trunk = "tink-5_P5";	// 14 chars	//=> file WAS generated (in this directory)
//	char* fname_trunk = "main\\D-6\\tink-2";	//=> file WAS generated (in this directory)
	//  char* fname_trunk = "\\main\\D-6\\b";	//=> file not generated (in this directory)
	//  char* fname_trunk = "..\\main\\D-6\\b";	//=> file not generated (in this directory)

	char* dirpath = "main\\D-6\\sound";	// 14 chars

	sprintf(fname_trunk_full, "%s\\%s", dirpath, fname_trunk);

	char* fname_ext = "wav";

	 get_file_name_with_time_label(fname_dst, fname_trunk_full, fname_ext);
//	 get_file_name_with_time_label(fname_dst, fname_trunk, fname_ext);

	 printf("[%s:%d] fname_dst => '%s'\n", basename(__FILE__, '\\'), __LINE__, fname_dst);

	 /**********************

		get: dirname

		**********************/
	 char* dpath = dirname(__FILE__, '\\');

	 printf("[%s:%d] dpath => '%s'\n", basename(__FILE__, '\\'), __LINE__, dpath);



	mono_wave_write(&pcm1, fname_dst); /* WAVEファイルにモノラルの音データを出力する */
	//  mono_wave_write(&pcm1, "b.wav"); /* WAVEファイルにモノラルの音データを出力する */
	//=> with "b.wav" ---> the file gets created at "C:\WORKS_2\WS\Eclipse_Luna\C_SoundProg"

	/**********************

		TINK-2

	**********************/

	/********************************************************
	 *
	 * free
	 *
	*********************************************************/
	free(pcm0.s); /* メモリの解放 */
	free(pcm1.s); /* メモリの解放 */

}//void sine_P4()

void sine_Cube() {

	MONO_PCM pcm0, pcm1;
	int n;

	//  mono_wave_read(&pcm0, "a.wav"); /* WAVEファイルからモノラルの音データを入力する */
	mono_wave_read(&pcm0, "C:\\WORKS_2\\WS\\Eclipse_Luna\\C_SoundProg\\main\\D-6\\a.wav");	//=> working

	pcm1.fs = pcm0.fs; /* 標本化周波数 */
	pcm1.bits = pcm0.bits; /* 量子化精度 */
	pcm1.length = pcm0.length; /* 音データの長さ */
	pcm1.s = calloc(pcm1.length, sizeof(double)); /* メモリの確保 */
	for (n = 0; n < pcm1.length; n++)
	{

		//ref fabs https://stackoverflow.com/questions/20956352/how-to-get-absolute-value-from-double-c-language "answered Jan 6 '14 at 18:08"
		pcm1.s[n] = pcm0.s[n] * pcm0.s[n] * pcm0.s[n];	// sin^2
//		pcm1.s[n] = pcm0.s[n] * pcm0.s[n];	// sin^2
//		pcm1.s[n] = fabs(pcm0.s[n]); /* 音データのコピー */
//	  pcm1.s[n] = pcm0.s[n]; /* 音データのコピー */

	}

	char fname_dst[100];

	char fname_trunk_full[50];

	//  char* fname_trunk = "b";
	char* fname_trunk = "tink-4_cube";	// 14 chars	//=> file WAS generated (in this directory)
//	char* fname_trunk = "main\\D-6\\tink-2";	//=> file WAS generated (in this directory)
	//  char* fname_trunk = "\\main\\D-6\\b";	//=> file not generated (in this directory)
	//  char* fname_trunk = "..\\main\\D-6\\b";	//=> file not generated (in this directory)

	char* dirpath = "main\\D-6\\sound";	// 14 chars

	sprintf(fname_trunk_full, "%s\\%s", dirpath, fname_trunk);

	char* fname_ext = "wav";

	 get_file_name_with_time_label(fname_dst, fname_trunk_full, fname_ext);
//	 get_file_name_with_time_label(fname_dst, fname_trunk, fname_ext);

	 printf("[%s:%d] fname_dst => '%s'\n", basename(__FILE__, '\\'), __LINE__, fname_dst);

	 /**********************

		get: dirname

		**********************/
	 char* dpath = dirname(__FILE__, '\\');

	 printf("[%s:%d] dpath => '%s'\n", basename(__FILE__, '\\'), __LINE__, dpath);



	mono_wave_write(&pcm1, fname_dst); /* WAVEファイルにモノラルの音データを出力する */
	//  mono_wave_write(&pcm1, "b.wav"); /* WAVEファイルにモノラルの音データを出力する */
	//=> with "b.wav" ---> the file gets created at "C:\WORKS_2\WS\Eclipse_Luna\C_SoundProg"

	/**********************

		TINK-2

	**********************/

	/********************************************************
	 *
	 * free
	 *
	*********************************************************/
	free(pcm0.s); /* メモリの解放 */
	free(pcm1.s); /* メモリの解放 */

}//void sine_Cube()

void sine_Cube__V2() {

	MONO_PCM pcm0, pcm1;
	int n;

	//  mono_wave_read(&pcm0, "a.wav"); /* WAVEファイルからモノラルの音データを入力する */
	mono_wave_read(&pcm0, "C:\\WORKS_2\\WS\\Eclipse_Luna\\C_SoundProg\\main\\D-6\\a.wav");	//=> working

	pcm1.fs = pcm0.fs; /* 標本化周波数 */
	pcm1.bits = pcm0.bits; /* 量子化精度 */
	pcm1.length = pcm0.length; /* 音データの長さ */
	pcm1.s = calloc(pcm1.length, sizeof(double)); /* メモリの確保 */

	/**********************
		volume down
	**********************/
	volume_Down_PCMData_By_Percent(&pcm0, 999);

	/**********************
		sine cube
	**********************/
	for (n = 0; n < pcm1.length; n++)
	{

		//ref fabs https://stackoverflow.com/questions/20956352/how-to-get-absolute-value-from-double-c-language "answered Jan 6 '14 at 18:08"
		pcm1.s[n] = pcm0.s[n] * pcm0.s[n] * pcm0.s[n];	// sin^2
//		pcm1.s[n] = pcm0.s[n] * pcm0.s[n];	// sin^2
//		pcm1.s[n] = fabs(pcm0.s[n]); /* 音データのコピー */
//	  pcm1.s[n] = pcm0.s[n]; /* 音データのコピー */

	}

	char fname_dst[100];

	char fname_trunk_full[50];

	//  char* fname_trunk = "b";
	char* fname_trunk = "tink-4_cube_V2";	// 14 chars	//=> file WAS generated (in this directory)
//	char* fname_trunk = "main\\D-6\\tink-2";	//=> file WAS generated (in this directory)
	//  char* fname_trunk = "\\main\\D-6\\b";	//=> file not generated (in this directory)
	//  char* fname_trunk = "..\\main\\D-6\\b";	//=> file not generated (in this directory)

	char* dirpath = "main\\D-6\\sound";	// 14 chars

	sprintf(fname_trunk_full, "%s\\%s", dirpath, fname_trunk);

	char* fname_ext = "wav";

	 get_file_name_with_time_label(fname_dst, fname_trunk_full, fname_ext);
//	 get_file_name_with_time_label(fname_dst, fname_trunk, fname_ext);

	 printf("[%s:%d] fname_dst => '%s'\n", basename(__FILE__, '\\'), __LINE__, fname_dst);

	 /**********************

		get: dirname

		**********************/
	 char* dpath = dirname(__FILE__, '\\');

	 printf("[%s:%d] dpath => '%s'\n", basename(__FILE__, '\\'), __LINE__, dpath);



	mono_wave_write(&pcm1, fname_dst); /* WAVEファイルにモノラルの音データを出力する */
	//  mono_wave_write(&pcm1, "b.wav"); /* WAVEファイルにモノラルの音データを出力する */
	//=> with "b.wav" ---> the file gets created at "C:\WORKS_2\WS\Eclipse_Luna\C_SoundProg"

	/**********************

		TINK-2

	**********************/

	/********************************************************
	 *
	 * free
	 *
	*********************************************************/
	free(pcm0.s); /* メモリの解放 */
	free(pcm1.s); /* メモリの解放 */

}//void sine_Cube__V2()

void sine_Squared() {

	MONO_PCM pcm0, pcm1;
	int n;

	//  mono_wave_read(&pcm0, "a.wav"); /* WAVEファイルからモノラルの音データを入力する */
	mono_wave_read(&pcm0, "C:\\WORKS_2\\WS\\Eclipse_Luna\\C_SoundProg\\main\\D-6\\a.wav");	//=> working

	pcm1.fs = pcm0.fs; /* 標本化周波数 */
	pcm1.bits = pcm0.bits; /* 量子化精度 */
	pcm1.length = pcm0.length; /* 音データの長さ */
	pcm1.s = calloc(pcm1.length, sizeof(double)); /* メモリの確保 */
	for (n = 0; n < pcm1.length; n++)
	{

		//ref fabs https://stackoverflow.com/questions/20956352/how-to-get-absolute-value-from-double-c-language "answered Jan 6 '14 at 18:08"
		pcm1.s[n] = pcm0.s[n] * pcm0.s[n];	// sin^2
//		pcm1.s[n] = fabs(pcm0.s[n]); /* 音データのコピー */
//	  pcm1.s[n] = pcm0.s[n]; /* 音データのコピー */

	}

	char fname_dst[100];

	char fname_trunk_full[50];

	//  char* fname_trunk = "b";
	char* fname_trunk = "tink-3_squared";	// 14 chars	//=> file WAS generated (in this directory)
//	char* fname_trunk = "main\\D-6\\tink-2";	//=> file WAS generated (in this directory)
	//  char* fname_trunk = "\\main\\D-6\\b";	//=> file not generated (in this directory)
	//  char* fname_trunk = "..\\main\\D-6\\b";	//=> file not generated (in this directory)

	char* dirpath = "main\\D-6\\sound";	// 14 chars

	sprintf(fname_trunk_full, "%s\\%s", dirpath, fname_trunk);

	char* fname_ext = "wav";

	 get_file_name_with_time_label(fname_dst, fname_trunk_full, fname_ext);
//	 get_file_name_with_time_label(fname_dst, fname_trunk, fname_ext);

	 printf("[%s:%d] fname_dst => '%s'\n", basename(__FILE__, '\\'), __LINE__, fname_dst);

	 /**********************

		get: dirname

		**********************/
	 char* dpath = dirname(__FILE__, '\\');

	 printf("[%s:%d] dpath => '%s'\n", basename(__FILE__, '\\'), __LINE__, dpath);



	mono_wave_write(&pcm1, fname_dst); /* WAVEファイルにモノラルの音データを出力する */
	//  mono_wave_write(&pcm1, "b.wav"); /* WAVEファイルにモノラルの音データを出力する */
	//=> with "b.wav" ---> the file gets created at "C:\WORKS_2\WS\Eclipse_Luna\C_SoundProg"

	/**********************

		TINK-2

	**********************/

	/********************************************************
	 *
	 * free
	 *
	*********************************************************/
	free(pcm0.s); /* メモリの解放 */
	free(pcm1.s); /* メモリの解放 */

}//void sine_Squared()

void sine_Squared__V2() {

	MONO_PCM pcm0, pcm1;
	int n;

	//  mono_wave_read(&pcm0, "a.wav"); /* WAVEファイルからモノラルの音データを入力する */
	mono_wave_read(&pcm0, "C:\\WORKS_2\\WS\\Eclipse_Luna\\C_SoundProg\\main\\D-6\\a.wav");	//=> working

	pcm1.fs = pcm0.fs; /* 標本化周波数 */
	pcm1.bits = pcm0.bits; /* 量子化精度 */
	pcm1.length = pcm0.length; /* 音データの長さ */
	pcm1.s = calloc(pcm1.length, sizeof(double)); /* メモリの確保 */

	/**********************
		volume --> down
	**********************/
	volume_Down_PCMData_By_Percent(&pcm0, 999);


	for (n = 0; n < pcm1.length; n++)
	{

		//ref fabs https://stackoverflow.com/questions/20956352/how-to-get-absolute-value-from-double-c-language "answered Jan 6 '14 at 18:08"
		pcm1.s[n] = pcm0.s[n] * pcm0.s[n];	// sin^2
//		pcm1.s[n] = fabs(pcm0.s[n]); /* 音データのコピー */
//	  pcm1.s[n] = pcm0.s[n]; /* 音データのコピー */

	}

	char fname_dst[100];

	char fname_trunk_full[50];

	//  char* fname_trunk = "b";
	char* fname_trunk = "tink-3_squared-V2";	// 14 chars	//=> file WAS generated (in this directory)
//	char* fname_trunk = "main\\D-6\\tink-2";	//=> file WAS generated (in this directory)
	//  char* fname_trunk = "\\main\\D-6\\b";	//=> file not generated (in this directory)
	//  char* fname_trunk = "..\\main\\D-6\\b";	//=> file not generated (in this directory)

	char* dirpath = "main\\D-6\\sound";	// 14 chars

	sprintf(fname_trunk_full, "%s\\%s", dirpath, fname_trunk);

	char* fname_ext = "wav";

	 get_file_name_with_time_label(fname_dst, fname_trunk_full, fname_ext);
//	 get_file_name_with_time_label(fname_dst, fname_trunk, fname_ext);

	 printf("[%s:%d] fname_dst => '%s'\n", basename(__FILE__, '\\'), __LINE__, fname_dst);

	 /**********************

		get: dirname

		**********************/
	 char* dpath = dirname(__FILE__, '\\');

	 printf("[%s:%d] dpath => '%s'\n", basename(__FILE__, '\\'), __LINE__, dpath);



	mono_wave_write(&pcm1, fname_dst); /* WAVEファイルにモノラルの音データを出力する */
	//  mono_wave_write(&pcm1, "b.wav"); /* WAVEファイルにモノラルの音データを出力する */
	//=> with "b.wav" ---> the file gets created at "C:\WORKS_2\WS\Eclipse_Luna\C_SoundProg"

	/**********************

		TINK-2

	**********************/

	/********************************************************
	 *
	 * free
	 *
	*********************************************************/
	free(pcm0.s); /* メモリの解放 */
	free(pcm1.s); /* メモリの解放 */

}//void sine_Squared()

void absolutize_Sound_Data() {

	MONO_PCM pcm0, pcm1;
	int n;

	//  mono_wave_read(&pcm0, "a.wav"); /* WAVEファイルからモノラルの音データを入力する */
	mono_wave_read(&pcm0, "C:\\WORKS_2\\WS\\Eclipse_Luna\\C_SoundProg\\main\\D-6\\a.wav");	//=> working

	pcm1.fs = pcm0.fs; /* 標本化周波数 */
	pcm1.bits = pcm0.bits; /* 量子化精度 */
	pcm1.length = pcm0.length; /* 音データの長さ */
	pcm1.s = calloc(pcm1.length, sizeof(double)); /* メモリの確保 */

	/**********************
		Volume down
	**********************/
	volume_Down_PCMData_By_Percent(&pcm0, 999);


	/**********************
		absolutize
	**********************/
	absolutize_MONO_PCM(&pcm0);



	for (n = 0; n < pcm1.length; n++)
	{

		//ref fabs https://stackoverflow.com/questions/20956352/how-to-get-absolute-value-from-double-c-language "answered Jan 6 '14 at 18:08"
		pcm1.s[n] = pcm0.s[n]; /* 音データのコピー */
//		pcm1.s[n] = fabs(pcm0.s[n]); /* 音データのコピー */
//	  pcm1.s[n] = pcm0.s[n]; /* 音データのコピー */

	}

	char fname_dst[100];

	char fname_trunk_full[50];

	//  char* fname_trunk = "b";
	char* fname_trunk = "tink-2.Absolute";	//=> file WAS generated (in this directory)
//	char* fname_trunk = "main\\D-6\\tink-2";	//=> file WAS generated (in this directory)
	//  char* fname_trunk = "\\main\\D-6\\b";	//=> file not generated (in this directory)
	//  char* fname_trunk = "..\\main\\D-6\\b";	//=> file not generated (in this directory)

	char* dirpath = "main\\D-6\\sound";

	sprintf(fname_trunk_full, "%s\\%s", dirpath, fname_trunk);

	char* fname_ext = "wav";

	 get_file_name_with_time_label(fname_dst, fname_trunk_full, fname_ext);
//	 get_file_name_with_time_label(fname_dst, fname_trunk, fname_ext);

	 printf("[%s:%d] fname_dst => '%s'\n", basename(__FILE__, '\\'), __LINE__, fname_dst);

	 /**********************

		get: dirname

		**********************/
	 char* dpath = dirname(__FILE__, '\\');

	 printf("[%s:%d] dpath => '%s'\n", basename(__FILE__, '\\'), __LINE__, dpath);



	mono_wave_write(&pcm1, fname_dst); /* WAVEファイルにモノラルの音データを出力する */
	//  mono_wave_write(&pcm1, "b.wav"); /* WAVEファイルにモノラルの音データを出力する */
	//=> with "b.wav" ---> the file gets created at "C:\WORKS_2\WS\Eclipse_Luna\C_SoundProg"

	/**********************

		TINK-2

	**********************/

	/********************************************************
	 *
	 * free
	 *
	*********************************************************/
	free(pcm0.s); /* メモリの解放 */
	free(pcm1.s); /* メモリの解放 */

}//void absolutize_Sound_Data()

void show_Basic_PCM_Data(MONO_PCM* pcm0) {

//	int fs; /* 標本化周波数 */
//	int bits; /* 量子化精度 */
//	int length; /* 音データの長さ */
//	double *s; /* 音データ */

	printf("[%s:%d] Basic data\n", basename(__FILE__, '\\'), __LINE__);

	printf("fs\t= %d\nbits\t= %d\nlength\t= %d", pcm0->fs, pcm0->bits, pcm0->length);


}//void show_Basic_PCM_Data(MONO_PCM* pcm0)

int main(void)
{

//	volume_Down_By_Percent(999);
//	volume_Down_By_Percent(99);
//	sine_P4();
//	sine_Cube();
	sine_Cube__V2();
//	sine_Squared();
//	sine_Squared__V2();
//	absolutize_Sound_Data();
//	write_PCMData_to_File();
//	test_ex1_x();

//  MONO_PCM pcm0, pcm1;
//  int n;
//
////  mono_wave_read(&pcm0, "a.wav"); /* WAVEファイルからモノラルの音データを入力する */
//  mono_wave_read(&pcm0, "C:\\WORKS_2\\WS\\Eclipse_Luna\\C_SoundProg\\main\\D-6\\a.wav");	//=> working
//
//  pcm1.fs = pcm0.fs; /* 標本化周波数 */
//  pcm1.bits = pcm0.bits; /* 量子化精度 */
//  pcm1.length = pcm0.length; /* 音データの長さ */
//  pcm1.s = calloc(pcm1.length, sizeof(double)); /* メモリの確保 */
//  for (n = 0; n < pcm1.length; n++)
//  {
//    pcm1.s[n] = pcm0.s[n]; /* 音データのコピー */
//  }
//
//  char fname_dst[100];
//
////  char* fname_trunk = "b";
//  char* fname_trunk = "main\\D-6\\b";	//=> file WAS generated (in this directory)
////  char* fname_trunk = "\\main\\D-6\\b";	//=> file not generated (in this directory)
////  char* fname_trunk = "..\\main\\D-6\\b";	//=> file not generated (in this directory)
//
//  char* fname_ext = "wav";
//
//   get_file_name_with_time_label(fname_dst, fname_trunk, fname_ext);
//
//   printf("[%s:%d] fname_dst => '%s'\n", basename(__FILE__, '\\'), __LINE__, fname_dst);
//
//   /**********************
//
//	get: dirname
//
//	**********************/
//   char* dpath = dirname(__FILE__, '\\');
//
//   printf("[%s:%d] dpath => '%s'\n", basename(__FILE__, '\\'), __LINE__, dpath);
//
//
//
//  mono_wave_write(&pcm1, fname_dst); /* WAVEファイルにモノラルの音データを出力する */
////  mono_wave_write(&pcm1, "b.wav"); /* WAVEファイルにモノラルの音データを出力する */
//  //=> with "b.wav" ---> the file gets created at "C:\WORKS_2\WS\Eclipse_Luna\C_SoundProg"
//
//  free(pcm0.s); /* メモリの解放 */
//  free(pcm1.s); /* メモリの解放 */
  
  return 0;
}
