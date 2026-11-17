/* sub_405D60 @ 00405d60   542 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_405D60(void)

{
  char cVar1;
  byte bVar2;
  int3 iVar5;
  int iVar3;
  uint uVar4;
  uint uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  undefined4 *puVar10;
  undefined4 uVar11;
  
  iVar8 = 0;
  iVar9 = 0x20;
  cVar1 = *(char *)(DAT_006d94e4 + 2);
  puVar10 = DAT_006d94e4;
  do {
    if (cVar1 == '\a') {
      sub_425BB0();
      sub_425C00();
      if ((DAT_005fcf08 & 0x4000) != 0) {
        DAT_006d9bd0 = 1;
      }
      _DAT_006d9bec = _DAT_006d9bec + DAT_006d94e0;
      if (_DAT_006d9bec == 0x80) {
        DAT_006d94e0 = 0;
      }
      if (DAT_006d94cc == 0) {
        if (_DAT_006d9bec == 0) {
          if (DAT_006d9bd0 == 0) {
            DAT_006d94cc = 0x96;
            DAT_006d94e4 = puVar10 + 3;
            DAT_006d94e0 = 2;
            return;
          }
        }
        else {
          DAT_006d94e0 = -2;
        }
        return;
      }
      DAT_006d94cc = DAT_006d94cc + -1;
      return;
    }
    bVar2 = *(byte *)(puVar10 + 2);
    if (9 < bVar2) goto switchD_00405d87_caseD_5;
    iVar5 = (int3)((char)bVar2 >> 7);
    switch(bVar2) {
    case 0:
      sub_436740(*puVar10,iVar9,CONCAT31(iVar5,DAT_006d9bec),_DAT_006d9bec & 0xff,
                 _DAT_006d9bec & 0xff);
      iVar9 = iVar9 + 0x12;
      break;
    case 1:
      iVar8 = puVar10[1];
      if (iVar8 == 0) {
        iVar9 = 100;
        iVar3 = 0;
LAB_00405dc7:
        iVar8 = 0x14;
      }
      else {
        iVar3 = iVar8 + -1;
        if (iVar3 == 0) {
          iVar9 = 0x50;
          goto LAB_00405dc7;
        }
      }
      sub_436740(*puVar10,iVar9,CONCAT31((int3)((uint)iVar3 >> 8),DAT_006d9bec),_DAT_006d9bec & 0xff
                 ,_DAT_006d9bec & 0xff);
      if (iVar8 == 2) {
        iVar8 = 0x14;
        iVar9 = iVar9 + 0x14;
      }
      else if (iVar8 == 3) {
        iVar8 = 0x10;
        iVar9 = iVar9 + 0x10;
      }
      else {
        iVar9 = iVar9 + 0x18;
      }
      break;
    case 2:
      sub_436890(*puVar10,iVar9,0,0x20,CONCAT31(iVar5,DAT_006d9bec),_DAT_006d9bec & 0xff,
                 _DAT_006d9bec & 0xff,0);
      uVar4 = _DAT_006d9bec & 0xff;
      uVar6 = _DAT_006d9bec & 0xff;
      uVar7 = _DAT_006d9bec & 0xff;
      uVar11 = 0x100;
      goto LAB_00405ebb;
    case 3:
      sub_436890(*puVar10,iVar9,0,0x20,CONCAT31(iVar5,DAT_006d9bec),_DAT_006d9bec & 0xff,
                 _DAT_006d9bec & 0xff,0);
      uVar4 = _DAT_006d9bec & 0xff;
      uVar6 = _DAT_006d9bec & 0xff;
      uVar7 = _DAT_006d9bec & 0xff;
      uVar11 = 0x120;
      goto LAB_00405ebb;
    case 4:
      sub_436890(*puVar10,iVar9,0,0x50,CONCAT31(iVar5,DAT_006d9bec),_DAT_006d9bec & 0xff,
                 _DAT_006d9bec & 0xff,0);
      uVar4 = _DAT_006d9bec & 0xff;
      uVar6 = _DAT_006d9bec & 0xff;
      uVar7 = _DAT_006d9bec & 0xff;
      uVar11 = 0x130;
LAB_00405ebb:
      sub_436890(puVar10[1],iVar9,0,uVar11,uVar4,uVar7,uVar6,0);
      iVar9 = iVar9 + iVar8;
      break;
    case 6:
      sub_436740(*puVar10,iVar9,CONCAT31(iVar5,DAT_006d9bec),_DAT_006d9bec & 0xff,
                 _DAT_006d9bec & 0xff);
      iVar9 = iVar9 + iVar8;
      break;
    case 8:
      iVar9 = iVar9 + puVar10[1];
      break;
    case 9:
      DAT_006d9bd0 = 1;
    }
switchD_00405d87_caseD_5:
    cVar1 = *(char *)(puVar10 + 5);
    puVar10 = puVar10 + 3;
  } while( true );
}

