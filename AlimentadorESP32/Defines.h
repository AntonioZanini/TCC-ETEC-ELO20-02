#define PINO_MOTOR 22
#define PINO_RESERVATORIO_SUPERIOR 24
#define PINO_RESERVATORIO_INFERIOR 26
#define PINO_BUZZER 25

#define COM_RACAO 1
#define SEM_RACAO 2

typedef enum NivelAbastecimento {
  VAZIO,
  ABASTECIDO,
  CHEIO
} nivel_abastecimento_t;
