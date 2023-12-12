#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "hospital.h"

int main()
{
  List *listGeral = cria_lista();
  Queue *Entrada = cria_fila();
  Queue *Raiox = cria_fila();
  Queue *Laudo = cria_fila();
  Hospital *H = cria_hospital();
  Log *log = cria_log();
  srand(time(NULL));

  for (int UT = 1; UT < 43201; UT++)
  {
    if (faz_pessoa())
    {
      Pessoa *paciente = faz_paciente(UT);
      inserir_lista(listGeral, paciente);
      ordenado(Entrada, paciente);
    }
    atualizacao_geral(H, Raiox, Laudo, UT);

    if (verifica_raiox(H))
    {
      raiox(Entrada, Raiox, H, UT);
    }
    if (verifica_laudo(H))
    {
      laudo(Raiox, Laudo, H, UT);
    }
    atualiza_tempo(Laudo, listGeral);
    if ((UT % 10) == 0)
    {
      // sleep(1);
      printa_metrica(listGeral, H);
    }
  }

  // saidas de registro
  logging_de_evento(log, formata_lista(listGeral));
  salvar_arquivo_log(log, "log.txt");
  // liberar geral
  libera_lista(listGeral);
  libera_fila(Raiox);
  libera_fila(Laudo);
  libera_fila(Entrada);
  libera_hospital(H);
  return 0;
}