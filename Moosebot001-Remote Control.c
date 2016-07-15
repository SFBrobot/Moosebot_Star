#define frWheel port2
#define brWheel port3
#define blWheel port4
#define flWheel port5
#define blLift port6
#define tlLift port7
#define trLift port8
#define brLift port9

void holoSteer(int fb, int strafe, int rot) { //fb = forward/back motion
	motor[flWheel] = fb + strafe + rot;
	motor[blWheel] = fb - strafe + rot;
	motor[brWheel] = -(fb + strafe - rot);
	motor[frWheel] = -(fb - strafe - rot);
}

int liftCtl(int pwr) {
	motor[tlLift] =
		motor[brLift] =
		pwr;
	motor[trLift] =
		motor[blLift] =
		-pwr;
	return pwr;
}

int liftPwr() {
	if(vexRT[Btn5U] ^ vexRT[Btn5D] ^ vexRT[Btn6U] ^ vexRT[Btn6D]) {
		if(vexRT[Btn5U])
			return 63;
		else if(vexRT[Btn5D])
			return -63;
		else if(vexRT[Btn6U]
			return 127;
		else
			return -127;
	}

	else
		return 0;
}

task main() {
	int rx,
		ly,
		lx;

	while(true) {
		rx = (abs(vexRT[Ch1]) >= 7) ? vexRT[Ch1] : 0;
		ly = (abs(vexRT[Ch3]) >= 7) ? vexRT[Ch3] : 0;
		lx = (abs(vexRT[Ch4]) >= 7) ? vexRT[Ch4] : 0;

		holoSteer(ly, lx, rx);

		liftCtl(liftPwr());
	}
}
