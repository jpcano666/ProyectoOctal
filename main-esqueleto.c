/*
PROYECTO 1 FUNDAMENTOS DE INFRAESTRUCTURA TECNOLOGICA - 201820
Integrante 1 - Codigo integrante 1
Integrante 2 - Codigo integrante 2
Integrante 3 - Codigo integrante 3
*/

#define _CRT_SECURE_NO_DEPRECATE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


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
	//TODO: COMPLETAR EL DESARROLLO DE LA FUNCION.
}

void traductorPos0(int i, int tamanio, unsigned char * c)
{
  if(i < tamanio)
  {
    unsigned char a = *c;
    unsigned char b = (a>>5) + '0';
    unsigned char x = a << 3;
    x = (x>>5) + '0';

    unsigned char y = a <<6;
    y = y>>5;

    c++;
    i++;
    
    if(i == tamanio)
    {
      y = y+'0';
    }
    traductorPos1(y, c, tamanio, i);
  }
}

void traductorPos1(unsigned char y, unsigned char *c, int tamanio, int i)
{
  if(i < tamanio)
  {
    unsigned char a = *c;
    unsigned char b = a >> 7;
    unsigned char d = a << 1;
    d = (d >> 5)+'0';
    unsigned char e = a << 4;
    e = (e>>5)+'0';
    unsigned char f = a << 7;
    f = (f>>5);
    y = (y ^ b) + '0';
    c++;
    i++;
    if(i == tamanio)
    {
      f = f+'0';
    }
    else
    {
      traductorPos2(f, c, tamanio, i);
    }
  }
}

void traductorPos2(unsigned char y, unsigned char *c, int tamanio, int i)
{
  if(i < tamanio)
  {
    unsigned char a = *c;
    unsigned char b = a>>6;
    unsigned char d = a<<2;
    d = (d>>5)+'0';

    unsigned char f = a<<5;
    f = (f>>5)+'0';
    y = (y^b) + '0';
    c++;
    i++;
    traductorPos0(i, tamanio, c);
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