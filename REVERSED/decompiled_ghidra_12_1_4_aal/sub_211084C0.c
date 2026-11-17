/* sub_211084C0 @ 211084c0   509 bytes */

DWORD __thiscall sub_211084C0(void *this,HANDLE param_1)

{
  DWORD DVar1;
  int *this_00;
  void *lpBuffer;
  int iVar2;
  int iVar3;
  BOOL BVar4;
  int *piVar5;
  int iVar6;
  DWORD DStack_14;
  DWORD local_10;
  void *pvStack_c;
  DWORD local_8;
  void *local_4;
  
  local_10 = 0;
  local_4 = this;
  if (*(int *)((int)this + 0x30) == 1) {
    DVar1 = *(DWORD *)((int)this + 0x2c);
    WriteFile(param_1,(LPCVOID)0x0,DVar1,&local_8,(LPOVERLAPPED)0x0);
    return DVar1;
  }
  this_00 = operator_new(0x11c);
  if (this_00 == (int *)0x0) {
    this_00 = (int *)0x0;
  }
  else {
    *this_00 = 0;
    this_00[1] = 0;
    piVar5 = this_00 + 0x24;
    iVar6 = 3;
    do {
      *piVar5 = 0;
      piVar5[1] = 0;
      piVar5 = piVar5 + 9;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
    this_00[0x16] = 0;
    this_00[2] = 0;
    this_00[3] = 0;
  }
  sub_21109F10(this_00,DAT_211155ac);
  sub_2110A040(this_00,(int)this);
  this_00[0x1c] = 1;
  if (this_00[0x24] != 0) {
    (*(code *)this_00[0x29])(this_00[0x2b],0,this_00 + 0x1c);
  }
  this_00[0x19] = *(int *)(*(int *)((int)this + 0x18) + 4);
  lpBuffer = operator_new(0x2000);
  pvStack_c = lpBuffer;
  if ((uint)this_00[this_00[0x16] + 0x10] < *(uint *)((int)this + 0x2c)) {
    do {
      DStack_14 = 0;
      if (this_00[0x24] != 0) {
        iVar6 = 0x2000;
        (*(code *)this_00[0x29])(this_00[0x2b],2,&DStack_14);
        do {
          iVar2 = (*(code *)this_00[0x28])(this_00[0x2b],DStack_14 + (int)lpBuffer,iVar6);
          iVar3 = (*(code *)this_00[0x2a])(this_00[0x2b],this_00[0x2c]);
          this_00[this_00[0x16] + 0x10] = iVar3;
          DStack_14 = DStack_14 + iVar2;
          iVar6 = iVar6 - iVar2;
          lpBuffer = pvStack_c;
          if (iVar2 == 0) break;
        } while (iVar6 != 0);
      }
      DVar1 = DStack_14;
      local_10 = local_10 + DStack_14;
      BVar4 = WriteFile(param_1,lpBuffer,DStack_14,&local_8,(LPOVERLAPPED)0x0);
      if ((BVar4 == 0) || (local_8 != DVar1)) {
        OutputDebugStringA(s_No_write_performed_21114614);
      }
    } while ((DVar1 != 0) && ((uint)this_00[this_00[0x16] + 0x10] < *(uint *)((int)local_4 + 0x2c)))
    ;
  }
  if (this_00 != (int *)0x0) {
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
    sub_2110D4F4(this_00);
  }
  if (lpBuffer != (LPVOID)0x0) {
    sub_2110D4F4(lpBuffer);
  }
  return local_10;
}

