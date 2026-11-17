/* sub_569F2F @ 00569f2f   110 bytes */

uint sub_569F2F(uint param_1,int *param_2)

{
  uint uVar1;
  
  if ((param_1 != 0xffffffff) &&
     ((uVar1 = param_2[3], (uVar1 & 1) != 0 || (((uVar1 & 0x80) != 0 && ((uVar1 & 2) == 0)))))) {
    if (param_2[2] == 0) {
      sub_569C81(param_2);
    }
    if (*param_2 == param_2[2]) {
      if (param_2[1] != 0) {
        return 0xffffffff;
      }
      *param_2 = *param_2 + 1;
    }
    if ((*(byte *)(param_2 + 3) & 0x40) == 0) {
      *param_2 = *param_2 + -1;
      *(char *)*param_2 = (char)param_1;
    }
    else {
      *param_2 = *param_2 + -1;
      if (*(char *)*param_2 != (char)param_1) {
        *param_2 = (int)((char *)*param_2 + 1);
        return 0xffffffff;
      }
    }
    param_2[1] = param_2[1] + 1;
    param_2[3] = param_2[3] & 0xffffffefU | 1;
    return param_1 & 0xff;
  }
  return 0xffffffff;
}

