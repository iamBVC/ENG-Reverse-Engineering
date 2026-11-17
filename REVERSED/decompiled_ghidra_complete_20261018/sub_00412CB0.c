/* sub_412CB0 @ 00412cb0   133 bytes */

uint sub_412CB0(int param_1,uint param_2,int param_3)

{
  uint uVar1;
  
  if ((*(uint *)(param_2 + 4) & 0x400) != 0) {
    param_2 = *(uint *)(param_2 + 0xc);
    switch(param_2) {
    case 8:
      if ((*(uint *)(param_3 + 0xa0) & 0x800) == 0) {
        return param_2 & 0xffffff00;
      }
      goto LAB_00412d18;
    default:
      goto switchD_00412ccf_caseD_9;
    case 0x10:
      uVar1 = *(uint *)(param_3 + 0xa0) & 0x400;
      break;
    case 0x18:
      uVar1 = *(uint *)(param_3 + 0xa0) & 0x200;
      break;
    case 0x20:
      uVar1 = *(uint *)(param_3 + 0xa0) & 0x100;
    }
    if (uVar1 != 0) {
LAB_00412d18:
      if (param_2 < 0x11) {
        return (uint)(*(uint *)(param_1 + 0xc) < param_2);
      }
      return (uint)(param_2 < *(uint *)(param_1 + 0xc));
    }
  }
switchD_00412ccf_caseD_9:
  return param_2 & 0xffffff00;
}

