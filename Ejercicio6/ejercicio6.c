#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <gmp.h>

int main(int argc, char** argv) {
    int rank, size;
    mpz_t term, n, x;
    mpz_init(term);  // Inicializa una variable GMP para almacenar el término.
    mpz_init(n);     // Inicializa una variable GMP para n.
    mpz_init(x);     // Inicializa una variable GMP para x.

    MPI_Init(&argc, &argv);  // Inicializa el entorno MPI.

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);  // Obtiene el rango del proceso actual.
    MPI_Comm_size(MPI_COMM_WORLD, &size);  // Obtiene el número total de procesos MPI.

    if (rank == 0) {  // Si el proceso actual tiene rango 0 (proceso maestro).
        mpz_set_ui(n, 1);  // Inicializa n en 1.
        mpz_set_ui(x, 1);  // Inicializa x en 1.
        for (int i = 1; i <= 1000; i++) {  // Bucle de 1 a 10.
            if (i % 2 == 0) {  // Si i es par.
                mpz_mul_ui(term, x, 2);  // Calcula term como el doble de x.
                mpz_add_ui(x, x, 1);    // Incrementa x en 1.
            } else {  // Si i es impar.
                mpz_set_ui(term, (mpz_get_ui(n) * mpz_get_ui(n)) + 1);  // Calcula term como n^2 + 1.
                mpz_add_ui(n, n, 1);  // Incrementa n en 1.
            }
            gmp_printf("Término %d: %Zd\n", i, term);  // Imprime el término calculado.
        }
    } else {  // Para los procesos con rango diferente de 0.
        mpz_set_ui(n, rank);  // Inicializa n con el rango del proceso actual.
        mpz_set_ui(x, rank);  // Inicializa x con el rango del proceso actual.
        for (int i = rank; i <= 1000; i += size - 1) {  // Bucle específico para procesos no maestros.
            if (i % 2 == 0) {  // Si i es par.
                mpz_mul_ui(term, x, 2);  // Calcula term como el doble de x.
                mpz_add_ui(x, x, size - 1);  // Incrementa x en (size - 1).
            } else {  // Si i es impar.
                mpz_set_ui(term, (mpz_get_ui(n) * mpz_get_ui(n)) + 1);  // Calcula term como n^2 + 1.
                mpz_add_ui(n, n, size - 1);  // Incrementa n en (size - 1).
            }
            MPI_Send(&term, sizeof(mpz_t), MPI_BYTE, 0, 0, MPI_COMM_WORLD);  // Envía term al proceso maestro.
        }
    }

    mpz_clear(term);  // Libera la memoria de la variable term.
    mpz_clear(n);     // Libera la memoria de la variable n.
    mpz_clear(x);     // Libera la memoria de la variable x.
    MPI_Finalize();   // Finaliza el entorno MPI.

    return 0;  // Retorna 0 para indicar una ejecución exitosa.
}
