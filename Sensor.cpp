#include "Sensor.hpp"

Sensor::Sensor(
    const std::string& tag,
    const std::string& unidade
)
:tag(tag),unidade(unidade),valor(0.0){
} 
std::string Sensor::getTag()const{
  return tag;
}
std::string Sensor::getUnidade()const{
  return unidade;
}
double Sensor::getValor() const{
  return valor;
}