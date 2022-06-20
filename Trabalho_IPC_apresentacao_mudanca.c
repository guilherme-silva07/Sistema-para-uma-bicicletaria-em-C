#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
	char nome[100], grupo[30];
  float preco;
  long int codigo;
} cadastra_produtos;

typedef struct{
	char nome[100], endereco[100], cpf[20], telefone[20], idade[3];
  int status;
  // 0 - não esta alugado
  // 1 - esta alugado
} cadastra_clientes;

typedef struct{
	char nome[100], status[20];
  long int codigo;
  // 0 - disponivel
  // 1 - ocupado
} bicicletas;

int abre_arquivo_produto(cadastra_produtos produto[], FILE *arquivo){

  int x, contador = 0, aux;
  char c;

  arquivo = fopen("produtos.txt", "r");

  if (arquivo == NULL){
    return contador;
  }

  do {

    x = fscanf (arquivo, "%[^\n]\n%s\n%f\n%ld\n", produto[contador].nome, produto[contador].grupo, &produto[contador].preco, &produto[contador].codigo);

    contador ++;

  } while (x != EOF);

  fclose(arquivo);

  return (contador-1);

}

void fecha_arquivo_produto(cadastra_produtos produto[], int quantidade_produto, FILE *arquivo){

  int contador;

  arquivo = fopen("produtos.txt", "w");

  if (arquivo == NULL){
    printf ("Erro na abertura do arquivo\n");
    exit(1);
  }

  for (contador = 0; contador < quantidade_produto; contador ++){

    fprintf (arquivo, "%s\n%s\n%.2f\n%ld\n", produto[contador].nome, produto[contador].grupo, produto[contador].preco, produto[contador].codigo);

  }

  fclose (arquivo);

}

int abre_arquivo_cliente(cadastra_clientes cliente[], FILE *arquivo){

  int x, contador = 0;

  arquivo = fopen("clientes.txt", "r");

  if (arquivo == NULL){
    return contador;
  }

  do {

    x = fscanf (arquivo, "%[^\n]\n%[^\n]\n%s\n%s\n%s\n%d\n", cliente[contador].nome, cliente[contador].endereco, cliente[contador].cpf, cliente[contador].idade, cliente[contador].telefone, &cliente[contador].status);

    contador ++;

  } while (x != EOF);

  fclose(arquivo);

  return (contador-1);

}

void fecha_arquivo_cliente(cadastra_clientes cliente[], int quantidade_cliente, FILE *arquivo){

  int contador;

  arquivo = fopen("clientes.txt", "w");

  if (arquivo == NULL){
    printf ("Erro na abertura do arquivo\n");
    exit(1);
  }

  for (contador = 0; contador < quantidade_cliente; contador ++){

    fprintf (arquivo, "%s\n%s\n%s\n%s\n%s\n%d\n", cliente[contador].nome, cliente[contador].endereco, cliente[contador].cpf, cliente[contador].idade, cliente[contador].telefone, cliente[contador].status);

  }

  fclose (arquivo);

}

int abre_arquivo_bicicleta(bicicletas bike[], FILE *arquivo){

  int x, contador = 0;

  arquivo = fopen("aluguel.txt", "r");

  if (arquivo == NULL){
    return contador;
  }

  do {

    x = fscanf (arquivo, "%[^\n]\n%ld\n%s\n", bike[contador].nome, &bike[contador].codigo, bike[contador].status);

    contador ++;

  } while (x != EOF);

  fclose(arquivo);

  return (contador-1);

}

int vetor_bicicleta(bicicletas bike[], int posicao_bike, cadastra_produtos produto[], int posicao_produto){

  strcpy(bike[posicao_bike].nome, produto[posicao_produto].nome);
  bike[posicao_bike].codigo = produto[posicao_produto].codigo;
  strcpy(bike[posicao_bike].status, "0");

  posicao_bike += 1;
  return posicao_bike;

}

void fecha_arquivo_bicicleta(bicicletas bike[], int quantidade_bicicleta, FILE *arquivo){

  int contador;

  arquivo = fopen("aluguel.txt", "w");

  if (arquivo == NULL){
    printf ("Erro na abertura do arquivo\n");
    exit(1);
  }

  for (contador = 0; contador < quantidade_bicicleta; contador ++){

    fprintf (arquivo, "%s\n%ld\n%s\n", bike[contador].nome, bike[contador].codigo, bike[contador].status);

  }

  fclose (arquivo);

}

int verifica_cpf(char cpf[20], cadastra_clientes cliente[], int qtde_cliente){

  int contador;

  for (contador = 0; contador < qtde_cliente; contador ++){

    if (strcmp(cpf, cliente[contador].cpf) == 0){
      return contador;
    }

  }

  return (-1);

}

int verifica_codigo_bicicleta(long int cdg, bicicletas bike[], int qtde_bicicleta){

  int contador;

  for (contador = 0; contador < qtde_bicicleta; contador ++){

    if (cdg == bike[contador].codigo){
      return 1;
    }

  }

  return 0;

}

int verifica_codigo_produto(cadastra_produtos produto[], int qtde_produto, long int codigo_digitado){

  int contador = 0;

  for (contador = 0; contador < qtde_produto; contador++){

    if (codigo_digitado == produto[contador].codigo){
      return 0;
    }

  }

  return 1;

}



void cadastro_produto(cadastra_produtos produto[], FILE *arquivo, bicicletas bike[]){

  int resposta, gp, quantidade_produto, quantidade_bicicleta, aux;
  long int codigo;

  quantidade_produto = abre_arquivo_produto(produto, arquivo);
  quantidade_bicicleta = abre_arquivo_bicicleta(bike, arquivo);

  do {
    system ("cls");
    do {
      printf ("Grupo do produto (%d):\n[1]Bicicleta\n[2]Acessorios\n[3]Vestuario\n---------------\n", quantidade_produto);
        scanf ("%d", &gp);
        setbuf(stdin, NULL);
      switch (gp){
        case 1:
          strcpy(produto[quantidade_produto].grupo, "Bicicleta");
          system("cls");
          break;
        case 2: 
          strcpy(produto[quantidade_produto].grupo, "Acessorio");
          system("cls");
          break;
        case 3: 
          strcpy(produto[quantidade_produto].grupo, "Vestuario");
          system("cls");
          break;
        default: 
          system("cls");
          printf ("Opcao invalida\n\n");
          break;
      }
    } while (gp != 1 && gp  != 2 && gp != 3);

  	printf ("Digite o nome do produto (%d): ", quantidade_produto);
      scanf ("%[^\n]s", produto[quantidade_produto].nome);
      setbuf(stdin, NULL);
    printf ("Digite o preco do produto (%d): R$", quantidade_produto);
      scanf ("%f", &produto[quantidade_produto].preco);
      setbuf(stdin, NULL);

    do {
      printf ("Digite o codigo do produto (%d): ", quantidade_produto);
        scanf ("%ld", &codigo);
        setbuf(stdin, NULL);
    
      aux = verifica_codigo_produto(produto, quantidade_produto, codigo);

      if (aux == 0){
        system("cls");
        printf ("Esse codigo ja pertence a outro produto\n\n");
      } else {
        produto[quantidade_produto].codigo = codigo;
      }

    } while (aux == 0);

    if (gp == 1){
      quantidade_bicicleta = vetor_bicicleta(bike, quantidade_bicicleta, produto, quantidade_produto);
    }

    printf ("\nVoce quer cadastrar outro produto?\n[1]SIM\n[2]NAO\n----------\n");
      scanf ("%d", &resposta);
      setbuf(stdin, NULL);

    quantidade_produto += 1;

  } while (resposta == 1);

  fecha_arquivo_bicicleta(bike, quantidade_bicicleta, arquivo);
  fecha_arquivo_produto(produto, quantidade_produto, arquivo);

  system("cls");

  printf ("Produto cadastrado com sucesso!\n\n");
  setbuf(stdin, NULL);
  getchar();
  setbuf(stdin, NULL);
  
}

void mostra_produto(cadastra_produtos produto [], FILE *arquivo){

  int contador, quantidade;
  float soma_total = 0.0;

  system("cls");

  quantidade = abre_arquivo_produto(produto, arquivo);
  
  for (contador = 0; contador < quantidade; contador ++){

    printf ("Nome: %s\nGrupo: %s\nPreco: R$%.2f\nCodigo: %ld\n\n", produto[contador].nome, produto[contador].grupo, produto[contador].preco, produto[contador].codigo);
    soma_total += produto[contador].preco;

  }

  printf ("Valor total: %.2f", soma_total);

}

void percentual(cadastra_produtos produto[], FILE *arquivo){

  int contador, quantidade;
  float soma_total = 0.0, percentual;

  system("cls");

  quantidade = abre_arquivo_produto(produto, arquivo);

  printf ("Qual o percentual de reajuste:");
    scanf("%f", &percentual);
  
  for (contador = 0; contador < quantidade; contador ++){

    produto[contador].preco = (produto[contador].preco*((percentual/100)+1.0));
    soma_total += produto[contador].preco;

  }

  // printf ("Valor total: %.2f", soma_total);

  fecha_arquivo_produto(produto, quantidade, arquivo);

}

void mostra_bicicletas_alugadas(bicicletas bike[], FILE *arquivo, cadastra_clientes cliente[], cadastra_produtos produto[]){

  int contador, quantidade_cliente, quantidade_bicicleta, auxiliar, aux_produto, quantidade_produto;
  float soma = 0.0;

  system("cls");

  quantidade_cliente = abre_arquivo_cliente(cliente, arquivo);
  quantidade_bicicleta = abre_arquivo_bicicleta(bike, arquivo);
  quantidade_produto = abre_arquivo_produto(produto, arquivo);
  
  for (contador = 0; contador < quantidade_bicicleta; contador ++){

    if (strcmp(bike[contador].status, "0") != 0){
      for (auxiliar = 0; auxiliar < quantidade_cliente; auxiliar ++){
        if (strcmp(bike[contador].status, cliente[auxiliar].cpf) == 0){
          printf ("Bicicleta: %s\nCodigo: %ld\nCliente: %s\n\n", bike[contador].nome, bike[contador].codigo, cliente[auxiliar].nome);
        }
        for (aux_produto = 0; aux_produto < quantidade_produto; aux_produto++){
          if (bike[contador].codigo == produto[aux_produto].codigo && (strcmp(bike[contador].status, cliente[auxiliar].cpf) == 0)){
            soma += produto[aux_produto].preco;
          }
        }
      }
    }

    

  }

  printf ("Valor total: R$%.2f\n\n", soma);

}

void mostra_produto_grupo(cadastra_produtos produto[], FILE *arquivo){

  int contador, opcao, quantidade;
  system("cls");

  quantidade = abre_arquivo_produto(produto, arquivo);

  do {
    printf ("Qual grupo de produtos deve ser mostrado:\n[1]Bicicletas\n[2]Acessorios\n[3]Vestuarios\n\nOpcao: ");
      scanf ("%d", &opcao);
    printf ("\n");

    switch(opcao){

      case 1:
        system("cls");
        for (contador = 0; contador < quantidade; contador ++){
          if (strcmp(produto[contador].grupo, "Bicicleta") == 0){
            printf ("Produto: %s\nPreco: R$%.2f\nCodigo: %ld\n\n", produto[contador].nome, produto[contador].preco, produto[contador].codigo);
          }
        }
        break;

      case 2:
        system("cls");
        for (contador = 0; contador < quantidade; contador ++){
          if (strcmp(produto[contador].grupo, "Acessorio") == 0){
            printf ("Produto: %s\nPreco: R$%.2f\nCodigo: %ld\n\n", produto[contador].nome, produto[contador].preco, produto[contador].codigo);
          }
        }
        break;

      case 3:
        system("cls");
        for (contador = 0; contador < quantidade; contador ++){
          if (strcmp(produto[contador].grupo, "Vestuario") == 0){
            printf ("Produto: %s\nPreco: R$%.2f\nCodigo: %ld\n\n", produto[contador].nome, produto[contador].preco, produto[contador].codigo);
          }
        }
        break;

        default:
          system("cls");
          printf ("Opcao invalida\n\n");
    
    }

  } while (opcao != 1 && opcao != 2 && opcao != 3);

}

void cadastro_cliente(cadastra_clientes cliente[], FILE *arquivo){

  int resposta, aux = 0, quantidade;

  quantidade = abre_arquivo_cliente(cliente, arquivo);

  do {
    system ("cls");

    printf ("Digite o CPF do cliente: ");
      scanf ("%[^\n]s", cliente[quantidade].cpf);
      setbuf(stdin, NULL);

    aux = verifica_cpf(cliente[quantidade].cpf, cliente, quantidade);

    if (aux != -1){
      system ("cls");
      printf ("CPF ja cadastrado\n\n");
      return;
    }

    printf ("Digite o nome do cliente: ");
      scanf ("%[^\n]s", cliente[quantidade].nome);
      setbuf(stdin, NULL);

    printf ("Digite a idade: ");
      scanf ("%[^\n]s", cliente[quantidade].idade);
      setbuf(stdin, NULL);
    
    printf ("Digite o endereco: ");
      scanf ("%[^\n]s", cliente[quantidade].endereco);
      setbuf(stdin, NULL);

    printf ("Digite o numero de telefone: ");
      scanf ("%[^\n]s", cliente[quantidade].telefone);
      setbuf(stdin, NULL);

    cliente[quantidade].status = 0;

    printf ("\nVoce quer cadastrar outro cliente?\n[1]SIM\n[2]NAO\n---------------\n");
      scanf ("%d", &resposta);
      setbuf(stdin, NULL);

    quantidade ++;

  } while (resposta == 1);

  fecha_arquivo_cliente(cliente, quantidade, arquivo);

  system ("cls");

  printf ("Cliente cadastrado com sucesso!\n\n");
  setbuf(stdin, NULL);
  getchar();
  setbuf(stdin, NULL);

}

void mostra_cliente(cadastra_clientes cliente[], FILE *arquivo){

  int quantidade, contador;

  quantidade = abre_arquivo_cliente(cliente, arquivo);

  system ("cls");

  for (contador = 0; contador < quantidade; contador++){
    printf ("Nome: %s\nCPF: %s\nIdade: %s anos\nEndereco: %s\nTelefone: %s\n\n", cliente[contador].nome, cliente[contador].cpf, cliente[contador].idade, cliente[contador].endereco, cliente[contador].telefone);
  }

}

void mostra_cliente_cpf(cadastra_clientes cliente[], FILE *arquivo){

  int contador, quantidade;
  char cpf[20];

  system ("cls");

  quantidade = abre_arquivo_cliente(cliente, arquivo);

  printf ("Digite o cpf do cliente: ");
    scanf ("%s", cpf);

  system ("cls");

  for (contador = 0; contador < quantidade; contador ++){

    if (strcmp(cpf, cliente[contador].cpf) == 0){
      printf ("Nome: %s\nCPF: %s\nIdade: %s anos\nEndereco: %s\nTelefone: %s\n\n", cliente[contador].nome, cliente[contador].cpf, cliente[contador].idade, cliente[contador].endereco, cliente[contador].telefone);
      break;
    }

  }

}

void editar_clientes (cadastra_clientes cliente[], FILE *arquivo){

  int contador, quantidade, opcao, aux = 0, aux_cliente = 0;
  char cpf[20], novo_cpf[20];

  quantidade = abre_arquivo_cliente(cliente, arquivo);

  system("cls");

  printf ("Digite o CPF do cliente que voce deseja editar: ");
    scanf ("%[^\n]s", cpf);
    setbuf(stdin, NULL);

  system("cls");

  for (contador = 0; contador < quantidade; contador++){


    if (strcmp(cpf, cliente[contador].cpf) == 0){

      printf ("----------Dados Atuais----------\n");
      printf ("Nome: %s\nCPF: %s\nEndereco: %s\nTelefone: %s\n", cliente[contador].nome, cliente[contador].cpf, cliente[contador].endereco, cliente[contador].telefone);
      printf ("--------------------------------\n\n");

      do{

        printf ("Qual dado voce quer editar?\n[1]Nome\n[2]CPF\n[3]Endereco\n[4]Telefone\n\nOpcao: ");
          scanf ("%d", &opcao);
          setbuf(stdin, NULL);

        switch(opcao){

          case 1:
            printf ("Digite o novo nome: ");
              scanf ("%[^\n]s", cliente[contador].nome);
              setbuf(stdin, NULL);
            break;

          case 2:
            printf ("Digite o novo CPF: ");
              scanf ("%[^\n]s", novo_cpf);
              setbuf(stdin, NULL);

            aux = verifica_cpf(novo_cpf, cliente, quantidade);

            if (aux != -1){
              system ("cls");
              printf ("CPF ja cadastrado\n\n");
              return;
            }
            strcpy(cliente[contador].cpf, novo_cpf);
            break;

          case 3:
            printf ("Digite o novo endereco: ");
              scanf ("%[^\n]s", cliente[contador].endereco);
              setbuf(stdin, NULL);
            break;

          case 4:
            printf ("Digite o novo telefone: ");
              scanf ("%[^\n]s", cliente[contador].telefone);
              setbuf(stdin, NULL);
            break;

          default:
            system("cls");
            printf ("Opcao Invalida\n\n");
            break;

        }

      } while(opcao != 1 && opcao != 2 && opcao != 3 && opcao != 4);
      aux_cliente ++;
      break;
    }
  }

  if (aux_cliente == 0){
    system ("cls");
    printf("Cliente nao encontrado\n\n");
    return;
  }

  fecha_arquivo_cliente(cliente, quantidade, arquivo);

  system ("cls");

  printf ("Cliente salvo com sucesso!\n\n");
  setbuf(stdin, NULL);
  getchar();
  setbuf(stdin, NULL);

}

void editar_produto (cadastra_produtos produto[], FILE *arquivo){

  system("cls");

  int contador, resposta, novo_grupo, quantidade, aux = 0;
  long int cod_produto, novo_codigo;

  quantidade = abre_arquivo_produto(produto, arquivo);

  printf ("Digite o codigo do produto que voce deseja editar: ");
    scanf ("%ld", &cod_produto);
    setbuf(stdin, NULL);

  for (contador = 0; contador < quantidade; contador++){

    if (cod_produto == produto[contador].codigo){
      system ("cls");

      printf ("----------Dados Atuais----------\n");
      printf ("Nome: %s\nGrupo: %s\nCodigo: %ld\nPreco: R$%.2f\n", produto[contador].nome, produto[contador].grupo, produto[contador].codigo, produto[contador].preco);
      printf ("--------------------------------\n\n");

      do {

        printf ("Qual dado voce quer editar?\n");
        printf ("[1]Nome\n[2]Grupo\n[3]Codigo\n[4]Preco\n----------\n");
          scanf ("%d", &resposta);
          setbuf(stdin, NULL);
  
        switch (resposta)
        {
  
        case 1:
          printf ("Digite o novo nome: ");
            scanf ("%[^\n]s", produto[contador].nome);
            setbuf(stdin, NULL);
          break;
  
        case 2:
          printf ("Digite a opcao do grupo:\n");
          printf ("[1]Bicicleta\n[2]Acessorio\n[3]Vestuario\n----------\n");
            scanf ("%d", &novo_grupo);
            setbuf(stdin, NULL);
          switch(novo_grupo){
            case 1:
              strcpy(produto[contador].grupo, "Bicicleta");
              break;
            case 2:
              strcpy(produto[contador].grupo, "Acessorio");
              break;
            case 3:
              strcpy(produto[contador].grupo, "Vestuario");
              break;
            default:
              printf ("Opcao invalida\n");
              break;
          }
          break;
        
        case 3:

          do {
            printf ("Digite o novo codigo: ");
              scanf("%ld", &novo_codigo);
              setbuf(stdin, NULL);
            
            cod_produto = verifica_codigo_produto(produto, quantidade, novo_codigo);

            if (cod_produto == 0){
              system("cls");
              printf ("Esse codigo ja pertence a outro produto\n\n");
            }

          } while(cod_produto == 0);
          produto[contador].codigo = novo_codigo;
          break;
  
        case 4:
          printf ("Digite o novo preco: R$");
            scanf ("%f", &produto[contador].preco);
            setbuf(stdin, NULL);
          break;
        
        default:
          system("cls");
          printf ("Opcao invalida\n");
          break;
        }

      } while (resposta != 1 && resposta != 2 && resposta != 3 && resposta != 4);
      aux++;
    }
  }

  if (aux == 0){
    system ("cls");
    printf ("Produto nao encontrado\n\n");
    return;
  }

  fecha_arquivo_produto(produto, quantidade, arquivo);

  system ("cls");

  printf ("Produto salvo com sucesso!\n\n");
  setbuf(stdin, NULL);
  getchar();
  setbuf(stdin, NULL);

}

void alugar_bicicleta (bicicletas bike[], FILE *arquivo, cadastra_clientes cliente[]){

  system("cls");

  char cpf_client[20];
  int contador, quantidade_cliente, quantidade_bicicleta, auxiliar, opcao, aux = 0;

  quantidade_bicicleta = abre_arquivo_bicicleta(bike, arquivo);
  quantidade_cliente = abre_arquivo_cliente(cliente, arquivo);

    printf ("Digite o cpf do cliente que deseja alugar a bicicleta: ");
      scanf ("%[^\n]s", cpf_client);
      setbuf(stdin, NULL);

    for (contador = 0; contador < quantidade_cliente; contador++){
      if(strcmp(cpf_client, cliente[contador].cpf) == 0){
        printf ("\nDigite o codigo da bicicleta de sua preferencia\n");
        aux++;
        if (cliente[contador].status == 1){
          system("cls");
          printf ("Este cliente ja possui uma bicicleta alugada\n\n");
          return;
        }
        break;
      }
    }

    if (aux == 0){
      printf ("\nCliente nao encontrado\n");
      return;
    }

    aux = 0;

    for (auxiliar = 0; auxiliar < quantidade_bicicleta; auxiliar++){
      if (strcmp(bike[auxiliar].status, "0") == 0){
        printf ("%s | Codigo: %ld | Disponivel\n", bike[auxiliar].nome, bike[auxiliar].codigo);
        aux ++;
      }
    }

    if (aux != 0){
      printf ("\nOpcao: ");
        scanf ("%d", &opcao);
        setbuf(stdin, NULL);
      for (auxiliar = 0; auxiliar < quantidade_bicicleta; auxiliar ++){
        if ((opcao == bike[auxiliar].codigo) && (strcmp(bike[auxiliar].status, "0") == 0)){
          strcpy(bike[auxiliar].status, cliente[contador].cpf);
          cliente[contador].status = 1;
          system("cls");
          printf ("Bicicleta alugada com sucesso!\n\n");
          setbuf(stdin, NULL);
          getchar();
          setbuf(stdin, NULL);
          break;
        }
      }
    } else {
      printf ("\nNenhuma opcao disponivel\n");
      return;
    }

    fecha_arquivo_bicicleta(bike, quantidade_bicicleta, arquivo);
    fecha_arquivo_cliente(cliente, quantidade_cliente, arquivo);

    system("cls");

}

void devolucao_bicicleta (bicicletas bike[], FILE *arquivo, cadastra_clientes cliente[]){

  char cpf[20];
  long int codigo;
  int contador, quantidade_cliente, quantidade_bicicleta, resposta, aux = 0;

  quantidade_cliente = abre_arquivo_cliente(cliente, arquivo);
  quantidade_bicicleta = abre_arquivo_bicicleta(bike, arquivo);

  system ("cls");

  printf ("Digite o CPF do cliente: ");
    scanf ("%s", cpf);

  resposta = verifica_cpf(cpf, cliente, quantidade_cliente);

  if (resposta == -1){
    system ("cls");
    printf ("CPF nao encontrado\n\n");
    return;
  }

  system ("cls");

  for (contador = 0; contador < quantidade_bicicleta; contador ++){
    if (strcmp(bike[contador].status, cliente[resposta].cpf) == 0){
      printf ("\n%s | Codigo: %ld", bike[contador].nome, bike[contador].codigo);
      aux++;
    }
  }

  aux = 0;

  printf ("\n\nDigite o codigo da bicicleta que voce deseja devolver\nOpcao: ");
    scanf ("%ld", &codigo);

  for (contador = 0; contador < quantidade_bicicleta; contador ++){
    if (codigo == bike[contador].codigo && (strcmp(cpf, bike[contador].status) == 0)){
      strcpy(bike[contador].status, "0");
      cliente[resposta].status = 0;
      aux++;
      break;
    }
  }

  if (aux == 0){
    system("cls");
    printf ("Opcao invalida\n\n");
    return;
  }

  fecha_arquivo_bicicleta(bike, quantidade_bicicleta, arquivo);
  fecha_arquivo_cliente(cliente, quantidade_cliente, arquivo);

  system ("cls");

  printf ("Bicicleta devolvida com sucesso!\n\n");
  setbuf(stdin, NULL);
  getchar();
  setbuf(stdin, NULL);

}

void menu(){

	int opcao;

	cadastra_produtos P[50];
  cadastra_clientes C[50];
  bicicletas B[50];

  FILE *produto;
  FILE *cliente;
  FILE *arq_bicicleta;

	while(1){
		printf("\nBem vindo ao Sistema da Bikes Lobo\n");
		printf("\n1- Cadastrar produtos ");
		printf("\n2- Mostrar todos os produtos");
		printf("\n3- Mostrar produtos por grupo");
    printf("\n4- Editar produtos");
    printf("\n5- Cadastrar clientes");
    printf("\n6- Mostrar todos os clientes");
    printf("\n7- Mostrar cliente especifico");
    printf("\n8- Editar clientes");
    printf("\n9- Alugar bicicletas"); 
    printf("\n10- Devolver bicicletas"); 
    printf("\n11- Mostra bicicletas alugadas"); 
    printf("\n12- Percentual");
		printf("\n0- Sair");
		printf("\nDigite opcao: ");
      scanf("%d", &opcao);
      setbuf(stdin, NULL);

		if(opcao == 1) cadastro_produto(P, produto, B);
		if(opcao == 2) mostra_produto(P, produto);
		if(opcao == 3) mostra_produto_grupo(P, produto);
    if(opcao == 4) editar_produto(P, produto);
		if(opcao == 5) cadastro_cliente(C, cliente);
    if(opcao == 6) mostra_cliente(C, cliente);
    if(opcao == 7) mostra_cliente_cpf(C, cliente);
    if(opcao == 8) editar_clientes(C, cliente);
    if(opcao == 9) alugar_bicicleta(B, arq_bicicleta, C);
    if(opcao == 10) devolucao_bicicleta(B, arq_bicicleta, C);
    if(opcao == 11) mostra_bicicletas_alugadas(B, arq_bicicleta, C, P);
    if(opcao == 12) percentual(P, produto);
		if(opcao == 0) return;
	}
}

int main(){
	menu();
  return 0;
}