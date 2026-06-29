# AI_LOG.md — Registro de Uso de Inteligência Artificial

## Projeto: EB-70 Mini-SCADA
## Desenvolvedor: Nicolas Lindu

Este documento registra como utilizei ferramentas de inteligência artificial durante o desenvolvimento do projeto EB-70. O objetivo é ser transparente sobre o papel dessas ferramentas, deixando claro que elas atuaram como suporte técnico enquanto as decisões arquiteturais e de implementação foram minhas.

As três ferramentas que utilizei foram:
- **Claude (Anthropic)** — revisões técnicas, análise de risco, documentação e implementação de melhorias
- **ChatGPT (OpenAI)** — planejamento, validação arquitetural e apoio na documentação
- **Replit Agent** — implementações pontuais no ambiente integrado

## Etapa 1 — Planejamento Inicial e Arquitetura

**Objetivo:** Definir a estrutura do projeto, os padrões de projeto a utilizar e o pipeline de dados.

**Como usei o ChatGPT:** Consultei o ChatGPT para me ajudar a estruturar a divisão em dois módulos independentes (dispositivo C++ e supervisor Python), a escolha do formato JSON Lines para comunicação entre camadas e a adoção dos padrões GoF Factory e Command como demonstrações acadêmicas centrais.

**Como usei o Claude:** Pedi ao Claude que validasse a decisão arquitetural e identificasse pontos de atenção.

**Como usei o Replit Agent:** Utilizei o Replit Agent para configurar o ambiente inicial de desenvolvimento, organizar a estrutura de pastas e preparar o ambiente de compilação C++17.

**Minha decisão:** Adotar a arquitetura em dois módulos com pipeline `C++ - JSONL - SQLite -Streamlit`, utilizando Factory e Command como padrões principais.


## Etapa 2 — Implementação do Módulo C++

**Objetivo:** Implementar sensores, bombas, alarmes, estação de bombeamento, padrões de projeto e exportação JSONL.

**Como usei o Replit Agent:** Utilizei o Replit Agent para implementar a estrutura inicial das classes de sensores, bombas e alarmes seguindo o modelo orientado a objetos que eu havia definido no planejamento.

**Como usei o ChatGPT:** Consultei o ChatGPT para validar a hierarquia de herança de `Sensor` e a interface base com `ler()`, `getTag()` e `getUnidade()`. Ele sugeriu o uso de `std::unique_ptr` no Factory para gerenciamento seguro de memória.

**Como usei o Claude:** Pedi ao Claude que revisasse o `JsonWriter` — ele identificou que `escaparString()` não tratava caracteres de controle (`\n`, `\r`, `\t`), o que poderia gerar JSON inválido.

**Minha decisão:** Corrigir o `escaparString()` e manter `std::localtime()` sem substituição, dado o contexto acadêmico single-thread do projeto.


## Etapa 3 — Fase 1 da Auditoria: Command Pattern

**Objetivo:** Auditar e melhorar a implementação do padrão Command.

**Como usei o Claude:** Pedi ao Claude uma revisão técnica completa dos arquivos do Command Pattern. Ele identificou cinco problemas: indentação inconsistente, ausência de documentação acadêmica, simetria `executar()`/`desfazer()` não documentada, comportamento questionável em `ResetAlarmeCommand::desfazer()` e typo em include guard. Claude implementou todas as correções que aprovei.

**Como usei o ChatGPT:** Consultei o ChatGPT para validar que nenhuma lógica funcional havia sido alterada após as mudanças estruturais.

**Minha decisão:** Aprovar todas as melhorias da Fase 1 após confirmar que o projeto compilou normalmente.


## Etapa 4 — Fase 2 da Auditoria: Alarmes e EstacaoBombeamento

**Objetivo:** Melhorar o sistema de alarmes e as regras operacionais da estação.

**Como usei o Claude:** Solicitei ao Claude uma análise de cada achado com classificação de risco. Ele avaliou seis possíveis melhorias e recomendou implementar apenas as de baixo risco:

*Aprovei e implementei:*
- Retorno por `const std::string&` em `getNome()` e `getMensagem()`
- Documentação Doxygen completa em `Alarme.hpp` e `Alarme.cpp`
- Extração dos limiares 27.0, 80.0 e 7.0 para `static constexpr`
- Comentários das Regras 1, 2 e 3 com explicação da zona morta e alternância

*Rejeitei por risco:*
- `enum Severidade` — exigiria alterações no schema JSON e SQLite
- Timestamp interno no `Alarme` — mesma razão
- Fallback de bomba bloqueada — exigiria alterar `Bomba.hpp` fora do escopo

**Nota sobre linguagem:** Após a primeira versão dos comentários, pedi ao Claude que reescrevesse com linguagem mais simples e direta, sem o tom formal de manual técnico. Aprovei a segunda versão.

**Minha decisão:** Implementar apenas as melhorias de baixo risco. A estabilidade do projeto foi minha prioridade nesta fase.


## Etapa 5 — Fase 3 da Auditoria: Simulações de Falha

**Objetivo:** Melhorar legibilidade e corretude das simulações de falha no `main.cpp`.

**Como usei o Claude:** Enviei os trechos das duas simulações e o `Bomba.hpp`. Claude identificou quatro problemas e reavaliou o risco do alarme de bomba bloqueada — inicialmente classificado como médio, foi reclassificado para baixo após confirmar que `estaBloqueada()` já existia na interface.

**Decisão arquitetural que tomei:** Decidi mover a lógica de status da bomba para dentro da própria classe `Bomba`, criando `getStatus()`. Isso eliminou a função auxiliar solta no `main.cpp` e tornou o design mais coeso.

**Bug encontrado nos testes:** Durante o Teste 1, o compilador apontou `statusBomba was not declared in this scope`. O `main.cpp` ainda chamava a função que havia sido descartada quando a lógica migrou para `Bomba::getStatus()`. Pedi ao Claude que diagnosticasse — ele identificou o problema e aplicou a correção em uma linha.

**Minha decisão:** Aprovar todas as melhorias. Aceitar `getStatus()` como método de instância em `Bomba`.


## Etapa 6 — Fase 4 da Auditoria: JsonWriter

**Objetivo:** Melhorar robustez e documentação do módulo de exportação JSON Lines.

**Como usei o Claude:** Pedi uma análise dos quatro achados identificados. Aprovei dois e rejeitei dois:

*Implementei:*
- Três casos adicionados em `escaparString()`: `'\n'`, `'\r'`, `'\t'`
- Comentário do formato JSON Lines no cabeçalho de `JsonWriter.hpp`

*Não implementei:*
- Substituição de `std::localtime()` — sem impacto real no contexto do projeto
- Alteração do `flush()` — comportamento correto e intencional para SCADA

**Minha decisão:** Implementar apenas o que agrega valor real sem risco.


## Etapa 7 — Fase 5 da Auditoria: SQLiteRepository

**Objetivo:** Melhorar robustez da camada de persistência Python.

**Como usei o Claude:** Enviei o arquivo completo e pedi análise dos cinco achados. Claude implementou as melhorias aprovadas: `conn = None` no `fechar()`, `__del__()`, `try/except` em `inserir()`, type hints e docstrings.

**Problema com o type checker do Replit:** Após as melhorias, o Replit apontou erros do tipo `Attribute execute is not defined on None`. Pedi ao Claude que identificasse a causa — ele explicou que o type hint `Connection | None` gerou ambiguidade e resolveu com guards `if not self.conn` nos métodos. Os `ty:ignore` que haviam sido inseridos incorretamente foram removidos.

**Minha decisão:** Aprovar todas as melhorias. Rejeitar limite em `listar()` — decidi não arriscar impacto silencioso no Streamlit nesta fase.


## Etapa 8 — Fase 6 da Auditoria: Streamlit

**Objetivo:** Melhorar o dashboard para uso operacional e acadêmico.

**Como usei o Claude:** Pedi duas reavaliações consecutivas dos achados antes de aprovar qualquer implementação. Aprovei quatro melhorias:
- Constantes EB-70 documentadas com comentário de sincronização com C++
- Linhas de limite 27% e 80% no gráfico
- Histórico decrescente
- Remoção de emojis

**Decisão que tomei sobre o gráfico:** Na primeira versão, Claude substituiu `st.line_chart()` por `plotly.graph_objects`. Rejeitei a troca de biblioteca — queria manter a dependência original. Claude reformulou usando colunas constantes no DataFrame, mantendo o `st.line_chart()`.

**Minha decisão:** Aprovar as quatro melhorias com a solução que não trocava de biblioteca.


## Etapa 9 — Criação do importar.py

**Objetivo:** Conectar o `leituras.jsonl` real ao `leituras.db` consumido pelo Streamlit.

**Como usei o Claude:** Antes de criar qualquer arquivo novo, pedi ao Claude que verificasse se já existia algum script de importação. Após análise do `testar_persistencia.py` e dos `grep` nos arquivos, ficou claro que não existia. Pedi então um orquestrador mínimo reutilizando as classes existentes.

**Minha decisão:** Criar o `importar.py` como peça final do pipeline. Fiz o upload no GitHub e puxei via `git pull` no Replit.


## Etapa 10 — SensorTurbidez: Diferencial Acadêmico

**Objetivo:** Demonstrar extensibilidade do Factory Pattern com adição de novo sensor.

**Como usei o Claude:** Pedi uma análise arquivo por arquivo do impacto antes de implementar. Claude confirmou que apenas quatro arquivos seriam tocados e que JSON, SQLite e Streamlit não precisariam de alteração.

**Problema nos testes:** O compilador retornou `fatal error: Sensorturbidez.hpp: No such file or directory`. Os arquivos não estavam na pasta `include/` e o nome do include tinha capitalização incorreta. Pedi ao Claude que resolvesse diretamente no terminal — ele usou `sed` para corrigir o nome e `cat >` para criar os arquivos sem depender do GitHub.

**Minha decisão:** Aprovar a implementação após confirmar compilação com `AT-001: 1 NTU` na saída.


## Etapa 11 — Execução dos Testes Finais

**Objetivo:** Validar o pipeline completo antes da entrega.

**Como usei o Claude:** Utilizei o Claude para organizar o roteiro de testes e identificar os comandos corretos para a estrutura real do projeto no Replit. Ele acompanhou cada teste e ajudou a diagnosticar os problemas de ambiente (porta do Streamlit, caminhos de diretório).

**Como usei o Replit Agent:** Tentei usar o Replit Agent para alguns passos de configuração, mas acabei resolvendo os problemas de porta e acesso manualmente com o suporte do Claude.

**Minha decisão:** Executar todos os sete testes e só considerar o projeto concluído após aprovação completa do fluxo.


## Etapa 12 — Documentação Final

**Objetivo:** Produzir README.md, AI_LOG.md e Pull Request para entrega acadêmica.

**Como usei o Claude:** Forneci o relatório completo de todas as fases e pedi a geração dos três documentos. Após a primeira versão, solicitei que os documentos fossem reescritos em primeira pessoa, como se eu tivesse escrito.

**Como usei o ChatGPT:** Utilizei o ChatGPT para definir a estrutura e os requisitos de cada documento antes de pedir a implementação ao Claude.

**Minha decisão:** Revisar e aprovar os documentos antes do commit final.


## Resumo das Contribuições

| Ferramenta | Principal contribuição |
|---|---|
| Claude | Revisões técnicas das Fases 1-6, análise de risco, implementação de melhorias, diagnóstico de bugs, documentação |
| ChatGPT | Planejamento arquitetural, validação de decisões, estrutura da documentação final |
| Replit Agent | Implementação inicial do módulo C++, configuração do ambiente, correções automáticas |

---

## Decisões que Tomei e Por Que as Tomei

| Decisão rejeitada | Meu motivo |
|---|---|
| `enum Severidade` em `Alarme` | Exigiria alteração no schema JSON e SQLite — risco de quebra |
| Timestamp interno no `Alarme` | Mesma razão |
| `std::localtime_r()` | Sem impacto real no contexto single-thread do projeto |
| Fallback de bomba bloqueada | Exigiria alterar `Bomba.hpp` fora do escopo da auditoria |
| Limite em `listar()` | Risco de impacto silencioso no Streamlit |
| `logging` no `JsonReader` | Deixei para pós-entrega — baixa prioridade no momento |
| `plotly` no gráfico | Preferi manter `st.line_chart()` sem adicionar dependências |
| SensorTurbidez antes dos testes | Implementei somente após todos os testes aprovados |