#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMCli 3
#define TAMProd 3
#define TAMVendas 10

typedef struct {
    int id;
    char nome[20];
    int quantidade;
    float valor;
} Produto;

typedef struct {
    int id;
    char nome[20];
} Cliente;

typedef struct {
    int idCliente;
    int idProduto;
    int quantProduto;
    float valorTotal;
} Venda;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void cadastrarCliente(Cliente *c) {
    for (int i = 0; i < TAMCli; i++) {
        printf("Cliente %d, Primeiro Nome: ", i + 1);
        scanf("%s", c[i].nome);
        limparBuffer();
        c[i].id = i + 1;
    }
}

void cadastrarProduto(Produto *p) {
    for (int i = 0; i < TAMProd; i++) {
        printf("\nProduto %d, Nome: ", i + 1);
        scanf("%s", p[i].nome);
        limparBuffer();

        printf("Quantidade: ");
        scanf("%d", &p[i].quantidade);
        limparBuffer();

        printf("Valor: ");
        scanf("%f", &p[i].valor);
        limparBuffer();

        p[i].id = i + 1;
    }
}

void consultarCliente(Cliente *c) {
    printf("\nLista de Clientes:\n");
    for (int i = 0; i < TAMCli; i++) {
        printf("ID: %d\n", c[i].id);
        printf("Nome: %s\n", c[i].nome);
        printf("-----------------------------\n");
    }
}

void consultarProduto(Produto *p) {
    printf("\nLista de Produtos:\n");
    for (int i = 0; i < TAMProd; i++) {
        printf("ID: %d\n", p[i].id);
        printf("Nome: %s\n", p[i].nome);
        printf("Quantidade: %d\n", p[i].quantidade);
        printf("Valor: %.2f\n", p[i].valor);
        printf("-----------------------------\n");
    }
}

void realizarVenda(Cliente *c, Produto *p, Venda *v, int *contVendas) {
    if (*contVendas >= TAMVendas) {
        printf("\nLimite de vendas atingido!\n");
        return;
    }

    int idCliente, idProduto, quantidade;


    while (1) {
        printf("\nDigite o ID do Cliente: ");
        scanf("%d", &idCliente);
        limparBuffer();
        if (idCliente >= 1 && idCliente <= TAMCli) break;
        printf("Cliente inválido! Tente novamente.\n");
    }


    while (1) {
        printf("Digite o ID do Produto: ");
        scanf("%d", &idProduto);
        limparBuffer();
        if (idProduto >= 1 && idProduto <= TAMProd) break;
        printf("Produto inválido! Tente novamente.\n");
    }


    while (1) {
        printf("Quantidade desejada: ");
        scanf("%d", &quantidade);
        limparBuffer();

        if (quantidade <= 0) {
            printf("Quantidade inválida! Deve ser maior que zero.\n");
        } else if (p[idProduto - 1].quantidade < quantidade) {
            printf("Estoque insuficiente! Estoque atual: %d\n", p[idProduto - 1].quantidade);
        } else {
            break;
        }
    }


    p[idProduto - 1].quantidade -= quantidade;
    v[*contVendas].idCliente = idCliente;
    v[*contVendas].idProduto = idProduto;
    v[*contVendas].quantProduto = quantidade;
    v[*contVendas].valorTotal = quantidade * p[idProduto - 1].valor;

    printf("\nVenda realizada com sucesso!\n");
    printf("Valor total da venda: R$ %.2f\n", v[*contVendas].valorTotal);

    (*contVendas)++;
}

void consultarVendas(Venda *v, int contVendas) {
    if (contVendas == 0) {
        printf("\nNenhuma venda realizada ainda.\n");
        return;
    }

    printf("\nLista de Vendas:\n");
    for (int i = 0; i < contVendas; i++) {
        printf("ID Cliente: %d\n", v[i].idCliente);
        printf("ID Produto: %d\n", v[i].idProduto);
        printf("Quantidade: %d\n", v[i].quantProduto);
        printf("Valor Total: R$ %.2f\n", v[i].valorTotal);
        printf("-----------------------------\n");
    }
}

int main() {
    int opcao, sair = 0, contVendas = 0;

    Cliente *clientes = (Cliente *)malloc(TAMCli * sizeof(Cliente));
    Produto *produtos = (Produto *)malloc(TAMProd * sizeof(Produto));
    Venda *vendas = (Venda *)malloc(TAMVendas * sizeof(Venda));

    if (clientes == NULL || produtos == NULL || vendas == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    do {
        printf("\n\n>>>> Sistema de Vendas <<<< \n");
        printf("1 - Cadastrar Clientes\n");
        printf("2 - Cadastrar Produtos\n");
        printf("3 - Consultar Clientes\n");
        printf("4 - Consultar Produtos\n");
        printf("5 - Realizar Venda\n");
        printf("6 - Consultar Vendas\n");
        printf("7 - Sair\n");
        printf(">>>> ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                cadastrarCliente(clientes);
                break;
            case 2:
                cadastrarProduto(produtos);
                break;
            case 3:
                consultarCliente(clientes);
                break;
            case 4:
                consultarProduto(produtos);
                break;
            case 5:
                realizarVenda(clientes, produtos, vendas, &contVendas);
                break;
            case 6:
                consultarVendas(vendas, contVendas);
                break;
            case 7:
                sair = 1;
                break;
            default:
                printf("\n\nOpcao Invalida!\n");
        }
    } while (!sair);

    free(clientes);
    free(produtos);
    free(vendas);

    return 0;
}
