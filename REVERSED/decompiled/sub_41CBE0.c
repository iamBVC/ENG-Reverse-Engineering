/* sub_41CBE0 @ 0041cbe0   129 bytes */

undefined4 sub_41CBE0(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 local_100 [256];
  
  uVar1 = sub_405790(s_HDPath_00571d94,0,0);
  sub_562717(local_100,s__sking_d_ksv_005724c0,uVar1,DAT_00584c28);
  iVar2 = sub_562AEE(local_100,&DAT_00571710);
  if (iVar2 == 0) {
    return 1;
  }
  sub_562B75(&DAT_00585274 + DAT_00584c28 * 0x100,0x100,1,iVar2);
  sub_5628EB(iVar2);
  return 0;
}

