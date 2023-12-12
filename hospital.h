#ifndef HOSPITAL_H
#define HOSPITAL_H

typedef struct node Node;
typedef struct list List;
typedef struct queue Queue;
typedef struct pessoa Pessoa;
typedef struct hospital Hospital;
typedef struct log Log;
typedef struct log_Evento Log_Evento;

List *cria_lista();
void inserir_lista(List *list, void *data);
void remove_lista(List *l, void *val);
void libera_lista(List *list);
Queue *cria_fila();
void remove_fila(Queue *fila);
void libera_fila(Queue *fila);
Hospital *cria_hospital();
int faz_pessoa();
int *faz__doenca();
int faz__raiox();
int faz_laudo();
char *faz_nome();
int faz_idade();
Pessoa *faz_paciente(int id);
void ordenado(Queue *fila, Pessoa *novo_paciente);
void raiox(Queue *fila_sala_de_entrada, Queue *raiox, Hospital *hospital, int UT);
void laudo(Queue *fila_raiox, Queue *laudo, Hospital *hospital, int UT);
int verifica_raiox(Hospital *h);
int verifica_laudo(Hospital *h);
void atualiza_tempo(Queue *Laudo, List *tempo);
void atualizacao_geral(Hospital *H, Queue *Raiox, Queue *Laudo, int UT);
float media_laudo(List *geral);
void media_doencas(List *geral, Hospital *h);
int pacientes_espera_pos_tempo(List *geral);
void printa_metrica(List *geral, Hospital *h);
void libera_hospital(Hospital *h);
Log *cria_log();
void logging_de_evento(Log *logging, const char *mensagem);
void salvar_arquivo_log(const Log *logging, const char *filename);
char *formata_lista(List *cont);
#endif