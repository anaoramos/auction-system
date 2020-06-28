// Por omissão, assume MacOSX.
// Para Linux tem de definir LINUX; basta descomentar a linha abaixo


// Descomentar a linha seguinte para usar em Linux
#define LINUX YES

// Descomentar a linha seguinte para criar semáforos com opção SEM_UNDO
//#define UNDO


#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <errno.h>

int cria_semaforo(key_t,int);
int remove_semaforo(int);
int P(int);
int V(int);



