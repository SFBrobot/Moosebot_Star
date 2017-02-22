#define setDriveR(pwr) motor[frWheel] = \
	motor[brWheel] = \
	pwr

#define setDriveL(pwr) motor[flWheel] = \
	motor[blWheel] = \
	pwr

#define setLift(pwr) motor[tlLift] = \
	motor[mlLift] = \
	motor[blLift] = \
	motor[trLift] = \
	motor[mrLift] = \
	motor[brLift] = \
	pwr


#define setClaw(pwr) SensorValue[lClawPn] = \
	SensorValue[rClawPn] = \
	pwr

void setDrive(int lPwr, int rPwr) {
	setDriveL(lPwr);
	setDriveR(rPwr);
	return;
}
