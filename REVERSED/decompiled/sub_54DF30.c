/* sub_54DF30 @ 0054df30   174 bytes */

void sub_54DF30(int param_1)

{
  int iVar1;
  
  iVar1 = sub_54D560(param_1);
  if (iVar1 != 0) {
    DAT_00584644 = iVar1;
    sub_54DE00(param_1,iVar1);
    if ((*(byte *)(iVar1 + 0x1c) & 2) == 0) {
      iVar1 = (int)*(short *)(iVar1 + 0x38);
      DAT_006da298 = iVar1;
      *(uint *)(param_1 + 0x30) =
           *(int *)(param_1 + 0x30) +
           ((uint)((longlong)iVar1 *
                  (longlong)(int)(&DAT_00574318)[*(int *)(param_1 + 0x24) >> 0xc & 0xfff]) >> 0xc |
           (int)((ulonglong)
                 ((longlong)iVar1 *
                 (longlong)(int)(&DAT_00574318)[*(int *)(param_1 + 0x24) >> 0xc & 0xfff]) >> 0x20)
           << 0x14);
      *(uint *)(param_1 + 0x38) =
           *(int *)(param_1 + 0x38) +
           ((uint)((longlong)iVar1 *
                  (longlong)(int)(&DAT_00574318)[(*(int *)(param_1 + 0x24) >> 0xc) + 0x400U & 0xfff]
                  ) >> 0xc |
           (int)((ulonglong)
                 ((longlong)iVar1 *
                 (longlong)(int)(&DAT_00574318)[(*(int *)(param_1 + 0x24) >> 0xc) + 0x400U & 0xfff])
                >> 0x20) << 0x14);
    }
  }
  return;
}

