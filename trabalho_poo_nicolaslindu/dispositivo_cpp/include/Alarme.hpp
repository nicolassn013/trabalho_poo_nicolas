#ifndef ALARME_HPP
#define ALARME_HPP
#include <string> 

//alarme sistema supervisorio
class Alarme {
private: 
  std::string nome;
  std::string mensagem; 
  bool ativo;

public:
  Alarme(
    const std::string& nome,
    const std::string& mensagem
);

void ativar();
void desativar();
bool estaAtivo() const;
std::string getNome() const;
std::string getMensagem() const;

};

#endif