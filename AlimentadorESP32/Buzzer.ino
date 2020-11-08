short  alertaSelecionado = 1;
int    notaAtual = 0;
bool   emExecucao = false;
int*   melodiaSelecionada;
int    tamanhoMelodia;

void iniciarBuzzer() {
  EasyBuzzer.setPin(PINO_BUZZER);
}

void selecionarAlerta(short numeroAlerta) {
  alertaSelecionado = numeroAlerta;
}

void selecionarMelodia() {
  switch (alertaSelecionado) {
    case 0:
      tamanhoMelodia = TAMANHO_ALERTA_SIMPLES;
      prepararMelodia(alertaSonoroSimples);
      break;
    case 1:
      tamanhoMelodia = TAMANHO_MUSICA_CURTA;
      prepararMelodia(alertaMusicalCurto);
      break;
    case 2:
      tamanhoMelodia = TAMANHO_MUSICA_LONGA;
      prepararMelodia(alertaMusicalLongo);
      break;
    default:
      tamanhoMelodia = TAMANHO_ALERTA_SIMPLES;
      prepararMelodia(alertaSonoroSimples);
  }
}

void prepararMelodia(int melodia[]) {
  if (melodiaSelecionada != NULL) {
    free(melodiaSelecionada);
  }
  melodiaSelecionada = (int *) malloc(tamanhoMelodia * sizeof(int));
  for (int i=0; i<tamanhoMelodia; i++) {
    melodiaSelecionada[i] = melodia[i];
  }
}

void pararAlerta() {
  EasyBuzzer.stopBeep();
}

void tocarAlerta() {
  selecionarMelodia();
  if (notaAtual == tamanhoMelodia) {
    notaAtual = 0;
    pararAlerta();
    return;
  }
  EasyBuzzer.singleBeep(
    melodiaSelecionada[notaAtual],
    obterTempo(melodiaSelecionada[notaAtual+1]),
    tocarAlerta
  );
  notaAtual += 2;
}

int obterTempo(int divisor) {
  int duracao = 0;
  int compasso = (60000 * 4) / 80;
  
  if (divisor > 0) {
    duracao = (compasso) / divisor;
  } else if (divisor < 0) {
    duracao = (compasso) / abs(divisor);
    duracao *= 1.5;
  }

  return duracao;
}

void atualizarMusica() {
  EasyBuzzer.update();
}
