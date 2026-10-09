/* sub_4134C0 @ 004134c0   35 bytes */

int sub_4134C0(int param_1,char *param_2)

{
  char *_Str1;
  int iVar1;
  
  _Str1 = (char *)sub_405720(*(undefined4 *)(param_1 + 0xc));
  iVar1 = __strcmpi(_Str1,param_2);
  return -(uint)(iVar1 != 0);
}

