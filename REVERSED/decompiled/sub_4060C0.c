/* sub_4060C0 @ 004060c0   1161 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_4060C0(void)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float *pfVar7;
  uint *puVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iStack00000004;
  int iStack00000008;
  int iStack0000000c;
  int iStack00000010;
  uint uStack00000014;
  float in_stack_00000018;
  float in_stack_0000001c;
  float in_stack_00000020;
  float in_stack_00000024;
  float in_stack_00000028;
  float in_stack_0000002c;
  float in_stack_00000030;
  float in_stack_00000034;
  float in_stack_00000038;
  float in_stack_00000040;
  float in_stack_00000044;
  float in_stack_00000048;
  float in_stack_00000050;
  float in_stack_00000054;
  float in_stack_00000058;
  float in_stack_00000060;
  float in_stack_00000064;
  float in_stack_00000068;
  undefined4 uVar13;
  undefined1 *puVar14;
  
  sub_562840();
  uStack00000014 = 0;
  if (*(int *)(DAT_0057f858 + 4) != 0) {
    iVar11 = 0;
    iStack00000004 = 0;
    iVar12 = DAT_0057f858;
    iVar10 = DAT_0057f848;
    do {
      uVar9 = 0;
      pfVar7 = *(float **)(*(int *)(iVar12 + 0xc) + 0x70 + iStack00000004);
      puVar8 = *(uint **)(iVar11 + 0x14 + iVar10);
      if (*(int *)(iVar11 + 0x10 + iVar10) != 0) {
        do {
          *pfVar7 = (float)((int)(*puVar8 << 0x16) >> 0x14) * (float)_DAT_0056e020;
          pfVar7[1] = (float)((int)((*puVar8 & 0xfffffcff) << 0xc) >> 0x14) * (float)_DAT_0056e020;
          uVar9 = uVar9 + 1;
          pfVar7[2] = -((float)((int)((*puVar8 & 0xfff3ffff) << 2) >> 0x14) * (float)_DAT_0056e020);
          pfVar7 = pfVar7 + 6;
          puVar8 = puVar8 + 1;
          iVar12 = DAT_0057f858;
          iVar10 = DAT_0057f848;
        } while (uVar9 < *(uint *)(iVar11 + 0x10 + DAT_0057f848));
      }
      iStack00000004 = iStack00000004 + 0x8c;
      uStack00000014 = uStack00000014 + 1;
      iVar11 = iVar11 + 0x20;
    } while (uStack00000014 < *(uint *)(iVar12 + 4));
  }
  in_stack_00000024 = (float)*(int *)(DAT_0057f8b8 + 0x30) * (float)_DAT_0056e020;
  in_stack_00000028 = (float)*(int *)(DAT_0057f8b8 + 0x34) * (float)_DAT_0056e020;
  in_stack_0000002c = -((float)*(int *)(DAT_0057f8b8 + 0x38) * (float)_DAT_0056e020);
  in_stack_00000018 = (float)*(int *)(DAT_0057f8b8 + 0x20) * (float)_DAT_0056e058;
  in_stack_0000001c = (float)*(int *)(DAT_0057f8b8 + 0x24) * (float)_DAT_0056e058;
  in_stack_00000020 = -((float)*(int *)(DAT_0057f8b8 + 0x28) * (float)_DAT_0056e058);
  iStack00000010 = *(int *)(DAT_0057f8b8 + 0x60);
  if (iStack00000010 == 0) {
    iStack00000010 = 1;
  }
  iStack0000000c = *(int *)(DAT_0057f8b8 + 100);
  fVar1 = (float)_DAT_0056e020;
  if (iStack0000000c == 0) {
    iStack0000000c = 1;
  }
  iStack00000004 = *(int *)(DAT_0057f8b8 + 0x68);
  fVar2 = (float)_DAT_0056e020;
  if (iStack00000004 == 0) {
    iStack00000004 = 1;
  }
  fVar3 = (float)_DAT_0056e020;
  sub_41E990(&stack0x00000018,(float)iStack00000010 * fVar1,(float)iStack0000000c * fVar2,
             (float)iStack00000004 * fVar3,&stack0x00000030);
  uStack00000014 = 0;
  if (*(int *)(DAT_0057f858 + 4) != 0) {
    iVar12 = 0;
    iStack00000008 = 0;
    do {
      fVar4 = (float)*(int *)(iVar12 + DAT_0057f848) * (float)_DAT_0056e020;
      fVar5 = (float)*(int *)(iVar12 + 4 + DAT_0057f848) * (float)_DAT_0056e020;
      fVar6 = -((float)*(int *)(iVar12 + 8 + DAT_0057f848) * (float)_DAT_0056e020);
      in_stack_00000024 =
           in_stack_00000030 * fVar4 + in_stack_00000040 * fVar5 + in_stack_00000050 * fVar6 +
           in_stack_00000060;
      in_stack_00000028 =
           in_stack_00000034 * fVar4 + in_stack_00000044 * fVar5 + in_stack_00000054 * fVar6 +
           in_stack_00000064;
      in_stack_0000002c =
           in_stack_00000038 * fVar4 + in_stack_00000048 * fVar5 + in_stack_00000058 * fVar6 +
           in_stack_00000068;
      iVar10 = *(int *)(iVar12 + 0x18 + DAT_0057f848);
      if (iVar10 == 0) {
        iVar10 = *(int *)(iVar12 + 0x10 + DAT_0057f848);
        uVar13 = CONCAT31((int3)((uint)iVar10 >> 8),iVar10 != 0);
        puVar14 = (undefined1 *)0x0;
        iVar10 = *(int *)(DAT_0057f858 + 0xc);
      }
      else {
        uVar9 = 0;
        if (iVar10 != 0) {
          iVar10 = 0;
          pfVar7 = (float *)&stack0x00000074;
          do {
            pfVar7[-1] = (float)(int)*(short *)(iVar10 + *(int *)(iVar12 + 0x1c + DAT_0057f848)) *
                         (float)_DAT_0056e020;
            *pfVar7 = (float)(int)*(short *)(iVar10 + 6 + *(int *)(iVar12 + 0x1c + DAT_0057f848)) *
                      (float)_DAT_0056e020;
            pfVar7[1] = -((float)(int)*(short *)(iVar10 + 0xc +
                                                *(int *)(iVar12 + 0x1c + DAT_0057f848)) *
                         (float)_DAT_0056e020);
            pfVar7[2] = 0.0;
            pfVar7[3] = (float)(int)*(short *)(iVar10 + 2 + *(int *)(iVar12 + 0x1c + DAT_0057f848))
                        * (float)_DAT_0056e020;
            pfVar7[4] = (float)(int)*(short *)(iVar10 + 8 + *(int *)(iVar12 + 0x1c + DAT_0057f848))
                        * (float)_DAT_0056e020;
            pfVar7[5] = -((float)(int)*(short *)(iVar10 + 0xe +
                                                *(int *)(iVar12 + 0x1c + DAT_0057f848)) *
                         (float)_DAT_0056e020);
            pfVar7[6] = 0.0;
            pfVar7[7] = -((float)(int)*(short *)(iVar10 + 4 + *(int *)(iVar12 + 0x1c + DAT_0057f848)
                                                ) * (float)_DAT_0056e020);
            pfVar7[8] = -((float)(int)*(short *)(iVar10 + 10 +
                                                *(int *)(iVar12 + 0x1c + DAT_0057f848)) *
                         (float)_DAT_0056e020);
            pfVar7[9] = (float)(int)*(short *)(iVar10 + 0x10 +
                                              *(int *)(iVar12 + 0x1c + DAT_0057f848)) *
                        (float)_DAT_0056e020;
            pfVar7[10] = 0.0;
            pfVar7[0xb] = (float)(int)*(short *)(iVar10 + 0x12 +
                                                *(int *)(iVar12 + 0x1c + DAT_0057f848)) *
                          (float)_DAT_0056e020;
            pfVar7[0xc] = (float)(int)*(short *)(iVar10 + 0x14 +
                                                *(int *)(iVar12 + 0x1c + DAT_0057f848)) *
                          (float)_DAT_0056e020;
            uVar9 = uVar9 + 1;
            iVar11 = iVar10 + 0x16;
            iVar10 = iVar10 + 0x18;
            pfVar7[0xd] = -((float)(int)*(short *)(iVar11 + *(int *)(iVar12 + 0x1c + DAT_0057f848))
                           * (float)_DAT_0056e020);
            pfVar7[0xe] = 1.0;
            pfVar7 = pfVar7 + 0x10;
          } while (uVar9 < *(uint *)(iVar12 + 0x18 + DAT_0057f848));
        }
        iVar10 = *(int *)(DAT_0057f858 + 0xc);
        puVar14 = &stack0x00000070;
        uVar13 = 1;
      }
      sub_41FB30(iVar10 + iStack00000008,&stack0x00000018,(float)iStack00000010 * fVar1,
                 (float)iStack0000000c * fVar2,(float)iStack00000004 * fVar3,0x3f800000,0,uVar13,
                 puVar14,0xffffffff,0xffffffff,0xffffffff,0,0);
      uStack00000014 = uStack00000014 + 1;
      iVar12 = iVar12 + 0x20;
      iStack00000008 = iStack00000008 + 0x8c;
    } while (uStack00000014 < *(uint *)(DAT_0057f858 + 4));
  }
  return;
}

