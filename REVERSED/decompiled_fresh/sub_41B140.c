/* sub_41B140 @ 0041b140   1786 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_41B140(void)

{
  ushort uVar1;
  byte bVar3;
  uint uVar2;
  undefined2 uVar4;
  undefined2 extraout_var;
  int iVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  bool bVar12;
  bool bVar13;
  undefined8 uVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  undefined4 uVar18;
  int local_4c;
  int local_48;
  undefined1 local_40 [64];
  
  if (DAT_00584bf0 != 0) {
    DAT_005fcf30 = 0;
    DAT_005fcf08 = 0;
    if (DAT_0058372c == 0) {
      if (DAT_00584bf4 == 0) {
        if (DAT_00584c0e == 0) {
          DAT_00584c0c = DAT_00584c0c + 1;
          DAT_00584c0e = 1;
          DAT_0057235a = 1;
        }
      }
      else {
        DAT_00584bf4 = DAT_00584bf4 + -1;
      }
    }
  }
  uVar1 = DAT_0057235a;
  iVar5 = (int)DAT_00584c0c;
  local_4c = *(int *)(&DAT_00572360 + iVar5 * 0x18);
  local_48 = *(int *)(&DAT_00572364 + iVar5 * 0x18);
  if (((DAT_00584c0e == 0) && (DAT_00584c04 == 0)) && (DAT_0058372c == 0)) {
    bVar12 = (DAT_005fcf30 & 0x80) != 0;
    DAT_005849b8 = DAT_00584c0c;
    if (bVar12) {
      DAT_0057235a = DAT_0057235a - 1;
    }
    bVar13 = (DAT_005fcf30 & 0x20) != 0;
    if (bVar13) {
      DAT_0057235a = DAT_0057235a + 1;
    }
    if (((DAT_00585018 & 0xff) - 1 == iVar5) &&
       (bVar3 = (byte)(DAT_00585018 >> 8), (short)(ushort)bVar3 < (short)DAT_0057235a)) {
      DAT_0057235a = (ushort)bVar3;
    }
    iVar6 = iVar5;
    if (((short)DAT_0057235a < 1) && (DAT_0057235a = 1, 0 < DAT_00584c0c)) {
      DAT_00584c0c = DAT_00584c0c + -1;
      DAT_00584c0e = 1;
      iVar6 = (int)DAT_00584c0c;
      DAT_0057235a = (ushort)(byte)(&DAT_00572420)[iVar6];
    }
    if (((short)(ushort)(byte)(&DAT_00572420)[iVar6] < (short)DAT_0057235a) &&
       (DAT_0057235a = (ushort)(byte)(&DAT_00572420)[iVar6], iVar6 + 1 < (int)(DAT_00585018 & 0xff))
       ) {
      DAT_00584c0c = DAT_00584c0c + 1;
      DAT_0057235a = 1;
      DAT_00584c0e = 1;
    }
    DAT_00584eb8 = DAT_00584c0c + 1;
    if ((bVar13 || bVar12) &&
       ((uVar1 != DAT_0057235a || ((iVar5 != DAT_00584c0c && (uVar1 != DAT_0057235a)))))) {
      sub_546170(0,0xffffff80,8);
      DAT_00584bfa = 0;
    }
  }
  DAT_00584ebc = (int)(short)DAT_0057235a;
  iVar5 = DAT_00584c0c * 0x18;
  _DAT_005fcff0 = *(int *)(&DAT_00572368 + iVar5);
  if (DAT_00584c0e != 0) {
    iVar6 = (0x20 - DAT_00584c0e) * (0x20 - DAT_00584c0e);
    iVar9 = DAT_005849b8 * 0x18;
    iVar7 = 0x100 - ((int)(iVar6 + (iVar6 >> 0x1f & 3U)) >> 2);
    iVar10 = 0x100 - iVar7;
    iVar6 = *(int *)(&DAT_00572360 + iVar5) * iVar7 + *(int *)(&DAT_00572360 + iVar9) * iVar10;
    local_4c = (int)(iVar6 + (iVar6 >> 0x1f & 0xffU)) >> 8;
    iVar5 = *(int *)(&DAT_00572364 + iVar5) * iVar7 + *(int *)(&DAT_00572364 + iVar9) * iVar10;
    local_48 = (int)(iVar5 + (iVar5 >> 0x1f & 0xffU)) >> 8;
    iVar5 = *(int *)(&DAT_00572368 + iVar9) * iVar10 + _DAT_005fcff0 * iVar7;
    _DAT_005fcff0 = (int)(iVar5 + (iVar5 >> 0x1f & 0xffU)) >> 8;
    DAT_00584c0e = DAT_00584c0e + 1;
    if (DAT_00584c0e == 0x20) {
      DAT_00584c0e = 0;
      DAT_00584bf0 = 0;
    }
  }
  uVar11 = -local_48;
  if (DAT_00584c04 != 0) {
    sub_436A50((&PTR_s_Se_continui_tutti_0057bbd4)[DAT_00584f04],0x50);
    sub_436A50((&PTR_s_i_dati_saranno_cancellati_0057bbd8)[DAT_00584f04],100);
    sub_436A50((&PTR_s_Sei_sicuro__0057bbc8)[DAT_00584f04],0x82);
    sub_4368D0((&PTR_DAT_0057bba8)[DAT_00584f04],0x9b,1,DAT_00584c08,1,0xe0);
    sub_4368D0((&PTR_DAT_0057bba4)[DAT_00584f04],0x9b,0,DAT_00584c08,0,0x120);
    sub_436A50((&PTR_s_INVIO_Seleziona_0057bb2c)[DAT_00584f04],0xeb);
    if (DAT_00584c04 != 0) goto LAB_0041b4f2;
  }
  if (((int)DAT_00584c0c + 1U != (DAT_00585018 & 0xff)) ||
     (DAT_0057235a != ((ushort)(DAT_00585018 >> 8) & 0xff))) {
    sub_436A50((&PTR_s_Se_giocherai_di_nuovo_in_questo_l_0057bb20)[DAT_00584f04],0xe);
    sub_436A50((&PTR_s_perderai_quelli_giocati_successi_0057bb24)[DAT_00584f04],0x20);
  }
LAB_0041b4f2:
  uVar8 = -local_4c & 0x8000003f;
  if ((int)uVar8 < 0) {
    uVar8 = (uVar8 - 1 | 0xffffffc0) + 1;
  }
  uVar2 = uVar11 & 0x8000003f;
  if ((int)uVar2 < 0) {
    uVar2 = (uVar2 - 1 | 0xffffffc0) + 1;
  }
  iVar5 = uVar2 - 0x140;
  local_48 = 0xb;
  do {
    iVar6 = uVar8 - 0x240;
    iVar7 = 0x13;
    do {
      sub_43B990(DAT_00584a4c,iVar6,iVar5,0x100,0,0x80,0x80,0x80);
      uVar4 = (undefined2)((uint)DAT_00584c04 >> 0x10);
      iVar6 = iVar6 + 0x40;
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
    iVar5 = iVar5 + 0x40;
    local_48 = local_48 + -1;
  } while (local_48 != 0);
  if (DAT_00584c04 == 0) {
    sub_436A50((&PTR_s_TASTI_FRECCIA_cambia_livello_map_0057bc6c)[DAT_00584f04],0xd7);
    sub_436A50((&PTR_s_INVIO_scegli_livello_mappa_ESC_i_0057bc70)[DAT_00584f04],0xeb);
    sub_436550(*(undefined4 *)((&PTR_PTR_0057bc94)[DAT_00584c0c] + DAT_00584f04 * 4),0x60,0x80,0x80,
               0x80,0,5,0xae);
    sub_562717(local_40,s__s__d_00571484,(&PTR_s_Capitolo_0057bc44)[DAT_00584f04],
               (int)(short)DAT_0057235a);
    sub_436550(local_40,0x73,0xa8,0xa8,0xa8,0,5,0xae);
    sub_562717(local_40,&DAT_00570300,
               *(undefined2 *)(&DAT_005722fe + (DAT_00584c0c * 5 + (int)(short)DAT_0057235a) * 2));
    uVar14 = sub_436550(local_40,0x91,0xa8,0xa8,0xa8,0,5,199);
    uVar4 = (undefined2)((ulonglong)uVar14 >> 0x10);
  }
  iVar5 = 0;
  do {
    DAT_00584bfa = DAT_00584bfa + 1;
    if (DAT_00584bfa < 0x97) {
      uVar16 = CONCAT22(uVar4,DAT_0057235a);
    }
    else {
      uVar16 = 0xffffffff;
    }
    sub_43C7B0(-local_4c,uVar11,iVar5,uVar16,DAT_00584c0c);
    if (300 < DAT_00584bfa) {
      DAT_00584bfa = 0;
    }
    iVar5 = iVar5 + 1;
    uVar4 = extraout_var;
  } while (iVar5 < 8);
  if (DAT_00584c04 == 0) {
    DAT_00584bf8 = DAT_00584bf8 + 1;
    if (0x1f < DAT_00584bf8) {
      DAT_00584bf8 = 0;
    }
    if (((&DAT_00584ece)[DAT_00584c0c * 6 + (int)(short)DAT_0057235a] & 2) == 0) {
      uVar18 = 0x80;
      uVar17 = 0x80;
      uVar15 = 0x80;
      uVar16 = (&DAT_00584a54)[(int)((int)DAT_00584bf8 + ((int)DAT_00584bf8 >> 0x1f & 3U)) >> 2];
    }
    else {
      uVar18 = 0x15;
      uVar17 = 0x65;
      uVar15 = 0x7f;
      uVar16 = (&DAT_00584a54)[(int)((int)DAT_00584bf8 + ((int)DAT_00584bf8 >> 0x1f & 3U)) >> 2];
    }
    sub_43B990(uVar16,0x8a,0x7f,0,0,uVar15,uVar17,uVar18);
    if (((&DAT_00584ece)[DAT_00584c0c * 6 + (int)(short)DAT_0057235a] & 1) != 0) {
      sub_43B990((&DAT_00584a78)[(int)((int)DAT_00584bf8 + ((int)DAT_00584bf8 >> 0x1f & 7U)) >> 3],
                 0x55,0x7d,0,0,0x80,0x80,0x80);
    }
    if (((((&DAT_00584ece)[DAT_00584c0c * 6 + (int)(short)DAT_0057235a] & 1) != 0) &&
        (((&DAT_00584ece)[DAT_00584c0c * 6 + (int)(short)DAT_0057235a] & 2) != 0)) &&
       (0x10 < DAT_00584bf8)) {
      sub_436550((&PTR_s_Spazio_per_vista_galleria_0057bc88)[DAT_00584f04],0x4b,0x80,0x80,0x80,0,5,
                 0xae);
    }
  }
  return;
}

