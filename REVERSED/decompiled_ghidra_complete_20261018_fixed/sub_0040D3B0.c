/* sub_40D3B0 @ 0040d3b0   153 bytes */

undefined4 sub_40D3B0(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  void *pvVar2;
  int local_14;
  int local_10;
  undefined4 local_8;
  size_t local_4;
  
  iVar1 = sub_562AEE(param_1,&DAT_00570350);
  if (iVar1 != 0) {
    sub_5629E6(&local_14,0x14,1,iVar1);
    if (((local_14 == -0x765067e9) && (local_10 == 0x12d142fe)) &&
       (pvVar2 = _malloc(local_4), pvVar2 != (void *)0x0)) {
      sub_5629E6(pvVar2,local_4,1);
      sub_40D300(pvVar2,param_2,local_8);
      sub_5628BC(pvVar2);
      return local_8;
    }
    sub_5628EB(iVar1);
  }
  return 0;
}

