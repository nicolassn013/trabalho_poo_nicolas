#ifndef COMANDO_HPP
#define COMANDO_HPP

// Interface base do padrão Command (GoF).
// Toda ação do sistema passa por aqui: executar faz a coisa,
// desfazer volta atrás. Simples assim.
class Comando {
public:
    virtual void executar() = 0;
    virtual void desfazer() = 0;
    virtual ~Comando() = default;
};

#endif
