#ifndef SENSORNIVEL_HPP
#define SENSORNIVEL_HPP
#include "Sensor.hpp"

//sensor nivel reservatorio
class SensorNivel: public Sensor{
//falha travar
private: 
    bool travado;
    int ciclosTravados;
    double valorTravado;

    void travar();

    void destravar();

    bool estaTravado() const;

public: 
    SensorNivel();
    double ler() override;
};
#endif