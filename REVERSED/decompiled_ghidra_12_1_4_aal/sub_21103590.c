/* _AAL_WriteRawData@8 @ 21103590   28 bytes */

DWORD _AAL_WriteRawData_8(void *param_1,HANDLE param_2)

{
  DWORD DVar1;
  
                    /* 0x3590  76  _AAL_WriteRawData@8 */
  DVar1 = 0xffffffff;
  if ((param_1 != (void *)0x0) && (param_2 != (HANDLE)0x0)) {
    DVar1 = sub_211084C0(param_1,param_2);
  }
  return DVar1;
}

