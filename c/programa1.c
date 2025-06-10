#include <stdio.h>
#include <stdlib.h>
#include <string.h>

    int i = 0;
    char linhas[250];

typedef struct{
    int DH;
    char sensor[5];
    float dds;
}DADOS;

DADOS dd[100];

int abrirarquivo(DADOS dados[]){
    FILE *arc = fopen("dados.txt", "r");
    if(arc == NULL){
        perror("Erro ao abrir o arquivo: ");
        return 1;
    }

    while(fgets(linhas, sizeof(linhas), arc) != NULL){

        char *tk;
        // Data e hora
        tk = strtok(linhas, " ");
        dados[i].DH = atoi(tk);

        // Sensores
        tk = strtok(NULL, " ");
        if(strlen(tk) >= sizeof(dados[i].sensor)){
            printf("Estouro de memoria em Sensores!");
        }
        strcpy(dados[i].sensor, tk);

        // Dados
        tk = strtok(NULL, " ");
        dados[i].dds = atof(tk);
        i++;
    }

    fclose(arc);
    return 0;
}
    
void orddh(DADOS dados[]){
    
    int aux;
    for(int p = 0; p < i; p++){

        for(int j = 0; j < i; j++){
            if(dados[j].DH > dados[j+1].DH){

                aux = dados[j].DH;
                dados[j].DH = dados[j+1].DH;
                dados[j+1].DH = aux;
            }else {
                continue;
            }
        }
    }

    for (int j = 0; j < i; j++){
        printf(" %-12d | %-5s | %-10.2f\n", dados[j].DH, dados[j].sensor, dados[j].dds);
    }

}

int narc(DADOS dados[]){

    FILE *narc = fopen("Dados_por_Data_e_Hora.txt", "w");
    if(narc == NULL){
        perror("Erro ao criar novo arquivo: ");
    }

    for(int j = 0; j < i; j++){
        fprintf(narc, "%d, %s, %.2f\n", dados[j].DH, dados[j].sensor, dados[j].dds);
    }
    fclose(narc);
    printf("\nDados salvos com sucesso!\n");
    return 0;
}

int cascii(char *c){
    return (int)c[0];
}

int senpres(DADOS dados[]){
    FILE *at = fopen("Dados_de_Pressao.txt", "w");
    if(at == NULL){
        perror("Erro ao gerar arquivo de Pressao: ");
        return 1;
    }

    for(int j = 0; j < i; j++){
        
        if(cascii(dados[j].sensor) == 80){

            fprintf(at, "%d, %s, %.2f\n", dados[j].DH, dados[j].sensor, dados[j].dds);
            fflush(at);
        }
    }
    printf("Arquivo de sensores de Pressao criado com sucessor!");
    fclose(at);
    return 0;
}

int sentemp(DADOS dados[]){
    FILE *at = fopen("Dados_de_Temperatura.txt", "w");
    if(at == NULL){
        perror("Erro ao gerar arquivo de temperatura: ");
        return 1;
    }

    for(int j = 0; j < i; j++){
        
        if(cascii(dados[j].sensor) == 84){

            fprintf(at, "%d, %s, %.2f\n", dados[j].DH, dados[j].sensor, dados[j].dds);
            fflush(at);
        }
    }
    printf("Arquivo de sensores de Temperatura criado com sucessor!");
    fclose(at);
    return 0;
}

int senvib(DADOS dados[]){
    FILE *at = fopen("Dados_de_Vibracao.txt", "w");
    if(at == NULL){
        perror("Erro ao gerar arquivo de Vibracao: ");
        return 1;
    }

    for(int j = 0; j < i; j++){
        
        if(cascii(dados[j].sensor) == 86){

            fprintf(at, "%d, %s, %.2f\n", dados[j].DH, dados[j].sensor, dados[j].dds);
            fflush(at);
        }
    }
    printf("Arquivo de sensores de Vibracao criado com sucessor!");
    fclose(at);
    return 0;
}

int main(){
        abrirarquivo(dd);

        int opc, opc2;

        do{
        printf("\n//=====================================\\\\\n");
        printf("||\t1 - Ler arquivo bruto\n");
        printf("||\t2 - Ordenar por Data/Hora\n");
        printf("||\t3 - Orndenar por Sensor\n");
        printf("||\t4 - Criar novo arquivo\n");
        printf("||\t5 - Sair\n");
        printf("\\\\=====================================//");
        scanf("%d", &opc);

            switch(opc){
            case 1:
            for (int j = 0; j < i; j++){
                printf(" %-12d | %-5s | %-10.2f\n", dd[j].DH, dd[j].sensor, dd[j].dds);
            }
            break;

            case 2:
                orddh(dd);
            break;

            case 3:

                do{
                printf("\n//=====================================\\\\\n");
                printf("||\t1 - Sensor de Temperatura\n");
                printf("||\t2 - Sensor de Vibracao\n");
                printf("||\t3 - Sensor de Pressao\n");
                printf("\\\\=====================================//");
                scanf("%d", &opc2);
                
                switch(opc2){

                    case 1:
                        sentemp(dd);
                    break;

                    case 2:
                        senvib(dd);
                    break;

                    case 3:
                        senpres(dd);
                    break;
                }

            break;

            case 4:
                    narc(dd);
            break;
                }while(opc2 != 4);
            }
        }while(opc != 5);
        
}