#include "header.h"

int main(
 int argc,
 char* argv[]
)

{

 FILE *fp;
 char filename[MAXLINE];
 char filename_source_image[MAXLINE];
 char filename_output_image[MAXLINE];
 char filename_output_file[MAXLINE];
 image_struct intensityMap;
 double rmin;
 double rmax;
 int err_flag;
 int *source_image_arr;
 int width;
 int height;
 int *output_image_arr;
 arrayHeader *sample_points;
 int dot_radius;
 int dot_radius2;

 /*
 Let's read in the input file
 */

 fp= fopen("thestippler_input.txt","r");
 if ( fp == NULL ) {
    fprintf(stdout,"thestippler_input.txt not found!\n");
    return 1; 
 }

 /*
 Get filename for source image
 */

 fscanf(fp,"%s",filename);

 fprintf(stdout,"source image = %s\n",filename);

 strcpy(filename_source_image,filename);

 /*
 Get minimum disk radius
 */

 fscanf(fp,"%lg",&rmin);

 fprintf(stdout,"minimum disk radius = %g\n",rmin);

 /*
 Get maximum disk radius
 */

 fscanf(fp,"%lg",&rmax);

 fprintf(stdout,"maximum disk radius = %g\n",rmax);

 /*
 Get filename for output image
 */

 fscanf(fp,"%s",filename);

 fprintf(stdout,"output image = %s\n",filename);

 strcpy(filename_output_image,filename);

 /*
 Get filename for output file
 */

 fscanf(fp,"%s",filename);

 fprintf(stdout,"output file = %s\n",filename);

 strcpy(filename_output_file,filename);

 /*
 Get dot radius
 */

 fscanf(fp,"%d",&dot_radius);

 fprintf(stdout,"dot radius = %d\n",dot_radius);

 /*
 Get dot radius 2
 */

 fscanf(fp,"%d",&dot_radius2);

 fprintf(stdout,"dot radius 2 (antialiasing) = %d\n",dot_radius2);

 /*
 Done reading the input file
 */

 fclose(fp);

 /*
 Load source image
 */

 err_flag= load_image(
  filename_source_image,
  &source_image_arr,
  &width,
  &height
 );

 if ( err_flag == 1 ) {
    fprintf(stdout,"source image file %s not loaded!\n",filename_source_image);
    return 1;
 }

 intensityMap.width= width;
 intensityMap.height= height;
 intensityMap.image_arr= source_image_arr;

 /*
 Create sample points container
 */

 point_container_new(
  &sample_points
 );

 /*
 Fill sample points container
 */

 sample(
  intensityMap,
  rmin,
  rmax,
  sample_points
 );

 /*
 Allocate memory for the output image
 */

 myCalloc(output_image_arr,int,width*height,sizeof(int));

 /*
 Write sample points to image
 */

 sample_points_write_to_image(
  width,
  height,
  output_image_arr,
  sample_points
 );

 if ( !(dot_radius2 >= dot_radius) ) {
    fprintf(stdout,"dot radius 2 must be greater or equal to dot radius!\n");
    return 1;
 }

 antialias_image(
  width,
  height,
  output_image_arr,
  dot_radius,
  dot_radius2
 );

 /*
 Write output image
 */

 err_flag= write_image(
  filename_output_image,
  output_image_arr,
  width,
  height
 );

 if ( err_flag == 1 ) {
    fprintf(stdout,"output image file %s not written!\n",filename_output_image);
    return 1;
 }

 /*
 Write sample points to file
 */

 sample_points_write_to_file(
  filename_output_file,
  sample_points
 );

 return 0;

}
