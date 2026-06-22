#include "ResetAlarmeCommand.hpp"

ResetAlarmeCommand::ResetAlarmeCommand(Alarme& alarme)
    : alarme(alarme)
{
}

void ResetAlarmeCommand::executar() {
    // Reseta o alarme — desativa ele.
    alarme.desativar();
}

void ResetAlarmeCommand::desfazer() {
    // Desfaz o reset reativando o alarme.
    // Em produção isso exigiria verificar se a condição ainda é válida,
    // mas aqui cumpre o contrato do padrão Command.
    alarme.ativar();
}
