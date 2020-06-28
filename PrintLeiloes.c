#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
//#include "fsmipc.c">
//#include "gera_leiloes.c"

typedef struct Leilao{
int idItem; // item (peça a vender )
double price;
int StartDateTime;
int EndDateTime;		
int IdUtilizador; // comprador	
int isOpen; //( 1 - leilao decorrer  0 - fechado )
}leilao;



void main ()
{
   FILE *infile;
   struct Leilao input;
   do{
   	printf("Atualizacao....\n");
	infile = fopen ("fileleiloes.dat","r");
   	if (infile == NULL)
   	{
      		fprintf(stderr, "\nError opening accounts.dat\n\n");
      		exit (1);
   	}
   	while (fread (&input, sizeof(struct Leilao), 1, infile))
      		printf ("iditem %d; preco  %f; Data  %d %d; utilizador  %d; Open %d\n",
              		input.idItem, input.price, input.StartDateTime, input.EndDateTime, input.IdUtilizador, input.isOpen);
	sleep(5);
   }while(1);
}
