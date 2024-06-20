#include "88.h"
#include <stdint.h>                     // for uint8_t
#include <sys/types.h>                  // for int16_t

char memory[MEMORY_SIZE];

REG r;

/* Variables used by I/O. */
int clkinterval;
int ttystat;

reg EA, RA, EOP, ROP;
int ovf, dirf, intf, signf, zerof, cf; /* flag bits */
char *pcx;                             /* pcx = &m[ (cs<<4) + pc] */
char *pcx_save; /* pcx saved here at instruction start */
char *xapc;
char *eapc, *rapc;
word *rapw; /* eapw is unusable since it might be odd */
word *stkp; /* scratch variable used by PUSH and POP */
int mask;

adr cs, ds, ss, es; /* contents of segment registers */
adr xs, dsx, ssx;
long cs16; /* cs16 = 16*cs  (= cs<<4) */

unsigned timer, ticks, nextint, ints_pending;
long realtime; /* measured in mach instr (5 microsec each) */

struct intstruct intstruct[NDEV];

long l, l1, l2;        /* scratch variables used for setting carry */
short x, y, z;         /* used in lazy condition code evaluation */
unchr xc, yc, zc;      /* ditto */
int operand;
int ccvalid; /* ditto */
int anything;          /* nonzero if any dumping or tracing on */
int whendump;          /* controls dumping */
int whatdump;          /* controls dumping */
long xx;               /* scratch variable used for mem checking */
unchr stopvlag, dumpt; /* ew dumping vlag and saved t */


int traceflag, instrcount, codelength; // procdepth(), breakpt(),


