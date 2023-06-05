#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include <stdbool.h>
#include "functions.h"
#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

typedef struct MeioEletrico {
    int id;
    char tipo[20];
    int carga_bateria;
    float custo;
    char localizacao[50];
    char local_grafo[50];
    int alugado;
    struct MeioEletrico *proximo;
} MeioEletrico;

typedef struct Cliente {
    char nome[50];
    char morada[100];
    char nif[20];
    char email[50];
    char pass[50];
    
    
    float saldo;
    struct Cliente *proximo;
} Cliente;

typedef struct Gestor {
    int id;
    char nome[50];
    char email[50];
    char pass[50];
    struct Gestor *proximo;
} Gestor;


typedef struct aresta {
    int id_origem;      // id do vértice de origem
    int id_destino;     // id do vértice de destino
    int peso;
    struct aresta* proxima;
} aresta;

typedef struct vertice {
    int id;
    char nome[50];
    char local_meio[50];
    MeioEletrico* meios;
    aresta* arestas; 
    struct vertice* seguinte;
} vertice;

typedef struct grafo {
    int num_vertices;
    int num_arestas;
    vertice* vertices;
} grafo;




#endif