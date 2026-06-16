#ifndef SENSOR_HPP
#define SENSOR_HPP
#include <string>

class Sensor {
protected:
    std::string tag;
    std::string unidade;
    double valor;

public:
    Sensor(
        const std::string& tag,
        const std::string& unidade
    );

    virtual ~Sensor() = default;

    virtual double ler() = 0;

    std::string getTag() const;
    std::string getUnidade() const;
    double getValor() const;
};

#endif
