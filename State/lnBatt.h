task battLvls() {
	float battLvls[3] = { 0, 0, 0 };
	string battString[2];
	string* pBattString[2];

	for(int i = 0; i < 2; i++)
		pBattString[i] = &battString[i];

	for(int i = 0; i < 3; i++)
		battLvls[i] = 0;

	while(true) {

		for(int i = 0; i < 3; i++)
			battLvls[i] = 0;

		for(int i = 0; i < 10; i++) {
			battLvls[0] += nImmediateBatteryLevel / 10000.;
			battLvls[1] += SensorValue[in1] / 456.;
			battLvls[2] += BackupBatteryLevel / 10000.;
			wait1Msec(20);
		}

		sprintf(*pBattString[0], "%2.2fV || %2.2fV", battLvls[0], battLvls[1]);
		sprintf(*pBattString[1], "%2.2fV", battLvls[2]);

		displayLCDCenteredString(0, *pBattString[0]);
		displayLCDCenteredString(1, *pBattString[1]);

		wait1Msec(20);

	}
}
