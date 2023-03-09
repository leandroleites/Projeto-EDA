#include <stdio.h>
#include <stdlib.h>
#include "functions.h"
#ifndef STRUCTS_H_INCLUDED
#define STRUCTS_H_INCLUDED

typedef struct MeioEletrico {
    int id;
    char tipo[20];
    int carga_bateria;
    float custo;
    char localizacao[20];
    struct MeioEletrico *proximo;
} MeioEletrico;

typedef struct Cliente {
    char nif[20];
    char nome[50];
    char morada[100];
    float saldo;
    struct Cliente *proximo;
} Cliente;

typedef struct Gestor {
    char nome[50];
    char email[50];
    struct Gestor *proximo;
} Gestor;







#endif