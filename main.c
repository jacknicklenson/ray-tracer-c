#include "linmath.h"
#include "stb_ds.h"
#include <stdio.h>

int main(void) {
  size_t image_width = 256;
  size_t image_height = 256;

  // prologue
  printf("P3\n%d %d\n255\n", image_width, image_height);

  for (size_t j = 0; j < image_height; j++) {
    for (size_t i = 0; i < image_width; i++) {
      vec3 col = {// map to 0.0 - 1.0 range
                  (float)i / (image_width - 1), (float)j / (image_height - 1),
                  0.0f};

      int ir = (int)(255.999 * col[0]);
      int ig = (int)(255.999 * col[1]);
      int ib = (int)(255.999 * col[2]);

      printf("%d %d %d\n", ir, ig, ib);
    }
  }
  return 0;
}
