#ifndef ALARME_HPP
#define ALARME_HPP

#include <string>

// Representa um alarme do sistema EB-70.
// Cada alarme tem um nome, uma mensagem e um estado (ativo ou não).
// A EstacaoBombeamento é quem decide quando ativar ou desativar.
class Alarme {
private:
    std::string nome;      // ex.: "NIVEL_BAIXO"
    std::string mensagem;  // texto exibido ao operador
    bool ativo;            // true = disparado, false = normal

public:
    // Cria o alarme com nome e mensagem. Começa inativo.
    Alarme(
        const std::string& nome,
        const std::string& mensagem
    );

    void ativar();      // marca o alarme como disparado
    void desativar();   // volta ao estado normal

    bool estaAtivo() const;             // consultado pelo JSON/SQLite/Streamlit
    const std::string& getNome() const;     // retorna ref para evitar cópia
    const std::string& getMensagem() const; // idem
};

#endif