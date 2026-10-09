/* sub_438CD0 @ 00438cd0   101 bytes */

void sub_438CD0(int param_1)

{
  int iVar1;
  
  iVar1 = param_1 * 0x20;
  (&PTR_DAT_00570370)[param_1 * 8] = (undefined *)&DAT_00583470;
  *(undefined1 **)(&DAT_00570374 + iVar1) = &LAB_00409640;
  *(undefined1 **)(&DAT_00570378 + iVar1) = &LAB_0040a030;
  *(undefined1 **)(&DAT_0057037c + iVar1) = &LAB_00409290;
  (&DAT_00570380)[iVar1] = 0;
  (&DAT_00570381)[iVar1] = 0;
  (&DAT_00570382)[iVar1] = 1;
  (&DAT_00570383)[iVar1] = 1;
  (&DAT_00570384)[iVar1] = 0;
  *(undefined4 *)(&DAT_00570388 + iVar1) = 1;
  *(undefined4 *)(&DAT_0057038c + iVar1) = 2;
  return;
}

