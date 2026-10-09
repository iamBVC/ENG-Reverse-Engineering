/* sub_558C90 @ 00558c90   149 bytes */

void sub_558C90(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 local_4;
  
  DAT_006da354 = sub_41EF00(0x800);
  uVar2 = param_2;
  iVar1 = param_1;
  iVar3 = 0;
  *(undefined4 *)(param_1 + 0x10) = DAT_006da354;
  do {
    sub_415AF0(uVar2,&param_1);
    sub_415AF0(uVar2,&param_2);
    sub_415AF0(uVar2,&local_4);
    sub_415AF0(uVar2,(int)&local_4 + 2);
    *(undefined2 *)(iVar3 + *(int *)(iVar1 + 0x10)) = (undefined2)param_1;
    *(undefined2 *)(iVar3 + 2 + *(int *)(iVar1 + 0x10)) = (undefined2)param_2;
    *(undefined2 *)(iVar3 + 4 + *(int *)(iVar1 + 0x10)) = (undefined2)local_4;
    *(undefined2 *)(iVar3 + 6 + *(int *)(iVar1 + 0x10)) = local_4._2_2_;
    iVar3 = iVar3 + 8;
  } while (iVar3 < 0x800);
  return;
}

