//Motor driver
const int rstPin = 21, sleepPin = 5, stepPin = 19, dirPin = 18, enaPin = 4;
int time_delay = 850, posicao = 0;

//Fim de cursos
const byte fimdeCurso = 25; 
const byte fimdeCurso2 = 26;
volatile byte fim1 = LOW, fim2 = LOW;
//Fim de curso de Software
int Max = -80000, Min = 80000; 

//Comunicacao
bool l_state = true, s_state = true;
const int ledPin = 13;

//Iluminacao
int relePin = 15;
bool r_state = HIGH;

float r = 1; //raio da polia

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
//  Serial.setTimeout(300);
  Serial.println("Iniciando...");
  Serial.flush();
  pinMode(ledPin, OUTPUT);

  //Rele
  pinMode(relePin, OUTPUT);
  digitalWrite(relePin, r_state);

  //Motor
  pinMode(rstPin, OUTPUT);
  pinMode(sleepPin, OUTPUT);
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  pinMode(enaPin, OUTPUT);
  digitalWrite(rstPin, HIGH);
  digitalWrite(sleepPin, LOW);
  digitalWrite(enaPin, HIGH);
  
  pinMode(fimdeCurso, INPUT_PULLUP);
  pinMode(fimdeCurso2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(fimdeCurso), stop1, FALLING);
  attachInterrupt(digitalPinToInterrupt(fimdeCurso2), stop2, CHANGE);
  
  Serial.flush();
}

//Funcao para o fim de curso
void stop1 () {
  digitalWrite(enaPin, HIGH);
//  posicao = Min;
  fim1 = HIGH;
}

void stop2 () {
  digitalWrite(enaPin, HIGH);
//  posicao = Max;
  fim2 = HIGH;
}


void loop() {
  // put your main code here, to run repeatedly:
  //Loop Serial
  if (Serial.available() > 0) {
//  delay(10);
    char option = Serial.read();
    Serial.print(option);
    switch (option) // Redireciona o código de acordo com a primeira letra
    {
      case '?': getPosition(); break;   // Print current target position
      case '!': test(); break;          // Turn led on/off
      case 'G': goTo(); break;          // Go to the desired position in steps
      case 'R': goToRelative(); break;  // Move the desired steps relative to current position
      case 'L': setLimits(); break;      // Set the axis limits
      case 'V': setDelay(); break; // Set velocity
      case 'S': setSleep(); break;      // Turn sleep on/off to save energy/disable outputs
      case 'I': setRele(); break;       // Turn Rele on/off
      case 'H': goHome(); break;       // Go to 0 position
    }

  }
}

void moveXY(float x, float y){
  //move o motor para um determinado ponto x, y
  //r é o raio da polia
  float theta1 = (-x + y)/r;
  float theta2 = (-x - y)/r;

  step_1(theta_to_steps(theta1));
  step_2(theta_to_steps(theta2));
}

int theta_to_steps(float theta){
  // Cada passo  = 1.8° de rev
  return (theta/1.8);
}

void step_1(int n){
  // Move o motor 1 n steps
  //TO DO: Reescrever a função Step para cada um dos motores
}

void step_2(int n){
  // Move o motor 2 n steps
  //TO DO: Reescrever a função Step para cada um dos motores
}


void goHome(){
  fim1 = LOW;
  while(!fim1){
    Step(-100);
  }
  Step(20);
  posicao = 0;
Serial.println(digitalRead(fimdeCurso));
Serial.println(fim1);
Serial.println();
  
}

void getPosition() {
  Serial.print(posicao);
  Serial.print(",OK\n");
}

void test() {
  l_state = !l_state;
  digitalWrite(ledPin, l_state);
  Serial.print(l_state);
  Serial.print(",OK\n");
}

void setSleep() {
  s_state = !s_state;
  digitalWrite(sleepPin, s_state); 
  digitalWrite(ledPin, s_state); //show sleep mode active
  Serial.print(s_state);
  Serial.print(",OK\n");
}

void goTo() {
  // TO DO: Trocar para movimentação dos dois motores
  digitalWrite(enaPin, LOW);
  digitalWrite(sleepPin, HIGH);
  int value = Serial.parseInt();
  if (value <= Max && value >= Min) {
    Step(value-posicao);
    Serial.print(",OK\n");
  }
  else {
    Serial.print(",XO\n");
  }
}


void setLimits() {
  Min = Serial.parseInt();
  Max = Serial.parseInt();
  Serial.print(Min);
  Serial.print(",");
  Serial.print(Max);
  Serial.print(",OK\n");
}

void setDelay() {
  int value = Serial.parseInt();
  Serial.print(value);
  if (value <= 2000 && value >= 500) {
    time_delay = value;
    Serial.print(",OK\n");
  }
  else {
    Serial.print(",XO\n");
  }
}

void setRele() {
  r_state = !r_state;
  digitalWrite(relePin, r_state); 
  Serial.print(r_state);
  Serial.print(",OK\n");
}


// Move the motor a set amount of steps, if positive move forward, if negative backwards
void Step(int steps){
  //Enabling movement
  digitalWrite(enaPin, LOW);    //Active LOW
  digitalWrite(sleepPin, HIGH);      //Active HIGH

  //Setting direction
  bool dir_state = HIGH;
  if (steps < 0){
    dir_state = LOW;
    steps = abs(steps);
  }
  
  digitalWrite(dirPin, dir_state);
  
  for (int i = 0; i < steps; i++) {
//    if(fim1 || fim2) return
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(time_delay);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(time_delay);
    if (dir_state) posicao += 1;
    else posicao -= 1;
  }
}

void goToRelative(){
  int delta = Serial.parseInt();
  Serial.print(posicao + delta);
  if (posicao + delta <= Max && posicao + delta >= Min) {
//    Step(delta); TO DO: Trocar por moveXY
    Serial.print(",OK\n");
  }
  else {
    Serial.print(",XO\n");
  }
}
