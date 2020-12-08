#ifndef _SevenSegmentsK_H_
#define _SevenSegmentsK_H_
#include <Arduino.h>;

class SevenSegmentsK
{
		public:
			SevenSegmentsK();
			void set(int segmentPins[8], int* digitPins, int pwmPin, char type, int digitsCount, int decimalsCount);
			void print(double value);
			void interrupt();
		private:
			int digitsCount = 0;
			int state = LOW;
			int segmentPins[8];
			int* digitPins;
			byte* digits;
			int currentDigitIndex = 0;
			int decimalsCount = 0;
};
#endif