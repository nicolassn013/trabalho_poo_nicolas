#include "DesligarBombaCommand.hpp"

DesligarBombaCommand::DesligarBombaCommand(Bomba& bomba)
    : bomba(bomba)
{
}

void DesligarBombaCommand::executar() {
    bomba.desligar();
}

void DesligarBombaCommand::desfazer() {
    bomba.ligar();
}
