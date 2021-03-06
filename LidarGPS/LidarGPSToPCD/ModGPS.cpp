#include "ModGPS.h"


double ModGPS::getSpeed(){return speed;} 
double ModGPS::getHeading(){return heading;} 
double ModGPS::getNorthing(){return northing;}  
double ModGPS::getEasting(){return easting;} 
int ModGPS::getUTC(){return utc;} 
double ModGPS::getAltitude(){return altitude;}
void ModGPS::setTime(double timeIN){genericTime = timeIN;}
	
void ModGPS::setSpeed(double speedIN){speed = speedIN;}
void ModGPS::setHeading(double headingIN)
{
	while(headingIN < 0)
	{
		headingIN += 360;
	}
	while(headingIN > 360)
	{
		headingIN -= 360;
	}
	
	heading =headingIN;
}
void ModGPS::setNorthing(double northingIN){northing = northingIN;}
void ModGPS::setEasting(double eastingIN){easting = eastingIN;}
void ModGPS::setUTC(int utcIN){utc=utcIN;}
void ModGPS::setAltitude(double altitudeIN){altitude=altitudeIN;}


void ModGPS::readGpsString(string gps)
{
	MergeTime time;
	GGA gga;
	RMC rmc;
	string rmcString, ggaString;
	if(gps.find("$GPGGA") == string::npos || gps.find("$GPRMC") == string::npos)
	{
		throw "GPS: Corrupted String - GGA or RMC not found";
	}
	time.setStamp(gps.substr(0,gps.find("$")));
	gps = gps.substr(gps.find("$"));
	ggaString = gps.substr(0,gps.find("$GPRMC"));
	rmcString = gps.substr(gps.find("$GPRMC"));
	
	gga.setString(ggaString);
	rmc.setString(rmcString);

	setSpeed(rmc.getSpeed());
	setHeading(rmc.getHeading());
	setNorthing(gga.getNorthing());
	setEasting(gga.getEasting());
	setUTC(gga.getUTC());
	setAltitude(gga.getHeight());
	setTime(time.getTime());
	
}


string ModGPS::toString()
{
	string string ="";
	string +="utc: "+to_string(utc)+"\n";
	string +="Northing: "+to_string(northing)+"\n";
	string +="Easting: "+to_string(easting)+"\n";
	string +="Heading: "+to_string(heading)+"\n";
	string +="Speed: "+to_string(speed)+"\n";
	return string;
}

double ModGPS::getTime(){return genericTime;}
