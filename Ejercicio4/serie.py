# Importar la clase Pool desde la biblioteca multiprocessing
import multiprocessing
from multiprocessing import Pool

# Definir una función llamada "serie" que toma dos argumentos, "a" y "b"
def serie(a, b):
    resultado1 = (a * a) + 1  
    resultado2 = 2 * b  
    return resultado1, resultado2

if __name__ == '__main__':
    inicio = 1  # Valor de inicio para el rango de valores
    fin = 10000  # Valor final para el rango de valores
    procesadores = multiprocessing.cpu_count()
    # Crea un grupo de procesos utilizando el número predeterminado de procesadores
    pool = Pool()  

    # Ejecuta la función "serie" en paralelo en un rango de valores
    resultados = pool.starmap(serie, [(x, x) for x in range(inicio, fin + 1)])  

    # Itera a través de los resultados, donde cada resultado es una tupla de dos valores
    for x, y in resultados:
        print(x)
        print(y) 
