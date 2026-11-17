/* sub_2110F827 @ 2110f827   100 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined * sub_2110F827(void)

{
  undefined4 in_stack_ffffffd8;
  undefined2 uVar1;
  uint local_10;
  uint uStack_c;
  undefined2 uStack_8;
  
  uVar1 = (undefined2)((uint)in_stack_ffffffd8 >> 0x10);
  sub_2110F88B(&local_10,(uint *)&stack0x00000004);
  _DAT_211157a8 = sub_21111028(local_10,uStack_c,CONCAT22(uVar1,uStack_8),0x11,0,&DAT_21115780);
  _DAT_211157a0 = (int)DAT_21115782;
  _DAT_211157a4 = (int)DAT_21115780;
  _DAT_211157ac = &DAT_21115784;
  return &DAT_211157a0;
}

