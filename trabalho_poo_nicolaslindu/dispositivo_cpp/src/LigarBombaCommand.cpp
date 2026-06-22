#include "LigarBombaCommand.hpp"

LigarBombaCommand::LigarBombaCommand(Bomba& bomba)
    : bomba(bomba)
{
}

void LigarBombaCommand::executar() {
    bomba.ligar();
}

void LigarBombaCommand::desfazer() {
    // Desfaz ligando? Desliga. Faz sentido.
    bomba.desligar();
}
