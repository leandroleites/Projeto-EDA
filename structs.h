#include <stdio.h>

typedef struct {
    int id;
    char tipo[20];
    int cargabateria;
    float custo;
    char localizacao[20];
} meioeletrico;

typedef struct {
    char nif[20];
    char nome[50];
    char morada[100];
    float saldo;
} Cliente;

typedef struct {
    int id;
    char nome[50];
} Gestor;