WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

const char* BROKER_ADDRESS = "192.168.2.110";
int BROKER_PORT = 1883;
const char* ID_MQTT = "esp32_mqtt";

char* topicos[] = {
  AGENDAMENTOS,
  TEMPO_ABASTECIMENTO,
  ALARME_SELECIONADO
};

void inciarMQTT() {
  mqttClient.setServer(BROKER_ADDRESS, BROKER_PORT);
  mqttClient.setCallback(receberResposta);
}

void conectarMQTT() {
  while (mqttClient.connected() == false && temporizar(2000, MQTT) == true) {
    if (mqttClient.connect(ID_MQTT) == true ) {
      assinarTopicos();
      return;
    }
    else {
      limparDisplay();
      escreverDisplay("FALHA NO MQTT", 0, 0);
      escreverDisplay("NOVA TENTATIVA", 1, 0);
      delay(400);
    }
  }
  limparDisplay();
  escreverDisplay("MQTT OFFLINE", 0, 0);
}

void assinarTopicos() {
  int totalTopicos = 3; //sizeof(topicos) / sizeof(topicos[0]);
  for (int atual=0; atual < totalTopicos; atual++) {
    mqttClient.subscribe(topicos[atual], 1); 
  }
}

void verificarMQTT() {
  if (verificarConexao() && mqttClient.connected() == false) {
    conectarMQTT();
  }
  mqttClient.loop();
}

void receberResposta(char* topico, byte* conteudo, unsigned int tamanho) {
  String topicoAtual = String(topico);
  String mensagem;

  for (int i = 0; i < tamanho; i++) {
    char caractere = (char)conteudo[i];
    mensagem = mensagem + caractere;
  }
  
  if (topicoAtual.equals(AGENDAMENTOS)) {
    armazenarTexto(AGENDAMENTOS, mensagem);
    atribuirAgendamentos(mensagem);
  } else if (topicoAtual.equals(TEMPO_ABASTECIMENTO)) {
    armazenarNumero(TEMPO_ABASTECIMENTO, mensagem.toInt());
    atribuirTempoAbastecimento(mensagem.toInt());    
  } else if (topicoAtual.equals(ALARME_SELECIONADO)) {
    armazenarNumero(ALARME_SELECIONADO, mensagem.toInt());
    selecionarAlerta(mensagem.toInt());
  } else if (topicoAtual.equals(TESTE_ABASTECIMENTO)) {
    testarAbastecimento();
  }
}

void publicarTopico(char* topico, const char* conteudo) {
  mqttClient.publish(topico, conteudo);
}
