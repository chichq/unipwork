
#ifndef LOGIN_H
#define LOGIN_H

#include <windows.h>
#include <string>


void setConsoleColor(WORD color);
void resetConsoleColor();
bool showLoginScreen();
bool showAdminLoginScreen();
void alterarSenha();


void carregarSenhaDoArquivo();
void salvarSenhaNoArquivo();


std::string codificarSenha(const std::string& senha, int chave = 3);    
std::string decodificarSenha(const std::string& senhaCodificada, int chave = 3); 

#endif
