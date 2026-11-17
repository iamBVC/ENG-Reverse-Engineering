/* sub_21105AB0 @ 21105ab0   598 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_21105AB0(void *param_1)

{
  void *this;
  int iVar1;
  int iVar2;
  undefined8 uVar3;
  undefined4 local_18;
  undefined4 *local_14;
  int local_10;
  undefined4 *local_c;
  undefined4 local_8;
  
  this = param_1;
  if (param_1 == (void *)0x0) {
    return;
  }
  if (DAT_211155e0 != 0) {
    return;
  }
  if ((*(byte *)((int)param_1 + 0xcc) & 0x10) == 0) {
    return;
  }
  LOCK();
  DAT_211155e4 = DAT_211155e4 + 1;
  UNLOCK();
  if (DAT_211155e4 != 1) goto LAB_21105cf8;
  LOCK();
  DAT_211155cc = DAT_211155cc + 1;
  UNLOCK();
  (**(code **)(**(int **)((int)param_1 + 0x88) + 0x10))
            (*(int **)((int)param_1 + 0x88),&local_8,&param_1);
  iVar2 = (uint)param_1 / *(uint *)((int)this + 0x90) + 1;
  if (iVar2 < *(int *)((int)this + 0x9c)) {
    *(int *)((int)this + 0x98) = *(int *)((int)this + 0x98) % *(int *)((int)this + 0x8c);
  }
  *(int *)((int)this + 0x9c) = iVar2;
  uVar3 = sub_211010C0(1);
  if (*(int *)((int)this + 0xa0) < (int)uVar3 - *(int *)((int)this + 0xa4)) {
LAB_21105b6c:
    iVar2 = 0;
    *(undefined4 *)((int)this + 0x98) = *(undefined4 *)((int)this + 0x9c);
  }
  else {
    if (*(int *)((int)this + 0x98) < *(int *)((int)this + 0x9c)) goto LAB_21105b6c;
    iVar2 = *(int *)((int)this + 0x98) - *(int *)((int)this + 0x9c);
  }
  *(int *)((int)this + 0xa4) = (int)uVar3;
  local_10 = 8;
  if (*(int *)((int)this + 0x8c) < 9) {
    local_10 = *(int *)((int)this + 0x8c) + -1;
  }
  if (iVar2 < local_10) {
    local_10 = local_10 - iVar2;
    do {
      iVar2 = (**(code **)(**(int **)((int)this + 0x88) + 0x2c))
                        (*(int **)((int)this + 0x88),
                         ((*(int *)((int)this + 0x98) + *(int *)((int)this + 0x8c)) %
                         *(int *)((int)this + 0x8c)) * *(int *)((int)this + 0x90),
                         *(int *)((int)this + 0x90),&local_c,&local_8,&local_18,&param_1,0);
      if (iVar2 == -0x7787ff6a) {
        (**(code **)(**(int **)((int)this + 0x88) + 0x50))(*(int **)((int)this + 0x88));
      }
      else if (iVar2 == 0) {
        local_14 = local_c;
        uVar3 = sub_211010C0(2);
        iVar1 = (int)uVar3;
        (**(code **)(*(int *)((int)this + 0xb0) + 8))
                  (*(undefined4 *)((int)this + 0x60),*(undefined4 *)((int)this + 0x5c),0,0);
        for (iVar2 = *(int *)((int)this + 4); iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x3c)) {
          if (*(void **)(iVar2 + 0x30) == this) {
            (**(code **)(iVar2 + 0x14))(*(undefined4 *)(iVar2 + 0x38));
          }
        }
        DAT_211157ec = *(int **)((int)this + 0x14);
        iVar2 = *DAT_211157ec;
        while (iVar2 != 0) {
          sub_21105D10(this,DAT_211157ec);
          DAT_211157ec = (int *)*DAT_211157ec;
          iVar2 = *DAT_211157ec;
        }
        sub_21106140(this,local_14);
        uVar3 = sub_211010C0(2);
        iVar2 = (int)uVar3;
        if (iVar2 < iVar1) {
          iVar2 = (iVar2 - iVar1) + -1;
        }
        else {
          iVar2 = iVar2 - iVar1;
        }
        DAT_211155c4 = DAT_211155c4 + iVar2;
        if (10000000 < DAT_211155c4) {
          _DAT_211155c0 = _DAT_211155c0 + DAT_211155c4 / 1000;
          DAT_211155c4 = DAT_211155c4 % 1000;
        }
        (**(code **)(**(int **)((int)this + 0x88) + 0x4c))
                  (*(int **)((int)this + 0x88),local_c,local_8,local_18,param_1);
      }
      local_10 = local_10 + -1;
      *(int *)((int)this + 0x98) = *(int *)((int)this + 0x98) + 1;
    } while (local_10 != 0);
  }
  LOCK();
  DAT_211155cc = DAT_211155cc + -1;
  UNLOCK();
LAB_21105cf8:
  LOCK();
  DAT_211155e4 = DAT_211155e4 + -1;
  UNLOCK();
  return;
}

