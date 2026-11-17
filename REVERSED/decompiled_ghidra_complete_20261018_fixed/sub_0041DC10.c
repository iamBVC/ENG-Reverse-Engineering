/* sub_41DC10 @ 0041dc10   34 bytes */

bool sub_41DC10(void)

{
  DWORD DVar1;
  
  CreateMutexA((LPSECURITY_ATTRIBUTES)0x0,0,"Emperors New Groove");
  DVar1 = GetLastError();
  return DVar1 == 0xb7;
}

