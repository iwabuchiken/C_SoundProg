/*
 * utils.h
 *
 *  Created on: 2015/08/22
 *      Author: kbuchi
 */
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

#ifndef UTILS_H_
#include "utils.h"
#endif

char* get_Time_Label(char* time_label) {

	//REF http://stackoverflow.com/questions/5141960/get-the-current-time-in-c answered Feb 28 '11 at 12:33
	time_t rawtime;
	struct tm * timeinfo;

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );

	//ref http://stackoverflow.com/questions/5141960/get-the-current-time-in-c answered May 29 at 4:59
//	sprintf(time_label, "[%d %d %d %d:%d:%d]",timeinfo->tm_mday, timeinfo->tm_mon + 1, timeinfo->tm_year + 1900, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);

//	char time_label[30];

	sprintf(time_label, "%s", "2015-08");

	return time_label;

}

char* get_Time_Label__Now() {

	char* time_label = malloc(sizeof(char) * 20);

	//REF http://stackoverflow.com/questions/5141960/get-the-current-time-in-c answered Feb 28 '11 at 12:33
	time_t rawtime;
	struct tm * timeinfo;

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );

//	printf("Current local time and date: %s", asctime(timeinfo));

//	//ref http://stackoverflow.com/questions/5498628/time-in-c-language answered Mar 31 '11 at 10:50
//	struct timespec ts = { 0 };
//
//	  clock_gettime(CLOCK_REALTIME, &ts);
//
//	  printf("sec: %ld nsec: %ld\n", ts.tv_sec, ts.tv_nsec);

	//ref http://stackoverflow.com/questions/5141960/get-the-current-time-in-c answered May 29 at 4:59
//	sprintf(time_label, "[%d]",timeinfo->tm_mday);

	/****************************
	 * month
	 *****************************/
	char month[3];

	if (timeinfo->tm_mon + 1 < 10) {

		month[0] = '0';
		month[1] = '0' + timeinfo->tm_mon + 1;
		month[2] = '\0';

	} else {

		sprintf(month, "%d", timeinfo->tm_mon + 1);

	}

	/****************************
	 * date
	 *****************************/
	char date[3];

	if (timeinfo->tm_mday < 10) {

		date[0] = '0';
		date[1] = '0' + timeinfo->tm_mday;
		date[2] = '\0';

	} else {

		sprintf(date, "%d", timeinfo->tm_mday);

	}



//	sprintf(time_label, "[%d%s%s_%d%d%d]",
//	sprintf(time_label, "[%d%s%2d_%d%d%d]",
//	sprintf(time_label, "[%d%s%d_%d%d%d]",
	sprintf(time_label, "%d%02d%02d_%02d%02d%02d",
//	sprintf(time_label, "[%d%02d%02d_%02d%02d%02d]",
//	sprintf(time_label, "[%d%d%d_%d%d%d]",

			//ref http://www.tutorialspoint.com/c_standard_library/c_function_localtime.htm "This function returns a pointe"
					timeinfo->tm_year + 1900,
					timeinfo->tm_mon + 1,
//					month,
//					date,
					timeinfo->tm_mday,

					timeinfo->tm_hour,
					timeinfo->tm_min,
					timeinfo->tm_sec);

//	char time_label[30];

//	sprintf(time_label, "%s", "2015-08");

	//ref http://stackoverflow.com/questions/5833094/get-a-timestamp-in-c-in-microseconds
//	struct timeval tv;
//	gettimeofday(&tv,NULL);
//
//	printf("[%s:%d] tv.sec => %d\n", basename(__FILE__, '\\'), __LINE__, tv.tv_sec);
//
//	unsigned long time_in_micros = 1000000 * tv.tv_sec + tv.tv_usec;
//
//	printf("[%s:%d] micro => %ld\n", basename(__FILE__, '\\'), __LINE__, time_in_micros);


	return time_label;

}

//REF http://stackoverflow.com/questions/9210528/split-string-with-delimiters-in-c answered Feb 9 '12 at 12:09
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

///////////////////////////////
//
// @return
//	=> number of tokens
//
///////////////////////////////
char** str_split_V2(char* a_str, const char a_delim, int* num) {
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

    printf("[%s:%d] count => done (count = %d)\n", __FILE__, __LINE__, count);

    ///////////////////////////////
	//
	// set num
	//
	 ///////////////////////////////
	*num = count - 1;

    result = malloc(sizeof(char*) * count);

    printf("[%s:%d] malloc => done\n", __FILE__, __LINE__);

    printf("[%s:%d] a_str = %s / delim = %c\n", __FILE__, __LINE__, a_str, a_delim);
//    printf("[%s:%d] a_str = %s / delim = %c\n", __FILE__, __LINE__, a_str, delim);


    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        printf("[%s:%d] strtok => 1st\n", __FILE__, __LINE__);


        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    printf("[%s:%d] result => set\n", __FILE__, __LINE__);


    return result;
}

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

char** tokenize(char *str, const char *delim) {
//void tokenize(char *str, const char *delim) {

	char *token;

	///////////////////////////////
	//
	// count: how many tokens
	//REF http://stackoverflow.com/questions/9210528/split-string-with-delimiters-in-c answered Feb 9 '12 at 12:09
	//
	 ///////////////////////////////
    char* tmp        = str;
    char* last_comma = 0;
//    char delim[2];
//    delim[0] = a_delim;
//    delim[1] = 0;

    size_t count     = 0;

    printf("[%s:%d] tmp = %s(&tmp=%p)\n", __FILE__, __LINE__, tmp, &tmp);
    printf("[%s:%d] tmp = %%d=%d (%%p=%p)\n", __FILE__, __LINE__, tmp, tmp);
    printf("[%s:%d] str = %%d=%d (%%p=%p)\n", __FILE__, __LINE__, str, str);
    printf("[%s:%d] &str = %%d=%d (%%p=%p)\n", __FILE__, __LINE__, &str, &str);

    printf("[%s:%d] delim = '%s'\n", __FILE__, __LINE__, delim);
    printf("[%s:%d] delim[0] = '%c'\n", __FILE__, __LINE__, delim[0]);


    while (*tmp)
    {
//    	printf("[%s:%d] *tmp = '%c'\n", __FILE__, __LINE__, *tmp);
//    	printf("[%s:%d] *tmp = %s\n", __FILE__, __LINE__, *tmp);

        if (delim[0] == *tmp)
//        if (delim == *tmp)
//        if (a_delim == *tmp)
        {
        	printf("[%s:%d] delim[0] = '%c' / *tmp = '%c'\n",
        						__FILE__, __LINE__, delim[0], *tmp);
//        	printf("[%s:%d] delim = '%s' / *tmp = '%s'\n", __FILE__, __LINE__, delim, *tmp);

            count++;
            last_comma = tmp;

            printf("[%s:%d] last_comma = %s\n", __FILE__, __LINE__, last_comma);

        }
        tmp++;
    }

    printf("[%s:%d] count = %d\n", __FILE__, __LINE__, count);

    printf("[%s:%d] &last_comma => %p(%%d=%d)\n",
    					__FILE__, __LINE__, &last_comma, &last_comma);
    printf("[%s:%d] &str => %p(%%d=%d)\n", __FILE__, __LINE__, &str, &str);
    printf("[%s:%d] strlen(str) - 1 => %d\n", __FILE__, __LINE__, strlen(str) - 1);
//    printf("[%s:%d] str => %d\n", __FILE__, __LINE__, &str + strlen(str) - 1);

    printf("[%s:%d] str + strlen(str) - 1 => %s\n", __FILE__, __LINE__, str + strlen(str) - 1);
    printf("[%s:%d] str + strlen(str) - 2 => %s\n", __FILE__, __LINE__, str + strlen(str) - 2);
    printf("[%s:%d] last_comma - (str + strlen(str) - 1) => %%d=%d\n",
    					__FILE__, __LINE__, last_comma - (str + strlen(str) - 1));
//    printf("[%s:%d] &(str + strlen(str) - 1) => %p\n",
//    						__FILE__, __LINE__, (&str) + strlen(str) - 1));
//    						__FILE__, __LINE__, &str + strlen(str) - 1));
//    						__FILE__, __LINE__, &(str + strlen(str) - 1));



	token = strtok(str, delim);

	printf("[%s:%d] str => %s\n", __FILE__, __LINE__, str);

	printf("[%s:%d] token => %s\n", __FILE__, __LINE__, token);

	while ( token != NULL ) {
	      printf( "%s\n", token );
	      token = strtok( NULL, delim );
//	      token = strtok( NULL, " " );
	}

	return NULL;

}

char* join
(char** tokens, const int numOf_Tokens, char* joint) {
//(char** tokens, const int numOf_Tokens, const char joint) {

	int i, tmp_i;

	int total_chars = 0;

	///////////////////////////////
	//
	// total num of chars
	//
	 ///////////////////////////////
	tmp_i = 0;

//	printf("[%s:%d] strlen(joint) = %d\n", basename(__FILE__, '\\'), __LINE__, strlen(joint));

	for (i = 0; i < numOf_Tokens; ++i) {

		printf("[%s:%d] tokens[i] = %s\n", basename(__FILE__, '\\'), __LINE__, tokens[i]);

//		printf("[%s:%d] *tokens[i] = %s\n", basename(__FILE__, '\\'), __LINE__, *tokens[i]);
//
		tmp_i = strlen(tokens[i]);
//		tmp_i = sizeof(tokens[i]) / sizeof(char);
//
		printf("[%s:%d] tmp_i = %d\n", basename(__FILE__, '\\'), __LINE__, tmp_i);
//
		total_chars += tmp_i;

	}

	printf("[%s:%d] total_chars = %d\n", basename(__FILE__, '\\'), __LINE__, total_chars);
//	printf("[%s:%d] total_chars = %d\n", basename(__FILE__, '\\'), __LINE__, tmp_i);

	///////////////////////////////
	//
	// total length
	//
	 ///////////////////////////////
	int len_String = 0;

	// if joint is blank
	if (strlen(joint) == 0) {	// joint = ""
//	if (joint == ' ') {

		len_String = total_chars + 1;	// total chars + '\0' char

	} else {

		// total chars + '\0' char + joint chars
		len_String = (total_chars + 1) + (numOf_Tokens - 1);

	}

	///////////////////////////////
	//
	// malloc
	//
	 ///////////////////////////////
	char* str_Jointed = malloc(sizeof(char) * len_String);

	///////////////////////////////
	//
	// joint
	//
	 ///////////////////////////////
	char* str_Joint = joint;
//	char str_Joint[2];
//
//	str_Joint[0] = joint;
//	str_Joint[1] = '\0';


	int index = 0;

	// first token
	strcpy(str_Jointed, tokens[0]);

	// 2nd token to the second last token
	if (numOf_Tokens > 1) {

		for (i = 1; i < numOf_Tokens - 1; ++i) {
//		for (i = 1; i < numOf_Tokens; ++i) {

			// joint
//
			strcat(str_Jointed, str_Joint);
//			str_Jointed[strlen(str_Jointed)] = joint;
//			str_Jointed[strlen(str_Jointed) + 1] = '\0';

			strcat(str_Jointed, tokens[i]);

			printf("[%s:%d] str_Jointed = %s (len = %d)\n",
							basename(__FILE__, '\\'),
							__LINE__,
							str_Jointed, strlen(str_Jointed));

//			// joint
//			str_Jointed[strlen(str_Jointed)] = joint;
//			str_Jointed[strlen(str_Jointed) + 1] = '\0';

		}

	}

	// the last token
	if (numOf_Tokens > 2) {

		// joint
		strcat(str_Jointed, str_Joint);
//		str_Jointed[strlen(str_Jointed)] = joint;
//		str_Jointed[strlen(str_Jointed) + 1] = '\0';

		strcat(str_Jointed, tokens[i]);

		printf("[%s:%d] str_Jointed => %s\n", basename(__FILE__, '\\'), __LINE__, str_Jointed);

	}

	///////////////////////////////
	//
	// return
	//
	 ///////////////////////////////
//	return NULL;
	return str_Jointed;

}

int get_MaxVal_In_Array
(int *array, int numOf_Array) {

	int i;

//	printf("[%s:%d] get_MaxVal_In_Array\n", basename(__FILE__, '\\'), __LINE__);

	int tmp = array[0];

	for (i = 0; i < numOf_Array; ++i) {

		if (tmp < array[i]) {

			tmp = array[i];

		};

	}//for (int i = 0; i < numOf_Array; ++i)

	return tmp;


}//int get_MaxVal_In_Array(int *array, int numOf_Array)
