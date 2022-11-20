#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "utils.h"

void main(int argc, char ** argv){
	int pipePromotor[2];
	pipe(pipePromotor);
	int pid = fork();

	if(pid < 0){
		return;
        }else if(pid == 0){
		close(pipePromotor[0]);
		close(STDOUT_FILENO);
		dup(pipePromotor[1]);
		close(pipePromotor[1]);

		execl("./promotor_oficial" , "./promotor_oficial", "NULL");
		perror("Ficheiro não encontrado\n");
	}else{
		char mensagem[200];
		close(pipePromotor[1]);
		while(1){
			read(pipePromotor[0], &mensagem, sizeof(mensagem));
			printf("%s\n", &mensagem);
		}
	}

}
