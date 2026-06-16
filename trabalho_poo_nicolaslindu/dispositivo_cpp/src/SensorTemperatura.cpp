#include "SensorTemperatura.hpp"
#include <cstdlib>

SensorTemperatura::SensorTemperatura()
    : Sensor("temperatura", "C")
{
}

double SensorTemperatura::ler() {
    valor = 20 + (rand() % 21);
    return valor;
}
