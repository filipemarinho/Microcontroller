# Robson8266
Repositório para ajudar o Robson a usar o presente dele

Robson aprenda a usar o github imeditamente!!!




Tutoriais para uso do ESP8266:
===

## Instalação da Arduino IDE:

Seja um bom computeiro e baixe os arquivos de instalação do [site oficial](https://www.arduino.cc/en/main/software) para sua arquitetura.

Coloque os arquivos baixados na sua /home (ou /opt se você utilizar), extraia e renomeie a pasta criada para "Arduino".

Dê permissão de execução ao arquivo install.sh que está dentro do diretório, faça isso pelo sub-menu de propriedades do arquivo ou pelo terminal com:

```
chmod +x install.sh
```

Execute o script de instalação:

```
./install.sh
```

Torça pra dar certo.

## Usando a Arduino IDE pela primeira vez

Se tudo der certo você verá a Arduino IDE no menu de aplicações, abra o programa.

Provavelmente você precisará se adicionar ao grupo local para ter permissão de acesso as portas USB, você pode fazer isso com:
```
sudo usermod -a -G dialout <username>
```
Lempre de substituir <username> pelo seu username!!!
  
É bom reiniciar paras alterações serem aplicadas.


Feito isso você deve estar preparando pra fazer uploads paa placas arduino, mas para utilizar o ESP8266 é preciso fazer mais ajustes.

## Usando o ESP8266 na Arduino IDE:

A Expressif, fabricante dos chips do ESP8266 e ESP32 tem ambientes de programação nativos como a IDF, mas utilizar a Arduino IDE é com certeza o método mais fácil para começar a programar, segue o fio para fazer a configuração:

### Driver CH340G:

Inicialmente você precisará do driver do USB Serial do ESP, normalmene ele usam o CH340g, como o Linux é top você só precisa conectar o ESP a uma porta USB usando um cabo do tipo **MicroUSB de dados**. O cabo de dados é importante (me pergunte o pq se quiser saber), normalmente os que vem com os smartphones funcionam. O linux vai instalar os drivers normalmente depois de ter conectado o USB (**Viva o linux**).

Caso esteja usando o windows dê seus pulos para instalar o driver.

### Suporte ao ESP8266

Vá em preferências dentro do menu de arquivos:

![Vá em preferências](https://uploads.filipeflop.com/2016/05/IDE-Arquivo.png)

no campo **URLs adicionais de Gerenciadores de Placas** adicione:

```
http://arduino.esp8266.com/stable/package_esp8266com_index.json
```

![adicione a URL](https://uploads.filipeflop.com/2016/05/IDE-Preferencias.png)


 Navegue até Ferramentas -> Placa -> Gerenciador de Placas:
 
![vá nas configurações de placas](https://uploads.filipeflop.com/2016/05/IDE-Menu-Ferramentas-Placa.png)

Procure por esp8266 e instale o pacote de placas.

Pronto, agora você tem suporte ao ESP8266 dentro da Arduino IDE.

### Selecionando a placa certa

Para que o compilador saiba gerar o código na linguagem montadora correta para sua arquitetura você precisa indicar que tipo de hardware está utilizando. Você fará isso selecionado a sua placa. Preste atenção: **antes de compilar/fazer upload de um código selecione a placa correta**

Vá até Ferramentas -> Placas:
E selecione NodeMCU 1.0 (ESP 12-E module), normalmente esse funciona.

![Selecionando a placa](https://uploads.filipeflop.com/2016/05/IDE-Selecao-Placa.png)

## Seu primeiro programa:

Parabéns, muito trampo isso tudo, vamos ao que interessa: seu primeiro programa. Normalmente você faria um "Hello World!" mas em microcontroladores o hello world é muito mais legal e se chama **Blynk**. 

Como o nome sugere o objetivo é Piscar um led que já vem embutido na placa, para verificar o funcionamento geral do que fizemos até aqui.

Em geral as etapas de um projeto qualquer são:
- Selecionar a placa que está trabalhando 
- Escrever o código
- Compilar e ver se retorna algum warning. Você pode compilar o programa apertando no icone do certo
- Conectar a placa no USB
- Selecionar a porta USB
- Fazer o upload do código para placa
- Torcer pra funcionar

### Blink:
O código é esse, não é dificil de entender, ele apaga e acende um led, qualquer duvida olhe a documentação ou me pergunte.


```
void setup() {
// Define o  pino do LED_BUILTIN (normalmente ligado ao pino 13) como saida
pinMode(LED_BUILTIN, OUTPUT);
}
void loop() {
digitalWrite(13, HIGH); // Acende o Led
delay(1000); // Aguarda 1 segundo
digitalWrite(13, LOW); // Apaga o Led
delay(1000); // Aguarda 1 segundo
}
```
cole este código na aréa de código da IDE.
Aperte no certo para compilar, veja se existem erros.

Vá em Ferramentas->Porta e verifique se a porta USB está selecionada.

Clique na seta para direita para fazer o upload do código.

Olhe para placa pra ver se o LED acende.


Fontes:
https://www.arduino.cc/en/guide/linux 
https://www.filipeflop.com/blog/programar-nodemcu-com-ide-arduino/
