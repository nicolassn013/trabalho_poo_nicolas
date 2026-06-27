#ifndef SENSORTURBIDEZ_HPP
#define SENSORTURBIDEZ_HPP

#include "Sensor.hpp"

// Sensor de turbidez da água — mede contaminação em NTU.
// Integrado via Factory Pattern sem alterar sensores existentes.
class SensorTurbidez : public Sensor {
public:
    SensorTurbidez();
    double ler() override;
};

#endif
