/* _AAL_LoadResourceType@16 @ 21103060   172 bytes */

undefined4 * _AAL_LoadResourceType_16(int param_1,int param_2,int param_3,int param_4)

{
  undefined4 *puVar1;
  int iVar2;
  
  for (iVar2 = (int)DAT_211155d8; iVar2 != 0; iVar2 = *(int *)(iVar2 + 0x4c)) {
  }
  puVar1 = operator_new(0x54);
  if (puVar1 == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)0x0;
  }
  else {
    puVar1 = (undefined4 *)sub_21106190(puVar1);
  }
  iVar2 = sub_21106460(puVar1,param_1,param_2,param_3,param_4);
  if (iVar2 == 0) {
    if (DAT_211155d8 == (undefined4 *)0x0) {
      DAT_211155d8 = puVar1;
      puVar1[0x13] = 0;
      DAT_211155dc = puVar1;
      return puVar1;
    }
    *(undefined4 **)((int)DAT_211155dc + 0x4c) = puVar1;
    puVar1[0x14] = DAT_211155dc;
    puVar1[0x13] = 0;
    DAT_211155dc = puVar1;
    return puVar1;
  }
  if (puVar1 != (undefined4 *)0x0) {
    sub_211061D0(puVar1);
    sub_2110D4F4(puVar1);
  }
  return (undefined4 *)0x0;
}

