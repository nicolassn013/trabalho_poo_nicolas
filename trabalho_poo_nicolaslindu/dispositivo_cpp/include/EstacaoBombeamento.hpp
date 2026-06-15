#ifndef ESTACAO_BOMBEAMENTO_HPP
#define ESTACAO_BOMBEAMENTO_HPP
#include "Bomba.hpp"
#include "Alarme.hpp"

//regras da estacao
class EstacaoBombeamento {
private: 
  Bomba& bombaPrincipal;
  Bomba& bombaReserva;

  Alarme& alarmeNivelBaixo;
  Alarme& alarmePressaoAlta;

  bool ultimaFoiPrincipal;

public: 
  EstacaoBombeamento(
      Bomba& bombaPrincipal,
      Bomba& bobmaReserva,
      Alarme& alarmeNivelBaixo,
      Alarme& alarmePressaoAlta
  );

 void verificarNivel(double nivel);

 void verificarPressao(double pressao);

};

#endif