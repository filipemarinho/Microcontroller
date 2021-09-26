//Placa esp32 doit devkit v1

//Baseado nos tutoriais:
//Tutorial de multicore do esp32: https://www.fernandok.com/2018/04/esp32-com-arduino-ide-programacao-multi.html
//Informacoes sobre o ADC do esp32: https://randomnerdtutorials.com/esp32-adc-analog-read-arduino-ide/
//Informacoes sobre o DAC do esp32: https://www.filipeflop.com/blog/como-usar-os-dacs-do-esp32/

bool state_led = LOW;

//pinos usados
const uint8_t pin_led = 18;
const uint8_t pin_pot = 34;
const uint8_t pin_DAC0 = 25;


//variaveis que indicam o núcleo
static uint8_t taskCoreZero = 0;
static uint8_t taskCoreOne  = 1;

void setup() {
  //led para debug
  pinMode(pin_led, OUTPUT);

  //Inicia a comunicação serial
  Serial.begin(115200);


  //cria uma tarefa que será executada na função coreTaskOne, com prioridade 2 e execução no núcleo 1
  //coreTaskOne:
//  xTaskCreatePinnedToCore(
//                    coreTaskOne,   /* função que implementa a tarefa */
//                    "coreTaskOne", /* nome da tarefa */
//                    10000,      /* número de palavras a serem alocadas para uso com a pilha da tarefa */
//                    NULL,       /* parâmetro de entrada para a tarefa (pode ser NULL) */
//                    5,          /* prioridade da tarefa (0 a N) */
//                    NULL,       /* referência para a tarefa (pode ser NULL) */
//                    taskCoreOne);         /* Núcleo que executará a tarefa */

    delay(500); //tempo para a tarefa iniciar

   //cria uma tarefa que será executada na função coreTaskTwo, com prioridade 2 e execução no núcleo 0
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
void coreTaskOne( void * pvParameters ){
    String taskMessage = "Task one running on core ";
    taskMessage = taskMessage + xPortGetCoreID();
    Serial.println(taskMessage);
    
     while(true){
        //Muda o estado do led para avaliar a velocidade no osciloscópio
        state_led = !state_led;
        digitalWrite(pin_led, state_led);
        int potValue = analogRead(pin_pot);
        vTaskDelay(1);  //Só consegui utilizar delay de milisegundos dentro do outro core, por isso movi para o loop
        yield();        //Alimenta o watchdog
        Serial.println(potValue);
    } 
}

//essa função será responsável por gerar uma rampa de 0-3V com o DAC utilizando os 8 bits de resolução
//Em paralelo ao loop principal
void coreTaskTwo( void * pvParameters ){

      //Mensagem para informar em que core a função está rodando
      String taskMessage = "Task Two running on core ";
      taskMessage = taskMessage + xPortGetCoreID();
      Serial.println(taskMessage);
      
     while(true){
      for(int i=0; i<=255; i++)
      {
          dacWrite(pin_DAC0, i);  
          vTaskDelay(1);  //Delay de 1ms utilizando as funções especificas para utilização multicore
          yield();        //Alimenta o watchdog
      }

    } 
}
