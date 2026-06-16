#ifndef SENSORNIVEL_HPP
#define SENSORNIVEL_HPP
#include "Sensor.hpp"

class SensorNivel : public Sensor {
private:
    bool travado;
    int ciclosTravados;
    double valorTravado;

public:
    SensorNivel();
    double ler() override;
    void travar();
    void destravar();
    int getCiclosTravados() const;
};

#endif
