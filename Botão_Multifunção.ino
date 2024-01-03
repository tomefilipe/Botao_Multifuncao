#include <SoftwareSerial.h>

#define tempoReset     2000  //define o tempo em que o botao Start deve ficar apertado para efetuar a funcão 2 (em milisegundos)
#define tempoReset2    5000  //define o tempo em que o botao Start deve ficar apertado para efetuar a funcão 3 
#define pinBotaoStart  2    // pino do botão
#define pinLED1 8            // pino LED1
#define pinLED2 9            // pino LED2
#define pinLED3 10           // pino LED3

byte pinBotaoStartApertado();



void setup() {
  
  pinMode(pinLED1, OUTPUT);    
  pinMode(pinLED2, OUTPUT);    
  pinMode(pinLED3, OUTPUT);   
  pinMode(pinBotaoStart, INPUT);
  Serial.begin(115200);
}

void loop() 
{
  

  byte estadoBotaoStart = pinBotaoStartApertado();  // ler o estado do botão: 1 clic ou quando segura o botão
  if ( estadoBotaoStart == 1 )                      // ser for um clic
  {
    digitalWrite(pinLED1, LOW);
    digitalWrite(pinLED2, LOW);
    digitalWrite(pinLED3, HIGH);
    delay(2000);
  }

  if ( estadoBotaoStart == 2 )                     // se o botão for apertado por dois segundos 
  {
    digitalWrite(pinLED1, HIGH);
    delay(2000);
    digitalWrite(pinLED2, LOW);
    digitalWrite(pinLED3, LOW);
    delay(2000);
  }

  if ( estadoBotaoStart == 3 )                     // se o botão for apertado por cinco segundos 
  {
    digitalWrite(pinLED1, HIGH);
    digitalWrite(pinLED2, LOW);
    digitalWrite(pinLED3, LOW);
    delay(2000);
  }

  digitalWrite(pinLED1, LOW);
  digitalWrite(pinLED1, LOW);
  digitalWrite(pinLED1, LOW);

}
   

byte pinBotaoStartApertado()                    // função para verificar se teve um clic no botão ou se ficou precionado 
  {
    #define tempoDebounce 50 //(tempo para eliminar o efeito Bounce EM MILISEGUNDOS)

    static bool estadoBotaoAnt; 
    static unsigned long delayBotao = 0;
    static unsigned long botaoApertado;
    static byte fase = 0;
    bool estadoBotao;
    byte estadoRet;

  estadoRet = 0;  
  if ( (millis() - delayBotao) > tempoDebounce ) 
  {
    estadoBotao = digitalRead(pinBotaoStart);
    if ( !estadoBotao && (estadoBotao != estadoBotaoAnt) ) 
    {
      delayBotao = millis();          
      botaoApertado = millis();
      fase = 1;
    } 
     

    if ( (fase == 1) && ((millis() - botaoApertado) > tempoReset2) ) 
    {
      fase = 0;
      estadoRet = 3;
    }

    if ( (fase == 1) && ((millis() - botaoApertado) > tempoReset) && estadoBotaoAnt != estadoBotao )
    {
      fase = 0;
      estadoRet = 2;
    }
                 
       
    if ( estadoBotao && (estadoBotao != estadoBotaoAnt) ) 
    {
      delayBotao = millis();
      if ( fase == 1 ) 
      {
        estadoRet = 1;
      } 
      fase = 0;
    } 
       
    estadoBotaoAnt = estadoBotao;
  }

  return estadoRet;
}  
