
#ifndef LN_UTILS
#define LN_UTILS

#define setDriveR(pwr) motor[frWheel] = \
	motor[brWheel] = \
	pwr

#define setDriveL(pwr) motor[flWheel] = \
	motor[blWheel] = \
	pwr

#define setLift(pwr) motor[lLift1] = \
	motor[lLift2] = \
	motor[rLift1] = \
	motor[rLift2] = \
	pwr


#define setClaw(pwr) motor[lClaw] = \
	motor[rClaw] = \
	pwr

void setDrive(int lPwr, int rPwr) {
	setDriveL(lPwr);
	setDriveR(rPwr);
	return;
}

#endif

void deployClaw() {
	setLift(127);
	wait1Msec(400);
	setLift(0);
	wait1Msec(20);
	setLift(-127);
	wait1Msec(250);
	setLift(0);
}

void throw() {
	setLift(127);
	while(SensorValue[liftEnc] < 2500)
		wait1Msec(20);
	setClaw(false);
	wait1Msec(50);
	setLift(0);
}

typedef struct {
	int target,
		val,
		valLast,
		err,
		mtrPwr,
		time,
		timeLast,
		dt,
		thresh;
	float prop,
		integ,
		integLim,
		deriv,
		kP,
		kI,
		kD;
	bool bIsOnTarg;
} Pid;

void initPid(Pid* pid, int thresh, float integLim, float kP, float kI, float kD) {
	pid->val =
		pid->valLast =
		pid->integ =
		pid->mtrPwr =
		0;
	pid->thresh = thresh;
	pid->bIsOnTarg = false;
	pid->integLim = integLim;
	pid->kP = kP;
	pid->kI = kI;
	pid->kD = kD;
}

int setPid(Pid* pid, int targ) {
	pid->target = targ;
	pid->integ = 0;
	return pid->target;
}

int upPid(Pid* pid, int val) {
	pid->timeLast = pid->time;
	pid->time = nSysTime;
	pid->dt = pid->time - pid->timeLast;
	pid->val = val;
	pid->err = pid->target - pid->val; //Calculate error
	if(fabs(pid->err) < pid->thresh) {
		pid->bIsOnTarg = true;
		pid->mtrPwr = 0;
	}
	else {
		pid->bIsOnTarg = false;
		pid->prop = pid->err * pid->kP;  //Calculate proportional
		pid->integ += (pid->err * pid->kI) * pid->dt; //Calculate integral
		if(fabs(pid->integ) > pid->integLim) //Collar integral
		pid->integ = pid->integLim * sgn(pid->integ);
		pid->deriv = pid->kD * (pid->val - pid->valLast) / pid->dt; //Calculate derivative
		pid->mtrPwr = round(pid->prop + pid->integ + pid->deriv); //Calculate motor power
	}
	return pid->mtrPwr;
}

int getPidPwr(Pid* pid) {
	return pid->mtrPwr;
}

Toggle LiftTog;

Pid LiftPid,
	DrivePidL,
	DrivePidR;

void redCubeAuton() {
	deployClaw();
	setPid(&DrivePidL, 400); //Advance left drive to middle tape line
	setPid(&DrivePidR, 400); //Advance right drive to middle tape line
	while(!(DrivePidL.bIsOnTarg && DrivePidR.bIsOnTarg)) {
		setDriveL(upPid(&DrivePidL, SensorValue[lDriveEnc]));
		setDriveR(upPid(&DrivePidR, SensorValue[rDriveEnc]));
		wait1Msec(20);
	}
	setPid(&DrivePidL, 800); //Advance left drive to turn right
	setPid(&DrivePidR, 0); //Reverse right drive to turn right
	while(!(DrivePidL.bIsOnTarg && DrivePidR.bIsOnTarg)) {
		setDriveL(upPid(&DrivePidL, SensorValue[lDriveEnc]));
		setDriveR(upPid(&DrivePidR, SensorValue[rDriveEnc]));
		wait1Msec(20);
	}
	setPid(&DrivePidL, 1200); //Advance left drive side to cube
	setPid(&DrivePidR, 800); //Advance right side to cube
	while(!(DrivePidL.bIsOnTarg && DrivePidR.bIsOnTarg)) {
		setDriveL(upPid(&DrivePidL, SensorValue[lDriveEnc]));
		setDriveR(upPid(&DrivePidR, SensorValue[rDriveEnc]));
		wait1Msec(20);
	}
	setClaw(true); //Grab cube
	wait1Msec(50);
	setPid(&LiftPid, 500); //Reduce resistance by lifting cube off ground
	setPid(&DrivePidL, 1600); //Advance left drive to turn right (facing away from fence)
	setPid(&DrivePidR, 400); //Reverse right drive to turn right
	while(!(DrivePidL.bIsOnTarg && DrivePidR.bIsOnTarg)) {
		setLift(upPid(&LiftPid, SensorValue[liftEnc]));
		setDriveL(upPid(&DrivePidL, SensorValue[lDriveEnc]));
		setDriveR(upPid(&DrivePidR, SensorValue[rDriveEnc]));
		wait1Msec(20);
	}
	setPid(&DrivePidL, 1200); //Reverse left drive to back up to fence
	setPid(&DrivePidR, 0); //Reverse right side to back up to fence
	while(!(DrivePidL.bIsOnTarg && DrivePidR.bIsOnTarg)) {
		setDriveL(upPid(&DrivePidL, SensorValue[lDriveEnc]));
		setDriveR(upPid(&DrivePidR, SensorValue[rDriveEnc]));
		wait1Msec(20);
	}
	throw(); //Lift arm and open claw to throw cube to far zone
	setPid(&LiftPid, 0); //Lower lift
	while(!LiftPid.bIsOnTarg) { //Wait until lift is down
		setLift(upPid(&LiftPid, SensorValue[liftEnc]));
		wait1Msec(20);
	}
	setPid(&DrivePidL, 1800); //Advance left drive to drive to back stars
	setPid(&DrivePidR, 600); //Advance right side to drive to back stars
	while(!(DrivePidL.bIsOnTarg && DrivePidR.bIsOnTarg)) {
		setDriveL(upPid(&DrivePidL, SensorValue[lDriveEnc]));
		setDriveR(upPid(&DrivePidR, SensorValue[rDriveEnc]));
		wait1Msec(20);
	}
	setClaw(true);
	wait1Msec(50);
	setPid(&DrivePidL, 1200); //Back up to fence (left)
	setPid(&DrivePidR, 0); //back up to fence (right)
	while(!(DrivePidL.bIsOnTarg && DrivePidR.bIsOnTarg)) {
		setDriveL(upPid(&DrivePidL, SensorValue[lDriveEnc]));
		setDriveR(upPid(&DrivePidR, SensorValue[rDriveEnc]));
		wait1Msec(20);
	}
	throw(); //Raise lift and open claw to throw stars
	setPid(&LiftPid, 0); //Lower lift
	while(!LiftPid.bIsOnTarg) { //Wait until lift is down
		setLift(upPid(&LiftPid, SensorValue[liftEnc]));
		wait1Msec(20);
	}
	setDriveL(127);
	setDriveR(127);
	wait1Msec(500);
	setDriveL(0);
	setDriveR(0);
}
