/* Store the same packed preference records using their actual value types. */
void sub_424680(void)
{
  int index;
  sub_545F90(DAT_00584ea0, 128);
  for (index = 0; index < 39; ++index) {
    int *entry = DAT_00572ee0_storage + index * 4;
    unsigned char *flags = (unsigned char *)(entry + 3);
    void *target = (void *)entry[1];
    if ((flags[0] != 0 && DAT_005833e0 == 0) ||
        (flags[1] != 0 && DAT_005833e0 != 0)) continue;
    if (entry[0] == 0) sub_405870(entry[2], *(int *)target);
    else if (entry[0] == 1)
      ((bool (__cdecl *)(undefined4, float))sub_405830)(entry[2], *(float *)target);
    else if (entry[0] == 2) sub_405870(entry[2], *(unsigned char *)target);
  }
}
