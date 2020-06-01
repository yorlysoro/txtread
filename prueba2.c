#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
 
int num_pulsaciones = 0;  /* Contador de pulsaciones de  CTRL-C */
int bucle = 1;            /* Controlador de salida del bucle de espera */
void terminar_bucle ();   /* Captura la señal de alarma SIGALRM */
void contar ();           /* Captura la señal de interrupción SIGINT */
 
int main (void) {
    /* Asociamos la señal SIGINT a la función cortar(). La señal SIGINT la recibe el programa cuando
       se pulsa CONTROL+C. */
    signal (SIGINT, contar);
 
    /* Asocia la señal SIGALRM a la función terminar_bucle(). Cuando el programa reciba la señal alarma
       se ejecutará la función terminar_bucle. */
    signal (SIGALRM, terminar_bucle);
 
    printf ("Pulsa varias veces CTRL-C durante 15 segundos.\n");
 
    /* Programamos una alarma para dentro de 15 segundos.
       Cuando pasen 15 segundos este programa
       recibirá una señal SIGALRM. */
    alarm(15);
 
    /* Entramos en un bucle infinito del que solo saldremos 
       cuando la variable bucle cambie su valor. Esto sucederá
       cuando se ejecute la función terminar_bucle(). */
    while (bucle==1);
 
    /* Desactivamos la señal SIGINT porque ya no vamos a contar
       más veces cuando el usuario pulse CTRL+C. */
    signal (SIGINT, SIG_IGN);
 
    printf ("Has pulsado CTRL+C %d veces.\n", num_pulsaciones);
 
    return 0;
    }
 
/* Esta función se ejecutará cuando el proceso reciba la señal SIGALRM al de 15 segundos. */
void terminar_bucle () {
      // Vamos a desactivar la alarma SIGALRM. SIG_IGN hace que se ignore la señal SIGALRM.
      signal (SIGALRM, SIG_IGN);
 
      // Queremos que el bucle infinito que había en la función main se termine. Como hacemos bucle=1
      // el bucle ya no cumple la condición bucle==1 y se termina.
      bucle=0;
      printf ("¡Alarma!\n");
}
 
/* Esta función se ejecuta cada vez que se pulsa CTRL+C (señal SIGINT).
   Cuando se termine esta función el programa seguirá en el punto que se había quedado. */
void contar ()
{
    /* Primero desactivamos la señal SIGINT por si se pulsa CTRL+C 
       mientras se está ejecutando esta función. */
    signal (SIGINT, SIG_IGN);
    printf ("Has pulsado CTRL-C\n");
    num_pulsaciones++;
    // Volvemos a asociar SIGINT con la función cortar() para la próxima vez que el usuario pulse CTRL+C.
    signal (SIGINT, contar);
}
