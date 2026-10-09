/* sub_438FD0 @ 00438fd0   204 bytes */

void sub_438FD0(int param_1,undefined1 param_2)

{
  int iVar1;
  
  if (DAT_006d7c65 != '\0') {
    iVar1 = param_1 * 0x20;
    (&PTR_DAT_00570370)[param_1 * 8] = (undefined *)&DAT_00583490;
    *(undefined1 **)(&DAT_00570374 + iVar1) = &LAB_0040af10;
    *(undefined1 **)(&DAT_00570378 + iVar1) = &LAB_0040b750;
    *(undefined1 **)(&DAT_0057037c + iVar1) = &LAB_0040ad30;
    (&DAT_00570380)[iVar1] = 1;
    (&DAT_00570381)[iVar1] = param_2;
    (&DAT_00570382)[iVar1] = 0;
    (&DAT_00570383)[iVar1] = 0;
    (&DAT_00570384)[iVar1] = 1;
    *(undefined4 *)(&DAT_00570388 + iVar1) = 0;
    *(undefined4 *)(&DAT_0057038c + iVar1) = 0;
    return;
  }
  iVar1 = param_1 * 0x20;
  (&PTR_DAT_00570370)[param_1 * 8] = (undefined *)&DAT_005834b0;
  *(undefined1 **)(&DAT_00570374 + iVar1) = &LAB_0040af10;
  *(undefined1 **)(&DAT_00570378 + iVar1) = &LAB_0040b750;
  *(undefined1 **)(&DAT_0057037c + iVar1) = &LAB_0040ad30;
  (&DAT_00570380)[iVar1] = 1;
  (&DAT_00570381)[iVar1] = param_2;
  (&DAT_00570382)[iVar1] = 0;
  (&DAT_00570383)[iVar1] = 0;
  (&DAT_00570384)[iVar1] = 0;
  *(undefined4 *)(&DAT_00570388 + iVar1) = 0;
  *(undefined4 *)(&DAT_0057038c + iVar1) = 0;
  return;
}

