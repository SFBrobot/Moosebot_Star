

void deployClaw() {
	setLift(127);
	wait1Msec(400);
	setLift(0);
	wait1Msec(20);
	setLift(-127);
	wait1Msec(250);
	setLift(0);
}

void redCubeAuton() {
	deployClaw();
	wait1Msec(250);
}
