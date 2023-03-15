#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include "structs.h"
#include "functions.c"
#include <stdlib.h>
#include <stdio.h> 

void insereCliente(Cliente **listaClientes);
void insereGestor(Gestor **listaGestores);
void mostraClientes(Cliente *listaClientes);

void insereMeio(MeioEletrico **listaMeios);
void mostraMeios(MeioEletrico **listaMeios);

void menuescolhasgestor();

void registraCliente(Cliente **listaClientes);
void loginGestor();
#endif