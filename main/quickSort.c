#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/types.h>

int part = 0;

struct arg_struct {
    int n;
    int threads;
    float *a;
};

struct arg_struct args;


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
  int k = 0, posDividido;
  // dividindo o array
  int thread_part = part++;

  // calcular direito e esquerdo
  int esq = thread_part * (args.n / args.threads);
  int dir = (thread_part + 1) * (args.n / args.threads) - 1;

  // pegar o meio da divisão de direito e esquerdo
  posDividido = esq + (dir - esq) / 2;
  if (esq < dir) {
      quickSort(args.a, esq, posDividido-1);
      quickSort(args.a, posDividido+1, dir);
  }
}


int main(){
  char nomeArquivoEntrada[15], nomeArquivoSaida[15];
  clock_t t;
  int nthread, i, teste = 0, n;

  //determinar tamanho de elementos do vetor
  printf("Tamanho do Vetor: ");
  scanf("%d", &args.n);
  float vetorParaOrdenar[args.n];

  //determinar o nome do arquivo para pegar os n elementos
  printf("Nome do Arquivo para ler esses %d dados: ", args.n);
  scanf("%s", &nomeArquivoEntrada);


  FILE *file;
  file = fopen(nomeArquivoEntrada, "r");

  for(int i=0; i < args.n; i++){
      fscanf(file, "%f", &vetorParaOrdenar[i]);
  }

  args.a = vetorParaOrdenar;

  fclose(file);

  if(args.a == NULL){
      printf("Erro para abrir Arquivo %s", nomeArquivoEntrada);
      return 0;
  }

  //determinar numero de threads
  printf("Numero de Threads: ");
  scanf("%d", &args.threads);

  t = clock();
  pthread_t threads[args.threads];

  //criar e rodar as threads
  for(i = 0; i < args.threads; i++){
      pthread_create(&threads[i], NULL, quickSortThread, (void *)NULL);
      //printf("Thread criada: %d\n", i);
  }

  for (i = 0; i < args.threads; i++){
      pthread_join(threads[i], NULL);
      //printf("Join da Thread: %d\n", i);
  }
  t = clock() - t;

  //passando o quick sort final nas partes rearranjadas
  quickSort(args.a, 0, args.n-1);

  //determinar e salvar o arquivo de saida
  printf("Nome do Arquivo para salvar vetor ordenado: ");
  scanf("%s", &nomeArquivoSaida);

  FILE *fileSaida;
  fileSaida = fopen(nomeArquivoSaida, "w+");

  for(int j=0; j<args.n; j++){
    fprintf(fileSaida, "%.0f\n", args.a[j]);
  }

  fclose(fileSaida);

  printf("Tempo demorado: %f\n",((float)t) / CLOCKS_PER_SEC);
  return 0;

}
