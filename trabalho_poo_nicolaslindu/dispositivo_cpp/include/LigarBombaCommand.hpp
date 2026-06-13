#ifndef LIGAR_BOMBA_COMMAND_HPP
#define LIGAR_BOBA_COMMAND_HPP
#include "Comando.hpp"
#include "Bomba.hpp"

//comando ligar bomba
class LigarBombaCommand : public Comando {
private:
  Bomba& bomba;

public:
   LigarBombaCommand(Bomba& bomba);

  void executar() override;

  void desfazer() override;

};

#endif