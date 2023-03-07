
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int menuescolhas()
{
	int op;
	printf(" -------------------------------------------\n");
	printf("| 1 Inserir Meio                            |\n");
	printf("| 2 Listar Meios                            |\n");
	printf("| 3 Remover Meio                            |\n");
	printf("| 4 Guardar Meios                           |\n");
	printf("| 5 Ler Meios                               |\n");
	printf("| 0 Sair                                    |\n");
	printf(" -------------------------------------------\n");
	printf(" Opcao:\n");
	scanf("%d", &op);
	return(op);

}


int main()
{

	menuescolhas();


}