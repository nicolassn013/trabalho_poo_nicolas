#ifndef MODO_MANUTENCAO_COMMAND_HPP
#define MODO_MANUTENCAO_COMMAND_HPP
#include "Comando.hpp"
#include "Bomba.hpp"

// Coloca a bomba em modo de manutenção, bloqueando qualquer operação.
// O desfazer desbloqueia e devolve a bomba ao estado normal.
class ModoManutencaoCommand : public Comando {
private:
    Bomba& bomba;

public:
    ModoManutencaoCommand(Bomba& bomba);
    void executar() override;
    void desfazer() override;
};

#endif
