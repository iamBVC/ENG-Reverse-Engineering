/* sub_43C220 @ 0043c220   1419 bytes */

void sub_43C220(undefined4 param_1)

{
  byte *pbVar1;
  int iVar2;
  byte *pbVar3;
  int iVar4;
  void *pvVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int *piVar10;
  undefined4 *puVar11;
  undefined4 *puVar12;
  undefined4 *puVar13;
  void *local_8c;
  int local_88;
  undefined1 local_84 [8];
  undefined4 local_7c [18];
  undefined4 local_34 [8];
  uint local_14;
  int local_10;
  
  sub_40D2C0();
  iVar4 = sub_415690(0,param_1);
  if ((iVar4 != 0) && (iVar4 = sub_562AEE(iVar4,&DAT_00570350), iVar4 != 0)) {
    sub_43AD50();
    sub_43B920(&DAT_006d8740,iVar4);
    sub_43B920(&DAT_00584a4c,iVar4);
    sub_43B920(&DAT_005849b4,iVar4);
    sub_43B920(&DAT_005849b0,iVar4);
    sub_43B920(&DAT_005849ac,iVar4);
    sub_43C1B0(DAT_00584a4c);
    sub_43C1B0(DAT_005849b4);
    sub_43C1B0(DAT_005849b0);
    sub_43C1B0(DAT_005849ac);
    puVar12 = &DAT_00584a54;
    do {
      sub_43B920(puVar12,iVar4);
      sub_43C1B0(*puVar12);
      puVar12 = puVar12 + 1;
    } while ((int)puVar12 < 0x584a74);
    puVar12 = &DAT_005849bc;
    do {
      sub_43B920(puVar12,iVar4);
      sub_43C1B0(*puVar12);
      puVar12 = puVar12 + 1;
    } while ((int)puVar12 < 0x5849c8);
    puVar12 = &DAT_00584a78;
    do {
      sub_43B920(puVar12,iVar4);
      sub_43C1B0(*puVar12);
      puVar12 = puVar12 + 1;
    } while ((int)puVar12 < 0x584a88);
    local_8c = _malloc(480000);
    iVar8 = 0;
    do {
      iVar7 = 0;
      local_88 = iVar8 * 0xb;
      do {
        sub_563DDC(iVar4,local_84);
        pvVar5 = _malloc(0x218);
        piVar10 = &DAT_00584a8c + local_88 + iVar7;
        *piVar10 = (int)pvVar5;
        sub_5629E6(pvVar5,0x218,1,iVar4);
        *(undefined4 *)(*piVar10 + 0x214) = 0;
        if (iVar7 == 0) {
          pvVar5 = _malloc((int)*(short *)((&DAT_00584a8c)[iVar8 * 0xb] + 0xe) *
                           (int)*(short *)((&DAT_00584a8c)[iVar8 * 0xb] + 0xc) * 3);
          *(void **)((&DAT_00584a8c)[iVar8 * 0xb] + 0x214) = pvVar5;
          iVar9 = (&DAT_00584a8c)[iVar8 * 0xb];
          sub_5629E6(*(undefined4 *)(iVar9 + 0x214),
                     (int)*(short *)(iVar9 + 0xe) * (int)*(short *)(iVar9 + 0xc) * 3,1,iVar4);
        }
        else {
          iVar9 = *piVar10;
          if (0 < (int)*(short *)(iVar9 + 0xe) * (int)*(short *)(iVar9 + 0xc)) {
            sub_5628BC(iVar9);
            sub_563DC4(iVar4,local_84);
            sub_43B920(piVar10,iVar4);
          }
        }
        iVar7 = iVar7 + 1;
      } while (iVar7 < 6);
      iVar7 = 6;
      local_88 = iVar8 * 0x2c;
      piVar10 = &DAT_00584aa4 + iVar8 * 0xb;
      do {
        pvVar5 = _malloc(0x218);
        *piVar10 = (int)pvVar5;
        sub_5629E6(pvVar5,0x218,1,iVar4);
        iVar9 = *piVar10;
        if (0 < (int)*(short *)(iVar9 + 0xe) * (int)*(short *)(iVar9 + 0xc)) {
          *(void **)(iVar9 + 0x214) = local_8c;
          iVar9 = *piVar10;
          sub_5629E6(*(undefined4 *)(iVar9 + 0x214),
                     (int)*(short *)(iVar9 + 0xe) * (int)*(short *)(iVar9 + 0xc) * 3,1,iVar4);
        }
        if ((((iVar8 < (int)(DAT_00585018 & 0xff)) && (iVar7 + -6 < (int)(DAT_00585018 >> 8 & 0xff))
             ) || (iVar8 + 1 < (int)(DAT_00585018 & 0xff))) &&
           (iVar9 = *piVar10, 0 < (int)*(short *)(iVar9 + 0xe) * (int)*(short *)(iVar9 + 0xc))) {
          sub_43C100(*(undefined4 *)((int)&DAT_00584a8c + local_88),iVar9);
        }
        iVar9 = *piVar10;
        iVar7 = iVar7 + 1;
        piVar10 = piVar10 + 1;
        *(undefined4 *)(iVar9 + 0x214) = 0;
      } while (iVar7 < 0xb);
      iVar8 = iVar8 + 1;
    } while (iVar8 < 8);
    sub_5628BC(local_8c);
    sub_5628EB(iVar4);
    piVar10 = &DAT_00584a8c;
    do {
      if (*(int *)(*piVar10 + 0x214) != 0) {
        sub_43C1B0(*piVar10);
      }
      piVar10 = piVar10 + 1;
    } while ((int)piVar10 < 0x584bec);
    local_8c = (void *)0x0;
    if (DAT_005833e1 == '\0') {
      if (0 < DAT_006d8748) {
        puVar12 = &DAT_006d8754;
        while( true ) {
          puVar11 = local_7c;
          for (iVar4 = 0x1f; iVar4 != 0; iVar4 = iVar4 + -1) {
            *puVar11 = 0;
            puVar11 = puVar11 + 1;
          }
          local_7c[0] = 0x7c;
          local_7c[1] = 0x1007;
          local_7c[3] = 0x100;
          local_7c[2] = 0x100;
          iVar4 = 8;
          puVar11 = (undefined4 *)PTR_DAT_005703b0;
          if (DAT_005833f9 == '\0') {
            puVar11 = (undefined4 *)PTR_DAT_00570430;
          }
          puVar13 = local_34;
          for (; iVar4 != 0; iVar4 = iVar4 + -1) {
            *puVar13 = *puVar11;
            puVar11 = puVar11 + 1;
            puVar13 = puVar13 + 1;
          }
          local_14 = (-(uint)(DAT_005833e1 != '\0') & 0xfffff040) + 0x1000 |
                     -(uint)(DAT_005833e0 != '\0') & 0x800;
          local_10 = (-(uint)(DAT_005833e0 != '\0') & 0xfffffff0) + 0x10;
          iVar4 = (**(code **)(*DAT_00582ccc + 0x18))(DAT_00582ccc,local_7c,puVar12,0);
          if (iVar4 != 0) break;
          if (DAT_005833f9 == '\0') {
            uVar6 = sub_40D130(*puVar12,0x70b0d0);
            sub_43B080(*puVar12,&local_8c,puVar12[1],uVar6,4);
            sub_40D230(*puVar12,0x70b0d0);
          }
          else {
            sub_43B080(*puVar12,&local_8c,puVar12[1],0,4);
          }
          iVar4 = (*(code *)**(undefined4 **)*puVar12)
                            ((undefined4 *)*puVar12,&DAT_0056e6dc,puVar12 + -1);
          if (iVar4 != 0) {
            return;
          }
          local_8c = (void *)((int)local_8c + 1);
          puVar12 = puVar12 + 0x25;
          if (DAT_006d8748 <= (int)local_8c) {
            return;
          }
        }
        sub_406740(1);
      }
    }
    else if (0 < DAT_006d8748) {
      piVar10 = &DAT_006d875c;
      do {
        pvVar5 = _malloc(0x20000);
        *piVar10 = (int)pvVar5;
        if (DAT_00583380 == '\0') {
          iVar8 = 0;
          iVar4 = 0;
          do {
            iVar9 = 0x100;
            iVar7 = iVar4;
            do {
              iVar4 = iVar7 + 2;
              iVar2 = iVar8 + 1;
              pbVar1 = (byte *)(iVar8 + piVar10[-1]);
              iVar8 = iVar8 + 4;
              iVar9 = iVar9 + -1;
              *(ushort *)(iVar7 + *piVar10) =
                   ((ushort)(*pbVar1 & 0xf8) << 5 | (ushort)(*(byte *)(iVar2 + piVar10[-1]) & 0xf8))
                   << 2 | (ushort)(pbVar1[2] >> 3);
              iVar7 = iVar4;
            } while (iVar9 != 0);
          } while (iVar4 < 0x20000);
        }
        else {
          iVar8 = 0;
          iVar4 = 0;
          do {
            iVar7 = 0x100;
            do {
              iVar4 = iVar4 + 2;
              pbVar3 = (byte *)(piVar10[-1] + 1 + iVar8);
              pbVar1 = (byte *)(piVar10[-1] + iVar8);
              iVar8 = iVar8 + 4;
              iVar7 = iVar7 + -1;
              *(ushort *)(*piVar10 + -2 + iVar4) =
                   ((ushort)(*pbVar1 & 0xf8) << 5 | (ushort)(*pbVar3 & 0xfc)) << 3 |
                   (ushort)(pbVar1[2] >> 3);
            } while (iVar7 != 0);
          } while (iVar4 < 0x20000);
        }
        local_8c = (void *)((int)local_8c + 1);
        piVar10 = piVar10 + 0x25;
      } while ((int)local_8c < DAT_006d8748);
      return;
    }
  }
  return;
}

