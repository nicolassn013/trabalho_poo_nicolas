#include "SensorFactory.hpp"
#include "SensorNivel.hpp"
#include "SensorPressao.hpp"
#include "SensorVazao.hpp"
#include "SensorTemperatura.hpp"
#include <stdexcept>

std::unique_ptr<Sensor> SensorFactory::criar(const std::string& tipo) {
    if (tipo == "nivel") {
        return std::make_unique<SensorNivel>();
    } else if (tipo == "pressao") {
        return std::make_unique<SensorPressao>();
    } else if (tipo == "vazao") {
        return std::make_unique<SensorVazao>();
    } else if (tipo == "temperatura") {
        return std::make_unique<SensorTemperatura>();
    } else {
        throw std::invalid_argument("Tipo de sensor desconhecido: " + tipo);
    }
}
