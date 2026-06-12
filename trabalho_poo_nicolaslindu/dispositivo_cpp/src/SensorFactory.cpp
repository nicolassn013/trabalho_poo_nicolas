#include "SensorFactory.hpp"
#include "SensorNivel.hpp"
#include "SensorPressao.hpp"
#include "SensorVazao.hpp"
#include "SensorTemperatura.hpp"

Sensor* SensorFactory::criarSensor(const std::string& tipo) {
    if (tipo == "nivel") {
        return new SensorNivel()
    }
    if (tipo == "pressao") {
        return new SensorPressao()
    } 
    if (tipo == "vazao") {
        return new SensorVazao()
    }
    if (tipo == "temperatura") {
        return new SensorTemperatura()
    }

 return nullptr;
}

