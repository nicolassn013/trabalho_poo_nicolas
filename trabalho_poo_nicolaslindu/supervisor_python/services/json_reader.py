import json
import os
from models.leitura import Leitura


class JsonReader:

    def __init__(self, caminho="leituras.jsonl"):
        self.caminho = caminho

    def ler(self):
        leituras = []

        if not os.path.exists(self.caminho):
            raise FileNotFoundError(f"Arquivo nao encontrado: {self.caminho}")

        with open(self.caminho, encoding="utf-8") as arquivo:
            for numero, linha in enumerate(arquivo, start=1):
                linha = linha.strip()
                if not linha:
                    continue
                try:
                    dado = json.loads(linha)
                    leitura = Leitura(
                        timestamp=dado["timestamp"],
                        estacao=dado["estacao"],
                        tag=dado["tag"],
                        tipo=dado["tipo"],
                        valor=dado["valor"],
                        unidade=dado["unidade"],
                        status=dado["status"]
                    )
                    leituras.append(leitura)
                except (json.JSONDecodeError, KeyError) as e:
                    print(f"Linha {numero} ignorada — erro: {e}")

        return leituras
