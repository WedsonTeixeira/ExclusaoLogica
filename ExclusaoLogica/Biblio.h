typedef struct
{
    int Dia;
    int Mes;
    int Ano;
}Data;

typedef struct
{
    char CPF[15];
    char Nome[30];
    int Telefone;
    Data DataCompra;
    float ValorCompra;
    char StatusCliente;
}Cliente;

void MensagemErroArquivo()
{
    system("cls");
    printf("ERRO DE ARQUIVO!\n");
    system("pause");
}

void PegarData(Data *Nova)
{
    time_t Tempo;
    struct tm * Date;

    time(&Tempo);
    Date = localtime(&Tempo);

    Nova->Dia = Date->tm_mday;
    Nova->Mes = Date->tm_mon+1;
    Nova->Ano = Date->tm_year+1900;
}

void DataParaChar(char *VetorData, Data *Nova)
{
    char ANO[5];
    char MES[3];
    char DIA[3];

    itoa(Nova->Ano,ANO,10);
    itoa(Nova->Mes,MES,10);
    itoa(Nova->Dia,DIA,10);

    strcpy(VetorData,ANO);

    if(Nova->Mes<10)
    {
        strcat(VetorData,"0");
        strcat(VetorData,MES);
    }
    else
    {
        strcat(VetorData,MES);
    }
    if(Nova->Dia<10)
    {
        strcat(VetorData,"0");
        strcat(VetorData,DIA);
    }
    else
    {
        strcat(VetorData,DIA);
    }
}

void CadastrarCliente()
{
    FILE *Gravar = fopen("Clientes.dat","ab");
    if(Gravar == NULL)
    {
        MensagemErroArquivo();
    }
    else
    {
        Cliente Novo;

        fflush(stdin);
        system("cls");
        printf("\t\tCADASTRO DE CLIENTES\n\n");

        printf("CPF DO CLIENTE......: ");
        gets(Novo.CPF);

        printf("NOME DO CLIENTE.....: ");
        gets(Novo.Nome);

        printf("TELEFONE DO CLIENTE.: ");
        scanf("%d", &Novo.Telefone);

        PegarData(&Novo.DataCompra);

        printf("VALOR DA COMPRA.....: ");
        scanf("%f", &Novo.ValorCompra);

        Novo.StatusCliente = '1';

        fwrite(&Novo, sizeof(Cliente), 1, Gravar);
        fclose(Gravar);

        fflush(stdin);
        printf("\nCliente Cadastrado Com Sucesso.\n\n");
        system("pause");
    }
}

void MostrarClientes()
{
    FILE *Ler = fopen("Clientes.dat","rb");
    if(Ler == NULL)
    {
        MensagemErroArquivo();
    }
    else
    {
        system("cls");
        printf("\t\tTABELA DE CLIENTES\n\n");

        Cliente Existente;
        while(fread(&Existente, sizeof(Cliente), 1, Ler) == 1)
        {
            printf("CPF DO CLIENTE......: %s\n", Existente.CPF);
            printf("NOME DO CLIENTE.....: %s\n", Existente.Nome);
            printf("TELEFONE DO CLIENTE.: %d\n", Existente.Telefone);
            printf("DATA COMPRA.........: %d/%d/%d\n", Existente.DataCompra.Dia, Existente.DataCompra.Mes, Existente.DataCompra.Ano);
            printf("VALOR DO PRODUTO....: %.2f\n", Existente.ValorCompra);
            printf("STATUS DO CLIENTE...: %s\n\n", Existente.StatusCliente == '1'? "Ativo":"Inativo");

        }
        fclose(Ler);
        system("pause");
    }
}

void ExclusaoLogica()
{
    FILE *LerGravar = fopen("Clientes.dat","r+b");

    if(LerGravar == NULL)
    {
        MensagemErroArquivo();
    }
    else
    {
        Cliente Existente;
        Data DataAtual;
        char CmpData1[9];
        char CmpData2[9];
        int Indice = 0;
        int QuantidadeDeInativos = 0;

        PegarData(&DataAtual);
        DataAtual.Ano = DataAtual.Ano-1;
        DataParaChar(CmpData1,&DataAtual);

        while(fread(&Existente, sizeof(Cliente), 1, LerGravar) == 1)
        {
            DataParaChar(CmpData2,&Existente.DataCompra);

            if(strcmp(CmpData1,CmpData2) > 0 && Existente.StatusCliente == '1')
            {
                Existente.StatusCliente = '0';

                fseek(LerGravar,sizeof(Cliente)*Indice, SEEK_SET);
                fwrite(&Existente, sizeof(Cliente), 1, LerGravar);
                fseek(LerGravar,sizeof(Cliente)*(Indice+1), SEEK_SET);
                QuantidadeDeInativos = QuantidadeDeInativos + 1;
            }
            Indice = Indice + 1;
        }
        fclose(LerGravar);

        system("cls");
        printf("\t\tEXCLUSÃO LÓGICA DE CLIENTES\n\n");
        printf("Quantidade de Clientes Que ficaram Inativos: %d\n\n", QuantidadeDeInativos);
        system("pause");
    }
}

void AlterarDados()
{
    FILE *LereGravar = fopen("Clientes.dat","r+b");
    if(LereGravar == NULL)
    {
        MensagemErroArquivo();
    }
    else
    {
        char CPFAux[15];
        int Indice = 0;
        int Flag = 0;

        fflush(stdin);
        system("cls");
        printf("\t\tPESQUISAR CLIENTE\n\n");

        printf("INFORME O CPF.......: ");
        gets(CPFAux);

        Cliente Existente;
        while(fread(&Existente, sizeof(Cliente), 1, LereGravar) == 1)
        {
            if(strcmp(CPFAux,Existente.CPF) == 0)
            {
                Flag = 1;
                printf("NOME DO CLIENTE.....: ");
                gets(Existente.Nome);

                printf("TELEFONE DO CLIENTE.: ");
                scanf("%d", &Existente.Telefone);

                Existente.StatusCliente = '1';

                fseek(LereGravar,sizeof(Cliente)*Indice, SEEK_SET);
                fwrite(&Existente, sizeof(Cliente), 1, LereGravar);
                fseek(LereGravar,sizeof(Cliente)*(Indice+1), SEEK_SET);
                printf("\nCliente Atualizado Com Sucesso.\n\n");
            }
            Indice = Indice+1;
        }
        fclose(LereGravar);
        if(Flag == 0)
        {
            printf("\nCliente não encontrado!\n\n");
        }
        system("pause");
    }
}
