#include <SevenSegmentsK.h>

//Objeto que controla o display
SevenSegmentsK sevenSegmentsK; 


void setup()
{   
    //Inicializa Serial
    Serial.begin(9600);
    //Pinos dos segmentos
    int segmentPins[8] = {PB1, PA10, PA8, PB14, PB12, PB0, PA9, PB15};
    //Pinos das posições dos dígitos
    int digitPins[8] = {PA15, PB3, PB4, PB5, PB6, PB7, PB8, PB9};
    //Indica os pinos de segmento, posição dos dígitos de interrupção, se o display é cátodo comum ou ânodo comum e quantidade de dígitos
    sevenSegmentsK.set(
      segmentPins,//Pinos de segmento
      digitPins, //Pinos da posição dos dígitos
      PA3, //Pino que gera o pulso
      'c', //Cátodo (c) ou ânodo (a) comum
      8, //Quantidade total de dígitos incluindo casas decimais 
      2); //Quantidade de casas decimais

    //Referencia a função que será executada quando chegar um pulso (gerado pelo PA3) no PA2  
    attachInterrupt(PA2, interrupt, RISING); 
}

//Executado toda vez que chega um pulso no pino PA2
void interrupt()
{
    //Mostrar o dígito no display
	sevenSegmentsK.interrupt();
}

void loop() 
{
    //Se tiver algo no Serial
    if (Serial.available()){ 
        //Faz a leitura
        String str = Serial.readStringUntil('\n');
        //Transforma String em double
        double d = atof(str.c_str());
        //Manda exibir no display o número
        sevenSegmentsK.print(d); 
    }
}