/* sub_56BB21 @ 0056bb21   146 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int sub_56BB21(int param_1,uint param_2)

{
  int iVar1;
  int iStack_8;
  
  if ((param_2._2_2_ & 0x7ff0) == 0x7ff0) {
    iVar1 = sub_56B9F4();
    if (iVar1 != 1) {
      if (iVar1 == 2) {
        iStack_8 = 4;
      }
      else if (iVar1 == 3) {
        iStack_8 = 2;
      }
      else {
        iStack_8 = 1;
      }
      return iStack_8;
    }
    return 0x200;
  }
  if (((param_2 & 0x7ff00000) == 0) && (((param_2 & 0xfffff) != 0 || (param_1 != 0)))) {
    return (-(uint)((param_2 & 0x80000000) != 0) & 0xffffff90) + 0x80;
  }
  if ((double)CONCAT26(param_2._2_2_,CONCAT24((undefined2)param_2,param_1)) == _DAT_0056e470) {
    return (-(uint)((param_2 & 0x80000000) != 0) & 0xffffffe0) + 0x40;
  }
  return (-(uint)((param_2 & 0x80000000) != 0) & 0xffffff08) + 0x100;
}

