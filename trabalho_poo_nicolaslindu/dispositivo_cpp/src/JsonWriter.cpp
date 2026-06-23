#include "JsonWriter.hpp"
#include <ctime>
#include <sstream>
#include <iomanip>
#include <stdexcept>

JsonWriter::JsonWriter(const std::string& caminhoArquivo, const std::string& estacao)
    : caminhoArquivo(caminhoArquivo),
      estacao(estacao)
{
    arquivo.open(caminhoArquivo, std::ios::app);
    if (!arquivo.is_open()) {
        throw std::runtime_error("Nao foi possivel abrir o arquivo: " + caminhoArquivo);
    }
}

JsonWriter::~JsonWriter() {
    if (arquivo.is_open()) {
        arquivo.close();
    }
}

std::string JsonWriter::gerarTimestamp() const {
    std::time_t agora = std::time(nullptr);
    std::tm* tm_local = std::localtime(&agora);
    std::ostringstream oss;
    oss << std::put_time(tm_local, "%Y-%m-%dT%H:%M:%S");
    return oss.str();
}

std::string JsonWriter::escaparString(const std::string& s) const {
    std::string resultado;
    for (char c : s) {
        if      (c == '"')  resultado += "\\\"";
        else if (c == '\\') resultado += "\\\\";
        else if (c == '\n') resultado += "\\n";
        else if (c == '\r') resultado += "\\r";
        else if (c == '\t') resultado += "\\t";
        else resultado += c;
    }
    return resultado;
}

void JsonWriter::escrever(
    const std::string& tag,
    const std::string& tipo,
    double valor,
    const std::string& unidade,
    const std::string& status
) {
    if (!arquivo.is_open()) {
        throw std::runtime_error("Arquivo nao esta aberto para escrita.");
    }
    std::ostringstream linha;
    linha << std::fixed << std::setprecision(1);
    linha << "{"
          << "\"timestamp\":\"" << escaparString(gerarTimestamp()) << "\","
          << "\"estacao\":\""   << escaparString(estacao)          << "\","
          << "\"tag\":\""       << escaparString(tag)              << "\","
          << "\"tipo\":\""      << escaparString(tipo)             << "\","
          << "\"valor\":"       << valor                           << ","
          << "\"unidade\":\""   << escaparString(unidade)          << "\","
          << "\"status\":\""    << escaparString(status)           << "\""
          << "}";
    arquivo << linha.str() << "\n";
    arquivo.flush();
}

bool JsonWriter::estaAberto() const {
    return arquivo.is_open();
}