/* sub_40FF40 @ 0040ff40   129 bytes */

undefined1 sub_40FF40(void)

{
  undefined1 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  uVar2 = sub_405790(s_DisplayDevice_00571784,&DAT_0057f834,0);
  uVar2 = sub_56D4ED(uVar2);
  uVar3 = sub_405790(s_D3DDevice_00571778,&DAT_0057f834,0);
  uVar3 = sub_56D4ED(uVar3);
  local_4 = 0x1e0;
  local_c = 0x1e0;
  local_8 = 0x280;
  local_10 = 0x280;
  uVar1 = sub_40FFD0(uVar2,uVar3,0x20,0x20,&local_8,&local_10);
  sub_5628BC(uVar2);
  sub_5628BC(uVar3);
  return uVar1;
}

