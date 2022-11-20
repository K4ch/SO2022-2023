
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utils.h"
#include "users_lib.h"

bool checkPointerNull(char *ptr){
        if(ptr == NULL){
                printf("Argumentos a mais\n");
                return true;
        }
        return false;
}


void main(int argc, char ** argv){

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
}
