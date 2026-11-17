/* sub_401780 @ 00401780   157 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_401780(int param_1,int param_2)

{
  undefined4 local_18;
  float local_14;
  undefined4 local_10;
  float local_c;
  float local_8;
  float local_4;
  
  if (*(int *)(param_1 + 0x28) != 0) {
    local_18 = 0;
    local_10 = 0;
    local_c = (float)*(int *)(param_2 + 0x10) * (float)_DAT_0056e020;
    local_8 = (float)(*(int *)(param_1 + 0x30) + -0x200 + *(int *)(param_2 + 0x14)) *
              (float)_DAT_0056e020;
    local_4 = -((float)*(int *)(param_2 + 0x18) * (float)_DAT_0056e020);
    local_14 = (float)(int)-((DAT_0057d834 >> 0xc & 0xfffU) + *(int *)(param_1 + 0x2c)) *
               (float)_DAT_0056e018;
    sub_401820(*(int *)(param_1 + 0x28),&local_18);
  }
  return;
}

