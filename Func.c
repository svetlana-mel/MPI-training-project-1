#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "AllFunc.h"

// console input processing function

void parametrs(int argc, char** argv, int* pm, int* pM, int* ps, int* pT) {
	int k = 1, num;
	char c, key;
	char* str;
	//-default values------
	*pm = 2;			 //
	*pM = 5949;			 //
	*ps = 512;			 //
	*pT = 20;			 //
	//-------------------//
	for (int i = 1; i < argc; i++) {
		str = malloc(sizeof(char) * 20);
		c = argv[i][0];
		key = c;
		c = argv[i][k];
		while (c != '\n' && c != '\0') {
			str[k - 1] = c;
			k++;
			c = argv[i][k];
		}
		str[k - 1] = '\0';
		num = atoi(str);
		k =	1;
		if (key == 'm') {
			*pm = num;
		}
		if (key == 'M') {
			*pM = num;
		}
		if (key == 's') {
			*ps = num;
		}
		if (key == 'T') {
			*pT = num;
		}
		free(str);
	}
}

//function for preparing a binary file with 2048 characters

void fillFile() {
	FILE* f;
	const char* filename = "binbase";
	char c = '\0';
	char* buffer;
	buffer = "The MPI interface is meant to provide essential virtual topology, synchronization, and communication functionality between a set of processes (that have been mapped to nodes/servers/computer instances) in a language-independent way, with language-specific syntax (bindings), plus a few language-specific features. MPI programs always work with processes, but programmers commonly refer to the processes as processors. Typically, for maximum performance, each CPU (or core in a multi-core machine) will be assigned just a single process. This assignment happens at runtime through the agent that starts the MPI program, normally called mpirun or mpiexec.  MPI library functions include, but are not limited to, point-to-point rendezvous-type send/receive operations, choosing between a Cartesian or graph-like logical process topology, exchanging data between process pairs (send/receive operations), combining partial results of computations (gather and reduce operations), synchronizing nodes (barrier operation) as well as obtaining network-related information such as the number of processes in the computing session, current processor identity that a process is mapped to, neighboring processes accessible in a logical topology, and so on. Point-to-point operations come in synchronous, asynchronous, buffered, and ready forms, to allow both relatively stronger and weaker semantics for the synchronization aspects of a rendezvous-send. Many outstanding[clarification needed] operations are possible in asynchronous mode, in most implementations.  MPI-1 and MPI-2 both enable implementations that overlap communication and computation, but practice and theory differ. MPI also specifies thread safe interfaces, which have cohesion and coupling strategies that help avoid hidden state within the interface. It is relatively easy to write multithreaded point-to-point MPI code, and some implementations support such code. Multithreaded collective communication is best accomplished with multiple copies of Communicators, as described below.MPI is a communication protocol for programming parallel computers. Both point-to-point and collective communication are supported. MPI is a message - passing application programmer interface, together with protocoland semantic specifications for how its features must behave in any implementation.[3] MPIs goals are high performance, scalability, and portability. MPI remains the dominant model used in high-performance computing today.[4]  MPI is not sanctioned by any major standards body; nevertheless, it has become a de facto standard for communication among processes that model a parallel program running on a distributed memory system. Actual distributed memory supercomputers such as computer clusters often run such programs.  The principal MPI-1 model has no shared memory concept, and MPI-2 has only a limited distributed shared memory concept. Nonetheless, MPI programs are regularly run on shared memory computers, and both MPICH and Open MPI can use shared memory for message transfer if it is available.[5][6] Designing programs around the MPI model (contrary to explicit shared memory models) has advantages over NUMA architectures since MPI encourages memory locality. Explicit shared memory programming was introduced in MPI-3.[7][8][9]  Although MPI belongs in layers 5 and higher of the OSI Reference Model, implementations may cover most layers, with sockets and Transmission Control Protocol (TCP) used in the transport layer.  Most MPI implementations consist of a specific set of routines directly callable from C, C++, Fortran (i.e., an API) and any language able to interface with such libraries, including C#, Java or Python. The advantages of MPI over older message passing libraries are portability (because MPI has been implemented for almost every distributed memory architecture) and speed (because each implementation is in principle optimized for the hardware on which it runs).  MPI uses Language Independent Specifications (LIS) for calls and language bindings. The first MPI standard specified ANSI C and Fortran-77 bindings together with the LIS. The draft was presented at Supercomputing 1994 (November 1994)[10] and finalized soon thereafter. About 128 functions constitute the MPI-1.3 standard which was released as the final end of the MPI-1 series in 2008.[11]  At present, the standard has several versions: version 1.3 (commonly abbreviated MPI-1), which emphasizes message passing and has a static runtime environment, MPI-2.2 (MPI-2), which includes new features such as parallel I/O, dynamic process management and remote memory operations,[12] and MPI-3.1 (MPI-3), which includes extensions to the collective operations with non-blocking versions and extensions to the one-sided operations.[13] MPI-2's LIS specifies over 500 functions and provides language bindings for ISO C, ISO C++, and Fortran 90. Object interoperability was also added to allow easier mixed-language message passing programming. A side-effect of standardizing MPI-2, completed in 1996, was clarifying the MPI-1 standard, creating the MPI-1.2.  MPI-2 is mostly a superset of MPI-1, although some functions have been deprecated. MPI-1.3 programs still work under MPI implementations compliant with the MPI-2 standard.  MPI-3 includes new Fortran 2008 bindings, while it removes deprecated C++ bindings as well as many deprecated routines and MPI objects.  MPI is often compared with Parallel Virtual Machine (PVM), which is a popular distributed environment and message passing system developed in 1989, and which was one of the systems that motivated the need for standard parallel message passing. Threaded shared memory programming models (such as Pthreads and OpenMP) and message passing programming (MPI/PVM) can be considered as complementary programming approaches, and can occasionally be seen together in applications, e.g. in servers with multiple large shared-memory nodes.";

	fopen_s(&f, "binbase", "wb");
	if (!f) { exit(3); }
	fwrite(buffer, sizeof(char), 2048, f);
	fwrite(&c, sizeof(char), 1, f);
	fclose(f);
}

// function of forming an array of message lengths 
// increasing in arithmetic progression with the given parameters
// parameters are set by console input or default values are taken

int* msglensArray(int m, int M, int s, int* pl) {
	int* arr;
	int length = 0, bb;
	bb = M;
	while (bb >= m) {
		length++;
		bb -= s;
	}
	if (bb + s != 0) {
		length++;
	}
	*pl = length;
	arr = (int*)malloc(sizeof(int) * length);
	for (int i = 0; i < length; i++) {
		if (i == length - 1) {
			arr[i] = M;
		}
		else {
			arr[i] = m + i * s;
		}
	}
	return arr;
}

void printIntArr(int* a, int len) {
	for (int i = 0; i < len; i++) {
		printf("%d ", a[i]);
	}
}