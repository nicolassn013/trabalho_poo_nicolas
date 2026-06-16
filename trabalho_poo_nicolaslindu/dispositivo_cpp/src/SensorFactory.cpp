#include "SensorFactory.hpp"
#include "SensorNivel.hpp"
#include "SensorPressao.hpp"
#include "SensorVazao.hpp"
#include "SensorTemperatura.hpp"
#include <stdexcept>

std::unique_ptr<Sensor> SensorFactory::criar(const std::string& tipo) {
    if (tipo == "nivel") {
        return std::unique_ptr<Sensor>(new SensorNivel());
    }
    if (tipo == "pressao") {
        return std::unique_ptr<Sensor>(new SensorPressao());
    }
    if (tipo == "vazao") {
        return std::unique_ptr<Sensor>(new SensorVazao());
    }
    if (tipo == "temperatura") {
        return std::unique_ptr<Sensor>(new SensorTemperatura());
    }
    throw std::invalid_argument("Tipo de sensor desconhecido: " + tipo);
}
