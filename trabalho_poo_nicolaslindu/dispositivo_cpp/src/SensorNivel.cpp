#include "SensorNivel.hpp"
#include <cstdlib>

SensorNivel::SensorNivel()
    : Sensor("nivel", "%"),
      travado(false),
      ciclosTravados(0),
      valorTravado(0.0)
{
}

void SensorNivel::travar() {
    travado = true;
    valorTravado = valor;
}

void SensorNivel::destravar() {
    travado = false;
    ciclosTravados = 0;
}

int SensorNivel::getCiclosTravados() const {
    return ciclosTravados;
}

double SensorNivel::ler() {
    if (travado) {
        ciclosTravados++;
        return valorTravado;
    }
    valor = rand() % 101;
    return valor;
}
