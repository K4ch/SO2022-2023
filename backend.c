#include "libs.h"

int serv_fd, cli_to_serv_fd, serv_to_cli_fd;
char *fUsers, *fPromoters, *fItems;
int Pid;

int highestItemId = 1;
Item *listaItems;
size_t listaItems_size = 0;
int listaItems_length = 0;
size_t listaUsers_size = 0;

const int MAXUSERS = 20, MAXPROMOTERS = 10, MAXITEMS = 30;

void shutdown(){
    fprintf(stderr, "\nA desligar...\n");
    close(serv_fd);
    close(serv_to_cli_fd);
    close(cli_to_serv_fd);
    unlink(SERVER_FIFO);
    unlink(CLIENT_TO_SERVER);
    exit(EXIT_FAILURE);
}

void sighand(int s){
    if(s == SIGINT){
        shutdown();
    }
}

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

void *ClientHandlerThread(void *arg){
    Mensagem msg = *(Mensagem *) arg;

    int pidCliente = msg.pid;
    char nameClientFifo[50];
    strcpy(nameClientFifo, msg.fifoName);

    int valid = isUserValid(msg.user.nome, msg.user.pwd);
    if(valid == -1){
        fprintf(stderr, "Erro a verificiar a validade do utilizador, a fechar thread de utilizador pid: %d, nome do fifo: %s, nome do user %s\n", pidCliente, nameClientFifo, msg.user.nome);
        //TODO: Matar cliente com sinal
        return NULL;
    }else if(valid == 0){
        fprintf(stderr, "O utilizador pid: %d, nome do fifo: %s, nome do user %s, não possui credenciais válidas, a fechar thread e utilizador\n", pidCliente, nameClientFifo, msg.user.nome);
        //TODO: Matar cliente com sinal
        return NULL;
    }

    char delim[] = " ";
    while(1){
        //TODO: ficar á espera de mensagens do utilizador e corresponder com a informação necessária
        if(read(cli_to_serv_fd, &msg, sizeof(msg)) == -1){
            fprintf(stderr, "Erro a ler mensagem do cliente\nA delisgar...\n");
            shutdown();
        }

        char *ptr = strtok(msg.cmd, delim);
        if(strcpy(ptr, "sell") == 0){
            Resposta rsp;
            Item tmp;
            tmp.id = ++highestItemId;
            ptr = strtok(NULL, delim);
            strcpy(tmp.nome, ptr);
            ptr = strtok(NULL, delim);
            strcpy(tmp.cat, ptr);
            ptr = strtok(NULL, delim);
            tmp.valorA  = atoi(ptr);
            ptr = strtok(NULL, delim);
            tmp.valorC  = atoi(ptr);
            ptr = strtok(NULL, delim);
            tmp.duracao = atoi(ptr);
            strcpy(tmp.nomeV, msg.user.nome);
            strcpy(tmp.nomeL, "-");
            listaItems = (Item*) realloc(listaItems, listaItems_size * sizeof(Item));
            listaItems_size += sizeof(Item);
            listaItems_length++;
            *(listaItems + listaItems_length-1) = tmp;

            rsp.wasExecuted = true;
            sprintf(rsp.resp, "%d", tmp.id);
            if(write(serv_to_cli_fd, &rsp, sizeof(rsp)) == -1){
                fprintf(stderr, "Erro a enviar mensagem ao cliente\nA delisgar...\n");
                shutdown();
            }
        }else if(strcpy(ptr, "list") == 0){
            Resposta rsp;
            rsp.wasExecuted = true;
            rsp.listaItems = (Item*) malloc(listaItems_size);
            *rsp.listaItems = *listaItems;
            if(write(serv_to_cli_fd, &rsp, sizeof(rsp)) == -1){
                fprintf(stderr, "Erro a enviar mensagem ao cliente\nA delisgar...\n");
                shutdown();
            }
        }else if(strcpy(ptr, "licat") == 0){
            Resposta rsp;
            char categoria[20];
            ptr = strtok(NULL, delim);
            strcpy(categoria, ptr);
            for(int i = 0; i < listaItems_length; i++){
                if(strcmp(categoria, (listaItems+i)->cat)==0){
                    if(rsp.listaItems == NULL){
                        rsp.listaItems = (Item*) malloc(sizeof(Item));
                        *(rsp.listaItems + rsp.listaItems_length) = *(listaItems+i);
                        rsp.listaItems_length++;
                    }else{
                        rsp.listaItems = (Item*) realloc(rsp.listaItems, rsp.listaItems_length * sizeof(Item));
                        *(rsp.listaItems + rsp.listaItems_length) = *(listaItems+i);
                        rsp.listaItems_length++;
                    }
                }
            }
            if(rsp.listaItems == NULL){
                rsp.wasExecuted = false;
            }else{
                rsp.wasExecuted = true;
            }
            if(write(serv_to_cli_fd, &rsp, sizeof(rsp)) == -1){
                fprintf(stderr, "Erro a enviar mensagem ao cliente\nA delisgar...\n");
                shutdown();
            }
        }else if(strcpy(ptr, "lisel") == 0){
            Resposta rsp;
            Item *tmp;
            int counter = 0;
            ptr = strtok(NULL, delim);
            char nomeV[20];
            strcpy(nomeV, ptr);
            //TODO:procurar pelo vendedor, adicionar á rsp e mandar
            for(int i = 0; i < listaItems_length; i++){
                if(strcmp((listaItems + i)->nomeV, nomeV) == 0){
                    if(tmp == NULL){
                        tmp = (Item*) malloc(sizeof(Item));
                    }else{
                        tmp = (Item*) realloc(tmp, counter * sizeof(Item));
                    }

                }
            }

        }else if(strcpy(ptr, "lival") == 0){
            Resposta rsp;
            //TODO:procurar pelo preco, adicionar á rsp e mandar


        }else if(strcpy(ptr, "litime") == 0){
            Resposta rsp;
            //TODO:procurar pelo tempo, adicionar á rsp e mandar


        }else if(strcpy(ptr, "cash") == 0){
            Resposta rsp;
            int saldo = getUserBalance(msg.user.nome);
            if(saldo == -1){
                rsp.wasExecuted = false;
            }else{
                rsp.wasExecuted = true;
                sprintf(rsp.resp, "%d", saldo);
            }
            if(write(serv_to_cli_fd, &rsp, sizeof(rsp)) == -1){
                fprintf(stderr, "Erro a enviar mensagem ao cliente\nA delisgar...\n");
                shutdown();
            }
        }else if(strcpy(ptr, "add") == 0){
            Resposta rsp;
            ptr = strtok(NULL, delim);
            int qnt = atoi(ptr);
            int res = updateUserBalance(msg.user.nome, qnt);
            if(res == -1){
                rsp.wasExecuted = false;
            }else{
                rsp.wasExecuted = true;
            }
            if(write(serv_to_cli_fd, &rsp, sizeof(rsp)) == -1){
                fprintf(stderr, "Erro a enviar mensagem ao cliente\nA delisgar...\n");
                shutdown();
            }
        }
    }
}

void main(int argc, char ** argv){

    //VERIFICAR SE ALGUM BACKEND ESTÁ A CORRER
    if(access(SERVER_FIFO, F_OK) == 0){
        fprintf(stderr, "\nJá se encontra um backend a correr!\nA desligar...\n");
        exit(EXIT_FAILURE);
    }

    //FICHEIRO DE USERS
    fUsers = getenv("FUSERS");
    if(fUsers == NULL){
        fprintf(stderr, "\nNão existe variável de ambiente com o path para o ficheiro de utilizadores\nA desligar...\n");
        exit(EXIT_FAILURE);
    }else{
        listaUsers_size = sizeof(Utilizador) * loadUsersFile(fUsers);
    }

    //FICHEIRO DE PROMOTORES
    fPromoters = getenv("FPROMOTERS");
    if(fPromoters == NULL){
        fprintf(stderr, "\nNão existe variável de ambiente com o path para o ficheiro de promotores\nA desligar...\n");
        exit(EXIT_FAILURE);
    }else{
        //TODO: Ler o ficheiro de promotores
    }

    //FICHEIRO DE ITEMS
    fItems = getenv("FITEMS");
    if(fItems == NULL){
        fprintf(stderr, "\nNão existe variável de ambiente com o path para o ficheiro de items\nNão vai ser carregado nenhum item\n");
    }else{
        fprintf(stderr, "\nFoi encontrado um ficheiro, procedendo á sua leitura...\n");
        FILE *file = fopen(fItems, "r");
        char* fullItem = NULL;
        size_t len = 0;
        char delim[] = " ";
        int counter = 0;

        if(file == NULL){
            printf("Erro a abrir ficheiro\n");
        }

        while(getline(&fullItem, &len, file) != -1){
            if(listaItems == NULL){
                printf("\nLista Items é null, a criar espaço para o primeiro membro\n");
                listaItems = (Item*) malloc(sizeof(Item));
                listaItems_size += sizeof(Item);
                listaItems_length++;
            }else{
                printf("\nLista Items não é null, a criar espaço para o próximo membro\n");
                listaItems = (Item*) realloc(listaItems, (listaItems_length)+1 * sizeof(Item));
                listaItems_size += sizeof(Item);
                listaItems_length++;
            }

            Item tmp;
            char* ptr = strtok(fullItem, delim);
            tmp.id = atoi(ptr);
            ptr = strtok(NULL, delim);
            strcpy(tmp.nome, ptr);
            ptr = strtok(NULL, delim);
            strcpy(tmp.cat, ptr);
            ptr = strtok(NULL, delim);
            tmp.valorA = atoi(ptr);
            ptr = strtok(NULL, delim);
            tmp.valorC = atoi(ptr);
            ptr = strtok(NULL, delim);
            tmp.duracao = atoi(ptr);
            ptr = strtok(NULL, delim);
            strcpy(tmp.nomeV, ptr);
            ptr = strtok(NULL, delim);
            strcpy(tmp.nomeL, ptr);

            *(listaItems + counter) = tmp;

            printItem(*(listaItems+counter));
            counter++;
        }
        fclose(file);
        for(int i = 0; i < listaItems_length; i++){
            if(i == 0){
                highestItemId = (listaItems + i)->id;
            }
            if(highestItemId < (listaItems + i)->id){
                highestItemId = (listaItems + i)->id;
            }
        }
    }

    Pid = getpid();

    system("clear");
    printf("\n******************************\n");
    printf("*****Bem-vindo ao Backend*****\n");
    printf("******************************\n");


    //CRIA FIFO DE SERVIDOR
    if(mkfifo(SERVER_FIFO, 0777) == -1){
        fprintf(stderr, "\nErro ao criar o FIFO do servidor\n");
        shutdown();
    }

    //ABRE FIFO DE SERVIDOR
    serv_fd = open(SERVER_FIFO, O_RDWR);
    if(serv_fd == -1){
        fprintf(stderr, "\nErro ao abrir FIFO do servidor\n");
        shutdown();
    }

    //CRIA FIFO DE CLIENTE PARA SERVIDOR
    if(mkfifo(CLIENT_TO_SERVER, 0777) == -1){
        fprintf(stderr, "\nErro ao criar o FIFO do cliente para o servidor\n");
        shutdown();
    }

    //ABRE FIFO DE CLIENTE PARA SERVIDOR
    cli_to_serv_fd = open(CLIENT_TO_SERVER, O_RDWR);
    if(cli_to_serv_fd == -1){
        fprintf(stderr, "\nErro ao abrir o FIFO do cliente para o servidor\n");
        shutdown();
    }

    pthread_t ClientHandler;
    Mensagem msg;

    while(1){
        if(read(cli_to_serv_fd, &msg, sizeof(msg)) == -1){
            fprintf(stderr, "Erro a ler mensagem do utilizador\nA desligar...\n");
            shutdown();
        }else{
            pthread_create( &ClientHandler, NULL, ClientHandlerThread, &msg);
        }
    }


    executaComandos();

	/*while(!endMenu){
        	printf("\nEscolha a próxima operação:\n1- Comandos\n2- Promotor\n3- Users\n4- Itens\n5- Terminar\n\n");
        	scanf("%d", &option);
        	switch(option){
      			case 1: executaComandos();break;

            		case 2: executaPromotor();break;

            		case 3: {
					TOD
					}
				}break;

            		case 4: {
					FILE *file = fopen("items.txt", "r");
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
    }*/
}
