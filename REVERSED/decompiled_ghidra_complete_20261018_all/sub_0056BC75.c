/* sub_56BC75 @ 0056bc75   49 bytes */

undefined4 sub_56BC75(byte param_1,uint param_2,byte param_3)

{
  if ((*(byte *)((int)&DAT_006da6c0 + param_1 + 1) & param_3) == 0) {
    if (param_2 == 0) {
      param_2 = 0;
    }
    else {
      param_2 = *(ushort *)(&DAT_0057c80e + (uint)param_1 * 2) & param_2;
    }
    if (param_2 == 0) {
      return 0;
    }
  }
  return 1;
}

