void antialias_image(
 int width,
 int height,
 int *image_arr,
 int radius,
 int radius2
);

double mapping_func_kernel(
 double x,
 double min,
 double max
);

int point_add(
 arrayHeader *point_container,
 double x,
 double y
);

void point_container_free(
 arrayHeader *point_container
);

void point_container_new(
 arrayHeader **ppoint_container
);

void point_get(
 arrayHeader *point_container,
 int point,
 double *px,
 double *py
);

void point_set(
 arrayHeader *point_container,
 int point,
 double x,
 double y
);

void sample(
 image_struct gray,
 double sample_r_min,
 double sample_r_max,
 arrayHeader *points
);

void sample_points_write_to_file(
 char *filename,
 arrayHeader *sample_points
);

void sample_points_write_to_image(
 int width,
 int height,
 int *image_arr,
 arrayHeader *sample_points
);
