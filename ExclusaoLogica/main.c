#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <string.h>
#include "Biblio.h"

int main()
{
    setlocale(LC_ALL,"Portuguese");
    int Opcao;

    do
    {
        system("cls");
        printf("\t\tVENDE TUDO MAIS BARATO\n\n");
        printf("1 - Novo Cliente\n");
        printf("2 - Mostrar Clientes\n");
        printf("3 - Exclusão Lógica\n");
        printf("4 - Alterar Dados\n");
        printf("5 - Sair\n\n");
        printf("Informe a Opção: ");
        scanf("%d", &Opcao);

        switch(Opcao)
        {
        case 1:
            CadastrarCliente();
            break;
        case 2:
            MostrarClientes();
            break;
        case 3:
            ExclusaoLogica();
            break;
        case 4:
            AlterarDados();
            break;
        }
    }
    while(Opcao != 5);
}
