
#include <omp.h> // Incluye la cabecera de OpenMP para la programación paralela.
#include <stdio.h> // Incluye la cabecera estándar de entrada/salida para funciones de E/S.
#include <string.h> // Incluye la cabecera para trabajar con cadenas de caracteres.

int main() {
    char cadena[] = "tres tristes tigres tragaban trigo por culpa del bolivar";
    int len = strlen(cadena); 
    char primera_parte[300] = "";
    char segunda_parte[300] = ""; 
    int sw = 1; 

    // Directiva OpenMP que inicia un bucle 'for' paralelo.
    #pragma omp parallel for
    for (int i = 0; i < len; i++) { 
        // Comienza una estructura condicional basada en el valor de 'sw'.
        #pragma omp critical
        {
            if (sw) { 
                if (cadena[i] != ' ') { 
                    // Agrega el carácter a 'primera_parte'.
                    strncat(primera_parte, &cadena[i], 1); 
                } else { 
                    // Agrega un espacio en blanco a 'primera_parte'.
                    sw = 0;
                    strncat(primera_parte, " ", 1);
                }
            } else { 
                if (cadena[i] != ' ') {
                    // Agrega el carácter a 'segunda_parte'.
                    strncat(segunda_parte, &cadena[i], 1); 
                } else { 
                    sw = 1; // Cambia el valor de 'sw' a 1.
                    // Agrega un espacio en blanco a 'segunda_parte'.
                    strncat(segunda_parte, " ", 1); 
                }
            }
        }   
    }
    printf("cadena 1: %s\n", primera_parte); 
    printf("cadena 2: %s\n", segunda_parte); 
    return 0; // Termina la función principal.
}
