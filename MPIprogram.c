#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include "AllFunc.h"

int main(int argc, char** argv)
{
	int msglen, m, M, s, T;
	int len, rank;
	int* arr;
	double time = -1, R;
	const char* filename = "binbase";
	char n = '\0';

	//m<размер> -задает стартовый(минимальный) размер сообщения("m0" позволяет измерить латентность)
	//M<размер> -задает конечный(максимальный) размер сообщения
	//s<приращ.> -msglen будет изменяться в арифметической прогрессии с указанным приращением
	//T<число> -тестовая процедура повторяется указанное число раз(для каждого значения msglen), результаты усредняются
	//o<файл> -таблица с результами теста будет выведена в указанный файл(если файл уже существовал, то результаты добавляются в конец файла)


	// инициализация параллельной части приложения
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	//ввод параметров с консоли
	parametrs(argc, argv, &m, &M, &s, &T);
	if (rank == 0) {
		printf("m = %d, M = %d, s = %d, T = %d", m, M, s, T);
		printf("\nSize:\tTransfer:\n");
	}
	
	arr = msglensArray(m, M, s, &len);

	for (int i = 0; i < len; i++) {
		msglen = arr[i];
		messagingFunc(msglen, T, &time);
		if (rank == 0) {
			R = (double)T * msglen * 2 / (time * 1000000);
			printf("%d\t%lf\n", msglen, R);
			PutDatainFile(msglen, R);
		}
	}
	
	MPI_Finalize();
	free(arr);
	
	return 0;
}