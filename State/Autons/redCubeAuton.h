void redCubeAuton() {
	deployClaw();
	driveForDist(400, 400);
	driveForDist(800, 0);
	driveForDist(1200, 800);
	setClaw(true); //Grab cube
	wait1Msec(100);
	setPid(&LiftPid, 500); //Reduce resistance by lifting cube off ground
	driveLiftForDist(1600, 400);
	driveForDist(1200, 0);
	throw(); //Lift arm and open claw to throw cube to far zone
	setLift(-63);
	wait1Msec(250);
	setLift(0);
	driveForDist(1800, 600);
	setClaw(true);
	wait1Msec(100);
	driveForDist(1200, 0);
	throw(); //Raise lift and open claw to throw stars
	driveClaw(0);
	driveForTime(127, 500);
}
