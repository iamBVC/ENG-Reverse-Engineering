/* sub_2110D967 @ 2110d967   54 bytes */

void __cdecl sub_2110D967(uint *param_1)

{
  int *piVar1;
  
  if ((param_1 <= DAT_21114ec8) && (piVar1 = sub_2110EB72(param_1), piVar1 != (int *)0x0)) {
    return;
  }
  if (param_1 == (uint *)0x0) {
    param_1 = (uint *)0x1;
  }
  HeapAlloc(DAT_21115b44,0,(int)param_1 + 0xfU & 0xfffffff0);
  return;
}

