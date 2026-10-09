/* sub_40DB90 @ 0040db90   456 bytes */

void sub_40DB90(int param_1)

{
  undefined1 uVar1;
  undefined *puVar2;
  int iVar3;
  uint uVar4;
  char cVar5;
  undefined1 local_40 [64];
  
  if (DAT_006d9e74 != 0) {
    if (param_1 == 1) {
      puVar2 = (&PTR_s_Salvataggio_gioco_1_0057bc14)[DAT_00584f04];
    }
    else if (param_1 == 2) {
      puVar2 = (&PTR_s_Salvataggio_gioco_2_0057bc18)[DAT_00584f04];
    }
    else {
      puVar2 = (&PTR_s_Salvataggio_gioco_3_0057bc1c)[DAT_00584f04];
    }
    sub_436740(puVar2,0xb4,0x80,0x80,0x80);
    iVar3 = DAT_00584c28 * 0x100;
    if ((&DAT_00585274)[iVar3] == '\0') {
      sub_436740((&PTR_s_VUOTO_0057bbe4)[DAT_00584f04],0xc6,0x80,0x80,0x80);
    }
    else {
      cVar5 = (&DAT_005852b7)[iVar3];
      uVar4 = (uint)(byte)(&DAT_005852b6)[iVar3];
      uVar1 = *(undefined1 *)((int)&DAT_00585278 + iVar3 + 3);
      if (uVar4 != 0) {
        uVar4 = uVar4 - 1;
      }
      if (cVar5 == '\0') {
        cVar5 = '\x01';
      }
      sub_436550(*(undefined4 *)((&PTR_PTR_0057bc94)[uVar4] + DAT_00584f04 * 4),0xc6,0x80,0x80,0x80,
                 0,6,0x32);
      sub_562717(local_40,s__s__d_00571484,(&PTR_s_Capitolo_0057bc44)[DAT_00584f04],cVar5);
      sub_436550(local_40,0xc6,0x80,0x80,0x80,0,6,0x100);
      sub_436550((&PTR_s_Monete_d_oro_0057bc48)[DAT_00584f04],0xd8,0x80,0x80,0x80,0,6,0x32);
      sub_562717(local_40,&DAT_00570300,uVar1);
      sub_436550(local_40,0xd8,0x80,0x80,0x80,0,6,0x100);
    }
    if (DAT_006d9ce8 == 0) {
      sub_427E90();
    }
  }
  return;
}

