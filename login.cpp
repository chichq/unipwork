#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include "login.h"

std::string currentPassword = "123"; // Senha padrão

std::string codificarSenha(const std::string& senha, int chave) {
    std::string codificada;
    for (char c : senha) {
        codificada += c + chave;
    }
    return codificada;
}

std::string decodificarSenha(const std::string& senhaCodificada, int chave) {
    std::string decodificada;
    for (char c : senhaCodificada) {
        decodificada += c - chave;
    }
    return decodificada;
}

void carregarSenhaDoArquivo() {
    std::ifstream arquivo("senha.txt");
    if (arquivo.is_open()) {
        std::string senhaCodificada;
        std::getline(arquivo, senhaCodificada);
        currentPassword = decodificarSenha(senhaCodificada);
        arquivo.close();
    }
}

void salvarSenhaNoArquivo() {
    std::ofstream arquivo("senha.txt");
    if (arquivo.is_open()) {
        std::string senhaCodificada = codificarSenha(currentPassword);
        arquivo << senhaCodificada;
        arquivo.close();
    }
}


std::string digitarSenhaOculta() {
    std::string senha;
    char ch;
    while ((ch = _getch()) != '\r') { 
        if (ch == '\b' && !senha.empty()) {
            
            std::cout << "\b \b";
            senha.pop_back();
        } else if (ch != '\b') {
            
            senha += ch;
            std::cout << '*'; 
        }
    }
    std::cout << std::endl;
    return senha;
}

// Login
bool showLoginScreen() {
    std::string username, password;
    std::cout << "Usuario: ";
    std::cin >> username;

    std::cout << "Senha: ";
    password = digitarSenhaOculta();

    return username == "Carlos" && password == currentPassword;
}

// Login adm
bool showAdminLoginScreen() {
    std::string adminPassword;
    std::cout << "Digite a senha do administrador: ";
    adminPassword = digitarSenhaOculta();

    return adminPassword == currentPassword;
}


void alterarSenha() {
    std::string novaSenha;
    std::cout << "Digite a nova senha: ";
    novaSenha = digitarSenhaOculta();

    currentPassword = novaSenha;
    salvarSenhaNoArquivo(); 
    std::cout << "Senha alterada com sucesso!" << std::endl;
}
