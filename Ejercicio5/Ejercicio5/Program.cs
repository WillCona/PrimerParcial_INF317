// See https://aka.ms/new-console-template for more information
using System.Collections;  // Importa el espacio de nombres System.Collections para utilizar ArrayList.
using System;              // Importa el espacio de nombres System para clases básicas.
using System.Threading;    // Importa el espacio de nombres System.Threading para trabajar con subprocesos.

class Program
{
    static ArrayList lista = new ArrayList();  // Declara una lista ArrayList llamada 'lista' como una variable estática.

    static void Serie(object state)  // Define un método llamado 'Serie' que acepta un objeto 'state' como argumento.
    {
        var values = (Tuple<long, long>)state;  // Convierte 'state' en una tupla de dos valores long.
        long a = values.Item1;  // Obtiene el primer valor de la tupla.
        long b = values.Item2;  // Obtiene el segundo valor de la tupla.

        long resultado1 = (a * a) + 1;  // Calcula el resultado1 como a^2 + 1.
        long resultado2 = 2 * a;        // Calcula el resultado2 como 2 * b.
        lista.Add(resultado1);
        lista.Add(resultado2);

    }
        

    static void Main()  // Define el método principal 'Main'.
    {   int aux = 0;
        int inicio = 1;     // Define una variable 'inicio' con el valor 1.
        int fin = 5;     // Define una variable 'fin'.

        aux = fin;
        if(fin%2 == 0)
        {
            fin -= 1;
        }

        for (int i = inicio; i < (fin/2)+2; i++)  // Un bucle que va desde 'inicio' hasta 'fin menos 1'.
        {
            long x = i;  // Asigna el valor de 'i' a la variable 'x'.
            long y = i;  // Asigna el valor de 'i' a la variable 'y'.

            ThreadPool.QueueUserWorkItem(Serie, new Tuple<long, long>(i, y));  // Agrega un trabajo en el ThreadPool para ejecutar el método 'Serie' con los argumentos 'x' y 'y'.
            Thread.Sleep(1);  // Pausa el hilo actual durante 1 milisegundo.
        }
        int tamano = aux % 2 == 0 ? lista.Count : lista.Count - 1;
        for (int i = 0; i < tamano; i++)
        {
            Console.WriteLine(lista[i]);
        }
        Console.ReadKey();  // Espera a que el usuario presione una tecla antes de finalizar la ejecución.
    }
}

