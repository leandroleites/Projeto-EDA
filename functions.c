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
    printf("Insira o email: ");
    scanf("%s", novoCliente->email);
    printf("Insire a password: ");
    scanf("%s", novoCliente->pass);
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
        printf("| Email: %s                              \n", aux->email);
        printf("| Password: ************                             \n");
        printf("| Morada: %s                            \n", aux->morada);
        printf("| Saldo: %.2f                           \n", aux->saldo);
        printf(" ------------------------------------\n");
    }
    printf("\n\n\n");
}
Cliente *listaClientes = NULL;
MeioEletrico *listaMeios =NULL;

void menuescolhasgestor()
{
   int opc;
   int op1;
  do
	{
        int opc;
        printf(" -------------------------------------------\n");
        printf("| 1 Inserir novos dados                     |\n");
        printf("| 2 Listar dados                            |\n");
        printf("| 3 Remover dados                           |\n");
        printf("| 4 Guardar dados                           |\n");
        printf("| 5 Ler dados                               |\n");
        printf("| 0 Sair                                    |\n");
        printf(" -------------------------------------------\n");
        printf(" Opcao: ");
        scanf("%d", &opc);
		switch(opc)
		{
          case 1: printf("\nDeseja inserir: \n\n");
		          printf(" ---------------\n");
				  printf("| 1- Meios      |\n");
				  printf("| 2- Clientes   |\n");
				  printf("| 3- Gestores   |\n");
				  printf(" --------------- \n\n");
		          printf(" Opcao: ");
				  scanf("%d",&op1);
				  switch (op1)
				  {
				  case 1:
					 insereMeio(&listaMeios);
					break;
				  case 2:
				    insereCliente(&listaClientes);
				    break;
				  case 3:
				    
				  default:
					break;
				  }
                  
				  break;
		      case 2: printf("\nDeseja listar: \n\n");
                        printf(" ---------------\n");
                        printf("| 1- Meios      |\n");
                        printf("| 2- Clientes   |\n");
                        printf("| 3- Gestores   |\n");
                        printf(" --------------- \n\n");
                        printf(" Opcao: ");
                        scanf("%d",&op1);
				  switch (op1)
				  {
				  case 1:
					mostraMeios(&listaMeios);
					break;
				  case 2:
				     mostraClientes(listaClientes);
				   break;

				  case 3:

				   break;
				  default:
					break;
				  }
		}
	}
	while(opc!=0);
   





}

void registraCliente(Cliente **listaClientes) {
    Cliente *novoCliente = malloc(sizeof(Cliente));
    novoCliente->proximo = NULL;
   
    // Pedir dados do novo cliente ao utilizador
    printf("\n\nNome: ");
    scanf("%s", novoCliente->nome);

    printf("Morada: ");
    scanf("%s", novoCliente->morada);

    printf("NIF: ");
    scanf("%d", novoCliente->nif);

    printf("Email: ");
    scanf("%s", novoCliente->email);

    Cliente *aux;
    for (aux = *listaClientes; aux != NULL; aux = aux->proximo) {
        if (strcmp(novoCliente->email, aux->email) == 0) {
            printf("ERRO: O email %s ja existe na lista.\n", novoCliente->email);
            free(novoCliente);
            return;
        }
    }

    printf("Senha: ");
    scanf("%s", novoCliente->pass);

    // Verificar se o email já existe na lista
    
    // Inserir o novo cliente no final da lista
    if (*listaClientes == NULL) {
        *listaClientes = novoCliente;
    } else {
        Cliente *ultimo = *listaClientes;
        while (ultimo->proximo != NULL) {
            ultimo = ultimo->proximo;
        }
        ultimo->proximo = novoCliente;
    }

    printf("Cliente registrado com sucesso.\n");
    
