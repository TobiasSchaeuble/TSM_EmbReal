/*-----------------------------
 stdout
 (c) H.Buchmann FHNW 2011
 $Id$
-------------------------------*/
#include "stdout.h"
#include "io/ascii.h"
#include "io/uart-poll.h"

static void out(char ch)
{
 uart_poll_out(ch);
}

static void newln()
{
 uart_poll_out('\n');
}

static void tab()
{
 uart_poll_out('\t');
}

void stdout_init()
{
}

Out stdout_={out,newln,tab};
Out* stdout=&stdout_;

