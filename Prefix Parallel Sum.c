#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char *argv[]){
	MPI_Init(&argc, &argv);
	int my_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	int my_world;
	MPI_Comm_size(MPI_COMM_WORLD, &my_world);
	
	int sumTotal;
	int total;

	const int n = 256;
	int a[n];
	int b[n];

	if (my_rank ==0){
		for(int i =0; i<n; i++){
			a[i] = i+1;
		}
	}	
	
	MPI_Scatter(a, n/my_world, MPI_INT, b, n/my_world, MPI_INT,0, MPI_COMM_WORLD);

	for(int i =0; i<n/my_world; i++){
		sumTotal += b[i];
	}
	
	MPI_Scan(&sumTotal, &total,1, MPI_INT,MPI_SUM,MPI_COMM_WORLD);
	printf("[MPI process %d] Total = %d.\n", my_rank,total);

	MPI_Finalize();
}
