unsigned long tempoAtivacao = 0;

bool temporizar(int milissegundos) {
  unsigned long tempoAtual = millis();
  if (tempoAtivacao == 0) {
    tempoAtivacao = tempoAtual;
  }
  if (tempoAtual - tempoAtivacao > milissegundos)
  {
    tempoAtivacao = 0;
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
