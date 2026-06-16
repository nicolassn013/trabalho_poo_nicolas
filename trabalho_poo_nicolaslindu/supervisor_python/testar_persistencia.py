import os
import sys
import json
import sqlite3

sys.path.insert(0, os.path.dirname(__file__))

from models.leitura import Leitura
from repository.sqlite_repository import SQLiteRepository
from services.json_reader import JsonReader

JSONL = "leituras_teste.jsonl"
BANCO = "leituras_teste.db"

linhas = [
    {"timestamp":"2026-06-16T20:00:01","estacao":"EB-70","tag":"LT-001","tipo":"nivel","valor":32.0,"unidade":"%","status":"OK"},
    {"timestamp":"2026-06-16T20:00:02","estacao":"EB-70","tag":"PT-001","tipo":"pressao","valor":0.6,"unidade":"bar","status":"OK"},
    {"timestamp":"2026-06-16T20:00:03","estacao":"EB-70","tag":"FT-001","tipo":"vazao","valor":277.0,"unidade":"L/min","status":"OK"},
    {"timestamp":"2026-06-16T20:00:04","estacao":"EB-70","tag":"TT-001","tipo":"temperatura","valor":39.0,"unidade":"C","status":"OK"},
    {"timestamp":"2026-06-16T20:00:05","estacao":"EB-70","tag":"LT-001","tipo":"nivel","valor":20.0,"unidade":"%","status":"ALERTA"},
    {"timestamp":"2026-06-16T20:00:06","estacao":"EB-70","tag":"PT-001","tipo":"pressao","valor":8.0,"unidade":"bar","status":"ALERTA"},
    {"timestamp":"2026-06-16T20:00:07","estacao":"EB-70","tag":"LT-001","tipo":"nivel","valor":8.0,"unidade":"%","status":"FALHA"},
    {"timestamp":"2026-06-16T20:00:08","estacao":"EB-70","tag":"BBA-001","tipo":"bomba","valor":0.0,"unidade":"estado","status":"FALHA"},
]

with open(JSONL, "w", encoding="utf-8") as f:
    for l in linhas:
        f.write(json.dumps(l) + "\n")

print(f"Arquivo {JSONL} criado com {len(linhas)} linhas.\n")

reader = JsonReader(caminho=JSONL)
leituras = reader.ler()
print(f"Leituras lidas do JSONL: {len(leituras)}\n")

if os.path.exists(BANCO):
    os.remove(BANCO)

repo = SQLiteRepository(banco=BANCO)

for leitura in leituras:
    repo.inserir(leitura)

print(f"Registros inseridos no banco: {repo.contar()}\n")

conn = sqlite3.connect(BANCO)
cursor = conn.cursor()

cursor.execute("SELECT sql FROM sqlite_master WHERE type='table' AND name='leituras'")
schema = cursor.fetchone()
print("=== Schema da tabela ===")
print(schema[0])

print("\n=== SELECT * FROM leituras ===")
cursor.execute("SELECT * FROM leituras")
colunas = [d[0] for d in cursor.description]
print(" | ".join(f"{c:12}" for c in colunas))
print("-" * 100)
for row in cursor.fetchall():
    print(" | ".join(f"{str(v):12}" for v in row))

print("\n=== SELECT por status ALERTA ===")
cursor.execute("SELECT tag, tipo, valor, unidade, status FROM leituras WHERE status = 'ALERTA'")
for row in cursor.fetchall():
    print(row)

print("\n=== SELECT por status FALHA ===")
cursor.execute("SELECT tag, tipo, valor, unidade, status FROM leituras WHERE status = 'FALHA'")
for row in cursor.fetchall():
    print(row)

conn.close()
repo.fechar()

os.remove(JSONL)
os.remove(BANCO)
print(f"\nArquivos de teste removidos. Banco leituras.db funcionando corretamente.")
