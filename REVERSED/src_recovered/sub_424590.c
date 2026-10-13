/* 39 packed 16-byte preference records at 00572EE0, ending at 00573150. */
void sub_424590(void)
{
  int index;
  for (index = 0; index < 39; ++index) {
    int *entry = DAT_00572ee0_storage + index * 4;
    unsigned char *flags = (unsigned char *)(entry + 3);
    void *target = (void *)entry[1];
    float fallback;
    float10 value;
    if ((flags[0] != 0 && DAT_005833e0 == 0) ||
        (flags[1] != 0 && DAT_005833e0 != 0)) continue;
    if (entry[0] == 0) fallback = (float)*(int *)target;
    else if (entry[0] == 1) fallback = *(float *)target;
    else if (entry[0] == 2) fallback = (float)*(unsigned char *)target;
    else continue;
    value = ((float10 (__cdecl *)(undefined4, float))sub_4057C0)(entry[2], fallback);
    if (entry[0] == 0) *(int *)target = (int)value;
    else if (entry[0] == 1) *(float *)target = (float)value;
    else *(unsigned char *)target = value != 0.0;
  }
}
