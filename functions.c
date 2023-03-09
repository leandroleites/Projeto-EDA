#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "functions.h"

void insereMeio(MeioEletrico **listaMeios) {
    MeioEletrico *novoMeio = malloc(sizeof(MeioEletrico));

    // Pedir dados do novo meio ao utilizador
    printf("\n\nID: ");
    scanf("%d", &novoMeio->id);

    // Verificar se o ID já existe na lista
    MeioEletrico *aux;
    for (aux = *listaMeios; aux != NULL; aux = aux->proximo) {
        if (novoMeio->id == aux->id) {
            printf("ERRO: O ID %d ja existe na lista.\n\n\n", novoMeio->id);
            free(novoMeio);
            return;
        }
    }

    printf("\nTipo: ");
    scanf("%s", novoMeio->tipo);

    printf("\nCarga da bateria: ");
    scanf("%d", &novoMeio->carga_bateria);

    printf("\nCusto: ");
    scanf("%f", &novoMeio->custo);

    printf("\nLocalizacao: ");
    scanf("%s", novoMeio->localizacao);

    // Inserir o novo meio no inicio da lista
    novoMeio->proximo = *listaMeios;
    *listaMeios = novoMeio;

    printf("\n\nMeio eletrico inserido com sucesso.\n\n\n");
}

void mostraMeios(MeioEletrico **listaMeios) {
    MeioEletrico *aux;

    if (*listaMeios == NULL) {
        printf("\nNao ha meios eletricos cadastrados.\n");
        return;
    }

    printf("\nMeios eletricos cadastrados:\n");
    for (aux = *listaMeios; aux != NULL; aux = aux->proximo) {
        printf("\n ------------------------------------\n");
        printf("| ID: %d\n", aux->id);
        printf("| Tipo: %s\n", aux->tipo);
        printf("| Carga da bateria: %d\n", aux->carga_bateria);
        printf("| Custo: %.2f\n", aux->custo);
        printf("| Localizacao: %s\n", aux->localizacao);
        printf(" ------------------------------------\n");
     }
     printf("\n\n\n");
}


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

    printf("\n Cliente criado com sucesso! \n \n ");
}

void mostraClientes(Cliente *listaClientes) {
    Cliente *aux;

    if (listaClientes == NULL) {
        printf("\nNao ha clientes cadastrados.\n");
        return;
    }

    printf("\nClientes cadastrados:\n");
    for (aux = listaClientes; aux != NULL; aux = aux->proximo) {
        printf("\n------------------------------------\n");
        printf("| NIF: %s                               \n", aux->nif);
        printf("| Nome: %s                              \n", aux->nome);
        printf("| Morada: %s                            \n", aux->morada);
        printf("| Saldo: %.2f                           \n", aux->saldo);
        printf(" ------------------------------------\n");
    }
    printf("\n\n\n");
}