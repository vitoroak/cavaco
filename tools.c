#include <stdio.h>
#include <math.h>
#include "engine.h"




int   contato_cil( double dphi, double dtheta, caso_t  X, double ponto[] )
{
    
    double theta, phi;
    int    fl_contato;
    

    theta   = 0.0;      // Para corte ascendente
    
    fl_contato = 0;
    while ( theta < DPI )
    {
        phi = 0.0;
        while ( phi < HPI )
        {
            if ( rcil( phi, theta, X ) < 1.0 )
            {
//                 printf( "Theta ini = %lf %lf\n", theta, theta/deg );
//                 printf( "phi       = %lf %lf\n", phi, phi/deg );
                fl_contato++;
                break;
            }
            phi += dphi;
        }
        if ( fl_contato )
            break;
        theta += dtheta;
    }
    
    if ( !fl_contato )
        return 1;
    
    ponto[0] = 1.0;
    ponto[1] = phi;
    ponto[2] = theta;
    
    return 0;
}



int   contato_plano( double dphi, double dtheta, caso_t  X, double ponto[] )
{
    
    double x, y, z, dx, dy, dz, deltaae;

    deltaae = sqrt( 1.0 - (1.0-X.ap)*(1.0-X.ap) ) - X.ae;
    
    x = (1.0 - X.ap)*(-X.n[0]) + deltaae*(-X.g[0]);
    y = (1.0 - X.ap)*(-X.n[1]) + deltaae*(-X.g[1]);
    z = (1.0 - X.ap)*(-X.n[2]) + deltaae*(-X.g[2]);
    

    dx = dy = dz = 0.0;
    do
    {
        dx += 0.001*X.f[0];
        dy += 0.001*X.f[1];
        dz += 0.001*X.f[2];
    } while ( mag( x+dx, y+dy, z+dz) <= 1.0 );
    
    x += dx;
    y += dy;
    z += dz;
    
    ponto[0] = mag( x, y, z);
    ponto[1] = phiesf( x, y, z);
    ponto[2] = thetaesf( x, y );
    
    return 0;
}



int   contato_fim( double dphi, double dtheta, caso_t  X, double ponto[] )
{
    
    double theta, phi;
    int    fl_contato;
    

    theta   = 0.0;      // Para corte ascendente
    
    fl_contato = 0;
    while ( theta < DPI )
    {
        phi = 0.0;
        while ( phi < HPI )
        {
            if ( rcil( phi, theta, X ) < 1.0 )
            {
//                 printf( "Theta ini = %lf %lf\n", theta, theta/deg );
//                 printf( "phi       = %lf %lf\n", phi, phi/deg );
                fl_contato++;
                break;
            }
            phi -= dphi;
        }
        if ( fl_contato )
            break;
        theta -= dtheta;
    }
    
    if ( !fl_contato )
        return 1;
    
    ponto[0] = 1.0;
    ponto[1] = phi;
    ponto[2] = theta;
    
    return 0;
}




