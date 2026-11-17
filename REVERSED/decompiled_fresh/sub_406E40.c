/* sub_406E40 @ 00406e40   723 bytes */

undefined4 sub_406E40(int *param_1)

{
  undefined1 uVar1;
  undefined2 uVar2;
  int *piVar3;
  void *pvVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  piVar3 = param_1;
  if (DAT_00581138 != (void *)0x0) {
    sub_407140();
  }
  DAT_00581134 = *(int *)*param_1;
  *param_1 = (int)((int *)*param_1 + 1);
  if (DAT_00581134 != 0) {
    DAT_00581138 = operator_new(DAT_00581134 << 4);
    if (DAT_00581138 == (void *)0x0) {
      return 0;
    }
    param_1 = (int *)0x0;
    if (0 < DAT_00581134) {
      iVar7 = 0;
      do {
        uVar2 = *(undefined2 *)*piVar3;
        *piVar3 = (int)((undefined2 *)*piVar3 + 1);
        *(undefined2 *)(iVar7 + (int)DAT_00581138) = uVar2;
        uVar1 = *(undefined1 *)*piVar3;
        *piVar3 = (int)((undefined1 *)*piVar3 + 1);
        *(undefined1 *)(iVar7 + 2 + (int)DAT_00581138) = uVar1;
        switch(*(undefined1 *)(iVar7 + 2 + (int)DAT_00581138)) {
        case 1:
        case 2:
          uVar1 = *(undefined1 *)*piVar3;
          *piVar3 = (int)((undefined1 *)*piVar3 + 1);
          *(undefined1 *)(iVar7 + 4 + (int)DAT_00581138) = uVar1;
          uVar1 = *(undefined1 *)*piVar3;
          *piVar3 = (int)((undefined1 *)*piVar3 + 1);
          *(undefined1 *)(iVar7 + 5 + (int)DAT_00581138) = uVar1;
          uVar1 = *(undefined1 *)*piVar3;
          *piVar3 = (int)((undefined1 *)*piVar3 + 1);
          *(undefined1 *)(iVar7 + 7 + (int)DAT_00581138) = uVar1;
          *(undefined1 *)(iVar7 + 6 + (int)DAT_00581138) = 0;
          break;
        case 7:
        case 9:
          uVar2 = *(undefined2 *)*piVar3;
          *piVar3 = (int)((undefined2 *)*piVar3 + 1);
          *(undefined2 *)(iVar7 + 4 + (int)DAT_00581138) = uVar2;
          uVar2 = *(undefined2 *)*piVar3;
          *piVar3 = (int)((undefined2 *)*piVar3 + 1);
          *(undefined2 *)(iVar7 + 6 + (int)DAT_00581138) = uVar2;
          uVar1 = *(undefined1 *)*piVar3;
          *piVar3 = (int)((undefined1 *)*piVar3 + 1);
          *(undefined1 *)(iVar7 + 8 + (int)DAT_00581138) = uVar1;
          uVar1 = *(undefined1 *)*piVar3;
          *piVar3 = (int)((undefined1 *)*piVar3 + 1);
          *(undefined1 *)(iVar7 + 9 + (int)DAT_00581138) = uVar1;
          *(undefined1 *)(iVar7 + 0xb + (int)DAT_00581138) = 0;
          break;
        case 8:
          uVar1 = *(undefined1 *)*piVar3;
          *piVar3 = (int)((undefined1 *)*piVar3 + 1);
          *(undefined1 *)(iVar7 + 4 + (int)DAT_00581138) = uVar1;
          uVar1 = *(undefined1 *)*piVar3;
          *piVar3 = (int)((undefined1 *)*piVar3 + 1);
          *(undefined1 *)(iVar7 + 5 + (int)DAT_00581138) = uVar1;
          uVar1 = *(undefined1 *)*piVar3;
          *piVar3 = (int)((undefined1 *)*piVar3 + 1);
          *(undefined1 *)(iVar7 + 8 + (int)DAT_00581138) = uVar1;
          pvVar4 = operator_new((uint)*(byte *)(iVar7 + 5 + (int)DAT_00581138) * 0x14);
          *(void **)(iVar7 + 0xc + (int)DAT_00581138) = pvVar4;
          if (*(int *)(iVar7 + 0xc + (int)DAT_00581138) == 0) {
            return 0;
          }
          iVar5 = 0;
          if (*(char *)(iVar7 + 5 + (int)DAT_00581138) != '\0') {
            iVar6 = 0;
            do {
              iVar6 = iVar6 + 0x14;
              uVar2 = *(undefined2 *)*piVar3;
              *piVar3 = (int)((undefined2 *)*piVar3 + 1);
              iVar5 = iVar5 + 1;
              *(undefined2 *)(*(int *)(iVar7 + 0xc + (int)DAT_00581138) + -0x14 + iVar6) = uVar2;
            } while (iVar5 < (int)(uint)*(byte *)(iVar7 + 5 + (int)DAT_00581138));
          }
          *(undefined1 *)(iVar7 + 7 + (int)DAT_00581138) = 0;
          *(undefined1 *)(iVar7 + 6 + (int)DAT_00581138) = 0;
          *(undefined1 *)(iVar7 + 9 + (int)DAT_00581138) = 0;
          break;
        case 10:
        case 0xb:
          uVar1 = *(undefined1 *)*piVar3;
          *piVar3 = (int)((undefined1 *)*piVar3 + 1);
          *(undefined1 *)(iVar7 + 4 + (int)DAT_00581138) = uVar1;
          uVar1 = *(undefined1 *)*piVar3;
          *piVar3 = (int)((undefined1 *)*piVar3 + 1);
          *(undefined1 *)(iVar7 + 5 + (int)DAT_00581138) = uVar1;
          uVar1 = *(undefined1 *)*piVar3;
          *piVar3 = (int)((undefined1 *)*piVar3 + 1);
          *(undefined1 *)(iVar7 + 7 + (int)DAT_00581138) = uVar1;
          uVar1 = *(undefined1 *)*piVar3;
          *piVar3 = (int)((undefined1 *)*piVar3 + 1);
          *(undefined1 *)(iVar7 + 8 + (int)DAT_00581138) = uVar1;
          pvVar4 = operator_new((uint)*(byte *)(iVar7 + 8 + (int)DAT_00581138) * 0x14);
          *(void **)(iVar7 + 0xc + (int)DAT_00581138) = pvVar4;
          if (*(int *)(iVar7 + 0xc + (int)DAT_00581138) == 0) {
            return 0;
          }
          iVar5 = 0;
          if (*(char *)(iVar7 + 8 + (int)DAT_00581138) != '\0') {
            iVar6 = 0;
            do {
              iVar6 = iVar6 + 0x14;
              uVar2 = *(undefined2 *)*piVar3;
              *piVar3 = (int)((undefined2 *)*piVar3 + 1);
              iVar5 = iVar5 + 1;
              *(undefined2 *)(*(int *)(iVar7 + 0xc + (int)DAT_00581138) + -0x14 + iVar6) = uVar2;
            } while (iVar5 < (int)(uint)*(byte *)(iVar7 + 8 + (int)DAT_00581138));
          }
          *(undefined1 *)(iVar7 + 6 + (int)DAT_00581138) = 0;
          *(undefined1 *)(iVar7 + 9 + (int)DAT_00581138) = 0;
        }
        param_1 = (int *)((int)param_1 + 1);
        iVar7 = iVar7 + 0x10;
      } while ((int)param_1 < DAT_00581134);
    }
  }
  return 1;
}

