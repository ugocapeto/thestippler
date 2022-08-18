#include "header.h"

void sample_points_write_to_file(
 char *filename,
 arrayHeader *sample_points
)

/*
I am storing the sample points in TSPLIB file format (.tsp)
so that concorde's linkern can be used to generate the tsp tour
*/

{

 int maxId;
 int point_nbr;
 int point_ind;
 double p_x_dbl;
 double p_y_dbl;
 FILE *fp;

 fp= fopen(filename,"w");

 fprintf(fp,"NAME : put whatever name you want here\n");
 fprintf(fp,"COMMENT : put whatever comment you want here\n");
 fprintf(fp,"TYPE : TSP\n");

 maxId= arrayMaxId(*sample_points);
 point_nbr= maxId+1;

 fprintf(fp,"DIMENSION : %d\n",
  point_nbr);

 fprintf(fp,"EDGE_WEIGHT_TYPE : EUC_2D\n");
 fprintf(fp,"NODE_COORD_SECTION\n");

 for ( point_ind= 0 ; point_ind< point_nbr ; point_ind++ ) {

    point_get(
     sample_points,
     point_ind,
     &p_x_dbl,
     &p_y_dbl
    );

    fprintf(fp,"%d %g %g\n",
     point_ind+1,
     p_x_dbl,
     p_y_dbl
    );
 }

 fprintf(fp,"EOF\n");

 fclose(fp);

}
