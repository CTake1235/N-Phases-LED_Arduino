#include <Arduino.h>
#include <math.h>

int sin_bias(double);
const int angle_diff 	= 6;
const int phases 		= 5;
const int pins[phases]	= {9,10,11,3,5};
int i=0;
double angle[phases] = {};
int cyclecounter[phases] = {};

void setup() {
	Serial.begin(9600);
	pinMode(3, OUTPUT);

	for(int j=0; j<phases; j++){
		angle[j] = {2*j*PI/phases};
		cyclecounter[j] = {angle_diff*2*j/phases};
	}
}

void loop() {
	// digitalWrite(3, HIGH);

	analogWrite(pins[i], sin_bias(angle[i]));
	Serial.println(angle[i]);

	if(cyclecounter[i] >= 2*angle_diff){
		angle[i] = 0.0;
		cyclecounter[i] = 0;
	}else{		
		angle[i] += PI/angle_diff;
		cyclecounter[i]++;
	}
	


	if(++i >= phases){
		Serial.println("=========\n");
		i=0;
	}

	delay(10);
}

int sin_bias(double angle_in_rad){
	return 255 * (sin(angle_in_rad) + 1.0) * 0.5;
}