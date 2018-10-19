#include <PID_v1.h>
#include <ESP32Servo.h>
#include <ESP32Encoder.h>
#include "src/PIDMotor.h"
#include "src/ServoEncoderPIDMotor.h"
#include "src/HBridgeEncoderPIDMotor.h"
#include <WiiChuck.h>
#include "src/GearWrist.h"
Accessory control;
HBridgeEncoderPIDMotor motor1;
HBridgeEncoderPIDMotor motor2;
GearWrist * wristPtr;
Servo jaw;
Servo panEyes;
Servo tiltEyes;
ESP32PWM dummy;
long lastPrint=0;
void setup(){
	Serial.begin(115200);

	motor1.attach(2,15, 36, 39);
	motor2.attach(16,4, 34, 35);
	Serial.println("Starting Motors: 1");
	control.begin();
	wristPtr=new GearWrist(&motor1,
			&motor2,
			16.0*// Encoder CPR
			50.0* // Gear box ratio
			2.5347* // Wrist gear stage ratio
			(1.0/360.0)* // degrees per revolution
			4.0,   // full quadrature, 4 ticks be encoder count
			0.8932); // ratio of second stage to first stage
	jaw.attach(19,1000,2000);
	jaw.setPeriodHertz(330);
	panEyes.setPeriodHertz(330);
	panEyes.attach(18,1000,2000);
	tiltEyes.setPeriodHertz(330);
	tiltEyes.attach(5,1000,2000);

}
float mapf(float x, float in_min, float in_max, float out_min, float out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
void loop(){
	wristPtr->loop();
	if(millis()-lastPrint>20){
		lastPrint=millis();
		control.readData();    // Read inputs and update maps
		float Servo1Val = mapf((float)control.values[1],0.0,255.0,-10.0,10.0);
		float Servo3Val = mapf((float)control.values[0],0.0,255.0,-60.0,60.0);// z button
		int panVal = map(control.values[2],0,255,35,148);
		int jawVal = map( control.values[5]>0?
							 0:// Upper button pressed
							 (control.values[18]>0?
								255:// Lower button pressed
								128)//neither pressed
							,0,255,80,160);
		int tiltVal = map(control.values[3],0,255,24,120);// z button
		panEyes.write(panVal);
		tiltEyes.write(tiltVal);
		jaw.write(jawVal);

		wristPtr->setTarget(Servo1Val, Servo3Val);
		//Serial.println(" Pan  = " +String(panVal)+" tilt = " +String(tiltVal));
		//Serial.println(" Angle of A = " +String(wristPtr->getA())+" Angle of B = " +String(wristPtr->getB()));

//		for (int i = 0; i < WII_VALUES_ARRAY_SIZE; i++) {
//			Serial.println(
//					"\tVal " + String(i) + " = "
//							+ String((uint8_t) control.values[i]));
//		}
	}
}