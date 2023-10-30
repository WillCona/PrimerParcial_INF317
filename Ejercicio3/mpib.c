#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

int main(int argc, char *argv[]) {
    int rank, size;
    char cadena[]="tres tristes tigres trigaban trigo por culpa del bolivar";
    char *palabra[100];
    int word_count = 0;
    char *palabra1[100];
    char *palabra2[100];
    int contador1 = 0;
    int contador2 = 0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
         // Compartir la cadena con otros procesos
        MPI_Bcast(cadena, sizeof(cadena), MPI_CHAR, 0, MPI_COMM_WORLD);
    } else {
        if (rank == 1){
        // Recibir la cadena compartida proceso 1 
        MPI_Bcast(cadena, sizeof(cadena), MPI_CHAR, 0, MPI_COMM_WORLD);
        }
        if (rank == 2){
        // Recibir la cadena compartida proceso 2
        MPI_Bcast(cadena, sizeof(cadena), MPI_CHAR, 0, MPI_COMM_WORLD);
        }
        if (rank == 3){
        // Recibir la cadena compartida proceso 3
        MPI_Bcast(cadena, sizeof(cadena), MPI_CHAR, 0, MPI_COMM_WORLD);
        }
    }

    // Tokenizar la entrada en palabras
    char *token = strtok(cadena, " \t\n");

    while (token != NULL) {
        palabra[word_count++] = strdup(token);
        token = strtok(NULL, " \t\n");
    }

    // Separar palabras en listas pares e impares
    for (int i = 0; i < word_count; i++) {
        if (i % 2 == 0) {
            palabra1[contador1++] = palabra[i];
        } else {
            palabra2[contador2++] = palabra[i];
        }
    }

    if (rank == 0) {
        printf("Palabras pares: ");
        for (int i = 0; i < contador1; i++) {
            printf("%s ", palabra1[i]);
            free(palabra1[i]);
        }

        printf("\nPalabras impares: ");
        for (int i = 0; i < contador2; i++) {
            printf("%s ", palabra2[i]);
            free(palabra2[i]);
        }

        printf("\n");
    }

    MPI_Finalize();

    return 0;
}
