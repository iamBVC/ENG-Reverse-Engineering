/* sub_419810 @ 00419810   471 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_419810(void)

{
  char cVar1;
  int *piVar2;
  int iVar3;
  undefined4 *puVar4;
  
  puVar4 = &DAT_005847c8;
  for (iVar3 = 0xe; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar4 = 0xffffffff;
    puVar4 = puVar4 + 1;
  }
  DAT_005847c8 = 0xcb;
  DAT_005847cc = 0xcd;
  _DAT_005847d0 = 200;
  _DAT_005847d4 = 0xd0;
  _DAT_005847d8 = 0x1e;
  _DAT_005847dc = 0x1f;
  _DAT_005847e4 = 0x2d;
  _DAT_005847e0 = 0x39;
  _DAT_005847e8 = 0x1c;
  _DAT_005847ec = 0x19;
  _DAT_005847f0 = 0xc9;
  _DAT_005847f4 = 0xd1;
  _DAT_005847f8 = 0x2c;
  _DAT_005847fc = 0x18;
  sub_40ECD0(0);
  cVar1 = sub_419BD0(0);
  if (cVar1 == '\0') {
    sub_419A60(0);
  }
  iVar3 = 0;
  do {
    *(undefined4 *)((int)&DAT_00584800 + iVar3) = 0;
    piVar2 = &DAT_005720e8;
    do {
      if (*(int *)((int)&DAT_00584758 + iVar3) == *piVar2) {
        *(undefined4 *)((int)&DAT_00584800 + iVar3) = 1;
        break;
      }
      piVar2 = piVar2 + 1;
    } while ((int)piVar2 < 0x572100);
    iVar3 = iVar3 + 4;
    if (0x37 < iVar3) {
      puVar4 = &DAT_00584790;
      for (iVar3 = 0xe; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar4 = 0xffffffff;
        puVar4 = puVar4 + 1;
      }
      _DAT_005847a8 = 1;
      DAT_00584790 = 0x20;
      DAT_00584794 = 0x21;
      _DAT_00584798 = 0x22;
      _DAT_0058479c = 0x23;
      _DAT_005847a0 = 4;
      _DAT_005847a4 = 5;
      _DAT_005847ac = 0;
      _DAT_005847b0 = 3;
      _DAT_005847b4 = 8;
      _DAT_005847b8 = 6;
      _DAT_005847bc = 7;
      _DAT_005847c0 = 2;
      _DAT_005847c4 = 9;
      for (piVar2 = DAT_00582260; (*piVar2 != 0 || (piVar2[1] == 0)); piVar2 = (int *)*piVar2) {
        sub_40ECD0(piVar2);
        cVar1 = sub_419BD0(piVar2);
        if (cVar1 == '\0') {
          sub_419A60(piVar2);
        }
        sub_40F290(piVar2,0,0xff,1000);
      }
      return;
    }
  } while( true );
}

