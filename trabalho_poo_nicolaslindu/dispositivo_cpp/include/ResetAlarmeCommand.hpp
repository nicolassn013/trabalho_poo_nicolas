#ifndef RESET_ALARME_COMMAND_HPP
#define RESET_ALARME_COMMAND_HPP
#include "Comando.hpp"
#include "Alarme.hpp"

// Reseta (desativa) um alarme.
// O desfazer reativa o alarme — faz sentido dentro do padrão Command,
// mas em produção real seria necessário validar se a condição ainda existe.
class ResetAlarmeCommand : public Comando {
private:
    Alarme& alarme;

public:
    ResetAlarmeCommand(Alarme& alarme);
    void executar() override;
    void desfazer() override;
};

#endif
