#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef unsigned long long u64;

// Função para medir tempo em ms
static inline double ms(clock_t a, clock_t b) {
    return 1000.0 * (double)(b - a) / CLOCKS_PER_SEC;
}

// Clona vetor RM
int* clone(const int *src, int n) {
    int *dst = (int*)malloc((size_t)n * sizeof(int));
    if (!dst) {
        fprintf(stderr, "Falha de memoria\n");
        exit(1);
    }
    memcpy(dst, src, (size_t)n * sizeof(int));
    return dst;
}

// Algoritmos de Ordenação (Bubble Sort, Insertion Sort e qsort)

// Implementação do Bubble Sort 
void bubble_sort(int *RM, int n, u64 *comps) {
    *comps = 0;     // inicializando o contador de comparações
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            (*comps)++;     // incrementando o contador a cada comparação
            if (RM[j] > RM[j + 1]) {
                int temp = RM[j];
                RM[j] = RM[j + 1];
                RM[j + 1] = temp;
            }
        }
    }
}

// Implementação do Insertion Sort
void insertion_sort(int *RM, int n, u64 *comps) {
    *comps = 0;     // inicializando o contador de comparações
    for (int i = 1; i < n; i++) {
        int key = RM[i];
        int j = i - 1;
        while (j >= 0) {
            (*comps)++;     // incrementando o contador a cada comparação
            if (RM[j] > key) {
                RM[j + 1] = RM[j];
                j--;
            } else {
                break;
            }
        }
        RM[j + 1] = key;
    }
}

// variável global para contar comparações no qsort
static u64 QSORT_COMPS = 0;

static int cmp_int_asc_count(const void *a, const void *b) {
    QSORT_COMPS++;
    int A = *(const int*)a;
    int B = *(const int*)b;
    return (A > B) - (A < B);
}

void qsort_asc_wrapped(int *RM, int n, u64 *comps) {
    QSORT_COMPS = 0;     // reseta o contador antes de cada execução
    qsort(RM, (size_t)n, sizeof(int), cmp_int_asc_count);
    *comps = QSORT_COMPS;   // guarda o numero de comparações em *comps
}

// Geração de Vetores

// cenário de dados: Aleatório
void gera_vetor_ale(int *RM, int n) {
    for (int i = 0; i < n; i++) {
        RM[i] = rand() % 10000;
    }
}

// cenário de dados: Ordenado crescente
void gera_vetor_cres(int *RM, int n) {
    for (int i = 0; i < n; i++) {
        RM[i] = i;
    }
}

// cenário de dados: Reverso
void gera_vetor_reverso(int *RM, int n) {
    for (int i = 0; i < n; i++) {
        RM[i] = n - i;
    }
}

// cenário de dados: Quase ordenado (com ≈10% de perturbação)
void gera_vetor_quase(int *RM, int n) {
    gera_vetor_cres(RM, n);
    int perturb = n / 10;
    for (int i = 0; i < perturb; i++) {
        int a = rand() % n;
        int b = rand() % n;
        int tmp = RM[a];
        RM[a] = RM[b];
        RM[b] = tmp;
    }
}

// Execução dos Testes 

int main() {
    srand(42);

    // Tamanhos de entrada (n)
    int tamanhos[] = {1000, 5000, 10000};
    int num_tamanhos = sizeof(tamanhos) / sizeof(tamanhos[0]);

    enum { ALEATORIO, CRESCENTE, REVERSO, QUASE };
    const char *cenarios[] = {"Aleatorio", "Crescente", "Reverso", "Quase Ordenado"};

     // Tabela de resultados em CSV, resultados.csv
    FILE *f_csv = fopen("resultados.csv", "w");
    if (!f_csv) {
        fprintf(stderr, "Erro ao criar o arquivo resultados.csv\n");
        return 1;
    }

     // Cabeçalho 
    fprintf(f_csv, "Tipo_de_Algoritmo,Tamanho_da_Entrada,Cenario,Numero_de_Repeticoes,Tempo_de_Execucao(ms),Comparacoes\n");

    for (int t = 0; t < num_tamanhos; t++) {
        int n = tamanhos[t];
        int *RM = (int*)malloc(n * sizeof(int));
        if (!RM) {
            fprintf(stderr, "Erro de memoria: Falha ao alocar vetor base de tamanho %d.\n", n);
            fclose(f_csv);
            return 1;
        }

        for (int cenario = ALEATORIO; cenario <= QUASE; cenario++) {
            switch (cenario) {
                case ALEATORIO:
                    gera_vetor_ale(RM, n);
                    break;
                case CRESCENTE:
                    gera_vetor_cres(RM, n);
                    break;
                case REVERSO:
                    gera_vetor_reverso(RM, n);
                    break;
                case QUASE:
                    gera_vetor_quase(RM, n);
                    break;
            }

            u64 comps_bubble, comps_insertion, comps_qsort;
            double tempo_bubble, tempo_insertion, tempo_qsort;

            for (int r = 0; r < 5; r++) {
                clock_t start, end;
                int *vetor_para_algoritmo;

                // Teste Bubble Sort
                vetor_para_algoritmo = clone(RM, n);
                start = clock();
                bubble_sort(vetor_para_algoritmo, n, &comps_bubble);
                end = clock();
                tempo_bubble = ms(start, end);
                free(vetor_para_algoritmo);
                fprintf(f_csv, "Bubble,%d,%s,%d,%.3f,%llu\n", n, cenarios[cenario], r + 1, tempo_bubble, comps_bubble);

                // Teste Insertion Sort
                vetor_para_algoritmo = clone(RM, n);
                start = clock();
                insertion_sort(vetor_para_algoritmo, n, &comps_insertion);
                end = clock();
                tempo_insertion = ms(start, end);
                free(vetor_para_algoritmo);
                fprintf(f_csv, "Insertion,%d,%s,%d,%.3f,%llu\n", n, cenarios[cenario], r + 1, tempo_insertion, comps_insertion);

                // Teste qsort
                vetor_para_algoritmo = clone(RM, n);
                start = clock();
                qsort_asc_wrapped(vetor_para_algoritmo, n, &comps_qsort);
                end = clock();
                tempo_qsort = ms(start, end);
                free(vetor_para_algoritmo);
                fprintf(f_csv, "Qsort,%d,%s,%d,%.3f,%llu\n", n, cenarios[cenario], r + 1, tempo_qsort, comps_qsort);
            }
        }
        free(RM);
    }

    // Fecha o arquivo CSV no final da execução
    fclose(f_csv);
    printf("Testes concluidos e os resultados foram salvos em 'resultados.csv'\n");

    return 0;
}
