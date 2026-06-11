#include "Bomba.hpp"

Bomba::Bomba(const std::string& nome)
   : nome(nome),
     ligada(false),
     bloqueada(false)
{
} 

 void Bomba::ligar() {
   //nao liga se estiver block
   if(!bloqueada){
     ligada = true;   
   } 
 }

void Bomba::desligar() {
  ligada = false;
}

void Bomba::bloquear() {
  bloqueada = true;
}

void Bomba::desbloquear() {
  bloqueada = false
}

bool Bomba::estaLigada() const {
  return ligada;
}

bool Bomba::estaBloqueada() const {
  return bloqueada;
}

std::string Bomba::getNome() const{
  return nome;
}