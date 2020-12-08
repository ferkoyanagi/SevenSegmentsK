#include <Arduino.h>
#include "SevenSegmentsK.h"

SevenSegmentsK::SevenSegmentsK()
{
}

/**
 * segmentPins: array com os pinos que controlam os 7 segmentos e o ponto decimal
 * digitPins: array com os pinos que controlam qual o digito está ativo no momento
 * pwmPin: pino onde será gerado o pulso para a interrupção
 * type: tipo do display, 'c' para catodo comum e 'a' para anodo comum
 * digitsCount: quantidade total de digitos usados (contando os decimais)
 * decimalsCount: quantidade de casas decimais usadas
 */
void SevenSegmentsK::set(int segmentPins[8], int* digitPins, int pwmPin, char type, int digitsCount, int decimalsCount) 
{
	this->digitsCount = digitsCount;
	this->decimalsCount = decimalsCount;

	//Coloca todos os pinos que controlam os seguimentos como output
	for(int i=0; i<8; i++)
	{
		this->segmentPins[i] = segmentPins[i];
		pinMode(this->segmentPins[i], OUTPUT);
	}

	//Aloca memória para a quantidade de pinos suficientes
	this->digitPins = (int*) malloc(sizeof(int) * this->digitsCount);

	//Aloca memória suficiente para todos os digitos
	this->digits = (byte*) malloc(digitsCount);

	//Inicializa os digitos como 0 e coloca os pinos que controlam a posição do digito atual como output
	for(int i=0; i<this->digitsCount; i++)
	{
		this->digits[i] = 0;
		this->digitPins[i] = digitPins[i];
		pinMode(this->digitPins[i], OUTPUT);
	}
	
	//Se o tipo do display for catodo comum
	if (type == 'c')
	{
		this->state = HIGH;
	}
	//Se o tipo de display for anodo comum
	else if (type == 'a')
	{
		this->state = LOW;
	}

	//Gera o pulso que irá gerar a interrupção
	pinMode(pwmPin, OUTPUT);
	analogWrite(pwmPin, 127);
}

/**
 * Exibe o número no display
 * value: o valor que será exibido
 */
void SevenSegmentsK::print(double value)
{
	//Transforma o número em inteiro multiplicando a potência de 10 à quantidade de casas decimais
	int v = value * pow(10, this->decimalsCount);

	//Começa pelo número menos significativo (mais à direita)
	int digitIndex = this->digitsCount - 1;

	//Para todos os digitos
	while (digitIndex >= 0)
	{
		//Pega apenas o primeiro digito à direita
		this->digits[digitIndex] = v % 10;
		//Remove o digito da direita
		v /= 10;
		//Parte para o próximo digito à esquerda
		digitIndex--;
	}
}
//Função que deve ser chamada a cada interrupção
void SevenSegmentsK::interrupt()
{
	//Desliga o dígito anterior
	digitalWrite(this->digitPins[this->currentDigitIndex], !state);
	//Vai para o próximo dígito
	this->currentDigitIndex++;

	//Se estourou a quantidade de dígitos
	if(this->currentDigitIndex == this->digitsCount)
	{
		//Volta para o primeiro dígito
		this->currentDigitIndex = 0;
	}

	//Dígito atual que será exibido
	int currentDigit = this->digits[this->currentDigitIndex];

	//Apaga os segmentos
	for(int i=0; i<8; i++)
	{
		digitalWrite(this->segmentPins[i], !state);
	}
	
	//Verifica qual o dígito e acende os segmentos correspondentes
	switch(currentDigit)
	{
		case 0:
			digitalWrite(this->segmentPins[0], state);
			digitalWrite(this->segmentPins[1], state);
			digitalWrite(this->segmentPins[2], state);
			digitalWrite(this->segmentPins[3], state);
			digitalWrite(this->segmentPins[4], state);
			digitalWrite(this->segmentPins[5], state);
			digitalWrite(this->segmentPins[6], !state);
			break;
		case 1:	
			digitalWrite(this->segmentPins[0], !state);
			digitalWrite(this->segmentPins[1], state);
			digitalWrite(this->segmentPins[2], state);
			digitalWrite(this->segmentPins[3], !state);
			digitalWrite(this->segmentPins[4], !state);
			digitalWrite(this->segmentPins[5], !state);
			digitalWrite(this->segmentPins[6], !state);
			break;
		case 2:
			digitalWrite(this->segmentPins[0], state);
			digitalWrite(this->segmentPins[1], state);
			digitalWrite(this->segmentPins[2], !state);
			digitalWrite(this->segmentPins[3], state);
			digitalWrite(this->segmentPins[4], state);
			digitalWrite(this->segmentPins[5], !state);
			digitalWrite(this->segmentPins[6], state);
			break;
		case 3:
			digitalWrite(this->segmentPins[0], state);
			digitalWrite(this->segmentPins[1], state);
			digitalWrite(this->segmentPins[2], state);
			digitalWrite(this->segmentPins[3], state);
			digitalWrite(this->segmentPins[4], !state);
			digitalWrite(this->segmentPins[5], !state);
			digitalWrite(this->segmentPins[6], state);
			break;
		case 4:
			digitalWrite(this->segmentPins[0], !state);
			digitalWrite(this->segmentPins[1], state);
			digitalWrite(this->segmentPins[2], state);
			digitalWrite(this->segmentPins[3], !state);
			digitalWrite(this->segmentPins[4], !state);
			digitalWrite(this->segmentPins[5], state);
			digitalWrite(this->segmentPins[6], state);
			break;
		case 5:
			digitalWrite(this->segmentPins[0], state);
			digitalWrite(this->segmentPins[1], !state);
			digitalWrite(this->segmentPins[2], state);
			digitalWrite(this->segmentPins[3], state);
			digitalWrite(this->segmentPins[4], !state);
			digitalWrite(this->segmentPins[5], state);
			digitalWrite(this->segmentPins[6], state);
			break;
		case 6:
			digitalWrite(this->segmentPins[0], state);
			digitalWrite(this->segmentPins[1], !state);
			digitalWrite(this->segmentPins[2], state);
			digitalWrite(this->segmentPins[3], state);
			digitalWrite(this->segmentPins[4], state);
			digitalWrite(this->segmentPins[5], state);
			digitalWrite(this->segmentPins[6], state);
			break;
		case 7:
			digitalWrite(this->segmentPins[0], state);
			digitalWrite(this->segmentPins[1], state);
			digitalWrite(this->segmentPins[2], state);
			digitalWrite(this->segmentPins[3], !state);
			digitalWrite(this->segmentPins[4], !state);
			digitalWrite(this->segmentPins[5], !state);
			digitalWrite(this->segmentPins[6], !state);
			break;
		case 8:
			digitalWrite(this->segmentPins[0], state);
			digitalWrite(this->segmentPins[1], state);
			digitalWrite(this->segmentPins[2], state);
			digitalWrite(this->segmentPins[3], state);
			digitalWrite(this->segmentPins[4], state);
			digitalWrite(this->segmentPins[5], state);
			digitalWrite(this->segmentPins[6], state);
			break;
		case 9:
			digitalWrite(this->segmentPins[0], state);
			digitalWrite(this->segmentPins[1], state);
			digitalWrite(this->segmentPins[2], state);
			digitalWrite(this->segmentPins[3], state);
			digitalWrite(this->segmentPins[4], !state);
			digitalWrite(this->segmentPins[5], state);
			digitalWrite(this->segmentPins[6], state);
			break;
	}

	//Verifica se precisa colocar o ponto decimal e coloca no lugar correspondente
	if(this->decimalsCount != 0 && this->currentDigitIndex == this->digitsCount - this->decimalsCount - 1)
	{
		digitalWrite(this->segmentPins[7], state);
	}

	//Liga o dígito atual
	digitalWrite(this->digitPins[this->currentDigitIndex], state);
}