/* Selected Ghidra export at 00434ad0. */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_434AD0(void)

{
  float fVar1;
  float fVar2;
  ushort uVar3;
  char cVar4;
  uint uVar5;
  float fVar6;
  float *pfVar7;
  undefined4 *puVar8;
  code *pcVar9;
  int iVar10;
  undefined4 uVar11;
  ushort *puVar12;
  int iVar13;
  int *piVar14;
  char cStack_6b;
  char cStack_6a;
  undefined1 uStack_69;
  uint uStack_68;
  float fStack_64;
  int iStack_60;
  float fStack_5c;
  float fStack_58;
  float fStack_54;
  float fStack_50;
  ushort *puStack_4c;
  float fStack_48;
  float fStack_44;
  float fStack_40;
  float fStack_3c;
  uint uStack_38;
  float fStack_34;
  float fStack_30;
  int *piStack_2c;
  int iStack_28;
  uint uStack_24;
  uint uStack_20;
  uint uStack_1c;
  float fStack_18;
  float fStack_14;
  float fStack_10;
  float fStack_8;
  float fStack_4;
  
  puVar12 = (ushort *)(DAT_00581154 + (DAT_006d9be8 * 5 + 10) * 4);
  iStack_60 = (char)(byte)puVar12[1] * 0x20 + DAT_0058114c;
  uStack_1c = 0;
  iVar13 = ((*puVar12 & 0x7000) >> 0xc) + (*puVar12 >> 8 & 7) * 5;
  uStack_38 = (&DAT_00573ef8)[iVar13 * 3];
  uStack_68 = (&DAT_00573efc)[iVar13 * 3];
  piVar14 = DAT_006d94b8;
  puStack_4c = puVar12;
  if (DAT_006da320 != 0) {
    do {
      if ((char)piVar14[4] != '\0') {
        fVar1 = (float)*piVar14 * (float)_DAT_0056e020;
        fVar6 = (float)piVar14[1] * (float)_DAT_0056e020;
        fVar2 = -((float)piVar14[2] * (float)_DAT_0056e020);
        fStack_18 = _DAT_0057dc28 * fVar1 + _DAT_0057dc38 * fVar6 + _DAT_0057dc48 * fVar2 +
                    _DAT_0057dc58;
        fStack_14 = _DAT_0057dc2c * fVar1 + _DAT_0057dc3c * fVar6 + _DAT_0057dc4c * fVar2 +
                    _DAT_0057dc5c;
        fStack_10 = _DAT_0057dc30 * fVar1 + _DAT_0057dc40 * fVar6 + _DAT_0057dc50 * fVar2 +
                    _DAT_0057dc60;
        piStack_2c = piVar14;
        uVar5 = sub_401000(&fStack_18);
        if ((uVar5 & 0x10) == 0) {
          if ((uVar5 & 0x20) == 0) {
            if ((((fStack_14 < fStack_10 * _DAT_0056e440) || (fStack_18 < fStack_10 * _DAT_0056e440)
                 ) || (fStack_10 * _DAT_0056e154 < fStack_18)) ||
               (-(int)*(short *)((int)piVar14 + 0x12) < 7)) {
              *(undefined1 *)(piVar14 + 4) = 0;
            }
            else {
              cStack_6b = __ftol();
              cStack_6b = -1 - cStack_6b;
              uStack_24 = CONCAT31(uStack_24._1_3_,cStack_6b);
              uStack_20 = CONCAT31(uStack_20._1_3_,cStack_6b);
              (*(code *)PTR_sub_408390_00570360)(&cStack_6b,&uStack_24,&uStack_20,&uStack_69,2);
              cStack_6a = sub_40C510(&cStack_6b,&uStack_24,&uStack_20);
              fStack_64 = _DAT_0056e008 / fStack_10;
              fVar6 = (float)(((uint)CONCAT11(uStack_69,cStack_6b) << 8 | uStack_24 & 0xff) << 8 |
                             uStack_20 & 0xff);
              fVar1 = (fStack_64 * fStack_18 + _DAT_0056e008) * _DAT_00583388;
              fStack_8 = (_DAT_0056e008 - fStack_64 * fStack_14) * _DAT_0058338c;
              fStack_4 = (fStack_10 - _DAT_0057d70c) * _DAT_0057d7fc * _DAT_0057f914 * fStack_64;
              fStack_34 = (float)DAT_00583374;
              fStack_58 = fStack_34 * fStack_64 * _DAT_0056e444;
              fStack_30 = (float)DAT_00583378;
              fStack_50 = fStack_30 * fStack_64 * _DAT_0056e444;
              fStack_5c = fVar1 - fStack_58;
              fStack_58 = fStack_58 + fVar1;
              fStack_54 = fStack_8 - fStack_50;
              fStack_50 = fStack_50 + fStack_8;
              if (((fStack_5c < fStack_34) && (_DAT_0056e00c < fStack_58)) &&
                 ((fStack_54 < fStack_30 && (_DAT_0056e00c < fStack_50)))) {
                fStack_48 = *(float *)(puVar12 + 2);
                fStack_44 = *(float *)(puVar12 + 4);
                fStack_40 = *(float *)(puVar12 + 6);
                fStack_3c = *(float *)(puVar12 + 8);
                if (fStack_5c < _DAT_0056e00c) {
                  fVar2 = -fStack_5c;
                  fVar1 = fStack_58 - fStack_5c;
                  fStack_5c = 0.0;
                  fStack_48 = (fVar2 * (fStack_44 - fStack_48)) / fVar1 + fStack_48;
                }
                if (fStack_34 < fStack_58) {
                  fStack_44 = ((fStack_34 - fStack_58) * (fStack_44 - fStack_48)) /
                              (fStack_58 - fStack_5c) + fStack_44;
                  fStack_58 = fStack_34;
                }
                if (fStack_54 < _DAT_0056e00c) {
                  fVar2 = -fStack_54;
                  fVar1 = fStack_50 - fStack_54;
                  fStack_54 = 0.0;
                  fStack_40 = (fVar2 * (fStack_3c - fStack_40)) / fVar1 + fStack_40;
                }
                if (fStack_30 < fStack_50) {
                  fStack_3c = ((fStack_30 - fStack_50) * (fStack_3c - fStack_40)) /
                              (fStack_50 - fStack_54) + fStack_3c;
                  fStack_50 = fStack_30;
                }
                if ((DAT_005833e4._1_1_ == '\0') ||
                   ((uStack_38 == 0 && (((*puVar12 & 2) == 0 || (DAT_00573d36 == '\0')))))) {
                  iVar13 = -1;
                  pfVar7 = (float *)&DAT_005ff250;
                }
                else {
                  iVar13 = 0;
                  iStack_28 = __ftol();
                  if (iStack_28 < 0) {
                    iStack_28 = 0;
                  }
                  else if (0x7ff < iStack_28) {
                    iStack_28 = 0x7ff;
                  }
                  pfVar7 = (float *)sub_41ED90(0x80);
                  puVar12 = puStack_4c;
                  piVar14 = piStack_2c;
                  if (pfVar7 == (float *)0x0) goto LAB_004350f3;
                }
                iVar10 = iStack_60;
                pfVar7[0x18] = fStack_5c;
                *pfVar7 = fStack_5c;
                pfVar7[0x10] = fStack_58;
                pfVar7[8] = fStack_58;
                pfVar7[1] = fStack_54;
                pfVar7[9] = fStack_54;
                pfVar7[0x19] = fStack_50;
                pfVar7[0x11] = fStack_50;
                pfVar7[0x12] = fStack_4;
                pfVar7[0x1a] = fStack_4;
                pfVar7[10] = fStack_4;
                pfVar7[2] = fStack_4;
                pfVar7[0x13] = fStack_64;
                pfVar7[0x1b] = fStack_64;
                pfVar7[3] = fStack_64;
                pfVar7[0xb] = fStack_64;
                pfVar7[0x1e] = fStack_48;
                pfVar7[6] = fStack_48;
                pfVar7[0xe] = fStack_44;
                pfVar7[0x16] = fStack_44;
                pfVar7[0xf] = fStack_40;
                pfVar7[0x1c] = fVar6;
                pfVar7[0x14] = fVar6;
                pfVar7[0xc] = fVar6;
                pfVar7[4] = fVar6;
                pfVar7[0x1d] = 0.0;
                pfVar7[0x15] = 0.0;
                pfVar7[0xd] = 0.0;
                pfVar7[5] = 0.0;
                pfVar7[7] = fStack_40;
                pfVar7[0x1f] = fStack_3c;
                pfVar7[0x17] = fStack_3c;
                if (iVar13 == -1) {
                  uVar3 = *puStack_4c;
                  if (DAT_005833e1 == '\0') {
                    if (iStack_60 == 0) {
                      if (DAT_006d7c58 != 1) {
                        (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,1);
                        DAT_006d7c58 = 1;
                      }
                    }
                    else {
                      if (DAT_006d7c54 != *(int *)(iStack_60 + 0x10)) {
                        (**(code **)(*DAT_00582cd4 + 0x98))
                                  (DAT_00582cd4,0,*(int *)(iStack_60 + 0x10));
                        DAT_006d7c54 = *(int *)(iVar10 + 0x10);
                      }
                      if (DAT_006d7c58 != (-(uint)(DAT_005833f0 != '\0') & 2) + 2) {
                        (**(code **)(*DAT_00582cd4 + 0xa0))
                                  (DAT_00582cd4,0,1,(-(DAT_005833f0 != '\0') & 2U) + 2);
                        if (DAT_005833f0 == '\0') {
                          DAT_006d7c58 = 2;
                        }
                        else {
                          DAT_006d7c58 = 4;
                        }
                      }
                    }
                    if (DAT_006d7c34 != 1) {
                      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,9,1);
                      DAT_006d7c34 = 1;
                    }
                    if (DAT_006d7c38 != '\x01') {
                      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xb,1);
                      DAT_006d7c38 = '\x01';
                    }
                    if ((((uVar3 & 2) == 0) || (DAT_006d7c6e == '\0')) || ((uStack_68 & 2) != 0)) {
                      cVar4 = '\0';
                    }
                    else {
                      cVar4 = '\x01';
                    }
                    if (DAT_006d7c4e != cVar4) {
                      if ((((uVar3 & 2) == 0) || (DAT_006d7c6e == '\0')) || ((uStack_68 & 2) != 0))
                      {
                        uVar11 = 0;
                      }
                      else {
                        uVar11 = 1;
                      }
                      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x29,uVar11);
                      if ((((uVar3 & 2) == 0) || (DAT_006d7c6e == '\0')) ||
                         (DAT_006d7c4e = '\x01', (uStack_68 & 2) != 0)) {
                        DAT_006d7c4e = '\0';
                      }
                    }
                    if (DAT_006d7c30 != '\x01') {
                      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,7,1);
                      DAT_006d7c30 = '\x01';
                    }
                    if (DAT_006d7c39 != '\x01') {
                      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xe,1);
                      DAT_006d7c39 = '\x01';
                    }
                    if (DAT_006d7c48 != 4) {
                      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x17,4);
                      DAT_006d7c48 = 4;
                    }
                    if (((uVar3 & 2) == 0) || (DAT_006d7c70 == '\0')) {
                      cVar4 = '\0';
                    }
                    else {
                      cVar4 = '\x01';
                    }
                    if (DAT_006d7c3a != cVar4) {
                      if (((uVar3 & 2) == 0) || (DAT_006d7c70 == '\0')) {
                        uVar11 = 0;
                      }
                      else {
                        uVar11 = 1;
                      }
                      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xf,uVar11);
                      if (((uVar3 & 2) == 0) || (DAT_006d7c3a = '\x01', DAT_006d7c70 == '\0')) {
                        DAT_006d7c3a = '\0';
                      }
                    }
                    if (DAT_006d7c50 != 0) {
                      (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x2f,0);
                      DAT_006d7c50 = 0;
                    }
                    switch(uStack_38) {
                    case 0:
                      if (DAT_005833fa == '\0') {
                        if (DAT_006d7c4c != '\0') {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,0);
                          DAT_006d7c4c = '\0';
                        }
                      }
                      else if (DAT_006d7c4d != '\0') {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,0);
                        DAT_006d7c4d = '\0';
                      }
                      break;
                    case 1:
                      if (DAT_005833fa == '\0') {
                        if (DAT_006d7c4c != '\x01') {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
                          DAT_006d7c4c = '\x01';
                        }
                      }
                      else if (DAT_006d7c4d != '\x01') {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
                        DAT_006d7c4d = '\x01';
                      }
                      iVar13 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
                      if (DAT_006d7c40 != iVar13) {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,iVar13);
                        DAT_006d7c40 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
                      }
                      if (DAT_006d7c44 != 6) {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,6);
                        DAT_006d7c44 = 6;
                      }
                      break;
                    case 2:
                      if (DAT_005833fa == '\0') {
                        if (DAT_006d7c4c != '\x01') {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
                          DAT_006d7c4c = '\x01';
                        }
                      }
                      else if (DAT_006d7c4d != '\x01') {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
                        DAT_006d7c4d = '\x01';
                      }
                      if (DAT_006d7c40 != 2) {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,2);
                        DAT_006d7c40 = 2;
                      }
                      if (DAT_006d7c44 != 2) {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,2);
                        DAT_006d7c44 = 2;
                      }
                      break;
                    case 3:
                      if (DAT_005833fa == '\0') {
                        if (DAT_006d7c4c != '\x01') {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
                          DAT_006d7c4c = '\x01';
                        }
                      }
                      else if (DAT_006d7c4d != '\x01') {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
                        DAT_006d7c4d = '\x01';
                      }
                      if (DAT_006d7c40 != 5) {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,5);
                        DAT_006d7c40 = 5;
                      }
                      if (DAT_006d7c44 != 2) {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,2);
                        DAT_006d7c44 = 2;
                      }
                    }
                    switch(uStack_68) {
                    case 0:
                    case 2:
                      if (DAT_006d7c5c != 2) {
                        (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,2);
                        DAT_006d7c5c = 2;
                      }
                      break;
                    case 1:
                      if (DAT_006d7c5c != 3) {
                        (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,3);
                        DAT_006d7c5c = 3;
                      }
                      break;
                    case 3:
                      if (DAT_006d7c5c != 4) {
                        (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,4);
                        DAT_006d7c5c = 4;
                      }
                    }
                    (**(code **)(*DAT_00582cd4 + 0x70))(DAT_00582cd4,6,0x1c4,pfVar7,4,0x1c);
                  }
                  else {
                    iVar13 = (uStack_38 * 4 | uStack_68) << 5;
                    if (iStack_60 == 0) {
                      uVar11 = 0;
                    }
                    else {
                      uVar11 = *(undefined4 *)(iStack_60 + 0x1c);
                    }
                    pcVar9 = sub_4C6CD0;
                    if (DAT_00583380 == '\0') {
                      pcVar9 = sub_442BD0;
                    }
                    (*pcVar9)(DAT_0058331c,DAT_005832f0,uVar11,DAT_00583308 >> 1,DAT_00583374,pfVar7
                              ,4,1,0,CONCAT31((int3)((uint)iVar13 >> 8),
                                              (byte)iVar13 | -((uVar3 & 2) != 0) & 4U) | 3);
                  }
                  puVar12 = puStack_4c;
                  piVar14 = piStack_2c;
                  if (cStack_6a != '\0') {
                    uVar5 = uStack_38 | 2;
                    uVar3 = *puStack_4c;
                    if (DAT_005833e1 == '\0') {
                      if (iStack_60 == 0) {
                        if (DAT_006d7c58 != 1) {
                          (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,1);
                          DAT_006d7c58 = 1;
                        }
                      }
                      else {
                        if (DAT_006d7c54 != *(int *)(iStack_60 + 0x10)) {
                          (**(code **)(*DAT_00582cd4 + 0x98))
                                    (DAT_00582cd4,0,*(int *)(iStack_60 + 0x10));
                          DAT_006d7c54 = *(int *)(iStack_60 + 0x10);
                        }
                        if (DAT_006d7c58 != (-(uint)(DAT_005833f0 != '\0') & 2) + 2) {
                          (**(code **)(*DAT_00582cd4 + 0xa0))
                                    (DAT_00582cd4,0,1,(-(DAT_005833f0 != '\0') & 2U) + 2);
                          if (DAT_005833f0 == '\0') {
                            DAT_006d7c58 = 2;
                          }
                          else {
                            DAT_006d7c58 = 4;
                          }
                        }
                      }
                      if (DAT_006d7c34 != 1) {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,9,1);
                        DAT_006d7c34 = 1;
                      }
                      if (DAT_006d7c38 != '\x01') {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xb,1);
                        DAT_006d7c38 = '\x01';
                      }
                      if ((((uVar3 & 2) == 0) || (DAT_006d7c6e == '\0')) || ((uStack_68 & 2) != 0))
                      {
                        cVar4 = '\0';
                      }
                      else {
                        cVar4 = '\x01';
                      }
                      if (DAT_006d7c4e != cVar4) {
                        if ((((uVar3 & 2) == 0) || (DAT_006d7c6e == '\0')) || ((uStack_68 & 2) != 0)
                           ) {
                          uVar11 = 0;
                        }
                        else {
                          uVar11 = 1;
                        }
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x29,uVar11);
                        if ((((uVar3 & 2) == 0) || (DAT_006d7c6e == '\0')) ||
                           (DAT_006d7c4e = '\x01', (uStack_68 & 2) != 0)) {
                          DAT_006d7c4e = '\0';
                        }
                      }
                      if (DAT_006d7c30 != '\x01') {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,7,1);
                        DAT_006d7c30 = '\x01';
                      }
                      if (DAT_006d7c39 != '\x01') {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xe,1);
                        DAT_006d7c39 = '\x01';
                      }
                      if (DAT_006d7c48 != 4) {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x17,4);
                        DAT_006d7c48 = 4;
                      }
                      if (((uVar3 & 2) == 0) || (DAT_006d7c70 == '\0')) {
                        cVar4 = '\0';
                      }
                      else {
                        cVar4 = '\x01';
                      }
                      if (DAT_006d7c3a != cVar4) {
                        if (((uVar3 & 2) == 0) || (DAT_006d7c70 == '\0')) {
                          uVar11 = 0;
                        }
                        else {
                          uVar11 = 1;
                        }
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xf,uVar11);
                        if (((uVar3 & 2) == 0) || (DAT_006d7c3a = '\x01', DAT_006d7c70 == '\0')) {
                          DAT_006d7c3a = '\0';
                        }
                      }
                      if (DAT_006d7c50 != 0) {
                        (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x2f,0);
                        DAT_006d7c50 = 0;
                      }
                      switch(uVar5) {
                      case 0:
                        if (DAT_005833fa == '\0') {
                          if (DAT_006d7c4c != '\0') {
                            (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,0);
                            DAT_006d7c4c = '\0';
                          }
                        }
                        else if (DAT_006d7c4d != '\0') {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,0);
                          DAT_006d7c4d = '\0';
                        }
                        break;
                      case 1:
                        if (DAT_005833fa == '\0') {
                          if (DAT_006d7c4c != '\x01') {
                            (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
                            DAT_006d7c4c = '\x01';
                          }
                        }
                        else if (DAT_006d7c4d != '\x01') {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
                          DAT_006d7c4d = '\x01';
                        }
                        iVar13 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
                        if (DAT_006d7c40 != iVar13) {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,iVar13);
                          DAT_006d7c40 = (-(uint)(DAT_006d7c6f != '\0') & 0xfffffffd) + 5;
                        }
                        if (DAT_006d7c44 != 6) {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,6);
                          DAT_006d7c44 = 6;
                        }
                        break;
                      case 2:
                        if (DAT_005833fa == '\0') {
                          if (DAT_006d7c4c != '\x01') {
                            (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
                            DAT_006d7c4c = '\x01';
                          }
                        }
                        else if (DAT_006d7c4d != '\x01') {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
                          DAT_006d7c4d = '\x01';
                        }
                        if (DAT_006d7c40 != 2) {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,2);
                          DAT_006d7c40 = 2;
                        }
                        if (DAT_006d7c44 != 2) {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,2);
                          DAT_006d7c44 = 2;
                        }
                        break;
                      case 3:
                        if (DAT_005833fa == '\0') {
                          if (DAT_006d7c4c != '\x01') {
                            (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x1b,1);
                            DAT_006d7c4c = '\x01';
                          }
                        }
                        else if (DAT_006d7c4d != '\x01') {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x27,1);
                          DAT_006d7c4d = '\x01';
                        }
                        if (DAT_006d7c40 != 5) {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x13,5);
                          DAT_006d7c40 = 5;
                        }
                        if (DAT_006d7c44 != 2) {
                          (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x14,2);
                          DAT_006d7c44 = 2;
                        }
                      }
                      switch(uStack_68) {
                      case 0:
                      case 2:
                        if (DAT_006d7c5c != 2) {
                          (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,2);
                          DAT_006d7c5c = 2;
                        }
                        break;
                      case 1:
                        if (DAT_006d7c5c != 3) {
                          (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,3);
                          DAT_006d7c5c = 3;
                        }
                        break;
                      case 3:
                        if (DAT_006d7c5c != 4) {
                          (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,4);
                          DAT_006d7c5c = 4;
                        }
                      }
                      (**(code **)(*DAT_00582cd4 + 0x70))(DAT_00582cd4,6,0x1c4,pfVar7,4,0x1c);
                      puVar12 = puStack_4c;
                      piVar14 = piStack_2c;
                    }
                    else {
                      iVar13 = (uVar5 * 4 | uStack_68) << 5;
                      if (iStack_60 == 0) {
                        uVar11 = 0;
                      }
                      else {
                        uVar11 = *(undefined4 *)(iStack_60 + 0x1c);
                      }
                      pcVar9 = sub_4C6CD0;
                      if (DAT_00583380 == '\0') {
                        pcVar9 = sub_442BD0;
                      }
                      (*pcVar9)(DAT_0058331c,DAT_005832f0,uVar11,DAT_00583308 >> 1,DAT_00583374,
                                pfVar7,4,1,0,
                                CONCAT31((int3)((uint)iVar13 >> 8),
                                         (byte)iVar13 | -((uVar3 & 2) != 0) & 4U) | 3);
                      puVar12 = puStack_4c;
                      piVar14 = piStack_2c;
                    }
                  }
                }
                else {
                  if (cStack_6a != '\0') {
                    uVar3 = *puStack_4c;
                    puVar8 = (undefined4 *)sub_41ED90(0x20);
                    if (puVar8 != (undefined4 *)0x0) {
                      iVar10 = iVar13 * 0x800 + iStack_28;
                      uVar11 = (&DAT_005f6ef8)[iVar10];
                      puVar8[3] = 0;
                      *puVar8 = uVar11;
                      puVar8[5] = iStack_60;
                      puVar8[4] = 0;
                      puVar8[6] = 0;
                      puVar8[1] = pfVar7;
                      puVar8[2] = 4;
                      puVar8[7] = (uStack_68 << 2 | uStack_38) << 0xc |
                                  -(uint)((uVar3 & 2) != 0) & 0x10 | 0x204f;
                      (&DAT_005f6ef8)[iVar10] = puVar8;
                    }
                  }
                  uVar3 = *puStack_4c;
                  puVar8 = (undefined4 *)sub_41ED90(0x20);
                  puVar12 = puStack_4c;
                  piVar14 = piStack_2c;
                  if (puVar8 != (undefined4 *)0x0) {
                    iVar13 = iVar13 * 0x800 + iStack_28;
                    *puVar8 = (&DAT_005f6ef8)[iVar13];
                    puVar8[1] = pfVar7;
                    puVar8[5] = iStack_60;
                    puVar8[2] = 4;
                    puVar8[3] = 0;
                    puVar8[4] = 0;
                    puVar8[6] = 0;
                    puVar8[7] = (uStack_68 << 2 | uStack_38) << 0xc |
                                -(uint)((uVar3 & 2) != 0) & 0x10 | 0x4f;
                    (&DAT_005f6ef8)[iVar13] = puVar8;
                  }
                }
              }
            }
          }
          else {
            *(undefined1 *)(piVar14 + 4) = 0;
          }
        }
      }
LAB_004350f3:
      uStack_1c = uStack_1c + 1;
      piVar14 = piVar14 + 8;
    } while (uStack_1c < DAT_006da320);
  }
  return;
}

