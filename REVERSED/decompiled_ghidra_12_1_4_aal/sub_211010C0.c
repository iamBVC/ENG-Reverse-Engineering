/* sub_211010C0 @ 211010c0   221 bytes */

undefined8 sub_211010C0(int param_1)

{
  DWORD DVar1;
  undefined4 extraout_EDX;
  undefined4 extraout_EDX_00;
  longlong lVar2;
  undefined8 uVar3;
  LARGE_INTEGER local_8;
  
  if ((DAT_21115570 & 1) == 0) {
    if (param_1 == 1) {
      DVar1 = timeGetTime();
      return CONCAT44(extraout_EDX,DVar1);
    }
    DVar1 = timeGetTime();
    return CONCAT44(extraout_EDX_00,DVar1 * 1000);
  }
  if (param_1 == 1) {
    QueryPerformanceCounter(&local_8);
    lVar2 = __allmul(local_8.s.LowPart - DAT_21115580,
                     (local_8.s.HighPart - DAT_21115584) - (uint)(local_8.s.LowPart < DAT_21115580),
                     1000,0);
    uVar3 = __alldiv((uint)lVar2,(uint)((ulonglong)lVar2 >> 0x20),DAT_21115578,DAT_2111557c);
    return uVar3;
  }
  QueryPerformanceCounter(&local_8);
  lVar2 = __allmul(local_8.s.LowPart - DAT_21115580,
                   (local_8.s.HighPart - DAT_21115584) - (uint)(local_8.s.LowPart < DAT_21115580),
                   1000000,0);
  uVar3 = __alldiv((uint)lVar2,(uint)((ulonglong)lVar2 >> 0x20),DAT_21115578,DAT_2111557c);
  return uVar3;
}

