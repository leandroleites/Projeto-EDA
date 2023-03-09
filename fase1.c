
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "functions.h"


int menuescolhas()
{
	int opc;
	printf(" -------------------------------------------\n");
	printf("| 1 Inserir novos dados                     |\n");
	printf("| 2 Listar dados                            |\n");
	printf("| 3 Remover dados                           |\n");
	printf("| 4 Guardar dados                           |\n");
	printf("| 5 Ler dados                               |\n");
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
	Cliente *listaClientes = NULL;
	MeioEletrico *listaMeios =NULL;
	
	do
	{
		opc=menuescolhas();
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
				    
				  default:
					break;
				  }
                  
				  break;
		  case 2: printf("\nDeseja listar: \n\n");
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
					mostraMeios(&listaMeios);
					break;
				  case 2:
				     mostraClientes(listaClientes);
				  break;

				  case 3:

				  break;
				  default:
					break;
				  }
		}
	}
	while(opc!=0);

   
	
	return(0);
    


}