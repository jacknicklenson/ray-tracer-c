#include "linmath.h"
#include "ray.h"
#include "stb_ds.h"
#include <stddef.h>
#include <stdio.h>

void ray_col(vec3 out, struct ray *r) {
  vec3 res, tmp, tmp2;
  vec3_norm(res, r->dir);
  float a = 0.5f * (res[1] + 1.f);
  vec3_scale(tmp, (vec3){1.f, 1.f, 1.f}, 1.f - a);
  vec3_scale(tmp2, (vec3){0.5f, 0.7f, 1.f}, a);
  vec3_add(out, tmp, tmp2);
}

void render(const vec3 pixel_color) {
  int ir = (int)(255.999 * pixel_color[0]);
  int ig = (int)(255.999 * pixel_color[1]);
  int ib = (int)(255.999 * pixel_color[2]);
  printf("%d %d %d\n", ir, ig, ib);
}

int main(void) {
  size_t image_width = 400;
  float aspect_ratio = 16.f / 9.f;
  size_t image_height = (size_t)(image_width / aspect_ratio);

  // viewport
  size_t viewport_h = 2.0;
  size_t viewport_w = viewport_h * ((float)image_width / image_height);

  float focal_len = 1.0f;
  vec3 camera_center = {0.f, 0.f, 0.f};

  // Calculate the vectors across the horizontal and down the vertical viewport
  // edges.
  vec3 viewport_u = {viewport_w, 0.f, 0.f};
  vec3 viewport_v = {0.f, -viewport_h, 0.f};

  // Calculate the horizontal and vertical delta vectors from pixel to pixel.
  vec3 pixel_delta_u;
  vec3_scale(pixel_delta_u, viewport_u, 1.f / (float)image_width);
  vec3 pixel_delta_v;
  vec3_scale(pixel_delta_v, viewport_v, 1.f / (float)image_height);

  // Calculate the location of the upper left pixel.
  vec3 viewport_upper_left;
  {
    vec3 out;
    vec3_sub(viewport_upper_left, camera_center, (vec3){0.f, 0.f, focal_len});
    vec3_scale(out, viewport_u, 0.5f);
    vec3_sub(viewport_upper_left, viewport_upper_left, out);
    vec3_scale(out, viewport_v, 0.5f);
    vec3_sub(viewport_upper_left, viewport_upper_left, out);
  }
  vec3 pixel00_loc;
  {
    vec3 out;
    vec3_add(out, pixel_delta_u, pixel_delta_v);
    vec3_scale(pixel00_loc, out, 0.5f);
    vec3_add(pixel00_loc, viewport_upper_left, pixel00_loc);
  }

  // prologue
  printf("P3\n%zu %zu\n255\n", image_width, image_height);

  vec3 col, tmp, pixel_center, ray_dir;
  struct ray r;
  for (size_t j = 0; j < image_height; j++) {
    /* printf("[%%%f] Rendering Line: %zu / %zu\n", */
    /*         (float)(j + 1) / (float)image_height, j + 1, image_height); */
    for (size_t i = 0; i < image_width; i++) {
      vec3_scale(tmp, pixel_delta_u, i);
      vec3_add(pixel_center, tmp, pixel00_loc);
      vec3_scale(tmp, pixel_delta_v, j);
      vec3_add(pixel_center, tmp, pixel_center);
      vec3_sub(ray_dir, pixel_center, camera_center);
      vec4_dup(r.orig, camera_center);
      vec4_dup(r.dir, ray_dir);
      ray_col(col, &r);
      render(col);
    }
  }
  return 0;
}
