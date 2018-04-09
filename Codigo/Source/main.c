/*
*---------------------------------------------------------------------
*   INCLUDE FILES
*---------------------------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../Header/transicoes.h"
#include "../Header/tokens.h"
#include "../Header/reservadas.h"



int main(int argc, char *argv[])
{

    printf("%s\n", tokenGetText( isPalavraReservada("fim_programa") ) );

    return 0;
}