#include "Bomba.hpp"

Bomba::Bomba(const std::string& nome)
    : nome(nome),
      ligada(false),
      bloqueada(false)
{
}

void Bomba::ligar() {
    if (!bloqueada) {
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
    bloqueada = false;
}

bool Bomba::estaLigada() const {
    return ligada;
}

bool Bomba::estaBloqueada() const {
    return bloqueada;
}

std::string Bomba::getNome() const {
    return nome;
}

// Retorna o status textual da bomba para escrita no JSON.
// Prioridade: bloqueada > ligada > ok.
std::string Bomba::getStatus() const {
    if (bloqueada) return "FALHA";
    if (ligada)    return "LIGADA";
    return "OK";
}