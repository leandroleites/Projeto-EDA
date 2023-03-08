
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "functions.h"
#include "structs.h"
int menuescolhas()
{
	int opc;
	printf(" -------------------------------------------\n");
	printf("| 1 Inserir Meio                            |\n");
	printf("| 2 Listar Meios                            |\n");
	printf("| 3 Remover Meio                            |\n");
	printf("| 4 Guardar Meios                           |\n");
	printf("| 5 Ler Meios                               |\n");
	printf("| 0 Sair                                    |\n");
	printf(" -------------------------------------------\n");
	printf(" Opcao: ");
	scanf("%d", &opc);
	return(opc);

}


int main()
{   
	
    int opc;
	int op1;
	do
	{
		opc=menuescolhas();
		switch(opc)
		{
          case 1: printf("\nDeseja inserir: \n 1- Meio \n 2- Cliente \n 3- Gestor\n");
		          printf(" Opcao: ");
				  scanf("%d",&op1);
				  switch (op1)
				  {
				  case 1:
					
					break;
				  case 2:
				    insereCliente(&listaClientes);
				  
				  default:
					break;
				  }
                  
				  break;
		}
	}
	while(opc!=0);

   
	
	return(0);
    


}