/* LGHT loader. Keep the world pointer separate from reused float stack slots. */
void sub_42C180(unsigned int param_1, void *param_2)
{
    unsigned int *world = (unsigned int *)param_1;
    int count = 0;
    int index;
    unsigned char type, red, green, blue, flag;
    float x, y, z, near_distance, far_distance;
    float r, g, b;
    unsigned int light;
    world[0x17] = 0;
    world[0x18] = 0;
    sub_415AB0(param_2, &count);
    if (!count) return;
    world[0x18] = sub_41EF00(count * 4);
    for (index = 0; index < count; ++index) {
        sub_415AD0(param_2, &type);
        sub_415AD0(param_2, &red);
        sub_415AD0(param_2, &green);
        sub_415AD0(param_2, &blue);
        r = (red * 2) * _DAT_0056e0c8;
        g = (green * 2) * _DAT_0056e0c8;
        b = (blue * 2) * _DAT_0056e0c8;
        if (type != 1 && type != 2 && type != 4) continue;
        sub_415AB0(param_2, &x);
        sub_415AB0(param_2, &y);
        sub_415AB0(param_2, &z);
        z = -z;
        near_distance = far_distance = 0;
        flag = 0;
        if (type != 1) {
            sub_415AB0(param_2, &near_distance);
            sub_415AB0(param_2, &far_distance);
            sub_415AD0(param_2, &flag);
        }
        if (type == 4) {
            r = (r + _DAT_0056e008) * _DAT_0056e1d4;
            g = (g + _DAT_0056e008) * _DAT_0056e1d4;
            b = (b + _DAT_0056e008) * _DAT_0056e1d4;
        }
        light = sub_41B8A0(type == 1 ? 1 : 2, r, g, b, x, y, z,
                          near_distance, far_distance, flag);
        ((unsigned int *)world[0x18])[world[0x17]] = light;
        sub_41BD70(DAT_0058115c, light);
        ++world[0x17];
    }
}
