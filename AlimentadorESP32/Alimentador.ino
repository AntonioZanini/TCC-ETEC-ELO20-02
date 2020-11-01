#define COM_RACAO 1
#define SEM_RACAO 0

short tempoAbastecimento = 0;
String agendamentos;
nivel_abastecimento_t nivelAtual = VAZIO;

void iniciarPinosAlimentador() {
  pinMode(PINO_MOTOR, OUTPUT);
  pinMode(PINO_RESERVATORIO_SUPERIOR, INPUT);
  pinMode(PINO_RESERVATORIO_INFERIOR, INPUT);
  desligarMotor();
}

void atualizarAlimentador() {
  if (verificarAgendamento() == true) {
    while(temporizar(tempoAbastecimento * 1000, ALIMENTADOR)){
      alimentacao();
    }
    desligarMotor();
    delay(60000);
  }
}

bool verificarAgendamento() {
  return false;
}

void atribuirTempoAbastecimento(short tempoNovo) {
  tempoAbastecimento = tempoNovo;
}

void atribuirAgendamentos(String agendamentosNovos) {
  agendamentos = agendamentosNovos;
}

void alimentacao() {
  nivel_abastecimento_t nivelCalculado = calcularReservatorio();
  if (nivelCalculado != nivelAtual) {
    publicarTopico(NIVEL_RESERVATORIO, String(nivelCalculado).c_str());
    nivelAtual = nivelCalculado;
  }
  if (nivelCalculado > VAZIO) {   
    ligarMotor();
  } else {
    desligarMotor();
    notificarFaltaRacao();
  }
}

void notificarFaltaRacao() {
  limparDisplay();
  escreverDisplay("RESERVATÓRIO", 0, 2);
  escreverDisplay("VAZIO!", 1, 5);

  tocarAlerta();

  // ENVIAR PARA O APP?
}

nivel_abastecimento_t calcularReservatorio() {
  bool sensorSuperior = digitalRead(PINO_RESERVATORIO_SUPERIOR);
  bool sensorInferior = digitalRead(PINO_RESERVATORIO_INFERIOR);
  nivel_abastecimento_t valorReservatorio = VAZIO;

  if (sensorSuperior == COM_RACAO && sensorInferior == COM_RACAO) {
    valorReservatorio = CHEIO;
  } else if (sensorSuperior == SEM_RACAO && sensorInferior == COM_RACAO) {
    valorReservatorio = ABASTECIDO;
  } else if (sensorSuperior == SEM_RACAO && sensorInferior == SEM_RACAO) {
    valorReservatorio = VAZIO;
  }
  return valorReservatorio;
}

void desligarMotor() {
  digitalWrite(PINO_MOTOR, LOW);
}

void ligarMotor() {
  digitalWrite(PINO_MOTOR, HIGH);
}
