# Importar la clase Pool desde la biblioteca multiprocessing
import multiprocessing
from multiprocessing import Pool
import math

# Definir una función llamada "serie" que toma dos argumentos, "a" y "b"
def serie(a, b):
    resultado1 = (a * a) + 1  
    resultado2 = 2 * b  
    return resultado1, resultado2

if __name__ == '__main__':
    inicio = 1  # Valor de inicio para el rango de valores
    fin = 9999
    rv = fin
    fl = fin%2==0
    fin = fin - 1 if fl else fin # Valor final para el rango de valores
    procesadores = multiprocessing.cpu_count()
    # Crea un grupo de procesos utilizando el número predeterminado de procesadores
    pool = Pool(procesadores)  

    # Ejecuta la función "serie" en paralelo en un rango de valores
    resultados = pool.starmap(serie, [(x, x) for x in range(inicio, (fin//2) + 2)])  
    #print(resultados)
    # Itera a través de los resultados, donde cada resultado es una tupla de dos valores

    
    for i in range(0, len(resultados) - 1):
        print(resultados[i][0], end=" ")
        print(resultados[i][1], end=" ")
    if(rv % 2 == 1):
        print(resultados[-1][0], end=" ")
    else:
        print(resultados[-1][0], end=" ")
        print(resultados[-1][1], end=" ")
    