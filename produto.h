#ifndef PRODUTO_H
#define PRODUTO_H

struct Produto {
    char nome[50];
    int quantidade;
    float valor;

    void salvarProduto(std::ofstream &arquivo);
    void carregarProduto(std::ifstream &arquivo);
};

void carregarProdutos(Produto produtos[], int &quantidade);
void salvarProdutos(Produto produtos[], int quantidade);
void cadastrarProduto(Produto produtos[], int *quantidade);
void controlarEstoque(Produto produtos[], int quantidade);
void registrarVenda(Produto produtos[], int quantidade);
void gerarRelatorio(Produto produtos[], int quantidade);
void iniciarSistemaDeEstoque();

#endif 
