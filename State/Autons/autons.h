
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

void throw(int timeout = 1000) {
	int timeStart = nSysTime;
	setLift(127);
	do {
		wait1Msec(20);
	} while((nSysTime - timeStart < timeout) || (SensorValue[liftEnc] < 1500));
	setClaw(-127);
	wait1Msec(100);
	setLift(0);
	setClaw(0);
	wait1Msec(20);
	setLift(-127);
	wait1Msec(500);
	setLift(0);
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

int movePidBy(Pid* pid, int deltaTarg) {
	pid->target += deltaTarg;
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

int autonTargs[2][5] = { { 1200, 1800, -800, 1200, -1200 },
		{ 1200, -1800, -800, 1200, -1200 } };

bool flipSide[5] = { false, true, false, false, false };

void leftAuton() {

	int clawPotLast;

	deployClaw();
	for(int i = 0; i < sizeof(autonTargs) / (2 * sizeof(int)); i++) {
		movePidBy(&DrivePidL, autonTargs[0][i]);
		movePidBy(&DrivePidR, autonTargs[1][i]);
		while(!DrivePidL.bIsOnTarg || !DrivePidR.bIsOnTarg) {
			upPid(&DrivePidL, SensorValue[lDriveEnc]);
			upPid(&DrivePidR, SensorValue[rDriveEnc]);
			wait1Msec(20);
		}
		if(i == 0 || i == 4) {
			setClaw(127);
			do {
				clawPotLast = SensorValue[clawPot];
				wait1Msec(20);
			} while(fabs(SensorValue[clawPot] - clawPotLast) > 25);
			setClaw(0);
			setLift(31);
		}
		else if(i == 2 || i == 5)
			throw();
	}
}

void rightAuton() {

	int clawPotLast;

	deployClaw();
	for(int i = 0; i < sizeof(autonTargs) / (2 * sizeof(int)); i++) {
		if(flipSide[i]) {
			movePidBy(&DrivePidL, -autonTargs[0][i]);
			movePidBy(&DrivePidR, -autonTargs[1][i]);
		}

		else {
			movePidBy(&DrivePidL, autonTargs[0][i]);
			movePidBy(&DrivePidR, autonTargs[1][i]);
		}

		while(!DrivePidL.bIsOnTarg || !DrivePidR.bIsOnTarg) {
			upPid(&DrivePidL, SensorValue[lDriveEnc]);
			upPid(&DrivePidR, SensorValue[rDriveEnc]);
			wait1Msec(20);
		}
		if(i == 0 || i == 4) {
			setClaw(127);
			do {
				clawPotLast = SensorValue[clawPot];
				wait1Msec(20);
			} while(fabs(SensorValue[clawPot] - clawPotLast) > 25);
			setClaw(0);
			setLift(31);
		}
		else if(i == 2 || i == 5)
			throw();
	}
}
