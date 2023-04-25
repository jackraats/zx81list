/*
	Jack Raats
	van Nispenstraat 7
	4651 XH Steenbergen
	Tel: 0031-167-540044
	Email: jack@raats.org

	version: 30 december 1992	DeSmet C / C68 v3.05
	update:  02 april 2023  	FreeBSD 13.2-RC6
*/

#include <stdio.h>
#include <stdlib.h>

char *tabel[] =
{
    " ","{1}","{2}","{7}","{4}",
    "{5}","{T}","{E}","{A}","{D}",
    "{S}","\"","#","$",":",
    "?","(",")",">","<",
    "=","+","-","*","/",
    ";",",",".","0","1",
    "2","3","4","5","6",
    "7","8","9","A","B",
    "C","D","E","F","G",
    "H","I","J","K","L",
    "M","N","O","P","Q",
    "R","S","T","U","V",
    "W","X","Y","Z","RND",
    "INKEY$","PI","CALL ","ERR MSGS ","DPOKE ",
    "ERROR ","CHAR "," ","TRACE ","DRAW ",
    "UNDRAW ","PROTECT ","EDIT ","AUTO ","DEF PROC ",
    "END PROC ","","DELETE ","DO ","LOOP ",
    "EXIT ","UNTIL ","WHILE ","WHEN ","INDENT ",
    "RESEQ ","OFF","CURSOR ","DATA ","RESTORE ",
    "READ ","NOSTALGIC ","USER ","*","ON",
    "HOME ","BREAK ","DPEEK ","LINE ","POP ",
    "PUSH ","CLR STACK ","DUP ","ELSE ","END WHEN ",
    "?","?","?","?","?",
    "?","?","?","?","?",
    "?","?","?","?","?",
    "?","?","?","[ ]","{Q}",
    "{W}","{6}","{R}","{8}","{Y}",
    "{E}","{H}","{G}","{F}","[\"]",
    "[#]","[$]","[:]","[?]","[(]",
    "[)]","[>]","[<]","[=]","[+]",
    "[-]","[*]","[/]","[;]","[,]",
    "[.]","[0]","[1]","[2]","[3]",
    "[4]","[5]","[6]","[7]","[8]",
    "[9]","[A]","[B]","[C]","[D]",
    "[E]","[F]","[G]","[H]","[I]",
    "[J]","[K]","[L]","[M]","[N]",
    "[O]","[P]","[Q]","[R]","[S]",
    "[T]","[U]","[V]","[W]","[X]",
    "[Y]","[Z]","\"\"","AT ","TAB ",
    "?","CODE ","VAL ","LEN ","SIN ",
    "COS ","TAN ","ASN ","ACS ","ATN ",
    "LN ","EXP ","INT ","SQR ","SGN ",
    "ABS ","PEEK ","USR ","STR$ ","CHR$ ",
    "NOT ","**"," OR "," AND ","<=",
    ">=","<>"," THEN "," TO "," STEP ",
    "LPRINT ","LLIST ","STOP ","SLOW ","FAST ",
    "NEW ","SCROLL ","CONT ","DIM ","REM ",
    "FOR ","GOTO ","GOSUB ","INPUT ","LOAD ",
    "LIST ","LET ","PAUSE ","NEXT ","POKE ",
    "PRINT ","PLOT ","RUN ","SAVE ","RAND ",
    "IF ","CLS ","UNPLOT ","CLEAR ","RETURN ",
    "COPY "
};

unsigned char buffer [128];
int  a,
     b,
     c,
     teller,
     lengte,
     count,
     dfile,
     regel;

FILE *fi, 
     *fo;

int dpeek ( positie )
int positie;
{
    a = buffer [positie];
    b = buffer [positie+1];
    return ( a + 256 * b );
}

int newline ( )
{
    fread ( buffer, 1, 4, fi );
    regel = 256 * buffer[0] + buffer[1];
    lengte = dpeek ( 2 );
    if ( teller >= dfile ) return ( 0 );
    fprintf ( fo, "\n%4d ", regel );
    count = 0;
    teller += 4;
    return ( 0 );
}

int fout ( )
{
    printf ("\n\n");
    fflush ( stdout );
    exit ( 1 );
}

int main ( argc, argv )
int argc;
char *argv[];
{
    printf ( "\nzx81 list utility           V02042023");
    printf ( "\n(C) Jack Raats, Steenbergen 1992-2023");
    printf ( "\nE-mail:                jack@raats.org");

    if ( argc != 3 )
    {
        printf ("\n\n   USAGE:");
        printf ("\n\n   zx81list filename.p filename.txt");
        fout();
    }

    if ( ! ( fi = fopen ( argv[1], "rb" ) ) ) 
    {
        printf ("\n\n   Cannot open %s", argv[1] );
        fout();
    }

    if ( ! ( fo = fopen ( argv[2], "wb" ) ) ) 
    {
        printf ("\n\n   Cannot open %s", argv[2] );
        fout();
    }

    fprintf ( fo, "\nzx81 list utility           V02042023");
    fprintf ( fo, "\n(C) Jack Raats, Steenbergen 1992-2023");
    fprintf ( fo, "\nE-mail:                jack@raats.org");

    fread ( buffer, 1, (16509-16393), fi );

    fprintf ( fo, "\n\nFILE: %s", argv [1] );

    fprintf ( fo, "\n\n----- SYSTEM VARIABLES -----\n");
    fprintf ( fo, "\nPROG  : %5d", 16509 );
    dfile = dpeek ( 3 );
    fprintf ( fo, "\nD_FILE: %5d", dfile );
    fprintf ( fo, "\nVARS  : %5d", dpeek (  7) );
    fprintf ( fo, "\nE_LINE: %5d", dpeek ( 11) );
    fprintf ( fo, "\nSTKBOT: %5d", dpeek ( 17) );
    fprintf ( fo, "\nSTKEND: %5d", dpeek ( 19) );

    fprintf ( fo, "\n\n----- LEGENDA -----\n");
    fprintf ( fo, "\n[A] means  INVERSE A");
    fprintf ( fo, "\n{A} means GRAPHICS A");
    fprintf ( fo, "\n\n----- START OF LISTING -----\n");

    teller = 16509;

    newline();

    while ( teller < dfile )
    {
        c = fgetc ( fi );
        teller++;
        count++;
        switch (c)
        {
            case 118:
                if ( count != lengte )
                {
                    b = lengte - count;
                    for ( a = 1 ; a <= b ; a ++ )
                        c = fgetc ( fi );
                    teller += b;
                }
                newline();
                break;
            case 126:
                fread ( buffer, 1, 5, fi );
                teller += 5;
                count += 5;
                break;
            default:
                fprintf ( fo, "%s", tabel[c] );
                break;
        }
    }
    fprintf ( fo, "\n\n----- END OF LISTING -----\n");
    fclose ( fi );
    fclose ( fo );
    printf ("\n\n   READY...\n\n");
    exit (0);
}
