/* sub_41C230 @ 0041c230   799 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_41C230(void)

{
  int iVar1;
  undefined *puVar2;
  
  iVar1 = sub_414FB0();
  if (iVar1 == 0) {
    DAT_005fcf08 = 0;
    DAT_005fcf30 = 0;
  }
  switch(DAT_00584c1c) {
  case 0:
    sub_41C1A0();
    return;
  case 5:
    if (DAT_005855b0 == 0) {
      puVar2 = (&PTR_s_INVIO_Salva_il_gioco_0057bc08)[DAT_00584f04];
    }
    else {
      if ((&DAT_00585274)[DAT_00584c28 * 0x100] != '\0') {
        sub_436740((&PTR_s_INVIO_Carica_e_continua_il_gioco_0057bbf4)[DAT_00584f04],0xe,0x80,0x80,
                   0x80);
        sub_436740((&PTR_s_SPAZIO_Cancella_e_inizia_un_nuov_0057bbf8)[DAT_00584f04],0x1f,0x80,0x80,
                   0x80);
        goto LAB_0041c310;
      }
      puVar2 = (&PTR_s_INVIO_Inizia_un_nuovo_gioco_ESC_I_0057bbfc)[DAT_00584f04];
    }
    sub_436740(puVar2,0xe,0x80,0x80,0x80);
LAB_0041c310:
    sub_436740((&PTR_s_TASTI_FRECCIA_scegli_un_gioco_0057bc64)[DAT_00584f04],0x8c,0x80,0x80,0x80);
    sub_41C5A0();
    return;
  case 0xf:
    _DAT_005855c4 = 1;
    sub_41C620();
    sub_41C820();
    DAT_00584c1c = 0x10;
    return;
  case 0x10:
    if (DAT_006d9c18 != 0) {
      sub_41CD10();
      return;
    }
    break;
  case 0x11:
    if (((DAT_005fcf30 & 0x20) == 0) || (DAT_005855a0 == 0)) {
      if (((DAT_005fcf30 & 0x80) != 0) && (DAT_005855a0 == 0)) {
        sub_546170(0,0xffffff80,8);
        DAT_005855a0 = 1;
      }
    }
    else {
      sub_546170(0,0xffffff80,8);
      DAT_005855a0 = 0;
    }
    sub_436740((&PTR_s_INVIO_Seleziona_0057bb2c)[DAT_00584f04],0xe,0x80,0x80,0x80);
    sub_436740((&PTR_s_Salvare__0057bc10)[DAT_00584f04],0x50,0x80,0x80,0x80);
    sub_4368D0((&PTR_DAT_0057bba8)[DAT_00584f04],0x78,1,DAT_005855a0,5,0xe0);
    sub_4368D0((&PTR_DAT_0057bba4)[DAT_00584f04],0x78,0,DAT_005855a0,4,0x120);
    return;
  case 0x13:
    sub_41C640();
    DAT_006d9c18 = 0x2d;
    DAT_00584c1c = 0xd;
    return;
  case 0x15:
    _DAT_0058521c = sub_41C160();
    _DAT_005855c0 = 0;
    break;
  case 0x1b:
  case 0x1c:
    if (((DAT_005fcf30 & 0x20) == 0) || (DAT_005855a0 == 0)) {
      if (((DAT_005fcf30 & 0x80) != 0) && (DAT_005855a0 == 0)) {
        sub_546170(0,0xffffff80,8);
        DAT_005855a0 = 1;
      }
    }
    else {
      sub_546170(0,0xffffff80,8);
      DAT_005855a0 = 0;
    }
    sub_436740((&PTR_s_INVIO_Seleziona_0057bb2c)[DAT_00584f04],0xe,0x80,0x80,0x80);
    sub_436740((&PTR_s_Sei_sicuro__0057bbc8)[DAT_00584f04],0x50,0x80,0x80,0x80);
    sub_4368D0((&PTR_DAT_0057bba8)[DAT_00584f04],0x78,1,DAT_005855a0,5,0xe0);
    sub_4368D0((&PTR_DAT_0057bba4)[DAT_00584f04],0x78,0,DAT_005855a0,4,0x120);
    return;
  }
  return;
}

