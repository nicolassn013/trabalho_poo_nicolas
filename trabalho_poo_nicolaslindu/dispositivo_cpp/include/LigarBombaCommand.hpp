#ifndef LIGAR_BOMBA_COMMAND_HPP
#define LIGAR_BOMBA_COMMAND_HPP
#include "Comando.hpp"
#include "Bomba.hpp"

// Liga uma bomba. Simples.
// O desfazer faz o oposto — desliga. É essa simetria que faz o padrão Command funcionar.
class LigarBombaCommand : public Comando {
private:
    Bomba& bomba;

public:
    LigarBombaCommand(Bomba& bomba);
    void executar() override;
    void desfazer() override;
};

#endif
