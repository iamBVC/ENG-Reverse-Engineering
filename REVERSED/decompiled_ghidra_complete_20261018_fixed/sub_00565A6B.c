/* sub_565A6B @ 00565a6b   145 bytes */

undefined * sub_565A6B(int param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined1 local_1c [12];
  undefined4 local_10;
  undefined4 uStack_c;
  int local_8;
  
  uVar3 = 0;
  uVar1 = sub_569F9D(local_1c,&local_8,param_1,0,0,0,0);
  if ((uVar1 & 4) == 0) {
    iVar2 = sub_569908(local_1c,&local_10);
    if (((uVar1 & 2) != 0) || (iVar2 == 1)) {
      uVar3 = 0x80;
    }
    if (((uVar1 & 1) != 0) || (iVar2 == 2)) {
      uVar3 = uVar3 | 0x100;
    }
  }
  else {
    uVar3 = 0x200;
    local_10 = 0;
    uStack_c = 0;
  }
  *(uint *)PTR_DAT_0057c800 = uVar3;
  *(int *)(PTR_DAT_0057c800 + 4) = local_8 - param_1;
  *(ulonglong *)(PTR_DAT_0057c800 + 0x10) = CONCAT44(uStack_c,local_10);
  return PTR_DAT_0057c800;
}

