#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int partition(float vetor[], int esq, int dir){

    float aux;//trocar a posição
    int contador = esq;

    for(int i=esq+1; i <= dir; i++){
        if(vetor[i] < vetor[esq]){
            contador++;

            aux = vetor[i];
            vetor[i] = vetor[contador];
            vetor[contador] = aux;
        }
    }

    aux = vetor[esq];
    vetor[esq] = vetor[contador];
    vetor[contador] = aux;

    return contador;
}

void quickSort(float vetor[], int esq, int dir){

    int posDividido;

    if(esq < dir){
        posDividido = partition(vetor, esq, dir);
        quickSort(vetor, esq, posDividido-1);
        quickSort(vetor, posDividido+1, dir);
    }

}

int main(){

    char nomeArquivoEntrada[15], nomeArquivoSaida[15];
    int n;

    printf("Numero de elementos do vetor: ");
    scanf("%d", &n);


    printf("Nome do Arquivo para ler esses %d dados: ", n);
    getchar();
    gets(nomeArquivoEntrada);


    FILE *file;
    file = fopen(nomeArquivoEntrada, "r");

    float vetorParaOrganizar[n];

    for(int i=0; i < n; i++){

        fscanf(file, "%f", &vetorParaOrganizar[i]);
        printf("%f", vetorParaOrganizar[i]);
    }

    fclose(file);

    if(vetorParaOrganizar == NULL){
        printf("Erro para abrir Arquivo %s", nomeArquivoEntrada);
        return 0;
    }
    else{
        printf("Vetor lido com sucesso!\n");
        quickSort(vetorParaOrganizar, 0, n-1);
    }

    printf("Nome do Arquivo para salvar vetor ordenado: ");
    gets(nomeArquivoSaida);

    FILE *fileSaida;
    fileSaida = fopen(nomeArquivoSaida, "w+");

    for(int j=0; j<n; j++){
        fprintf(fileSaida, "%.3f\n", vetorParaOrganizar[j]);
        printf("teste");
    }

    fclose(fileSaida);

    getch();


}

