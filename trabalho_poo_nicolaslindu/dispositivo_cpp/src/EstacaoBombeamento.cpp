#include "EstacaoBombeamento.hpp"
 
// A bomba principal é sempre a primeira a ser acionada na partida.
// As bombas e alarmes chegam prontos de fora — quem os cria é a Factory.
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
 
// Regra 1 — nível baixo (< 27%):
//   Dispara o alarme e liga a próxima bomba na fila.
//   As bombas se alternam a cada acionamento para distribuir o desgaste.
//
// Regra 2 — nível alto (> 80%):
//   Desliga as duas bombas e limpa o alarme de nível.
//
// Entre 27% e 80% não faz nada — essa zona morta evita que as bombas
// fiquem ligando e desligando o tempo todo por variações pequenas.
void EstacaoBombeamento::verificarNivel(double nivel) {
 
    if (nivel < NIVEL_BAIXO_LIMITE) {        // Regra 1
        alarmeNivelBaixo.ativar();
 
        // alterna entre principal e reserva a cada chamada
        if (ultimaFoiPrincipal) {
            bombaReserva.ligar();
            ultimaFoiPrincipal = false;
        } else {
            bombaPrincipal.ligar();
            ultimaFoiPrincipal = true;
        }
 
    } else if (nivel > NIVEL_ALTO_LIMITE) {  // Regra 2
        bombaPrincipal.desligar();
        bombaReserva.desligar();
        alarmeNivelBaixo.desativar();
    }
 
    // zona morta: sem ação
}
 
// Regra 3 — pressão alta (> 7.0 bar): dispara o alarme.
// Voltou ao normal: limpa o alarme.
// Decidir se desliga a bomba por pressão é responsabilidade de quem chama.
void EstacaoBombeamento::verificarPressao(double pressao) {
 
    if (pressao > PRESSAO_ALTA_LIMITE) {
        alarmePressaoAlta.ativar();
    } else {
        alarmePressaoAlta.desativar();
    }
}