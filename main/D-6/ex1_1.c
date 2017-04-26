#include <stdio.h>
#include <stdlib.h>
//#include "wave.h"
#include "../../utils/utils.h"

#include "../../utils/wave.h"

int main(void)
{
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
  char* fname_trunk = "b";
  char* fname_ext = "wav";

   get_file_name_with_time_label(fname_dst, fname_trunk, fname_ext);

   printf("[%s:%d] fname_dst => '%s'\n", basename(__FILE__, '\\'), __LINE__, fname_dst);


  mono_wave_write(&pcm1, fname_dst); /* WAVEファイルにモノラルの音データを出力する */
//  mono_wave_write(&pcm1, "b.wav"); /* WAVEファイルにモノラルの音データを出力する */
  //=> with "b.wav" ---> the file gets created at "C:\WORKS_2\WS\Eclipse_Luna\C_SoundProg"
  
  free(pcm0.s); /* メモリの解放 */
  free(pcm1.s); /* メモリの解放 */
  
  return 0;
}
