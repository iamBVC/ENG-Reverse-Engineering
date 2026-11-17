/* _AAL_WriteResampledData@16 @ 211035b0   38 bytes */

int _AAL_WriteResampledData_16(void *param_1,HANDLE param_2,byte param_3,int param_4)

{
  int iVar1;
  
                    /* 0x35b0  77  _AAL_WriteResampledData@16 */
  iVar1 = -1;
  if ((param_1 != (void *)0x0) && (param_2 != (HANDLE)0x0)) {
    iVar1 = sub_211086C0(param_1,param_2,param_3,param_4);
  }
  return iVar1;
}

