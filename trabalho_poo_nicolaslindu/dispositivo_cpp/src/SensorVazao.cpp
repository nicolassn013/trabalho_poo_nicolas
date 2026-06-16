#include "SensorVazao.hpp"
#include <cstdlib>

SensorVazao::SensorVazao()
    : Sensor("vazao", "L/min")
{
}

double SensorVazao::ler() {
    valor = rand() % 500;
    return valor;
}
