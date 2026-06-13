#ifndef DESLIGAR_BOMBA_COMMNAD_HPP
#define DESLIGAR_BOMBA_COMMAND_HPP
#include "Comando.hpp"
#include "Bomba.hpp"

//desligar bomba
class DesligarBombaCommand : public Comando{
private:
  Bomba& bomba;

public:
  DesligarBombaCommand(Bomba& bomba);

  void executar() override;

  void desfazer() override;
};

#endif