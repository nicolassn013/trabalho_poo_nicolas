#include "LigarBombaCommand.hpp"

LigarBombaCommand::LigarBombaCommand(Bomba& bomba)
    : bomba(bomba)
{
}

void LigarBombaCommand::executar() {
    bomba.ligar();
}

void LigarBombaCommand::desfazer() {
    bomba.desligar();
}
