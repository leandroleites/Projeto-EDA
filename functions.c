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


void alugarMeio(Cliente *cliente) {
    FILE *arquivo;
    MeioEletrico *meios = NULL, *meio_atual;
    char linha[150], *token;
    int meio_id, encontrou_meio = 0;
    float custo_meio;
    // Abrir arquivo de meios
    arquivo = fopen("meios.txt", "r");
    if (arquivo == NULL) {
    printf("\nErro ao abrir o arquivo de meios.\n");
    return;
    }

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
        meio_atual->proximo = meios;
        meios = meio_atual;
    }
    fclose(arquivo);

// Mostrar lista de meios disponíveis para o cliente
  // Imprimir lista de meios disponíveis
    printf("\nLista de meios disponiveis:\n\n");
    meio_atual = meios;
    while (meio_atual != NULL) {
        if (meio_atual->carga_bateria > 0) {
            printf("ID: %d\nTipo: %s\nCarga da bateria: %d%%\nCusto: %.2f€\nLocalizacao: %s\n\n", meio_atual->id, meio_atual->tipo, meio_atual->carga_bateria, meio_atual->custo, meio_atual->localizacao);
        }
        meio_atual = meio_atual->proximo;
    }

// Pedir ao cliente para selecionar um meio para alugar
    printf("Digite o ID do meio que deseja alugar: ");
    scanf("%d", &meio_id);

// Procurar o meio selecionado na lista de meios
meio_atual = meios;
while (meio_atual != NULL) {
  if (meio_atual->id == meio_id && meio_atual->alugado == 0) {
    // Meio encontrado e disponível para aluguel
  
       
   
     
    // Marcar o meio como alugado
    meio_atual->alugado = 1;
    printf("\nMeio alugado com sucesso!\n");
    printf("Tipo: %s\n", meio_atual->tipo);
    printf("Custo: %.2f\n", meio_atual->custo);
    printf("Localizacao: %s\n", meio_atual->localizacao);
    printf("\n");
    return;
}
   meio_atual = meio_atual->proximo;
}

// Meio não encontrado ou já alugado
printf("\nMeio nao encontrado ou ja alugado.\n");
return;
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


