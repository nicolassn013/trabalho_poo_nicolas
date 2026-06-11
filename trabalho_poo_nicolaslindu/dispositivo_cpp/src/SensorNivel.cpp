#include "SensorNivel.hpp"
//biblioteca para gerar numeros aleatorios
#include <cstdlib>

SensorNivel::SensorNivel():Sensor("nivel","%"){
}

double SensorNivel::ler(){
//simula valor entre 0 e 100
valor = rand() % 101;

return valor;
}