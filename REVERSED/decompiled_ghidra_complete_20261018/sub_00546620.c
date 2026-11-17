/* sub_546620 @ 00546620   523 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 sub_546620(int param_1,undefined4 param_2,short param_3)

{
  int iVar1;
  int iVar2;
  undefined4 local_11c;
  undefined2 local_118;
  undefined2 local_116;
  int local_114;
  int local_110;
  undefined2 local_10c;
  undefined2 local_10a;
  undefined2 local_108;
  undefined1 local_104 [260];
  
  local_11c = 0xffffffff;
  if ((((DAT_005834dc != 0) && (param_1 != -1)) && ((uint)(int)param_3 < DAT_006d91c8)) &&
     (DAT_006d91c4 != 0)) {
    iVar1 = param_3 * 0x10;
    _DAT_006d93e0 = 0;
    DAT_006d93e4 = *(short *)(iVar1 + 4 + DAT_006d91c4);
    _DAT_006d93e6 = *(undefined2 *)(DAT_006d9490 + 0x5c);
    _DAT_006d93e8 = 0x2000;
    _DAT_006d93ea = 0;
    DAT_006d94a0 = sub_5487A0(&DAT_006d93e0,param_2,0,&local_11c);
    if (DAT_006d94a0 != 0) {
      sub_562717(local_104,s__s_CVS_00578e50,s_ENGLISH_00578940);
      iVar2 = sub_415690(s_Music_00578e48,local_104);
      if (iVar2 != 0) {
        DAT_006d91d8 = sub_546830(iVar2);
        if (DAT_006d91d8 != 0) {
          *(undefined4 *)(DAT_006d94a0 + 0x38) = 0x40000;
          *(undefined4 *)(DAT_006d94a0 + 0x34) = 0x4000;
          *(int *)(DAT_006d94a0 + 0x58) = *(int *)(iVar1 + 8 + DAT_006d91c4) + DAT_006d91d8;
          *(uint *)(DAT_006d94a0 + 0x54) =
               *(int *)(iVar1 + 0xc + DAT_006d91c4) + 0x7ffU & 0xfffff800;
          _DAT_006d93f4 =
               _AAL_LoadResourceType_16
                         (*(undefined4 *)(DAT_006d94a0 + 0x58),*(undefined4 *)(DAT_006d94a0 + 0x54),
                          0x15,0);
          if (_DAT_006d93f4 != 0) {
            local_108 = 0;
            local_118 = 1;
            local_116 = 1;
            local_10a = 0x10;
            local_10c = 2;
            local_114 = DAT_006d93e4 * 0xac44 >> 0xc;
            local_110 = local_114 * 2;
            _AAL_SetResource_8(_DAT_006d93f4,&local_118);
            *(undefined4 *)(DAT_006d9498 + 0x60) = 0x800;
            *(undefined4 *)(DAT_006d9498 + 100) = 0xffffff00;
            sub_5489C0(DAT_006d9498 + 0x10,DAT_006d94a0);
            return local_11c;
          }
        }
      }
    }
  }
  return 0xffffffff;
}

