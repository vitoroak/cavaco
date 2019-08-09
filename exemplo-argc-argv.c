#include <stdio.h>

/*****************************************************
 * 
 * Comando de compilação
 * 
  gcc main.c -o main -lm
 */


int    main( int argc, char* argv[]  )
{
    int     i;
    
    printf( "Hello World!\n" );
    
    printf( "%d palavras:\n", argc );
    for (i=0; i<argc; i++)
        printf( " - argv[%d] = %s\n", i, argv[i] );
    
    
}
