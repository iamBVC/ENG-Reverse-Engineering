/* sub_41CEE0 @ 0041cee0   983 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void sub_41CEE0(int param_1)

{
  float fVar1;
  bool bVar2;
  undefined4 uVar3;
  BOOL BVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  float *pfVar8;
  undefined4 *puVar9;
  undefined8 uVar10;
  LARGE_INTEGER local_18;
  int local_10;
  int local_c;
  int local_8;
  int local_4;
  
  bVar2 = false;
  if (DAT_00586408 == 0 && DAT_0058640c == 0) {
    BVar4 = QueryPerformanceFrequency(&local_18);
    if (BVar4 == 0) {
      DAT_00586410 = 0;
      DAT_00586414 = 0;
      DAT_005863b8 = timeGetTime();
      DAT_005863bc = 0;
    }
    else {
      DAT_00586410 = local_18.s.LowPart;
      DAT_00586414 = local_18.s.HighPart;
      QueryPerformanceCounter(&local_18);
      DAT_005863b8 = local_18.s.LowPart;
      DAT_005863bc = local_18.s.HighPart;
    }
    DAT_005724d4 = 1;
    _DAT_005724e0 = 1.0;
    _DAT_005724d8 = 1.0;
    DAT_00586408 = DAT_005863b8;
    DAT_0058640c = DAT_005863bc;
    if (0 < param_1) {
      puVar9 = &DAT_00585744;
      for (iVar7 = param_1; iVar7 != 0; iVar7 = iVar7 + -1) {
        *puVar9 = 0;
        puVar9 = puVar9 + 1;
      }
    }
  }
  do {
    iVar7 = param_1 >> 0x1f;
    if (DAT_00586410 == 0 && DAT_00586414 == 0) {
      DAT_00585a68 = timeGetTime();
      DAT_00585a6c = 0;
      uVar10 = __allmul(DAT_00585a68 - DAT_00586408,
                        -(uint)(DAT_00585a68 < DAT_00586408) - DAT_0058640c,param_1,iVar7);
      iVar6 = __alldiv(uVar10,1000,0);
      uVar10 = __allmul(DAT_005863b8 - DAT_00586408,
                        (DAT_005863bc - DAT_0058640c) - (uint)((uint)DAT_005863b8 < DAT_00586408),
                        param_1,iVar7);
      iVar7 = __alldiv(uVar10,1000,0);
      iVar6 = iVar6 - iVar7;
      DAT_005724d4 = iVar6;
      if (!bVar2) {
        local_8 = DAT_00585a68 - DAT_005863b8;
        bVar2 = true;
        local_4 = (DAT_00585a6c - DAT_005863bc) - (uint)(DAT_00585a68 < (uint)DAT_005863b8);
        iVar7 = DAT_005863c8 + 1;
        DAT_005863c8 = iVar7;
        *(float *)(&DAT_00585740 + iVar7 * 4) =
             _DAT_0056e008 / ((float)param_1 * _DAT_0056e350 * (float)local_8);
        if (param_1 <= iVar7) {
          DAT_005863c8 = 0;
        }
      }
      DAT_005863b8 = DAT_00585a68;
      DAT_005863bc = DAT_00585a6c;
    }
    else {
      QueryPerformanceCounter(&local_18);
      uVar3 = local_18.s.LowPart;
      DAT_00585a6c = local_18.s.HighPart;
      DAT_00585a68 = local_18.s.LowPart;
      uVar10 = __allmul(DAT_005863b8 - DAT_00586408,
                        (DAT_005863bc - DAT_0058640c) - (uint)((uint)DAT_005863b8 < DAT_00586408),
                        param_1,iVar7);
      iVar5 = __alldiv(uVar10,DAT_00586410,DAT_00586414);
      uVar10 = __allmul(uVar3 - DAT_00586408,
                        (local_18.s.HighPart - DAT_0058640c) - (uint)((uint)uVar3 < DAT_00586408),
                        param_1,iVar7);
      iVar6 = __alldiv(uVar10,DAT_00586410,DAT_00586414);
      iVar6 = iVar6 - iVar5;
      DAT_005724d4 = iVar6;
      if (!bVar2) {
        bVar2 = true;
        local_10 = uVar3 - DAT_005863b8;
        local_c = (local_18.s.HighPart - DAT_005863bc) - (uint)((uint)uVar3 < (uint)DAT_005863b8);
        iVar7 = DAT_005863c8 + 1;
        DAT_005863c8 = iVar7;
        *(float *)(&DAT_00585740 + iVar7 * 4) =
             _DAT_0056e008 /
             (((float)param_1 / (float)CONCAT44(DAT_00586414,DAT_00586410)) * (float)local_10);
        if (param_1 <= iVar7) {
          DAT_005863c8 = 0;
        }
      }
      DAT_005863b8 = uVar3;
      DAT_005863bc = local_18.s.HighPart;
    }
  } while (iVar6 == 0);
  if (param_1 < iVar6) {
    DAT_005724d4 = param_1;
    iVar6 = param_1;
  }
  iVar7 = 0;
  DAT_00586400 = DAT_00586400 + iVar6;
  if (0 < param_1) {
    pfVar8 = (float *)&DAT_00585744;
    fVar1 = _DAT_0056e00c;
    do {
      if (_DAT_0056e00c < *pfVar8) {
        fVar1 = fVar1 + *pfVar8;
        iVar7 = iVar7 + 1;
      }
      pfVar8 = pfVar8 + 1;
      param_1 = param_1 + -1;
    } while (param_1 != 0);
    if (iVar7 != 0) {
      fVar1 = fVar1 / (float)iVar7;
      if (_DAT_0056e008 < fVar1) {
        fVar1 = fVar1 * _DAT_0056e218 + _DAT_0056e34c;
      }
      _DAT_005724e0 = _DAT_005724d8 * fVar1;
      if (_DAT_005724e0 <= _DAT_0056e180) {
        if (_DAT_005724e0 < _DAT_0056e008) {
          _DAT_005724e0 = 1.0;
        }
      }
      else {
        _DAT_005724e0 = 2.0;
      }
    }
  }
  _DAT_005724d8 = _DAT_005724d8 * _DAT_0056e344 + _DAT_005724e0 * _DAT_0056e348;
  DAT_00584650 = DAT_00584650 + iVar6 * 2;
  return;
}

