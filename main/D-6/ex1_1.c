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

int write_PCMData_to_File(void);
//int write_PCMData_to_File(MONO_PCM pcm);
void absolutize_Sound_Data();
void sine_Squared();

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

void absolutize_Sound_Data() {

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
		pcm1.s[n] = fabs(pcm0.s[n]); /* 音データのコピー */
//	  pcm1.s[n] = pcm0.s[n]; /* 音データのコピー */

	}

	char fname_dst[100];

	char fname_trunk_full[50];

	//  char* fname_trunk = "b";
	char* fname_trunk = "tink-2";	//=> file WAS generated (in this directory)
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

int main(void)
{

	sine_Cube();
//	sine_Squared();
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
