#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fsmipc.c"

typedef struct Leilao{
int idItem; // item (peça a vender )
double price;
int StartDateTime;
int EndDateTime;		
int IdUtilizador; // comprador	
int isOpen; //( 1 - leilao decorrer  0 - fechado )
}leilao;

FILE *infile;
struct Leilao input;

int mutex;

void alterar(int idItem, double preco, int idutilizador);
int procurar(int idItem);

void main (int argc, char* argv[]) // argv[0]=nome do programa ; argv[1] idItem ; argv[2] preco ; argv[3] idutilizador
{
   int _idItem = atoi(argv[1]);
   double preco = atoi(argv[2]);
   int idutilizador = atoi(argv[3]);

   mutex=cria_semaforo(1,1);

   infile = fopen ("fileleiloes.dat","r+b");
   if (infile == NULL)
   {
      fprintf(stderr, "\nError opening accounts.dat\n\n");
      exit (1);
   }
	while (fread (&input, sizeof(struct Leilao), 1, infile)){

        if (input.idItem==_idItem){
		  P(mutex);
		  alterar(_idItem,preco,idutilizador);//argv[1]);
		  V(mutex);
	}}
}

int procura (int idItem){
   int encontra=-1;
   int posicao=0;
 
   infile = fopen ("fileleiloes.dat","r");
   if(infile == NULL)
	   exit(1);
   rewind(infile);
   
   while((!feof(infile))&&(encontra==-1))
   {
      fread(&input, sizeof(struct Leilao), 1, infile);
      if (!feof(infile))
    	{if (idItem == input.idItem){
        	encontra=1;
	}else{posicao++;}
    }
      else{posicao=-1;}
   }
   if (encontra==-1)
      {posicao=-1;}
   fclose(infile);
   return(posicao);
}

void alterar(int idItem, double preco, int idutilizador){
   int pos=-1;
   pos=procura(idItem);
   if (pos==-1)
      {
    printf("\n O item que introduziu nao esta em Leilao");
      }
      if(pos==-2)
         {
       printf("\n O item que introduziu nao esta em Leilao");
         }
       else
       {
          
	  infile = fopen ("fileleiloes.dat","r+b");
          fseek(infile,pos*sizeof(struct Leilao),SEEK_CUR);
          fread(&input, sizeof(struct Leilao), 1, infile);
          	  input.idItem;
		  input.price;
		  input.StartDateTime;
		  input.EndDateTime;
		  input.IdUtilizador;
		  input.isOpen;
          input.price=preco;
          input.IdUtilizador=idutilizador;
          fseek(infile,pos*sizeof(struct Leilao),SEEK_SET);
          if(fwrite(&input, sizeof(struct Leilao),1, infile)!=1)
             {
           printf("\nErro na gravacao...");
             }
	  else
           {
              printf("\nRegravacao feita com sucesso...");
           }
       }
   fclose(infile);
}
