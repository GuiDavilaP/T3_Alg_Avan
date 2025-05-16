import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np
import os

# Configuração do estilo dos gráficos
plt.style.use('bmh')  # Using a built-in style instead of seaborn
sns.set_theme()  # Initialize seaborn's default theme

# Criar diretório para gráficos
os.makedirs('results/graficos', exist_ok=True)

# 1. Tempo em função do número de equipes
df_tempo = pd.read_csv('results/tempo_vs_n.csv')
df_tempo = df_tempo.sort_values('n')

plt.figure(figsize=(10, 6))
sns.lineplot(data=df_tempo, x='n', y='tempo', marker='o', markersize=8)
plt.xlabel('Número de Equipes (n)')
plt.ylabel('Tempo de Execução (segundos)')
plt.title('Tempo de Execução vs Número de Equipes')
plt.grid(True)
plt.savefig('results/graficos/tempo_vs_n.png')
plt.close()

# 2. Probabilidade de vitória possível em função do viés
df_vies = pd.read_csv('results/prob_vs_vies.csv')
df_vies = df_vies.sort_values('vies')

plt.figure(figsize=(10, 6))
sns.lineplot(data=df_vies, x='vies', y='probabilidade_vitoria', marker='o', markersize=8)
plt.xlabel('Viés da Primeira Equipe (β)')
plt.ylabel('Probabilidade de Vitória ser Possível')
plt.title('Probabilidade de Vitória ser Possível vs Viés da Primeira Equipe')
plt.grid(True)
plt.savefig('results/graficos/prob_vs_vies.png')
plt.close()

# 3. Probabilidade de vitória possível em função da fração de jogos
df_fracao = pd.read_csv('results/prob_vs_fracao.csv')
df_fracao = df_fracao.sort_values('fracao_jogos')

plt.figure(figsize=(10, 6))
sns.lineplot(data=df_fracao, x='fracao_jogos', y='probabilidade_vitoria', marker='o', markersize=8)
plt.xlabel('Fração de Jogos Realizados (α)')
plt.ylabel('Probabilidade de Vitória ser Possível')
plt.title('Probabilidade de Vitória ser Possível vs Fração de Jogos Realizados')
plt.grid(True)
plt.savefig('results/graficos/prob_vs_fracao.png')
plt.close()

# 4. Probabilidade de vitória possível em função do viés e fração de jogos
df_vies_fracao = pd.read_csv('results/prob_vs_vies_fracao.csv')

# Criar figura com dimensões apropriadas
plt.figure(figsize=(12, 8))

# Criar scatter plot com gradiente de cores
scatter = plt.scatter(
    df_vies_fracao['vies'],
    df_vies_fracao['fracao_jogos'],
    c=df_vies_fracao['probabilidade_vitoria'],
    cmap='viridis',  # Colormap mais adequado para visualização de dados
    s=200,          # Tamanho dos pontos
    alpha=0.6       # Transparência para melhor visualização
)

# Configurar colorbar
cbar = plt.colorbar(scatter)
cbar.set_label('Probabilidade de Vitória Possível', size=12, labelpad=10)
cbar.ax.tick_params(labelsize=10)

# Configurar eixos
plt.xlabel('Viés da Primeira Equipe (β)', fontsize=12, labelpad=10)
plt.ylabel('Fração de Jogos Realizados (α)', fontsize=12, labelpad=10)
plt.title('Probabilidade de Vitória ser Possível por Viés e Fração de Jogos', 
          fontsize=14, pad=20)

# Ajustar limites e ticks dos eixos
plt.xlim(-1.0, 1.0)
plt.ylim(0.0, 1.0)
plt.xticks(np.arange(-0.9, 1.0, 0.2), rotation=45)
plt.yticks(np.arange(0.1, 1.0, 0.1))

# Adicionar grid com transparência
plt.grid(True, alpha=0.3, linestyle='--')

# Ajustar layout
plt.tight_layout()

# Salvar com alta resolução
plt.savefig('results/graficos/prob_vs_vies_fracao.png', 
            dpi=300, 
            bbox_inches='tight',
            facecolor='white')
plt.close()