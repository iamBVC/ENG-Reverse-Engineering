/* sub_4054C0 @ 004054c0   512 bytes */

void sub_4054C0(int param_1)

{
  ushort uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int local_8;
  int local_4;
  
  DAT_0057ddc0 = param_1;
  if ((*(byte *)(param_1 + 0xec) & 2) != 0) {
    iVar3 = *(int *)(param_1 + 0xc0);
    if ((*(ushort *)(iVar3 + 6) & 3) != 0) {
      if ((*(ushort *)(iVar3 + 6) & 1) == 0) {
        uVar2 = (uint)*(ushort *)(iVar3 + 8);
        if (((*(byte *)(DAT_006d9dc0 + 0xec + uVar2 * 0x154) & 0x20) == 0) ||
           (iVar5 = *(int *)(DAT_006d9dc0 + uVar2 * 0x154 + 0x10), iVar5 == 0)) {
          uVar1 = 0;
          iVar5 = 0;
          local_4 = 0;
          local_8 = 0;
        }
        else {
          iVar3 = *(int *)(iVar5 + 0x80) + (uint)*(ushort *)(iVar3 + 10) * 0x20;
          local_8 = (int)*(char *)(iVar3 + 2) << 5;
          local_4 = (int)*(char *)(iVar3 + 4) << 5;
          iVar5 = (int)*(char *)(iVar3 + 3) << 5;
          uVar1 = *(short *)(uVar2 * 0x20 + 4 + *(int *)(DAT_00584648 + 0x3c)) - 0x800U & 0xfff;
        }
      }
      else {
        iVar4 = *(int *)(DAT_005846ec + 0x80 +
                        *(int *)(*(int *)(DAT_00584648 + 0x4c) + *(short *)(iVar3 + 0xc) * 4) * 0x84
                        ) + (uint)*(ushort *)(iVar3 + 0xe) * 0x20;
        local_8 = (int)*(char *)(iVar4 + 2) << 5;
        iVar5 = (int)*(char *)(iVar4 + 3) << 5;
        local_4 = (int)*(char *)(iVar4 + 4) << 5;
        uVar1 = *(ushort *)(*(short *)(iVar3 + 0xc) * 0x20 + 4 + *(int *)(DAT_00584648 + 0x3c));
      }
      iVar4 = (int)(short)uVar1;
      fpatan((float10)local_8,(float10)local_4);
      uVar2 = iVar4 - (*(int *)(param_1 + 0x24) >> 0xc);
      DAT_0057dd90 = (&DAT_00574318)[uVar2 + 0x400 & 0xfff] * local_4 -
                     (&DAT_00574318)[uVar2 & 0xfff] * local_8 >> 0xc;
      uVar2 = iVar4 - (*(int *)(param_1 + 0x24) >> 0xc);
      DAT_0057dda8 = -((&DAT_00574318)[uVar2 + 0x400 & 0xfff] * local_8 +
                      (&DAT_00574318)[uVar2 & 0xfff] * local_4) >> 0xc;
      iVar3 = __ftol();
      DAT_0057dd9c = local_8;
      DAT_0057dda0 = local_4;
      DAT_0057dd94 = iVar4 - iVar3 & 0xfff;
      DAT_0057dda4 = 0x1000 - iVar5;
      return;
    }
  }
  DAT_0057dda0 = 0;
  DAT_0057dd9c = 0;
  DAT_0057dda4 = 0;
  DAT_0057dd94 = 0;
  DAT_0057dda8 = 0;
  DAT_0057dd90 = 0;
  return;
}

