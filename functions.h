#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include "structs.h"
#include "functions.c"
#include <stdlib.h>
#include <stdio.h> 

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

#endif