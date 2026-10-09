/* sub_546E30 @ 00546e30   28 bytes */

void sub_546E30(int *param_1)

{
  if (*param_1 != 0) {
    *(int *)(*param_1 + 4) = param_1[1];
  }
  if ((int *)param_1[1] != (int *)0x0) {
    *(int *)param_1[1] = *param_1;
  }
  return;
}

