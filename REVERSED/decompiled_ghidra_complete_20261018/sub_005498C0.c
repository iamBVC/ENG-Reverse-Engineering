/* sub_5498C0 @ 005498c0   188 bytes */

int sub_5498C0(short param_1,short param_2,byte param_3,char param_4)

{
  short sVar1;
  short sVar2;
  
  param_1 = param_1 - (ushort)param_3;
  sVar1 = 0;
  if (param_1 < 0) {
    sVar1 = 0;
    if (param_1 < -0xb) {
      sVar2 = (short)((uint)-(int)param_1 / 0xc);
      sVar1 = -sVar2;
      param_1 = param_1 + sVar2 * 0xc;
    }
    if (param_1 != 0) {
      param_1 = param_1 + 0xc;
      sVar1 = sVar1 + -1;
    }
  }
  else if ((0 < param_1) && (0xb < param_1)) {
    sVar1 = (short)((uint)(int)param_1 / 0xc);
    param_1 = param_1 + sVar1 * -0xc;
  }
  sVar2 = param_1 * 0x10 +
          (short)((int)((int)param_2 + (int)param_4 + ((int)param_2 + (int)param_4 >> 0x1f & 3U)) >>
                 2);
  if (sVar2 < 0) {
    sVar2 = sVar2 + 0xbf;
    sVar1 = sVar1 + -1;
  }
  else if (0xbf < sVar2) {
    sVar2 = sVar2 + -0xc0;
    sVar1 = sVar1 + 1;
  }
  if (sVar1 < 0) {
    return (int)*(short *)(&DAT_00578c78 + sVar2 * 2) >> (-(byte)sVar1 & 0x1f);
  }
  return (int)*(short *)(&DAT_00578c78 + sVar2 * 2) << ((byte)sVar1 & 0x1f);
}

