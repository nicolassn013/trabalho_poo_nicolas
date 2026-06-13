#include "LigarBombaCommand.hpp"

LigarBombaCommand::LigarBombaCommand(BombaM&boma): bomba(bomba)
{
}

void LigarBombaCommand::executar() {
  bomba.ligar();
}

void LigarBombaCommand::desfazer() {
  bomba.desligar();
}