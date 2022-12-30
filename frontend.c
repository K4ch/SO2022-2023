#include "libs.h"

int servFd, cliToServFd, servToCliFd;

int pid;

char nameClientFifo[50];

void shutdown(){
    close(servFd);
    close(cliToServFd);
    close(servToCliFd);
    unlink(nameClientFifo);
    exit(EXIT_FAILURE);
}

bool checkPointerNull(char *ptr){
	if(ptr == NULL){
		printf("Comando inválido\n");
		return true;
	}
	return false;
}

void menuComandos(){
    bool end = false;

    char input[100];

    int initSize = strlen(input);
    char delim[] = " ";
    while(!end){
        fgets(input, 100, stdin);
        char *ptr = strtok(input, delim);
        if(strcmp(ptr, "sell")==0){
            ptr = strtok(NULL, delim);
            if(checkPointerNull(ptr)){
                continue;
            }
            char nomeI[20];
            strcpy(nomeI, ptr);
            printf("%s\n", &nomeI);

            ptr = strtok(NULL, delim);
            if(checkPointerNull(ptr)){
                continue;
            }
            char nomeCat[20];
            strcpy(nomeCat, ptr);
            printf("%s\n", &nomeCat);

            ptr = strtok(NULL, delim);
            if(checkPointerNull(ptr)){
                continue;
            }
            int precoB;
            if(atoi(ptr) == 0){
                printf("Preço base introduzido inválido, por favor introduza um número\n");
                continue;
            }
            printf("%d\n", precoB);

            ptr = strtok(NULL, delim);
            if(checkPointerNull(ptr)){
                continue;
            }
            int precoC = atoi(ptr);
            if(atoi(ptr) == 0){
                printf("Preço de compra imediata introduzido inválido, por favor introduza um número\n");
                continue;
            }
            printf("%d\n", precoC);

            ptr = strtok(NULL, delim);
            if(checkPointerNull(ptr)){
                continue;
            }
            int duracao = atoi(ptr);
            if(atoi(ptr) == 0){
                printf("Duração introduzida inválido, por favor introduza um número\n");
                continue;
            }
            printf("%d\n", duracao);

            ptr = strtok(NULL, delim);
            if(ptr != NULL){
                printf("Argumentos a mais para o comando \"sell\"\n");
                continue;
            }
            printf("Comando \"sell\" recebido\n", &nomeI, &nomeCat, precoB, precoC, duracao);
        }else if(strcmp(ptr, "list\n")==0){
            printf("Dentro list\n");
            ptr = strtok(NULL, delim);
            if(ptr != NULL){
                printf("Argumentos a mais para o comando \"list\"\n");
                continue;
            }
            printf("Comando \"list\" recebido\n");
        }else if(strcmp(ptr, "licat")==0){
            ptr = strtok(NULL, delim);
            if(checkPointerNull(ptr)){
                continue;
            }
            char nomeCat[20];
            strcpy(nomeCat, ptr);

            ptr = strtok(NULL, delim);
            if(ptr != NULL){
                printf("Argumentos a mais para o comando \"licat\"\n");
                continue;
            }
            printf("Comando \"licat\" recebido\n");
        }else if(strcmp(ptr, "lisel")==0){
            ptr = strtok(NULL, delim);
            if(checkPointerNull(ptr)){
                continue;
            }
            char nomeVen[20];
            strcpy(nomeVen, ptr);

            ptr = strtok(NULL, delim);
            if(ptr != NULL){
                printf("Argumentos a mais no comando \"lisel\"\n");
                continue;
            }
            printf("Comando \"lisel\" recebido\n");
        }else if(strcmp(ptr, "lival")==0){
            ptr = strtok(NULL, delim);
            if(checkPointerNull(ptr)){
                continue;
            }
            if(atoi(ptr)==0){
                printf("Comando inválido\n");
                continue;
            }
            int precoM = atoi(ptr);

            ptr = strtok(NULL, delim);
            if(ptr != NULL){
                printf("Argumentos a mais no comando \"lival\"\n");
            }
            printf("Comando \"lival\" recebido\n");
        }else if(strcmp(ptr, "litime")==0){
            ptr = strtok(NULL, delim);
            if(checkPointerNull(ptr)){
                continue;
            }
            if(atoi(ptr)==0){
                printf("Comando inválido\n");
                continue;
            }
            int duracao = atoi(ptr);

            ptr = strtok(NULL, delim);
            if(ptr != NULL){
                printf("Argumentos a mais no comando \"litime\"\n");
            }
            printf("Comando \"litime\" recebido\n");
        }else if(strcmp(ptr, "time\n")==0){
            if(ptr != NULL){
                printf("Argumentos a mais no comando \"time\"\n");
            }
            printf("Comando \"time\" recebido\n");
        }else if(strcmp(ptr, "buy")==0){
            ptr = strtok(NULL, delim);
            if(checkPointerNull(ptr)){
                continue;
            }
            if(atoi(ptr)==0){
                printf("Comando inválido\n");
                continue;
            }
            int id = atoi(ptr);

            ptr = strtok(NULL, delim);
            if(checkPointerNull(ptr)){
                continue;
            }
            if(atoi(ptr)==0){
                printf("Comando inválido\n");
                continue;
            }
            int valor = atoi(ptr);

            ptr = strtok(NULL, delim);
            if(ptr != NULL){
                printf("Argumentos a mais no comando \"buy\"\n");
            }
            printf("Comando \"buy\" recebido\n");

        }else if(strcmp(ptr, "cash\n")==0){
            if(!checkPointerNull(ptr)){
                printf("Arguementos a mais no comando \"cash\"\n");
            }
            printf("Comando \"cash\" recebido\n");
        }else if(strcmp(ptr, "add")==0){
            ptr = strtok(NULL, delim);
            if(checkPointerNull(ptr)){
                continue;
            }
            if(atoi(ptr)==0){
                printf("Comando inválido\n");
                continue;
            }
            int valor = atoi(ptr);

            ptr = strtok(NULL, delim);
            if(ptr != NULL){
                printf("Argumentos a mais no comando \"add\"\n");
            }
            printf("Comando \"add\" recebido\n");
        }else if(strcmp(ptr, "exit")==0){
            if(!checkPointerNull(ptr)){
                printf("Argumentos a mais no comando \"exit\n");
            }
            printf("Comando \"exit\" recebido\n");
            end = true;
        }else{
            printf("Comando inválido\n");
        }
        printf("\n\n");
    }
}

int main(int argc, char ** argv){
	if(argc != 3){
		printf("Por favor inicie o programa como: ./frontend <username> <password>\n");
		return -1;
	}

    pid = getpid();

    servFd = open(SERVER_FIFO, O_WRONLY);

    if(servFd == -1){
        fprintf(stderr, "\nO servidor não se encontra a correr\nA desligar...\n");
        exit(EXIT_FAILURE);
    }

    cliToServFd = open(CLIENT_TO_SERVER, O_WRONLY);

    sprintf(nameClientFifo, SERVER_TO_CLIENT, O_WRONLY);

    if(mkfifo(nameClientFifo, 0777) == -1){
        fprintf(stderr, "Erro ao criar FIFO do cliente %d!\n", pid);
        exit(EXIT_FAILURE);
    }

	Utilizador user;
	strcpy(user.nome, argv[1]);
	strcpy(user.pwd, argv[2]);

    Mensagem msg;
    msg.user = user;
    msg.pid = pid;
    strcpy(msg.fifoName, nameClientFifo);

    servToCliFd = open(nameClientFifo, O_RDWR);

    if(servToCliFd == -1){
        fprintf(stderr, "Erro ao abrir FIFO do client\n");
        shutdown();
    }

    if(write(c))

    menuComandos();

}

