/* sub_56AA33 @ 0056aa33   125 bytes */

void * sub_56AA33(int param_1,int param_2)

{
  void *_Dst;
  LPVOID pvVar1;
  int iVar2;
  uint _Size;
  uint uVar3;
  
  _Size = param_1 * param_2;
  uVar3 = _Size;
  if (_Size < 0xffffffe1) {
    if (_Size == 0) {
      uVar3 = 1;
    }
    uVar3 = uVar3 + 0xf & 0xfffffff0;
  }
  do {
    if (uVar3 < 0xffffffe1) {
      if ((_Size < DAT_0057ca20 || _Size - DAT_0057ca20 == 0) &&
         (_Dst = (void *)sub_565F41(_Size), _Dst != (void *)0x0)) {
        _memset(_Dst,0,_Size);
        return _Dst;
      }
      pvVar1 = HeapAlloc(DAT_006db91c,8,uVar3);
      if (pvVar1 != (LPVOID)0x0) {
        return pvVar1;
      }
    }
    if (DAT_006da40c == 0) {
      return (void *)0x0;
    }
    iVar2 = sub_5672AD(uVar3);
  } while (iVar2 != 0);
  return (void *)0x0;
}

