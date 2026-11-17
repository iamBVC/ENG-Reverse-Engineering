/* sub_4264B0 @ 004264b0   74 bytes */

void sub_4264B0(short *param_1)

{
  if ((char)param_1[1] != '\0') {
    *(char *)(param_1 + 1) = (char)param_1[1] + -1;
    return;
  }
  if (*(char *)((int)param_1 + 3) == '\0') {
    *param_1 = *param_1 + -0x10;
    if (*param_1 < 0) {
      *param_1 = 0;
      return;
    }
  }
  else {
    *param_1 = *param_1 + 0x10;
    if ((0x7f < *param_1) && (*param_1 = 0x7f, *(char *)((int)param_1 + 7) != '\0')) {
      *(undefined1 *)((int)param_1 + 3) = 0;
      *(undefined1 *)(param_1 + 1) = 0x50;
    }
  }
  return;
}

