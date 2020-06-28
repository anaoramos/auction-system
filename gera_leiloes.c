#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Leilao{
int idItem; // item (peça a vender )
double price;
int StartDateTime;
int EndDateTime;		
int IdUtilizador; // comprador	
int isOpen; //( 1 - leilao decorrer  0 - fechado )
}leilao;


FILE *infile;

int procura(int idItem);
struct Leilao input;

int main(){
	int pos;
	infile = fopen("fileleiloes.dat","r+b");
	while (fread(&input,sizeof(struct Leilao),1,infile))
		if (input.StartDateTime < input.EndDateTime){
			pos=procura(input.idItem);
    			if (pos==-1)
	  		{
				printf("\n O item que introduziu nao esta em Leilao");
	
	  		}
	  		else if(pos==-2)
		 	{
				printf("\n O item que introduziu nao esta em Leilao");
		 	}
		 	else{
			infile = fopen ("fileleiloes.dat","r+b");
			fseek(infile,pos*sizeof(struct Leilao),SEEK_CUR);
			fread (&input, sizeof(struct Leilao), 1, infile);
				if (input.StartDateTime < input.EndDateTime)
					input.idItem;
					input.price;
					input.StartDateTime;
					input.EndDateTime;
					input.IdUtilizador;
					input.isOpen;
				input.isOpen=1;
				fseek(infile,pos*sizeof(struct Leilao),SEEK_SET);
				if(fwrite(&input, sizeof(struct Leilao),1, infile)!=1)
								 
					{printf("\nErro na gravacao...");}
			}
		}
}	
			


int procura (int idItem){
   int encontra=-1,posicao=0;
   infile = fopen ("fileleiloes.dat","r");
   rewind(infile);
   while((!feof(infile))&&(encontra==-1))
   {
    fread(&input, sizeof(struct Leilao), 1, infile);
    if (!feof(infile))
    {if (idItem==input.idItem){
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


