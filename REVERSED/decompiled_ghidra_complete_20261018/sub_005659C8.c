/* sub_5659C8 @ 005659c8   36 bytes */

undefined4 sub_5659C8(int *param_1,undefined4 param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  do {
    *param_1 = *param_1 + 1;
    uVar1 = sub_565997(param_2);
    iVar2 = sub_562E7B(uVar1);
  } while (iVar2 != 0);
  return uVar1;
}

