#define TEXTO_VAZIO       ""
#define NUMERO_INVALIDO   -1

Preferences armazenamento;

void iniciarArmazenamento() {
  if (verificarArmazenamentoTexto(AGENDAMENTOS)) {
    String agendamentosGravados = obterTexto(AGENDAMENTOS);
    atribuirAgendamentos(agendamentosGravados);
    publicarTopico(AGENDAMENTOS, agendamentosGravados.c_str());
  }
  if (verificarArmazenamentoNumero(ALARME_SELECIONADO)) {
    short alarmeSelecionadoGravado = obterNumero(ALARME_SELECIONADO);
    selecionarAlerta(alarmeSelecionadoGravado);
    publicarTopico(ALARME_SELECIONADO, String(alarmeSelecionadoGravado).c_str());
  }
  if (verificarArmazenamentoNumero(TEMPO_ABASTECIMENTO)) {
    short tempoAbastecimentoGravado = obterNumero(TEMPO_ABASTECIMENTO);
    atribuirTempoAbastecimento(tempoAbastecimentoGravado);
    publicarTopico(TEMPO_ABASTECIMENTO, String(tempoAbastecimentoGravado).c_str());
  }
}

bool verificarArmazenamentoTexto(char* chave) {
  bool resultado;
  armazenamento.begin(CONTEXTO, true);
  resultado = !armazenamento.getString(chave, TEXTO_VAZIO).equals(TEXTO_VAZIO);
  armazenamento.end();
  return resultado;
}

bool verificarArmazenamentoNumero(char* chave) {
  bool resultado;
  armazenamento.begin(CONTEXTO, true);
  resultado = armazenamento.getShort(chave, NUMERO_INVALIDO) != NUMERO_INVALIDO;
  armazenamento.end();
  return resultado;
}

void armazenarTexto(char* chave, String texto) {
  armazenamento.begin(CONTEXTO);
  armazenamento.putString(chave, texto);
  armazenamento.end();
}

void armazenarNumero(char* chave, int16_t  numero) {
  armazenamento.begin(CONTEXTO);
  armazenamento.putShort(chave, numero);
  armazenamento.end();
}

String obterTexto(char* chave) {
  String resultado;
  armazenamento.begin(CONTEXTO, true);
  resultado = armazenamento.getString(chave);
  armazenamento.end();
  return resultado;
}

short obterNumero(char* chave) {
  short resultado;
  armazenamento.begin(CONTEXTO, true);
  resultado = armazenamento.getShort(chave);
  armazenamento.end();
  return resultado;
}
