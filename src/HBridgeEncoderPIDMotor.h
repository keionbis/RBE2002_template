/*
 * HBridgeEncoderPIDMotor.h
 *
 *  Created on: Oct 17, 2018
 *      Author: hephaestus
 */

#ifndef SRC_HBRIDGEENCODERPIDMOTOR_H_
#define SRC_HBRIDGEENCODERPIDMOTOR_H_
#include "PIDMotor.h"
#include <ESP32Servo.h>
#include <ESP32Encoder.h>
class HBridgeEncoderPIDMotor : public PIDMotor{
private:
	ESP32Encoder encoder;
	ESP32PWM motor;
	int directionPin;
public:
	HBridgeEncoderPIDMotor();
	virtual ~HBridgeEncoderPIDMotor();
	void attach(int pwmPin,int directionPin,int encoderA, int encoderB);
	int64_t getPosition();
	 int64_t getOutputMin();
	 int64_t getOutputMax();
	 void setOutput(int64_t out);
	 void overrideCurrentPositionHardware(int64_t val);

};

#endif /* SRC_HBRIDGEENCODERPIDMOTOR_H_ */
