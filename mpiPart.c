#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include "AllFunc.h"


void messagingFunc(int msglen, int T, double* ptime) {
	double time_start, time_stop;
	MPI_Status status1, status2;
	int rank;
	char* strout;
	char* str = fillWithDatamsglen(msglen);
	if (msglen != 0) {
		strout = malloc(sizeof(char) * msglen);
	}
	else { strout = '\0'; }
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if (rank == 0) {
		time_start = MPI_Wtime();

		for (int i = 0; i <= T; i++) {
			MPI_Send(str, msglen, MPI_CHAR, rank + 1, 5, MPI_COMM_WORLD);
			MPI_Recv(str, msglen, MPI_CHAR, rank + 1, 6, MPI_COMM_WORLD, &status1);
			
		}

		time_stop = MPI_Wtime();
		*ptime = (time_stop - time_start);
	}
	if (rank == 1) {

		for (int i = 0; i <= T; i++) {
			MPI_Recv(strout, msglen, MPI_CHAR, rank - 1, 5, MPI_COMM_WORLD, &status2);
			MPI_Send(strout, msglen, MPI_CHAR, rank - 1, 6, MPI_COMM_WORLD);
		}
	}
	free(str);
	free(strout);
}
