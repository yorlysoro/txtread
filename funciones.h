#include <stdio.h>
#include <ctype.h>
#include <signal.h>
#include <stdlib.h>
#define LON 50
void crear(char nomfich[LON]);
void menu(void);
int menu2(void);
void abrir(char nomfich[LON]);
void modificar(char nomfich[LON]);
int borrar_archivo(char nomfich[LON]);
void cerrar();
void nombrearchivomodf(void);

void menu(void)
{
	int opcion;
	char nomarchivo[LON];
	
	puts("\t\tTXTREAD");
	puts("Selecione una opcion:");
	printf("1)Crear un archivo \t\t2)Abrir un archivo\n");
	printf("3)Modificar un archivo \t\t4)Salir\n");
	scanf("%i", &opcion);
	switch(opcion)
	{
		case 1:
		puts("Introduzca el nombre del archivo");
		fgets(nomarchivo,LON-1,stdin);
		crear(nomarchivo);
		break;
		
		case 2:
		puts("Introduzca el nombre del archivo");
		fgets(nomarchivo,LON-1,stdin);
		abrir(nomarchivo);
		break;
		
		case 3:
		nombrearchivomodf();
		break;
		
		case 4:
		puts("Adios!");
		exit(2);
		
		default:
		puts("Error!");
		exit(3);
	}	
		
}
void crear(char nomfich[LON])
{
	FILE * archivo;
	char c;
	int bucle = 1;
	signal(SIGINT, cerrar);
	archivo = fopen(nomfich, "w+");
	if(archivo != NULL)
	{
		puts("Introduzca el contenido del archivo");
		puts("Presione CTRL-C para salir");
		do
		{
			c = getchar();
			fputc(c,archivo);
		
		}while(bucle == 1);
		fclose(archivo);
	}
	else
		puts("Error al crear el archivo");
		
	
}
void cerrar()
{
	signal(SIGINT, SIG_IGN);
	bucle = 0;
	menu();
}
void abrir(char nomfich[LON])
{
	FILE * archivo;
	char c;
	archivo = fopen(nomfich, "r");
	if(archivo != NULL)
	{
		while(feof(archivo) == 0)
		{
			c = fgetc(archivo);
			printf("%c", c);
		}
		puts("\n");
		fclose(archivo);
	}
	else
		puts("Error al leer el archivo");
}

void modificar(char nomfich[LON])
{
	FILE * archivo;
	int bucle;
	int opcion;
	char c;
	opcion = menu2();
	switch(opcion)
	{
		case 1 :
		archivo = fopen(nomfich, "a+");
		signal(SIGINT, cerrar);
		if(archivo != NULL)
		{	
			bucle = 1;
			docase 3:
		menu();
		break;
			{
				c = getchar();
				fputc(c,archivo);
			}while(bucle == 1);
			puts("\nCTRL-C para volver al menu");
			fclose(archivo);
		}
		else
			puts("Error al leer el archivo");
		break;
		case 2:
		archivo = fopen(nomfich, "w+");
		signal(SIGINT, cerrar);
		if(archivo != NULL)
		{	
			bucle = 1;
			do
			{
				c = getchar();
				fputc(c,archivo);
			}while(bucle == 1);
			puts("\nCTRL-C para volver al menu");
			fclose(archivo);
		}
		else
			puts("Error al leer el archivo");
		break;
		case 3:
		menu();
		break;
		default : puts("¡Opcion Invalida¡"); exit(1);
	}
}

int menu2(void)
{
	int opcion;
	puts("Selecione la forma en que va a modificar el archivo");
	puts("1)Sin eliminar su contenido");
	puts("2)Eliminar su contenido");
	puts("3)Volver al menu principal");
	scanf("%i", &opcion);
	return opcion;
}

void nombrearchivomodf(void)
{
	char nomarchivo[LON];
	puts("Introduzca el nombre del archivo");
	fgets(nomarchivo,LON-1,stdin);
	modificar(nomarchivo);
}
