#include "misc.h"
#include "time.h"

double sdt;
long sdt_millis;
//input deg ,output hour
double sidereal_timeGMT (double longitude, int tz)
{
  struct timeval now;
  double JD;
  double sidereal, tmp;
  double T;
  gettimeofday(&now, NULL);
  JD = ((now.tv_sec + now.tv_usec / 1000000.0)) / 86400.0 + 2440587.5;
  T = (JD - 2451545.0) / 36525.0;
  /* calc mean angle */
  sidereal = 280.46061837 + (360.98564736629 * (JD - 2451545.0)) + (0.000387933 * T * T) - (T * T * T / 38710000.0);
  /* add a convenient multiple of 360 degrees */
  sidereal = fmod (sidereal + longitude, 360.0);
  /* change to hours */
  sidereal /= 15.0 ;
 return sidereal;
}

void lxprintde1(char* message, double ang)

{
  if (ang > M_PI) ang = ang - (M_PI * 2.0);

  int x = ang * RAD_TO_DEG * 3600.0;
  char c = '+';
  if (x < 0)
  {
    x = -x;
    c = '-';
  }
  int gra = x / 3600;
  int temp = (x % 3600);
  int min = temp / 60;
  int sec = temp % 60;
  sprintf(message, "%c%02d%c%02d:%02d#", c, gra, 225, min, sec);

};										  
void lxprintde(char* message,double ang)

{
    if (ang>M_PI) ang=ang-(M_PI*2.0);

    int x = ang*RAD_TO_DEG*3600.0;
    char c='+';
    if (x<0)
    {
        x=-x;
        c= '-';
    }
    int gra=x/3600;
    int temp=(x %3600);
    int min=temp/60;
    int sec=temp%60;
    sprintf(message,"%c%02d %02d:%02d",c,gra,min,sec);

};
void lxprintra1(char *message,double ang)
{
    int x = ang*RAD_TO_DEG*3600.0/15.0;
    int gra=x/3600;
    int temp=(x %3600);
    int min=temp/60;
    int sec=temp%60;
    sprintf(message,"%02d:%02d:%02d#",gra,min,sec);
    //APPEND
};
void lxprintra(char *message,double ang)
{
    int x = ang*RAD_TO_DEG*3600.0/15.0;
    int gra=x/3600;
    int temp=(x %3600);
    int min=temp/60;
    int sec=temp%60;
    sprintf(message,"%02d:%02d:%02d",gra,min,sec);
    //APPEND
};
void config_NTP(int zone,int dls)
{
 configTime(zone * 3600, dls * 3600 , "0.es.pool.ntp.org", "cuco.rediris.es", "hora.roa.es");
}
double sidereal_timeGMT_alt(double longitude)
{
    double temp= (millis()-sdt_millis)/(1000.0* 3600.0);
    temp=sdt+temp*K_SID;
    if (temp>=24.0) return temp-24.0;
    return temp;
}


