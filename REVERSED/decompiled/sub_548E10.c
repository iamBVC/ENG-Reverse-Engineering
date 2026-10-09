/* sub_548E10 @ 00548e10   551 bytes */

void sub_548E10(int param_1)

{
  undefined2 uVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  undefined2 *puVar7;
  
  iVar3 = param_1;
  do {
    puVar7 = (undefined2 *)(iVar3 + 0x30);
    switch(*puVar7) {
    case 0:
      iVar6 = *(int *)(iVar3 + 0x3c);
      if (iVar6 != 0) {
        puVar2 = *(undefined4 **)(iVar3 + 0x74);
        while (puVar2 != (undefined4 *)0x0) {
          if (puVar2[3] == iVar6) {
            if (puVar2[4] != 0) {
              sub_547890(*(undefined4 *)(iVar3 + 0x10),puVar2[0x22]);
              sub_547800(*(undefined4 *)(iVar3 + 0x10),puVar2 + 0x20);
              puVar2[4] = 0;
            }
            sub_549070(iVar3,puVar2 + 0x20);
            puVar2 = *(undefined4 **)(iVar3 + 0x74);
          }
          else {
            puVar2 = (undefined4 *)*puVar2;
          }
        }
        sub_547DF0(iVar3 + 0x14,iVar6);
        *(undefined1 *)(iVar6 + 0x4a) = 0;
      }
      break;
    default:
      sub_549200(iVar3,puVar7);
      break;
    case 2:
      iVar6 = *(int *)(iVar3 + 0x3c);
      if ((iVar6 != 0) && (*(char *)(iVar6 + 0x4a) == '\0')) {
        sub_548C90(iVar6);
        *(undefined4 *)(iVar6 + 0x34) = *(undefined4 *)(iVar6 + 4);
        *(undefined2 *)(iVar6 + 0x48) = *(undefined2 *)(iVar6 + 0x10);
        *(undefined4 *)(iVar6 + 0x44) = *(undefined4 *)(iVar6 + 8);
        sub_549150(iVar3,iVar6);
        *(undefined1 *)(iVar6 + 0x4a) = 2;
      }
      break;
    case 3:
      iVar6 = *(int *)(iVar3 + 0x3c);
      if (iVar6 != 0) {
        iVar4 = *(int *)(iVar3 + 0x34);
        if (iVar4 < 0) {
          iVar4 = 0;
        }
        else if (0x80 < iVar4) {
          iVar4 = 0x80;
        }
        *(char *)(iVar6 + 0x4b) = (char)iVar4;
        if (*(char *)(iVar6 + 0x4a) == '\x02') {
          for (puVar2 = *(undefined4 **)(iVar3 + 0x74); puVar2 != (undefined4 *)0x0;
              puVar2 = (undefined4 *)*puVar2) {
            if ((puVar2[3] == iVar6) && (puVar2[4] != 0)) {
              uVar5 = sub_5490C0(iVar3,iVar6,puVar2);
              sub_5478C0(puVar2[0x22],uVar5);
            }
          }
        }
      }
      break;
    case 4:
      iVar6 = *(int *)(iVar3 + 0x3c);
      iVar4 = *(int *)(iVar3 + 0x34);
      if ((iVar6 != 0) && (*(char *)(iVar6 + 0x4a) == '\x02')) {
        for (puVar2 = *(undefined4 **)(iVar3 + 0x74); puVar2 != (undefined4 *)0x0;
            puVar2 = (undefined4 *)*puVar2) {
          if ((puVar2[3] == iVar6) && (puVar2[4] != 0)) {
            if (iVar4 < 0) {
              *(undefined2 *)(puVar2 + 0x1b) = *(undefined2 *)((int)puVar2 + 0x6e);
            }
            else {
              uVar1 = *(undefined2 *)(puVar2 + 0x1b);
              *(short *)(puVar2 + 0x1b) = (short)iVar4;
              *(undefined2 *)((int)puVar2 + 0x6e) = uVar1;
            }
            sub_547900(puVar2[0x22],
                       CONCAT22((short)((uint)puVar2[4] >> 0x10),*(undefined2 *)(puVar2 + 0x1b)));
          }
        }
      }
      break;
    case 8:
      sub_547D70(iVar3 + 0x14,puVar7,*(undefined4 *)(iVar3 + 0x48));
      break;
    case 0x12:
      iVar6 = *(int *)(iVar3 + 0x3c);
      iVar4 = *(int *)(iVar6 + 0xc);
      if (*(int *)(iVar4 + 0x10) != 0) {
        param_1 = 0;
        sub_5478C0(*(undefined4 *)(iVar6 + 8),&param_1);
        sub_547800(*(undefined4 *)(iVar3 + 0x10),iVar6);
        *(undefined4 *)(iVar4 + 0x10) = 0;
      }
      sub_549070(iVar3,iVar6);
    }
    iVar6 = sub_547D20(iVar3 + 0x14,iVar3 + 0x30);
    *(int *)(iVar3 + 0x40) = iVar6;
  } while (iVar6 == 0);
  *(int *)(iVar3 + 0x50) = *(int *)(iVar3 + 0x50) + iVar6;
  return;
}

