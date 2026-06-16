#include "ModoManutencaoCommand.hpp"

ModoManutencaoCommand::ModoManutencaoCommand(Bomba& bomba)
    : bomba(bomba)
{
}

void ModoManutencaoCommand::executar() {
    bomba.bloquear();
}

void ModoManutencaoCommand::desfazer() {
    bomba.desbloquear();
}
