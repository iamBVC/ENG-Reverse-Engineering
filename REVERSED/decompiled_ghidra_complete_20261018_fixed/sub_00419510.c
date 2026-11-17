/* sub_419510 @ 00419510   170 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sub_419510(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  CHAR local_50 [80];
  
  sub_41ACA0();
  _DAT_00584630 = 0;
  sub_558820(&DAT_00584668,param_1,param_2,param_3,param_4);
  cVar1 = sub_558880(&DAT_00584668);
  if (cVar1 == '\0') {
    sub_562717(local_50,s_Couldnt_load_wad_tribe__d__level_00571f84,param_1,param_2,param_3,param_4)
    ;
    MessageBoxA(*(HWND *)PTR_DAT_005724dc,local_50,s_Can_t_find_Wad_00571f74,0x10);
    sub_41DF60();
    return 0;
  }
  _DAT_00571f68 = param_3;
  _DAT_00571f64 = param_2;
  _DAT_00571f60 = param_1;
  _DAT_00571f6c = param_4;
  return 1;
}

