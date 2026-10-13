/* Original renderer input is one contiguous block of six floats. */
void sub_401780(int param_1,int param_2)
{
  float transform[6];
  if (*(int *)(param_1 + 0x28) == 0) return;
  transform[0] = 0;
  transform[1] = (float)(int)-((DAT_0057d834 >> 0xc & 0xfffU) + *(int *)(param_1 + 0x2c)) * _DAT_0056e018;
  transform[2] = 0;
  transform[3] = (float)*(int *)(param_2 + 0x10) * _DAT_0056e020;
  transform[4] = (float)(*(int *)(param_1 + 0x30) - 0x200 + *(int *)(param_2 + 0x14)) * _DAT_0056e020;
  transform[5] = -((float)*(int *)(param_2 + 0x18) * _DAT_0056e020);
  sub_401820(*(int *)(param_1 + 0x28), transform);
}
