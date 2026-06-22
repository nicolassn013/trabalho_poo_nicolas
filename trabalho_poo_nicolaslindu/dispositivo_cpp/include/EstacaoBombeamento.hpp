#ifndef ESTACAO_BOMBEAMENTO_HPP
#define ESTACAO_BOMBEAMENTO_HPP

#include "Bomba.hpp"
#include "Alarme.hpp"

/**
 * @class EstacaoBombeamento
 * @brief Núcleo de regras operacionais do sistema supervisório EB-70.
 *
 * Implementa as três regras fundamentais da estação:
 *   - Regra 1 (nível baixo):  aciona alarme e ativa bomba com alternância automática.
 *   - Regra 2 (nível alto):   desliga todas as bombas e desativa o alarme de nível.
 *   - Regra 3 (pressão alta): aciona ou desativa o alarme de pressão.
 *
 * Assinatura operacional EB-70 (não alterar):
 *   - NIVEL_BAIXO_LIMITE  = 27%
 *   - NIVEL_ALTO_LIMITE   = 80%
 *   - PRESSAO_ALTA_LIMITE = 7.0 bar
 *
 * Padrões aplicados: Factory (criação da estação) e Command (ações nas bombas).
 */
class EstacaoBombeamento {
public:
    // ----------------------------------------------------------
    // Constantes operacionais da assinatura EB-70.
    // Centralizadas aqui para evitar magic numbers no código e
    // facilitar rastreabilidade em relatórios acadêmicos.
    // ----------------------------------------------------------

    /** Limiar inferior de nível do reservatório (%). Abaixo: aciona bomba. */
    static constexpr double NIVEL_BAIXO_LIMITE  = 27.0;

    /** Limiar superior de nível do reservatório (%). Acima: desliga bombas. */
    static constexpr double NIVEL_ALTO_LIMITE   = 80.0;

    /** Limiar de pressão da linha (bar). Acima: aciona alarme de pressão. */
    static constexpr double PRESSAO_ALTA_LIMITE = 7.0;

private:
    Bomba& bombaPrincipal;    ///< Bomba primária da estação
    Bomba& bombaReserva;      ///< Bomba de reserva (alternância automática)
    Alarme& alarmeNivelBaixo; ///< Alarme ativado quando nível < NIVEL_BAIXO_LIMITE
    Alarme& alarmePressaoAlta;///< Alarme ativado quando pressão > PRESSAO_ALTA_LIMITE
    bool ultimaFoiPrincipal;  ///< Controla qual bomba será acionada no próximo ciclo

public:
    /**
     * @brief Constrói a estação associando bombas e alarmes já existentes.
     * @param bombaPrincipal    Bomba primária.
     * @param bombaReserva      Bomba de reserva.
     * @param alarmeNivelBaixo  Alarme de nível baixo.
     * @param alarmePressaoAlta Alarme de pressão alta.
     */
    EstacaoBombeamento(
        Bomba& bombaPrincipal,
        Bomba& bombaReserva,
        Alarme& alarmeNivelBaixo,
        Alarme& alarmePressaoAlta
    );

    /**
     * @brief Aplica as regras de nível (Regras 1 e 2).
     *
     * - Se nivel < NIVEL_BAIXO_LIMITE: ativa alarme e aciona a próxima
     *   bomba na sequência de alternância.
     * - Se nivel > NIVEL_ALTO_LIMITE:  desliga ambas as bombas e
     *   desativa o alarme de nível baixo.
     * - Entre os limiares: nenhuma ação (zona morta intencional).
     *
     * @param nivel Nível atual do reservatório em percentual (0–100).
     */
    void verificarNivel(double nivel);

    /**
     * @brief Aplica a regra de pressão (Regra 3).
     *
     * - Se pressao > PRESSAO_ALTA_LIMITE: ativa o alarme de pressão.
     * - Caso contrário: desativa o alarme de pressão.
     *
     * @param pressao Pressão atual da linha em bar.
     */
    void verificarPressao(double pressao);
};

#endif // ESTACAO_BOMBEAMENTO_HPP