#ifndef JSONWRITER_HPP
#define JSONWRITER_HPP

#include <string>
#include <fstream>

class JsonWriter {
private:
    std::string caminhoArquivo;
    std::string estacao;
    std::ofstream arquivo;

    std::string gerarTimestamp() const;
    std::string escaparString(const std::string& s) const;

public:
    JsonWriter(const std::string& caminhoArquivo, const std::string& estacao);
    ~JsonWriter();

    void escrever(
        const std::string& tag,
        const std::string& tipo,
        double valor,
        const std::string& unidade,
        const std::string& status
    );

    bool estaAberto() const;
};

#endif
