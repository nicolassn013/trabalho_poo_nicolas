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
//regra 1 + 2 (1- liga bomba e alarme nivel baixo e 2- desliga bomba e desativa alarme)
void EstacaoBombeamento::verificarNIvel(doble nivel) {
  if (nivel < 27) {
    alarmeNivelBaixo.ativar();

     if(ultimaFoiPrincipal) {
       bombaReserva.ligar();
       ultimaFoiPrincipal = false;
     }
     else {
       bombaPrincipal.ligar();
       ultimaFoiPrincipal = true;
     }
  }

  else if (nivel >80) {

    bombaPrincipal.desligar();
    bombaReserva.desligar();

    alarmeNivelBaixo.desativar();
  }
}

//regra 3 ativa pressao e alarme pressao alta

void EstacaoBombeamento::verificarPressao(double pressao) {
   if (pressao > 7.0) {
     alarmePressaoAlta.ativar();
   }
   else {
    alarmePressaoAlta.desativar();
   }
  
}

//regra extra 4 alternancia de bombas
if (ultimaFoiPrincipal)
//1 princpal, 2 reserva, 3 principal e 4 reserva
}
