/* sub_56D3B4 @ 0056d3b4   53 bytes */

int __thiscall sub_56D3B4(int param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  
  cVar1 = sub_413F10(param_3,1);
  if (cVar1 != '\0') {
    sub_566D90(*(undefined4 *)(param_1 + 4),param_2,param_3);
    *(int *)(param_1 + 8) = param_3;
    *(undefined1 *)(*(int *)(param_1 + 4) + param_3) = 0;
  }
  return param_1;
}

