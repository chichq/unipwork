#include <iostream>
#include "login.h"
#include "produto.h"

int main() {
    carregarSenhaDoArquivo(); 

    int escolha;

    std::cout << "Escolha uma opcao:\n";
    std::cout << "(1) Login normal\n";
    std::cout << "(2) Area administrativa\n";
    std::cin >> escolha;

    if (escolha == 1) {
        if (showLoginScreen()) {
            iniciarSistemaDeEstoque();
        } else {
            std::cout << "Acesso negado. Encerrando o programa." << std::endl;
            return 1;
        }
    } else if (escolha == 2) {
        if (showAdminLoginScreen()) {
            alterarSenha();
        } else {
            std::cout << "Acesso negado à área administrativa." << std::endl;
        }
    } else {
        std::cout << "Opcao invalida. Encerrando o programa." << std::endl;
        return 1;
    }

    return 0;
}
