int totalNotas = 200;
int NotasMusica[] = {};
int duracaoNotas[] = {};

int notaAtual = 0;
bool pararSom = false;

void iniciarBuzzer() {
  EasyBuzzer.setPin(PINO_BUZZER);
}

void pararMusica() {
  EasyBuzzer.stopBeep();
  pararSom = true;
}

void tocarNota() {
  if (pararSom == true) {
    return;
  }
  if (notaAtual == totalNotas) {
    notaAtual = 0;
  }
  EasyBuzzer.singleBeep(
    NotasMusica[notaAtual],
    duracaoNotas[notaAtual],
    tocarNota
  );
  notaAtual += 1;
}

void atualizarMusica() {
  EasyBuzzer.update();
}
