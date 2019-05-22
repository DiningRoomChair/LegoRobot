//Definitions for note frequencies and durations
//FIFTH OCTAVE NOTE FREQUENCIES
#define    C5  523    //    C    note frequency
#define    Cs5 554    //    C    sharp note frequency
#define    D5  587    //    D    note frequency
#define    Ds5 622    //    D    sharp note frequency
#define    E5  659    //    E    note frequency
#define    F5  698    //    F    note frequency
#define    Fs5 740    //    F    sharp note frequency
#define    G5  784    //    G    note frequency
#define    Gs5 831    //    G    sharp note frequency
#define    A5  880    //    A    note frequency
#define    As5 932    //    A    sharp note frequency
#define    B5  988    //    B    note frequency
//SIXTH OCTAVE NOTE FREQUENCIES
#define    C6  1046    //    note frequency
#define    Cs6 1109    //    sharp note frequency
#define    D6  1175    //    note frequency
#define    Ds6 1245    //    sharp note frequency
#define    E6  1319    //    note frequency
#define    F6  1397    //    note frequency
#define    Fs6 1480    //    sharp note frequency
#define    G6  1568    //    note frequency
#define    Gs6 1661    //    sharp note frequency
#define    A6  1760    //    note frequency
#define    As6 1865    //    sharp note frequency
#define    B6  1976    //    note frequency
//SEVENTH OCTAVE NOTE FREQUENCIES
#define    C7  2093    //    note frequency
#define    Cs7 2217    //    sharp note frequency
#define    D7  2349    //    note frequency
#define    Ds7 2489    //    sharp note frequency
#define    E7  2637    //    note frequency
#define    F7  2794    //    note frequency
#define    Fs7 2960    //    sharp note frequency
#define    G7  3136    //    note frequency
#define    Gs7 3322    //    sharp note frequency
#define    A7  3520    //    note frequency
#define    As7 3729    //    sharp note frequency
#define    B7  3951    //    note frequency

#define    P        0 //note frequency (a rest note)

//NOTE DURATION FACTORS (THEY MULTIPLY THE WHOLE NOTE DURATION)
#define    N1   1.0     //whole note
#define    N2   0.5     //half note
#define    N2h  0.75    //dotted half note
#define    N4   0.25    //quarter note
#define    N4h  0.375   //dotted quarter note
#define    N8   0.125   //eighth note
#define    N8h  0.1875  //dotted eighth note
#define    N16  0.0625  //sixteenth note
#define    N16h     0.09375 //dotted    sixteenth note
#define    N32     0.03125     //thirty-secondth note
#define    N32h     0.046875 //dotted thirty-secondth note

//Arrays for notes and durations
//for the pokemon battle theme.
int notesF[] = {
    G6, Fs6, F6, E6, G6, Fs6, F6, E6, G6,
    Fs6, F6, E6, G6, Fs6, F6, E6, G6, Fs6,
    F6, E6, G6, Fs6, F6, E6, G6, Fs6, F6,
    E6, G6, Fs6, F6, E6, G5, P, G5, P,
    G5, G5, G5, P, G5, Fs5, G5, P, G5,
    P, G5, G5, G5, P, G5, Fs5, G5, Fs5,
    E5, G5, A5, G5, Gs5, G5, Gs5, G5, Cs6,
    0
};
float notesD[] = {
    N16, N16, N16, N16, N16, N16, N16, N16, N16,
    N16, N16, N16, N16, N16, N16, N16, N16, N16,
    N16, N16, N16, N16, N16, N16, N16, N16, N16,
    N16, N16, N16, N16, N16, N8h, N8h, N8h, N8h,
    N2h, N1, N8h, N8h, N2, N2, N8h, N8h, N8h,
    N8h, N2h, N1, N8h, N8h, N2, N2, N4h, N4h,
    N4, N4h, N4h, N4, N2h, N4, N8, N4h, N2,
    0
};
#define SIZE 60     //definitions for the size of and location
#define XC 20       //of the spiral display
#define YC 1
#define ROWSD 29
#define COLSD 46
#define LEFTD 25  //horizontal screen position at left edge of image
#define TOPD 40  //vertical screen position at top edge of image
#define ROWSDI 30
#define COLSDI 39
#define LEFTDI 30  //horizontal screen position at left edge of image
#define TOPDI 40  //vertical screen position at top edge of image
int bu;
task display();     //function declarations
task move();
void pokemon();
#define ROTATIONSCALE 205
#define INERTIAWAIT 65
#define SPEED 30
#define LIGHTTHRESH 55
void Drive(int speed);
void Backup(int speed, int duration);
void Rotate(int speed, int degrees);
void PathFind (int speed);
int GetBumps();
task main()
{
	int bump;
	
	//	nMotorPIDSpeedCtrl [motorA] = mtrNoReg;
	
	nMotorPIDSpeedCtrl[1] = mtrSpeedReg;
	nMotorPIDSpeedCtrl[2] = mtrSpeedReg;
	
	SensorType[0] = sensorTouch;
	SensorType[3] = sensorTouch;
	
	while(true)
	{   
		PathFind(SPEED);
		bump = GetBumps();
		
		if (bump==1)
		{
			bu = 1;
			Backup (20, 2);           
			pokemon();
			Rotate (40, -90);
			Drive (SPEED);
			
		}
		
		else if (bump==2)
		{
			bu = 2;
			motor[1] = 0;
			motor[2] = 0;
			Backup (20, 2);
			pokemon();
			Rotate (40, 90);
			Drive (SPEED);
			
		}
		
		else if (bump==3)
		{
			bu = 3;
			motor[1] = 0;
			motor[2] = 0;
			Backup (20, 2);
			pokemon();
			Rotate (40, 180);
			Drive (SPEED);
			
		}
	}
}

//GET BUMPS
int GetBumps()
{
	int rightbump;
	int leftbump;
	int bump_result;
	
	rightbump = SensorValue[0];
	leftbump = SensorValue[3];
	
	if(leftbump==0 && rightbump==0)
		bump_result = 0;
	else if(leftbump==1 && rightbump==0)
		bump_result = 1;
	else if(leftbump==0 && rightbump==1)
		bump_result = 2;
	else if(leftbump==1 && rightbump==1)
		bump_result = 3;
	return bump_result;
}

// ROTATE:
void Rotate(int speed, int degrees)
{ 
	
	int rot_msecs;
	float fval;
	
	fval = (float)(ROTATIONSCALE) * (abs(degrees)/speed);
	rot_msecs = fval;
	
	
	rot_msecs = rot_msecs + INERTIAWAIT;
	
	if(degrees>0)
	{
		motor[1] = speed;
		motor[2] = -speed;
		
		
	}
	else
	{
		motor[1] = -speed;
		motor[2] = speed;
		
	}
	
	wait1Msec(rot_msecs);
	
	motor[1] = 0;
	motor[2] = 0;
	wait1Msec(200);
}

// DRIVE:
void Drive(int speed)
{
	motor[1] = speed;
	motor[2] = speed;
	wait10Msec(50);
	
	motor[1] = 0;
	motor[2] = 0;
	
	
}

//BACKUP:
void Backup(int speed, int duration)
{
	
	int needed_loops;
	int i;
	
	motor[1] = -speed;
	motor[2] = -speed;
	
	needed_loops=6;
	
	
	for(i=1; i<=needed_loops; i++)
	{
		wait10Msec(20);
		motor[0] = 100;
		PlayTone(1100, 30);
		wait10Msec(duration);
		motor[0]=0;
		
	}
	
	motor[1] = 0;
	motor[2] = 0;
}

//PATHFIND
void PathFind (int speed)
{
	int level;    
	int darkstate;
	
	//define the light sensor type on port S2
	SensorType[1] = sensorLightActive;
	
	darkstate = 0;
	
	motor[1] = SPEED;
	motor[2] = -SPEED;
	
	
	level = SensorValue[1];
	if(level >= LIGHTTHRESH)
	{	nxtDisplayTextLine(4, "SEEKING DARK");
		darkstate = 0;
	}
	else
	{	nxtDisplayTextLine(4, "SEEKING LIGHT");
		darkstate = 1;
	}
	
	if(darkstate == 0)
	{   
		motor[1] = 0;
		motor[2] = SPEED;
	}
	if(darkstate==1)
	{
		motor[1] = SPEED;
		motor[2] = 0;
	}
	
	wait10Msec(20);
}

void pokemon()
{   
	int freq;      //declarations of necessary variables
	float dur;
	int beats;
	int tics;
	int i = 1;     //set to 1 to avoid error
	float duration;
	int wholenote, quarternote;
	
	beats = 180;                       //tempo of the song
	quarternote = 1000*(60/(float)beats); //note durations in
	wholenote = 4*quarternote;
	
	bPlaySounds = true;
	nVolume = 2;
	
	StartTask(display);
	StartTask(move);
	
	freq = notesF[i];
	
	do
	{
		freq = notesF[i]; //get first note frequency
		duration = notesD[i]; //get first note duration
		tics = (int)((wholenote * duration) / 10); //how many 10 msec tics
		PlayTone(freq, tics); //queue it
		wait10Msec(tics); //let it play
		i++;
	} while (duration > 0);
}

task display()
{       
	byte diglett[ROWSD][COLSD] =
                 {	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
					{1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
				};
	
	byte ditto[ROWSDI][COLSDI] =
               {    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,1,1,1,0,0,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                    {1,1,0,0,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                    {1,1,0,1,1,0,1,0,1,1,1,0,0,1,1,1,1,1,0,0,1,1,1,1,0,1,1,1,0,0,1,1,1,1,1,1,1,1,1},
                    {1,1,0,1,1,1,0,1,1,1,1,0,0,1,1,1,1,1,0,0,1,1,1,1,0,0,1,0,1,1,0,1,1,1,1,1,1,1,1},
                    {1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,0,1,1,1,1,1,1,1,1},
                    {1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1},
                    {1,1,1,1,1,1,0,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,1,1,1,1,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
                            };
	int h,i,j,k,l,m,a,b,c,d,x,y;   //for loop variables
	int end = SIZE;    // sets end for use in creating spiral motion
	int time = 18;
	m=0;
	
	eraseDisplay();
	
	for(i=end ; i>=0 ; i--)    //nested for loops to display an inward moving
	{	//spiral beginning at the top right.
		for(j=0 ; j<=end ; j++)   
			nxtSetPixel(j+XC, i+YC);
		wait1Msec(time);
		{
			for(k=end ; k>=0 ; k--)   
				nxtSetPixel(j+XC, k+YC);
			wait1Msec(time);
			{
				for(l=end ; l>=0 ; l--) 
					nxtSetPixel(l+XC, m+YC);
				wait1Msec(time);
				{
					for(h=0 ; h<=end ; h++) 
						nxtSetPixel(m+XC,h+YC);
					wait1Msec(time);
					
					m++;
					end--;   //makes the loop move inward each time
				}
			}
		}
	}
	
	wait10Msec(200);   //stay black for half a second
	eraseDisplay();    //clear screen
	
	if (bu == 1)
	{
		nxtDisplayTextLine(3, "   Wild Diglett");
		nxtDisplayTextLine(4, "     Appeared!");
		wait10Msec(200);
		eraseDisplay();
		wait10Msec(200);
		
		for(a=0; a<=ROWSDI-1; a++)
		{
			for(b=0; b<=COLSDI-1; b++)
			{
				x = LEFTD + b; //set x screen position according to the column value
				y = TOPD - a; //set y screen position according to the row value
				if(diglett[a][b] == 1)
					nxtClearPixel(x, y);
				else if(diglett[a][b] == 0)
					nxtSetPixel(x, y);               
			}
		}
		wait10Msec(600);  //delay end of program so we can image on the screen
		eraseDisplay();
	}
	else
	{
		nxtDisplayTextLine(3, "   Wild Ditto");
		nxtDisplayTextLine(4, "     Appeared!");
		wait10Msec(200);
		eraseDisplay();
		wait10Msec(200);
		
		for(c=0; c<=ROWSDI-1; c++)
		{
			for(d=0; d<=COLSDI-1; d++)
			{
				x = LEFTDI+d; //set x screen position according to the column value
				y = TOPDI-c; //set y screen position according to the row value
				if(ditto[c][d] == 1)
					nxtClearPixel(x, y);
				else if(ditto[c][d] == 0)
					nxtSetPixel(x, y);
				
			}
		}
		wait10Msec(600); //delay end of program so we can image on the screen
		eraseDisplay();
	}
}
task move()
{
	motor[1] = 70;
	motor[2] = -70;
	wait10Msec(300);
	motor[1] = 0;
	motor[2] = 0;
}
