void turn90(char direction)
{
	if (direction  == 'L')
	{
		motor[motorA] = -50;
		motor[motorC] = 50;
		while(getGyroDegrees(S4) > (90))
		{}
		motor[motorA] = motor[motorC] = 0;
		wait1Msec(1000);
	}

	else
	{
		motor[motorA] = 50;
		motor[motorC] = -50;
		while(getGyroDegrees(S4) > (-90))
		{}
		motor[motorA] = motor[motorC] = 0;
		wait1Msec(1000);
	}
}

void drivedist(int distance)
{
	const int ENC_LIMIT = distance * 180 / (2.75 * PI);
	nMotorEncoder[motorA] = 0;
	motor[motorA] = motor[motorC] = 50;
	while (nMotorEncoder[motorA] < ENC_LIMIT)
	{}
	motor[motorA] = motor[motorC] = 0;
}



task main()
{
	SensorType[S1] = sensorEV3_Touch;
	SensorType[S4] = sensorEV3_Gyro;
	wait1Msec(50);
	SensorMode[S4] = modeEV3Gyro_Calibration;
	wait1Msec(50);
	SensorMode[S4] = modeEV3Gyro_RateAndAngle;
	wait1Msec(50);

	//Drive forward
	motor[motorA] = motor[motorC] = 50;

	if(SensorValue(S1) == 1)
	{
		motor[motorA] = motor[motorC] = 0;
		wait1MSec(1500);

	//Turn left, drive forward, turn right, drive forward
		turn90('L');
		drivedist(25);
		turn90('R');
		drivedist(50);
		turn90('R');
		drivedist(25);
		turn90('L');
	}

}
