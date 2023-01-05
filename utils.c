#include "libs.h"

const int maxUsers = 20;
const int maxPromo = 10;
const int maxItems = 30;

void printItem(Item a){
    printf("ID: %d NOME: %s CATEGORIA: %s LICITACAO: %d COMPRA: %d DURACAO: %d NOME VEND: %s NOME LIC: %s\n\n", a.id, a.nome, a.cat, a.valorA, a.valorC, a.duracao, a.nomeV, a.nomeL);
}
