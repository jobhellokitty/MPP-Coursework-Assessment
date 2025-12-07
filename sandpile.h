/*
 *  Main header file for the sandpile exercise
 */

/*
 *  System size L
 */

#define L 512

/*
 *  Although overall system is square, i.e. size L x L, we will define
 *  different variables for the first and second dimensions. This is
 *  because, in the parallel code, the local arrays will not be
 *  square. For example, using a simple 1D decomposition over NPROC
 *  processes, then LX = L/NPROC and LY = L
 */

#define LX L
#define LY L

/*
 *  A couple of constants
 */

#define MAXH 3
#define NRGB 3

/*
 *  Prototypes for supplied functions
 */

/*
 *  Visualisation
 */

void sandwrite(char *cellfile, int cell[L][L]);
void sandwritedynamic(char *cellfile, int **cell, int l);
