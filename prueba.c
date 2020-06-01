#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#define LON 50
void crear(char nomfich[LON]);
/*void tiempo_espera();*/
int main(void)
{		
	int opcion[LON];
	char nomarchivo[LON];
	scaf("%i", &opcion);
	if(opcion == 1)
	{
		puts("Introduzca el nombre del archivo");
		fgets(nomarchivo,LON-1,stdin);
		crear(nomarchivo);
	}
	return 0;
}

void crear(char nomfich[LON])
{
	printf("%s", nomfich);
}
