/* sub_21109660 @ 21109660   241 bytes */

undefined4 __thiscall sub_21109660(void *this,LPCSTR param_1,uint *param_2,uint *param_3)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint local_4;
  
  if (param_2 == (uint *)0x0) {
    param_2 = &local_4;
  }
  if (*param_2 == 0) {
    local_4 = 1;
  }
  else {
    local_4 = *param_2 + 1;
  }
  if (local_4 < **(uint **)this) {
    do {
      bVar1 = false;
      if (param_1 == (LPCSTR)0x0) {
LAB_21109716:
        *param_2 = local_4;
        *param_3 = local_4;
        return 1;
      }
      iVar3 = *(int *)(*(int *)((int)this + 4) + 0xc);
      uVar4 = 0xc;
      while (uVar4 < 0x80c) {
        for (; iVar3 != 0; iVar3 = *(int *)(iVar3 + 8)) {
          if ((*(uint *)(iVar3 + 0x18) == local_4) &&
             (iVar2 = lstrcmpA((LPCSTR)(iVar3 + 0x1c),param_1), iVar2 == 0)) {
            bVar1 = true;
            break;
          }
        }
        iVar3 = *(int *)(*(int *)((int)this + 4) + 4 + uVar4);
        uVar4 = uVar4 + 4;
        if (bVar1) goto LAB_21109716;
      }
      local_4 = local_4 + 1;
    } while (local_4 < **(uint **)this);
  }
  *param_2 = 0;
  *param_3 = 0;
  return 0;
}

