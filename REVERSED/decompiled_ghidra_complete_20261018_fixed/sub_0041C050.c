/* sub_41C050 @ 0041c050   144 bytes */

void sub_41C050(void)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined1 local_200 [256];
  undefined1 local_100 [256];
  
  local_100[0] = 0;
  iVar3 = 0;
  do {
    uVar1 = sub_405790(s_HDPath_00571d94,0,0);
    sub_562717(local_200,s__sking_d_ksv_005724c0,uVar1,iVar3);
    iVar2 = sub_562AEE(local_200,&DAT_00570350);
    if (iVar2 == 0) {
      uVar1 = sub_562AEE(local_200,&DAT_00571710);
      sub_562B75(local_100,0x100,1,uVar1);
      sub_5628EB(uVar1);
    }
    else {
      sub_5628EB(iVar2);
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 < 3);
  return;
}

