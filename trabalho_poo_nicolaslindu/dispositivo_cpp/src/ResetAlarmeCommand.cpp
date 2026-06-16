#include "ResetAlarmeCommand.hpp"

ResetAlarmeCommand::ResetAlarmeCommand(Alarme& alarme)
    : alarme(alarme)
{
}

void ResetAlarmeCommand::executar() {
    alarme.desativar();
}

void ResetAlarmeCommand::desfazer() {
    alarme.ativar();
}
