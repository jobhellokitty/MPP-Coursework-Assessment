#include <stdio.h>
#include <stdlib.h>

#include "sandpile.h"

/*
 *  Function to write the sandpile in RGB colour Portable Pixmap (PPM)
 *  format.
 */

void sandwrite(char *sandfile, int height[L][L])
{
  FILE *fp;

  int i, j, npix, c;
  static int pixperline = 12;

  // Encoding is black, green, magenta, yellow

  int col[MAXH+1][NRGB] = { {0,0,0}, {0,1,0}, {1,0,1}, {1,1,0} };

  /*
   *  Write the file
   */

  printf("sandwrite: opening file <%s>\n", sandfile);

  fp = fopen(sandfile, "w");

  printf("sandwrite: writing data ...\n");

  /*
   *  Start with the PPM header
   */

  fprintf(fp, "P3\n");
  fprintf(fp, "# Written by sandwrite\n");
  fprintf(fp, "%d %d\n", L, L) ;
  fprintf(fp, "%d\n", 1) ;

  /*
   *  Now write the heights to file so that height[0][0] is in the
   *  bottom-left-hand corner and height[L-1][L-1] is in the
   *  top-right-hand corner
   */

  npix = 0;

  for (j=L-1; j >= 0; j--)
    {
      for (i=0; i < L; i++)
	{
	  npix++;

          c = height[i][j];

          if (c > MAXH) c = MAXH;

	  // Make sure lines wrap after "pixperline" pixels

	  if (npix == 1)
	    {
              fprintf(fp, "%1d %1d %1d", col[c][0], col[c][1], col[c][2]);
	    }
	  else if (npix < pixperline)
	    {
              fprintf(fp, " %1d %1d %1d", col[c][0], col[c][1], col[c][2]);
	    }
	  else
	    {
              fprintf(fp, " %1d %1d %1d\n", col[c][0], col[c][1], col[c][2]);
	      npix = 0;
	    }
	}
    }

  if (npix != 0) fprintf(fp, "\n");

  printf("sandwrite: ... done\n");

  fclose(fp);
  printf("sandwrite: file closed\n");
}


/*
 *  Function to write the sandpile in RGB colour Portable Pixmap (PPM)
 *  format.
 *
 *  Note that this version expects the heihgt array to have been
 *  dynamically allocated, e.g. using the arralloc() routine:
 *
 *  int **height;
 *  cell = (int **) arraymalloc2d(L, L, sizeof(int));
 *  ...
 *  sandwritedynamic("sand.ppm", height, L);
 */

void sandwritedynamic(char *sandfile, int **height, int l)
{
  FILE *fp;

  int i, j, npix, c;
  static int pixperline = 12;

  // Encoding is black, green, magenta, yellow

  int col[MAXH+1][NRGB] = { {0,0,0}, {0,1,0}, {1,0,1}, {1,1,0} };

  /*
   *  Write the file
   */

  printf("sandwritedynamic: opening file <%s>\n", sandfile);

  fp = fopen(sandfile, "w");

  printf("sandwritedynamic: writing data ...\n");

  /*
   *  Start with the PPM header
   */

  fprintf(fp, "P3\n");
  fprintf(fp, "# Written by sandwritedynamic\n");
  fprintf(fp, "%d %d\n", l, l) ;
  fprintf(fp, "%d\n", 1) ;

  /*
   *  Now write the heights to file so that height[0][0] is in the
   *  bottom-left-hand corner and height[l-1][l-1] is in the
   *  top-right-hand corner
   */

  npix = 0;

  for (j=l-1; j >= 0; j--)
    {
      for (i=0; i < l; i++)
	{
	  npix++;

          c = height[i][j];

          if (c > MAXH) c = MAXH;

	  // Make sure lines wrap after "pixperline" pixels

	  if (npix == 1)
	    {
              fprintf(fp, "%1d %1d %1d", col[c][0], col[c][1], col[c][2]);
	    }
	  else if (npix < pixperline)
	    {
              fprintf(fp, " %1d %1d %1d", col[c][0], col[c][1], col[c][2]);
	    }
	  else
	    {
              fprintf(fp, " %1d %1d %1d\n", col[c][0], col[c][1], col[c][2]);
	      npix = 0;
	    }
	}
    }

  if (npix != 0) fprintf(fp, "\n");

  printf("sandwritedynamic: ... done\n");

  fclose(fp);
  printf("sandwritedynamic: file closed\n");
}
