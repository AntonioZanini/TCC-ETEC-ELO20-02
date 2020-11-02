volatile unsigned long tempoAtivacao[] = { 0, 0, 0, 0, 0 };

bool temporizar(int milissegundos, int remetente) {
  unsigned long tempoAtual = millis();
  if (tempoAtivacao[remetente] == 0) {
    tempoAtivacao[remetente] = tempoAtual;
  }
  if (tempoAtual - tempoAtivacao[remetente] > milissegundos)
  {
    tempoAtivacao[remetente] = 0;
    return false;
  }
  return true;
}

String preencherZeros(int numero, int tamanho) {
  String textoNumero = String(numero);
  int tamanhoNumero = textoNumero.length();
  if (tamanhoNumero < tamanho) {
    for (int n = 0; n < (tamanho - tamanhoNumero); n++) {
      textoNumero = "0" + textoNumero;
    }
  }
  return textoNumero;
}
