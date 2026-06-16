class Leitura:
    def __init__(
        self,
        timestamp,
        estacao,
        tag,
        tipo,
        valor,
        unidade,
        status
    ):
        self.timestamp = timestamp
        self.estacao = estacao
        self.tag = tag
        self.tipo = tipo
        self.valor = valor
        self.unidade = unidade
        self.status = status

    def __repr__(self):
        return (
            f"Leitura(tag={self.tag}, tipo={self.tipo}, "
            f"valor={self.valor}, status={self.status})"
        )
