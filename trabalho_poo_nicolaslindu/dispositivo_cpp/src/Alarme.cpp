#include "Alarme.hpp"

// ------------------------------------------------------------
// Construtor
// Inicializa nome e mensagem via lista de inicialização.
// O alarme começa sempre no estado inativo (ativo = false).
// ------------------------------------------------------------
Alarme::Alarme(
    const std::string& nome,
    const std::string& mensagem
)
    : nome(nome),
      mensagem(mensagem),
      ativo(false)
{
}

// ------------------------------------------------------------
// ativar()
// Sinaliza a ocorrência de um evento anormal. A EstacaoBombeamento
// chama este método quando uma condição operacional é violada.
// ------------------------------------------------------------
void Alarme::ativar() {
    ativo = true;
}

// ------------------------------------------------------------
// desativar()
// Limpa o estado do alarme quando a condição retorna ao normal.
// ------------------------------------------------------------
void Alarme::desativar() {
    ativo = false;
}

// ------------------------------------------------------------
// estaAtivo()
// Consultado pelo sistema de persistência (JSON/SQLite) e pela
// interface Streamlit para exibir o estado atual ao operador.
// ------------------------------------------------------------
bool Alarme::estaAtivo() const {
    return ativo;
}

// ------------------------------------------------------------
// getNome() / getMensagem()
// Retornam referência constante para evitar cópia desnecessária
// de std::string. Seguro porque o objeto Alarme tem ciclo de
// vida maior que qualquer uso dessas referências.
// ------------------------------------------------------------
const std::string& Alarme::getNome() const {
    return nome;
}

const std::string& Alarme::getMensagem() const {
    return mensagem;
}