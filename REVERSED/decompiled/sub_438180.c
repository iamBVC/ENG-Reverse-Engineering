/* sub_438180 @ 00438180   1617 bytes */

undefined4 sub_438180(void)

{
  uint *puVar1;
  uint *puVar2;
  bool bVar3;
  char cVar4;
  char cVar5;
  char cVar6;
  char cVar7;
  char cVar8;
  char cVar9;
  char cVar10;
  char cVar11;
  char cVar12;
  int iVar13;
  int iVar14;
  int *piVar15;
  undefined1 uVar16;
  undefined4 *puVar17;
  undefined4 *puVar18;
  char *local_20;
  undefined4 local_1c;
  char local_18;
  undefined1 local_17;
  undefined1 local_16;
  undefined1 local_15;
  undefined1 local_14;
  char local_13;
  char local_12;
  char local_11;
  char local_10;
  char local_f;
  undefined1 local_d;
  
  cVar12 = DAT_006d7c70;
  cVar11 = DAT_006d7c6f;
  cVar10 = DAT_006d7c6e;
  cVar9 = DAT_006d7c6d;
  cVar8 = DAT_006d7c69;
  cVar7 = DAT_006d7c68;
  cVar5 = DAT_006d7c66;
  cVar4 = DAT_006d7c65;
  if (DAT_00584644 == 0) {
    iVar13 = 3;
  }
  else {
    iVar13 = *(int *)(DAT_00584644 + 0x34);
  }
  if ((DAT_00573d28 < 0) || (4 < DAT_00573d28)) {
    DAT_00573d28 = 4;
  }
  puVar17 = &DAT_00573d28;
  puVar18 = &local_1c;
  for (iVar14 = 7; iVar14 != 0; iVar14 = iVar14 + -1) {
    *puVar18 = *puVar17;
    puVar17 = puVar17 + 1;
    puVar18 = puVar18 + 1;
  }
  sub_4387E0();
  sub_4388D0(&local_1c,&local_1c);
  DAT_006d7c62 = local_16;
  DAT_006d7c64 = local_15;
  DAT_006d7c61 = local_17;
  DAT_006d7c60 = local_18;
  DAT_006d7c63 = local_14;
  DAT_006d7c65 = local_13;
  if ((local_12 == '\0') || (DAT_006d7c66 = '\x01', DAT_005833f3 == '\0')) {
    DAT_006d7c66 = '\0';
  }
  if ((local_12 == '\0') || (DAT_006d7c67 = '\x01', DAT_005833f4 == '\0')) {
    DAT_006d7c67 = '\0';
  }
  if ((local_12 == '\0') || (DAT_006d7c68 = '\x01', DAT_005833f7 == '\0')) {
    DAT_006d7c68 = '\0';
  }
  DAT_006d7c69 = local_11;
  if ((iVar13 == 2) && (local_18 != '\0')) {
    bVar3 = true;
    DAT_006d7c6b = 1;
LAB_004382d9:
    DAT_006d7c6c = 0;
    DAT_006d7c6a = 0;
    if (!bVar3) goto LAB_004382f2;
  }
  else {
    bVar3 = false;
    DAT_006d7c6b = 0;
    if ((iVar13 != 3) || (local_f == '\0')) goto LAB_004382d9;
    DAT_006d7c6c = 1;
  }
  DAT_006d7c6a = 1;
LAB_004382f2:
  DAT_006d7c6d = local_10;
  if ((((local_10 != '\0') && ((char)DAT_005833e4 != '\0')) && (local_13 == '\0')) ||
     (DAT_006d7c6e = '\x01', DAT_005833eb == '\0')) {
    DAT_006d7c6e = '\0';
  }
  if (((local_10 == '\0') && (DAT_005833eb != '\0')) ||
     (((char)DAT_005833e4 == '\0' || (DAT_006d7c70 = '\x01', local_13 != '\0')))) {
    DAT_006d7c70 = '\0';
  }
  if ((local_18 == '\0') || (DAT_006d7c6f = '\x01', DAT_005833f9 == '\0')) {
    DAT_006d7c6f = '\0';
  }
  DAT_006d7c71 = local_d;
  sub_438A90(0);
  if (DAT_006d7c66 == '\0') {
    sub_438B80(1);
  }
  else {
    sub_438AC0();
  }
  if (DAT_006d7c68 == '\0') {
    if (DAT_006d7c66 == '\0') {
      sub_438B80(2);
    }
    else {
      sub_438AC0();
    }
  }
  else {
    sub_438B00(2);
  }
  if (DAT_006d7c66 == '\0') {
    sub_438B80(3);
  }
  else {
    sub_438AC0();
  }
  if (DAT_006d7c68 == '\0') {
    if (DAT_006d7c66 == '\0') {
      sub_438B80(4);
    }
    else {
      sub_438AC0();
    }
  }
  else if (DAT_006d7c66 == '\0') {
    sub_438B00(4);
  }
  else {
    sub_438B40();
  }
  cVar6 = DAT_006d7c67;
  iVar13 = 0;
  do {
    puVar1 = (uint *)((int)&DAT_00574060 + iVar13);
    *puVar1 = *(uint *)((int)&DAT_00573eb8 + iVar13);
    *(undefined4 *)((int)&DAT_00574064 + iVar13) = *(undefined4 *)((int)&DAT_00573ebc + iVar13);
    *(undefined4 *)((int)&DAT_00574068 + iVar13) = *(undefined4 *)((int)&DAT_00573ec0 + iVar13);
    if (cVar6 != '\0') {
      *puVar1 = *puVar1 | 1;
      *(uint *)((int)&DAT_00574064 + iVar13) = *(uint *)((int)&DAT_00574064 + iVar13) | 1;
    }
    iVar13 = iVar13 + 0xc;
  } while (iVar13 < 0x3c);
  sub_438BB0(0);
  sub_438C10(1);
  if (DAT_006d7c69 == '\0') {
    if (DAT_006d7c70 == '\0') {
      sub_438FD0(2,1);
    }
    else {
      sub_4390A0();
    }
  }
  else {
    sub_438CD0(2);
  }
  if (DAT_006d7c68 == '\0') {
    if (DAT_006d7c69 == '\0') {
      sub_438FD0(3,0);
    }
    else {
      sub_438CD0(3);
    }
  }
  else {
    sub_438D40(3);
  }
  if (DAT_006d7c6d == '\0') {
    if (DAT_006d7c70 == '\0') {
      sub_438C10(4);
    }
    else {
      sub_438E80();
    }
  }
  else {
    sub_438E10(4);
  }
  if (DAT_006d7c68 == '\0') {
    if (DAT_006d7c69 == '\0') {
      if (DAT_006d7c70 == '\0') {
        sub_438FD0(5,0);
      }
      else {
        sub_4390A0();
      }
    }
    else {
      sub_438CD0(5);
    }
  }
  else if (DAT_006d7c6d == '\0') {
    if (DAT_006d7c70 == '\0') {
      sub_438D40(5);
    }
    else {
      sub_438F60();
    }
  }
  else {
    sub_438EF0(5);
  }
  if (DAT_006d7c66 == '\0') {
    if (DAT_006d7c69 == '\0') {
      sub_438FD0(6,0);
    }
    else {
      sub_438CD0(6);
    }
  }
  else {
    sub_438C10(6);
  }
  if (DAT_006d7c66 == '\0') {
    if (DAT_006d7c69 == '\0') {
      if (DAT_006d7c70 == '\0') {
        sub_438FD0(7,0);
      }
      else {
        sub_4390A0();
      }
    }
    else {
      sub_438CD0(7);
    }
  }
  else if (DAT_006d7c6d == '\0') {
    if (DAT_006d7c70 == '\0') {
      sub_438C10(7);
    }
    else {
      sub_438E80();
    }
  }
  else {
    sub_438E10(7);
  }
  iVar13 = 0;
  piVar15 = &DAT_00574208;
  do {
    local_20 = (char *)((int)&DAT_00573ec0 + 1);
    do {
      puVar1 = (uint *)((int)&DAT_00573ef8 + iVar13);
      iVar14 = *piVar15 * 0x20;
      *puVar1 = *(uint *)(&DAT_00570388 + iVar14);
      *(undefined4 *)((int)&DAT_00573efc + iVar13) = *(undefined4 *)(&DAT_0057038c + iVar14);
      if (((&DAT_00570381)[iVar14] == '\0') &&
         (((&DAT_00570380)[iVar14] == '\0' || (local_20[-1] == '\0')))) {
        uVar16 = 0;
      }
      else {
        uVar16 = 1;
      }
      *(undefined1 *)((int)&DAT_00573f00 + iVar13) = uVar16;
      if (((&DAT_00570383)[iVar14] == '\0') || (*local_20 == '\0')) {
        uVar16 = 0;
      }
      else {
        uVar16 = 1;
      }
      *(undefined1 *)((int)&DAT_00573f00 + iVar13 + 1) = uVar16;
      if ((DAT_006d7c66 != '\0') && (*(char *)((int)&DAT_00573f00 + iVar13) != '\0')) {
        *puVar1 = *puVar1 | 1;
        *(uint *)((int)&DAT_00573efc + iVar13) = *(uint *)((int)&DAT_00573efc + iVar13) | 1;
        *(undefined1 *)((int)&DAT_00573f00 + iVar13 + 1) = 1;
      }
      puVar2 = (uint *)((int)&DAT_005740a0 + iVar13);
      *puVar2 = *puVar1;
      *(undefined4 *)((int)&DAT_005740a4 + iVar13) = *(undefined4 *)((int)&DAT_00573efc + iVar13);
      *(undefined4 *)((int)&DAT_005740a8 + iVar13) = *(undefined4 *)((int)&DAT_00573f00 + iVar13);
      if (((DAT_006d7c67 != '\0') && (DAT_005833f1 != '\0')) || ((*puVar1 & 2) == 0)) {
        *puVar2 = *puVar2 | 1;
        *(uint *)((int)&DAT_005740a4 + iVar13) = *(uint *)((int)&DAT_005740a4 + iVar13) | 1;
      }
      piVar15 = piVar15 + 1;
      local_20 = local_20 + 0xc;
      iVar13 = iVar13 + 0xc;
    } while ((int)local_20 < 0x573efd);
  } while ((int)piVar15 < 0x574280);
  if (((((cVar4 == DAT_006d7c65) && (cVar5 == DAT_006d7c66)) &&
       ((cVar7 == DAT_006d7c68 && ((cVar8 == DAT_006d7c69 && (cVar9 == DAT_006d7c6d)))))) &&
      (cVar10 == DAT_006d7c6e)) && ((cVar11 == DAT_006d7c6f && (cVar12 == DAT_006d7c70)))) {
    return 0;
  }
  return 1;
}

