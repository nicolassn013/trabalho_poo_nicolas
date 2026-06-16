#ifndef BOMBA_HPP
#define BOMBA_HPP
#include <string>

class Bomba {
private:
    std::string nome;
    bool ligada;
    bool bloqueada;

public:
    Bomba(const std::string& nome);

    void ligar();
    void desligar();
    void bloquear();
    void desbloquear();
    bool estaLigada() const;
    bool estaBloqueada() const;
    std::string getNome() const;
};

#endif
