import sys
import os
import pandas as pd
import streamlit as st

sys.path.insert(0, os.path.dirname(__file__))

from repository.sqlite_repository import SQLiteRepository

BANCO = os.path.join(os.path.dirname(__file__), "leituras.db")
COLUNAS = ["id", "timestamp", "estacao", "tag", "tipo", "valor", "unidade", "status"]

NIVEL_BAIXO  = 27.0
NIVEL_ALTO   = 80.0
PRESSAO_ALTA = 7.0

st.set_page_config(
    page_title="Mini-SCADA EB-70",
    page_icon="🏭",
    layout="wide"
)

st.title("🏭 Mini-SCADA — Estação de Bombeamento EB-70")
st.caption("Supervisor de leituras, alarmes e falhas em tempo real.")

@st.cache_data(ttl=5)
def carregar_dados():
    repo = SQLiteRepository(banco=BANCO)
    registros = repo.listar()
    repo.fechar()
    if not registros:
        return pd.DataFrame(columns=COLUNAS)
    return pd.DataFrame(registros, columns=COLUNAS)

df = carregar_dados()

if df.empty:
    st.warning("Nenhuma leitura encontrada em leituras.db. Execute o dispositivo C++ primeiro para gerar dados.")
    st.stop()

# --- Métricas da última leitura ---
st.subheader("📊 Última Leitura por Sensor")

sensores = ["nivel", "pressao", "vazao", "temperatura"]
cols = st.columns(len(sensores))

for col, tipo in zip(cols, sensores):
    df_tipo = df[df["tipo"] == tipo]
    if not df_tipo.empty:
        ultima = df_tipo.iloc[-1]
        status = ultima["status"]
        icone = "✅" if status == "OK" else ("⚠️" if status == "ALERTA" else "🚨")
        col.metric(
            label=f"{icone} {tipo.capitalize()} ({ultima['tag']})",
            value=f"{ultima['valor']} {ultima['unidade']}",
            delta=status
        )
    else:
        col.metric(label=tipo.capitalize(), value="—")

st.divider()

# --- Gráfico: evolução do nível do reservatório ---
st.subheader("📈 Evolução do Nível do Reservatório")

df_nivel = df[df["tipo"] == "nivel"].copy()

if df_nivel.empty:
    st.info("Sem leituras de nível disponíveis.")
else:
    df_nivel = df_nivel.reset_index(drop=True)
    df_nivel.index = df_nivel.index + 1

    chart_data = df_nivel.set_index("timestamp")[["valor"]].rename(columns={"valor": "Nível (%)"})

    st.line_chart(chart_data)

    col1, col2, col3 = st.columns(3)
    col1.metric("Mínimo", f"{df_nivel['valor'].min():.1f} %")
    col2.metric("Máximo", f"{df_nivel['valor'].max():.1f} %")
    col3.metric("Último", f"{df_nivel['valor'].iloc[-1]:.1f} %")

    st.caption(f"Limite baixo: {NIVEL_BAIXO}% | Limite alto: {NIVEL_ALTO}%")

st.divider()

# --- Histórico completo ---
st.subheader("📋 Histórico Completo de Leituras")

col_busca, col_tipo, col_status = st.columns([3, 2, 2])

with col_busca:
    filtro_tag = st.text_input("Filtrar por TAG", placeholder="ex: LT-001")

with col_tipo:
    tipos_disponiveis = ["Todos"] + sorted(df["tipo"].unique().tolist())
    filtro_tipo = st.selectbox("Tipo de sensor", tipos_disponiveis)

with col_status:
    filtro_status = st.selectbox("Status", ["Todos", "OK", "ALERTA", "FALHA"])

df_filtrado = df.copy()
if filtro_tag:
    df_filtrado = df_filtrado[df_filtrado["tag"].str.contains(filtro_tag, case=False)]
if filtro_tipo != "Todos":
    df_filtrado = df_filtrado[df_filtrado["tipo"] == filtro_tipo]
if filtro_status != "Todos":
    df_filtrado = df_filtrado[df_filtrado["status"] == filtro_status]

def colorir_status(val):
    if val == "ALERTA":
        return "background-color: #fff3cd; color: #856404"
    elif val == "FALHA":
        return "background-color: #f8d7da; color: #721c24"
    elif val == "OK":
        return "background-color: #d4edda; color: #155724"
    return ""

st.dataframe(
    df_filtrado[["timestamp", "estacao", "tag", "tipo", "valor", "unidade", "status"]]
    .style.applymap(colorir_status, subset=["status"]),
    use_container_width=True
)
st.caption(f"{len(df_filtrado)} registro(s) exibido(s) de {len(df)} total.")

st.divider()

# --- Alertas e Falhas ---
col_alerta, col_falha = st.columns(2)

with col_alerta:
    st.subheader("⚠️ Registros em ALERTA")
    df_alerta = df[df["status"] == "ALERTA"][["timestamp", "tag", "tipo", "valor", "unidade"]]
    if df_alerta.empty:
        st.success("Nenhum alerta registrado.")
    else:
        st.dataframe(df_alerta, use_container_width=True)
        st.caption(f"{len(df_alerta)} alerta(s)")

with col_falha:
    st.subheader("🚨 Registros em FALHA")
    df_falha = df[df["status"] == "FALHA"][["timestamp", "tag", "tipo", "valor", "unidade"]]
    if df_falha.empty:
        st.success("Nenhuma falha registrada.")
    else:
        st.dataframe(df_falha, use_container_width=True)
        st.caption(f"{len(df_falha)} falha(s)")

st.divider()

# --- Rodapé ---
st.caption(
    f"Total de leituras no banco: **{len(df)}** | "
    f"Estação: **EB-70** | "
    f"Limites: nível {NIVEL_BAIXO}%–{NIVEL_ALTO}% | pressão < {PRESSAO_ALTA} bar"
)

if st.button("🔄 Atualizar dados"):
    st.cache_data.clear()
    st.rerun()
