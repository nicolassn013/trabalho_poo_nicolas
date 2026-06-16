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

int main() {

    // --- 1. SENSORES DIRETOS ---
    std::cout << "=== Leituras dos sensores ===" << std::endl;

    SensorNivel nivel;
    SensorPressao pressao;
    SensorVazao vazao;
    SensorTemperatura temperatura;

    std::cout << nivel.getTag()        << ": " << nivel.ler()        << " " << nivel.getUnidade()        << std::endl;
    std::cout << pressao.getTag()      << ": " << pressao.ler()      << " " << pressao.getUnidade()      << std::endl;
    std::cout << vazao.getTag()        << ": " << vazao.ler()        << " " << vazao.getUnidade()        << std::endl;
    std::cout << temperatura.getTag()  << ": " << temperatura.ler()  << " " << temperatura.getUnidade()  << std::endl;

    // --- 2. FACTORY PATTERN ---
    std::cout << "\n=== Factory Pattern ===" << std::endl;

    std::unique_ptr<Sensor> sensorNivelF  = SensorFactory::criar("nivel");
    std::unique_ptr<Sensor> sensorPressaoF = SensorFactory::criar("pressao");

    std::cout << sensorNivelF->getTag()   << ": " << sensorNivelF->ler()   << " " << sensorNivelF->getUnidade()   << std::endl;
    std::cout << sensorPressaoF->getTag() << ": " << sensorPressaoF->ler() << " " << sensorPressaoF->getUnidade() << std::endl;

    // --- 3. BOMBAS ---
    std::cout << "\n=== Bombas ===" << std::endl;

    Bomba bombaPrincipal("Bomba Principal");
    Bomba bombaReserva("Bomba Reserva");

    bombaPrincipal.ligar();
    std::cout << bombaPrincipal.getNome() << " ligada: "   << bombaPrincipal.estaLigada()   << std::endl;
    std::cout << bombaPrincipal.getNome() << " bloqueada: " << bombaPrincipal.estaBloqueada() << std::endl;

    // --- 4. ALARMES ---
    std::cout << "\n=== Alarmes ===" << std::endl;

    Alarme alarmeNivelBaixo("Nivel Baixo",    "Nivel abaixo de 27%");
    Alarme alarmePressaoAlta("Pressao Alta",  "Pressao acima de 7.0 bar");
    Alarme alarmeBombaBloqueada("Bomba Bloqueada", "Falha na bomba principal");

    alarmeNivelBaixo.ativar();
    std::cout << alarmeNivelBaixo.getNome()   << " ativo: " << alarmeNivelBaixo.estaAtivo()   << " - " << alarmeNivelBaixo.getMensagem()   << std::endl;
    std::cout << alarmePressaoAlta.getNome()  << " ativo: " << alarmePressaoAlta.estaAtivo()  << std::endl;
    std::cout << alarmeBombaBloqueada.getNome()<< " ativo: " << alarmeBombaBloqueada.estaAtivo()<< std::endl;

    // --- 5. COMMAND PATTERN ---
    std::cout << "\n=== Command Pattern ===" << std::endl;

    Bomba bombaTeste("Bomba Teste");

    LigarBombaCommand cmdLigar(bombaTeste);
    cmdLigar.executar();
    std::cout << bombaTeste.getNome() << " apos executar LigarBombaCommand: " << bombaTeste.estaLigada() << std::endl;

    cmdLigar.desfazer();
    std::cout << bombaTeste.getNome() << " apos desfazer LigarBombaCommand: " << bombaTeste.estaLigada() << std::endl;

    DesligarBombaCommand cmdDesligar(bombaTeste);
    ResetAlarmeCommand cmdReset(alarmeNivelBaixo);
    ModoManutencaoCommand cmdManutencao(bombaTeste);

    cmdManutencao.executar();
    std::cout << bombaTeste.getNome() << " bloqueada apos ModoManutencaoCommand: " << bombaTeste.estaBloqueada() << std::endl;

    cmdManutencao.desfazer();
    std::cout << bombaTeste.getNome() << " bloqueada apos desfazer: " << bombaTeste.estaBloqueada() << std::endl;

    // --- 6. ESTACAO BOMBEAMENTO (regras + alternancia) ---
    std::cout << "\n=== Estacao EB-70 — Regras ===" << std::endl;

    Bomba principal("Bomba Principal");
    Bomba reserva("Bomba Reserva");
    Alarme aNivelBaixo("Nivel Baixo",   "Nivel abaixo de 27%");
    Alarme aPressaoAlta("Pressao Alta", "Pressao acima de 7.0 bar");

    EstacaoBombeamento estacao(principal, reserva, aNivelBaixo, aPressaoAlta);

    // Regra 1+extra: nivel baixo -> liga bomba com alternancia
    estacao.verificarNivel(20.0);
    std::cout << "Nivel=20 | Alarme nivel baixo: " << aNivelBaixo.estaAtivo()
              << " | Principal: " << principal.estaLigada()
              << " | Reserva: "   << reserva.estaLigada() << std::endl;

    // Segunda chamada com nivel baixo -> deve alternar para a outra bomba
    estacao.verificarNivel(20.0);
    std::cout << "Nivel=20 (2x) | Principal: " << principal.estaLigada()
              << " | Reserva: "   << reserva.estaLigada() << std::endl;

    // Regra 2: nivel alto -> desliga tudo
    estacao.verificarNivel(85.0);
    std::cout << "Nivel=85 | Principal: " << principal.estaLigada()
              << " | Reserva: "   << reserva.estaLigada() << std::endl;

    // Regra 3: pressao alta
    estacao.verificarPressao(8.0);
    std::cout << "Pressao=8.0 | Alarme pressao alta: " << aPressaoAlta.estaAtivo() << std::endl;

    estacao.verificarPressao(5.0);
    std::cout << "Pressao=5.0 | Alarme pressao alta: " << aPressaoAlta.estaAtivo() << std::endl;

    // --- 7. FALHA SIMULADA 1: sensor de nivel travado por 10 ciclos ---
    std::cout << "\n=== Falha Simulada 1: Sensor Nivel Travado ===" << std::endl;

    SensorNivel nivelFalha;
    nivelFalha.ler();
    nivelFalha.travar();

    for (int i = 0; i < 10; i++) {
        std::cout << "Ciclo " << (i + 1) << ": " << nivelFalha.ler() << "%" << std::endl;
    }
    std::cout << "Ciclos travados: " << nivelFalha.getCiclosTravados() << std::endl;

    nivelFalha.destravar();
    std::cout << "Sensor destravado. Nova leitura: " << nivelFalha.ler() << "%" << std::endl;

    // --- 8. FALHA SIMULADA 2: bomba bloqueada ---
    std::cout << "\n=== Falha Simulada 2: Bomba Bloqueada ===" << std::endl;

    Bomba bombaFalha("Bomba Falha");
    bombaFalha.bloquear();
    bombaFalha.ligar();
    std::cout << bombaFalha.getNome() << " tentou ligar mas esta bloqueada: " << bombaFalha.estaLigada() << std::endl;

    alarmeBombaBloqueada.ativar();
    std::cout << alarmeBombaBloqueada.getNome() << " ativo: " << alarmeBombaBloqueada.estaAtivo() << std::endl;

    return 0;
}
