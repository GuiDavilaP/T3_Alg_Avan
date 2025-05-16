#!/bin/bash

# Garante que o script seja executado a partir do diretório correto
cd "$(dirname "$0")/.."

# Cria o diretório bin se não existir
mkdir -p bin

# Compila o programa
make

# Verifica se a compilação deu certo
if [ $? -ne 0 ]; then
    echo "Compilation failed!"
    exit 1
fi

# Roda os testes
echo "Running test/t1..."
./bin/torneio < test/t1
echo "Running test/t2..."
./bin/torneio < test/t2
echo "Running test/t3..."
./bin/torneio < test/t3
echo "Running test/t4..."
./bin/torneio < test/t4

echo ""