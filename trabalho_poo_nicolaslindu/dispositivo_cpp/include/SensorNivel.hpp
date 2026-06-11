#ifndef SENSORNIVEL_HPP
#define SENSORNIVEL_HPP
#include "Sensor.hpp"

//sensor nivel reservatorio
class SensorNivel: public Sensor{
public: 
    SensorNivel();
    double ler() override;
};
#endif