#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/types.h>


#define MAX 100000
#define THREADS 8

float a[MAX];
int part = 0;


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

void* quickSortThread(void *arg){

  int k = 0;

  printf("Rodando: \n");
  // which part out of 2 parts
  int thread_part = part++;

  // calculating low and high
  int esq = thread_part * (MAX / THREADS);
  int dir = (thread_part + 1) * (MAX / THREADS) - 1;

  // evaluating mid point
  int posDividido = esq + (dir - esq) / 2;
  if (esq < dir) {
      quickSort(arg, esq, posDividido-1);
      quickSort(arg, posDividido+1, dir);
  }
}


int main(){
  char nomeArquivoEntrada[15], nomeArquivoSaida[15];
  clock_t t1, t2;
  printf("Nome do Arquivo para ler esses %d dados: ", MAX);
  //getchar();
  scanf("%s", &nomeArquivoEntrada);


  FILE *file;
  file = fopen(nomeArquivoEntrada, "r");

  for(int i=0; i < MAX; i++){
      fscanf(file, "%f", &a[i]);;
  }

  fclose(file);

  if(a == NULL){
      printf("Erro para abrir Arquivo %s", nomeArquivoEntrada);
      return 0;
  }

  int nthread;

  int i;
  /*
  for (i = 0; i < MAX; i++) {
      a[i] = rand() % MAX;
      printf("%f\n", a[i]);
  }

  printf("\n\n");*/


  printf("Numero de Threads: ");
  scanf("%d", &nthread);

  t1 = clock();
  pthread_t threads[nthread];

  for(i = 0; i < nthread; i++){
      pthread_create(&threads[i], NULL, quickSortThread, (void*)a);
      printf("thread criada: %d\n", i);
  }

  for (i = 0; i < nthread; i++){
      pthread_join(threads[i], NULL);
      printf("juntando: %d\n", i);
  }
  t2 = clock();

  int teste = 0;
  //quickSort(a, 0, MAX-1);//*
  /*
  printf("Deseja printar o vetor ordenado: ");
  scanf("%d", &teste);
  if(teste == 1){
    for (i = 0; i < MAX; i++) {
        printf("%f\n", a[i]);
    }
  }*/


/*    int n;

    printf("Numero de elementos do vetor: ");
    scanf("%d", &n);*/






    printf("Nome do Arquivo para salvar vetor ordenado: ");
    //fgets(nomeArquivoSaida, sizeof(nomeArquivoSaida), stdin);
    scanf("%s", &nomeArquivoSaida);

    FILE *fileSaida;
    fileSaida = fopen(nomeArquivoSaida, "w+");

    for(int j=0; j<MAX; j++){
        fprintf(fileSaida, "%.3f\n", a[j]);
    }

    fclose(fileSaida);

    printf("Tempo demorado: %f\n", (t2 - t1) / (double)CLOCKS_PER_SEC);

    //getch();


}
