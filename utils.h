extern const int maxUsers;
extern const int maxPromo;
extern const int maxItems;

typedef struct item{
    int id;
    char nome[20];
    char cat[20];
    int valorA;
    int valorC;
    int duracao;
    char nomeV[20];
    char nomeL[20];
} Item;

typedef struct utilizador{
        char nome[20];
        char pwd[20];
        int saldo;
} Utilizador;

typedef struct mensagemToServ{
    Utilizador user;
    int pid;
    char fifoName[50];
    char cmd[20];
} Mensagem;

typedef struct respostaFromServ{
    bool wasExecuted;
    char resp[50];
    Item *listaItems;
} Reposta;


