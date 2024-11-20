#include <iostream>
#include <fstream>
#include <string>
#include "produto.h"

void Produto::salvarProduto(std::ofstream &arquivo) {
    arquivo << nome << ";" << quantidade << ";" << valor << "\n";
}

void Produto::carregarProduto(std::ifstream &arquivo) {
    std::string linha;
    if (std::getline(arquivo, linha)) {
        sscanf(linha.c_str(), "%49[^;];%d;%f", nome, &quantidade, &valor);
    }
}

void carregarProdutos(Produto produtos[], int &quantidade) {
    std::ifstream arquivo("produtos.txt");
    if (!arquivo) {
        return;
    }

    while (!arquivo.eof()) {
        produtos[quantidade].carregarProduto(arquivo);
        quantidade++;
    }

    arquivo.close();
}

void salvarProdutos(Produto produtos[], int quantidade) {
    std::ofstream arquivo("produtos.txt");
    if (!arquivo) {
        std::cout << "Erro ao abrir arquivo para salvar." << std::endl;
        return;
    }

    for (int i = 0; i < quantidade; i++) {
        produtos[i].salvarProduto(arquivo);
    }

    arquivo.close();
}

void cadastrarProduto(Produto produtos[], int *quantidade) {
    std::cout << "Digite o nome do produto: ";
    std::cin.ignore();
    std::cin.getline(produtos[*quantidade].nome, 50);
    
    std::cout << "Digite a quantidade do produto: ";
    std::cin >> produtos[*quantidade].quantidade;
    std::cin.ignore();
    
    std::cout << "Digite o valor do produto: ";
    std::cin >> produtos[*quantidade].valor;
    std::cin.ignore();
    
    (*quantidade)++;

    std::cout << "=========================" << std::endl;
    std::cout << "Produto Cadastrado com sucesso." << std::endl;
    std::cout << "=========================" << std::endl;
}

void controlarEstoque(Produto produtos[], int quantidade) {
    if (quantidade == 0) {
        std::cout << "Nenhum produto cadastrado." << std::endl;
        return;
    }

    std::cout << "Produtos cadastrados:" << std::endl;
    for (int i = 0; i < quantidade; i++) {
        std::cout << i + 1 << ". " << produtos[i].nome << " - Quantidade: " << produtos[i].quantidade << std::endl;
    }

    int indice;
    std::cout << "Escolha o numero do produto para controlar o estoque: ";
    std::cin >> indice;
    
    if (indice < 1 || indice > quantidade) {
        std::cout << "Produto inválido." << std::endl;
        return;
    }

    int opcao;
    std::cout << "Digite 1 para adicionar produtos ao estoque ou 2 para remover produtos do estoque: ";
    std::cin >> opcao;
    
    if (opcao == 1) {
        std::cout << "Digite a quantidade de produtos a ser adicionada: ";
        int quantidadeAdicionada;
        std::cin >> quantidadeAdicionada;
        produtos[indice - 1].quantidade += quantidadeAdicionada;
    } else if (opcao == 2) {
        std::cout << "Digite a quantidade de produtos a ser removida: ";
        int quantidadeRemovida;
        std::cin >> quantidadeRemovida;
        if (quantidadeRemovida > produtos[indice - 1].quantidade) {
            std::cout << "Quantidade em estoque insuficiente!" << std::endl;
        } else {
            produtos[indice - 1].quantidade -= quantidadeRemovida;
        }
    } else {
        std::cout << "Opção inválida." << std::endl;
    }
}

void registrarVenda(Produto produtos[], int quantidade) {
    if (quantidade == 0) {
        std::cout << "Nenhum produto cadastrado." << std::endl;
        return;
    }

    std::cout << "Digite o nome do produto vendido: ";
    std::string nomeProduto;
    std::cin.ignore();
    std::getline(std::cin, nomeProduto);

    int i;
    for (i = 0; i < quantidade; i++) {
        if (nomeProduto == produtos[i].nome) {
            std::cout << "Digite a quantidade de produtos vendidos: ";
            int quantidadeVendida;
            std::cin >> quantidadeVendida;
            if (quantidadeVendida <= produtos[i].quantidade) {
                produtos[i].quantidade -= quantidadeVendida;
                std::cout << "Venda registrada com sucesso!" << std::endl;
            } else {
                std::cout << "Quantidade em estoque insuficiente!" << std::endl;
            }
            break;
        }
    }
    
    if (i == quantidade) {
        std::cout << "Produto não encontrado!" << std::endl;
    }
}


void gerarRelatorio(Produto produtos[], int quantidade) {
    if (quantidade == 0) {
        std::cout << "Nenhum produto cadastrado." << std::endl;
        return;
    }

    std::cout << "Relatório de Vendas:" << std::endl;
    for (int i = 0; i < quantidade; i++) {
        std::cout << "Produto: " << produtos[i].nome << " - Quantidade: " << produtos[i].quantidade << " - Valor: " << produtos[i].valor << std::endl;
    }
}

void iniciarSistemaDeEstoque() {
    Produto produtos[100];
    int quantidade = 0;
    carregarProdutos(produtos, quantidade);
    int opcao;
    while (opcao != 5) {
        std::cout << "(1) para cadastrar produto:\n(2) para controlar estoque:\n(3) para registrar venda:\n(4) para gerar relatorio:\n(5) para sair:\n";
        std::cin >> opcao;
        
        switch (opcao) {
            case 1:
                cadastrarProduto(produtos, &quantidade);
                break;
            case 2:
                controlarEstoque(produtos, quantidade);
                break;
            case 3:
                registrarVenda(produtos, quantidade);
                break;
            case 4:
                gerarRelatorio(produtos, quantidade);
                break;
            case 5:
                salvarProdutos(produtos, quantidade);
                std::cout << "Saindo do sistema de estoque..." << std::endl;
                break;
            default:
                std::cout << "Opção inválida. Tente novamente." << std::endl;
        }
    }
}
