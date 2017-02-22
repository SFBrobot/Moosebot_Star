typedef struct {
	int target,
		val,
		valLast,
		err,
		mtrPwr;
	float prop,
		integ,
		integLim,
		deriv,
		kP,
		kI,
		kD;
} Pid;

void initPid(Pid* pid, float integLim, float kP, float kI, float kD) {
	pid->val =
		pid->valLast =
		pid->integ =
		pid->mtrPwr =
		0;
	pid->integLim = integLim;
	pid->kP = kP;
	pid->kI = kI;
	pid->kD = kD;
}

int setPidTarg(Pid* pid, int targ) {
	pid->target = targ;
	pid->integ = 0;
	return pid->target;
}

int upPid(Pid* pid, int val, int dt) {
	pid->val = val;
	pid->err = pid->target - pid->val; //Calculate error
	pid->prop = pid->err * pid->kP;  //Calculate proportional
	pid->integ += (pid->err * pid->kI) * dt; //Calculate integral
	if(fabs(pid->integ) > pid->integLim) //Collar integral
		pid->integ = pid->integLim * sgn(pid->integ);
	pid->deriv = pid->kD * (pid->val - pid->valLast) / dt; //Calculate derivative
	pid->mtrPwr = round(pid->prop + pid->integ + pid->deriv); //Calculate motor power
	return pid->mtrPwr;
}

int getPidPwr(Pid* pid) {
	return pid->mtrPwr;
}
