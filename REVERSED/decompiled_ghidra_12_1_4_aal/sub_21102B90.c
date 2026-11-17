/* _AAL_CPUPercent@0 @ 21102b90   196 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

float10 _AAL_CPUPercent_0(void)

{
  float fVar1;
  float10 fVar2;
  ulonglong uVar3;
  
                    /* 0x2b90  6  _AAL_CPUPercent@0 */
  uVar3 = sub_211010C0(1);
  fVar1 = (float)(uVar3 & 0xffffffff) - _DAT_211155d0;
  if (fVar1 < _DAT_21112334) {
    return (float10)_DAT_211155d4;
  }
  _DAT_211155d0 = (float)(uVar3 & 0xffffffff);
  _DAT_211155c0 = _DAT_211155c0 + DAT_211155c4 / 1000;
  DAT_211155c4 = DAT_211155c4 % 1000;
  if (fVar1 == _DAT_2111232c) {
    fVar2 = (float10)_DAT_2111232c;
  }
  else {
    fVar2 = ((float10)_DAT_211155c0 * (float10)_DAT_21112330) / (float10)fVar1;
  }
  _DAT_211155c0 = 0;
  if ((float10)_DAT_21112330 < fVar2) {
    fVar2 = (float10)_DAT_21112330;
  }
  _DAT_211155d4 = (float)fVar2;
  return fVar2;
}

