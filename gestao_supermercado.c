#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

void incluir(void);
void listar(void);
void consultar(void);
void alterar(void);
void excluir(void);
void sair(void);

void main(void)
{
	setlocale(LC_ALL, "Portuguese");
	int opcao;
	do
	{
		do
		{
			system("cls");
			printf("\n\n\n\n\n\n\n");
			printf("\t########################################################\n");
			printf("\t#                                                      #\n");
			printf("\t#                     SuperMercardo                    #\n");
			printf("\t#                   Gestão de Estoque                  #\n");
			printf("\t#                                                      #\n");
			printf("\t########################################################\n\n\n");
			printf("\n Digite uma das opcoes\n\n");
			printf("\n 1 - Incluir");
			printf("\n 2 - Alterar");
			printf("\n 3 - Excluir");
			printf("\n 4 - Consultar");
			printf("\n 5 - Listar");
			printf("\n 6 - Sair");
			printf("\n\n\n Opcao: ");
			scanf("%d", &opcao);
		} while (opcao < 1 || opcao > 6);
		switch (opcao)
		{
		case 1:
			incluir();
			break;
		case 2:
			alterar();
			break;
		case 3:
			excluir();
			break;
		case 4:
			consultar();
			break;
		case 5:
			listar();
			break;
		case 6:
			sair();
			break;
		}
	} while (1);
}

void incluir()
{
	char produto[4][20], produto1[4][20], nome[4][20] = {"o código", "a descrição", "o valor", "a quantidade"};
	int escolha, i, quantidade_produto = 0;

	FILE *fp;
	fp = fopen("produtos.txt", "r+"); // Abre o arquivo produtos.txt
	if (fp == NULL)
	{									  // Caso não tenha nenhum arquivo
		fp = fopen("produtos.txt", "w+"); // Cria um novo arquivo produtos.txt
		fclose(fp);
		return;
	}
	fclose(fp);

	for (i = 0; i < 4; i++)
	{
		printf("Digite %s  do produto: ", nome[i]); // Vai receber os valores do item
		scanf("%s", &produto[i]);
	}
	fp = fopen("produtos.txt", "r"); // Abre o arquivo produtos.txt
	while (fscanf(fp, "%s  %s  %s  %s", &produto1[0], &produto1[1], &produto1[2], &produto1[3]) != EOF)
	{ // Verifica se o codigo do produto ja foi cadastrado percorrendo por todo o arquivo Enquanto não estiver no fim do arquivo,
		if (strcmp(produto1[0], produto[0]) == 0)
		{
			quantidade_produto++;
		}
	}

	if (quantidade_produto > 0) // Se existir um produto com o mesmo código
	{
		printf("Código já cadastrado! digite: \n1 - para continuar cadastro \n2 - para alterar cadastro existente");
		scanf("%d", &escolha);
		while (escolha < 1 || escolha > 2) // Pede para escolher entre
		{
			printf("Opçãoo invalida! digite: \n1 - para continuar cadastro \n2 - para alterar cadastro existente");
			scanf("%d", &escolha);
			system("cls");
		}
		switch (escolha)
		{
		case 1:
			fclose(fp);
			fopen("produtos.txt", "a");
			fprintf(fp, "%s  %s  %s  %s ", produto[0], produto[1], produto[2], produto[3]);
			fclose(fp);
			printf("produto cadastrado com sucesso!");
			Sleep(5000);
			break;
		case 2:
			fclose(fp);
			alterar();
			break;
		}
	}
	else
	{
		fclose(fp);
		fopen("produtos.txt", "a");
		fprintf(fp, "%s  %s  %s  %s ", produto[0], produto[1], produto[2], produto[3]);
		fclose(fp);
	}
}

void listar()
{ // Listar todos os items
	char produto[4][20], quantidade_produto;
	FILE *fp;
	fp = fopen("produtos.txt", "r+");
	if (fp == NULL)
	{ // Caso não ache nenhum arquivo chamado produtos.txt, retorna ao menu
		printf("Arquivo inexistente!");
		return;
	}

	while (fscanf(fp, "%s  %s  %s  %s", &produto[0], &produto[1], &produto[2], &produto[3]) != EOF) // Percorre todo o arquivo
	{
		printf("Cod: %s --- Descricao: %s --- valor: %s --- quantidade: %s\n", produto[0], produto[1], produto[2], produto[3]); // E printa eles
	}
	fclose(fp);
	system("pause");
}

void consultar() // Consulta o produto de pelo codigo ou pelo nome
{
	char produto[4][20], codigo[20];
	int escolha = 0, quantidade_produto = 0;
	FILE *fp = fopen("produtos.txt", "r"); // Abre o arquivo
	if (fp == NULL) // Caso retorne NULL
	{
		printf("Arquivo inexistente!");
		return;  // Retorna ao menu
	}
	while (escolha < 1 || escolha > 2)  // Enquanto a opção não for 1 ou 2
	{
		printf("Digite:\n 1 - para usar o código\n 2 - para usar a descrição   ");
		scanf("%d", &escolha);
		system("cls");
	}
	switch (escolha)
	{
		case 1:
			printf("Digite o Código do Produto: ");
			scanf("%s", &codigo);
			break;
		case 2:
			printf("Digite o nome do Produto: ");
			scanf("%s", &codigo);
			break;
	}
	while (fscanf(fp, "%s  %s  %s  %s", &produto[0], &produto[1], &produto[2], &produto[3]) != EOF) // Percorre linha por linha até o fim do código
	{
		if (escolha == 1) // Caso deseja consultar pelo código, irá comparar linha por linha até achar um código igual ao do produto desejado
		{
			if (strcmp(produto[0], codigo) == 0)
			{
				printf("Cod: %s --- Descricao: %s --- valor: %s --- quantidade: %s\n", produto[0], produto[1], produto[2], produto[3]);
				quantidade_produto++;
			}
		}
		else // Caso deseja consultar pelo nome do produto, irá comparar linha por linha até achar o nome do produto igual ao do produto desejado
		{
			if (strcmp(produto[1], codigo) == 0)
			{
				printf("Cod: %s --- Descricao: %s --- valor: %s --- quantidade: %s\n", produto[0], produto[1], produto[2], produto[3]);
				quantidade_produto++;
			}
		}
	}
	if (quantidade_produto == 0) // Se não for encontrado nenhum produto, vai perguntar se quer ver todos os produtos
	{
		printf("produto não encontrado! \nDeseja ver todos os produtos cadastrados? \n1 - Sim \n2 - não");
		scanf("%d", &escolha);
		if (escolha == 1)
		{
			listar();
		}
	}
	system("pause");
}

void alterar() // Alterar 
{
	char produto[4][20], codigo1[20], descricao1[20], valor1[20], quantidade1[20], newcodigo[20], newdescricao[20], newvalor[20], newquantidade[20];
	int escolha1, escolha2, quantidade_produto = 0, posicao_cursor;
	FILE *fp, *fp1;

	fp = fopen("produtos.txt", "r"); // Abre o arquivo de produtos para leitura
	if (fp == NULL) // Caso não exista, irá retornar para o menu
	{
		printf("Arquivo inexistente!");
		return;
	}
	fclose(fp);
	printf("Digite o que deseja Alterar: \n1 - código \n2 - Descrição \n3 - Valor \n4 - quantidade: \nescolha:");
	scanf("%d", &escolha1);
	switch (escolha1)
	{
	case 1: // Alterar código
		fp = fopen("produtos.txt", "r+"); // Abrindo o arquivo para alteração
		printf("Digite o código do produto que deseja alterar:"); // Obtêm o codigo do produto para alterar o codigo do produto
		scanf("%s", &codigo1);
		while (fscanf(fp, "%s  %s  %s  %s", &produto[0], &produto[1], &produto[2], &produto[3]) != EOF) // Percorre todas as linhas em busca do produto com o codigo informado
		{
			if (strcmp(produto[0], codigo1) == 0)
			{
				printf("Cod: %s --- Descricao: %s --- marca: %s --- quantidade: %s\n", produto[0], produto[1], produto[2], produto[3]);
				quantidade_produto++;
			}
		}
		fclose(fp);
		if (quantidade_produto > 1) // Caso exista mais de um produto com o codigo informado
		{
			printf("Deseja alterar o código de todos os produtos acima? \n1 - sim \n2 - não"); // Confirma se quer alterar ou não o código dos produtos
			scanf("%d", &escolha2);
			while (escolha2 < 1 || escolha2 > 2) // Enquanto a escolha não for válida
			{
				printf("Opção Invalida!");
				printf("Deseja mesmo alterar o código atual? \n1 - sim \n2 - não");
				scanf("%d", &escolha2);
			}
			if (escolha2 == 1) // Se for sim,
			{
				printf("Digite o novo codigo do produto: "); // Pede o novo código do produto
				scanf("%s", &newcodigo);
				fp = fopen("produtos.txt", "r+"); // Abre o arquivo para a leitura
				fp1 = fopen("produtos2.txt", "w+"); // Cria e abre o arquivo secundario para a alteração
				while (fscanf(fp, "%s  %s  %s  %s", &produto[0], &produto[1], &produto[2], &produto[3]) != EOF) // Percorre a base de produtos principal toda
				{
					if (strcmp(produto[0], codigo1) == 0) // E procura o código do produto para alteração e escreve no arquivo secundario
					{
						fprintf(fp1, "%s  %s  %s  %s ", newcodigo, produto[1], produto[2], produto[3]); 
					}
					else
					{
						fprintf(fp1, "%s  %s  %s  %s ", produto[0], produto[1], produto[2], produto[3]);
					}
				}
				fclose(fp);
				fclose(fp1);
				fp1 = fopen("produtos2.txt", "r+"); // Abre os dois arquivos produtos
				fp = fopen("produtos.txt", "w+"); 	// porem, apenas o principal para alteração.
				while (fscanf(fp1, "%s  %s  %s  %s", &produto[0], &produto[1], &produto[2], &produto[3]) != EOF) // percorre todo o arquivo secundario e escreve por cima do principal, alterando o codigo do produto desejado
				{
					fprintf(fp, "%s  %s  %s  %s ", produto[0], produto[1], produto[2], produto[3]);
				}
				fclose(fp1);
				fclose(fp);
			}
			else
			{
				printf("Digite a descriçãoo do produto que deseja alterar o código:"); // Pede a descrição do produto para especificar qual dos produtos que deseja alterar o codigo
				scanf("%s", &descricao1);
				printf("Digite o novo codigo do produto: "); // Pede o novo codigo para a alteração
				scanf("%s", &newcodigo);
				fp = fopen("produtos.txt", "r+"); 
				fp1 = fopen("produtos2.txt", "w+");
				while (fscanf(fp, "%s  %s  %s  %s", &produto[0], &produto[1], &produto[2], &produto[3]) != EOF) // Percorre todos os produtos e cria uma copia com a alteração feita no fp1
				{
					if (strcmp(produto[0], codigo1) == 0 && strcmp(produto[1], descricao1) == 0)
					{
						fprintf(fp1, "%s  %s  %s  %s ", newcodigo, produto[1], produto[2], produto[3]);
					}
					else
					{
						fprintf(fp1, "%s  %s  %s  %s ", produto[0], produto[1], produto[2], produto[3]);
					}
				}
				fclose(fp);
				fclose(fp1);
				fp1 = fopen("produtos2.txt", "r+");
				fp = fopen("produtos.txt", "w+");
				while (fscanf(fp1, "%s  %s  %s  %s", &produto[0], &produto[1], &produto[2], &produto[3]) != EOF) // Percorre por todos os produtos do arquivo copia
				{
					fprintf(fp, "%s  %s  %s  %s ", produto[0], produto[1], produto[2], produto[3]); // Escreve no arquivo de produtos principal os produtos já alterados.
				}
				fclose(fp1);
				fclose(fp);
			}
		}
		else if (quantidade_produto == 1) // Caso exista apenas 1 produto com o código informado
		{
			printf("Digite o novo codigo do produto: "); // Pede o novo codigo do produto
			scanf("%s", &newcodigo);
			fp = fopen("produtos.txt", "r+"); 
			fp1 = fopen("produtos2.txt", "w+"); // Cria um arquivo temporario
			while (fscanf(fp, "%s  %s  %s  %s", &produto[0], &produto[1], &produto[2], &produto[3]) != EOF) // Percorre todos os produtos do arquivo principal 
			{
				if (strcmp(produto[0], codigo1) == 0) // Procura o codigo do produto que vai ser alterado e escreve no temporario
				{
					fprintf(fp1, "%s  %s  %s  %s ", newcodigo, produto[1], produto[2], produto[3]);
				}
				else
				{
					fprintf(fp1, "%s  %s  %s  %s ", produto[0], produto[1], produto[2], produto[3]);
				}
			}
			fclose(fp);
			fclose(fp1);
			fp1 = fopen("produtos2.txt", "r+");
			fp = fopen("produtos.txt", "w+");
			while (fscanf(fp1, "%s  %s  %s  %s", &produto[0], &produto[1], &produto[2], &produto[3]) != EOF) // Escreve por cima do arquivo principal os dados alterados do arquivo temporario
			{
				fprintf(fp, "%s  %s  %s  %s ", produto[0], produto[1], produto[2], produto[3]);
			}
			fclose(fp1);
			fclose(fp);
		}
		else // Caso não exista um produto com o código informado
		{
			printf("Produto não encontrado, verifique novamente:");
			Sleep(2000);
		}
		break;
	case 2: // Alterar descrição
		fp = fopen("produtos.txt", "r+");
		printf("Digite o código do produto que deseja alterar:"); // Pede o codigo do produto 
		scanf("%s", &codigo1);
		while (fscanf(fp, "%s  %s  %s  %s", &produto[0], &produto[1], &produto[2], &produto[3]) != EOF) // Percorre por todos os produtos
		{
			if (strcmp(produto[0], codigo1) == 0) // Acha o produto com o codigo informado
			{
				printf("Cod: %s --- Descricao: %s --- valor: %s --- quantidade: %s\n", produto[0], produto[1], produto[2], produto[3]);
				quantidade_produto++;
			}
		}
		fclose(fp);
		if (quantidade_produto > 1) // Caso tenha mais de um produto 
		{
			printf("Deseja mesmo alterar a descrição atual de todos produtos acima? \n1 - sim \n2 - não"); // Pede confirmação para alterar o nome de todos os produtos
			scanf("%d", &escolha2);
			while (escolha2 < 1 || escolha2 > 2) // Pede confirmação até que tenha uma opção válida.
			{
				printf("Opção Invalida!");
				printf("Deseja mesmo alterar a descrição atual? \n1 - sim \n2 - não");
				scanf("%d", &escolha2);
			}
			if (escolha2 == 1) // Caso sim,
			{
				printf("Digite a nova descrição do produto: "); // Pede uma nova descrição
				scanf("%s", &newdescricao);
				fp = fopen("produtos.txt", "r+");
				fp1 = fopen("produtos2.txt", "w+");
				while (fscanf(fp, "%s  %s  %s  %s", &produto[0], &produto[1], &produto[2], &produto[3]) != EOF) // Percorre por todo arquivo dos produtos
				{
					if (strcmp(produto[0], codigo1) == 0) // Procura o codigo do produto que vai ser alterado e escreve no arquivo temporario
					{
						fprintf(fp1, "%s  %s  %s  %s ", produto[0], newdescricao, produto[2], produto[3]);
					}
					else
					{
						fprintf(fp1, "%s  %s  %s  %s ", produto[0], produto[1], produto[2], produto[3]);
					}
				}
				fclose(fp);
				fclose(fp1);
				fp1 = fopen("produtos2.txt", "r+");
				fp = fopen("produtos.txt", "w+");
				while (fscanf(fp1, "%s  %s  %s  %s", &produto[0], &produto[1], &produto[2], &produto[3]) != EOF) // Percorre o arquivo temporario e escreve uma copia no arquivo principal
				{
					fprintf(fp, "%s  %s  %s  %s ", produto[0], produto[1], produto[2], produto[3]);
				}
				fclose(fp1);
				fclose(fp);
			}
			else // Caso não, 
			{
				printf("Digite a descrição do produto que deseja alterar:"); // Pede para ser mais especifico, pedindo a descrição 
				scanf("%s", &descricao1);
				printf("Digite a nova descrição: "); // pede a nova descrição
				scanf("%s", &newdescricao);
				fp = fopen("produtos.txt", "r+");
				fp1 = fopen("produtos2.txt", "w+");
				while (fscanf(fp, "%s  %s  %s  %s", &produto[0], &produto[1], &produto[2], &produto[3]) != EOF) // Percorre o arquivo principal dos produtos 
				{
					if (strcmp(produto[0], codigo1) == 0 && strcmp(produto[1], descricao1) == 0) // cria uma copia do arivo principal com a alteração feita
					{
						fprintf(fp1, "%s  %s  %s  %s ", produto[0], newdescricao, produto[2], produto[3]);
					}
					else
					{
						fprintf(fp1, "%s  %s  %s  %s ", produto[0], produto[1], produto[2], produto[3]);
					}
				}
				fclose(fp);
				fclose(fp1);
				fp1 = fopen("produtos2.txt", "r+"); 
				fp = fopen("produtos.txt", "w+");
				while (fscanf(fp1, "%s  %s  %s  %s", &produto[0], &produto[1], &produto[2], &produto[3]) != EOF) // Percorre o arquivo temporário
				{
					fprintf(fp, "%s  %s  %s  %s ", produto[0], produto[1], produto[2], produto[3]); // e sobrescreve o arquivo principal.
				}
				fclose(fp1);
				fclose(fp);
			}
		}
		else if (quantidade_produto == 1) // caso tenha apenas um produto 
		{
			printf("Digite a nova descrição: "); // Pede uma nova descrição
			scanf("%s", &newdescricao);
			fp = fopen("produtos.txt", "r+");
			fp1 = fopen("produtos2.txt", "w+");
			while (fscanf(fp, "%s  %s  %s  %s", &produto[0], &produto[1], &produto[2], &produto[3]) != EOF) // Percorre por todo arquivo dos produtos
			{
				if (strcmp(produto[0], codigo1) == 0) // Procura o codigo do produto que vai ser alterado e escreve no arquivo temporario
				{
					fprintf(fp1, "%s  %s  %s  %s ", produto[0], newdescricao, produto[2], produto[3]); 
				}
				else
				{
					fprintf(fp1, "%s  %s  %s  %s ", produto[0], produto[1], produto[2], produto[3]);
				}
			}
			fclose(fp);
			fclose(fp1);
			fp1 = fopen("produtos2.txt", "r+");
			fp = fopen("produtos.txt", "w+");
			while (fscanf(fp1, "%s  %s  %s  %s", &produto[0], &produto[1], &produto[2], &produto[3]) != EOF) // Percorre o arquivo temporario e escreve uma copia no arquivo principal
			{
				fprintf(fp, "%s  %s  %s  %s ", produto[0], produto[1], produto[2], produto[3]);
			}
			fclose(fp1);
			fclose(fp);
		}
		else // Caso não tenha encontrado nenhum produto
		{
			printf("Produto não encontrado, verifique novamente:");
			Sleep(2000);
		}
		break;

	case 3: // Alterar o valor
		fp = fopen("produtos.txt", "r+");
		printf("Digite o código do produto que deseja alterar:"); // Pede o código do produto que deseja alterar
		scanf("%s", &codigo1);
		while (fscanf(fp, "%s  %s  %s  %s", &produto[0], &produto[1], &produto[2], &produto[3]) != EOF) // Percorre por todo arquivo de produtos
		{
			if (strcmp(produto[0], codigo1) == 0) // Procura um produto que tenha o mesmo codigo informado
			{
				printf("Cod: %s --- Descricao: %s --- valor: %s --- quantidade: %s\n", produto[0], produto[1], produto[2], produto[3]);
				quantidade_produto++;
			}
		}
		fclose(fp);
		if (quantidade_produto > 1) // Caso tenha mais de um produto
		{
			printf("Deseja mesmo alterar a marca de todos os produtos acima? \n1 - sim \n2 - não"); // Pede uma confirmação se quer alterar todos de uma vez
			scanf("%d", &escolha2);
			while (escolha2 < 1 || escolha2 > 2)
			{
				printf("Opção Invalida!");
				printf("Deseja mesmo alterar o código atual? \n1 - sim \n2 - não");
				scanf("%d", &escolha2);
			}
			if (escolha2 == 1)
			{
				printf("Digite o novo valor do produto: ");
				scanf("%s", &newvalor);
				fp = fopen("produtos.txt", "r+");
				fp1 = fopen("produtos2.txt", "w+");
				while (fscanf(fp, "%s  %s  %s  %s", &produto[0], &produto[1], &produto[2], &produto[3]) != EOF)
				{
					if (strcmp(produto[0], codigo1) == 0)
					{
						fprintf(fp1, "%s  %s  %s  %s ", produto[0], produto[1], newvalor, produto[3]);
					}
					else
					{
						fprintf(fp1, "%s  %s  %s  %s ", produto[0], produto[1], produto[2], produto[3]);
					}
				}
				fclose(fp);
				fclose(fp1);
				fp1 = fopen("produtos2.txt", "r+");
				fp = fopen("produtos.txt", "w+");
				while (fscanf(fp1, "%s  %s  %s  %s", &produto[0], &produto[1], &produto[2], &produto[3]) != EOF)
				{
					fprintf(fp, "%s  %s  %s  %s ", produto[0], produto[1], produto[2], produto[3]);
				}
				fclose(fp1);
				fclose(fp);
			}
			else
			{
				printf("Digite a descrição do produto que deseja alterar:");
				scanf("%s", &descricao1);
				printf("Digite a nova marca: ");
				scanf("%s", &newvalor);
				fp = fopen("produtos.txt", "r+");
				fp1 = fopen("produtos2.txt", "w+");
				while (fscanf(fp, "%s  %s  %s  %s", &produto[0], &produto[1], &produto[2], &produto[3]) != EOF)
				{
					if (strcmp(produto[0], codigo1) == 0 && strcmp(produto[1], descricao1) == 0)
					{
						fprintf(fp1, "%s  %s  %s  %s ", produto[0], produto[1], newvalor, produto[3]);
					}
					else
					{
						fprintf(fp1, "%s  %s  %s  %s ", produto[0], produto[1], produto[2], produto[3]);
					}
				}
				fclose(fp);
				fclose(fp1);
				fp1 = fopen("produtos2.txt", "r+");
				fp = fopen("produtos.txt", "w+");
				while (fscanf(fp1, "%s  %s  %s  %s", &produto[0], &produto[1], &produto[2], &produto[3]) != EOF)
				{
					fprintf(fp, "%s  %s  %s  %s ", produto[0], produto[1], produto[2], produto[3]);
				}
				fclose(fp1);
				fclose(fp);
			}
		}
		else if (quantidade_produto == 1)
		{
			printf("Digite a nova marca: ");
			scanf("%s", &newvalor);
			fp = fopen("produtos.txt", "r+");
			fp1 = fopen("produtos2.txt", "w+");
			while (fscanf(fp, "%s  %s  %s  %s", &produto[0], &produto[1], &produto[2], &produto[3]) != EOF)
			{
				if (strcmp(produto[0], codigo1) == 0)
				{
					fprintf(fp1, "%s  %s  %s  %s ", produto[0], produto[1], newvalor, produto[3]);
				}
				else
				{
					fprintf(fp1, "%s  %s  %s  %s ", produto[0], produto[1], produto[2], produto[3]);
				}
			}
			fclose(fp);
			fclose(fp1);
			fp1 = fopen("produtos2.txt", "r+");
			fp = fopen("produtos.txt", "w+");
			while (fscanf(fp1, "%s  %s  %s  %s", &produto[0], &produto[1], &produto[2], &produto[3]) != EOF)
			{
				fprintf(fp, "%s  %s  %s  %s ", produto[0], produto[1], produto[2], produto[3]);
			}
			fclose(fp1);
			fclose(fp);
		}
		else
		{
			printf("Produto não encontrado, verifique novamente:");
			Sleep(2000);
		}
		break;
	case 4: // Alterar quantidade
		fp = fopen("produtos.txt", "r+");
		printf("Digite o código do produto que deseja alterar:");
		scanf("%s", &codigo1);
		while (fscanf(fp, "%s  %s  %s  %s", &produto[0], &produto[1], &produto[2], &produto[3]) != EOF)
		{
			if (strcmp(produto[0], codigo1) == 0)
			{
				printf("Cod: %s --- Descricao: %s --- valor: %s --- quantidade: %s\n", produto[0], produto[1], produto[2], produto[3]);
				quantidade_produto++;
			}
		}
		fclose(fp);
		if (quantidade_produto > 1)
		{
			printf("Deseja mesmo alterar a marca de todos os produtos acima? \n1 - sim \n2 - não");
			scanf("%d", &escolha2);
			while (escolha2 < 1 || escolha2 > 2)
			{
				printf("Opção Invalida!");
				printf("Deseja mesmo alterar o código atual? \n1 - sim \n2 - nï¿½o");
				scanf("%d", &escolha2);
			}
			if (escolha2 == 1)
			{
				printf("Digite a nova quantidade do produto: ");
				scanf("%s", &newquantidade);
				fp = fopen("produtos.txt", "r+");
				fp1 = fopen("produtos2.txt", "w+");
				while (fscanf(fp, "%s  %s  %s  %s", &produto[0], &produto[1], &produto[2], &produto[3]) != EOF)
				{
					if (strcmp(produto[0], codigo1) == 0)
					{
						fprintf(fp1, "%s  %s  %s  %s ", produto[0], produto[1], produto[1], newquantidade);
					}
					else
					{
						fprintf(fp1, "%s  %s  %s  %s ", produto[0], produto[1], produto[2], produto[3]);
					}
				}
				fclose(fp);
				fclose(fp1);
				fp1 = fopen("produtos2.txt", "r+");
				fp = fopen("produtos.txt", "w+");
				while (fscanf(fp1, "%s  %s  %s  %s", &produto[0], &produto[1], &produto[2], &produto[3]) != EOF)
				{
					fprintf(fp, "%s  %s  %s  %s ", produto[0], produto[1], produto[2], produto[3]);
				}
				fclose(fp1);
				fclose(fp);
			}
			else
			{
				printf("Digite a descrição do produto que deseja alterar:");
				scanf("%s", &descricao1);
				printf("Digite a nova quantidade: ");
				scanf("%s", &newquantidade);
				fp = fopen("produtos.txt", "r+");
				fp1 = fopen("produtos2.txt", "w+");
				while (fscanf(fp, "%s  %s  %s  %s", &produto[0], &produto[1], &produto[2], &produto[3]) != EOF)
				{
					if (strcmp(produto[0], codigo1) == 0 && strcmp(produto[1], descricao1) == 0)
					{
						fprintf(fp1, "%s  %s  %s  %s ", produto[0], produto[1], produto[2], newquantidade);
					}
					else
					{
						fprintf(fp1, "%s  %s  %s  %s ", produto[0], produto[1], produto[2], produto[3]);
					}
				}
				fclose(fp);
				fclose(fp1);
				fp1 = fopen("produtos2.txt", "r+");
				fp = fopen("produtos.txt", "w+");
				while (fscanf(fp1, "%s  %s  %s  %s", &produto[0], &produto[1], &produto[2], &produto[3]) != EOF)
				{
					fprintf(fp, "%s  %s  %s  %s ", produto[0], produto[1], produto[2], produto[3]);
				}
				fclose(fp1);
				fclose(fp);
			}
		}
		else if (quantidade_produto == 1)
		{
			printf("Digite a nova quantidade: ");
			scanf("%s", &newquantidade);
			fp = fopen("produtos.txt", "r+");
			fp1 = fopen("produtos2.txt", "w+");
			while (fscanf(fp, "%s  %s  %s  %s", &produto[0], &produto[1], &produto[2], &produto[3]) != EOF)
			{
				if (strcmp(produto[0], codigo1) == 0)
				{
					fprintf(fp1, "%s  %s  %s  %s ", produto[0], produto[1], produto[2], newquantidade);
				}
				else
				{
					fprintf(fp1, "%s  %s  %s  %s ", produto[0], produto[1], produto[2], produto[3]);
				}
			}
			fclose(fp);
			fclose(fp1);
			fp1 = fopen("produtos2.txt", "r+");
			fp = fopen("produtos.txt", "w+");
			while (fscanf(fp1, "%s  %s  %s  %s", &produto[0], &produto[1], &produto[2], &produto[3]) != EOF)
			{
				fprintf(fp, "%s  %s  %s  %s ", produto[0], produto[1], produto[2], produto[3]);
			}
			fclose(fp1);
			fclose(fp);
		}
		else
		{
			printf("Produto não encontrado, verifique novamente:");
			Sleep(2000);
		}
		break;
	}
}

void excluir() // Apagar produto
{
	char codigo1[20], produto[4][20], descricao[20];
	int quantidade_produto = 0, escolha2;
	FILE *fp, *fp1;

	printf("Digite o código do produto que deseja excluir: "); // Pede o codigo do produto
	scanf("%s", &codigo1);

	fp = fopen("produtos.txt", "r+");
	while (fscanf(fp, "%s  %s  %s  %s", &produto[0], &produto[1], &produto[2], &produto[3]) != EOF) // Percorre todo arquivo produtos
	{
		if (strcmp(produto[0], codigo1) == 0) // procura um produto com o codigo igual ao informado
		{
			printf("Cod: %s --- Descricao: %s --- valor: %s --- quantidade: %s\n", produto[0], produto[1], produto[2], produto[3]);
			quantidade_produto++;
		}
	}
	fclose(fp);
	if (quantidade_produto > 1) // Caso tenha mais de um produto
	{
		printf("Deseja Excluir todos os produtos acima? \n1 - sim \n2 - não"); // Pergunta ao usuário se deseja excluir todos os produtos selecionados
		scanf("%d", &escolha2);
		while (escolha2 < 1 || escolha2 > 2)
		{
			printf("Opção Invalida!");
			printf("Deseja Excluir todos os produtos acima? \n1 - sim \n2 - não");
			scanf("%d", &escolha2);
		}
		if (escolha2 == 1) // Caso sim
		{
			fp = fopen("produtos.txt", "r+");
			fp1 = fopen("produtos2.txt", "w+");
			while (fscanf(fp, "%s  %s  %s  %s", &produto[0], &produto[1], &produto[2], &produto[3]) != EOF)
			{
				if (strcmp(produto[0], codigo1) != 0)
				{
					fprintf(fp1, "%s  %s  %s  %s ", produto[0], produto[1], produto[2], produto[3]);
				}
				else
				{
					Sleep(1);
				}
			}
			fclose(fp);
			fclose(fp1);
			fp1 = fopen("produtos2.txt", "r+");
			fp = fopen("produtos.txt", "w+");
			while (fscanf(fp1, "%s  %s  %s  %s", &produto[0], &produto[1], &produto[2], &produto[3]) != EOF)
			{
				fprintf(fp, "%s  %s  %s  %s ", produto[0], produto[1], produto[2], produto[3]);
			}
			fclose(fp1);
			fclose(fp);
		}
		else
		{
			printf("Digite a descrição do produto que deseja excluir:");
			scanf("%s", &descricao);
			fp = fopen("produtos.txt", "r+");
			fp1 = fopen("produtos2.txt", "w+");
			while (fscanf(fp, "%s  %s  %s  %s", &produto[0], &produto[1], &produto[2], &produto[3]) != EOF)
			{
				if (strcmp(produto[0], codigo1) != 0 && strcmp(produto[1], descricao) != 0)
				{
					fprintf(fp1, "%s  %s  %s  %s ", produto[0], produto[1], produto[2], produto[3]);
				}
				else
				{
					Sleep(1);
				}
			}
			fclose(fp);
			fclose(fp1);
			fp1 = fopen("produtos2.txt", "r+");
			fp = fopen("produtos.txt", "w+");
			while (fscanf(fp1, "%s  %s  %s  %s", &produto[0], &produto[1], &produto[2], &produto[3]) != EOF)
			{
				fprintf(fp, "%s  %s  %s  %s ", produto[0], produto[1], produto[2], produto[3]);
			}
			fclose(fp1);
			fclose(fp);
		}
	}
	else if (quantidade_produto == 1)
	{
		printf("Deseja Excluir o produto acima? \n1 - sim \n2 - não   ");
		scanf("%d", &escolha2);
		while (escolha2 < 1 || escolha2 > 2)
		{
			printf("Opção Invalida!");
			printf("Deseja Excluir o produto acima? \n1 - sim \n2 - não   ");
			scanf("%d", &escolha2);
		}
		if (escolha2 == 1)
		{
			fp = fopen("produtos.txt", "r+");
			fp1 = fopen("produtos2.txt", "w+");
			while (fscanf(fp, "%s  %s  %s  %s", &produto[0], &produto[1], &produto[2], &produto[3]) != EOF)
			{
				if (strcmp(produto[0], codigo1) != 0)
				{
					fprintf(fp1, "%s  %s  %s  %s ", produto[0], produto[1], produto[2], produto[3]);
				}
				else
				{
					Sleep(1);
				}
			}
			fclose(fp);
			fclose(fp1);
			fp1 = fopen("produtos2.txt", "r+");
			fp = fopen("produtos.txt", "w+");
			while (fscanf(fp1, "%s  %s  %s  %s", &produto[0], &produto[1], &produto[2], &produto[3]) != EOF)
			{
				fprintf(fp, "%s  %s  %s  %s ", produto[0], produto[1], produto[2], produto[3]);
			}
			fclose(fp1);
			fclose(fp);
		}
	}
	else
	{
		printf("produto não encontrado!");
		Sleep(2000);
	}
}

void sair()
{
	exit(EXIT_SUCCESS);
}
