#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

float DAT_0056e418 = 1.0f;
float DAT_0056e008 = 1.0f;
float DAT_0056e00c = 0.0f;
float DAT_0056e49c = 65536.0f;
float DAT_00583390 = 0.0f;
float DAT_00583394 = 0.0f;
unsigned char DAT_00583398 = 0;
unsigned char DAT_0058339c = 0;
unsigned char DAT_005833a0 = 0;
unsigned char DAT_005833a4 = 0;
unsigned char DAT_006d7c6b = 0;
unsigned char DAT_006d7c6c = 0;
unsigned char DAT_006d7c6f = 0;

int sub_43A110(int plane, float *input, int count, float *output);
int sub_43A810(int plane, float *input, int count, float *output, float mode);

static void set_vertex(float *v, float x, float y, float z, float w, float u, float t)
{
    v[0] = x; v[1] = y; v[2] = z; v[3] = w;
    v[4] = (float)0xff204060U; v[5] = 0.0f; v[6] = u; v[7] = t;
}

static int check_clip(int count, const float *output, int axis, float boundary, int keep_less)
{
    int i;
    int intersections = 0;
    if (count != 4) return 1;
    for (i = 0; i < count; ++i) {
        float value = output[i * 8 + axis];
        if (keep_less ? value > boundary + 0.0001f : value < boundary - 0.0001f)
            return 2;
        if (fabsf(value - boundary) < 0.0001f) ++intersections;
    }
    return intersections == 2 ? 0 : 3;
}

int main(void)
{
    float input[24], output[64];
    int count, rc;

    set_vertex(&input[0], -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
    set_vertex(&input[8], 1.0f, 0.0f, -2.0f, 1.0f, 1.0f, 0.0f);
    set_vertex(&input[16], -0.5f, 1.0f, 0.0f, 1.0f, 0.5f, 1.0f);

    count = sub_43A110(4, input, 3, output);
    rc = check_clip(count, output, 2, -1.0f, 0);
    if (rc != 0) {
        fprintf(stderr, "near-plane clip failed: count=%d check=%d\n", count, rc);
        return 1;
    }

    count = sub_43A810(0, input, 3, output, 0.0f);
    rc = check_clip(count, output, 0, 0.0f, 1);
    if (rc != 0) {
        fprintf(stderr, "left-plane clip failed: count=%d check=%d\n", count, rc);
        return 2;
    }
    puts("clipper intersections and bounds verified");
    return 0;
}
