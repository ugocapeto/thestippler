#include "header.h"

void sample_points_write_to_image(
 int width,
 int height,
 int *image_arr,
 arrayHeader *sample_points
)

{

 int i;
 int j;
 int pixel;
 int maxId;
 int point_nbr;
 int point_ind;
 double p_x_dbl;
 double p_y_dbl;
 int p_x_int;
 int p_y_int;

 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< width ; j++ ) {
       pixel= i*width+j;
       image_arr[pixel]= 255;
    }
 }

 maxId= arrayMaxId(*sample_points);
 point_nbr= maxId+1;

 for ( point_ind= 0 ; point_ind< point_nbr ; point_ind++ ) {

    point_get(
     sample_points,
     point_ind,
     &p_x_dbl,
     &p_y_dbl
    );

    p_x_int= (int)round(p_x_dbl);
    if ( p_x_int < 0 )
     p_x_int= 0;
    if ( p_x_int > width-1 )
     p_x_int= width-1;

    p_y_int= (int)round(p_y_dbl);
    if ( p_y_int < 0 )
     p_y_int= 0;
    if ( p_y_int > height-1 )
     p_y_int= height-1;

    i= p_y_int;
    j= p_x_int;
    pixel= i*width+j;
    image_arr[pixel]= 0;
 }

}
