#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "functions.h"


void insereCliente(Cliente **listaClientes) {
    Cliente *novoCliente = (Cliente*) malloc(sizeof(Cliente));

    printf("Insira o NIF do cliente: ");
    scanf("%s", novoCliente->nif);
    printf("Insira o nome do cliente: ");
    scanf("%s", novoCliente->nome);
    printf("Insira a morada do cliente: ");
    scanf("%s", novoCliente->morada);
    printf("Insira o saldo do cliente: ");
    scanf("%f", &novoCliente->saldo);

    novoCliente->proximo = *listaClientes;
    *listaClientes = novoCliente;
}

void mostraClientes(Cliente *listaClientes) {
    Cliente *aux;

    if (listaClientes == NULL) {
        printf("Nao ha clientes cadastrados.\n");
        return;
    }

    printf("Clientes cadastrados:\n");
    for (aux = listaClientes; aux != NULL; aux = aux->proximo) {
        printf("NIF: %s\n", aux->nif);
        printf("Nome: %s\n", aux->nome);
        printf("Morada: %s\n", aux->morada);
        printf("Saldo: %.2f\n\n", aux->saldo);
    }
}