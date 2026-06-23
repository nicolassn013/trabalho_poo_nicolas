import sqlite3
from models.leitura import Leitura


class SQLiteRepository:
    """
    Repositório de persistência do EB-70.
    Armazena leituras importadas do arquivo JSONL no banco SQLite.
    Consumido pelo supervisor Streamlit via leituras.db.
    """

    def __init__(self, banco="leituras.db"):
        """Abre (ou cria) o banco e garante que a tabela de leituras existe."""
        self.conn: sqlite3.Connection | None = sqlite3.connect(banco)
        self.conn.execute("""
            CREATE TABLE IF NOT EXISTS leituras (
                id        INTEGER PRIMARY KEY AUTOINCREMENT,
                timestamp TEXT    NOT NULL,
                estacao   TEXT    NOT NULL,
                tag       TEXT    NOT NULL,
                tipo      TEXT    NOT NULL,
                valor     REAL    NOT NULL,
                unidade   TEXT    NOT NULL,
                status    TEXT    NOT NULL
            )
        """)
        self.conn.commit()

    def inserir(self, leitura: Leitura):
        """
        Insere uma leitura no banco.
        Loga erros de SQLite sem interromper o fluxo de persistência.
        """
        if not self.conn:
            return
        try:
            self.conn.execute("""
                INSERT INTO leituras (
                    timestamp, estacao, tag, tipo, valor, unidade, status
                ) VALUES (?, ?, ?, ?, ?, ?, ?)
            """, (
                leitura.timestamp,
                leitura.estacao,
                leitura.tag,
                leitura.tipo,
                leitura.valor,
                leitura.unidade,
                leitura.status
            ))
            self.conn.commit()
        except sqlite3.Error as e:
            print(f"[SQLiteRepository] Erro ao inserir leitura: {e}")

    def listar(self):
        """Retorna todas as leituras armazenadas ordenadas por id crescente."""
        if not self.conn:
            return []
        cursor = self.conn.cursor()
        cursor.execute("SELECT * FROM leituras ORDER BY id ASC")
        return cursor.fetchall()

    def contar(self):
        """Retorna o total de leituras armazenadas no banco."""
        if not self.conn:
            return 0
        cursor = self.conn.cursor()
        cursor.execute("SELECT COUNT(*) FROM leituras")
        return cursor.fetchone()[0]

    def fechar(self):
        """Fecha a conexão com o banco. Seguro para chamadas múltiplas."""
        if self.conn:
            self.conn.close()
            self.conn = None  # evita ProgrammingError em chamada dupla

    def __del__(self):
        """Garante fechamento da conexão mesmo sem chamada explícita a fechar()."""
        self.fechar()