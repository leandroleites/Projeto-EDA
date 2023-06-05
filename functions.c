#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <float.h>
#include "structs.h"
#include "functions.h"


Cliente *listaClientes = NULL;
MeioEletrico *listaMeios =NULL;
Gestor *listaGestores=NULL;
grafo* headV = NULL;
	



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
    FILE *fp;
    MeioEletrico *meioAtual;
    int id, carga_bateria;
    float custo;
    char tipo[20], localizacao[20];
    fp = fopen("meios.txt", "r");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo de meios.\n");
        return;
    }
    while (fscanf(fp, "%d %s %d %f %s", &id, tipo, &carga_bateria, &custo, localizacao) == 5) {
        meioAtual = (MeioEletrico*) malloc(sizeof(MeioEletrico));
        if (meioAtual == NULL) {
            printf("Erro ao alocar memoria.\n");
            return;
        }
        meioAtual->id = id;
        strcpy(meioAtual->tipo, tipo);
        meioAtual->carga_bateria = carga_bateria;
        meioAtual->custo = custo;
        strcpy(meioAtual->localizacao, localizacao);
        meioAtual->proximo = NULL;
        if (*listaMeios == NULL) {
            *listaMeios = meioAtual;
        } else {
            MeioEletrico *aux = *listaMeios;
            while (aux->proximo != NULL) {
                aux = aux->proximo;
            }
            aux->proximo = meioAtual;
        }
    }
    fclose(fp);
}


void mostrarMeios() {
    FILE *arquivo;
    MeioEletrico *meios = NULL, *meio_atual;
    char linha[150], *token;
    
    // Abrir arquivo de meios
    arquivo = fopen("meios.txt", "r");
    if (arquivo == NULL) {
        printf("\nErro ao abrir o arquivo de meios.\n");
        return;
    }

    // Ler o arquivo e criar a lista de meios
    while (fgets(linha, 150, arquivo) != NULL) {
        // Criar novo meio e adicionar à lista
        meio_atual = (MeioEletrico*) malloc(sizeof(MeioEletrico));
        token = strtok(linha, ";");
        meio_atual->id = atoi(token);
        token = strtok(NULL, ";");
        strcpy(meio_atual->tipo, token);
        token = strtok(NULL, ";");
        meio_atual->carga_bateria = atoi(token);
        token = strtok(NULL, ";");
        meio_atual->custo = atof(token);
        token = strtok(NULL, ";");
        strcpy(meio_atual->localizacao, token);
        token = strtok(NULL, ";");
        meio_atual->alugado = atoi(token);
        meio_atual->proximo = meios;
        meios = meio_atual;
    }
    fclose(arquivo);

    // Imprimir lista de meios
    printf("\nLista de meios:\n\n");
    meio_atual = meios;
    while (meio_atual != NULL) {
        printf("ID: %d\nTipo: %s\nCarga da bateria: %d%%\nCusto: %.2f€\nLocalizacao: %s\nAlugado: %s\n\n", meio_atual->id, meio_atual->tipo, meio_atual->carga_bateria, meio_atual->custo, meio_atual->localizacao, meio_atual->alugado ? "Sim" : "Nao");
        meio_atual = meio_atual->proximo;
    }

    // Liberar a memória alocada para a lista de meios
    meio_atual = meios;
    while (meio_atual != NULL) {
        meios = meio_atual->proximo;
        free(meio_atual);
        meio_atual = meios;
    }
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

void lerGestores(Gestor **listaGestores) {
    FILE *arquivo;
    char linha[250];
    char *nome,  *email, *pass;
    Gestor *novogestor;

    // Abrir arquivo de clientes
    arquivo = fopen("gestores.txt", "r");

    // Ler arquivo linha por linha e armazenar na lista de clientes
    while (fgets(linha, sizeof(linha), arquivo)) {
        // Separar campos pelo caractere ';'
        nome = strtok(linha, ";");
        email = strtok(NULL, ";");
        pass = strtok(NULL, ";");


        // Criar novo cliente e adicionar à lista
        novogestor = (Gestor*) malloc(sizeof(Gestor));
        strcpy(novogestor->nome, nome);
        strcpy(novogestor->email, email);
        strcpy(novogestor->pass, pass);

 
        novogestor->proximo = *listaGestores;
        *listaGestores = novogestor;
    }

    fclose(arquivo);
}
void mostragestores(Gestor **listaGestores) {
    Cliente *aux;
    lerGestores(&listaGestores);
    if (listaGestores == NULL) {
        printf("\nNao ha gestores cadastrados.\n");
        return;
    }

    printf("\nGestores registrados:\n");
    for (aux = listaGestores; aux != NULL; aux = aux->proximo) {
        printf("\n-----------------------------------\n");
        printf("| Nome: %s                              \n", aux->nome);
        printf("| Email: %s                              \n", aux->email);
        printf("| Password: ************                             \n");
        printf(" ------------------------------------\n");
    }
    printf("\n\n\n");
}


void mostraClientes() {
    FILE *ficheiro_clientes = fopen("clientes.txt", "r");
    if (ficheiro_clientes == NULL) {
        printf("Erro ao abrir o ficheiro de clientes.\n");
        return;
    }
    char linha[200];
    printf("=== Lista de clientes ===\n\n");
    while (fgets(linha, 200, ficheiro_clientes)) {
        Cliente *cliente_atual = (Cliente *)malloc(sizeof(Cliente));
        sscanf(linha, "%[^;];%[^;];%[^;];%[^;];%[^;];%f", cliente_atual->nome, cliente_atual->morada, cliente_atual->nif, cliente_atual->email, cliente_atual->pass, &cliente_atual->saldo);
        cliente_atual->proximo = NULL;
        printf("Nome: %s\nMorada: %s\nNIF: %s\nE-mail: %s\nSaldo: %.2f\n\n", cliente_atual->nome, cliente_atual->morada, cliente_atual->nif, cliente_atual->email, cliente_atual->saldo);
        free(cliente_atual);
    }
    fclose(ficheiro_clientes);
}

void remover_meio(MeioEletrico *listaMeios) {
    int id_procurado;
    printf("\n\nDigite o ID do meio eletrico que deseja remover: ");
    scanf("%d", &id_procurado);

    FILE *arquivo;
    arquivo = fopen("meios.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!");
        exit(1);
    }

    FILE *temporario;
    temporario = fopen("temp.txt", "w");
    if (temporario == NULL) {
        printf("Erro ao criar arquivo temporario!");
        exit(1);
    }

    MeioEletrico meio;
    char linha[200];
    char *token;
    while (fgets(linha, sizeof(linha), arquivo)) {
        token = strtok(linha, ";");
        meio.id = atoi(token);
        if (meio.id == id_procurado) {
            continue; // pula a linha que corresponde ao meio a ser removido
        }
        fprintf(temporario, "%s", linha);
    }
    fclose(arquivo);
    fclose(temporario);

    remove("meios.txt");
    rename("temp.txt", "meios.txt");

    printf("Meio eletrico com ID %d removido com sucesso!\n\n", id_procurado);
}

void remover_cliente(Cliente **listaClientes) {
    char email_procurado[50];
    printf("\nDigite o email do cliente que deseja remover: \n");
    scanf("%s", email_procurado);

    FILE *arquivo;
    arquivo = fopen("clientes.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo!");
        exit(1);
    }

    FILE *temporario;
    temporario = fopen("temp.txt", "w");
    if (temporario == NULL) {
        printf("Erro ao criar arquivo temporario!");
        exit(1);
    }

    char linha[400];
    char *token;
    Cliente *atual = *listaClientes;
    Cliente *anterior = NULL;
    while (fgets(linha, sizeof(linha), arquivo)) {
        Cliente *cliente = (Cliente*) malloc(sizeof(Cliente));
        token = strtok(linha, ";");
        strcpy(cliente->nome, token);
        token = strtok(NULL, ";");
        strcpy(cliente->morada, token);
        token = strtok(NULL, ";");
        strcpy(cliente->nif, token);
        token = strtok(NULL, ";");
        strcpy(cliente->email, token);
        token = strtok(NULL, ";");
        strcpy(cliente->pass, token);
        token = strtok(NULL, ";");
        cliente->saldo = atof(token);

        if (strcmp(cliente->email, email_procurado) == 0) {
            if (anterior == NULL) {
                *listaClientes = cliente->proximo;
            } else {
                anterior->proximo = cliente->proximo;
            }
            free(cliente);
            continue;
        }

        fprintf(temporario, "%s", linha);

        anterior = cliente;
        if (atual != NULL) {
        atual = atual->proximo;
}
    }

    fclose(arquivo);
    fclose(temporario);

    remove("clientes.txt");
    rename("temp.txt", "clientes.txt");

    printf("\nCliente com email %s removido com sucesso!\n", email_procurado);
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
        printf("| 4 Alterar dados                           |\n");
        printf(" -------------------------------------------\n");
        printf("| 5 Registar localizacao                    |\n");
        printf("| 6 Editar localizacao                      |\n");
        printf("| 7 Remover localizacao                     |\n");
        printf("| 8 Registar conexao                        |\n");
        printf("| 9 Remover conexao                         |\n");
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
                      printf(" --------------- \n\n");
                      printf(" Opcao: ");
                      scanf("%d",&op1);
				  switch (op1)
				  {
				  case 1:
					mostrarMeios(&listaMeios);
					break;
				  case 2:
				    mostraClientes(listaClientes);
				   break;
				  default:
					break;
				  }
       
              case 3:
                printf("\nDeseja remover: \n\n");
                printf(" ---------------\n");
                printf("| 1- Meios      |\n");
                printf("| 2- Clientes   |\n");
                printf(" --------------- \n\n");
                printf(" Opcao: ");
                scanf("%d",&op1);
                switch (op1) {
                    case 1:
                        remover_meio(&listaMeios);
                        break;
                    case 2:
                        remover_cliente(&listaClientes);
                        break;
                    default:
                        break;
                }
                break;

                case 5:
                   criarVertice(headV);
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

void loginCliente() {
    FILE *arquivo;
    char linha[150];
    char *nome, *morada, *nif, *email, *senha;
    Cliente *novo_cliente;
    Cliente *clientes = NULL;
    char email_login[50], senha_login[50];

    // Abrir arquivo de clientes
    arquivo = fopen("clientes.txt", "r");
    nome = (char*) malloc(50 * sizeof(char));
    morada = (char*) malloc(100 * sizeof(char));
    nif = (char*) malloc(20 * sizeof(char));
    email = (char*) malloc(50 * sizeof(char));
    senha = (char*) malloc(50 * sizeof(char));
    // Ler arquivo linha por linha e armazenar na lista de clientes
    while (fscanf(arquivo, "%[^;];%[^;];%[^;];%[^;];%s", nome, morada, nif, email, senha) == 5) {
        // Criar novo cliente e adicionar à lista
        novo_cliente = (Cliente*) malloc(sizeof(Cliente));
        strcpy(novo_cliente->nome, nome);
        strcpy(novo_cliente->morada, morada);
        strcpy(novo_cliente->nif, nif);
        strcpy(novo_cliente->email, email);
        strcpy(novo_cliente->pass, senha);
        novo_cliente->saldo = 0;
        novo_cliente->proximo = clientes;
        clientes = novo_cliente;
    }

    int login_bem_sucedido = 0;
    while (!login_bem_sucedido) {
        // Pedir email e senha para login
        printf("\n\n Email: ");
        scanf("%s", email_login);
        printf("\n Senha: ");
        scanf("%s", senha_login);

        // Verificar se email e senha correspondem a algum cliente na lista
        Cliente *c = clientes;
        while (c != NULL) {
            if (strcmp(c->email, email_login) == 0 && strcmp(c->pass, senha_login) == 0) {
                // Login bem-sucedido, chamar o menu de opções para o cliente
                system("cls");
                printf("\nBem-vindo, %s!\n\n", c->nome);
                menuopcoescliente(c);
                return;
            }
            c = c->proximo;
        }

        // Caso email e/ou senha estejam incorretos
        printf("\nEmail e/ou senha incorretos. Tente novamente.\n\n");
    }
}



void menuopcoescliente()
{
    
   int opc;
   int op1;
    do
	{
    
        printf(" -------------------------------------------\n");
        printf("| 1 Alugar meio                             |\n");
        printf("| 2 Listar meios por autonomia              |\n");
        printf(" -------------------------------------------\n");
        printf(" Opcao: ");
        scanf("%d", &opc);
		switch(opc)
		{
          case 1:
           alugarMeio(&listaClientes);
           break;
          case 2:
            listarMeiosPorAutonomia();
          break;
          case 3:

          break;
          default:
          break;

        }
    }
    while(opc!=0);
}


void alugarMeio(Cliente* cliente) {
    FILE* arquivo_meios;
    FILE* arquivo_alugueres;
    MeioEletrico* meios = NULL;
    MeioEletrico* meio_atual;
    char linha[150], *token;
    int meio_id, encontrou_meio = 0;
    float custo_meio;

    // Abrir arquivo de meios
    arquivo_meios = fopen("meios.txt", "r");
    if (arquivo_meios == NULL) {
        printf("\nErro ao abrir o arquivo de meios.\n");
        return;
    }

    while (fgets(linha, 150, arquivo_meios) != NULL) {
        // Criar novo meio e adicionar à lista
        meio_atual = (MeioEletrico*)malloc(sizeof(MeioEletrico));
        token = strtok(linha, ";");
        meio_atual->id = atoi(token);
        token = strtok(NULL, ";");
        strcpy(meio_atual->tipo, token);
        token = strtok(NULL, ";");
        meio_atual->carga_bateria = atoi(token);
        token = strtok(NULL, ";");
        meio_atual->custo = atof(token);
        token = strtok(NULL, ";");
        strcpy(meio_atual->localizacao, token);
        meio_atual->alugado = 0;  // Inicialmente, o meio não está alugado
        meio_atual->proximo = meios;
        meios = meio_atual;
    }

    fclose(arquivo_meios);

    // Mostrar lista de meios disponíveis para o cliente
    printf("\nLista de meios disponiveis:\n\n");
    meio_atual = meios;
    while (meio_atual != NULL) {
        if (meio_atual->carga_bateria > 0 && !meio_atual->alugado) {
            printf("ID: %d\nTipo: %s\nCarga da bateria: %d%%\nCusto: %.2f€\nLocalizacao: %s\n\n",
                   meio_atual->id, meio_atual->tipo, meio_atual->carga_bateria, meio_atual->custo,
                   meio_atual->localizacao);
        }
        meio_atual = meio_atual->proximo;
    }

    // Pedir ao cliente para selecionar um meio para alugar
    printf("Digite o ID do meio que deseja alugar: ");
    scanf("%d", &meio_id);

    // Procurar o meio selecionado na lista de meios
    meio_atual = meios;
    while (meio_atual != NULL) {
        if (meio_atual->id == meio_id && meio_atual->carga_bateria > 0 && !meio_atual->alugado) {
            // Meio encontrado e disponível para aluguel
            // Marcar o meio como alugado
            meio_atual->alugado = 1;
            if (cliente->saldo >= meio_atual->custo) {
                // Meio encontrado e disponível para aluguel
                // Marcar o meio como alugado
                meio_atual->alugado = 1;

                // Subtrair o valor do meio alugado do saldo do cliente
                cliente->saldo -= meio_atual->custo;

                // Resto do código...
            } else {
                printf("Saldo insuficiente para alugar o meio.\n");
            }
            // Obter a data e hora atuais
            time_t t = time(NULL);
            struct tm* tm_info = localtime(&t);
            char data_hora[30];
            strftime(data_hora, sizeof(data_hora), "%Y-%m-%d %H:%M:%S", tm_info);

            // Abrir arquivo de alugueres em modo de adição
            arquivo_alugueres = fopen("alugueres.txt", "a");
            if (arquivo_alugueres == NULL) {
                printf("\nErro ao abrir o arquivo de alugueres.\n");
                return;
            }

            // Escrever as informações do aluguer no arquivo
            fprintf(arquivo_alugueres, "Cliente: %s\n", cliente->nome);
            fprintf(arquivo_alugueres, "Meio: %s\n", meio_atual->tipo);
            fprintf(arquivo_alugueres, "Custo: %.2f\n", meio_atual->custo);
            fprintf(arquivo_alugueres, "Localizacao: %s\n", meio_atual->localizacao);
            fprintf(arquivo_alugueres, "Data e Hora: %s\n\n", data_hora);

            // Fechar o arquivo de alugueres
            fclose(arquivo_alugueres);

            printf("\nMeio alugado com sucesso!\n");
            printf("Tipo: %s\n", meio_atual->tipo);
            printf("Custo: %.2f\n", meio_atual->custo);
            printf("Localizacao: %s\n", meio_atual->localizacao);
            printf("Data e Hora: %s\n\n", data_hora);
            break;  // Saia do loop após alugar o meio
        }
        meio_atual = meio_atual->proximo;
    }

    // Meio não encontrado, já alugado ou com carga insuficiente
    if (meio_atual == NULL) {
        printf("\nMeio nao encontrado, ja alugado ou com carga insuficiente.\n");
    }
}



void listarMeiosPorAutonomia() {
    FILE *arquivo;
    MeioEletrico *meios = NULL, *meio_atual, *temp;
    char linha[150], *token;
    int i, j, qtd_meios = 0;
    // Abrir arquivo de meios
    arquivo = fopen("meios.txt", "r");
    if (arquivo == NULL) {
        printf("\nErro ao abrir o arquivo de meios.\n");
        return;
    }

    // Ler meios do arquivo
    while (fgets(linha, 150, arquivo) != NULL) {
        // Criar novo meio e adicionar à lista
        meio_atual = (MeioEletrico*) malloc(sizeof(MeioEletrico));
        token = strtok(linha, ";");
        meio_atual->id = atoi(token);
        token = strtok(NULL, ";");
        strcpy(meio_atual->tipo, token);
        token = strtok(NULL, ";");
        meio_atual->carga_bateria = atoi(token);
        token = strtok(NULL, ";");
        meio_atual->custo = atof(token);
        token = strtok(NULL, ";");
        strcpy(meio_atual->localizacao, token);
        meio_atual->alugado = 0;
        meio_atual->proximo = meios;
        meios = meio_atual;
        qtd_meios++;
    }
    fclose(arquivo);

    // Ordenar meios por autonomia
    for (i = 0; i < qtd_meios; i++) {
        meio_atual = meios;
        for (j = 0; j < qtd_meios - 1; j++) {
           if (meio_atual->proximo != NULL && meio_atual->carga_bateria < meio_atual->proximo->carga_bateria) {
                // Trocar posição dos meios na lista
                if (j == 0) {
                    temp = meio_atual->proximo->proximo;
                    meio_atual->proximo->proximo = meio_atual;
                    meios = meio_atual->proximo;
                    meio_atual->proximo = temp;
                } else {
                    temp = meio_atual->proximo->proximo;
                    meio_atual->proximo->proximo = meio_atual;
                    meio_atual->proximo = temp;
                    meio_atual = meio_atual->proximo;
                }
            } else {
                meio_atual = meio_atual->proximo;
            }
        }
    }

    // Imprimir lista de meios por autonomia
    printf("\nLista de meios por ordem decrescente de autonomia:\n\n");
    meio_atual = meios;
    while (meio_atual != NULL) {
        printf("ID: %d\nTipo: %s\nCarga da bateria: %d%%\nCusto: %.2f€\nLocalizacao: %s\n\n", meio_atual->id, meio_atual->tipo, meio_atual->carga_bateria, meio_atual->custo, meio_atual->localizacao);
        meio_atual = meio_atual->proximo;
    }

    // Liberar memória alocada para a lista de meios
    meio_atual = meios;
    while (meio_atual != NULL) {
        temp = meio_atual;
        meio_atual = meio_atual->proximo;
        free(temp);
    }
}



/////////////////////////////////////////////////////////////////////////////
//                            fase 2.                                      //
/////////////////////////////////////////////////////////////////////////////


grafo* criarGrafo() {
    grafo* g = (grafo*)malloc(sizeof(grafo));
    g->num_vertices = 8;
    g->num_arestas = 0;
    g->vertices = NULL;

    char nomes[8][50] = {
        "///mantenha.pactual.prestigiar",
        "///couve.vinha.expõe",
        "///importava.autênticas.escalão",
        "///estrelinha.misturam.negociado",
        "///levou.bonés.tapeçaria",
        "///consideráveis.exprimindo.afobar",
        "///coisas.suspensos.rasgão",
        "///desvairar.envolvimento.reintegrando"
    };

    char local_meios[8][50] = {
      "Monte_SantoOvidio",
      "Zé_Dos_Cães",
      "Tasca_Lemos",
      "Igreja_SaoBento",
      "Junta_de_Freguesia",
      "Largo_Vilarinho",
      "Campo_Desportivo",
      "Mercearia_Teixeira"
    };

    for (int i = 0; i < g->num_vertices; i++) {
        vertice* novoVertice = (vertice*)malloc(sizeof(vertice));
        novoVertice->id = i;
        strcpy(novoVertice->nome, nomes[i]);
        strcpy(novoVertice->local_meio, local_meios[i]);
        novoVertice->arestas = NULL;
        novoVertice->seguinte = NULL;

        if (g->vertices == NULL) {
            g->vertices = novoVertice;
        }
        else {
            vertice* atual = g->vertices;
            while (atual->seguinte != NULL) {
                atual = atual->seguinte;
            }
            atual->seguinte = novoVertice;
        }
    }

    return g;
}

aresta* criarConexao() {
    aresta* listaArestas = NULL;
    int conexoes[12][3] = {
        {0, 1, 13},
        {0, 2, 15},
        {1, 2, 17},
        {1, 4, 23},
        {2, 3, 19},
        {2, 6, 28},
        {3, 4, 13},
        {3, 5, 15},
        {4, 5, 17},
        {4, 7, 28},
        {5, 6, 19},
        {6, 7, 15}
    };
        for (int i = 0; i < 12; i++) {
            int id_origem = conexoes[i][0];
            int id_destino = conexoes[i][1];
            int peso = conexoes[i][2];

            aresta* novaAresta = (aresta*)malloc(sizeof(aresta));
            novaAresta->id_origem = id_origem;
            novaAresta->id_destino = id_destino;
            novaAresta->peso = peso;
            novaAresta->proxima = NULL;

        // Adiciona a nova aresta à lista de arestas
        if (listaArestas == NULL) {
            listaArestas = novaAresta;
        }
        else {
            aresta* atual = listaArestas;
            while (atual->proxima != NULL) {
                atual = atual->proxima;
            }
            atual->proxima = novaAresta;
        }
    }

    return listaArestas;
}

grafo* carregarGrafo() {
    grafo* g = (grafo*)malloc(sizeof(grafo));
    g->num_vertices = 0;
    g->num_arestas = 0;
    g->vertices = NULL;

    FILE* arquivo = fopen("grafo.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return g;
    }

    char linha[100];

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        int id;
        char local_meio[50];
        char nome[50];
        if (sscanf(linha, "%d %s %s\n", &id, local_meio, nome) == 3) {
            vertice* novoVertice = (vertice*)malloc(sizeof(vertice));
            novoVertice->id = id;
            strcpy(novoVertice->local_meio, local_meio);
            strcpy(novoVertice->nome, nome);
            novoVertice->arestas = NULL;
            novoVertice->seguinte = NULL;

            if (g->vertices == NULL) {
                g->vertices = novoVertice;
            }
            else {
                vertice* atual = g->vertices;
                while (atual->seguinte != NULL) {
                    atual = atual->seguinte;
                }
                atual->seguinte = novoVertice;
            }

            g->num_vertices++;
        }
    }

    fclose(arquivo);

    return g;
}

aresta* carregarAresta() {
    
    FILE* arquivo = fopen("arestas.txt", "r");
    if (arquivo == NULL) {
        printf("Erro: Falha ao abrir o arquivo.\n");
        return NULL;
    }
        aresta* lista_arestas = NULL;  

        int id_origem, id_destino, peso;
        while (fscanf(arquivo, "%d %d %d", &id_origem, &id_destino, &peso) == 3) {
 
        aresta* nova_aresta = (aresta*)malloc(sizeof(aresta));
            if (nova_aresta == NULL) {
                printf("Erro: Falha ao alocar memoria para a nova aresta.\n");
                fclose(arquivo);
                return lista_arestas;
            }
                nova_aresta->id_origem = id_origem;
                nova_aresta->id_destino = id_destino;
                nova_aresta->peso = peso;
                nova_aresta->proxima = NULL;
    
        if (lista_arestas == NULL) {
            lista_arestas = nova_aresta;
        }
        else {
            aresta* atual = lista_arestas;
            while (atual->proxima != NULL) {
                atual = atual->proxima;
            }
                atual->proxima = nova_aresta;
        }
    }
   
    fclose(arquivo);
    return lista_arestas;
}

vertice* buscarVertice(grafo* g, int id) {
    g = carregarGrafo();
    vertice* atual = g->vertices;
    while (atual != NULL) {
        if (atual->id == id) {
            return atual;
        }
        atual = atual->seguinte;
    }
    return NULL; 
}

void salvarGrafo(grafo* g) {
    FILE* arquivo = fopen("grafo.txt", "w");
    FILE* arquivo_bin = fopen("grafo.bin", "wb");

    if (arquivo == NULL || arquivo_bin == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    vertice* atual = g->vertices;
    while (atual != NULL) {
        fprintf(arquivo, "%d %s %s\n", atual->id, atual->local_meio, atual->nome);
        fwrite(atual, sizeof(vertice), 1, arquivo_bin);
        atual = atual->seguinte;
    }
        fclose(arquivo);
    fclose(arquivo_bin);
}

void criarVertice(grafo* g) {  
    char nome[50];
    char local_meio[50];
    g = carregarGrafo();
    
    
    printf("Digite o geocodigo do vertice: ");
    scanf("%s", nome);

    printf("\nDigite o local do vertice: ");
    scanf("%s", local_meio);

    
    vertice* novoVertice = (vertice*)malloc(sizeof(vertice));
    novoVertice->id = g->num_vertices;
    strcpy(novoVertice->nome, nome);
    strcpy(novoVertice->local_meio, local_meio);

    novoVertice->arestas = NULL;
    novoVertice->seguinte = NULL;
 
    if (g->vertices == NULL) {
        g->vertices = novoVertice;
    }
    else {
        vertice* atual = g->vertices;
        while (atual->seguinte != NULL) {
            atual = atual->seguinte;
        }
        atual->seguinte = novoVertice;
    }
        g->num_vertices++;
  
    atualizarVertices(g->vertices);

    system("clear || cls");
    printf("\nNovo vertice criado com sucesso!\n");
    getchar();
}

void editarVertice(grafo* g) {
    g = carregarGrafo();
    
    int id;
    char novoNome[50];
    char novoLocal[50];

    imprimirVertices(g);

    printf("\nDigite o ID do vertice a ser editado: ");
    scanf("%d", &id);


    vertice* atual = g->vertices;
    while (atual != NULL) {
        if (atual->id == id) {
            break;
        }
        atual = atual->seguinte;
    }

    if (atual == NULL) {
        printf("\nVertice com o ID %d nao encontrado.", id);
        return;
    }
    printf("\nDigite o novo geocodigo do vertice: ");
    scanf("%s", novoNome);
    strcpy(atual->nome, novoNome);
    printf("\nDigite o novo local do vertice: ");
    scanf("%s", novoLocal);
    strcpy(atual->local_meio, novoLocal);
    atualizarVertices(g->vertices);

    system("clear || cls");
    printf("\nVertice editado com sucesso!\n");
    getchar();
}

void removerVertice(grafo* g) {
    g = carregarGrafo();
    imprimirVertices(g);
    int id;

  
    printf("\nDigite o ID do vertice a ser removido: ");
    scanf("%d", &id);
    vertice* atual = g->vertices;
    vertice* anterior = NULL;
    while (atual != NULL) {
        if (atual->id == id) {
            break;
        }
        anterior = atual;
        atual = atual->seguinte;
    }
    if (atual == NULL) {
        printf("\nVertice com o ID %d nao encontrado.", id);
        return;
    }
   
    if (anterior == NULL) {
    
        g->vertices = atual->seguinte;
    }
    else {
        
        anterior->seguinte = atual->seguinte;
    }


    atualizarVertices(g->vertices);

    system("clear || cls");
    printf("\nVertice removido com sucesso!\n");
    getchar();
}

void imprimirVertices(grafo* g) {
    printf("Localizacoes:\n\n");
    printf("%-5s | %-17s | %s\n", "ID", "Local", "Nome");
    printf("----------------------------------\n");

    vertice* v = g->vertices;
    while (v != NULL) {
        printf("%-5d | %-17s | %s\n", v->id, v->local_meio, v->nome);
        v = v->seguinte;
    }
}

void atualizarVertices(vertice* vertices) {
    FILE* arquivo = fopen("grafo.txt", "w");
    FILE* arquivo_bin = fopen("grafo.bin", "wb");

    if (arquivo == NULL || arquivo_bin == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
        vertice* novoVertice = vertices;
        while (novoVertice != NULL) {
            fprintf(arquivo, "%d %s %s\n", novoVertice->id, novoVertice->local_meio, novoVertice->nome);
            fwrite(novoVertice, sizeof(vertice), 1, arquivo_bin);
            novoVertice = novoVertice->seguinte;
    }
        fclose(arquivo);
        fclose(arquivo_bin);
}

char* obterNomeVertice(grafo* g, int id_vertice) {
    vertice* verticePtr = g->vertices;
    while (verticePtr != NULL && verticePtr->id != id_vertice) {
        verticePtr = verticePtr->seguinte;
    }

    if (verticePtr != NULL) {
        return _strdup(verticePtr->nome);
    }

    return NULL;
}

void mostrarMeios(grafo* g, MeioEletrico* m, char** nomesVertices, int numVertices, const char* tipo_meio) {
    // Abrir arquivo em modo de leitura
    FILE* txt_file = fopen("meios.txt", "r");
   
    // Ler todos os meios para uma lista ligada
    MeioEletrico* head = NULL;
    MeioEletrico* curr = NULL;
    lerMeios(txt_file, &head);
    fclose(txt_file);

    printf("\nMeios disponiveis nos locais:\n\n");
    printf("ID | Nome      | Tipo      | Custo  | Bateria  | Local             | Reserva\n");

    // Verificar se o tipo_meio é "Bicicleta" ou "Trotinete"
    if (strcmp(tipo_meio, "Bicicleta") != 0 && strcmp(tipo_meio, "Trotinete") != 0) {
        printf("Tipo de meio inválido! Deve ser 'Bicicleta' ou 'Trotinete'.\n");
        return;
    }

    // Percorrer os nomes dos vizinhos encontrados
    for (int i = 0; i < numVertices; i++) {
        char* nomeVertice = nomesVertices[i];

        // Percorrer a lista de meios
        curr = head;
        while (curr != NULL) {
            // Comparar o nome do vizinho com o local_grafo do meio e o tipo
            if (strcmp(nomeVertice, curr->local_grafo) == 0 && strcmp(tipo_meio, curr->tipo) == 0) {
                // Meio encontrado no local vizinho e do tipo desejado, imprimir informações
                printf("---+-----------+-----------+--------+----------+-------------------+---------+\n");
                printf("%-3d| %-10s| %-10s| %-7.2f| %-9.2f| %-18s| %-6d\n",
                    curr->id, curr->tipo, curr->tipo, curr->custo, curr->carga_bateria, curr->local_grafo, curr->alugado);
            }
                curr = curr->proximo;  // Move to the next meio
        }
    }
}

void criarAresta(grafo* g) {
    int id_origem, id_destino, peso;
    g = carregarGrafo();
    imprimirVertices(g);

    // Obter as entradas do usuário
    printf("\nDigite o ID da localizacao de origem: ");
    scanf("%d", &id_origem);

    printf("Digite o ID da localizacao de destino: ");
    scanf("%d", &id_destino);

    // Verificar se os IDs de origem e destino existem nos vértices do grafo
    vertice* vertice_origem = buscarVertice(g, id_origem);
    vertice* vertice_destino = buscarVertice(g, id_destino);
    if (vertice_origem == NULL || vertice_destino == NULL) {
        printf("\nErro: IDs de origem e/ou destino invalidos.\n");
        getchar();
        return;
    }

    // Verificar se o ID de origem é igual ao ID de destino
    if (id_origem == id_destino) {
        printf("\nErro: O ID de origem nao pode ser igual ao ID de destino.\n");
        getchar();
        return;
    }

    printf("Digite a distancia: ");
    scanf("%d", &peso);

    // Criar uma nova aresta
    aresta* nova_aresta = (aresta*)malloc(sizeof(aresta));
    if (nova_aresta == NULL) {
        printf("Erro: Falha ao alocar memoria para a nova conexao.\n");
        return;
    }
    nova_aresta->id_origem = id_origem;
    nova_aresta->id_destino = id_destino;
    nova_aresta->peso = peso;
    nova_aresta->proxima = NULL;

    // Abrir o arquivo em modo de append
    FILE* arquivo = fopen("arestas.txt", "a");
    FILE* arquivo_bin = fopen("arestas.bin", "ab");

    if (arquivo == NULL || arquivo_bin == NULL) {
        printf("Erro: Falha ao abrir o arquivo.\n");
        free(nova_aresta);
        return;
    }

    // Escrever a aresta no arquivo
    fprintf(arquivo, "%d %d %d\n", nova_aresta->id_origem, nova_aresta->id_destino, nova_aresta->peso);
    fwrite(nova_aresta, sizeof(aresta), 1, arquivo_bin);

    // Fechar o arquivo
    fclose(arquivo);
    fclose(arquivo_bin);

    printf("\nConexao das localizacoes criada com sucesso!\n");
    getchar();
}

void salvarAresta(aresta* a) {
    // Salvar em arquivo de texto (.txt)
    FILE* arquivoTxt = fopen("arestas.txt", "w");
    FILE* arquivoBin = fopen("arestas.bin", "wb");
    if (arquivoTxt == NULL || arquivoBin == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }
    aresta* atualTxt = a;
    while (atualTxt != NULL) {
        fprintf(arquivoTxt, "%d %d %d\n", atualTxt->id_origem, atualTxt->id_destino, atualTxt->peso);
        atualTxt = atualTxt->proxima;
    }

    aresta* atualBin = a;
    while (atualBin != NULL) {
        fwrite(&atualBin->id_origem, sizeof(int), 1, arquivoBin);
        fwrite(&atualBin->id_destino, sizeof(int), 1, arquivoBin);
        fwrite(&atualBin->peso, sizeof(int), 1, arquivoBin);
        atualBin = atualBin->proxima;
    }
    fclose(arquivoTxt);
    fclose(arquivoBin);
}

void removerAresta(aresta* a) {
    a = carregarAresta();
    if (a == NULL) {
        printf("Erro: Lista de conexoes vazia.\n");
        getchar();
        return;
    }

    imprimirAresta(a);

    int id_origem, id_destino;
    printf("\nDigite o ID da localizacao de origem: ");
    scanf("%d", &id_origem);

    printf("\nDigite o ID da localizacao de destino: ");
    scanf("%d", &id_destino);

    aresta* anterior = NULL;
    aresta* atual = a;

    // Atravessa a lista para encontrar a aresta a ser removida
    while (atual != NULL) {
        if (atual->id_origem == id_origem && atual->id_destino == id_destino) {
            // Aresta encontrada, remove-a da lista 
            if (anterior == NULL) {
                a = atual->proxima;
            }
            else {
                anterior->proxima = atual->proxima;
            }

            // Liberta a memória ocupada pela aresta
            free(atual);
            printf("\nConexao removida com sucesso.\n");
            getchar();

            // Atualiza o ficheiro
            atualizarAresta(a);
            return;
        }
            anterior = atual;
            atual = atual->proxima;
    }

    printf("\nErro: Conexao nao encontrada.\n");
    getchar();
}

void imprimirAresta(aresta* a) {
    a = carregarAresta();
    printf("\nLista de conexoes:\n\n");
    aresta* atual = a;
    while (atual != NULL) {
        printf("Origem: %d, Destino: %d, Peso: %d\n", atual->id_origem, atual->id_destino, atual->peso);
        atual = atual->proxima;
    }
}

void atualizarAresta(aresta* a) {
    // Abrir o arquivo em modo de escrita
    FILE* arquivo = fopen("arestas.txt", "w");
    FILE* arquivo_bin = fopen("arestas.bin", "wb");

    if (arquivo == NULL || arquivo_bin == NULL) {
        printf("Erro: Falha ao abrir o arquivo.\n");
        return;
    }

    // Escreve as arestas da lista no ficheiro
    aresta* atual = a;
    while (atual != NULL) {
        fprintf(arquivo, "%d %d %d\n", atual->id_origem, atual->id_destino, atual->peso);
        fwrite(atual, sizeof(aresta), 1, arquivo_bin);
        atual = atual->proxima;
    }

    // Fecha o ficheiro
    fclose(arquivo);
    fclose(arquivo_bin);
}

void verConexoesRaio(grafo* g, aresta* a, MeioEletrico* m, int caller) {
    g = carregarGrafo();
    a = carregarAresta();
    imprimirVertices(g);

    int id_origem;
    float raio;
    int tipo_opcao;
    char tipo_meio[50];

    printf("\nDigite o ID onde se encontra: ");
    scanf("%d", &id_origem);

    printf("\nDigite o tipo de meio:\n\n");
    printf("1. Bicicleta\n");
    printf("2. Trotinete\n\n");
    scanf("%d", &tipo_opcao);

    if (tipo_opcao == 1) {
        strcpy(tipo_meio, "Carro");
    }
    else if (tipo_opcao == 2) {
        strcpy(tipo_meio, "Mota");
    }
  
    printf("\nDigite o raio de distancia: ");
    scanf("%f", &raio);

    printf("\nConexoes dentro do raio de %.2f a partir do ID %d:\n\n", raio, id_origem);

    if (caller == 0) {
        encontrarConexoes(g, a, m, id_origem, raio, tipo_meio, 0);
    }
    else if (caller == 1) {
        encontrarConexoes(g, a, m, id_origem, raio, tipo_meio, 1);
    }

    getchar();
}

void encontrarConexoes(grafo* g, aresta* a, MeioEletrico* m, int id_origem, float raio, const char* tipo_meio, int caller) {
    bool* visitados = calloc(g->num_vertices, sizeof(bool));
    float* distancias = malloc(g->num_vertices * sizeof(float));
    int* antecessores = malloc(g->num_vertices * sizeof(int));
    char** nomesVertices = malloc(g->num_vertices * sizeof(char*));
    int numVertices = 0;

    for (int i = 0; i < g->num_vertices; i++) {
        distancias[i] = FLT_MAX;
        antecessores[i] = -1;
    }

    distancias[id_origem] = 0.0;

    for (int count = 0; count < g->num_vertices - 1; count++) {
        int verticeAtual = -1;
        float menorDistancia = FLT_MAX;

        for (int v = 0; v < g->num_vertices; v++) {
            if (!visitados[v] && distancias[v] < menorDistancia) {
                verticeAtual = v;
                menorDistancia = distancias[v];
            }
        }

        if (verticeAtual == -1) {
            break;
        }

        visitados[verticeAtual] = true;

        for (aresta* arestaAtual = a; arestaAtual != NULL; arestaAtual = arestaAtual->proxima) {
            int idVizinho = -1;

            if (arestaAtual->id_origem == verticeAtual) {
                idVizinho = arestaAtual->id_destino;
            }
            else if (arestaAtual->id_destino == verticeAtual) {
                idVizinho = arestaAtual->id_origem;
            }

            if (idVizinho != -1) {
                float distanciaAcumulada = distancias[verticeAtual] + arestaAtual->peso;

                if (distanciaAcumulada <= raio && distanciaAcumulada < distancias[idVizinho]) {
                    distancias[idVizinho] = distanciaAcumulada;
                    antecessores[idVizinho] = verticeAtual;
                }
            }
        }
    }

  
    nomesVertices[numVertices] = obterNomeVertice(g, id_origem);
    numVertices++;

    printf("+----------+---------+-----------+-------------------+\n");
    printf("| Origem   | Destino | Distancia |       Caminho     |\n");
    printf("+----------+---------+-----------+-------------------+\n");

    for (int i = 0; i < g->num_vertices; i++) {
        if (i != id_origem && distancias[i] <= raio) {
            int destino = i;

            // Reconstruir o caminho percorrido
            int* caminho = malloc(g->num_vertices * sizeof(int));
            int index = 0;
            int atual = destino;

            while (atual != -1) {
                caminho[index++] = atual;
                atual = antecessores[atual];
            }

            // Imprimir a conexão
            imprimirConexao(id_origem, destino, distancias[destino], caminho, index);

            // Armazenar o nome do vértice vizinho
            nomesVertices[numVertices] = obterNomeVertice(g, i);
            numVertices++;
        }
    }

    if (caller == 0) {
        mostrarMeios(g, m, nomesVertices, numVertices, tipo_meio);
    }
    else if (caller == 1) {
        mostrarMeiosCliente(g, m, nomesVertices, numVertices, tipo_meio);
    }
}

void imprimirConexao(int id_origem, int destino, float distancia, int* caminho, int tamanho) {

    printf("| %8d | %7d | %9.2f | ", id_origem, destino, distancia);
    
    for (int i = tamanho - 1; i >= 0; i--) {
        printf("%d", caminho[i]);
        if (i > 0) {
            printf(" -> ");
        }
    }
        printf("\n");
        printf("+----------+---------+-----------+-------------------+\n");
    }







