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

    // Retorna o status textual da bomba para escrita no JSON.
    // Segue o mesmo padrão de statusNivel() e statusPressao() do main.
    std::string getStatus() const; // "FALHA", "LIGADA" ou "OK"
};
#endif