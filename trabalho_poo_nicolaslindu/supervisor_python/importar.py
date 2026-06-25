import os
import sys

sys.path.insert(0, os.path.dirname(__file__))

from services.json_reader import JsonReader
from repository.sqlite_repository import SQLiteRepository

# Caminho do leituras.jsonl gerado pelo C++
JSONL = os.path.abspath(os.path.join(
    os.path.dirname(__file__),
    "../dispositivo_cpp/leituras.jsonl"
))

# Banco consumido pelo Streamlit
BANCO = os.path.join(os.path.dirname(__file__), "leituras.db")

print(f"Importando: {JSONL}")
print(f"Banco:      {BANCO}\n")

if not os.path.exists(JSONL):
    print(f"ERRO: arquivo nao encontrado — {JSONL}")
    print("Execute o C++ primeiro para gerar o leituras.jsonl.")
    sys.exit(1)

reader = JsonReader(caminho=JSONL)
leituras = reader.ler()
print(f"Leituras lidas do JSONL:    {len(leituras)}")

repo = SQLiteRepository(banco=BANCO)
for leitura in leituras:
    repo.inserir(leitura)

print(f"Registros no banco (total): {repo.contar()}")
repo.fechar()

print("\nImportacao concluida. Abra o Streamlit para visualizar os dados.")
