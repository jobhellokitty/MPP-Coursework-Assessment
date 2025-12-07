#include <stdio.h>
#include <stdlib.h>

#include "sandpile.h"

/*
 * Serial program to simulate a simple 2D abelian sandpile
 */

int main(int argc, char *argv[])
{
  /*
   *  Define the main arrays for the simulation
   */

  int newh[LX+2][LY+2], oldh[LX+2][LY+2];

  /*
   *  Additional array WITHOUT halos for IO. This is of size LxL
   *  because, even in our parallel program, we do IO in serial
   */

  int height[L][L];

  /*
   *  Local variables
   */

  int i, j, h, step, maxstep, printfreq;
  int pileheight, offset, nchange;

  if (argc != 2)
    {
      printf("Usage: sandpile <offset>\n");
      return 1;
    }

  /*
   *  Set the initial pile height etc.
   */

  pileheight = 2*L*L;
  maxstep = 5*pileheight/4;
  
  offset = atoi(argv[1]);

  printf("sandpile: L = %d, height = %d, offset = %d, maxstep = %d\n",
         L, pileheight, offset, maxstep);

  /*
   * Zero the arrays including the halos
   */

  for (i=0; i <= LX+1; i++)
    {
      for (j=0; j <= LY+1; j++)
        {
          oldh[i][j] = 0;
          newh[i][j] = 0;
        }
    }

  /*
   *  Place the initial pile at position (offset, offset). Remember
   *  that the arrays have halos so need to use the index offset+1.
   */

  oldh[offset+1][offset+1] = pileheight;

  /*
   *  Update for a fixed number of steps and periodically report progress
   */

  printfreq = 5000;

  for (step = 1; step <= maxstep; step++)
    {
      nchange = 0;

      for (i=1; i<=LX; i++)
        {
          for (j=1; j<=LY; j++)
            {
              h = oldh[i][j];
          
              // Sandpiles greater than MAXH tumble in all directions

              if (h > MAXH) h = h - 4;

              // Sandpile grows if neighbours tumble

              if (oldh[i-1][j] > MAXH) h = h + 1;
              if (oldh[i+1][j] > MAXH) h = h + 1;
              if (oldh[i][j-1] > MAXH) h = h + 1;
              if (oldh[i][j+1] > MAXH) h = h + 1;

              if (h != oldh[i][j]) nchange = nchange + 1;
              newh[i][j] = h;
            }
        }

      /*
       * Copy back for next step
       */

      for (i=1; i<=LX ; i++)
        {
          for (j=1; j<=LY ; j++)
            {
              oldh[i][j] = newh[i][j];
            }
        }

      /*
       *  Report progress of simulation every now and then
       */

      if (step%printfreq == 0)
        printf("sandpile: changes on step %d is %d\n", step, nchange);
    }

  /*
   *  Copy the centre of the sandpile, excluding the halos, into height
   */
  
  for (i=1; i<=LX; i++)
    {
      for (j=1; j<=LY; j++)
        {
          height[i-1][j-1] = oldh[i][j];
        }
    }

  /*
   *  Write the sandpile to the file "sand.ppm"
   */

  sandwrite("sand.ppm", height);

  return 0;
}
