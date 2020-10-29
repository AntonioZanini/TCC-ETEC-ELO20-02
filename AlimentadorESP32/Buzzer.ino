int alertaSelecionado = 0;
int notaAtual = 0;
bool pararSom = false;

void iniciarBuzzer() {
  EasyBuzzer.setPin(PINO_BUZZER);
}

void selecionarAlerta(int numeroAlerta) {
  alertaSelecionado = numeroAlerta;
}

int* obterAlerta() {
  switch (alertaSelecionado) {
    case 0:
      return melodyNokia;
    case 1:
      return melodyStarTrek;
    case 2:
      return melodyJigglypuff;
    default:
      return melodyNokia;
  }
}

void pararMusica() {
  EasyBuzzer.stopBeep();
  pararSom = true;
}

void tocarNota() {
  int* musicaAtual = obterAlerta();
  int totalNotas = sizeof(musicaAtual) / sizeof(musicaAtual[0]) / 2;
  if (pararSom == true) {
    return;
  }
  if (notaAtual == totalNotas) {
    notaAtual = 0;
  }
  EasyBuzzer.singleBeep(
    musicaAtual[notaAtual],
    obterTempo(musicaAtual[notaAtual+1]),
    tocarNota
  );
  notaAtual += 2;
}


int obterTempo(int divisor) {
  int duracao = 0;
  int compasso = (60000 * 4) / 80;
  
  if (divisor > 0) {
    // regular note, just proceed
    duracao = (compasso) / divisor;
  } else if (divisor < 0) {
    // dotted notes are represented with negative durations!!
    duracao = (compasso) / abs(divisor);
    duracao *= 1.5; // increases the duration in half for dotted notes
  }

  return duracao;
}

void atualizarMusica() {
  EasyBuzzer.update();
}
