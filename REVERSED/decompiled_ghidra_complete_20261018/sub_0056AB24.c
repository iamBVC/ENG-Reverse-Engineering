/* sub_56AB24 @ 0056ab24   28 bytes */

bool sub_56AB24(LPVOID param_1,UINT_PTR param_2)

{
  BOOL BVar1;
  
  BVar1 = IsBadWritePtr(param_1,param_2);
  return BVar1 == 0;
}

