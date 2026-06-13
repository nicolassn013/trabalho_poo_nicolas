#include <iostream>
#include "SensorNivel.hpp"
#include "SensorPressao.hpp"
#include "SensorVazao.hpp"
#include "SensorTemperatura.hpp"
#include "Bomba.hpp"
#include "SensorFactory.hpp"
#include "Alarme.hpp"


int main() {

//sensores da estacao
  SensorNivel nivel;
  SensorPressao pressao;
  SensorVazao vazao;
  SensorTemperatura temperatura;

  //mostra leituras
  std::cout << nivel.ler() << std::endl;
  std::cout << pressao.ler() << std::endl;
  std::cout << vazao.ler() << std::endl;
  std::cout << temperatura.ler() << std::endl;

 //bombas 
Bomba bombaPrincipal("Bomba Principal");
Bomba bombaReserva("Bomba Reserva");

//    
bombaPrincipal.ligar();
  
  std::cout
    << bombaPrincipal.getNome()                <<"ligada: "
    << bombaPrincipal.estaLigada()
    << std::endl;

  bombaReserva.ligar();
  
  std::cout << bombaReserva.getNome()<<"ligada: " << bombaReserva.estaLigada()<< std::endl;
  
  std::cout << bombaPrincipal.getNome()<< "bloqueada:" << bombaPrincipal.estaBloqueada() << std::endl;

  std::cout << bombaReserva.getNome()<< "bloqueada:" << bombaReserva.estaBloqueada() << std::endl;

  //sensores factory  
  Sensor* sensorNivel =
      SensorFactory::criarSensor("nivel");

  Sensor* sensorPressao =
      SensorFactory::criarSensor("pressao");

  std::cout
      << sensorNivel->getTag()
      << ": "
      << sensorNivel->ler()
      << " "
      << sensorNivel->getUnidade()
      << std::endl;

  std::cout
      << sensorPressao->getTag()
      << ": "
      << sensorPressao->ler()
      << " "
      << sensorPressao->getUnidade()
      << std::endl;

  delete sensorNivel;
  delete sensorPressao;
    
//alarmes
    Alarme nivelBaixo(
        "Nivel Baixo",
        "Nivel abaixo de 27%"
    );

    nivelBaixo.ativar();

    std::cout
        << nivelBaixo.getNome()
        << " ativo: "
        << nivelBaixo.estaAtivo()
        << std::endl;

    std::cout
        << nivelBaixo.getMensagem()
        << std::endl;


//comandos 
    Bomba bombaPrincipal("Bomba Principal");

    LigarBombaCommand ligar(bombaPrincipal);

    ligar.executar();

    std::cout
        << bombaPrincipal.getNome()
        << " ligada: "
        << bombaPrincipal.estaLigada()
        << std::endl;

    ligar.desfazer();

    std::cout
        << bombaPrincipal.getNome()
        << " ligada: "
        << bombaPrincipal.estaLigada()
        << std::endl;

    
    
  return 0;

}