/* sub_21109B80 @ 21109b80   98 bytes */

undefined4 * __thiscall sub_21109B80(void *this,int param_1)

{
  int *piVar1;
  int *piVar2;
  
  *(int *)((int)this + 4) = param_1;
  piVar1 = operator_new(param_1 * 0x14 + 4);
  if (piVar1 == (int *)0x0) {
    piVar2 = (int *)0x0;
  }
  else {
    piVar2 = piVar1 + 1;
    *piVar1 = param_1;
    piVar1 = piVar2;
    if (-1 < param_1 + -1) {
      do {
        piVar1[3] = 0;
        piVar1[2] = 0;
        piVar1[1] = 0;
        *piVar1 = 0;
        piVar1[4] = 0;
        param_1 = param_1 + -1;
        piVar1 = piVar1 + 5;
      } while (param_1 != 0);
    }
  }
  *(int **)this = piVar2;
  *(undefined4 *)((int)this + 8) = 0;
  *(undefined4 *)((int)this + 0x14) = 0;
  *(undefined4 *)((int)this + 0xc) = 0;
  *(undefined4 *)((int)this + 0x10) = 0;
  return this;
}

