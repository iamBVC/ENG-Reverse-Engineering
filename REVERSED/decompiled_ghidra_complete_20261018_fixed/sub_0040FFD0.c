/* sub_40FFD0 @ 0040ffd0   854 bytes */

undefined4 sub_40FFD0(char *param_1,char *param_2,int param_3,int param_4,int *param_5,int *param_6)

{
  bool bVar1;
  char cVar2;
  char *pcVar3;
  int iVar4;
  int *piVar5;
  int *piVar6;
  int *piVar7;
  int *piVar8;
  int *piVar9;
  int *piVar10;
  int *piVar11;
  undefined4 *puVar12;
  bool bVar13;
  char *pcVar14;
  int *local_c;
  int *local_8;
  
  piVar5 = param_6;
  piVar6 = param_5;
  if (DAT_00582cc8 != '\0') {
    pcVar14 = param_1;
    pcVar3 = (char *)sub_405720(*(undefined4 *)(DAT_00583420 + 0xc));
    iVar4 = __strcmpi(pcVar3,pcVar14);
    if (iVar4 == 0) {
      pcVar14 = param_2;
      pcVar3 = (char *)sub_405720(*(undefined4 *)(DAT_00583424 + 0xc));
      iVar4 = __strcmpi(pcVar3,pcVar14);
      if (iVar4 == 0) {
        if (DAT_005833e0 == '\0') {
          if ((DAT_0058337c != param_3) || (DAT_00583374 != *piVar6)) goto LAB_00410061;
          iVar4 = piVar6[1];
        }
        else {
          if ((DAT_0058337c != param_4) || (DAT_00583374 != *piVar5)) goto LAB_00410061;
          iVar4 = piVar5[1];
        }
        if (DAT_00583378 == iVar4) {
          DAT_00583430 = 0;
          return 1;
        }
      }
    }
  }
LAB_00410061:
  sub_40FE10();
  for (piVar6 = DAT_00583410; (*piVar6 != 0 || (piVar6[1] == 0)); piVar6 = (int *)*piVar6) {
    iVar4 = sub_4134C0(piVar6,param_1);
    if (iVar4 == 0) goto LAB_004100be;
    if (0 < iVar4) break;
  }
  piVar6 = (int *)0x0;
LAB_004100be:
  bVar13 = piVar6 == (int *)0x0;
  if (bVar13) {
    piVar6 = DAT_00583410;
  }
  piVar5 = piVar6;
  if (piVar6 == (int *)0x0) {
    return 0;
  }
  do {
    cVar2 = sub_410550(piVar5);
    if (cVar2 != '\0') {
      for (piVar7 = (int *)piVar5[7]; (*piVar7 != 0 || (piVar7[1] == 0)); piVar7 = (int *)*piVar7) {
        iVar4 = sub_4134C0(piVar7,param_2);
        if (iVar4 == 0) goto LAB_00410120;
        if (0 < iVar4) break;
      }
      piVar7 = (int *)0x0;
LAB_00410120:
      bVar1 = bVar13;
      local_8 = piVar7;
      if (piVar7 == (int *)0x0) {
        piVar7 = (int *)piVar5[9];
        bVar13 = true;
        bVar1 = bVar13;
        local_8 = piVar7;
      }
      while (piVar7 != (int *)0x0) {
        if ((!bVar13) || ((char)piVar7[4] == '\0')) {
          puVar12 = &param_4;
          if ((char)piVar7[4] == '\0') {
            puVar12 = &param_3;
          }
          for (piVar8 = (int *)piVar7[0xb]; (*piVar8 != 0 || (piVar8[1] == 0));
              piVar8 = (int *)*piVar8) {
            iVar4 = sub_4136C0(piVar8,puVar12);
            if (iVar4 == 0) goto LAB_00410184;
            if (0 < iVar4) break;
          }
          piVar8 = (int *)0x0;
LAB_00410184:
          local_c = piVar8;
          if (piVar8 == (int *)0x0) {
            piVar8 = (int *)piVar7[0xb];
            if (piVar8 == piVar7 + 0xc) {
              piVar8 = (int *)0x0;
              local_c = piVar8;
            }
            else {
              for (piVar9 = (int *)*piVar8; (*piVar9 != 0 || (local_c = piVar8, piVar9[1] == 0));
                  piVar9 = (int *)*piVar9) {
                iVar4 = sub_4136D0(piVar9,piVar8,&param_3);
                if (0 < iVar4) {
                  piVar8 = piVar9;
                }
              }
            }
          }
          while (piVar8 != (int *)0x0) {
            piVar9 = param_6;
            if ((char)piVar7[4] == '\0') {
              piVar9 = param_5;
            }
            for (piVar10 = (int *)piVar8[0xc]; (*piVar10 != 0 || (piVar10[1] == 0));
                piVar10 = (int *)*piVar10) {
              iVar4 = sub_4137B0(piVar10,piVar9);
              if (iVar4 == 0) goto LAB_00410203;
              if (0 < iVar4) break;
            }
            piVar10 = (int *)0x0;
LAB_00410203:
            piVar9 = piVar10;
            if (piVar10 == (int *)0x0) {
              piVar10 = (int *)piVar8[0xc];
              if (piVar10 == piVar8 + 0xd) {
                piVar10 = (int *)0x0;
                piVar9 = piVar10;
              }
              else {
                for (piVar11 = (int *)*piVar10;
                    (*piVar11 != 0 || (piVar9 = piVar10, piVar11[1] == 0));
                    piVar11 = (int *)*piVar11) {
                  iVar4 = sub_4137D0(piVar11,piVar10,param_5);
                  if (0 < iVar4) {
                    piVar10 = piVar11;
                  }
                }
              }
            }
            while (piVar10 != (int *)0x0) {
              cVar2 = sub_410700(piVar8,piVar10,piVar5,piVar7);
              if (cVar2 != '\0') {
                cVar2 = sub_411000(piVar7);
                if (cVar2 != '\0') {
                  DAT_00582cc8 = 1;
                  sub_4114F0(piVar5,piVar7,piVar8,piVar10,bVar1);
                  sub_411620();
                  return 1;
                }
                sub_410ED0();
              }
              bVar1 = true;
              piVar10 = (int *)sub_413820(piVar9);
            }
            bVar1 = true;
            piVar8 = (int *)sub_413820(local_c);
          }
          bVar13 = true;
          bVar1 = true;
        }
        piVar7 = (int *)sub_413510(local_8);
      }
      sub_4106C0();
    }
    bVar13 = true;
    piVar5 = (int *)sub_413510(piVar6);
    if (piVar5 == (int *)0x0) {
      return 0;
    }
  } while( true );
}

