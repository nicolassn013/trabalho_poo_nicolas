#include "SensorPressao.hpp"
#include <cstdlib>

SensorPressao::SensorPressao()
    : Sensor("pressao", "bar")
{
}

double SensorPressao::ler() {
    valor = (rand() % 80) / 10.0;
    return valor;
}
