/* sub_211086C0 @ 211086c0   779 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

int __thiscall sub_211086C0(void *this,HANDLE param_1,byte param_2,int param_3)

{
  int *this_00;
  int *piVar1;
  uint uVar2;
  BOOL BVar3;
  int iVar4;
  int *piVar5;
  undefined4 *puVar6;
  longlong lVar7;
  int iStack_28;
  int *local_24;
  undefined4 *local_20;
  int local_1c;
  int local_18;
  int local_14;
  undefined4 *local_10;
  uint local_c;
  undefined4 *local_8;
  
  local_14 = 0;
  this_00 = operator_new(0x11c);
  if (this_00 == (int *)0x0) {
    this_00 = (int *)0x0;
  }
  else {
    sub_211089D0(this_00);
    piVar1 = this_00 + 0x24;
    iVar4 = 3;
    do {
      *piVar1 = 0;
      piVar1[1] = 0;
      piVar1 = piVar1 + 9;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
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
  iStack_28 = 0;
  local_24 = &local_18;
  local_20 = (undefined4 *)
             (((float)*(uint *)(*(int *)((int)this + 0x18) + 4) * _DAT_2111233c) / (float)param_3);
  local_18 = (int)ROUND(ROUND((float)local_20));
  local_8 = *(undefined4 **)((int)this + 0x34);
  local_1c = *(int *)((int)this + 0x2c) + (int)local_8;
  piVar1 = operator_new(0x8020);
  local_10 = operator_new(0x8020);
  local_20 = operator_new(0x8020);
  if ((uint)this_00[this_00[0x16] + 0x10] < (uint)this_00[this_00[0x16] + 0x12]) {
    do {
      piVar5 = piVar1;
      for (iVar4 = 0x2000; iVar4 != 0; iVar4 = iVar4 + -1) {
        *piVar5 = 0;
        piVar5 = piVar5 + 1;
      }
      puVar6 = local_10;
      for (iVar4 = 0x2000; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar6 = 0;
        puVar6 = puVar6 + 1;
      }
      puVar6 = local_20;
      for (iVar4 = 0x2000; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar6 = 0;
        puVar6 = puVar6 + 1;
      }
      local_24 = piVar1;
      if (this_00[0x24] != 0) {
        iVar4 = (uint)((param_2 & 2) != 2) * -2;
        uVar2 = iVar4 + 3;
        local_1c = (((param_2 & 1) != 0) + 1) * param_3;
        lVar7 = __ftol();
        uVar2 = uVar2 - (int)lVar7 & ~uVar2;
        if (uVar2 == 0) {
          uVar2 = iVar4 + 4;
        }
        if (0x8000 < (int)uVar2) {
          uVar2 = 0x8000;
        }
        local_8 = local_20 + 4;
        local_1c = (*(code *)this_00[0x28])(this_00[0x2b],local_8,uVar2);
        local_1c = local_1c + (int)local_8;
      }
      (*(code *)this_00[0x39])
                (&local_8,this_00 + 0x1d,local_1c,&local_24,piVar1 + 0x2000,this_00 + 0x20,
                 this_00 + 0x21,local_18,this_00[0x22],this_00[0x23],0x26);
      uVar2 = (int)local_24 - (int)piVar1;
      sub_2110A120(this_00,local_10,piVar1,uVar2);
      uVar2 = uVar2 >> 1;
      BVar3 = WriteFile(param_1,local_10,uVar2,&local_c,(LPOVERLAPPED)0x0);
      if ((BVar3 == 0) || (local_c != uVar2)) {
        OutputDebugStringA(s_No_write_performed_21114614);
      }
      local_14 = local_14 + local_c;
      if (this_00[0x24] == 0) {
        this_00[this_00[0x16] + 0x10] = (int)local_8 - this_00[this_00[0x16] + 0xe];
      }
      else {
        iStack_28 = (int)local_8 - local_1c;
        if (iStack_28 != 0) {
          (*(code *)this_00[0x29])(this_00[0x2b],3,&iStack_28);
        }
        iVar4 = (*(code *)this_00[0x2a])(this_00[0x2b],this_00[0x2c]);
        this_00[this_00[0x16] + 0x10] = iVar4;
      }
    } while ((uint)this_00[this_00[0x16] + 0x10] < (uint)this_00[this_00[0x16] + 0x12]);
  }
  if (local_20 != (undefined4 *)0x0) {
    sub_2110D4F4(local_20);
  }
  if (local_10 != (undefined4 *)0x0) {
    sub_2110D4F4(local_10);
  }
  if (piVar1 != (int *)0x0) {
    sub_2110D4F4(piVar1);
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
  return local_14;
}

