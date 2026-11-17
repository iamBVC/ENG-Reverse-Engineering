/* sub_211048C0 @ 211048c0   136 bytes */

void __thiscall sub_211048C0(void *this,int *param_1)

{
  int *this_00;
  int iVar1;
  int *piVar2;
  
  this_00 = *(int **)((int)this + 0x14);
  iVar1 = *this_00;
  while (iVar1 != 0) {
    if (this_00 == param_1) {
      this_00[0x16] = 0;
      this_00[3] = 0;
      this_00[0x46] = 0;
      this_00[6] = 0;
      sub_2110A200(this_00,4,0,0);
      if (*this_00 != 0) {
        *(int *)(*this_00 + 4) = this_00[1];
        *(int *)this_00[1] = *this_00;
        *this_00 = 0;
        this_00[1] = 0;
      }
      piVar2 = *(int **)((int)this + 0x10);
      if (*piVar2 != 0) {
        if (*this_00 != 0) {
          *(int *)(*this_00 + 4) = this_00[1];
          *(int *)this_00[1] = *this_00;
          *this_00 = 0;
          this_00[1] = 0;
        }
        iVar1 = *piVar2;
        this_00[1] = (int)piVar2;
        *this_00 = iVar1;
        *(int **)(iVar1 + 4) = this_00;
        *(int **)this_00[1] = this_00;
      }
    }
    this_00 = (int *)*this_00;
    iVar1 = *this_00;
  }
  return;
}

