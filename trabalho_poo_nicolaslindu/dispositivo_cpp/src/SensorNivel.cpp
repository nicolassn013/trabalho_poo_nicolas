#include "SensorNivel.hpp"
//biblioteca para gerar numeros aleatorios
#include <cstdlib>

SensorNivel::SensorNivel():Sensor("nivel","%")
: travado(false)
  ciclosTravado(0)
  valorTravado(0.0)
{
}

void SensorNivel::travar(){
  travado = true;
  
  valorTravado = valor;
}

void SensorNivel::destravar(){
  travado = false;

  ciclosTravad = 0;
}

double SensorNivel::ler(){
  if(travado) {
    ciclosTravados++;

    return valorTravado;
  }

  valor = gerarValor();

  return valor;
}

double SensorNivel::ler(){
//simula valor entre 0 e 100
valor = rand() % 101;

return valor;
}