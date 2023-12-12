# Trabalho 3 Estrutura de Dados - Desenvolvimento de Função Logging (continuação do trabalho 2)
# Alunos: Thiago Augusto de Carvalho 
# Professor: Thiago Paixão

##Introdução

O propósito deste código é gerenciar a fila de pacientes em um hospital que atende a cinco tipos de patologias (Saúde normal, Bronquite, Pneumonia, Fratura de Fêmur e Apendicite). No hospital, os pacientes passam por uma sala de raio-x (com cinco salas disponíveis) e, em seguida, recebem um laudo (com três salas disponíveis).

O código utiliza uma estrutura de dados do tipo Lista para organizar as informações gerais dos pacientes, incluindo horários de entrada e saída do hospital, bem como detalhes específicos de cada sala. Esses dados são essenciais para calcular métricas que avaliam o desempenho do hospital, identificando possíveis gargalos.

Cada paciente é atribuído um nome, CPF, idade, identificador, patologia (indicando o tipo e gravidade da doença) e horários associados aos eventos no hospital. Além disso, o hospital mantém registros das salas de raio-x e laudo, incluindo informações sobre disponibilidade, tempo de consulta e identificação do paciente.

A fila de atendimento é dinamicamente atualizada para priorizar os pacientes com base na gravidade da patologia. A cada iteração do código, representando uma unidade de tempo, métricas importantes são exibidas a cada intervalo de 10 unidades de tempo. Essas métricas incluem o tempo médio para obtenção de um laudo, média de espera por patologia e a quantidade de exames realizados após o limite de tempo estabelecido.

Foram adicionadas as funções de logging para registrar os dados em um arquivo.txt.
OBS: O arquivo está preenchido com a saida de uma execução para o professor ter uma ideia do que esperar da saída do programa antes de executar.

Para executar o programa em um ambiente compatível (como um sistema Linux com GCC 11), basta utilizar o comando make seguido por ./main no terminal. Essa sequência de comandos compila e executa o programa.