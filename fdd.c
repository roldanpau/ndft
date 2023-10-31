// Forward Divided Diferences

/* Given k+1 data points (x_0, y_0), ..., (x_k, y_k), 
   compute the (1st order) forward divided differences 
   [y_0, y_1]
   [y_1, y_2]
   ...
   [y_{k-1}, y_k]
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int
main (int argc, char *argv[])
{
	FILE *fp;
	const int k = 4;	/* there are 5 data points */

	double x[k+1], y[k+1];	// input data
	double d[k+1][k+1];			// divided differences

	/* auxiliary variables */
	double *xp, *yp;
	int i,j;

	/* Read filename with data points */
	char *filename;

	if (argc != 2) {
		printf("Usage: %s datafile\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	filename = argv[1];

	/* Read data poins */
    xp = x; yp = y;
    fp = fopen(filename, "r");
    while(fscanf(fp,"%le %le", xp, yp) != EOF) {
        /* advance pointers */
        xp ++; yp ++;
    }
	fclose(fp);

	j=0;
	printf("%d-order DDs: \n", j);
	for(i=0; i<=k-j; i++)
		printf("%le ", d[j][i] = y[i]);
	printf("\n");

	for(j=1; j<=k; j++)
	{
		printf("%d-order DDs: \n", j);
		for(i=0; i<=k-j; i++)
			printf("%le ", d[j][i] = (d[j-1][i+1]-d[j-1][i])/(x[i+j]-x[i]));
		printf("\n");
	}

	return 0;
}

