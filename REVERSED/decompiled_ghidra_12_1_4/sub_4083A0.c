/* sub_4083A0 @ 004083a0   206 bytes */

void sub_4083A0(uint *param_1,undefined4 param_2,undefined4 param_3,int param_4,char param_5)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  
  if (0 < param_4) {
    do {
      uVar1 = __ftol();
      uVar2 = __ftol();
      uVar3 = __ftol();
      uVar4 = uVar1 & 0xffff0000 | uVar2 & 0xff00 | uVar3 & 0xff | 0xff000000;
      if ((param_5 != '\0') &&
         (((uVar1 & 0xff0000) == 0 && (uVar2 & 0xff00) == 0) && (uVar3 & 0xff) == 0)) {
        uVar4 = 0xff000001;
      }
      *param_1 = uVar4;
      param_1 = param_1 + 1;
      param_4 = param_4 + -1;
    } while (param_4 != 0);
  }
  return;
}

