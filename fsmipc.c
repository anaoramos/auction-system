
/******************************************************************
   Esta implementação (ainda) usa semáforos Unix Sys V.
   Já devia usar Posix... 


   O Unix permite 32 semáforos asociados à mesma chave. No entanto, para
   facilitar a utilização, aqui há uma coorespondência 1:1
   cada chave só cria um semáforo

   A primitiva de criação chama-se cria_semaforo

   int s;
   s = cria_semaforo (chave, valor_inicial);

   No entanto, só o primeiro processo cria e inicializa o semáforo. Os seguintes
   apenas se associam ao semáforo já criado. Isto torna o código mais legível
   pois não temos de saber se o semáforo já foi criado ou não. Todos tentamos
   criá-lo, se já existir apenas ficamos a saber o número associado a essa chave,
   Mas obviamente não se reinicializa o semáforo.

   Para usar, basta invocar os P() ou V() passando como argumento o semáforo
   ou seja, o resultado do cria_semaforo()

   No fim, o último apaga os semáforos; ou deixa isso para um script de limpeza,
   com o comando ipcrm


**********************************************************************/



#include "fsmipc.h"

//#ifndef LINUX
extern int errno;
//#endif



/*
 ************ semaforos  ***********
 */


 


#define ERRO (-1)

#ifdef UNDO
//struct  sembuf _P_semaforo = {0,-1,SEM_UNDO};
//struct  sembuf _V_semaforo = {0,1,SEM_UNDO};
#else
struct  sembuf _P_semaforo = {0,-1,0};
struct  sembuf _V_semaforo = {0,1,0};
#endif

#ifdef LINUX
union semun {
         int              val;    /* Value for SETVAL */
         struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
         unsigned short  *array;  /* Array for GETALL, SETALL */
         struct seminfo  *__buf;  /* Buffer for IPC_INFO
                                           (Linux-specific) */
};
#endif



int cria_semaforo(key_t chave, int inicial)
{
        int     id;
	union semun	valor;
        if ((id = semget((key_t) chave, 1, IPC_CREAT|IPC_EXCL|0666)) == ERRO)
                if ((id = semget((key_t) chave,1,0666)) == ERRO){
                        perror("Erro no get_semaforo");
                        return(ERRO);
                } else
                        return(id);

        else {
                /* inicializa o semaforo */
		valor.val = inicial;
                if (semctl(id,0,SETVAL,valor) == ERRO) {
                        perror("Erro no cria_semaforo");
                        return(ERRO);
                } else
                        return(id);
        }
}
                
int P(int id)
{
        int     temp;
        if ((temp = semop(id,&_P_semaforo,1)) == ERRO) {
                printf("Erro no P(%d) errno=%d\n",id, errno);
		perror("P");
                return(ERRO);
        } else
                return(temp);
}
                

int V(int id)
{
        int     temp;
        if ((temp = semop(id,&_V_semaforo,1)) == ERRO) {
                printf("Erro no V(%d) errno=%d\n",id, errno);
		perror("V");
                return(ERRO);
        } else
                return(temp);
}


int remove_semaforo(int id)
{
	int error;
	if ((error = semctl(id,0,IPC_RMID,0)) == ERRO) {
		perror("Erro no remove_semaforo");
	}        
	return(error);
}
