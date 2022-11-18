#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utils.h"

void main(int argc, char ** argv){
	if(argc != 3){
		printf("Por favor inicie o programa como: ./frontend <username> <password>\n");
		return;
	}

	Utilizador user;
	strcpy(user.nome, argv[1]);
	strcpy(user.pwd, argv[2]);

	printf("%s, %s\n", user.nome, user.pwd);

	bool end = false;

	char input[100];

	int initSize = strlen(input);
	char delim[] = " ";
	while(!end){
		fgets(input, 100, stdin);
		char *ptr = strtok(input, delim);
		if(strcpy(ptr, "sell"){
			ptr = strtok(NULL, delim);
			char nomeI[20];
			strcpy(nomeI, ptr);

			ptr = strtok(NULL, delim);
			char nomeCat[20];
			strcpy(nomeCat, ptr);

			ptr = strtok(NULL, delim);
			int precoB;
			if(atoi(ptr) == 0){
				printf("Preço base introduzido inválido, por favor introduza um número\n");
				continue;
			}

			ptr = strtok(NULL, delim);
			int precoC = atoi(ptr);
			if(atoi(ptr) == 0){
				printf("Preço de compra imediata introduzido inválido, por favor introduza um número\n");
				continue;
			}

			ptr = strtok(NULL, delim);
			int duracao = atoi(ptr);
			if(atoi(ptr) == 0){
				printf("Duração introduzida inválido, por favor introduza um número\n");
				continue;
			}

			ptr = strtok(NULL, delim);
			if(ptr != NULL){
				printf("Argumentos a mais para o comando \"sell\"\n");
				continue;
			}
			printf("Comando \"sell %s %s %d %d %d\"\n", &nomeI, %nomeCat, precoB, precoC, duracao);
		}else if(strcpy(ptr, "list"){
			ptr = strtok(NULL, delim);
			if(ptr != NULL){
				printf("Argumentos a mais para o comando \"list\"\n");
				continue;
			}
			printf("Comando \"list\" recebido\n");
		}else if(strcpy(ptr, "licat"){
			ptr = strtok(NULL, delim);
			char nomeCat[20];
			strcpy(nomeCat, ptr);
			ptr = strtok(NULL, delim);
			if(ptr != NULL){
				printf("Argumentos a mais para o comando \"licat\"\n");
				continue;
			}
			printf("Comando \"licat\" recebido\n");
		}else if(strcpy(ptr, "lisel"){

		}else if(strcpy(ptr, "lival"){

		}else if(strcpy(ptr, "litime"){

		}else if(strcpy(ptr, "time"){

		}else if(strcpy(ptr, "buy"){

		}else if(strcpy(ptr, "cash"){

		}else if(strcpy(ptr, "add"){

		}else if(strcpy(ptr, "exit"){

		}
	}
}
