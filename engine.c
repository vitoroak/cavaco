#include <stdio.h>
#include <math.h>
#include "engine.h"






caso_t    GetCaso( FILE *input )
{
    int     i;
    char    linha[100];
    double  aux;
    caso_t  output;
    
    
    fgets( linha, 100, input ); // Despreza a primeira linha com o cabeçalho
    fscanf( input, "%d",  &output.num );
    fscanf( input, "%lf", &output.fz );
    fscanf( input, "%lf", &output.ae );
    fscanf( input, "%lf", &output.ap );
    for (i=0; i<3; i++ )
        fscanf( input, "%lf", &output.n[i] );


    
    /* Unitarização do vetor n */
    aux = 0.0;
    for (i=0; i<3; i++)
        aux += output.n[i]*output.n[i];     // aux += é equivalente à   aux = aux + 
    aux = sqrt( aux );
    
    for (i=0; i<3; i++)
        output.n[i] = output.n[i]/aux;
    
    

    /* hat(f) = hat(j) times hat(n) = (0,1,0) times (nx,ny,nz) */
    output.f[0] = 1.0*output.n[2];
    output.f[1] = 0.0;
    output.f[2] =-1.0*output.n[0];

    
    /* Normalização do vetor f */
    aux = 0.0;
    for (i=0; i<3; i++)
        aux += output.f[i]*output.f[i];     // aux += é equivalente à   aux = aux + 
    aux = sqrt( aux );
    
    for (i=0; i<3; i++)
        output.f[i] = output.f[i]/aux;

    
    
    /* Normalização do vetor f */
    output.g[0] = output.n[1]*output.f[2] - output.n[2]*output.f[1];
    output.g[1] = output.n[2]*output.f[0] - output.n[0]*output.f[2];
    output.g[2] = output.n[0]*output.f[1] - output.n[1]*output.f[0];

    
    return output;
}

double mag2( double x, double y, double z)
{
    return x*x +y*y  +z*z;
}

double mag( double x, double y, double z)
{
    return sqrt( mag2( x,y,z ) );
}

double  xesf( double r, double phi, double theta )
{
    return r*cos(phi)*sin(theta);
}

double  yesf( double r, double phi, double theta )
{
    return r*cos(phi)*cos(theta);
}

double  zesf( double r, double phi, double theta )
{
    return -r*sin(phi);
}

double phiesf( double x, double y, double z)
{
    return asin( - z/mag(x,y,z) );
}

double thetaesf( double x, double y )
{
    return atan2( x, y );
//     return atan2( y, x );
}

double r0( double phi, double theta, caso_t param )
/* Raio da última rotação */
{
    double auxH;
    
    auxH = param.fz*1.0/sqrt(1.0-param.n[1]*param.n[1])*(  param.n[0]*sin(phi) + param.n[2]*cos(phi)*sin(theta)  );

    return sqrt( auxH*auxH + (1.0-param.fz*param.fz) ) - auxH;
}


double rplano( double phi, double theta, caso_t param )
/* Raio do plano da peça */
{

    return -(1.0-param.ap)/( cos(phi)*(param.n[0]*sin(theta) + param.n[1]*cos(theta) ) - param.n[2]*sin(phi)  );
}


double rcil( double phi, double theta, caso_t param )
/* Raio do cilíndro da última passada */
{
    double auxGa, auxGb;
    
    auxGa = 1.0 - ( param.n[2]*cos(phi)*sin(theta) + param.n[0]*sin(phi) )*( param.n[2]*cos(phi)*sin(theta) + param.n[0]*sin(phi) ) /(1.0-param.n[1]*param.n[1]);
    auxGb = param.ae*( ( param.g[0]*sin(theta) + param.g[1]*cos(theta) )*cos(phi) - param.g[2]*sin(phi) );
    return ( sqrt( auxGb*auxGb + auxGa*(1.0-param.ae*param.ae) ) + auxGb )/auxGa;

}


