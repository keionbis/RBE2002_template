/*
 * PIDMotor.h
 *
 *  Created on: Oct 16, 2018
 *      Author: hephaestus
 */

#ifndef SRC_PIDMOTOR_H_
#define SRC_PIDMOTOR_H_
#include <PID_v1.h>
#include <stdint.h>
#define PID_OUTPUT_COMPUTE_RANGE 900
class PIDMotor {
protected:
	PID myPID;
	float Kp=2, Ki=0, Kd=0;
	double Setpoint=0, Input=0, Output=0;
	bool lastErrPositive=false;
public:
	PIDMotor();
	virtual ~PIDMotor();
	void loop();
	void overrideCurrentPosition(int64_t val);
	void setSetpoint(int64_t val);
	void SetTunings(double Kp, double Ki, double Kd);
	void pidinit();
	virtual int64_t getPosition()=0;
	virtual int64_t getOutputMin()=0;
	virtual int64_t getOutputMax()=0;
	virtual void setOutput(int64_t out)=0;
	virtual void overrideCurrentPositionHardware(int64_t val)=0;

};

#endif /* SRC_PIDMOTOR_H_ */