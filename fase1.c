
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "functions.h"

int main()
{   
	

    int opc;
	int op1;
	int opinicial;
	Cliente *listaClientes = NULL;
	MeioEletrico *listaMeios =NULL;
	printf("\nEscolha uma opcao:\n");
    printf(" --------------------------\n");
	printf("| 1- Login como Gestor     |\n");
	printf("| 2- Login como Cliente    |\n");
	printf("| 3- Registar como Cliente |\n");
    printf(" --------------------------\n\n");
    printf(" Opcao: ");
	scanf("%d",&opinicial);

    switch(opinicial)
	{
		case 1:
		 loginGestor();
		break;
		case 2:

		break;

		case 3:
		registraCliente(&listaClientes);

		break;
		default:
		break;
	}




	

   
	
	return(0);
    


}