/* sub_41C0E0 @ 0041c0e0   123 bytes */

void sub_41C0E0(void)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined1 local_100 [256];
  
  iVar3 = 0;
  puVar4 = &DAT_00585274;
  do {
    uVar1 = sub_405790(s_HDPath_00571d94,0,0);
    sub_562717(local_100,s__sking_d_ksv_005724c0,uVar1,iVar3);
    iVar2 = sub_562AEE(local_100,&DAT_00570350);
    if (iVar2 == 0) {
      *puVar4 = 0;
    }
    else {
      sub_5629E6(puVar4,0x100,1,iVar2);
      sub_5628EB(iVar2);
    }
    puVar4 = puVar4 + 0x100;
    iVar3 = iVar3 + 1;
  } while ((int)puVar4 < 0x585574);
  return;
}

