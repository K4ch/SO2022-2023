#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "utils.h"
#include "users_lib.h"

bool checkPointerNull(char *ptr){
        if(ptr == NULL){
                printf("Argumentos a mais\n");
                return true;
        }
        return false;
}

void executaComandos(){
    	char input[100];
	bool end = false;
	int initSize = strlen(input);
        char delim[] = " ";

       	while(!end){
                fgets(input, 100, stdin);
                char *ptr = strtok(input, delim);
		if(strcmp(ptr, "users\n")==0){
			printf("Comando \"users\" recebido\n");
		}else if(strcmp(ptr, "list\n")==0){
                        printf("Comando \"list\" recebido\n");
		}else if(strcmp(ptr, "kick")==0){
                        ptr = strtok(NULL, delim);
                        if(checkPointerNull(ptr)){
                                continue;
                        }
			char username[20];
			strcpy(username, ptr);
                        printf("Comando \"kick\" recebido\n");
                }else if(strcmp(ptr, "prom\n")==0){
                        printf("Comando \"prom\" recebido\n");
                }else if(strcmp(ptr, "reprom\n")==0){
                        printf("Comando \"reprom\" recebido\n");
                }else if(strcmp(ptr, "cancel")==0){
                        ptr = strtok(NULL, delim);
                        if(checkPointerNull(ptr)){
                                continue;
                        }
                        char nomeExec[20];
                        strcpy(nomeExec, ptr);
                        printf("Comando \"cancel\" recebido\n");
                }else if(strcmp(ptr, "close\n")==0){
                        printf("Comando \"reprom\" recebido\n");
                }else{
			printf("Comando inválido\n");
		}
		printf("\n\n");
	}

	return;
}

void executaPromotor(){
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
                read(pipePromotor[0], &mensagem, sizeof(mensagem));
                printf("%s\n", &mensagem);
		return;
        }
}

void printItem(Item a){
	printf("%d, %s, %s, %d, %d, %d, %s, %s\n\n", a.id, a.nome, a.cat, a.valorA, a.valorC, a.duracao, a.nomeV, a.nomeL);
	return;
}

void printUserSaldo(Utilizador a){
	printf("Saldo do utilizador [%s] é %d\n\n", a.nome, a.saldo);
	return;
}

void main(int argc, char ** argv){

	int nUsers;
	int option;
	bool endMenu = false;
	char* fUsers = getenv("USERS_FILE");
	char* fPromos = getenv("PROMOS_FILE");
	char* fItems = getenv("ITEMS_FILE");

	nUsers = loadUsersFile("/home/fabio/SOBay/FUSERS.txt");
	if(nUsers == -1){
		printf("Erro a carregar os utilizadores\n");
	}

	Utilizador dummy1;
	strcpy(dummy1.nome, "Dummy1");
	strcpy(dummy1.pwd, "1234");
	dummy1.saldo = 100;

	Utilizador dummy2;
	strcpy(dummy2.nome, "Dummy2");
	strcpy(dummy2.pwd, "4321");
	dummy2.saldo = 200;

	Utilizador users[2];
	users[0] = dummy1;
	users[1] = dummy2;

	Item items[3];
	Item item1, item2, item3;
	items[0] = item1;
	items[1] = item2;
	items[2] = item3;

	while(!endMenu){
        	printf("\nEscolha a próxima operação:\n1- Comandos\n2- Promotor\n3- Users\n4- Itens\n5- Terminar\n\n");
        	scanf("%d", &option);
        	switch(option){
      			case 1: executaComandos();break;

            		case 2: executaPromotor();break;

            		case 3: {
					if(saveUsersFile("FUSERS.txt")==-1){
						printf("Erro a guardar users\n");
					}
					for(int i = 0; i < 2; i++){
						users[i].saldo -= 1;
						printUserSaldo(users[i]);
					}
				}break;

            		case 4: {
					FILE *file = fopen("FITEMS.txt", "r");
					char* fullItem = NULL;
					size_t len = 0;
					char delim[] = " ";
					int counter = 0;
					if(file == NULL){
						printf("Erro a abrir ficheiro\n");
					}
					while(getline(&fullItem, &len, file) != -1){
						char* ptr = strtok(fullItem, delim);
						items[counter].id = atoi(ptr);
						ptr = strtok(NULL, delim);
						strcpy(items[counter].nome, ptr);
                                                ptr = strtok(NULL, delim);
                                                strcpy(items[counter].cat, ptr);
						ptr = strtok(NULL, delim);
                                                items[counter].valorA = atoi(ptr);
                                                ptr = strtok(NULL, delim);
                                                items[counter].valorC = atoi(ptr);
                                                ptr = strtok(NULL, delim);
                                                items[counter].duracao = atoi(ptr);
                                                ptr = strtok(NULL, delim);
                                                strcpy(items[counter].nomeV, ptr);
                                                ptr = strtok(NULL, delim);
                                                strcpy(items[counter].nomeL, ptr);

						printItem(items[counter]);
						counter++;
					}
					fclose(file);
				}break;

            		case 5: endMenu = true;break;
        }
    }
}
