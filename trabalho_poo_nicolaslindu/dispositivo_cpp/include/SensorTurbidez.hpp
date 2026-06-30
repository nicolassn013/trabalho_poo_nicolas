#ifndef SENSORTURBIDEZ_HPP
#define SENSORTURBIDEZ_HPP

#include "Sensor.hpp"

// Sensor de turbidez da água, mede contaminação em NTU.
class SensorTurbidez : public Sensor {
public:
    SensorTurbidez();
    double ler() override;
};

#endif
