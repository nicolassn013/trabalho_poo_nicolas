#ifndef COMANDO_HPP
#define COMANDO_HPP

//base padrao command
class Comando {
public: 
  virtual void executar() = 0;

  virtual void desfazer() = 0;

 virtual ~Comando() = default;
};

#endif