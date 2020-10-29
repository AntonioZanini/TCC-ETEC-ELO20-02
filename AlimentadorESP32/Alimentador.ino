
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
  // ESCREVER NO DISPLAY
  // ENVIAR PARA O APP?
}

int calcularReservatorio() {
  /*
   * VALORES DOS SENSORES:
   * HIGH: Com ração
   * LOW:  Sem ração
   */
  bool sensorSuperior = digitalRead(pinReservatorioAlto);
  bool sensorInferior = digitalRead(pinReservatorioVazio);
  int valorReservatorio = 0;

  if (sensorSuperior == HIGH && sensorInferior == HIGH) {
    valorReservatorio = 2;
  } else if (sensorSuperior == LOW && sensorInferior == HIGH) {
    valorReservatorio = 1;
  } else if (sensorSuperior == LOW && sensorInferior == LOW) {
    valorReservatorio = 0;
  }
  return valorReservatorio;
}

void desligarMotor() {
  digitalWrite(pinMotor, LOW);
}

void ligarMotor() {
  digitalWrite(pinMotor, HIGH);
}
