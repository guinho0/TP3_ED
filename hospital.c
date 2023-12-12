#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hospital.h"

struct hospital
{
  int raioX[5][3];
  int laudo[3][3];
  float **reg;
};
struct pessoa
{
  char nome[50];
  char cpf[15];
  int idade;
  int id;
  int doenca[2];
  int entrada, E_raiox, S_raiox, E_laudo, S_laudo;
};
struct node
{
  void *data;
  Node *Next;
  Node *Prev;
};
struct list
{
  Node *First;
  Node *Last;
  int size;
};

struct queue
{
  Node *Front;
  Node *Rear;
  int size;
};

struct log_Evento
{
  char message[256];
  time_t timestamp;
};

struct log
{
  Log_Evento eventos[9000];
  int count;
};

List *cria_lista()
{
  List *list = (List *)malloc(sizeof(List));
  list->First = NULL;
  list->Last = NULL;
  list->size = 0;
  return list;
}
void inserir_lista(List *list, void *data)
{
  Node *novo = (Node *)malloc(sizeof(Node));
  novo->data = data;
  novo->Next = list->First;
  novo->Prev = NULL;
  if (list->size != 0)
  {
    list->First->Prev = novo;
  }
  else
  {
    list->Last = novo;
  }
  list->First = novo;
  list->size++;
}
void remove_lista(List *l, void *val)
{
  Node *temp = l->First;
  Node *Prev = NULL;
  Node *aux;
  while (temp != NULL)
  {
    if (temp->data == val)
    {
      aux = temp;
      if (Prev != NULL)
      {
        Prev->Next = temp->Next;
        if (temp->Next == NULL)
        {
          l->Last = Prev;
        }
      }
      else
      {
        l->First = temp->Next;
        if (temp->Next == NULL)
        {
          l->Last = NULL;
        }
      }
      temp = temp->Next;
      free(aux);
    }
    else
    {
      Prev = temp;
      temp = temp->Next;
    }
  }
  l->size--;
}
void libera_lista(List *list)
{
  Node *First = list->First;
  Node *Next;
  while (First != NULL)
  {
    Next = First->Next;
    free(First);
    First = Next;
  }
  free(list);
}

Queue *cria_fila()
{
  Queue *fila = (Queue *)malloc(sizeof(Queue));
  fila->Rear = NULL;
  fila->Front = NULL;
  fila->size = 0;
  return fila;
}
void remove_fila(Queue *fila)
{
  if (fila->Front == NULL)
  {
    fprintf(stderr, "Erro: Fila vazia\n");
    return;
  }
  Node *temp = fila->Front;
  fila->Front = fila->Front->Next;
  if (fila->Front == NULL)
  {
    fila->Rear = NULL;
  }
  else
  {
    fila->Front->Prev = NULL;
  }
  free(temp);
  fila->size--;
}
void libera_fila(Queue *fila)
{
  Node *Front = fila->Front;
  Node *Next;
  while (Front != NULL)
  {
    Next = Front->Next;
    free(Front);
    Front = Next;
  }
  free(fila);
}
Hospital *cria_hospital()
{
  Hospital *hospital = (Hospital *)malloc(sizeof(Hospital));
  hospital->reg = (float **)malloc(5 * sizeof(int *));
  for (int i = 0; i < 5; i++)
  {
    hospital->reg[i] = (float *)malloc(sizeof(float) * 2);
    hospital->reg[i][0] = i + 1;
    hospital->reg[i][1] = 0;
  }
  return hospital;
}
int faz_pessoa()
{
  int faz_pessoa = rand() % 100;
  if (faz_pessoa < 20)
  {
    return 1;
  }
  return 0;
}
int *faz__doenca()
{
  int faz__doenca = rand() % 100;
  int *doenca = (int *)malloc(sizeof(int) * 2);
  int sn = 1;
  int b = 2;
  int p = 3;
  int ff = 4;
  int a = 4;

  if (faz__doenca < 30)
  {
    doenca[0] = 1;
    doenca[1] = sn;
  }
  else if (faz__doenca >= 30 && faz__doenca < 50)
  {
    doenca[0] = 2;
    doenca[1] = b;
  }
  else if (faz__doenca >= 50 && faz__doenca < 70)
  {
    doenca[0] = 3;
    doenca[1] = p;
  }
  else if (faz__doenca >= 70 && faz__doenca < 85)
  {
    doenca[0] = 4;
    doenca[1] = ff;
  }
  else if (faz__doenca >= 85)
  {
    doenca[0] = 5;
    doenca[1] = a;
  }
  return doenca;
}
int faz__raiox()
{
  return 5 + (rand() % 6);
}
int faz_laudo()
{
  return 10 + rand() % 21;
}
char *faz_nome()
{
  char *nomes[] = {"Dorival", "Romário", "Marta", "Whinderson", "Felipe Neto", "Casemiro", "Chico", "Luísa", "Jeremias", "Rose", "Marinalva"};
  int indice = rand() % (sizeof(nomes) / sizeof(nomes[0]));
  char *nome = strdup(nomes[indice]);
  return nome;
}
char *faz_cpf()
{
  char cpf[15];
  sprintf(cpf, "%03d.%03d.%03d-%02d", rand() % 1000, rand() % 1000, rand() % 1000, rand() % 100);
  char *resultado = strdup(cpf);
  return resultado;
}
int faz_idade()
{
  return rand() % 120;
}
Pessoa *faz_paciente(int id)
{
  Pessoa *paciente = (Pessoa *)malloc(sizeof(Pessoa));
  int *doenca = (int *)malloc(sizeof(int) * 2);
  doenca = faz__doenca();
  // Gera aleatoriamente o nome, CPF e idade
  strcpy(paciente->nome, faz_nome());
  strcpy(paciente->cpf, faz_cpf());
  paciente->idade = faz_idade();
  paciente->id = id;
  paciente->doenca[0] = doenca[0];
  paciente->doenca[1] = doenca[1];
  paciente->entrada = id;
  free(doenca);
  return paciente;
}
void ordenado(Queue *fila, Pessoa *pessoa)
{
  Node *novo = (Node *)malloc(sizeof(Node));
  novo->data = pessoa;
  novo->Prev = NULL;
  novo->Next = NULL;
  // Caso especial: fila vazia
  if (fila->Front == NULL)
  {
    fila->Front = novo;
    fila->Rear = novo;
    fila->size++;
    return;
  }
  Node *atual = fila->Front;
  while (atual != NULL && pessoa->doenca[1] <= ((Pessoa *)atual->data)->doenca[1])
  {
    atual = atual->Next;
  }
  // Insere o novo na posição correta
  if (atual != NULL)
  {
    Node *Prev = atual->Prev;
    novo->Next = atual;
    novo->Prev = Prev;
    if (Prev != NULL)
    {
      Prev->Next = novo;
    }
    else
    {
      fila->Front = novo;
    }
    atual->Prev = novo;
  }
  else
  {
    Node *Last = fila->Rear;
    novo->Prev = Last;
    Last->Next = novo;
    fila->Rear = novo;
  }
  fila->size++;
}
void raiox(Queue *fila_sala_de_entrada, Queue *raiox, Hospital *hospital, int UT)
{
  if (fila_sala_de_entrada->Front == NULL)
  {
    return;
  }
  Pessoa *aux = (Pessoa *)fila_sala_de_entrada->Front->data;
  for (int i = 0; i < 5; i++)
  {
    if (hospital->raioX[i][0] == 0)
    {
      hospital->raioX[i][0] = 1;
      hospital->raioX[i][1] = faz__raiox();
      hospital->raioX[i][2] = aux->id;
      aux->E_raiox = UT;
      remove_fila(fila_sala_de_entrada);
      ordenado(raiox, aux);
      return;
    }
  }
}
void laudo(Queue *fila_raiox, Queue *laudo, Hospital *hospital, int UT)
{
  if (fila_raiox->Front == NULL)
  {
    return;
  }

  Pessoa *aux = (Pessoa *)fila_raiox->Front->data;
  if (aux->S_raiox == 0)
  {
    return;
  }

  for (int i = 0; i < 3; i++)
  {
    if (hospital->laudo[i][0] == 0)
    {
      hospital->laudo[i][0] = 1;
      hospital->laudo[i][1] = faz_laudo();
      hospital->laudo[i][2] = aux->id;
      aux->E_laudo = UT;
      remove_fila(fila_raiox);
      ordenado(laudo, aux);
      return;
    }
  }
}

int verifica_raiox(Hospital *h)
{
  for (int i = 0; i < 5; i++)
  {
    if (h->raioX[i][0] == 0)
    {
      return 1;
    }
  }
  return 0;
}
int verifica_laudo(Hospital *h)
{
  for (int i = 0; i < 3; i++)
  {
    if (h->laudo[i][0] == 0)
    {
      return 1;
    }
  }
  return 0;
}
void atualiza_tempo(Queue *Laudo, List *tempo)
{
  if (Laudo->Front == NULL || tempo->First == NULL)
  {
    return;
  }
  Node *aux = Laudo->Front;
  if (((Pessoa *)aux->data)->S_laudo == 0)
    return;
  for (Node *UT = tempo->First; UT != NULL; UT = UT->Next)
  {
    if (((Pessoa *)UT->data)->id == ((Pessoa *)aux->data)->id)
    {
      tempo->First->data = UT->data;
      remove_fila(Laudo);
      return;
    }
  }
}
void atualizacao_geral(Hospital *H, Queue *Raiox, Queue *Laudo, int UT)
{
  for (int i = 0; i < 5; i++)
  {
    if (H->raioX[i][1] != 0)
    {
      H->raioX[i][1]--;
    }
    if (H->raioX[i][1] == 0)
    {
      H->raioX[i][0] = 0;
    }
  }

  for (int i = 0; i < 3; i++)
  {
    if (H->laudo[i][1] != 0)
    {
      H->laudo[i][1]--;
    }
    if (H->laudo[i][1] == 0)
    {
      H->laudo[i][0] = 0;
    }
  }

  for (int i = 0; i < 5; i++)
  {
    if (H->raioX[i][1] == 0)
    {
      Node *Aux = Raiox->Front;
      Pessoa *paciente;
      while (Aux != NULL)
      {
        paciente = (Pessoa *)Aux->data;
        if (paciente->id == H->raioX[i][2])
        {
          paciente->S_raiox = UT;
          H->raioX[i][2] = 0;
          return;
        }
        Aux = Aux->Next;
      }
    }
  }

  for (int i = 0; i < 3; i++)
  {
    if (H->laudo[i][1] == 0)
    {
      Node *Aux = Laudo->Front;
      while (Aux != NULL)
      {
        Pessoa *paciente = (Pessoa *)Aux->data;
        if (paciente->id == H->laudo[i][2])
        {
          paciente->S_laudo = UT;
          H->laudo[i][2] = 0;
          return;
        }
        Aux = Aux->Next;
      }
    }
  }
}

float media_laudo(List *geral)
{
  float Soma = 0.0;
  int k = 0;
  Node *paciente = geral->First;
  for (int i = 0; i < geral->size; i++)
  {
    if (((Pessoa *)paciente->data)->S_laudo != 0)
    {
      Soma += ((Pessoa *)paciente->data)->S_laudo - ((Pessoa *)paciente->data)->entrada;
      k++;
    }
    paciente = paciente->Next;
  }
  if (k != 0)
  {
    return Soma / k;
  }
  return 0.0;
}

void media_doencas(List *geral, Hospital *h)
{
  if (geral->First == NULL)
  {
    return;
  }
  Node *aux = geral->First;
  for (int i = 0; i < 5; i++)
  {
    float somas = 0.0;
    int counter = 0;
    while (aux != NULL)
    {
      Pessoa *paciente = (Pessoa *)aux->data;
      if (paciente->S_laudo != 0 && paciente->doenca[0] == h->reg[i][0])
      {
        somas += paciente->S_laudo - paciente->entrada;
        counter++;
      }
      aux = aux->Next;
    }
    if (counter != 0)
    {
      h->reg[i][1] = somas / counter;
    }
    else
    {
      h->reg[i][1] = 0.0;
    }
    h->reg[i][1] = (counter != 0) ? (somas / counter) : 0.0;
    aux = geral->First;
  }
}
int pacientes_espera_pos_tempo(List *geral)
{
  float Soma = 0.0;
  int counter = 0;
  Node *aux = (Node *)malloc(sizeof(Node));
  aux = geral->First;

  for (int i = 0; i < geral->size; i++)
  {
    if (((Pessoa *)aux->data)->S_laudo != 0)
    {
      Soma = ((Pessoa *)aux->data)->S_laudo - ((Pessoa *)aux->data)->entrada;
      if (Soma > 7200)
      {
        counter++;
      }
    }
    aux = aux->Next;
  }
  return counter;
}
void test(List *Geral)
{
  Node *aux = Geral->First;

  for (int i = 0; i < Geral->size; i++)
  {
    if (((Pessoa *)aux->data)->S_raiox == 0)
    {
      printf("%d\n%d\n%d\n%d\n\n ", ((Pessoa *)aux->data)->E_raiox, ((Pessoa *)aux->data)->S_raiox, ((Pessoa *)aux->data)->E_laudo, ((Pessoa *)aux->data)->S_laudo);
      aux = aux->Next;
    }
  }
}
void printa_metrica(List *geral, Hospital *h)
{
  media_doencas(geral, h);
  printf("\n----------------------------------------------------------------------------------\n");
  printf("laudo: %f\n", media_laudo(geral));
  printf("Saúde Normal: %f\n", h->reg[0][1]);
  printf("Bronquite: %f\n", h->reg[1][1]);
  printf("Pneumonia: %f\n", h->reg[2][1]);
  printf("Fratura do fêmur: %f\n", h->reg[3][1]);
  printf("Apendicite: %f\n", h->reg[4][1]);
  printf("Fora do tempo: %d\n", pacientes_espera_pos_tempo(geral));
  printf("----------------------------------------------------------------------------------\n");
}

void libera_hospital(Hospital *h)
{
  if (h != NULL)
  {
    for (int i = 0; i < 5; i++)
    {
      free(h->reg[i]);
    }
    free(h->reg);
    free(h);
  }
}

//----------------------------implementações TP3-----------------------------------

//criar registro(log)
Log *cria_log()
{
  Log *logging = (Log *)malloc(sizeof(Log));
  logging->count = 0;
  return logging;
}

//registrando
void logging_de_evento(Log *logging, const char *mensagem)
{
  int k = 0;
  for (int i = 0; mensagem[k]; i++)
  {
    for (int j = 0; j < 256; j++)
    {
      if ((char)mensagem[k] == '|')
      {
        k++;
        break;
      }
      logging->eventos[i].message[j] = mensagem[k];
      k++;
    }
    logging->count++;
  }
}

//salvar mensagens no arquivo.txt
void salvar_arquivo_log(const Log *logging, const char *filename)
{
  FILE *arquivo = fopen(filename, "w");
  if (arquivo == NULL)
  {
    printf("Erro ao abrir o arquivo.\n");
    exit(1);
  }
  
  for (int i = 0; i < logging->count; i++)
  {
    fprintf(arquivo, "%s\n", logging->eventos[i].message);
  }
  fclose(arquivo);
}

// formatação de saída para o aquivo.txt
char *formata_lista(List *cont)
{
  char *texto;
  Node *atual;
  Pessoa *Pessoa;
  char E_string[10], E_raiox_string[10], S_raiox_string[10],
      E_laudo_string[10], S_string[10], idade[10], doenca[20];
  atual = cont->First;

  texto = (char *)malloc((255) * sizeof(char) * 9000);
  while (atual != NULL)
  {
    Pessoa = atual->data;

    // output
    sprintf(E_string, "%d", Pessoa->entrada);
    sprintf(E_raiox_string, "%d", Pessoa->E_raiox);
    sprintf(S_raiox_string, "%d", Pessoa->S_raiox);
    sprintf(E_laudo_string, "%d", Pessoa->E_laudo);
    sprintf(S_string, "%d", Pessoa->S_laudo);
    sprintf(idade, "%d", Pessoa->idade);
    if (Pessoa->doenca[0] == 1)
    {
      strcpy(doenca, "Saúde normal");
    }
    else if (Pessoa->doenca[0] == 2)
    {
      strcpy(doenca, "Bronquite");
    }
    else if (Pessoa->doenca[0] == 3)
    {
      strcpy(doenca, "Pneumonia");
    }
    else if (Pessoa->doenca[0] == 4)
    {
      strcpy(doenca, "Fratura de fêmur");
    }
    else if (Pessoa->doenca[0] == 5)
    {
      strcpy(doenca, "Apendicite");
    }

    // coloca o conteúdo na mensagem
    strcat(texto, "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
    strcat(texto, "Nome: ");
    strcat(texto, Pessoa->nome);
    strcat(texto, "\nCPF: ");
    strcat(texto, Pessoa->cpf);
    strcat(texto, "\nIdade: ");
    strcat(texto, idade);
    strcat(texto, "\nDoença: ");
    strcat(texto, doenca);

    // entrada e saida
    strcat(texto, "\nEntrada: ");
    strcat(texto, E_string);
    strcat(texto, "\nEntrada Raio-X: ");
    strcat(texto, E_raiox_string);
    strcat(texto, "\nSaída Raio-X: ");
    strcat(texto, S_raiox_string);
    strcat(texto, "\nEntrada Laudo: ");
    strcat(texto, E_laudo_string);
    strcat(texto, "\nSaída: ");
    strcat(texto, S_string);
    strcat(texto, "\n-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    strcat(texto, "\n|");
    atual = atual->Next;
  }
  return texto;
}