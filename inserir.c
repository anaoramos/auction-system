#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include "fsmipc.c"

typedef struct Leilao{
int idItem; // item (peça a vender )
double price;
int StartDateTime;
int EndDateTime;		
int IdUtilizador; // comprador	
int isOpen; //( 1 - leilao decorrer  0 - fechado )
}leilao;

FILE *fileleiloes;
FILE *file;

void inserirleilao(int idItem, int price, int StartDateTime, int EndDateTime,int IdUtilizador, int isOpen);


int mutex;


void main (){
int i, idItem, price, StartDateTime, EndDateTime, IdUtilizador, isOpen;

mutex = cria_semaforo(1,1);
printf("Prima 1 para Inserir Leilao;\n");
scanf("%d",&i);
if(i==1){
	printf("IdItem: ");
   	scanf("%i", &idItem);
   	printf("Preço: ");
   	scanf("%i", &price);
   	printf("Data de inicio: ");
   	scanf("%i", &StartDateTime);
   	printf("Data de Fim: ");
   	scanf("%i", &EndDateTime);
   	printf("id utilizador: ");
   	scanf("%i", &IdUtilizador);
	P(mutex);
	inserirleilao(idItem, price, 
			StartDateTime, EndDateTime, IdUtilizador, isOpen=0);
	V(mutex);
}else{
	printf("Argumentos Inválidos\n");
}}

void inserirleilao(int idItem, int price, int StartDateTime, int EndDateTime, int IdUtilizador, int isOpen){
leilao l;
file=fopen("fileleiloes.dat","a");

l.idItem=idItem;
l.price=price;
l.StartDateTime=StartDateTime;
l.EndDateTime=EndDateTime;
l.IdUtilizador=IdUtilizador;
l.isOpen=isOpen;

fwrite(&l,sizeof(struct Leilao),1, file);

fclose(file);

}	
