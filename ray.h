#ifndef RAY_H
#define RAY_H

#include "linmath.h"

struct ray {
  vec3 orig;
  vec3 dir;
};

void ray_at(vec3 out, struct ray *r, float t) {
  vec3 scale;
  vec3_scale(scale, r->dir, t);
  vec3_add(out, r->orig, scale);
}

#endif
