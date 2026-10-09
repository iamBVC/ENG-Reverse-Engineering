/* sub_40CAB0 @ 0040cab0   1072 bytes */

undefined4 sub_40CAB0(undefined4 param_1,undefined4 param_2,int *param_3)

{
  uint uVar1;
  int iVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  int iStack_140;
  int iStack_10c;
  undefined4 local_f8 [14];
  int iStack_c0;
  uint uStack_a8;
  uint uStack_a4;
  uint uStack_a0;
  uint uStack_9c;
  undefined4 auStack_84 [27];
  undefined4 uStack_18;
  int *piStack_10;
  
  puVar6 = local_f8;
  for (iVar4 = 0x1f; iVar4 != 0; iVar4 = iVar4 + -1) {
    *puVar6 = 0;
    puVar6 = puVar6 + 1;
  }
  local_f8[0] = 0x7c;
  iVar4 = (**(code **)(*param_3 + 0x58))();
  if (iVar4 != 0) {
    return 0;
  }
  for (; (uStack_a8 & 1) == 0; uStack_a8 = uStack_a8 >> 1) {
  }
  bVar3 = 0;
  for (uVar1 = uStack_a4; (uVar1 & 1) == 0; uVar1 = uVar1 >> 1) {
    bVar3 = bVar3 + 1;
  }
  iVar4 = (int)(0xff / (ulonglong)(uStack_a4 >> (bVar3 & 0x1f)));
  for (; (uStack_a0 & 1) == 0; uStack_a0 = uStack_a0 >> 1) {
  }
  if (uStack_9c != 0) {
    for (; (uStack_9c & 1) == 0; uStack_9c = uStack_9c >> 1) {
    }
  }
  iVar2 = *param_3;
  puVar6 = auStack_84;
  for (iVar5 = 0x1f; iVar5 != 0; iVar5 = iVar5 + -1) {
    *puVar6 = 0;
    puVar6 = puVar6 + 1;
  }
  auStack_84[0] = 0x7c;
  iVar2 = (**(code **)(iVar2 + 100))(param_3,0,auStack_84,1,0);
  if (iVar2 == 0) {
    iVar2 = sub_562AEE(uStack_18,&DAT_005713b0);
    if (iVar2 != 0) {
      sub_562B75(&stack0xfffffed0,0x12,1,iVar2);
      iStack_140 = 0;
      if (0 < iStack_10c) {
        do {
          if (iStack_c0 == 8) {
            iVar5 = 0;
            if (iVar4 != 0) {
              do {
                sub_562B75(&stack0xfffffebf,1,1,iVar2);
                sub_562B75(&stack0xfffffebd,1,1,iVar2);
                sub_562B75(&stack0xfffffebe,1,1,iVar2);
                iVar5 = iVar5 + 1;
              } while (iVar5 < iVar4);
            }
          }
          else if (iStack_c0 == 0x10) {
            iVar5 = 0;
            if (iVar4 != 0) {
              do {
                sub_562B75(&stack0xfffffebe,1,1,iVar2);
                sub_562B75(&stack0xfffffebd,1,1,iVar2);
                sub_562B75(&stack0xfffffebf,1,1,iVar2);
                iVar5 = iVar5 + 1;
              } while (iVar5 < iVar4);
            }
          }
          else if ((iStack_c0 == 0x20) && (iVar5 = 0, iVar4 != 0)) {
            do {
              sub_562B75(&stack0xfffffebf,1,1,iVar2);
              sub_562B75(&stack0xfffffebd,1,1,iVar2);
              sub_562B75(&stack0xfffffebe,1,1,iVar2);
              iVar5 = iVar5 + 1;
            } while (iVar5 < iVar4);
          }
          iStack_140 = iStack_140 + 1;
        } while (iStack_140 < iStack_10c);
      }
      (**(code **)(*piStack_10 + 0x80))(piStack_10,0);
      sub_5628EB(iVar2);
      return 1;
    }
    return 0;
  }
  (**(code **)(*param_3 + 8))(param_3);
  return 0;
}

