/* sub_2110D99D @ 2110d99d   47 bytes */

void __cdecl sub_2110D99D(LPVOID param_1)

{
  uint *puVar1;
  
  if (param_1 != (LPVOID)0x0) {
    puVar1 = (uint *)sub_2110E81C((int)param_1);
    if (puVar1 != (uint *)0x0) {
      sub_2110E847(puVar1,(uint)param_1);
      return;
    }
    HeapFree(DAT_21115b44,0,param_1);
  }
  return;
}

