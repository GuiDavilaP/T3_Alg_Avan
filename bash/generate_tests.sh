#!/bin/bash

# Garante que estamos no diretório correto
cd "$(dirname "$0")/.."

# Cria diretórios necessários
mkdir -p bin test/num_equipes test/vies_equipe test/frac_jogos

# Compila o gerador de torneios
g++ src/generate_tournament.cpp -o bin/generate_tournament

# Verifica se a compilação foi bem sucedida
if [ $? -ne 0 ]; then
    echo "Falha na compilação do gerador de torneios!"
    exit 1
fi

ITERATIONS=30  # Número de iterações para cada parâmetro

echo "Gerando testes para número de equipes..."
# Teste 1: Variação do número de equipes (mantém igual)
for n in $(seq 4 4 100); do
    echo "Gerando torneio com $n equipes..."
    output_file="test/num_equipes/n${n}.txt"
    ./bin/generate_tournament $n 2 0.5 0.1 > "$output_file"
done

echo "Gerando testes para viés da primeira equipe..."
# Teste 2: Variação do viés da primeira equipe
n=16  # número fixo de equipes
for beta in $(seq -0.9 0.1 0.9); do
    beta_str=$(printf "%.1f" $beta)
    echo "Gerando $ITERATIONS torneios com viés $beta_str..."
    dir="test/vies_equipe/b${beta_str/./_}"
    mkdir -p "$dir"
    for i in $(seq 1 $ITERATIONS); do
        output_file="$dir/test_${i}.txt"
        ./bin/generate_tournament $n 2 0.5 $beta_str > "$output_file"
    done
done

echo "Gerando testes para fração de jogos..."
# Teste 3: Variação da fração de jogos realizados
for alpha in $(seq 0.1 0.1 0.9); do
    alpha_str=$(printf "%.1f" $alpha)
    echo "Gerando $ITERATIONS torneios com fração $alpha_str de jogos..."
    dir="test/frac_jogos/f${alpha_str/./_}"
    mkdir -p "$dir"
    for i in $(seq 1 $ITERATIONS); do
        output_file="$dir/test_${i}.txt"
        ./bin/generate_tournament $n 2 $alpha_str 0.1 > "$output_file"
    done
done

echo "Gerando testes para pareamento viés-fração..."
# Teste 4: Pareamento de viés e fração
mkdir -p test/vies_fracao
for beta in $(seq -0.9 0.1 0.9); do
    beta_str=$(printf "%.1f" $beta)
    for alpha in $(seq 0.1 0.1 0.9); do
        alpha_str=$(printf "%.1f" $alpha)
        dir="test/vies_fracao/b${beta_str/./_}_f${alpha_str/./_}"
        mkdir -p "$dir"
        echo "Gerando 10 torneios com viés $beta_str e fração $alpha_str..."
        for i in $(seq 1 10); do
            output_file="$dir/test_${i}.txt"
            ./bin/generate_tournament $n 2 $alpha_str $beta_str > "$output_file"
        done
    done
done

echo "Geração de testes concluída!"