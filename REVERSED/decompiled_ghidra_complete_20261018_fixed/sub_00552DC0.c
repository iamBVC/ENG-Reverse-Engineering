/* sub_552DC0 @ 00552dc0   63 bytes */

void sub_552DC0(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = sub_54BC00(param_1);
  iVar2 = sub_54BC00(param_1);
  sub_54BBD0(param_1,(uint)((longlong)iVar1 * (longlong)iVar2) >> 0xc |
                     (int)((ulonglong)((longlong)iVar1 * (longlong)iVar2) >> 0x20) << 0x14);
  return;
}

