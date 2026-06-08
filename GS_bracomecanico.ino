#include <Servo.h>

// Servos do braço e da garra
Servo servoBraco;
Servo servoGarra;

// Pinos utilizados
const int PINO_BRACO = 9;
const int PINO_GARRA = 10;
const int LED_STATUS = 7;

// Posição inicial dos servos
int posBraco = 90;
int posGarra = 90;

void setup() {

  // Inicia a comunicação serial
  Serial.begin(9600);

  // Liga os servos aos pinos
  servoBraco.attach(PINO_BRACO);
  servoGarra.attach(PINO_GARRA);

  // Configura o LED
  pinMode(LED_STATUS, OUTPUT);

  // Deixa os servos na posição inicial
  servoBraco.write(posBraco);
  servoGarra.write(posGarra);

  // Acende o LED indicando que o sistema iniciou
  digitalWrite(LED_STATUS, HIGH);

  // Menu de comandos
  Serial.println("Sistema Inicializado, escolha uma opcao");
  Serial.println("U = Subir Braco");
  Serial.println("D = Descer Braco");
  Serial.println("O = Abrir Garra");
  Serial.println("C = Fechar Garra");
  Serial.println("S = Status");
}

void loop() {

  // Verifica se foi digitado algum comando
  if (Serial.available() > 0) {

    char comando = Serial.read();

    switch (toupper(comando)) {

      case 'U':
        subirBraco();
        break;

      case 'D':
        descerBraco();
        break;

      case 'O':
        abrirGarra();
        break;

      case 'C':
        fecharGarra();
        break;

      case 'S':
        mostrarStatus();
        break;

      default:
        Serial.println("Comando invalido!");
        Serial.println("");
        break;
    }
  }
}

// Faz o braço subir
void subirBraco() {

  if (posBraco < 180) {
    posBraco += 15;
  }

  servoBraco.write(posBraco);

  acaoLED();

  Serial.print("Braco elevado para ");
  Serial.print(posBraco);
  Serial.println(" graus");
  Serial.println("");
}

// Faz o braço descer
void descerBraco() {

  if (posBraco > 0) {
    posBraco -= 15;
  }

  servoBraco.write(posBraco);

  acaoLED();

  Serial.print("Braco abaixado para ");
  Serial.print(posBraco);
  Serial.println(" graus");
  Serial.println("");
}

// Abre a garra
void abrirGarra() {

  posGarra = 150;

  servoGarra.write(posGarra);

  acaoLED();

  Serial.println("Garra aberta");
  Serial.println("");
}

// Fecha a garra para pegar a amostra
void fecharGarra() {

  posGarra = 60;

  servoGarra.write(posGarra);

  acaoLED();

  Serial.println("Amostra capturada");
  Serial.println("Garra fechada");
  Serial.println("");
}

// Mostra o estado atual do sistema
void mostrarStatus() {

  Serial.println("===== STATUS =====");

  Serial.print("Posicao Braco: ");
  Serial.println(posBraco);

  Serial.print("Garra: ");

  if (posGarra >= 100) {
    Serial.println("Aberta");
  } else {
    Serial.println("Fechada");
  }

  Serial.println("Sistema Operacional");
  Serial.println("==================");
  Serial.println("");
}

// Pisca o LED quando alguma ação é executada
void acaoLED() {

  digitalWrite(LED_STATUS, LOW);
  delay(200);

  digitalWrite(LED_STATUS, HIGH);
  delay(200);
}