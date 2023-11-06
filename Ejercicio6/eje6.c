#include <stdio.h>
#include <mpi.h>

void Serie(int n, int vector[]) {
    int contador = 0;
    for (int i = 1; i <= n; i++) {
        vector[contador++] = i * i + 1; // Calcula i^2 + 1
        if (contador >= n)
            break;
        vector[contador++] = 2 * i; // Calcula 2 * i
    }
}

int main(int argc, char *argv[]) {
    int n = 10000; // Tamaño de la secuencia
    int vector[n]; // Arreglo para almacenar los resultados

    MPI_Init(&argc, &argv); // Inicializa MPI

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtiene el rango del proceso actual
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtiene el número total de procesos

    int nroElemntos = n / size; // Cuántos elementos le corresponden a cada proceso
    int inicio = rank * nroElemntos; // Dónde comienza a almacenar sus elementos

    Serie(n, vector); // Llama a la función para calcular la secuencia

    int vectorResultado[n]; // Arreglo para almacenar resultados recopilados

    MPI_Gather(vector + inicio, nroElemntos, MPI_INT, vectorResultado, nroElemntos, MPI_INT, 0, MPI_COMM_WORLD);
    // Recopila datos calculados por todos los procesos en el proceso raíz (con rango 0)

    if (rank == 0) { // Proceso raíz
        for (int i = 0; i < n; i++) {
            printf("%d\n", vectorResultado[i]); // Imprime los resultados recopilados
        }
    }

    MPI_Finalize(); // Finaliza MPI y libera recursos

    return 0;
}
