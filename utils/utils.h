/*
 * utils.h
 *
 *  Created on: 2015/08/22
 *      Author: kbuchi
 */

#ifndef UTILS_H_
#define UTILS_H_

#ifndef ASSERT_H_
#define ASSERT_H_
#include <assert.h>
#endif

#ifndef STRING_H_
#define STRING_H_
#include <string.h>
#endif

#ifndef STDIO_H_
#define STDIO_H_
#include <stdio.h>
#endif

#ifndef STDLIB_H_
#define STDLIB_H_
#include <stdlib.h>
#endif

#ifndef TIME_H_
#define TIME_H_
#include <time.h>
#endif

#ifndef LIMITS_H_
#define LIMITS_H_
#include <limits.h>
#endif

/********************************************************
 *
 * prototypes
 *
*********************************************************/
char* get_Time_Label(char*);
char** str_split(char*, const char);
int get_random_integer(int);
char* get_file_name_with_time_label(char[], char*, char*);
char* basename(char*, const char);
char** str_split_V3(char* a_str, const char a_delim, int* num);

/********************************************************
 *
 * functions
 *
*********************************************************/
//char* get_Time_Label(char* time_label) {
//
////	char time_label[30];
//
//	sprintf(time_label, "%s", "2015-08");
//
//	return time_label;
//
//}

/********************************************************
 *
 * from: C:\WORKS_2\WS\Eclipse_Neon\Sound_Programming_in_C\src\D-4\utils\utils.h
 * at: 2017/04/27 02:06:39
 *
*********************************************************/
/****************************
 *	@param time_label ---> char[14]
 *
 *	@return
 *	20161217_0112 (13 + 1 = 14 length)
 *
 *****************************/
char* get_Time_Label(char* time_label) {

	//ref http://stackoverflow.com/questions/5141960/get-the-current-time-in-c
	time_t rawtime;
	struct tm * timeinfo;

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );

	sprintf(time_label, "%04d%02d%02d_%02d%02d%02d",
//	sprintf(time_label, "[%04d%02d%02d_%02d%02d%02d]",
//			timeinfo->tm_year,
			timeinfo->tm_year + 1900,
			timeinfo->tm_mon + 1,
			timeinfo->tm_mday,
			timeinfo->tm_hour,
			timeinfo->tm_min,
			timeinfo->tm_sec);

//	char time_label[30];

//	sprintf(time_label, "%s", "2015-08");

	return time_label;

}

char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}

int get_random_integer(int max) {

	//ref http://stackoverflow.com/questions/17846212/generate-a-random-number-between-1-and-10-in-c
	int randomnumber;

	srand(time(NULL));

	randomnumber = rand() % max;


	return randomnumber;

}//get_random_integer(int)

///////////////////////

// from: /Sound_Programming_in_C/src/D-4/utils/utils.h
// at: 2017/04/27 00:45:30

///////////////////////
char* get_file_name_with_time_label
(char fname[], char* fname_trunk, char* fname_ext) {

//	char	fname[50];	//=>

	// get: time label
	char	time_label[14];
	get_Time_Label(time_label);

	//test
//	char* fname_format = "files\\test_2.%s.aaaaaaaaaaaaaaaaaaaaaaa.txt";
//	char* fname_format = "files\\test_2.%s.txt";

	sprintf(fname, "%s.%s.%s", fname_trunk, time_label, fname_ext);

	return fname;

}//char* get_file_name_with_time_label

/********************************************************
 *
 * basename(char* full_path, const char path_delimiter)
 * from: C:\WORKS_2\WS\Eclipse_Luna\C_ImageProg\utils\utils.c
 * at: 2017/04/27 00:50:24
 *
*********************************************************/
char* basename(char* full_path, const char path_delimiter) {

	char *tmp = malloc((sizeof(char) * (strlen(full_path) + 1)));
	strcpy(tmp, full_path);

	char **tokens;

	int num;

//	printf("full_path = [%s] (%d)\n\n", full_path, strlen(full_path));

	tokens = str_split_V3(tmp, path_delimiter, &num);

//	printf("[%s:%d] num => %d\n", __FILE__, __LINE__, num);

	///////////////////////////////
	//
	// basename
	//
	 ///////////////////////////////
	char * bname = malloc(sizeof(char) * (strlen(tokens[num - 1]) + 1));
//	char * bname = malloc(sizeof(char) * tokens[num - 1] + 1);

	strcpy(bname, tokens[num - 1]);

//	printf("[%s:%d] bname => %s\n", __FILE__, __LINE__, bname);

	///////////////////////////////
	//
	// free
	//
	 ///////////////////////////////
	int i;

	for (i = 0; i < num - 1; ++i) {

		free(tokens[i]);

	}

	///////////////////////////////
	//
	// return
	//
	 ///////////////////////////////
	return bname;

//	char** tokens;
//
//	char delim_char = '\\';
//
//	int num;
//
//	printf("[%s:%d] delim_char = %c\n", __FILE__, __LINE__, delim_char);
//
//
//	// split
////	tokens = str_split_V2(full_path, delim_char, num);
//	tokens = str_split_V2(full_path, delim_char, &num);
//
//	printf("[%s:%d] split done => %s (num = %d)\n", __FILE__, __LINE__, full_path, num);
////	printf("[%s:%d] split done => %s (num = %d)\n", __FILE__, __LINE__, full_path, *num);
//
//
//	// get the last token
//	if (num <= 1) {
//
//		printf("[%s:%d] num <= 1: tokens[0] = %s\n", __FILE__, __LINE__, tokens[0]);
//
//		return tokens[0];
//
////		return tokens[0];
//
//	} else {
//
//		printf("[%s:%d] num > 1: tokens[0] = %s\n", __FILE__, __LINE__, tokens[0]);
//
//		return tokens[0];
//
////		int i;
////
////		for (i = 0; i < num - 2; ++i) {
////
////			free(*(tokens + i));
////
////		}
////
////		return tokens[i];
//
//	}

}//basename(char* full_path, const char path_delimiter)

char* dirname(char* full_path,  const char path_delimiter) {

	int len_1 = strlen(full_path);

	char* bname = basename(full_path, '\\');

	int len_2 = strlen(bname);

	int len_3 = len_1 - len_2;

	/**********************

		validate

	**********************/
	if (len_3 < 1) {

		printf("[%s:%d] seems no dir path... : '%s'\n", basename(__FILE__, '\\'), __LINE__, full_path);

		return full_path;

	} else {

		printf("[%s:%d] full path = '%s'\n", basename(__FILE__, '\\'), __LINE__, full_path);
		printf("[%s:%d] base name = '%s'\n", basename(__FILE__, '\\'), __LINE__, bname);


	}

	/**********************

		build dirpath

	**********************/
	char* dpath = malloc(sizeof(char) * (len_3 + 1));

	// omit separator char
//	printf("[%s:%d] full_path[len_3 - 1] => '%c'\n",
//			basename(__FILE__, '\\'), __LINE__, full_path[len_3 - 1]);

	if (full_path[len_3 - 1] == '\\') {

		strncpy(dpath, full_path, len_3 - 1);

		dpath[len_3 - 1] = '\0';

	} else {//if (full_path[len_3 - 1] == '\\')

		strncpy(dpath, full_path, len_3);

		dpath[len_3] = '\0';

	}//if (full_path[len_3 - 1] == '\\')


//	strncpy(dpath, full_path, len_3);

	// ending char
//	dpath[len_3] = '\0';

	/**********************

		free variables

	**********************/
	free(bname);

	/**********************

		return

	**********************/
	return dpath;


//	char *tmp = malloc((sizeof(char) * (strlen(full_path) + 1)));
//	strcpy(tmp, full_path);
//
//	char **tokens;
//
//	int num;
//
////	printf("full_path = [%s] (%d)\n\n", full_path, strlen(full_path));
//
//	tokens = str_split_V3(tmp, path_delimiter, &num);
//
//	printf("[%s:%d] num => '%d'\n", basename(__FILE__, '\\'), __LINE__, num);
//
//	printf("[%s:%d] full_path => '%s'\n", basename(__FILE__, '\\'), __LINE__, full_path);
//
//	//ref strlen http://simd.jugem.jp/?eid=123
//	int string_len = strlen(full_path);
////	int string_len = sizeof(full_path) / sizeof(char);
////
//	printf("[%s:%d] string length => %d\n", basename(__FILE__, '\\'), __LINE__, string_len);
//
//
////	printf("[%s:%d] num => %d\n", __FILE__, __LINE__, num);
//
//	///////////////////////////////
//	//
//	// basename
//	//
//	 ///////////////////////////////
//	char * bname = malloc(sizeof(char) * (strlen(tokens[num - 1]) + 1));
////	char * bname = malloc(sizeof(char) * tokens[num - 1] + 1);
//
//	strcpy(bname, tokens[num - 1]);
//
////	printf("[%s:%d] bname => %s\n", __FILE__, __LINE__, bname);
//
//	///////////////////////////////
//	//
//	// free
//	//
//	 ///////////////////////////////
//	int i;
//
//	for (i = 0; i < num - 1; ++i) {
//
//		free(tokens[i]);
//
//	}
//
//	///////////////////////////////
//	//
//	// return
//	//
//	 ///////////////////////////////
//	return bname;

}//dirname(char* full_path,  const char path_delimiter)


/********************************************************
 *
 * str_split_V3(char* a_str, const char a_delim, int* num)
 * from: C:\WORKS_2\WS\Eclipse_Luna\C_ImageProg\utils\utils.c
 * at: 2017/04/27 00:50:24
 *
*********************************************************/
///////////////////////////////
//
// @return
//	=> number of tokens
//
///////////////////////////////
char** str_split_V3(char* a_str, const char a_delim, int* num) {
    char** result    = 0;
    size_t count     = 0;

//    printf("[%s:%d] a_str => %d\n", __FILE__, __LINE__, strlen(a_str));

//    char *a_str_dup = malloc((sizeof(char) * (strlen(a_str) + 2)));
////    char *a_str_dup = malloc((sizeof(char) * (strlen(a_str) + 1)));
//
//    strcpy(a_str_dup, a_str);
//
//    printf("[%s:%d] a_str_dup = %s\n", __FILE__, __LINE__, a_str_dup);
//
//
//    char* tmp        = a_str_dup;
    char* tmp        = a_str;

//    printf("[%s:%d] tmp => %s\n", __FILE__, __LINE__, tmp);


    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

//    printf("[%s:%d] count => done (count = %d)\n", __FILE__, __LINE__, count);

    ///////////////////////////////
	//
	// set num
	//
	 ///////////////////////////////
	*num = count - 1;

    result = malloc(sizeof(char*) * count);

//    printf("[%s:%d] malloc => done\n", __FILE__, __LINE__);
//
//    printf("[%s:%d] a_str = %s / delim = %c\n", __FILE__, __LINE__, a_str, a_delim);
//    printf("[%s:%d] a_str = %s / delim = %c\n", __FILE__, __LINE__, a_str, delim);


    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

//        printf("[%s:%d] strtok => 1st\n", __FILE__, __LINE__);


        while (token)
        {
//        	printf("[%s:%d] assert(idx < count)\n", __FILE__, __LINE__);

            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }

//        printf("[%s:%d] assert(idx == count - 1)\n", __FILE__, __LINE__);

        assert(idx == count - 1);
        *(result + idx) = 0;
    }

//    printf("[%s:%d] result => set\n", __FILE__, __LINE__);


    return result;
}


#endif /* UTILS_H_ */
