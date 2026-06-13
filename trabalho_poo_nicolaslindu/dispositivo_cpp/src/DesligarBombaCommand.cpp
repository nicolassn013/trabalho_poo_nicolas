#include "DesligarBombaCommand.hpp"

DesligarBombaCommand::DesligarBombaCommand(Bomba& bomba) : bomba(bomba)
{
}

void DesligarBombaCommand::executar() {
  bobma.desligar();
}

void DesligarBombaCommnad::desfazer() {
  bomba.ligar();
}