#ifndef All
#define All

char* fillWithDatamsglen(int msglen);

void parametrs(int argc, char** argv, int* pm, int* pM, int* ps, int* pN);

void messagingFunc(int msglen, int T, double* ptime);

void printFileLine(int m);

void fillFile();

int printLine(char* st, int len);

int* msglensArray(int m, int M, int s, int* pl);

void printIntArr(int* a, int len);

#endif


