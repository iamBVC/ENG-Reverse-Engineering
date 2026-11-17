/* sub_401820 @ 00401820   3820 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sub_401820(int param_1,int param_2)

{
  float *pfVar1;
  ushort *puVar2;
  ushort uVar3;
  float *pfVar4;
  float fVar5;
  code *pcVar6;
  uint uVar7;
  uint uVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  undefined4 uVar11;
  byte bVar12;
  int iVar13;
  uint uVar14;
  int iVar15;
  float *pfVar16;
  uint uVar17;
  uint uVar18;
  bool bVar19;
  int local_1c;
  int local_18;
  int local_c;
  byte *local_8;
  undefined4 *local_4;
  
  sub_41E990(param_2,0x40000000,0x40000000,0x40000000,&DAT_006d7b68);
  _DAT_006d7be8 =
       _DAT_0057db20 * _DAT_006d7b68 +
       _DAT_0057db30 * _DAT_006d7b6c + _DAT_0057db40 * _DAT_006d7b70 + _DAT_0057db50 * _DAT_006d7b74
  ;
  _DAT_006d7bec =
       _DAT_0057db54 * _DAT_006d7b74 +
       _DAT_0057db24 * _DAT_006d7b68 + _DAT_0057db34 * _DAT_006d7b6c + _DAT_0057db44 * _DAT_006d7b70
  ;
  _DAT_006d7bf0 =
       _DAT_0057db28 * _DAT_006d7b68 +
       _DAT_0057db38 * _DAT_006d7b6c + _DAT_0057db48 * _DAT_006d7b70 + _DAT_0057db58 * _DAT_006d7b74
  ;
  _DAT_006d7bf4 =
       _DAT_0057db2c * _DAT_006d7b68 +
       _DAT_0057db3c * _DAT_006d7b6c + _DAT_0057db4c * _DAT_006d7b70 + _DAT_0057db5c * _DAT_006d7b74
  ;
  _DAT_006d7bf8 =
       _DAT_006d7b78 * _DAT_0057db20 +
       _DAT_006d7b7c * _DAT_0057db30 + _DAT_006d7b80 * _DAT_0057db40 + _DAT_006d7b84 * _DAT_0057db50
  ;
  _DAT_006d7bfc =
       _DAT_006d7b78 * _DAT_0057db24 +
       _DAT_006d7b7c * _DAT_0057db34 + _DAT_006d7b80 * _DAT_0057db44 + _DAT_006d7b84 * _DAT_0057db54
  ;
  _DAT_006d7c00 =
       _DAT_006d7b78 * _DAT_0057db28 +
       _DAT_006d7b7c * _DAT_0057db38 + _DAT_006d7b80 * _DAT_0057db48 + _DAT_006d7b84 * _DAT_0057db58
  ;
  _DAT_006d7c04 =
       _DAT_006d7b78 * _DAT_0057db2c +
       _DAT_006d7b7c * _DAT_0057db3c + _DAT_006d7b80 * _DAT_0057db4c + _DAT_006d7b84 * _DAT_0057db5c
  ;
  _DAT_006d7c08 =
       _DAT_006d7b88 * _DAT_0057db20 +
       _DAT_006d7b8c * _DAT_0057db30 + _DAT_006d7b90 * _DAT_0057db40 + _DAT_006d7b94 * _DAT_0057db50
  ;
  _DAT_006d7c0c =
       _DAT_006d7b88 * _DAT_0057db24 +
       _DAT_006d7b8c * _DAT_0057db34 + _DAT_006d7b90 * _DAT_0057db44 + _DAT_006d7b94 * _DAT_0057db54
  ;
  _DAT_006d7c10 =
       _DAT_006d7b88 * _DAT_0057db28 +
       _DAT_006d7b8c * _DAT_0057db38 + _DAT_006d7b90 * _DAT_0057db48 + _DAT_006d7b94 * _DAT_0057db58
  ;
  _DAT_006d7c14 =
       _DAT_006d7b88 * _DAT_0057db2c +
       _DAT_006d7b8c * _DAT_0057db3c + _DAT_006d7b90 * _DAT_0057db4c + _DAT_006d7b94 * _DAT_0057db5c
  ;
  _DAT_006d7c18 =
       DAT_006d7b98 * _DAT_0057db20 +
       DAT_006d7b9c * _DAT_0057db30 + DAT_006d7ba0 * _DAT_0057db40 + _DAT_006d7ba4 * _DAT_0057db50;
  _DAT_006d7c1c =
       DAT_006d7b98 * _DAT_0057db24 +
       DAT_006d7b9c * _DAT_0057db34 + DAT_006d7ba0 * _DAT_0057db44 + _DAT_006d7ba4 * _DAT_0057db54;
  iVar15 = 0;
  param_2 = 0;
  _DAT_006d7c20 =
       DAT_006d7b98 * _DAT_0057db28 +
       DAT_006d7b9c * _DAT_0057db38 + DAT_006d7ba0 * _DAT_0057db48 + _DAT_006d7ba4 * _DAT_0057db58;
  _DAT_006d7c24 =
       DAT_006d7b98 * _DAT_0057db2c +
       DAT_006d7b9c * _DAT_0057db3c + DAT_006d7ba0 * _DAT_0057db4c + _DAT_006d7ba4 * _DAT_0057db5c;
  if (*(short *)(param_1 + 0x6c) != 0) {
    iVar13 = 0;
    pfVar16 = (float *)&DAT_0058b0fc;
    do {
      pfVar1 = pfVar16 + -3;
      pfVar4 = (float *)(*(int *)(param_1 + 0x70) + iVar13);
      *pfVar1 = _DAT_006d7be8 * *pfVar4 + _DAT_006d7bf8 * pfVar4[1] + _DAT_006d7c08 * pfVar4[2] +
                _DAT_006d7c18;
      pfVar16[-2] = _DAT_006d7bfc * pfVar4[1] + _DAT_006d7bec * *pfVar4 + _DAT_006d7c0c * pfVar4[2]
                    + _DAT_006d7c1c;
      pfVar16[-1] = _DAT_006d7c00 * pfVar4[1] + _DAT_006d7bf0 * *pfVar4 + _DAT_006d7c10 * pfVar4[2]
                    + _DAT_006d7c20;
      *pfVar16 = _DAT_006d7c04 * pfVar4[1] + _DAT_006d7bf4 * *pfVar4 + _DAT_006d7c14 * pfVar4[2] +
                 _DAT_006d7c24;
      fVar5 = (float)sub_401080(pfVar1);
      pfVar16[5] = fVar5;
      if (fVar5 == 0.0) {
        fVar5 = _DAT_0056e008 / *pfVar16;
        pfVar16[1] = (*pfVar1 * fVar5 + (float)_DAT_0056e038) * _DAT_00583388;
        pfVar16[2] = ((float)_DAT_0056e038 - pfVar16[-2] * fVar5) * _DAT_0058338c;
        pfVar16[3] = ((float)_DAT_0056e038 - pfVar16[-1] * fVar5) * (float)_DAT_0056e030;
        pfVar16[4] = fVar5;
      }
      iVar15 = iVar15 + 1;
      iVar13 = iVar13 + 0x18;
      pfVar16 = pfVar16 + 9;
    } while (iVar15 < (int)(uint)*(ushort *)(param_1 + 0x6c));
  }
  local_c = 0;
  if (*(short *)(param_1 + 0x6e) == 0) {
    return 1;
  }
  do {
    puVar2 = (ushort *)(*(int *)(param_1 + 0x74) + local_c * 0x1c);
    if ((*puVar2 & 8) != 0) {
      if (param_2 != 0) {
        uVar14 = (byte)~*local_8 & 1;
        if (0 < param_2) {
          if (DAT_005833e1 == '\0') {
            if (local_1c == 0) {
              if (DAT_006d7c58 != 1) {
                (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,1);
                DAT_006d7c58 = 1;
              }
            }
            else {
              if ((local_18 != 0) && (*(int *)(local_1c + 0x14) != local_18)) {
                (**(code **)(**(int **)(local_1c + 0xc) + 0x7c))
                          (*(int **)(local_1c + 0xc),*(undefined4 *)(local_18 + 0x10));
                *(int *)(local_1c + 0x14) = local_18;
              }
              if (DAT_006d7c54 != *(int *)(local_1c + 0x10)) {
                (**(code **)(*DAT_00582cd4 + 0x98))(DAT_00582cd4,0,*(int *)(local_1c + 0x10));
                DAT_006d7c54 = *(int *)(local_1c + 0x10);
              }
              if (DAT_006d7c58 != 2) {
                (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,2);
                DAT_006d7c58 = 2;
              }
            }
            if (DAT_006d7c34 != 1) {
              (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,9,1);
              DAT_006d7c34 = 1;
            }
            if ((_DAT_006d7c38 & 0xff) != uVar14) {
              (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xb,uVar14);
              _DAT_006d7c38 = CONCAT31(_DAT_006d7c39,(char)uVar14);
            }
            if (DAT_006d7c4e != '\0') {
              (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x29,0);
              DAT_006d7c4e = '\0';
            }
            if ((_DAT_006d7c30 & 0xff) == (uint)(DAT_005833e4._2_1_ == '\0')) {
LAB_00401f48:
              if (DAT_005833e4._2_1_ == '\0') goto LAB_00401f57;
              uVar14 = 0;
            }
            else {
              (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,7,DAT_005833e4._2_1_ == '\0');
              if (DAT_005833e4._2_1_ != '\0') {
                _DAT_006d7c30 = (uint)DAT_006d7c30_1 << 8;
                goto LAB_00401f48;
              }
              _DAT_006d7c30 = CONCAT31(DAT_006d7c30_1,1);
LAB_00401f57:
              uVar14 = 1;
            }
            if ((_DAT_006d7c38 >> 8 & 0xff) != uVar14) {
              (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xe,DAT_005833e4._2_1_ == '\0');
              _DAT_006d7c38 = CONCAT11(DAT_005833e4._2_1_ == '\0',DAT_006d7c38);
            }
            if (DAT_006d7c48 != 8) {
              (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x17,8);
              DAT_006d7c48 = 8;
            }
            if (DAT_006d7c3a != '\0') {
              (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xf,0);
              _DAT_006d7c38 = (uint3)_DAT_006d7c38;
            }
            if (DAT_006d7c50 != 0) {
              (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x2f,0);
              DAT_006d7c50 = 0;
            }
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
            if (DAT_006d7c5c != 2) {
              (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,2);
              DAT_006d7c5c = 2;
            }
            (**(code **)(*DAT_00582cd4 + 0x70))(DAT_00582cd4,4,0x1c4,&DAT_005d15f8,param_2,0x1c);
          }
          else {
            if (local_1c == 0) {
              uVar11 = 0;
            }
            else {
              uVar11 = *(undefined4 *)(local_1c + 0x1c);
            }
            pcVar6 = sub_4C6CD0;
            if (DAT_00583380 == '\0') {
              pcVar6 = sub_442BD0;
            }
            (*pcVar6)(DAT_0058331c,DAT_005832f0,uVar11,DAT_00583308 >> 1,DAT_00583374,&DAT_005d15f8,
                      param_2,0,local_18,(-(uint)((~*local_8 & 1) != 0) & 0xfffffe00) + 0x200 | 0x1a
                     );
          }
        }
        param_2 = 0;
      }
      local_8 = *(byte **)(puVar2 + 4);
      if ((*local_8 & 1) == 0) {
        if (local_8[2] == 0xff) {
          local_1c = 0;
        }
        else {
          local_1c = (char)local_8[2] * 0x20 + DAT_0058114c;
        }
        if (local_8[3] != 0xff) {
          local_18 = DAT_00581144 + (char)local_8[3] * 0x1c;
          goto LAB_0040209f;
        }
      }
      else {
        local_1c = 0;
      }
      local_18 = 0;
    }
LAB_0040209f:
    fVar5 = _DAT_0056e028;
    uVar18 = (uint)puVar2[2];
    uVar17 = (uint)puVar2[3];
    uVar14 = (uint)puVar2[1];
    if (((&DAT_0058b110)[uVar17 * 9] & (&DAT_0058b110)[uVar14 * 9] & (&DAT_0058b110)[uVar18 * 9]) ==
        0) {
      iVar15 = 3;
      uVar7 = (&DAT_0058b110)[uVar14 * 9] | (&DAT_0058b110)[uVar18 * 9] |
              (&DAT_0058b110)[uVar17 * 9];
      bVar19 = uVar7 == 0;
      if (!bVar19) {
        iVar15 = 0;
        for (uVar8 = uVar7; uVar8 != 0; uVar8 = (int)uVar8 >> 1) {
          if ((uVar8 & 1) != 0) {
            iVar15 = iVar15 + 1;
          }
        }
        iVar15 = iVar15 * 3 + 3;
      }
      iVar13 = param_2 * 0x20;
      puVar9 = (undefined4 *)(&DAT_005d15f8 + iVar13);
      if (bVar19) {
        *puVar9 = (&DAT_0058b100)[uVar14 * 9];
        *(undefined4 *)(&DAT_005d15fc + iVar13) = (&DAT_0058b104)[uVar14 * 9];
        *(undefined4 *)(&DAT_005d1600 + iVar13) = 0x3f7ffffe;
        *(undefined4 *)(&DAT_005d1604 + iVar13) = (&DAT_0058b10c)[uVar14 * 9];
        *(undefined4 *)(&DAT_005d1618 + iVar13) = (&DAT_0058b100)[uVar18 * 9];
        *(undefined4 *)(&DAT_005d161c + iVar13) = (&DAT_0058b104)[uVar18 * 9];
        *(undefined4 *)(&DAT_005d1620 + iVar13) = 0x3f7ffffe;
        *(undefined4 *)(&DAT_005d1624 + iVar13) = (&DAT_0058b10c)[uVar18 * 9];
        *(undefined4 *)(&DAT_005d1638 + iVar13) = (&DAT_0058b100)[uVar17 * 9];
        *(undefined4 *)(&DAT_005d163c + iVar13) = (&DAT_0058b104)[uVar17 * 9];
        *(undefined4 *)(&DAT_005d1640 + iVar13) = 0x3f7ffffe;
        uVar11 = (&DAT_0058b10c)[uVar17 * 9];
        puVar10 = puVar9;
      }
      else {
        iVar13 = (param_2 + iVar15) * 0x20;
        *(undefined4 *)(&DAT_005d15f8 + iVar13) = (&DAT_0058b0f0)[uVar14 * 9];
        *(undefined4 *)(&DAT_005d15fc + iVar13) = (&DAT_0058b0f4)[uVar14 * 9];
        *(float *)(&DAT_005d1600 + iVar13) = fVar5 - (float)(&DAT_0058b0fc)[uVar14 * 9];
        *(undefined4 *)(&DAT_005d1604 + iVar13) = (&DAT_0058b0fc)[uVar14 * 9];
        fVar5 = _DAT_0056e028;
        *(undefined4 *)(&DAT_005d1618 + iVar13) = (&DAT_0058b0f0)[uVar18 * 9];
        *(undefined4 *)(&DAT_005d161c + iVar13) = (&DAT_0058b0f4)[uVar18 * 9];
        *(float *)(&DAT_005d1620 + iVar13) = fVar5 - (float)(&DAT_0058b0fc)[uVar18 * 9];
        *(undefined4 *)(&DAT_005d1624 + iVar13) = (&DAT_0058b0fc)[uVar18 * 9];
        fVar5 = _DAT_0056e028;
        *(undefined4 *)(&DAT_005d1638 + iVar13) = (&DAT_0058b0f0)[uVar17 * 9];
        *(undefined4 *)(&DAT_005d163c + iVar13) = (&DAT_0058b0f4)[uVar17 * 9];
        *(float *)(&DAT_005d1640 + iVar13) = fVar5 - (float)(&DAT_0058b0fc)[uVar17 * 9];
        uVar11 = (&DAT_0058b0fc)[uVar17 * 9];
        puVar10 = (undefined4 *)(&DAT_005d15f8 + iVar13);
        local_4 = puVar9;
      }
      puVar10[0x13] = uVar11;
      bVar12 = **(byte **)(puVar2 + 4);
      puVar10[4] = 0xffffff;
      if ((bVar12 & 1) == 0) {
        puVar10[0xc] = 0xffffff;
        puVar10[5] = 0;
        puVar10[0xd] = 0;
        puVar10[0x14] = 0xffffff;
        puVar10[0x15] = 0;
        uVar3 = *puVar2;
        bVar12 = (byte)uVar3;
        if ((uVar3 & 0x800) == 0) {
          iVar13 = *(int *)(puVar2 + 4);
          bVar12 = bVar12 >> 5 & 1;
          if (bVar12 == 0) {
            uVar11 = *(undefined4 *)(iVar13 + 8);
          }
          else {
            uVar11 = *(undefined4 *)(iVar13 + 4);
          }
          puVar10[6] = uVar11;
          puVar10[7] = *(undefined4 *)(iVar13 + 0x10);
          if (bVar12 == 0) {
            uVar11 = *(undefined4 *)(iVar13 + 4);
          }
          else {
            uVar11 = *(undefined4 *)(iVar13 + 8);
          }
          puVar10[0xe] = uVar11;
          puVar10[0xf] = *(undefined4 *)(iVar13 + 0x10);
          if (bVar12 == 0) goto LAB_0040234d;
LAB_00402440:
          uVar11 = *(undefined4 *)(iVar13 + 4);
LAB_00402350:
          puVar10[0x16] = uVar11;
          uVar11 = *(undefined4 *)(iVar13 + 0xc);
        }
        else {
          if ((uVar3 & 0x10) == 0) {
            iVar13 = *(int *)(puVar2 + 4);
            bVar12 = bVar12 >> 5 & 1;
            if (bVar12 == 0) {
              uVar11 = *(undefined4 *)(iVar13 + 8);
            }
            else {
              uVar11 = *(undefined4 *)(iVar13 + 4);
            }
            puVar10[6] = uVar11;
            puVar10[7] = *(undefined4 *)(iVar13 + 0x10);
            if (bVar12 == 0) {
              uVar11 = *(undefined4 *)(iVar13 + 4);
            }
            else {
              uVar11 = *(undefined4 *)(iVar13 + 8);
            }
            puVar10[0xe] = uVar11;
            puVar10[0xf] = *(undefined4 *)(iVar13 + 0x10);
            if (bVar12 == 0) goto LAB_00402440;
LAB_0040234d:
            uVar11 = *(undefined4 *)(iVar13 + 8);
            goto LAB_00402350;
          }
          iVar13 = *(int *)(puVar2 + 4);
          bVar12 = bVar12 >> 5 & 1;
          if (bVar12 == 0) {
            uVar11 = *(undefined4 *)(iVar13 + 4);
          }
          else {
            uVar11 = *(undefined4 *)(iVar13 + 8);
          }
          puVar10[6] = uVar11;
          puVar10[7] = *(undefined4 *)(iVar13 + 0xc);
          if (bVar12 == 0) {
            uVar11 = *(undefined4 *)(iVar13 + 8);
          }
          else {
            uVar11 = *(undefined4 *)(iVar13 + 4);
          }
          puVar10[0xe] = uVar11;
          puVar10[0xf] = *(undefined4 *)(iVar13 + 0xc);
          if (bVar12 == 0) {
            puVar10[0x16] = *(undefined4 *)(iVar13 + 8);
            uVar11 = *(undefined4 *)(iVar13 + 0x10);
          }
          else {
            puVar10[0x16] = *(undefined4 *)(iVar13 + 4);
            uVar11 = *(undefined4 *)(iVar13 + 0x10);
          }
        }
        puVar10[0x17] = uVar11;
      }
      else {
        puVar10[0xc] = 0xffffff;
        puVar10[5] = 0;
        puVar10[0xd] = 0;
        puVar10[0x14] = 0xffffff;
        puVar10[0x15] = 0;
      }
      *(undefined1 *)((int)puVar10 + 0x13) = 0xff;
      *(undefined1 *)((int)puVar10 + 0x33) = 0xff;
      *(undefined1 *)((int)puVar10 + 0x53) = 0xff;
      puVar10[4] = 0xffffff;
      puVar10[5] = 0;
      puVar10[0xc] = 0xffffff;
      puVar10[0xd] = 0;
      puVar10[0x14] = 0xffffff;
      puVar10[0x15] = 0;
      if ((bVar19) || (iVar15 = sub_439F20(local_4,puVar10,3,uVar7), iVar15 != 0)) {
        param_2 = param_2 + iVar15;
      }
    }
    local_c = local_c + 1;
  } while (local_c < (int)(uint)*(ushort *)(param_1 + 0x6e));
  if (param_2 == 0) {
    return 1;
  }
  uVar14 = (byte)~*local_8 & 1;
  if (param_2 < 1) {
    return 1;
  }
  if (DAT_005833e1 != '\0') {
    if (local_1c == 0) {
      uVar11 = 0;
    }
    else {
      uVar11 = *(undefined4 *)(local_1c + 0x1c);
    }
    pcVar6 = sub_4C6CD0;
    if (DAT_00583380 == '\0') {
      pcVar6 = sub_442BD0;
    }
    (*pcVar6)(DAT_0058331c,DAT_005832f0,uVar11,DAT_00583308 >> 1,DAT_00583374,&DAT_005d15f8,param_2,
              0,local_18,(-(uint)((~*local_8 & 1) != 0) & 0xfffffe00) + 0x200 | 0x1a);
    return 1;
  }
  if (local_1c == 0) {
    if (DAT_006d7c58 != 1) {
      (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,1);
      DAT_006d7c58 = 1;
    }
  }
  else {
    if ((local_18 != 0) && (*(int *)(local_1c + 0x14) != local_18)) {
      (**(code **)(**(int **)(local_1c + 0xc) + 0x7c))
                (*(int **)(local_1c + 0xc),*(undefined4 *)(local_18 + 0x10));
      *(int *)(local_1c + 0x14) = local_18;
    }
    if (DAT_006d7c54 != *(int *)(local_1c + 0x10)) {
      (**(code **)(*DAT_00582cd4 + 0x98))(DAT_00582cd4,0,*(int *)(local_1c + 0x10));
      DAT_006d7c54 = *(int *)(local_1c + 0x10);
    }
    if (DAT_006d7c58 != 2) {
      (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,1,2);
      DAT_006d7c58 = 2;
    }
  }
  if (DAT_006d7c34 != 1) {
    (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,9,1);
    DAT_006d7c34 = 1;
  }
  if ((_DAT_006d7c38 & 0xff) != uVar14) {
    (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xb,uVar14);
    _DAT_006d7c38 = CONCAT31(_DAT_006d7c39,(char)uVar14);
  }
  if (DAT_006d7c4e != '\0') {
    (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x29,0);
    DAT_006d7c4e = '\0';
  }
  if ((_DAT_006d7c30 & 0xff) == (uint)(DAT_005833e4._2_1_ == '\0')) {
LAB_004025d3:
    if (DAT_005833e4._2_1_ != '\0') {
      uVar14 = 0;
      goto LAB_004025e4;
    }
  }
  else {
    (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,7,DAT_005833e4._2_1_ == '\0');
    if (DAT_005833e4._2_1_ != '\0') {
      _DAT_006d7c30 = (uint)DAT_006d7c30_1 << 8;
      goto LAB_004025d3;
    }
    _DAT_006d7c30 = CONCAT31(DAT_006d7c30_1,1);
  }
  uVar14 = 1;
LAB_004025e4:
  if ((_DAT_006d7c38 >> 8 & 0xff) != uVar14) {
    (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xe,DAT_005833e4._2_1_ == '\0');
    _DAT_006d7c38 = CONCAT11(DAT_005833e4._2_1_ == '\0',DAT_006d7c38);
  }
  if (DAT_006d7c48 != 8) {
    (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x17,8);
    DAT_006d7c48 = 8;
  }
  if (DAT_006d7c3a != '\0') {
    (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0xf,0);
    _DAT_006d7c38 = (uint3)_DAT_006d7c38;
  }
  if (DAT_006d7c50 != 0) {
    (**(code **)(*DAT_00582cd4 + 0x58))(DAT_00582cd4,0x2f,0);
    DAT_006d7c50 = 0;
  }
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
  if (DAT_006d7c5c != 2) {
    (**(code **)(*DAT_00582cd4 + 0xa0))(DAT_00582cd4,0,4,2);
    DAT_006d7c5c = 2;
  }
  (**(code **)(*DAT_00582cd4 + 0x70))(DAT_00582cd4,4,0x1c4,&DAT_005d15f8,param_2,0x1c);
  return 1;
}

