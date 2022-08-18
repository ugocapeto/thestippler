#include "header.h"

void antialias_image(
 int width,
 int height,
 int *image_arr,
 int radius,
 int radius2
)

{

 int i;
 int j;
 int pixel;
 int i2;
 int j2;
 double dist;
 int pixel2;
 int dist2_int;
 double val_dbl;
 int val_int;
 int grayscale;
 int *image_copy_arr;

 myCalloc(image_copy_arr,int,width*height,sizeof(int));

 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< width ; j++ ) {
       pixel= i*width+j;

       grayscale= image_arr[pixel];

       image_copy_arr[pixel]= grayscale;
    }
 }

 for ( i= 0 ; i< height ; i++ ) {
    for ( j= 0 ; j< width ; j++ ) {
       pixel= i*width+j;

       grayscale= image_copy_arr[pixel];

       if ( grayscale == 255 )
        continue;

       if ( grayscale != 0 ) {
          error_handler((char *)"antialias_image");
       }

       /*
       Any pixel within radius is full black
       */

       for ( i2= i-radius ; i2<= i+radius ; i2++ ) {
          for ( j2= j-radius ; j2<= j+radius ; j2++ ) {

             if ( i2 < 0 )
              continue;
             if ( i2 > height-1 )
              continue;
             if ( j2 < 0 )
              continue;
             if ( j2 > width-1 )
              continue;

             dist2_int= (i2-i)*(i2-i)+(j2-j)*(j2-j);
             dist= sqrt( (double)dist2_int );
             if ( !(dist <= (double)radius) )
              continue;

             pixel2= i2*width+j2;
             image_arr[pixel2]= 0;
          }
       }

       /*
       Any pixel withing radius2 gets a level black
       depending on the diff between distance to center pixel and radius
       The smaller the diff, the more black
       */

       for ( i2= i-radius2 ; i2<= i+radius2 ; i2++ ) {
          for ( j2= j-radius2 ; j2<= j+radius2 ; j2++ ) {

             if ( i2 < 0 )
              continue;
             if ( i2 > height-1 )
              continue;
             if ( j2 < 0 )
              continue;
             if ( j2 > width-1 )
              continue;

             dist2_int= (i2-i)*(i2-i)+(j2-j)*(j2-j);
             dist= sqrt( (double)dist2_int );
             if ( !(dist <= (double)radius2) )
              continue;
             if (   dist <= (double)radius   )
              continue;

             val_dbl= dist-(double)radius;
             val_dbl/= (double)(radius2-radius);
             val_int= (int)(val_dbl*255.0);

             pixel2= i2*width+j2;

             /*
             Change the pixel grayscale value only if it makes it more black
             */

             if ( val_int < image_arr[pixel2] )
              image_arr[pixel2]= val_int;
          }
       }
    }
 }

 myFree(image_copy_arr);

}
