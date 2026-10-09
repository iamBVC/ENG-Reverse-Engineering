/* sub_54C4A0 @ 0054c4a0   2628 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_54C4A0(void)

{
  ushort uVar1;
  undefined4 *puVar2;
  uint *puVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  undefined4 *puVar9;
  int iVar10;
  uint uVar11;
  undefined4 *puVar12;
  uint local_8;
  
  puVar2 = DAT_006d9e38;
  DAT_006d9e10 = DAT_006d9e10 + 0x1000;
  DAT_006d9db8 = 0x20;
  if (DAT_00584708 != 0) {
    DAT_006d9db8 = 0x48;
  }
  sub_54C440();
  DAT_0057ddc0 = 0;
  do {
    do {
      while( true ) {
        puVar9 = puVar2;
        if (puVar9 == (undefined4 *)0x0) {
          if (DAT_005fcf64 != 0) {
            if (0x5a < DAT_005fcf64) {
              DAT_005fcf64 = 0x5a;
            }
            DAT_005fcf64 = DAT_005fcf64 + -1;
          }
          puVar2 = DAT_006d9e38;
          if (_DAT_005fcf14 != 0) {
            if (0 < DAT_005fcf68) {
              DAT_005fcf68 = -0xff;
            }
            _DAT_005fcf14 = _DAT_005fcf14 + DAT_005fcf68;
            if (_DAT_005fcf14 < 0) {
              _DAT_005fcf14 = 0;
            }
            else if (0xff < _DAT_005fcf14) {
              _DAT_005fcf14 = 0xff;
            }
          }
          for (; puVar9 = DAT_006d9e38, puVar2 != (undefined4 *)0x0;
              puVar2 = (undefined4 *)puVar2[1]) {
            uVar6 = puVar2[0x3b];
            puVar2[0x3a] = puVar2[0x3a] & 0xff3fffff;
            puVar2[0x3b] = uVar6 & 0xfcffffff;
            if (((uVar6 & 0x18000) != 0x18000) && ((puVar2[0x4e] & 0x48000) != 0)) {
              *(ushort *)(puVar2[0x30] + 6) = *(ushort *)(puVar2[0x30] + 6) & 0xfff3;
              if ((puVar2[0x3a] & 0x40000) != 0) {
                if (puVar2 == DAT_006d9e1c) {
                  iVar5 = puVar2[0xc];
                  iVar4 = (puVar2[0x16] - puVar2[0xe]) * (puVar2[0x16] - puVar2[0xe]) +
                          (puVar2[0x14] - iVar5) * (puVar2[0x14] - iVar5);
                  if ((0 < iVar4) && (iVar4 < 2000000)) {
                    iVar4 = puVar2[0xd];
                    iVar10 = puVar2[0xe];
                    puVar2[0xc] = iVar5 + puVar2[0x14] >> 1;
                    puVar2[0xd] = iVar4 + puVar2[0x15] >> 1;
                    puVar2[0xe] = puVar2[0x16] + iVar10 >> 1;
                    sub_403EE0(puVar2,DAT_005846ec,DAT_00584648);
                    puVar2[0xc] = puVar2[0xc] + (iVar5 - puVar2[0x14] >> 1);
                    puVar2[0xd] = puVar2[0xd] + (iVar4 - puVar2[0x15] >> 1);
                    puVar2[0xe] = puVar2[0xe] + (iVar10 - puVar2[0x16] >> 1);
                  }
                }
                sub_403EE0(puVar2,DAT_005846ec,DAT_00584648);
              }
              if ((puVar2[0x3a] & 0x8000) != 0) {
                sub_403020(puVar2,DAT_005846ec,DAT_00584648);
              }
            }
          }
          for (; puVar2 = DAT_006d9e38, puVar9 != (undefined4 *)0x0;
              puVar9 = (undefined4 *)puVar9[1]) {
            if ((((puVar9[0x3b] & 0x18000) != 0x18000) && ((puVar9[0x3a] & 0x48000) != 0)) &&
               ((*(byte *)(puVar9[0x30] + 6) & 2) != 0)) {
              uVar11 = (uint)*(ushort *)(puVar9[0x30] + 8);
              uVar6 = *(uint *)(DAT_006d9dc0 + 0xec + uVar11 * 0x154);
              iVar5 = DAT_006d9dc0 + uVar11 * 0x154;
              *(uint *)(iVar5 + 0xec) = uVar6 | 0x1000000;
              if ((puVar9[0x3a] & 0x800) != 0) {
                *(uint *)(iVar5 + 0xec) = uVar6 | 0x3000000;
              }
              if ((*(byte *)(puVar9 + 0x3b) & 2) != 0) {
                uVar6 = *(uint *)(iVar5 + 0xe8);
                *(uint *)(iVar5 + 0xe8) = uVar6 | 0x400000;
                if ((puVar9[0x3a] & 0x800) != 0) {
                  *(uint *)(iVar5 + 0xe8) = uVar6 | 0xc00000;
                }
                if ((puVar9[0x3a] & 0x40000) != 0) {
                  *(uint *)(iVar5 + 0xec) = *(uint *)(iVar5 + 0xec) | 0x40;
                }
                if ((*(byte *)(puVar9 + 0x3b) & 2) != 0) {
                  puVar9[0xc] = puVar9[0xc] + (*(int *)(iVar5 + 0x30) - *(int *)(iVar5 + 0x50));
                  puVar9[0xd] = puVar9[0xd] + (*(int *)(iVar5 + 0x34) - *(int *)(iVar5 + 0x54));
                  puVar9[0xe] = puVar9[0xe] + (*(int *)(iVar5 + 0x38) - *(int *)(iVar5 + 0x58));
                  if (*(int *)(iVar5 + 0x24) != *(int *)(iVar5 + 0x44)) {
                    iVar4 = puVar9[0xc] - *(int *)(iVar5 + 0x30);
                    uVar6 = (uint)(short)(-*(int *)(iVar5 + 0x44) >> 0xc);
                    iVar10 = puVar9[0xe] - *(int *)(iVar5 + 0x38);
                    iVar7 = (&DAT_00574318)[uVar6 & 0xfff] * iVar10 +
                            (&DAT_00574318)[uVar6 + 0x400 & 0xfff] * iVar4 >> 0xc;
                    uVar11 = (uint)(short)(*(int *)(iVar5 + 0x24) >> 0xc);
                    iVar8 = (&DAT_00574318)[uVar6 + 0x400 & 0xfff] * iVar10 -
                            (&DAT_00574318)[uVar6 & 0xfff] * iVar4 >> 0xc;
                    iVar4 = (&DAT_00574318)[uVar11 & 0xfff];
                    iVar10 = (&DAT_00574318)[uVar11 + 0x400 & 0xfff];
                    puVar9[0xc] = (iVar4 * iVar8 + iVar10 * iVar7 >> 0xc) + *(int *)(iVar5 + 0x30);
                    puVar9[0xe] = (iVar10 * iVar8 - iVar4 * iVar7 >> 0xc) + *(int *)(iVar5 + 0x38);
                    puVar9[9] = (puVar9[9] - *(int *)(iVar5 + 0x44)) + *(int *)(iVar5 + 0x24) &
                                0xffffff;
                    puVar9[0x14] = (int)(puVar9[0x14] + puVar9[0xc]) >> 1;
                    puVar9[0x15] = (int)(puVar9[0xd] + puVar9[0x15]) >> 1;
                    puVar9[0x16] = (int)(puVar9[0x16] + puVar9[0xe]) >> 1;
                  }
                }
              }
            }
          }
          for (; puVar2 != (undefined4 *)0x0; puVar2 = (undefined4 *)puVar2[1]) {
            if ((puVar2[0x3b] & 0x18000) != 0x18000) {
              sub_54BC30(puVar2);
              if ((puVar2[4] == 0) ||
                 (((puVar2[0xc] == puVar2[0x14] && (puVar2[0xd] == puVar2[0x15])) &&
                  (puVar2[0xe] == puVar2[0x16])))) {
                uVar6 = puVar2[0x3b] & 0xdfffffff;
              }
              else {
                uVar6 = puVar2[0x3b] | 0x20000000;
              }
              puVar2[0x3b] = uVar6;
              puVar9 = puVar2 + 8;
              puVar12 = puVar2 + 0x10;
              for (iVar5 = 8; iVar5 != 0; iVar5 = iVar5 + -1) {
                *puVar12 = *puVar9;
                puVar9 = puVar9 + 1;
                puVar12 = puVar12 + 1;
              }
            }
          }
          sub_4051D0();
          if ((DAT_006d9e1c != (undefined4 *)0x0) &&
             (iVar5 = (int)*(short *)((int)DAT_006d9e1c + 0xd2) / 2,
             iVar5 < *(short *)(DAT_006d9e1c + 0x35))) {
            *(short *)(DAT_006d9e1c + 0x35) = (short)iVar5;
          }
          return;
        }
        DAT_006d9e18 = (undefined4 *)puVar9[1];
        if ((*(byte *)(puVar9 + 0x3a) & 4) == 0) break;
        if (puVar9[0x3d] != 0) {
          sub_41ADA0(puVar9[0x3d]);
        }
        if (puVar9[0x30] != 0) {
          sub_41ADA0(puVar9[0x30]);
        }
        sub_546240(puVar9,0xffffffff);
        if (*(char *)((int)puVar9 + 0x153) != -1) {
          sub_429DB0((int)*(char *)((int)puVar9 + 0x153));
        }
        if (*(char *)(puVar9 + 0x54) != -1) {
          sub_429DB0((int)*(char *)(puVar9 + 0x54));
        }
        if (*(char *)((int)puVar9 + 0x151) != -1) {
          sub_429DB0((int)*(char *)((int)puVar9 + 0x151));
        }
        if (*(char *)((int)puVar9 + 0x152) != -1) {
          sub_429DB0((int)*(char *)((int)puVar9 + 0x152));
        }
        *(undefined1 *)((int)puVar9 + 0x152) = 0xff;
        *(undefined1 *)((int)puVar9 + 0x151) = 0xff;
        *(undefined1 *)(puVar9 + 0x54) = 0xff;
        *(undefined1 *)((int)puVar9 + 0x153) = 0xff;
        puVar9[0x3b] = 0;
        puVar9[0x3a] = 0;
        if (puVar9[1] != 0) {
          *(undefined4 *)(puVar9[1] + 8) = puVar9[2];
        }
        if (puVar9[2] == 0) {
          DAT_006d9e38 = (undefined4 *)puVar9[1];
        }
        else {
          *(undefined4 *)(puVar9[2] + 4) = puVar9[1];
        }
        puVar9[2] = 0;
        puVar9[1] = DAT_006d9e3c;
        DAT_006d9dc8 = DAT_006d9dc8 + -1;
        DAT_006d9e3c = puVar9;
        puVar2 = DAT_006d9e18;
      }
      puVar2 = DAT_006d9e18;
    } while ((puVar9[0x3b] & 0x18000) == 0x18000);
    *(undefined2 *)(puVar9 + 0x3f) = 0;
    if ((*(byte *)(puVar9 + 0x3a) & 8) != 0) {
      *(short *)((int)puVar9 + 0x116) = *(short *)((int)puVar9 + 0x116) + *(short *)(puVar9 + 0x45);
      uVar1 = *(ushort *)((int)puVar9 + 0x116);
      while (0xfff < uVar1) {
        uVar6 = 0;
        *(ushort *)((int)puVar9 + 0x116) = uVar1 - 0x1000;
        puVar3 = (uint *)puVar9[5];
        if (*puVar3 != 0) {
          do {
            if ((uint)*(ushort *)(puVar3[1] + uVar6 * 4) == puVar9[0x44]) {
              *(ushort *)(puVar9 + 0x3f) =
                   *(ushort *)(puVar9 + 0x3f) | *(ushort *)(*(int *)(puVar9[5] + 4) + 2 + uVar6 * 4)
              ;
            }
            puVar3 = (uint *)puVar9[5];
            uVar6 = uVar6 + 1;
          } while (uVar6 < *puVar3);
        }
        iVar5 = *(int *)(puVar9[5] + 0xc);
        if (iVar5 != 0) {
          iVar4 = iVar5 + puVar9[0x44] * 8;
          iVar5 = (int)*(short *)(iVar5 + puVar9[0x44] * 8) << 2;
          iVar10 = (int)*(short *)(iVar4 + 2) << 2;
          iVar4 = (int)*(short *)(iVar4 + 4) << 2;
          puVar9[0xe] = puVar9[0xe] +
                        ((int)(((uint)((longlong)iVar4 * (longlong)(int)puVar9[0x24]) >> 0xc |
                               (int)((ulonglong)((longlong)iVar4 * (longlong)(int)puVar9[0x24]) >>
                                    0x20) << 0x14) +
                               ((uint)((longlong)iVar10 * (longlong)(int)puVar9[0x21]) >> 0xc |
                               (int)((ulonglong)((longlong)iVar10 * (longlong)(int)puVar9[0x21]) >>
                                    0x20) << 0x14) +
                               ((uint)((longlong)iVar5 * (longlong)(int)puVar9[0x1e]) >> 0xc |
                               (int)((ulonglong)((longlong)iVar5 * (longlong)(int)puVar9[0x1e]) >>
                                    0x20) << 0x14) + 2) >> 2);
          puVar9[0xc] = puVar9[0xc] +
                        ((int)(((uint)((longlong)iVar4 * (longlong)(int)puVar9[0x22]) >> 0xc |
                               (int)((ulonglong)((longlong)iVar4 * (longlong)(int)puVar9[0x22]) >>
                                    0x20) << 0x14) +
                               ((uint)((longlong)iVar10 * (longlong)(int)puVar9[0x1f]) >> 0xc |
                               (int)((ulonglong)((longlong)iVar10 * (longlong)(int)puVar9[0x1f]) >>
                                    0x20) << 0x14) +
                               ((uint)((longlong)iVar5 * (longlong)(int)puVar9[0x1c]) >> 0xc |
                               (int)((ulonglong)((longlong)iVar5 * (longlong)(int)puVar9[0x1c]) >>
                                    0x20) << 0x14) + 2) >> 2);
          puVar9[0xd] = puVar9[0xd] +
                        ((int)(((uint)((longlong)iVar4 * (longlong)(int)puVar9[0x23]) >> 0xc |
                               (int)((ulonglong)((longlong)iVar4 * (longlong)(int)puVar9[0x23]) >>
                                    0x20) << 0x14) +
                               ((uint)((longlong)iVar10 * (longlong)(int)puVar9[0x20]) >> 0xc |
                               (int)((ulonglong)((longlong)iVar10 * (longlong)(int)puVar9[0x20]) >>
                                    0x20) << 0x14) +
                               ((uint)((longlong)iVar5 * (longlong)(int)puVar9[0x1d]) >> 0xc |
                               (int)((ulonglong)((longlong)iVar5 * (longlong)(int)puVar9[0x1d]) >>
                                    0x20) << 0x14) + 2) >> 2);
          puVar9[9] = puVar9[9] +
                      *(short *)(*(int *)(puVar9[5] + 0xc) + 6 + puVar9[0x44] * 8) * 0x1000;
        }
        if (puVar9[0x44] == *(int *)(puVar9[5] + 8) + -1) {
          puVar9[0x3a] = puVar9[0x3a] & 0xfffffff7;
          break;
        }
        iVar5 = puVar9[0x44] + 1;
        puVar9[0x44] = iVar5;
        if (*(int *)(puVar9[5] + 0x10) != 0) {
          sub_41FA30(puVar9[4],puVar9[5],iVar5);
        }
        uVar1 = *(ushort *)((int)puVar9 + 0x116);
      }
    }
    iVar5 = 0;
    if ((((puVar9[0x40] != 0) && ((*(byte *)(puVar9 + 0x3a) & 0x40) == 0)) &&
        (*(short *)((int)puVar9 + 0xfe) == 0)) && (local_8 = 0, puVar9[0x40] != 0)) {
      iVar4 = 0;
      do {
        puVar3 = (uint *)(puVar9[0x3e] + iVar4);
        uVar6 = *puVar3;
        if (uVar6 < 0x41) {
          if (uVar6 == 0x40) {
            if (((uint)*(ushort *)(puVar9 + 0x3f) & 1 << ((byte)puVar3[1] & 0x1f)) != 0) {
              sub_54BBD0(puVar9,*puVar9);
              *puVar9 = *(undefined4 *)(iVar4 + 8 + puVar9[0x3e]);
            }
          }
          else if (uVar6 == 2) {
            puVar3[3] = puVar3[3] - 0x1000;
            iVar10 = iVar4 + puVar9[0x3e];
            if (*(int *)(iVar4 + 0xc + puVar9[0x3e]) == 0) {
              iVar5 = iVar5 + 1;
              *(undefined4 *)(iVar10 + 0xc) = *(undefined4 *)(iVar10 + 4);
            }
          }
          else if (uVar6 == 4) {
            if ((puVar9[0x3a] & 0x4000000) != 0) {
              iVar5 = iVar5 + 1;
              puVar9[0x3a] = puVar9[0x3a] & 0xfbffffff;
            }
          }
          else if (uVar6 == 0x20) {
            puVar3[3] = puVar3[3] - 0x1000;
            if (*(int *)(iVar4 + 0xc + puVar9[0x3e]) == 0) {
              iVar5 = iVar5 + 1;
              *(undefined4 *)(iVar4 + puVar9[0x3e]) = 0;
            }
          }
        }
        else if (uVar6 == 0x80) {
          if ((uint)puVar9[0x52] <= puVar3[1] * puVar3[1]) goto LAB_0054c9d6;
        }
        else if (uVar6 == 0x100) {
          if (puVar3[1] * puVar3[1] <= (uint)puVar9[0x52]) goto LAB_0054c9d6;
        }
        else if ((uVar6 == 0x200) && ((*(byte *)(puVar9[0x30] + 6) & 0xc) != 0)) {
LAB_0054c9d6:
          iVar5 = iVar5 + 1;
        }
        if (iVar5 != 0) {
          iVar5 = 0;
          sub_54BBD0(puVar9,*puVar9);
          *puVar9 = *(undefined4 *)(iVar4 + 8 + puVar9[0x3e]);
        }
        local_8 = local_8 + 1;
        iVar4 = iVar4 + 0x10;
      } while (local_8 < (uint)puVar9[0x40]);
    }
    puVar9[0x3a] = puVar9[0x3a] & 0xfffffffd;
    if (*(short *)((int)puVar9 + 0xfe) == 0) {
      sub_54D180(puVar9);
      puVar2 = DAT_006d9e18;
    }
    else {
      *(short *)((int)puVar9 + 0xfe) = *(short *)((int)puVar9 + 0xfe) + -1;
      puVar2 = DAT_006d9e18;
    }
  } while( true );
}

