/*
PROYECTO 1 FUNDAMENTOS DE INFRAESTRUCTURA TECNOLOGICA - 201820
Juan Pablo Cano - 201712395 - jp.cano@uniandes.edu.co
Christer Omar Osorio - 
*/

#define _CRT_SECURE_NO_DEPRECATE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void traductorPos0 (int, unsigned char *,int, unsigned char *);
void traductorPos1 (int, unsigned char*,unsigned char, int, unsigned char *);
void traductorPos2 (unsigned char*,unsigned char, unsigned char *, int , int);

//-- Definicion de la estructura para los datos del archivo de entrada y el de salida
typedef struct datos
{
	int tamanio;
	unsigned char *informacion;
} Datos;


//-- Prototipos de las funciones
int readFile(Datos * archivo, char *);
void writeFile(Datos * archivoEnOctal, char *);
void convertirAOctal(Datos * archivo, Datos * archivoEnOctal);


//-- Funciones

// Esta funcion se encarga de abrir un datos y leerlo en el vector informacion.
// Retorna el numero de bytes leidos.
// No hay que completar nada en esta funcion.
int readFile(Datos * archivo, char * nombreArchivo)
{
	FILE *file;
	int n;

	file = fopen(nombreArchivo, "rb");

	if (!file)
	{
		printf("No se pudo abrir el archivo para leer: %s\n", nombreArchivo);
        system("PAUSE");
		exit(EXIT_FAILURE);
	}
	fseek(file, 0, SEEK_END);
	n = ftell(file);
	fseek(file, 0, SEEK_SET);

	archivo->tamanio = n;
	archivo->informacion = (unsigned char *)calloc(n, sizeof(unsigned char));

	fread(archivo->informacion, sizeof(unsigned char), n, file);

	fclose(file);

	return n;
}


// Esta funcion se encarga de escribir un datos a partir del vector datos.
// El numero de bytes que se deben escribir viene en el parametro n.
// No hay que completar nada en esta funcion.
void writeFile(Datos * archivoEnOctal, char *nombreArchivo)
{
	FILE *file;

	file = fopen(nombreArchivo, "wb");

	if (!file) {
		printf("No se pudo abrir el archivo para escribir: %s\n", nombreArchivo);
        system("PAUSE");
		exit(EXIT_FAILURE);
	}

	fwrite(archivoEnOctal->informacion, sizeof(char), archivoEnOctal->tamanio, file);

	fclose(file);
}


// Esta funcion se encarga de convertir a octal cada uno de los bytes que se
//encuentran en la estructura datosBin->informacion y asignar los nuevos valores a la estructura datosOct->informacion.
// Deben desarrollar esta funcion en su totalidad.
void convertirAOctal(Datos * datosBin, Datos * datosOct)
{
	traductorPos0(0, datosOct->informacion, datosBin->tamanio, datosBin->informacion);
}

/**
 * Esta funcion convierte el byte ,cuya posicion en su caracter modulo 3 es 0, si no hay nada despues del primer Byte, traduce los ultimos dos bits junto con un '0'
 * que se añade para completar el octal. Si hay otro byte despues, guarda estos dos bits sobrantes para leerlos junto con los bits del byte siguiente. La traduccion la hace
 * tomando los primero tres bits y haciendo un corrimiento de cinco bits a la derecha para tenerlos aislados al final del byte y traducirlos, despues se hace un
 * corrimiento de 3 bits a la izquierda para eliminar los bits que ya fueron traducidos y nuevamente se hace un corrimiento de 5 bits a la derecha para traducir
 * los tres bits que sigue, finalmente, se hace un corrimiento de 6 bits a la izquierda para eliminar los primeros dos octales traducidos, y finalmente se corre 5 bits
 * a la derecha para tener estos dos ultimos bits y un '0' adicional para traduccion.
 * pre: los datos ingresados no pueden ser nulos ni tampoco el caracter que contiene la traduccion.
 * @param i Posición del caracter de entrada cuyo modulo con 3 sea cero, por ejemplo, si entra la cadena "abcd" i seria la posición de 'a' y de 'd'.
 * @param datosOctal caracter que apunta a la primera posicion de los datos traducidos a octal
 * @param tamanioTotal tamaño total del archivo.
 * @param datosBin caracter que apunta a la primera posicion de los datos a trducir.
 **/
void traductorPos0(int i, unsigned char * datosOctal, int tamanioTotal, unsigned char *datosBin)
{
  if (i < tamanioTotal)
    {
      unsigned char a = *datosBin;
      unsigned char b = (a >> 5) + '0';
      unsigned char x = a << 3;
      x = (x >> 5) + '0';
      unsigned char y = a << 6;
      y = y >> 5;
			datosOctal[i] = b;
			datosOctal[i+1] = x;

      datosBin++;
      i++;
      if(i==tamanioTotal)
      {
          y = y+'0';
					datosOctal[i] = y;
      }
      traductorPos1 (i, datosOctal , y , tamanioTotal, datosBin);
    }
}

/**
 * Esta función convierte el byte a octal, cuya posicion en su caracter modulo 3 es 1, haciendo corrimientos, primero se hace un corrimiento de 7 bits a la derecha para tener el primer bit, despues 
 * a este bit se le opera con "XOR" con los dos bits que traemos de la función anterior para tener los tres bits juntos. despues corremos un bit a la izquierda para no tener en 
 * cuenta el bit que ya tradujimos, y lo que queda le hacemos un corrimiento de 5 bits a la derecha para traducir nuestro octal, hacemos los mismo con los siguientes tres bits,
 * por lo que al final tendremos un bit que correremos 7 bits a la izquierda, luego 5 bits a la derecha, si no hay otro byte despues de este, se traduce este octal, de lo
 * contrario, se lee en el siguiente byte.
 * @param i Posición del caracter de entrada cuyo modulo con tres es uno, por ejemplo, si entra la cadena "abcdef" i seria la posición de 'b' y de 'e'.
 * @param y Son los dos bits que vienen del anterior método.
 * @param datosOctal caracter que apunta a la primera posicion de los datos traducidos a octal
 * @param datosBin caracter que apunta a la primera posicion de los datos a trducir.
 * @param tamanioTotal tamaño total del archivo.
 **/
void traductorPos1 ( int i, unsigned char *datosOctal,unsigned char y, int tamanioTotal, unsigned char *datosBin)
{
  if (i < tamanioTotal)
    {
      char a = *datosBin;
      char b = a >> 7;
      unsigned char c = a << 1;
      c = (c >> 5) +'0';
      unsigned char d = a << 4;
      d = (d >> 5)+'0';
      unsigned char e = a << 7;
      e = (e >> 5);
      y = (y ^ b) + '0';
			datosOctal[i]=y;
			datosOctal[i+1] = c;
			datosOctal[i+2] = d;
      datosBin++;
      i++;
      if(i==tamanioTotal)
      {
          e = e+'0';
					datosOctal[i] = e;
      }
      traductorPos2(datosOctal,e, datosBin, tamanioTotal, i);
    }
}

/**
 * En este método se busca traducri el byte cuya posicion en su caracter modulo 3 es 2, haciendo corrimientos. Primero corremos el byte 6 bits ala derecha y le aplicamos la función
 * "XOR" con el bit que traemos del metodo anterior para poder traducir nuestro octal. Despues, hacemos un corrimiento de dos bits para deshacernos de los dos bits que ya 
 * tradujimos y corremos 5 a la derecha, traducimos este octal y pasamos a los siguiente tres bits, corremos 5 bits a la izquierda y luego a la derecha, se traduce este octal.
 * Finalmente, se devuelve al primer método a verificar si a se terminó la cadena de caracteres, si se acabó, se devuelve la cadena traducida en datosOctal, si no, se repite todo
 * el procedimiento hasta que se termine todo.
 * @param i Posición del caracter de entrada cuyo modulo con tres es dos, por ejemplo, si entra la cadena "abcdef" i seria la posición de 'c' y de 'f'.
 * @param y Es un bit que viene del anterior método.
 * @param datosOctal caracter que apunta a la primera posicion de los datos traducidos a octal
 * @param datosBin caracter que apunta a la primera posicion de los datos a trducir.
 * @param tamanioTotal tamaño total del archivo.
 **/
void traductorPos2(unsigned char *datosOctal,unsigned char y, unsigned char *datosBin, int tamanioTotal, int i)
{
  if (i < tamanioTotal)
    {
      unsigned char a = *datosBin;
      unsigned char b = a >> 6;
      unsigned char c = a << 2;
      c = (c >> 5) +'0';
      unsigned char d = a << 5;
      d = (d >> 5)+'0';
      y = (y ^ b) + '0';
			datosOctal[i] = y;
			datosOctal[i+1] = c;
			datosOctal[i+2] = d;

      datosBin++;
      i++;
      traductorPos0(i, datosOctal, tamanioTotal, datosBin);
    }
}

//-- Funcion main de la aplicacion
// No hay que completar nada en esta funcion.
int main()
{
	// Mensaje inicial
	printf("PROYECTO 1 - INFRATEC (ISIS-1304)");

	// Declaracion de todas las variables necesarias.
	int tamanio;
	int tamanioRepOctales;
	char nombreArchivo[200];
	char nombreArchivoOctales[200];
	Datos * archivo = (Datos *)malloc(sizeof(Datos));
	Datos * archivoEnOctal = (Datos *)malloc(sizeof(Datos));

	printf("\n\nIngrese el nombre del archivo a leer (incluya el formato. i.e. archivo.txt): \n");
	scanf("%s", nombreArchivo);
	tamanio = readFile(archivo, nombreArchivo);
	printf("\nEl tamanio del archivo es de %d bytes\n", tamanio);
	tamanioRepOctales = ((tamanio * 8) / 3) + ((tamanio % 3 == 0)? 0 : 1);
	archivoEnOctal->informacion = (unsigned char *)calloc(tamanioRepOctales, sizeof(unsigned char));
	archivoEnOctal->tamanio = tamanioRepOctales;
	printf("\nIngrese el nombre del archivo para guardar la representacion en octales del archivo origen (incluya el .txt): \n");
	scanf("%s", nombreArchivoOctales);
	convertirAOctal(archivo, archivoEnOctal);
	writeFile(archivoEnOctal, nombreArchivoOctales);
	printf("\nEl archivo se transformo en su representacion a octal exitosamente!\n\n");
	printf("Revisa el archivo con nombre '%s' para ver el resultado!\n", nombreArchivoOctales);

	// Terminar
	system("PAUSE");
	return 0;
}