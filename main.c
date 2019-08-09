#include <stdio.h>
#include "engine.h"
#include "tools.h"

/*****************************************************
 * 
 * Comando de compilação
 * 
  gcc -g main.c engine.c tools.c  -o cavaco -lm
 */





int    main( int argc, char* argv[]  )
{
    int     i, j;
    caso_t  X;
        
    FILE*   arqE;
    double  ponto[3];
    
    
    if ( argc < 2 )
    {
        printf( "Especifique o nome do arquivo com os parâmetros!\n"); 
        printf( "Exemplo:\n");
        printf( "  %s caso1.txt\n", argv[0] );
        return 1;
    }
    
    
    arqE = fopen( argv[1], "r" );  // Tenta abrir o arquivo de entrada
    if ( !arqE )
    {
        printf( "Erro ao tentar abrir o arquivo de entrada '%s'!\n", argv[1]); 
        return 1;
    }
    
    
    X = GetCaso( arqE );
    
    contato_cil( 0.1*deg, 0.1*deg, X, &ponto[0] );
    printf( "%.6lf, % .6lf, % .6lf\n", ponto[0], ponto[1], ponto[2]);
    
    contato_plano( 0.1*deg, 0.1*deg, X, &ponto[0] );
    printf( "%.6lf, % .6lf, % .6lf\n", ponto[0], ponto[1], ponto[2]);
    
    contato_fim( 0.1*deg, 0.1*deg, X, &ponto[0] );
    printf( "%.6lf, % .6lf, % .6lf\n", ponto[0], ponto[1], ponto[2]);
}
