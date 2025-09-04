# 📊 Medindo Performance de Ordenações

Este projeto tem o objetivo de implementar e comparar a performance de diferentes algoritmos de ordenação em C, medindo **tempo de execução** e **número de comparações** sob diferentes cenários de entrada.

Atualmente, os algoritmos avaliados são:
- **Bubble Sort**
- **Insertion Sort**
- **Quick Sort** (via `qsort` da biblioteca padrão do C)

---

## 🚀 Funcionalidades

- Geração de vetores em diferentes cenários:
  - Aleatório
  - Crescente 
  - Reverso 
  - Quase ordenado (≈10% de perturbação)

- Medição:
  - Tempo de execução em **milissegundos**
  - Número de comparações realizadas

- Exportação dos resultados em formato **CSV** para análise posterior (`resultados.csv`).

---

## 🛠️ Tecnologias

- Linguagem: **C**
- Bibliotecas utilizadas:
  - `stdio.h`
  - `stdlib.h`
  - `string.h`
  - `time.h`

---

## ⚙️ Como Executar

### 1. Clonar o repositório
```bash
git clone https://github.com/lU4N4ht/Medindo-Performance-de-Ordenacoes.git

cd Medindo-Performance-de-Ordenacoes
```

### 2. Compilar o código

É necessário ter um compilador C (como o GCC) instalado. Execute o comando abaixo no terminal para compilar o main.c:

```bash
gcc -o analise_ordenacao main.c
```
### 3. Rodar os testes
Após a compilação, execute o arquivo gerado:

```bash
./analise_ordenacao
```
Ao final da execução, os resultados detalhados dos testes serão salvos no arquivo resultados.csv na pasta raiz do projeto.

## 📈 Análise dos Resultados
O arquivo resultados.csv contém os dados tabulados, prontos para serem usados em ferramentas de análise de dados.

As colunas do CSV incluem:
  - `Tipo_de_Algoritmo`
  - `Tamanho_da_Entrada`
  - `Cenario`
  - `Numero_de_Repeticoes`
  - `Tempo_de_Execucao(ms)`
  - `Comparacoes`
