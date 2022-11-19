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
		printf("Antes fgets\n");
		fgets(input, 100, stdin);
		printf("Depois fgets\n");
		char *ptr = strtok(input, delim);
		printf("%s\n", ptr);
		if(strcmp(ptr, "sell")==0){
			printf("Depois compare a sell\n");
			ptr = strtok(NULL, delim);
			char nomeI[20];
			strcpy(nomeI, ptr);

			ptr = strtok(NULL, delim);
			char nomeCat[20];
			strcpy(nomeCat, ptr);

			ptr = strtok(NULL, delim);
			int precoB;
			if(atoi(ptr) == 0 && strcmp(ptr, NULL) == 0){
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
			printf("Comando \"sell %s %s %d %d %d\"\n", &nomeI, &nomeCat, precoB, precoC, duracao);
		}else if(strcmp(ptr, "list")==0){
			ptr = strtok(NULL, delim);
			if(ptr != NULL){
				printf("Argumentos a mais para o comando \"list\"\n");
				continue;
			}
			printf("Comando \"list\" recebido\n");
		}else if(strcmp(ptr, "licat")==0){
			ptr = strtok(NULL, delim);
			char nomeCat[20];
			strcpy(nomeCat, ptr);
			ptr = strtok(NULL, delim);
			if(ptr != NULL){
				printf("Argumentos a mais para o comando \"licat\"\n");
				continue;
			}
			printf("Comando \"licat\" recebido\n");
		}else if(strcmp(ptr, "lisel")==0){

		}else if(strcmp(ptr, "lival")==0){

		}else if(strcmp(ptr, "litime")==0){

		}else if(strcmp(ptr, "time")==0){

		}else if(strcmp(ptr, "buy")==0){

		}else if(strcmp(ptr, "cash")==0){

		}else if(strcmp(ptr, "add")==0){

		}else if(strcmp(ptr, "exit")==0){

		}
	}
}
