/* sub_438E10 @ 00438e10   101 bytes */

void sub_438E10(int param_1)

{
  int iVar1;
  
  iVar1 = param_1 * 0x20;
  (&PTR_DAT_00570370)[param_1 * 8] = (undefined *)&DAT_00583450;
  *(code **)(&DAT_00570374 + iVar1) = sub_408470;
  *(undefined1 **)(&DAT_00570378 + iVar1) = &LAB_00408970;
  *(code **)(&DAT_0057037c + iVar1) = sub_4083A0;
  (&DAT_00570380)[iVar1] = 1;
  (&DAT_00570381)[iVar1] = 0;
  (&DAT_00570382)[iVar1] = 1;
  (&DAT_00570383)[iVar1] = 0;
  (&DAT_00570384)[iVar1] = 0;
  *(undefined4 *)(&DAT_00570388 + iVar1) = 1;
  *(undefined4 *)(&DAT_0057038c + iVar1) = 2;
  return;
}

