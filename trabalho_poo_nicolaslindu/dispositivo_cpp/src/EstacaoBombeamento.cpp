#include "EstacaoBombeamento.hpp"

EstacaoBombeamento::EstacaoBombeamento(
    Bomba& bombaPrincipal,
    Bomba& bombaReserva,
    Alarme& alarmeNivelBaixo,
    Alarme& alarmePressaoAlta
)
    : bombaPrincipal(bombaPrincipal),
      bombaReserva(bombaReserva),
      alarmeNivelBaixo(alarmeNivelBaixo),
      alarmePressaoAlta(alarmePressaoAlta),
      ultimaFoiPrincipal(false)
{
}

// Regra 1: nivel baixo -> ativa alarme e liga bomba (com alternancia)
// Regra 2: nivel alto  -> desliga bombas e desativa alarme
// Regra extra: alternancia automatica entre bombas
void EstacaoBombeamento::verificarNivel(double nivel) {
    if (nivel < 27.0) {
        alarmeNivelBaixo.ativar();

        if (ultimaFoiPrincipal) {
            bombaReserva.ligar();
            ultimaFoiPrincipal = false;
        } else {
            bombaPrincipal.ligar();
            ultimaFoiPrincipal = true;
        }
    } else if (nivel > 80.0) {
        bombaPrincipal.desligar();
        bombaReserva.desligar();
        alarmeNivelBaixo.desativar();
    }
}

// Regra 3: pressao alta -> ativa alarme de pressao
void EstacaoBombeamento::verificarPressao(double pressao) {
    if (pressao > 7.0) {
        alarmePressaoAlta.ativar();
    } else {
        alarmePressaoAlta.desativar();
    }
}
