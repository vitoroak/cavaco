#define PI  3.14159265358979
#define DPI 6.28318530717959
#define HPI 1.5707963267949
#define deg 0.0174532925199433

typedef struct  caso_t {
    int     num;
    double  fz;
    double  ae;
    double  ap;
    double  n[3];
    double  f[3];
    double  g[3];
} caso_t;



caso_t  GetCaso( FILE *input );
double mag2( double x, double y, double z);
double mag ( double x, double y, double z);
double  yesf( double r, double phi, double theta );
double  zesf( double r, double phi, double theta );
double  xesf( double r, double phi, double theta );
double phiesf( double x, double y, double z);
double thetaesf( double x, double y );
double r0    ( double phi, double theta, caso_t param );
double rplano( double phi, double theta, caso_t param );
double rcil  ( double phi, double theta, caso_t param );
