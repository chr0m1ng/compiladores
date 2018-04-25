#ifndef _ANALISADORLEXICO_H //Carregar somente uma vez na memória
#define _ANALISADORLEXICO_H

/*
*---------------------------------------------------------------------
*   INCLUDE FILES
*---------------------------------------------------------------------
*/

#include <string.h>
#include <stdio.h>
#include <wctype.h>
#include "erroLexico.h"
#include "lexema.h"
#include "reservadas.h"
#include "saidas.h"
#include "simbolos.h"
#include "tokens.h"
#include "transicoes.h"

/*
*-----------------------------------------------------------------------
*   Data types and global variables
*-----------------------------------------------------------------------
*/

//Tipo posição no arquivo
typedef struct {
    int lin;
    int col;
    int tamLinhaAnterior;
} tPosArq;

FILE *arq;
char *nomeArq;
tPosArq posAtualArq;

/*
*-----------------------------------------------------------------------
*   Signatures
*-----------------------------------------------------------------------
*/

void inicializarAnalisadorLexico(char *);
char lerProxChar();
void devolverChar(int);
tToken obterProxToken();
void finalizarAnalisadorLexico();

/*
*-----------------------------------------------------------------------
*   FUNCTIONS
*-----------------------------------------------------------------------
*/

/* Aloca e abre nome de arquivo a ser lido, inicializa posição no arquivo, 
   aloca lexema, tabela de simbolos, tabela de tokens e tabela de erros lexicos */
void inicializarAnalisadorLexico(char *nomeArqIn)
{
    nomeArq = (char *) malloc(strlen(nomeArqIn) * sizeof(char));
    if(nomeArq == NULL)
    {
        printf("Erro ao inicializar analisador lexico\n");
        exit(-1);
    }
    strcpy(nomeArq, nomeArqIn);

    arq = fopen(nomeArq, "r");
    if(arq == NULL)
    {
        printf("Erro ao inicializar analisador lexico\n");
        exit(-1);
    }
    posAtualArq.lin = 1;
    posAtualArq.col = 1;
    posAtualArq.tamLinhaAnterior = 0;
    
    alocarLexema();
    alocarTabelaTkEncontrados();
    alocarTabSimb();
    alocarTabErrLex();
}

/* Lê e devolve proximo caractere no arquivo e trata reconhecimento de \n */
char lerProxChar()
{
    char c = fgetc(arq);
    if(c == '\n')
    {
        posAtualArq.lin++;
        posAtualArq.tamLinhaAnterior = posAtualArq.col;
        posAtualArq.col = 0;
    }
    else
        posAtualArq.col++;
    return c;
}

/* Retorna n posições no arquivo de entrada */
void devolverChar(int n)
{
    fseek(arq, -n, SEEK_CUR);

    if ((posAtualArq.col -= n) < 0) //mais caracteres que a linha atual, voltou uma linha
    {
        posAtualArq.lin--;
        posAtualArq.col = posAtualArq.tamLinhaAnterior - posAtualArq.col; //Tamanho da linha anterior - tamanho da linha atual
    }
}

tToken obterProxToken()
{
    int estadoAtual = 0;
    tToken tkAtual;
    int tamComentBloco = 0;
    tPosArq posInicioToken;
    char charAtual = ' ';
    int posTkNaTabSimb = 0;
    int primeiraQuebraDeLinhaBloco = -1;
    int erroCharAcentuado = 0;

    zerarLexema();
    while(1) 
    {
        switch (estadoAtual)
        {
            case 0: //Estado Inicial
                posInicioToken.col = posAtualArq.col;
                posInicioToken.lin = posAtualArq.lin;
                break;
            
            case 1: //TK_EOF
                addTkTabelaEncontrados(TK_EOF, posInicioToken.lin, posInicioToken.col, -1, -1);
                return TK_EOF;
            
            case 2: //Inicio TK_IDEN
                addCharNoLexema(charAtual);
                break;
            
            case 3: //TK_IDEN ou Palavra Reservada
                devolverChar(1);
                tkAtual = isPalavraReservada(lexema_atual.lex);
				if (tkAtual == TK_IDEN)
                { 
					posTkNaTabSimb = addSimbNaTab(tkAtual, lexema_atual.lex, posInicioToken.lin, posInicioToken.col);
                    addTkTabelaEncontrados(tkAtual, posInicioToken.lin, posInicioToken.col, hash(lexema_atual.lex), posTkNaTabSimb);
					return tkAtual;
				} 
                else
                {
                    addTkTabelaEncontrados(tkAtual, posInicioToken.lin, posInicioToken.col, -1, -1);
					return tkAtual;
                } 
				break;

            case 4: //Pode ser inicio de comentario em linha ou bloco ou divisão
                break;

            case 5: //Recebeu barra e depois OUTRO
                devolverChar(1);
                addTkTabelaEncontrados(TK_DIVIDIDO, posInicioToken.lin, posInicioToken.col, -1, -1);
                return TK_DIVIDIDO;
            
            case 6: //Comentario de linha
                break;
            
            case 7: //Encontra digito
                addCharNoLexema(charAtual);
                break;

            case 8: //TK_INT 
                devolverChar(1);
                posTkNaTabSimb = addSimbNaTab(TK_INT, lexema_atual.lex, posInicioToken.lin, posInicioToken.col);
                addTkTabelaEncontrados(TK_INT, posInicioToken.lin, posInicioToken.col, hash(lexema_atual.lex), posTkNaTabSimb);
                return TK_INT;
            
            case 9: //TK_INT + erro de delimitador esperado
                devolverChar(1);
                posTkNaTabSimb = addSimbNaTab(TK_INT, lexema_atual.lex, posInicioToken.lin, posInicioToken.col);
                addTkTabelaEncontrados(TK_INT, posInicioToken.lin, posInicioToken.col, hash(lexema_atual.lex), posTkNaTabSimb);
                addErrNaTab(ERRO_DEL_ESP, charAtual, posAtualArq.lin, posAtualArq.col);
                return TK_INT;

            case 10: //Inicio numero decimal digito seguido de ponto
                addCharNoLexema(charAtual);
                break;
            
            case 11: //TK_DEC + erro de delimitador esperado
                devolverChar(1);
                posTkNaTabSimb = addSimbNaTab(TK_DEC, lexema_atual.lex, posInicioToken.lin, posInicioToken.col);
                addTkTabelaEncontrados(TK_DEC, posInicioToken.lin, posInicioToken.col, hash(lexema_atual.lex), posTkNaTabSimb);
                addErrNaTab(ERRO_DEL_ESP, charAtual, posAtualArq.lin, posAtualArq.col);
                return TK_DEC;

            case 12: //TK_DEC
                devolverChar(1);
                posTkNaTabSimb = addSimbNaTab(TK_DEC, lexema_atual.lex, posInicioToken.lin, posInicioToken.col);
                addTkTabelaEncontrados(TK_DEC, posInicioToken.lin, posInicioToken.col, hash(lexema_atual.lex), posTkNaTabSimb);
                return TK_DEC;
            
            case 13: //Inicio numero decimal iniciando com ponto
                addCharNoLexema(charAtual);
                break;

            case 14: //Ponto isolado
                devolverChar(2);
                addErrNaTab(ERRO_PT_ISO, '.', posInicioToken.lin, posInicioToken.col);
                zerarLexema();
                break;

            case 15: //Inicio de Cadeia
                addCharNoLexema(charAtual);
                break;
            
            case 16: //TK_CADEIA
                addCharNoLexema(charAtual);
                posTkNaTabSimb = addSimbNaTab(TK_CADEIA, lexema_atual.lex, posInicioToken.lin, posInicioToken.col);
                addTkTabelaEncontrados(TK_CADEIA, posInicioToken.lin, posInicioToken.col, hash(lexema_atual.lex), posTkNaTabSimb);
                return TK_CADEIA;

            case 17: //TK_CADEIA + erro de cadeia não fechada
                posTkNaTabSimb = addSimbNaTab(TK_CADEIA, lexema_atual.lex, posInicioToken.lin, posInicioToken.col);
                addTkTabelaEncontrados(TK_CADEIA, posInicioToken.lin, posInicioToken.col, hash(lexema_atual.lex), posTkNaTabSimb);
                addErrNaTab(ERRO_CAD_N_FECH, '"', posInicioToken.lin, posInicioToken.col);
                return TK_CADEIA;

            case 18:  //TK_VIRG
                addTkTabelaEncontrados(TK_VIRG, posInicioToken.lin, posInicioToken.col, -1, -1);
                return TK_VIRG;

            case 19: //TK_PT_VIRG
                addTkTabelaEncontrados(TK_PT_VIRG, posInicioToken.lin, posInicioToken.col, -1, -1);
                return TK_PT_VIRG;
                
            case 20: //Inicio dois pts, pode ser atribuição
                break;

            case 21: //TK_DOIS_PTS
                devolverChar(1);
                addTkTabelaEncontrados(TK_DOIS_PTS, posInicioToken.lin, posInicioToken.col, -1, -1);
                return TK_DOIS_PTS;
            
            case 22: //TK_ATRIB
                addTkTabelaEncontrados(TK_ATRIB, posInicioToken.lin, posInicioToken.col, -1, -1);
                return TK_ATRIB;

            case 23: //TK_ABRE_PAR
                addTkTabelaEncontrados(TK_ABRE_PAR, posInicioToken.lin, posInicioToken.col, -1, -1);
                return TK_ABRE_PAR;

            case 24: //TK_FECHA_PAR
                addTkTabelaEncontrados(TK_FECHA_PAR, posInicioToken.lin, posInicioToken.col, -1, -1);
                return TK_FECHA_PAR;

            case 25: //Inicio Menor, pode ser menor, menor igual ou diferente
                break;
            
            case 26: //TK_MENOR_IGUAL
                addTkTabelaEncontrados(TK_MENOR_IGUAL, posInicioToken.lin, posInicioToken.col, -1, -1);
                return TK_MENOR_IGUAL;

            case 27: //TK_DIFERENTE
                addTkTabelaEncontrados(TK_DIFERENTE, posInicioToken.lin, posInicioToken.col, -1, -1);
                return TK_DIFERENTE;

            case 28: //TK_MENOR
                devolverChar(1);
                addTkTabelaEncontrados(TK_MENOR, posInicioToken.lin, posInicioToken.col, -1, -1);
                return TK_MENOR;

            case 29: //Inicio Maior, pode ser maior ou maior igual
                break;
            
            case 30: //TK_MAIOR_IGUAL
                addTkTabelaEncontrados(TK_MAIOR_IGUAL, posInicioToken.lin, posInicioToken.col, -1, -1);
                return TK_MAIOR_IGUAL;

            case 31: //TK_MAIOR
                devolverChar(1);
                addTkTabelaEncontrados(TK_MAIOR, posInicioToken.lin, posInicioToken.col, -1, -1);
                return TK_MAIOR;

            case 32: //TK_IGUAL
                addTkTabelaEncontrados(TK_IGUAL, posInicioToken.lin, posInicioToken.col, -1, -1);
                return TK_IGUAL;

            case 33: //TK_VEZES
                addTkTabelaEncontrados(TK_VEZES, posInicioToken.lin, posInicioToken.col, -1, -1);
                return TK_VEZES;

            case 34: //Inicio mais, pode ser incremento ou mais
                break;

            case 35: //TK_INCR
                addTkTabelaEncontrados(TK_INCR, posInicioToken.lin, posInicioToken.col, -1, -1);
                return TK_INCR;

            case 36: //TK_MAIS
                devolverChar(1);
                addTkTabelaEncontrados(TK_MAIS, posInicioToken.lin, posInicioToken.col, -1, -1);
                return TK_MAIS;

            case 37: //Inicio menos, pode ser decremento ou menos
                break;

            case 38: //TK_DECR
                addTkTabelaEncontrados(TK_DECR, posInicioToken.lin, posInicioToken.col, -1, -1);
                return TK_DECR;

            case 39: //TK_MENOS
                addTkTabelaEncontrados(TK_MENOS, posInicioToken.lin, posInicioToken.col, -1, -1);
                return TK_MENOS;

            case 40: //Caractere Invalido
                devolverChar(1);
                if(!erroCharAcentuado)
                {
                    addErrNaTab(ERRO_CHAR_INV, charAtual, posInicioToken.lin, posInicioToken.col);
                    if(!isascii(charAtual))
                        erroCharAcentuado = 1;
                }
                else
                    erroCharAcentuado = 0;    
                break;

            case 41: //Abertura de comentario de bloco
            case 42: //Possivel fechamento de comentario de bloco
                if(charAtual == '\n' && primeiraQuebraDeLinhaBloco == -1)
                    primeiraQuebraDeLinhaBloco = tamComentBloco;
                tamComentBloco++;
                break;

            case 43: //Comentario de bloco não fechado
                // printf("posicao primeira quebra de linha %d\n", primeiraQuebraDeLinhaBloco);
                // printf("voltar %d\n", tamComentBloco - primeiraQuebraDeLinhaBloco - 1);
                if(primeiraQuebraDeLinhaBloco > 0)
                    devolverChar(tamComentBloco - primeiraQuebraDeLinhaBloco);
                printf("%d %d", posAtualArq.lin, posAtualArq.col);
                devolverChar(1);
                addErrNaTab(ERRO_COMEN_BLC_N_FECH, '/', posInicioToken.lin, posInicioToken.col);
                posAtualArq.lin = posInicioToken.lin;
                posAtualArq.col = 1;
                break;

        }
        //AQUI EU VOU FAZER A LEITURA DO PROXIMO CARACTERE DO ARQUIVO E ANDAR PELO AUTOMATO
        charAtual = lerProxChar();
        estadoAtual = tabela_transicao[estadoAtual][charToAlfabeto(&charAtual)];
    }
}

/* Gera saidas do analisador lexico e libera espaços alocados na memoria */
void finalizarAnalisadorLexico()
{
    fclose(arq);

    salvarArquivoErr(nomeArq);
    salvarArquivoTabSimb(nomeArq);
    salvarArquivoTks(nomeArq);


    liberarLexema();
    liberarTabelaTkEncontrados();
    liberarTabErrLex();
    liberarTabSimb();
    
    free(nomeArq);
}

#endif