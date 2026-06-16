#include <iostream>
#include <memory>
#include "SensorNivel.hpp"
#include "SensorPressao.hpp"
#include "SensorVazao.hpp"
#include "SensorTemperatura.hpp"
#include "Bomba.hpp"
#include "Alarme.hpp"
#include "SensorFactory.hpp"
#include "EstacaoBombeamento.hpp"
#include "LigarBombaCommand.hpp"
#include "DesligarBombaCommand.hpp"
#include "ResetAlarmeCommand.hpp"
#include "ModoManutencaoCommand.hpp"
#include "JsonWriter.hpp"

// EB-70: limites da assinatura operacional
static const double NIVEL_BAIXO   = 27.0;
static const double NIVEL_ALTO    = 80.0;
static const double PRESSAO_ALTA  = 7.0;
static const std::string ESTACAO  = "EB-70";

std::string statusNivel(double valor) {
    if (valor < NIVEL_BAIXO || valor > NIVEL_ALTO) return "ALERTA";
    return "OK";
}

std::string statusPressao(double valor) {
    if (valor > PRESSAO_ALTA) return "ALERTA";
    return "OK";
}

int main() {

    JsonWriter writer("leituras.jsonl", ESTACAO);

    // --- 1. SENSORES DIRETOS ---
    std::cout << "=== Leituras dos sensores ===" << std::endl;

    SensorNivel nivel;
    SensorPressao pressao;
    SensorVazao vazao;
    SensorTemperatura temperatura;

    double vNivel       = nivel.ler();
    double vPressao     = pressao.ler();
    double vVazao       = vazao.ler();
    double vTemperatura = temperatura.ler();

    std::cout << nivel.getTag()       << ": " << vNivel       << " " << nivel.getUnidade()       << std::endl;
    std::cout << pressao.getTag()     << ": " << vPressao     << " " << pressao.getUnidade()     << std::endl;
    std::cout << vazao.getTag()       << ": " << vVazao       << " " << vazao.getUnidade()       << std::endl;
    std::cout << temperatura.getTag() << ": " << vTemperatura << " " << temperatura.getUnidade() << std::endl;

    writer.escrever("LT-001", "nivel",       vNivel,       nivel.getUnidade(),       statusNivel(vNivel));
    writer.escrever("PT-001", "pressao",     vPressao,     pressao.getUnidade(),     statusPressao(vPressao));
    writer.escrever("FT-001", "vazao",       vVazao,       vazao.getUnidade(),       "OK");
    writer.escrever("TT-001", "temperatura", vTemperatura, temperatura.getUnidade(), "OK");

    // --- 2. FACTORY PATTERN ---
    std::cout << "\n=== Factory Pattern ===" << std::endl;

    std::unique_ptr<Sensor> sensorNivelF   = SensorFactory::criar("nivel");
    std::unique_ptr<Sensor> sensorPressaoF = SensorFactory::criar("pressao");

    double vNF = sensorNivelF->ler();
    double vPF = sensorPressaoF->ler();

    std::cout << sensorNivelF->getTag()   << ": " << vNF << " " << sensorNivelF->getUnidade()   << std::endl;
    std::cout << sensorPressaoF->getTag() << ": " << vPF << " " << sensorPressaoF->getUnidade() << std::endl;

    writer.escrever("LT-002", "nivel",   vNF, sensorNivelF->getUnidade(),   statusNivel(vNF));
    writer.escrever("PT-002", "pressao", vPF, sensorPressaoF->getUnidade(), statusPressao(vPF));

    // --- 3. BOMBAS ---
    std::cout << "\n=== Bombas ===" << std::endl;

    Bomba bombaPrincipal("Bomba Principal");
    Bomba bombaReserva("Bomba Reserva");

    bombaPrincipal.ligar();
    std::cout << bombaPrincipal.getNome() << " ligada: "    << bombaPrincipal.estaLigada()    << std::endl;
    std::cout << bombaPrincipal.getNome() << " bloqueada: " << bombaPrincipal.estaBloqueada() << std::endl;

    // --- 4. ALARMES ---
    std::cout << "\n=== Alarmes ===" << std::endl;

    Alarme alarmeNivelBaixo("Nivel Baixo",       "Nivel abaixo de 27%");
    Alarme alarmePressaoAlta("Pressao Alta",     "Pressao acima de 7.0 bar");
    Alarme alarmeBombaBloqueada("Bomba Bloqueada", "Falha na bomba principal");

    alarmeNivelBaixo.ativar();
    std::cout << alarmeNivelBaixo.getNome()    << " ativo: " << alarmeNivelBaixo.estaAtivo()    << " - " << alarmeNivelBaixo.getMensagem()    << std::endl;
    std::cout << alarmePressaoAlta.getNome()   << " ativo: " << alarmePressaoAlta.estaAtivo()   << std::endl;
    std::cout << alarmeBombaBloqueada.getNome()<< " ativo: " << alarmeBombaBloqueada.estaAtivo() << std::endl;

    // --- 5. COMMAND PATTERN ---
    std::cout << "\n=== Command Pattern ===" << std::endl;

    Bomba bombaTeste("Bomba Teste");

    LigarBombaCommand     cmdLigar(bombaTeste);
    DesligarBombaCommand  cmdDesligar(bombaTeste);
    ResetAlarmeCommand    cmdReset(alarmeNivelBaixo);
    ModoManutencaoCommand cmdManutencao(bombaTeste);

    cmdLigar.executar();
    std::cout << bombaTeste.getNome() << " apos LigarBombaCommand: "    << bombaTeste.estaLigada()    << std::endl;
    cmdLigar.desfazer();
    std::cout << bombaTeste.getNome() << " apos desfazer:           "   << bombaTeste.estaLigada()    << std::endl;

    cmdManutencao.executar();
    std::cout << bombaTeste.getNome() << " bloqueada apos Manutencao: " << bombaTeste.estaBloqueada() << std::endl;
    cmdManutencao.desfazer();
    std::cout << bombaTeste.getNome() << " bloqueada apos desfazer:  "  << bombaTeste.estaBloqueada() << std::endl;

    // --- 6. ESTACAO EB-70 (regras + alternancia) ---
    std::cout << "\n=== Estacao EB-70 — Regras ===" << std::endl;

    Bomba principal("Bomba Principal");
    Bomba reserva("Bomba Reserva");
    Alarme aNivelBaixo("Nivel Baixo",   "Nivel abaixo de 27%");
    Alarme aPressaoAlta("Pressao Alta", "Pressao acima de 7.0 bar");

    EstacaoBombeamento estacao(principal, reserva, aNivelBaixo, aPressaoAlta);

    estacao.verificarNivel(20.0);
    writer.escrever("LT-001", "nivel", 20.0, "%", "ALERTA");
    std::cout << "Nivel=20 | Alarme: " << aNivelBaixo.estaAtivo()
              << " | Principal: " << principal.estaLigada()
              << " | Reserva: "   << reserva.estaLigada() << std::endl;

    estacao.verificarNivel(20.0);
    writer.escrever("LT-001", "nivel", 20.0, "%", "ALERTA");
    std::cout << "Nivel=20 (2x) | Principal: " << principal.estaLigada()
              << " | Reserva: "   << reserva.estaLigada() << std::endl;

    estacao.verificarNivel(85.0);
    writer.escrever("LT-001", "nivel", 85.0, "%", "ALERTA");
    std::cout << "Nivel=85 | Principal: " << principal.estaLigada()
              << " | Reserva: "   << reserva.estaLigada() << std::endl;

    estacao.verificarPressao(8.0);
    writer.escrever("PT-001", "pressao", 8.0, "bar", "ALERTA");
    std::cout << "Pressao=8.0 | Alarme pressao alta: " << aPressaoAlta.estaAtivo() << std::endl;

    estacao.verificarPressao(5.0);
    writer.escrever("PT-001", "pressao", 5.0, "bar", "OK");
    std::cout << "Pressao=5.0 | Alarme pressao alta: " << aPressaoAlta.estaAtivo() << std::endl;

    // --- 7. FALHA SIMULADA 1: sensor de nivel travado por 10 ciclos ---
    std::cout << "\n=== Falha Simulada 1: Sensor Nivel Travado ===" << std::endl;

    SensorNivel nivelFalha;
    nivelFalha.ler();
    nivelFalha.travar();

    for (int i = 0; i < 10; i++) {
        double leitura = nivelFalha.ler();
        writer.escrever("LT-001", "nivel", leitura, "%", "FALHA");
        std::cout << "Ciclo " << (i + 1) << ": " << leitura << "%" << std::endl;
    }
    std::cout << "Ciclos travados: " << nivelFalha.getCiclosTravados() << std::endl;

    nivelFalha.destravar();
    double leituraPos = nivelFalha.ler();
    writer.escrever("LT-001", "nivel", leituraPos, "%", statusNivel(leituraPos));
    std::cout << "Sensor destravado. Nova leitura: " << leituraPos << "%" << std::endl;

    // --- 8. FALHA SIMULADA 2: bomba bloqueada ---
    std::cout << "\n=== Falha Simulada 2: Bomba Bloqueada ===" << std::endl;

    Bomba bombaFalha("Bomba Falha");
    bombaFalha.bloquear();
    bombaFalha.ligar();
    writer.escrever("BBA-001", "bomba", 0.0, "estado", "FALHA");
    std::cout << bombaFalha.getNome() << " tentou ligar mas esta bloqueada: " << bombaFalha.estaLigada() << std::endl;

    alarmeBombaBloqueada.ativar();
    std::cout << alarmeBombaBloqueada.getNome() << " ativo: " << alarmeBombaBloqueada.estaAtivo() << std::endl;

    std::cout << "\n=== Arquivo leituras.jsonl gerado com sucesso ===" << std::endl;

    return 0;
}
