/* sub_40FE30 @ 0040fe30   261 bytes */

undefined1 sub_40FE30(void)

{
  undefined1 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  uVar2 = sub_405790(s_DisplayDevice_00571784,&DAT_0057f834,0);
  uVar2 = sub_56D4ED(uVar2);
  uVar3 = sub_405790(s_D3DDevice_00571778,&DAT_0057f834,0);
  uVar3 = sub_56D4ED(uVar3);
  sub_4057C0(s_ScreenBPP_0057176c,0x42000000,0);
  uVar4 = __ftol();
  sub_4057C0(s_ScreenW_00571764,0x44200000,0);
  local_8 = __ftol();
  sub_4057C0(s_ScreenH_0057175c,0x43f00000,0);
  local_4 = __ftol();
  sub_4057C0(s_SoftwareScreenBPP_00571748,0x42000000,0);
  uVar5 = __ftol();
  sub_4057C0(s_SoftwareScreenW_00571738,0x43a00000,0);
  local_10 = __ftol();
  sub_4057C0(s_SoftwareScreenH_00571728,0x43480000,0);
  local_c = __ftol();
  uVar1 = sub_40FFD0(uVar2,uVar3,uVar4,uVar5,&local_8,&local_10);
  sub_5628BC(uVar2);
  sub_5628BC(uVar3);
  return uVar1;
}

