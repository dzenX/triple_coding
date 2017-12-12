#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

char *block_read()
{
	const size_t block_size = 25; 

	char *result, *block, *temp;  
	size_t size = block_size; 
	size_t n = 0; 

	result = block = (char*)malloc(size); 

	if (!result)
		return NULL;

	*result = '\0';
	
	for (;;) {
		if (fgets(block, block_size, stdin) == NULL)
			break;

		n += strlen(block);

		if (*(result + n - 1) == '\n')
			break;

		/*if (result[n - 1] == '\n')
			break;*/

		size += block_size;
		temp = (char*)realloc(result, size);

		if (temp == NULL)
			break;

		result = temp;
		block = result + n;
	}

	if (*result == '\0') {
		free(result);
		result = NULL;
	}

	return result;
}

void make_stable(char* s1, const char* s2) {
	while (*s2 != '\n') {
		*s1++ = *s2;
		*s1++ = *s2;
		*s1++ = *s2++;
	}
	*s1++ = '\n';
	*s1 = '\0';
}

void make_mist(char* res, const char* src) {
	srand(time(NULL));
	int n = rand() % (strlen(src) - 2);
	int i = 0;
	while (*src) {
		if (i++ != n)
			*res++ = *src++;
		else
			src++;
	}
	*res = '\0';
}

void fix_mist(char* fixed, const char* with_mist) {

	if ((strlen(with_mist) - 1) % 3 == 0) {
		strcpy(fixed, with_mist);
		return;
	}
		
	int k = 0;
	char c = *with_mist;
	while (*with_mist) {
		if (*with_mist == c) {
			*fixed++ = *with_mist++;
			k++;
		}
		else
			if (k % 3 != 0) {
				*fixed++ = c;
				c = *with_mist;
				*fixed++ = *with_mist++;
				k = 1;
			}
			else {
				c = *with_mist;
				*fixed++ = *with_mist++;
				k = 1;
			}
	}
	*fixed = '\0';
}

int main(int argc, char* argv[]) {
	printf("Enter str: ");
	char* str = block_read();
	char* str_s = (char*)malloc(strlen(str)*3-1);
	char* str_m = (char*)malloc(strlen(str_s) - 1);
	char* str_f = (char*)malloc(strlen(str_s));

	make_stable(str_s, str);
	make_mist(str_m, str_s);
	fix_mist(str_f, str_m);

	printf("Initial str: %s", str);
	printf("Tripled str: %s", str_s);
	printf("Str with mistake: %s", str_m);
	printf("Fixed str: %s", str_f);

	free(str);
	free(str_s);
	free(str_m);
	free(str_f);

	return 0;
}