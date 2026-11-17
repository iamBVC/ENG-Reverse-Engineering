/* sub_40DD60 @ 0040dd60   635 bytes */

void sub_40DD60(int param_1)

{
  undefined *puVar1;
  int iVar2;
  undefined1 local_40 [64];
  
  if (DAT_005846e4 != 4) {
    if (param_1 == 0) {
      sub_436A50(*(undefined4 *)((&PTR_DAT_0057bc90)[DAT_0058500c] + DAT_00584f04 * 4),0x3e);
      puVar1 = (&PTR_s_Capitolo_0057bc44)[DAT_00584f04];
      iVar2 = DAT_00585010;
    }
    else {
      if (DAT_006da294 == '\0') {
        return;
      }
      sub_436A50(*(undefined4 *)((&PTR_DAT_0057bc90)[DAT_00584eb8] + DAT_00584f04 * 4),0x3e);
      puVar1 = (&PTR_s_Capitolo_0057bc44)[DAT_00584f04];
      iVar2 = DAT_00584ebc;
    }
    sub_562717(local_40,s__s__d_00571484,puVar1,iVar2);
    sub_436A50(local_40,0x52);
    if (param_1 == 0) {
      sub_562717(local_40,s__s__d____d_0057148c,(&PTR_s_Monete_raccolte_0057bc50)[DAT_00584f04],
                 (uint)(&DAT_00584f1c)[DAT_00585010 + DAT_0058500c * 6] >> 0xc,DAT_005ff064);
      DAT_00581d78 = DAT_00581d78 + 1;
      if (((&DAT_00584ec8)[DAT_0058500c * 6 + DAT_00585010] & 1) != 0) {
        sub_427E00((int)DAT_00581d78);
      }
      if (((&DAT_00584ec8)[DAT_0058500c * 6 + DAT_00585010] & 2) != 0) {
        sub_427E40((int)DAT_00581d78);
      }
    }
    else {
      sub_562717(local_40,s__s__d_00571484,(&PTR_s_Monete_0057bc5c)[DAT_00584f04],DAT_005ff070);
    }
    sub_436A50(local_40,0x6e);
    if (param_1 == 0) {
      sub_562717(local_40,s__s__d____d_0057148c,(&PTR_s_Segreti_trovati_0057bc54)[DAT_00584f04],
                 DAT_00584e64,DAT_005ff06c);
      sub_436A50(local_40,0x82);
      if (DAT_006d9c08 != 0) {
        sub_436A50((&PTR_s_Sei_sicuro__0057bbc8)[DAT_00584f04],0xb4);
        sub_4368D0((&PTR_DAT_0057bba8)[DAT_00584f04],200,1,DAT_006d9c10,5,0xe0);
        sub_4368D0((&PTR_DAT_0057bba4)[DAT_00584f04],200,0,DAT_006d9c10,4,0x120);
        return;
      }
      sub_436A50((&PTR_s_Premi_INVIO_per_salvare_0057bb48)[DAT_00584f04],0xb4);
      sub_436A50((&PTR_s_Oppure_premi_ESC_per_continuare_0057bb4c)[DAT_00584f04],200);
    }
  }
  return;
}

