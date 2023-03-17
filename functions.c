#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "functions.h"

Cliente *listaClientes = NULL;
MeioEletrico *listaMeios =NULL;
Gestor *listaGestores=NULL;



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

    // Armazena o meio eletrico no arquivo meios.txt
    FILE *arquivoMeios = fopen("meios.txt", "a");
    if (arquivoMeios == NULL) {
        printf("ERRO: Não foi possível abrir o arquivo de meios.\n");
        return;
    }
    fprintf(arquivoMeios, "%d;%s;%d;%.2f;%s\n", novoMeio->id, novoMeio->tipo, novoMeio->carga_bateria, novoMeio->custo, novoMeio->localizacao);
    fclose(arquivoMeios);
}
void lerMeios(MeioEletrico **listaMeios) {
    FILE *arquivo;
    char linha[250];
    char *idStr, *tipo, *cargaStr, *custoStr, *localizacao;
    MeioEletrico *novoMeio;

    // Abrir arquivo de meios
    arquivo = fopen("meios.txt", "r");

    // Ler arquivo linha por linha e armazenar na lista de meios
    while (fgets(linha, sizeof(linha), arquivo)) {
        // Separar campos pelo caractere ';'
        idStr = strtok(linha, ";");
        tipo = strtok(NULL, ";");
        cargaStr = strtok(NULL, ";");
        custoStr = strtok(NULL, ";");
        localizacao = strtok(NULL, ";");

        // Criar novo meio e adicionar à lista
        novoMeio = (MeioEletrico*) malloc(sizeof(MeioEletrico));
        novoMeio->id = atoi(idStr);  // converter string para int
        strcpy(novoMeio->tipo, tipo);
        novoMeio->carga_bateria = atoi(cargaStr);  // converter string para int
        novoMeio->custo = atof(custoStr);  // converter string para float
        strcpy(novoMeio->localizacao, localizacao);
        novoMeio->proximo = *listaMeios;
        *listaMeios = novoMeio;
    }

    fclose(arquivo);
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
    // Armazena o cliente no arquivo clientes.txt
    FILE *arquivoClientes = fopen("clientes.txt", "a");
    if (arquivoClientes == NULL) {
        printf("ERRO: Não foi possível abrir o arquivo de clientes.\n");
        return;
    }
    fprintf(arquivoClientes, "%s;%s;%s;%s;%.2f\n", novoCliente->nif, novoCliente->email, novoCliente->pass, novoCliente->morada, novoCliente->saldo);
    fclose(arquivoClientes);
    printf("\n Cliente criado com sucesso! \n \n ");
}

void insereGestor(Gestor **listaGestores) {
    Gestor *novoGestor = (Gestor*) malloc(sizeof(Gestor));

    printf("Insira o nome do gestor: ");
    scanf("%s", novoGestor->nome);
    printf("Insira o email: ");
    scanf("%s", novoGestor->email);
    printf("Insire a password: ");
    scanf("%s", novoGestor->pass);

    novoGestor->proximo = *listaGestores;
    *listaGestores = novoGestor;
    // Armazena o gestor no arquivo gestores.txt
    FILE *arquivoGestores = fopen("gestores.txt", "a");
    if (arquivoGestores == NULL) {
        printf("ERRO: Não foi possível abrir o arquivo de gestores.\n");
        return;
    }
    fprintf(arquivoGestores, "%s;%s;%s\n", novoGestor->nome, novoGestor->email, novoGestor->pass);
    fclose(arquivoGestores);
    printf("\n Gestor criado com sucesso! \n \n ");
    system("cls");
}



void lerClientes(Cliente **listaClientes) {
    FILE *arquivo;
    char linha[250];
    char *nome, *morada, *nif, *email, *senha, *saldoStr;
    Cliente *novoCliente;

    // Abrir arquivo de clientes
    arquivo = fopen("clientes.txt", "r");

    // Ler arquivo linha por linha e armazenar na lista de clientes
    while (fgets(linha, sizeof(linha), arquivo)) {
        // Separar campos pelo caractere ';'
        nome = strtok(linha, ";");
        morada = strtok(NULL, ";");
        nif = strtok(NULL, ";");
        email = strtok(NULL, ";");
        senha = strtok(NULL, ";");
        saldoStr = strtok(NULL, ";");

        // Criar novo cliente e adicionar à lista
        novoCliente = (Cliente*) malloc(sizeof(Cliente));
        strcpy(novoCliente->nome, nome);
        strcpy(novoCliente->morada, morada);
        strcpy(novoCliente->nif, nif);
        strcpy(novoCliente->email, email);
        strcpy(novoCliente->pass, senha);
        novoCliente->saldo = atof(saldoStr);  // converter string para float
        novoCliente->proximo = *listaClientes;
        *listaClientes = novoCliente;
    }

    fclose(arquivo);
}











void mostraClientes(Cliente *listaClientes) {
    Cliente *aux;
    lerClientes(&listaClientes);
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


void menuescolhasgestor()
{
    
   int opc;
   int op1;
  do
	{
    
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
				    insereGestor(&listaGestores);
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

    // Abrir arquivo para escrita
    FILE *arquivoClientes;
    arquivoClientes = fopen("clientes.txt", "a");


    // Verificar se o email já existe na lista
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
    fprintf(arquivoClientes, "%s;%s;%d;%s;%s\n", novoCliente->nome, novoCliente->morada, novoCliente->nif, novoCliente->email, novoCliente->pass);
    fclose(arquivoClientes);
    printf("Cliente registrado com sucesso.\n");
    
}



void loginGestor() {
    FILE *arquivo;
    char linha[150];
    char *nome, *email, *senha;
    Gestor *novo_gestor;
    Gestor *gestores = NULL;
    char email_login[50], senha_login[50];

    // Abrir arquivo de gestores
    arquivo = fopen("gestores.txt", "r");
    nome = (char*) malloc(50 * sizeof(char));
    email = (char*) malloc(50 * sizeof(char));
    senha = (char*) malloc(50 * sizeof(char));
    // Ler arquivo linha por linha e armazenar na lista de gestores
   while (fscanf(arquivo, "%[^;];%[^;];%s", nome, email, senha) == 3) {
    // Criar novo gestor e adicionar à lista
    novo_gestor = (Gestor*) malloc(sizeof(Gestor));
    strcpy(novo_gestor->nome, nome);
    strcpy(novo_gestor->email, email);
    strcpy(novo_gestor->pass, senha);
    novo_gestor->proximo = gestores;
    gestores = novo_gestor;
}

  
    int login_bem_sucedido = 0;
    while (!login_bem_sucedido) {
        // Pedir email e senha para login
        printf("\n\n Email: ");
        scanf("%s", email_login);
        printf("\n Senha: ");
        scanf("%s", senha_login);

        // Verificar se email e senha correspondem a algum gestor na lista
        Gestor *g = gestores;
        while (g != NULL) {
            if (strcmp(g->email, email_login) == 0 && strcmp(g->pass, senha_login) == 0) {
                // Login bem-sucedido, chamar o menu de opções para o gestor
                system("cls");
                printf("\nBem-vindo, %s!\n\n", g->nome);
                menuescolhasgestor();
                return;
            }
            g = g->proximo;
        }

        // Caso email e/ou senha estejam incorretos
        printf("\nEmail e/ou senha incorretos. Tente novamente.\n\n");
    }
}