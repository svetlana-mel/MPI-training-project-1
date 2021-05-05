#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "AllFunc.h"

// the function returns a pointer to a string of a certain length filled with data
// dynamic memory is in use and needs to be freed

char* fillWithDatamsglen(int msglen) {
	FILE* f;
	const char* filename = "binbase";
	char* str;
	if (msglen != 0) {
		fopen_s(&f, filename, "rb");
		if (!f) { exit(2); }
		str = (char*)malloc(sizeof(char) * msglen);
		fread(str, sizeof(char), msglen, f);

		fclose(f);
	}
	else {
		str = "\0";
	}
	return str;
}

void printFileLine(int m) {
	char* str3;
	str3 = fillWithDatamsglen(m);
	if (str3 == NULL) { printf("Emty string\n"); }
	else {
		str3[m - 1] = '\0';
		printf("string:\n%s", str3);
	}
	free(str3);
}

int printLine(char* st, int len) {
	char ch;
	ch = st[len - 1];
	if (len == 0) { printf("Emty string\n"); return 0; }
	else {
		st[len - 1] = '\0';
		printf("%s%c\n", st, ch);
		st[len - 1] = ch;
	}
	return 1;
}

// function of writing data to a file
// Size, Transfer

void PutDatainFile(int msglen, double R) {
	FILE* f;
	char* str;
	char p = ' ';
	char n = '\n';
	
	fopen_s(&f, "dataMPI.txt", "a+");
	if (!f) { printf("Open file error from PutDatainFile function\n"); exit(2); }
	fprintf(f, "%d", msglen);
	fprintf(f, "%c", p);
	fprintf(f, "%lf", R);
	fprintf(f, "%c", n);
	
	fclose(f);
}