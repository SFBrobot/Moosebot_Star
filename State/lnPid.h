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
