# Robson8266
Repositório para ajudar o Robson a usar o presente dele

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
  
  
