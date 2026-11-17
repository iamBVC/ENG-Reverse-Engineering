/* sub_43B790 @ 0043b790   258 bytes */

void sub_43B790(undefined4 param_1)

{
  int iVar1;
  void *pvVar2;
  int iVar3;
  int unaff_EBX;
  int unaff_ESI;
  undefined4 *puVar4;
  undefined4 uStack_8c;
  undefined4 auStack_7c [26];
  undefined4 uStack_14;
  
  if (DAT_006d91b8 != (int *)0x0) {
    (**(code **)(*DAT_006d91b8 + 8))();
  }
  uStack_8c = param_1;
  iVar1 = sub_415690(0);
  if (iVar1 != 0) {
    uStack_8c = 0;
    puVar4 = auStack_7c;
    for (iVar3 = 0x1f; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar4 = 0;
      puVar4 = puVar4 + 1;
    }
    auStack_7c[0] = 0x7c;
    auStack_7c[1] = 7;
    auStack_7c[3] = 0x280;
    auStack_7c[2] = 0x1e0;
    uStack_14 = 0x40;
    iVar3 = (**(code **)(*DAT_00582ccc + 0x18))(DAT_00582ccc,auStack_7c,&DAT_006d91b8);
    if ((iVar3 == 0) && (pvVar2 = _malloc(unaff_ESI * unaff_EBX * 3), pvVar2 != (void *)0x0)) {
      iVar3 = sub_40D3B0(iVar1,pvVar2);
      if (iVar3 == 0) {
        iVar1 = sub_562AEE(iVar1,&DAT_00570350);
        if (iVar1 == 0) {
          return;
        }
        sub_5629E6(pvVar2,unaff_ESI * unaff_EBX * 3,1,iVar1);
        sub_5628EB(iVar1);
      }
      sub_43B080(DAT_006d91b8,&uStack_8c,pvVar2,0,3);
      sub_5628BC(pvVar2);
    }
  }
  return;
}

