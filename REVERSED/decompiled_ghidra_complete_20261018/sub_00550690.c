/* sub_550690 @ 00550690   130 bytes */

void sub_550690(int param_1)

{
  int iVar1;
  
  iVar1 = sub_54BC00(param_1);
  *(uint *)(param_1 + 0x30) =
       *(int *)(param_1 + 0x30) +
       ((uint)((longlong)iVar1 *
              (longlong)(int)(&DAT_00574318)[*(int *)(param_1 + 0x24) >> 0xc & 0xfff]) >> 0xc |
       (int)((ulonglong)
             ((longlong)iVar1 *
             (longlong)(int)(&DAT_00574318)[*(int *)(param_1 + 0x24) >> 0xc & 0xfff]) >> 0x20) <<
       0x14);
  *(uint *)(param_1 + 0x38) =
       *(int *)(param_1 + 0x38) +
       ((uint)((longlong)iVar1 *
              (longlong)(int)(&DAT_00574318)[(*(int *)(param_1 + 0x24) >> 0xc) + 0x400U & 0xfff]) >>
        0xc | (int)((ulonglong)
                    ((longlong)iVar1 *
                    (longlong)
                    (int)(&DAT_00574318)[(*(int *)(param_1 + 0x24) >> 0xc) + 0x400U & 0xfff]) >>
                   0x20) << 0x14);
  return;
}

