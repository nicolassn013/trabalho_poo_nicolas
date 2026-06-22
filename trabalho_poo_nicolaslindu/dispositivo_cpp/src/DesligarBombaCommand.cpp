#include "DesligarBombaCommand.hpp"

DesligarBombaCommand::DesligarBombaCommand(Bomba& bomba)
    : bomba(bomba)
{
}

void DesligarBombaCommand::executar() {
    bomba.desligar();
}

void DesligarBombaCommand::desfazer() {
    // Desfaz desligando? Liga de volta. Inverso exato.
    bomba.ligar();
}
