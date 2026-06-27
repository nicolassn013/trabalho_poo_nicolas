#include "SensorTurbidez.hpp"
#include <cstdlib>

SensorTurbidez::SensorTurbidez()
    : Sensor("AT-001", "NTU")
{
}

double SensorTurbidez::ler() {
    valor = static_cast<double>(std::rand() % 16);
    return valor;
}
