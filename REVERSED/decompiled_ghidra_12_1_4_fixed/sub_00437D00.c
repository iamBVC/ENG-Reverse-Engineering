/* sub_437D00 @ 00437d00   389 bytes */

bool sub_437D00(void)

{
  char cVar1;
  int iVar2;
  void *pvVar3;
  int *piVar4;
  uint uVar5;
  int iVar6;
  undefined4 uStack_80;
  undefined1 auStack_7c [16];
  undefined4 uStack_6c;
  
  uVar5 = 0;
  uStack_80 = (uint)(uint3)uStack_80;
  if (DAT_006d7acc != 0) {
    iVar6 = 0;
    do {
      piVar4 = *(int **)(iVar6 + 0x10 + DAT_006d7ad0);
      if (piVar4 != (int *)0x0) {
        (**(code **)(*piVar4 + 8))(piVar4);
        *(undefined4 *)(iVar6 + 0x10 + DAT_006d7ad0) = 0;
      }
      cVar1 = sub_437C90(iVar6 + 0x10 + DAT_006d7ad0,*(undefined4 *)(iVar6 + DAT_006d7ad0),
                         *(undefined4 *)(iVar6 + 4 + DAT_006d7ad0),auStack_7c);
      if (cVar1 == '\0') {
LAB_00437dd2:
        uStack_80 = CONCAT13(1,(uint3)uStack_80);
        *(undefined4 *)(iVar6 + 0x10 + DAT_006d7ad0) = 0;
      }
      else {
        piVar4 = *(int **)(iVar6 + 0x10 + DAT_006d7ad0);
        iVar2 = (**(code **)(*piVar4 + 100))(piVar4,0,auStack_7c,0x821,0);
        if (iVar2 != 0) {
          piVar4 = *(int **)(iVar6 + 0x10 + DAT_006d7ad0);
LAB_00437dcc:
          (**(code **)(*piVar4 + 8))(piVar4);
          goto LAB_00437dd2;
        }
        if ((*(byte *)(iVar6 + 8 + DAT_006d7ad0) & 0x80) == 0) {
          pvVar3 = *(void **)(iVar6 + 0xc + DAT_006d7ad0);
        }
        else {
          pvVar3 = operator_new(*(int *)(iVar6 + 4 + DAT_006d7ad0) * *(int *)(iVar6 + DAT_006d7ad0)
                                * 2);
          if (pvVar3 == (void *)0x0) {
            piVar4 = *(int **)(iVar6 + 0x10 + DAT_006d7ad0);
            (**(code **)(*piVar4 + 0x80))(piVar4,0);
            piVar4 = *(int **)(iVar6 + 0x10 + DAT_006d7ad0);
            goto LAB_00437dcc;
          }
          sub_406A10(*(undefined4 *)(iVar6 + 0xc + DAT_006d7ad0),pvVar3,
                     *(undefined4 *)(iVar6 + DAT_006d7ad0),*(undefined4 *)(iVar6 + 4 + DAT_006d7ad0)
                    );
        }
        sub_408470(uStack_6c,uStack_80,pvVar3,*(undefined4 *)(iVar6 + DAT_006d7ad0),0,0,
                   *(undefined4 *)(iVar6 + DAT_006d7ad0),*(undefined4 *)(iVar6 + 4 + DAT_006d7ad0),0
                   ,0,DAT_0058342c + 0x5c);
        if ((*(byte *)(iVar6 + 8 + DAT_006d7ad0) & 0x80) != 0) {
          sub_562941(pvVar3);
        }
        piVar4 = *(int **)(iVar6 + 0x10 + DAT_006d7ad0);
        (**(code **)(*piVar4 + 0x80))(piVar4,0);
      }
      uVar5 = uVar5 + 1;
      iVar6 = iVar6 + 0x14;
    } while (uVar5 < DAT_006d7acc);
  }
  return uStack_80._3_1_ == '\0';
}

