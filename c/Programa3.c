#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_SENSORES 5
#define LEITURAS_POR_SENSOR 1000

const char *sensores[NUM_SENSORES] = {"TEM", "PRE", "VIB", "UMI", "FLU"};

float criar_val(int sensor) {
    switch (sensor) {
        case 0:
            return (rand() % 1000) / 10.0 + 20.0;
        case 1:
            return (rand() % 1000) / 10.0 + 1000.0;
        case 2:
            return (rand() % 1000) / 1000.0; 
        case 3: 
            return rand() % 101; 
        case 4: 
            return (rand() % 5000) / 10.0; 
        default:
            return 0.0;
    }
}

time_t gerar_timtamp(int d, int m, int a) {
    struct tm t = {0};

    t.tm_year = a - 1900; 
    t.tm_mon = m - 1; 
    t.tm_mday = d;
    t.tm_hour = rand() % 24; 
    t.tm_min = rand() % 60;  
    t.tm_sec = rand() % 60;

    return mktime(&t);
}

int main() {
    int d, m, a;

    printf("//===================================\\\\");
    printf("\n||\n");
    printf("\r||\tDigite o dia (1-31): ");
    scanf("%d", &d);
    printf("||\n");
    printf("||\tDigite o mes (1-12): ");
    scanf("%d", &m);
    printf("||\n");
    printf("\r||\tDigite o ano: ");
    scanf("%d", &a);
    printf("||\n");
    printf("\\\\==================================//\n");

    srand(time(NULL));

    FILE *fp = fopen("novos_dados.txt", "w");
    if (!fp) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return 1;
    }

    // Leituras aleatorias
    for (int i = 0; i < NUM_SENSORES; i++) {
        for (int j = 0; j < LEITURAS_POR_SENSOR; j++) {
            time_t timtamp = gerar_timtamp(d, m, a);
            float valor = criar_val(i);
            fprintf(fp, "%ld %s %.2f\n", timtamp, sensores[i], valor);
        }
    }
    fclose(fp);
    printf("\n//======================================\\\\\n");
    printf("||\n");
    printf("||\tArquivo com novos dados criados!\n");
    printf("||\n");
    printf("\\\\======================================//");
    return 0;
}