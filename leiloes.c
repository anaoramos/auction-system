#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>

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

void inserirleilao(int idItem,double price,int StartDateTime,int EndDateTime, int IdUtilizador,int isOpen);

void main (){
int i, idItem, price, StartDateTime, EndDateTime, IdUtilizador, isOpen;

printf("Inicio simulador\n");
for (i=1; i<11; i++){
	idItem=i++;
	price=i;
	StartDateTime=i;
	EndDateTime=i+5;
	IdUtilizador=i;
	isOpen=0;
		inserirleilao(idItem,price,StartDateTime,EndDateTime,IdUtilizador,isOpen=0);
printf("Simulador finalizado");
	
}}

void inserirleilao(int idItem, double price, int StartDateTime, int EndDateTime, int IdUtilizador, int isOpen){
leilao l;
file=fopen("fileleiloes.dat","ab");

l.idItem=idItem;
l.price=price;
l.StartDateTime=StartDateTime;
l.EndDateTime=EndDateTime;
l.IdUtilizador=IdUtilizador;
l.isOpen=isOpen;

fwrite(&l,sizeof(leilao),1, file);
fclose(file);

}

