enum NivelAbastecimento {
  VAZIO,
  ABASTECIDO,
  CHEIO
}

byte tempoAbastecimento = 0;

void iniciarPinosAlimentador() {
  pinMode(pinMotor, OUTPUT);
  pinMode(pinReservatorioAlto, INPUT);
  pinMode(pinReservatorioVazio, INPUT);
  desligarMotor();
}

void atualizarAlimentador() {
  if (verificarAgendamento() == true) {
    while(temporizador(tempoAbastecimento * 1000)){
      alimentacao();
    }
    desligarMotor();
    delay(60000);
  }
}

bool verificarAgendamento() {
  return false;
}

void alimentacao() {
  if (calcularReservatorio() >= 1) {   
    ligarMotor();
  } else {
    desligarMotor();
    notificarFaltaRacao();
  }
}

void notificarFaltaRacao() {
  limparDisplay();
  escreverDisplay("RESERVATÓRIO", 0, 2);
  escreverDisplay("VAZIO!", 0, 5);

  // TOCAR SOM SELECIONADO

  // ENVIAR PARA O APP?
}

int calcularReservatorio() {
  /*
   * VALORES DOS SENSORES:
   * HIGH: Com ração
   * LOW:  Sem ração
   */
  bool sensorSuperior = digitalRead(PINO_RESERVATORIO_SUPERIOR);
  bool sensorInferior = digitalRead(PINO_RESERVATORIO_INFERIOR);
  NivelAbastecimento valorReservatorio = VAZIO;

  if (sensorSuperior == HIGH && sensorInferior == HIGH) {
    valorReservatorio = CHEIO;
  } else if (sensorSuperior == LOW && sensorInferior == HIGH) {
    valorReservatorio = ABASTECIDO;
  } else if (sensorSuperior == LOW && sensorInferior == LOW) {
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
