/* sub_21109C50 @ 21109c50   196 bytes */

int __thiscall sub_21109C50(void *this,undefined4 param_1,undefined4 param_2,uint param_3)

{
  HANDLE pvVar1;
  DWORD local_4;
  
  local_4 = *(DWORD *)((int)this + 4);
  if (*(int *)((int)this + 0x14) == 0) {
    pvVar1 = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,1,0,(LPCSTR)0x0);
    *(HANDLE *)((int)this + 8) = pvVar1;
    pvVar1 = CreateThread((LPSECURITY_ATTRIBUTES)0x0,0,sub_21109DA0,this,0,&local_4);
    *(HANDLE *)((int)this + 0x14) = pvVar1;
    SetThreadPriority(pvVar1,0xf);
  }
  local_4 = 0;
  if (0 < *(int *)((int)this + 4)) {
    do {
      if (*(int *)(*(int *)this + 8 + local_4 * 0x14) == 0) {
        *(undefined4 *)(*(int *)this + local_4 * 0x14) = 0;
        *(undefined4 *)(*(int *)this + 0x10 + local_4 * 0x14) = param_1;
        *(undefined4 *)(*(int *)this + 0xc + local_4 * 0x14) = param_2;
        *(int *)(*(int *)this + 8 + local_4 * 0x14) = (int)(1000000 / (ulonglong)param_3);
        return local_4;
      }
      local_4 = local_4 + 1;
    } while ((int)local_4 < *(int *)((int)this + 4));
  }
  return -1;
}

