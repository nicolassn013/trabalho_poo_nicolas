#ifndef DESLIGAR_BOMBA_COMMAND_HPP
#define DESLIGAR_BOMBA_COMMAND_HPP
#include "Comando.hpp"
#include "Bomba.hpp"

// Desliga uma bomba.
// O desfazer liga ela de volta — inverso exato do LigarBombaCommand.
class DesligarBombaCommand : public Comando {
private:
    Bomba& bomba;

public:
    DesligarBombaCommand(Bomba& bomba);
    void executar() override;
    void desfazer() override;
};

#endif
