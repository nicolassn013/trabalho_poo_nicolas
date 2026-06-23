#ifndef JSONWRITER_HPP
#define JSONWRITER_HPP

#include <string>
#include <fstream>

// JsonWriter serializa(converte dados) leituras no formato JSON Lines (.jsonl):
// cada linha é um objeto JSON independente e completo.
// O formato permite leitura que incrementa pelo supervisor Python,
// acoplacao direta no SQLite e consumo linha por linha pelo Streamlit.
class JsonWriter {
private:
    std::string caminhoArquivo;
    std::string estacao;
    std::ofstream arquivo;

    std::string gerarTimestamp() const;

    // Escapa caracteres especiais para garantir JSON válido.
    //  aspas, barra invertida e caracteres de controle (\n, \r, \t).
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