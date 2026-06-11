#ifndef BOMBA_HPP
#define BOMBA_HPP
#include <string>

//classe base para as bombas
class Bomba{
//nao podem ser alterados diretamente
private:
std::string nome;
bool ligada;
bool bloqueada;

public:
  Bomba(const std::string& nome);

  void ligar();
  void desligar();
  void bloquear();
  void desbloquear();
  bool estaLigada() const;
  bool estaBloqueada() const;

  std::string getNome() const

};

#endif