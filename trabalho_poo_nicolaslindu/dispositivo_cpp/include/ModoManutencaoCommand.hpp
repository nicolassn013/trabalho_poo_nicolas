#ifndef MODO_MANUTENCAO_COMMAND_HPP
#define MODO_MANUTENCAO_COMMAND_HPP
#include "Comando.hpp"
#include "Bomba.hpp"

//bota bomba em manutencao
class ModoManutencaoCommand : public Comando {
private:
   Bomba& bomba;

public: 
  ModoManutencaoCommand(Bomba& bomba);

  void executar() override;

  void desfazer() override;

};

#endif