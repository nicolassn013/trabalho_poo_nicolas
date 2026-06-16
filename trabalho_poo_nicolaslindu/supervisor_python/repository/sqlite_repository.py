import sqlite3


class SQLiteRepository:

    def __init__(self, banco="leituras.db"):
        self.conn = sqlite3.connect(banco)
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

    def inserir(self, leitura):
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

    def listar(self):
        cursor = self.conn.cursor()
        cursor.execute("SELECT * FROM leituras ORDER BY id ASC")
        return cursor.fetchall()

    def contar(self):
        cursor = self.conn.cursor()
        cursor.execute("SELECT COUNT(*) FROM leituras")
        return cursor.fetchone()[0]

    def fechar(self):
        if self.conn:
            self.conn.close()
