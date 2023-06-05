#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include "structs.h"
#include "functions.c"
#include <stdlib.h>
#include <stdio.h> 
#include <float.h>
#include <stdbool.h>

void lerMeios(MeioEletrico **listaMeios);
void insereCliente(Cliente **listaClientes);
void insereGestor(Gestor **listaGestores);
void mostraClientes();
void mostragestores(Gestor **listaGestores);
void insereMeio(MeioEletrico **listaMeios);
void mostrarMeios();
void menuescolhasgestor();
void registraCliente(Cliente **listaClientes);
void remover_meio(MeioEletrico *listaMeios);
void remover_cliente(Cliente **listaClientes);
void loginGestor();
void loginCliente();
void alugarMeio(Cliente *cliente);
void listarMeiosPorAutonomia();







grafo* criarGrafo();
aresta* criarConexao();
grafo* carregarGrafo();
aresta* carregarAresta();
vertice* buscarVertice(grafo* g, int id);
void salvarGrafo(grafo* g);
void criarVertice(grafo* g);
void editarVertice(grafo* g);
void removerVertice(grafo* g);
void imprimirVertices(grafo* g);
void atualizarVertices(vertice* vertices);
char* obterNomeVertice(grafo* g, int id_vertice);
void mostrarMeios(grafo* g, MeioEletrico* m, char** nomesVertices, int numVertices, const char* tipo_meio);
void criarAresta(grafo* g);
void salvarAresta(aresta* a);
void removerAresta(aresta* a);
void imprimirAresta(aresta* a);
void atualizarAresta(aresta* a);
void verConexoesRaio(grafo* g, aresta* a, MeioEletrico* m, int caller);
void encontrarConexoes(grafo* g, aresta* a, MeioEletrico* m, int id_origem, float raio, const char* tipo_meio, int caller);
void imprimirConexao(int id_origem, int destino, float distancia, int* caminho, int tamanho);







#endif