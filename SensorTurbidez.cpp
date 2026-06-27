#include "SensorTurbidez.hpp"
#include <cstdlib>

// Segue o mesmo padrão dos outros sensores: inicializa tag e unidade via Sensor().
SensorTurbidez::SensorTurbidez()
    : Sensor("AT-001", "NTU")
{
}

// simula leitura entre 0 e 15 NTU.
//  3 faixas de status:0-5 NTU  → OK ; 5-10 NTU → ALERTA ; >10 NTU  → FALHA
double SensorTurbidez::ler() {
    valor = static_cast<double>(std::rand() % 16);
    return valor;
}