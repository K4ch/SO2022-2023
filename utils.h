extern const int maxUsers;
extern const int maxPromo;
extern const int maxItems;

typedef struct utilizador{
        char nome[20];
        char pwd[20];
        int saldo;
} Utilizador;

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

