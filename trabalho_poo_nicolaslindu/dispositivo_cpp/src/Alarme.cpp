#include "Alarme.hpp"

Alarme::Alarme(
  const std::string& nome,
  const std::string& mensagem

)
  : nome(nome),
    mensagem(mensagem),
    ativo(false) 
{
}

void Alarme::ativar(){
    ativo = true;
}

void Alarme::desativar(){
    ativo = false;
}

bool Alarme::estaAtivo() const {
   return ativo;
}

std::string Alarme::getNome() const{
  return nome;
}

std::string Alarme::getMensagem() const{
  return mensagem;

 Alarme alarmeBombaBloqueada("Bomba Bloqueada", "Falha na bomba");
  if(bombaPrincipal.estaBloqueada()){
    alarmeBombaBloqueada.ativar();
  }
}