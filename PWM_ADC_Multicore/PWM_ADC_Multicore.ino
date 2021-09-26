//Placa esp32 doit devkit v1

//Baseado nos tutoriais:
//Tutorial de multicore do esp32: https://www.fernandok.com/2018/04/esp32-com-arduino-ide-programacao-multi.html
//Informacoes sobre o ADC do esp32: https://randomnerdtutorials.com/esp32-adc-analog-read-arduino-ide/
//Informacoes sobre o PWM do esp32: https://www.electronicshub.org/esp32-pwm-tutorial/
bool state_led = LOW;

//pinos usados
const uint8_t pin_led = 18;
const uint8_t pin_pot = 34;

//Configurações do PWM
int dutyCycle;
const int PWMFreq = 1000; /* 1 KHz */
const int PWMChannel = 0;
const int PWMResolution = 16; //frequencia e resolução são inversamente proporcionais
const int MAX_DUTY_CYCLE = (int)(pow(2, PWMResolution) - 1);
const int pin_PWM_out=16;


//variaveis que indicam o núcleo
static uint8_t taskCoreZero = 0;
static uint8_t taskCoreOne  = 1;

void setup() {
  //led para debug
  pinMode(pin_led, OUTPUT);

  //Inicia a comunicação serial
  Serial.begin(115200);

  //ledc é a função análoga ao analogWrite das placas arduino
  ledcSetup(PWMChannel, PWMFreq, PWMResolution);
  /* Attach the LED PWM Channel to the GPIO Pin */
  ledcAttachPin(pin_PWM_out, PWMChannel);
  
  delay(500); //tempo para a tarefa iniciar

  //cria uma tarefa que será executada na função coreTaskTwo, com prioridade 5 e execução no núcleo 0
  //coreTaskTwo:
  xTaskCreatePinnedToCore(
    coreTaskTwo,   /* função que implementa a tarefa */
    "coreTaskTwo", /* nome da tarefa */
    10000,      /* número de palavras a serem alocadas para uso com a pilha da tarefa */
    NULL,       /* parâmetro de entrada para a tarefa (pode ser NULL) */
    5,          /* prioridade da tarefa (0 a N) */
    NULL,       /* referência para a tarefa (pode ser NULL) */
    taskCoreZero);         /* Núcleo que executará a tarefa */

}

void loop() {
  //Mudando estado da porta para avaliar a velocidade
  digitalWrite(pin_led, HIGH);
  int potValue = analogRead(pin_pot);
  Serial.println(potValue);
  delayMicroseconds(10);
  digitalWrite(pin_led, LOW);

}

//essa função será responsável apenas por ler o ADC e mudar o estado de um led
void coreTaskOne( void * pvParameters ) {
  String taskMessage = "Task one running on core ";
  taskMessage = taskMessage + xPortGetCoreID();
  Serial.println(taskMessage);

  while (true) {
    //Muda o estado do led para avaliar a velocidade no osciloscópio
    state_led = !state_led;
    digitalWrite(pin_led, state_led);
    int potValue = analogRead(pin_pot);
    vTaskDelay(1);  //Só consegui utilizar delay de milisegundos dentro do outro core, por isso movi para o loop
    yield();        //Alimenta o watchdog
    Serial.println(potValue);
  }
}

//essa função será responsável por gerar uma rampa de 0-3V com o PWM utilizando os 16 bits de resolução
//Em paralelo ao loop principal
void coreTaskTwo( void * pvParameters ) {

  //Mensagem para informar em que core a função está rodando
  String taskMessage = "Task Two running on core ";
  taskMessage = taskMessage + xPortGetCoreID();
  Serial.println(taskMessage);

  while (true) {
    /* Rampa de subida com PWM */
    for (dutyCycle = 0; dutyCycle <= MAX_DUTY_CYCLE; dutyCycle++) {
      ledcWrite(PWMChannel, dutyCycle);
      vTaskDelay(1);  //Delay de 1ms utilizando função especifica para thread
      yield();        //Alimenta o watchdog
      //delayMicroseconds(100);
    }
    /* Rampa de descida com PWM */
    for (dutyCycle = MAX_DUTY_CYCLE; dutyCycle >= 0; dutyCycle--) {
      ledcWrite(PWMChannel, dutyCycle);
      vTaskDelay(1);  //Delay de 1ms utilizando função especifica para thread
      yield();        //Alimenta o watchdog
      //delayMicroseconds(100);
    }

  }
}
