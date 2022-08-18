#include "header.h"

void sample(
 image_struct gray,
 double sample_r_min,
 double sample_r_max,
 arrayHeader *points
)

{

 double radius;
 int width;
 int height;
 int *image_arr;
 int y;
 int x;
 int pixel;
 int intensity;
 bool isIsolated;
 int i;
 int j;
 arrayHeader *p_list;
 int block;
 double x2_dbl;
 double y2_dbl;
 int x2;
 int y2;
 int dist2_int;
 double dist;
 double gray_scale;
 int point;
 double x_dbl;
 double y_dbl;
 int r1;
 int r2;
 int *duh_int_arr;

 width= gray.width;
 height= gray.height;
 image_arr= gray.image_arr;

 myCalloc(p_list,arrayHeader,height,sizeof(arrayHeader));

 block= 100;
 for ( y= 0 ; y< height ; y++ ) {
    arrayInit(p_list[y],block); 
 } 

 for ( y= 0 ; y< height ; y++ ) {
    for ( x= 0 ; x< width ; x++ ) {
       pixel= y*width+x;
       intensity= image_arr[pixel];
       gray_scale= (double)intensity/255.0;
       radius = mapping_func_kernel(gray_scale,sample_r_min*2.0,sample_r_max*2.0) / 2.0;
       isIsolated = true;
       for ( i= y-radius ; i< y+radius ; i++ ) {
          if ( i < 0 ) {
             i = 0;
          }
          else if ( i >= height ) {
             break;
          }
          if ( x < width/2 ) {
             for ( j= 0 ; j< arrayMaxId(p_list[i])+1 ; j++ ) {
                point_get(
                 &p_list[i],
                 j,
                 &x2_dbl,
                 &y2_dbl
                );
                x2= (int)x2_dbl;
                y2= (int)y2_dbl;
                dist2_int= (x2-x)*(x2-x)+(y2-y)*(y2-y);
                dist= sqrt((double)dist2_int);
                if ( dist <= radius ) {
                   isIsolated = false;
                   break;
                }
                if ( x2 > x + radius ) {
                   break;
                }
             }
          }
          else {
             for ( j= arrayMaxId(p_list[i])+1-1 ; j>= 0 ; j-- ) {
                point_get(
                 &p_list[i],
                 j,
                 &x2_dbl,
                 &y2_dbl
                );
                x2= (int)x2_dbl;
                y2= (int)y2_dbl;
                dist2_int= (x2-x)*(x2-x)+(y2-y)*(y2-y);
                dist= sqrt((double)dist2_int);

                if ( dist <= radius ) {
                   isIsolated = false;
                   break;
                }
                if ( x2 < x - radius ) {
                   break;
                }
             }
          }
          if ( !isIsolated )
           break;
       }
       if ( isIsolated ) {
          point= point_add(
           &p_list[y],
           (double)x,
           (double)y
          );
       }
    }
 }

 /*
 Allocate memory for duh_int_arr
 */

 myCalloc(duh_int_arr,int,width*height,sizeof(int));

 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< arrayMaxId(p_list[i])+1 ; j++ ) {
       point_get(
        &p_list[i],
        j,
        &x_dbl,
        &y_dbl
       );
       x= (int)x_dbl;
       y= (int)y_dbl;

       /*
       Let's jiggle the point position a tiny bit!
       */

       /*
       r1 = rand()%3-1;
       r2 = rand()%3-1;

       if ( x + r1 >= 0 && x + r1 < width ) {
          x += r1;
       }
       if ( y + r2 >= 0 && y + r2 < height ) {
          y += r2;
       }
       */

       /*
       Do not add pixel if it was already added
       I absolutely do not want duplicate entries in points
       as it may be a problem with linkern if you have some
       */

       if ( duh_int_arr[y*width+x] == 1 )
        continue;

       /* 
       Add point to the sample points
       */

       point= point_add(
        points,
        (double)x,
        (double)y
       );

       /*
       Store the fact that this pixel has been added
       */
       
       duh_int_arr[y*width+x]= 1;
    }
 }

 /*
 Free duh_int_arr
 */

 myFree(duh_int_arr);

}
