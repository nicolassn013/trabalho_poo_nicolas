# EB-70  Mini-SCADA para Estação de Bombeamento

Este projeto é um sistema supervisório simplificado, que desenvolvi para a disciplina de Programação Orientada a Objetos. O sistema monitora em tempo real uma estação de bombeamento, exporta leituras em JSON Lines, persiste os dados em SQLite e exibe um dashboard operacional via Streamlit.


## Objetivo

Desenvolvi este projeto com o objetivo de demonstrar na prática:

- Aplicação dos padrões de projeto GoF **Factory** e **Command**
- Integração entre módulo C++ (dispositivo) e supervisor Python
- Pipeline de dados completo: `C++ → JSON Lines → SQLite → Streamlit`
- Simulação de falhas operacionais reais (sensor travado, bomba bloqueada)
- Extensibilidade arquitetural com adição de novos sensores sem modificar código existente


## Assinatura Operacional EB-70

Os limiares abaixo definem o comportamento da estação e estão presentes tanto no módulo C++ (`EstacaoBombeamento.hpp`) quanto no supervisor Python (`app.py`). Optei por mantê-los como constantes nomeadas em ambas as camadas para garantir rastreabilidade.

| Parâmetro | Valor | Efeito |
|---|---|---|
| Nível baixo | 27% | Aciona bomba e dispara alarme |
| Nível alto | 80% | Desliga bombas e limpa alarme |
| Pressão alta | 7.0 bar | Dispara alarme de pressão |


## Arquitetura

Dividi o projeto em dois módulos independentes que se comunicam exclusivamente via arquivo JSON Lines, sem acoplamento direto entre camadas.

```
dispositivo_cpp/
│   Módulo C++: leitura de sensores, controle de bombas,
│   aplicação das regras operacionais e exportação JSONL
│
supervisor_python/
    Módulo Python: leitura do JSONL, persistência SQLite
    e dashboard Streamlit
```

### Pipeline completo

```
C++ (eb70)
    -  leituras.jsonl  (JSON Lines)
importar.py  (JsonReader + SQLiteRepository)
    -  leituras.db  (SQLite)
app.py  (Streamlit)
    -  Dashboard operacional
```


## Padrões de Projeto Utilizados

### Factory Pattern
Utilizei o `SensorFactory` para centralizar a criação de sensores. A decisão de adotar este padrão me permitiu, no final do projeto, adicionar o `SensorTurbidez` sem alterar nenhuma classe existente — demonstrando na prática o princípio Open/Closed do SOLID.

```cpp
std::unique_ptr<Sensor> sensor = SensorFactory::criar("turbidez");
```

### Command Pattern
Encapsuleo cada ação sobre bombas e alarmes em um objeto `Comando` com métodos `executar()` e `desfazer()`, permitindo reversibilidade e desacoplamento entre quem ordena e quem executa.

```cpp
LigarBombaCommand cmd(bomba);
cmd.executar();   // liga
cmd.desfazer();   // desliga
```


## Tecnologias Utilizadas

| Camada | Tecnologia |
|---|---|
| Dispositivo | C++17 |
| Exportação | JSON Lines (.jsonl) |
| Persistência | SQLite3 (Python) |
| Dashboard | Streamlit |
| Linguagem supervisor | Python 3.11 |


## Estrutura de Pastas

```
trabalho_poo_nicolaslindu/
├── dispositivo_cpp/
│   ├── include/
│   │   ├── Sensor.hpp
│   │   ├── SensorNivel.hpp
│   │   ├── SensorPressao.hpp
│   │   ├── SensorVazao.hpp
│   │   ├── SensorTemperatura.hpp
│   │   ├── SensorTurbidez.hpp        - diferencial acadêmico
│   │   ├── SensorFactory.hpp
│   │   ├── Bomba.hpp
│   │   ├── Alarme.hpp
│   │   ├── Comando.hpp
│   │   ├── LigarBombaCommand.hpp
│   │   ├── DesligarBombaCommand.hpp
│   │   ├── ResetAlarmeCommand.hpp
│   │   ├── ModoManutencaoCommand.hpp
│   │   ├── EstacaoBombeamento.hpp
│   │   └── JsonWriter.hpp
│   └── src/
│       ├── main.cpp
│       ├── Sensor.cpp
│       ├── SensorNivel.cpp
│       ├── SensorPressao.cpp
│       ├── SensorVazao.cpp
│       ├── SensorTemperatura.cpp
│       ├── SensorTurbidez.cpp        - diferencial acadêmico
│       ├── SensorFactory.cpp
│       ├── Bomba.cpp
│       ├── Alarme.cpp
│       ├── LigarBombaCommand.cpp
│       ├── DesligarBombaCommand.cpp
│       ├── ResetAlarmeCommand.cpp
│       ├── ModoManutencaoCommand.cpp
│       ├── EstacaoBombeamento.cpp
│       └── JsonWriter.cpp
└── supervisor_python/
    ├── models/
    │   ├── leitura.py
    │   └── alarme.py
    ├── repository/
    │   └── sqlite_repository.py
    ├── services/
    │   └── json_reader.py
    ├── app.py
    ├── importar.py                   - orquestrador do pipeline real
    └── testar_persistencia.py
```


## Sensores Implementados

| Tag | Tipo | Unidade | Descrição |
|---|---|---|---|
| LT-001 | nivel | % | Nível do reservatório |
| PT-001 | pressao | bar | Pressão da linha |
| FT-001 | vazao | L/min | Vazão da linha |
| TT-001 | temperatura | C | Temperatura do fluido |
| AT-001 | turbidez | NTU | Contaminação da água |


## Diferencial Acadêmico — SensorTurbidez

Adicionei o `SensorTurbidez` na etapa final do projeto para demonstrar na prática a extensibilidade do Factory Pattern. Não precisei alterar nenhum sensor existente — criei apenas a nova classe e registrei uma entrada no `SensorFactory`. O JSON, SQLite e Streamlit suportaram o novo sensor automaticamente, sem nenhuma alteração.

Regra de status que defini:
- até 5 NTU → `OK`
- 5 a 10 NTU → `ALERTA`
- acima de 10 NTU → `FALHA`

## Como Compilar e Executar

### Passo 1 — Compilar o módulo C++

```bash
cd trabalho_poo_nicolaslindu/dispositivo_cpp
g++ -std=c++17 src/*.cpp -Iinclude -o eb70 && ./eb70
```

Isso gera o executável `eb70` e o arquivo `leituras.jsonl` com todas as leituras.

### Passo 2 — Importar para o SQLite

```bash
cd trabalho_poo_nicolaslindu/supervisor_python
python importar.py
```

Lê o `leituras.jsonl` gerado pelo C++ e persiste no `leituras.db`.

### Passo 3 — Abrir o dashboard Streamlit

```bash
cd trabalho_poo_nicolaslindu/supervisor_python
python -m streamlit run app.py \
  --server.address 0.0.0.0 \
  --server.port 8501 \
  --server.headless true \
  --server.enableCORS false \
  --server.enableXsrfProtection false
```


## Funcionalidades do Dashboard

- Última leitura por sensor (nível, pressão, vazão, temperatura)
- Gráfico de evolução do nível com linhas horizontais de limite (27% e 80%)
- Histórico completo de leituras ordenado do mais recente para o mais antigo
- Filtros por TAG, tipo de sensor e status
- Colorização automática por status (OK, ALERTA, FALHA)
- Painel de alertas e falhas separados
- Rodapé com totais e limites operacionais


## Testes Realizados

| Teste | Descrição | Resultado |
|---|---|---|
| Teste 1 | Compilação e execução completa do C++ |  Aprovado |
| Teste 2 | Assinatura operacional EB-70 (27%, 80%, 7.0 bar) |  Aprovado |
| Teste 3 | Sensor travado: 10 ciclos com valor constante |  Aprovado |
| Teste 4 | Bomba bloqueada: tentativa de ligar sem efeito | Aprovado |
| Teste 5 | Geração do JSONL com 7 campos obrigatórios |  Aprovado |
| Teste 6 | Importação JSON - SQLite via testar_persistencia.py |  Aprovado |
| Teste 9 | Fluxo completo C++ - JSONL - SQLite - Streamlit |  Aprovado |


## Autor e Ferramentas de Apoio

**Desenvolvedor:** Nicolas Soares

Durante o desenvolvimento, utilizei três ferramentas de IA como suporte técnico. Todas as decisões arquiteturais, de implementação e de priorização foram minhas.

- **Claude (Anthropic)** — utilizei para revisões técnicas detalhadas das seis fases de auditoria, identificação de problemas, análise de risco de cada alteração, implementação de melhorias estruturais e apoio durante os testes.
- **ChatGPT (OpenAI)** — utilizei para planejamento arquitetural inicial, validação de decisões e estruturação da documentação final.
- **Replit Agent** — utilizei para implementações pontuais no ambiente de desenvolvimento e auxílio na integração entre módulos.
