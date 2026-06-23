#ifndef ESTACAO_BOMBEAMENTO_HPP
#define ESTACAO_BOMBEAMENTO_HPP
 
#include "Bomba.hpp"
#include "Alarme.hpp"
 
// Coração do sistema EB-70: aplica as três regras operacionais da estação.
//   Regra 1 — nível baixo:  dispara alarme e liga uma bomba (alternando entre elas).
//   Regra 2 — nível alto:   desliga tudo e limpa o alarme de nível.
//   Regra 3 — pressão alta: dispara ou limpa o alarme de pressão.
class EstacaoBombeamento {
public:
    // Limiares da assinatura EB-70 — não alterar esses valores.
    static constexpr double NIVEL_BAIXO_LIMITE  = 27.0; // % — abaixo disso liga bomba
    static constexpr double NIVEL_ALTO_LIMITE   = 80.0; // % — acima disso desliga tudo
    static constexpr double PRESSAO_ALTA_LIMITE =  7.0; // bar — acima disso alarme de pressão
 
private:
    Bomba& bombaPrincipal;     // bomba A
    Bomba& bombaReserva;       // bomba B (alternância automática)
    Alarme& alarmeNivelBaixo;  // dispara quando o nível cai demais
    Alarme& alarmePressaoAlta; // dispara quando a pressão passa do limite
    bool ultimaFoiPrincipal;   // lembra qual bomba foi usada por último
 
public:
    // Recebe as bombas e alarmes já criados pela Factory.
    EstacaoBombeamento(
        Bomba& bombaPrincipal,
        Bomba& bombaReserva,
        Alarme& alarmeNivelBaixo,
        Alarme& alarmePressaoAlta
    );
 
    // Aplica as regras 1 e 2.
    // Entre 27% e 80% não faz nada (zona morta intencional).
    void verificarNivel(double nivel);
 
    // Aplica a regra 3.
    void verificarPressao(double pressao);
};
 
#endif