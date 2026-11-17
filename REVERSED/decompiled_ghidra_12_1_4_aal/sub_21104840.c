/* sub_21104840 @ 21104840   122 bytes */

int * __fastcall sub_21104840(int param_1)

{
  int *this;
  int *piVar1;
  int iVar2;
  
  this = *(int **)(param_1 + 8);
  if (this == (int *)(param_1 + 0xc)) {
    return (int *)0x0;
  }
  if (*this != 0) {
    *(int *)(*this + 4) = this[1];
    *(int *)this[1] = *this;
    *this = 0;
    this[1] = 0;
  }
  if (this != (int *)0x0) {
    piVar1 = *(int **)(param_1 + 0x1c);
    if (*piVar1 != 0) {
      if (*this != 0) {
        *(int *)(*this + 4) = this[1];
        *(int *)this[1] = *this;
        *this = 0;
        this[1] = 0;
      }
      iVar2 = *piVar1;
      this[1] = (int)piVar1;
      *this = iVar2;
      *(int **)(iVar2 + 4) = this;
      *(int **)this[1] = this;
    }
    sub_21109F10(this,param_1);
  }
  return this;
}

