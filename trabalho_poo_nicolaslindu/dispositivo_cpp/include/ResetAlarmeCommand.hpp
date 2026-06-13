#ifndef RESET_ALARME_COMMAND_HPP
#define RESET_ALARME_COMMAND_HPP
#include "Comando.hpp"
#include "Alarme.hpp"

//resetar um alarme
class ResetAlarmeCommand : public Comando {
private:
  Alarme& alarme;

public: 
  ResetAlarmeCommand(Alarme& alarme);

  void executar() override;

  void desfazer() override;
};

#endif