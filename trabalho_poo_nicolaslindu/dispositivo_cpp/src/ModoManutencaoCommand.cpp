#include "ModoManutencaoCommand.hpp"

ModoManutencaoCommand::ModoManutencaoCommand(Bomba& bomba)
    : bomba(bomba)
{
}

void ModoManutencaoCommand::executar() {
    // Bloqueia a bomba — entra em manutenção.
    bomba.bloquear();
}

void ModoManutencaoCommand::desfazer() {
    // Sai da manutenção — desbloqueia e volta ao normal.
    bomba.desbloquear();
}
