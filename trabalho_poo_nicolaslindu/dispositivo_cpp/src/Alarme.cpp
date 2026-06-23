#include "Alarme.hpp"
 
// Começa sempre inativo — quem ativa é a EstacaoBombeamento.
Alarme::Alarme(
    const std::string& nome,
    const std::string& mensagem
)
    : nome(nome),
      mensagem(mensagem),
      ativo(false)
{
}
 
// Algo saiu do normal — marca o alarme como disparado.
void Alarme::ativar() {
    ativo = true;
}
 
// Condição voltou ao normal — limpa o alarme.
void Alarme::desativar() {
    ativo = false;
}
 
// Consultado toda vez que o sistema precisa saber se o alarme está on.
bool Alarme::estaAtivo() const {
    return ativo;
}
 
// Retorna referência direta para não copiar a string à toa.
const std::string& Alarme::getNome() const {
    return nome;
}
 
const std::string& Alarme::getMensagem() const {
    return mensagem;
}
 