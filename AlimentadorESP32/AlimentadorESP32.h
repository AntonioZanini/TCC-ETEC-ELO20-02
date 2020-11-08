#define CONTEXTO "ALIMENTADOR_ANIMAL"

#define PINO_MOTOR                  32
#define PINO_RESERVATORIO_SUPERIOR  27
#define PINO_RESERVATORIO_INFERIOR  26
#define PINO_BUZZER                 25

#define WIFI          0
#define TIME          1
#define ALIMENTADOR   2
#define MQTT          3

#define AGENDAMENTOS        "alimentador/horariosAlimentacao"
#define ALARME_SELECIONADO  "alimentador/tipoAlertaSonoro"
#define TEMPO_ABASTECIMENTO "alimentador/tempoAbastecimento"
#define TESTE_ABASTECIMENTO "alimentador/testeAbastecimento"
#define NIVEL_RESERVATORIO  "alimentador/nivelReservatorio"

typedef enum NivelAbastecimento {
  VAZIO,
  ABASTECIDO,
  CHEIO
} nivel_abastecimento_t;
