/* sub_21107800 @ 21107800   747 bytes */

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __thiscall sub_21107800(void *this,ushort *param_1,int param_2)

{
  int iVar1;
  ushort *puVar2;
  int iVar3;
  float10 fVar4;
  float10 fVar5;
  longlong lVar6;
  
  puVar2 = param_1;
  if ((ushort)(param_1[2] - *param_1) != 0) {
    iVar3 = 0;
    param_1 = (ushort *)(uint)(ushort)(param_1[2] - *param_1);
    do {
      iVar1 = param_2 + ((uint)*puVar2 + iVar3) * 4;
      switch(*(undefined2 *)(param_2 + ((uint)*puVar2 + iVar3) * 4)) {
      case 0:
        *(short *)((int)this + 4) = *(short *)((int)this + 4) + *(short *)(iVar1 + 2);
        break;
      case 1:
        *(short *)((int)this + 6) = *(short *)((int)this + 6) + *(short *)(iVar1 + 2);
        break;
      case 2:
        *(short *)((int)this + 8) = *(short *)((int)this + 8) + *(short *)(iVar1 + 2);
        break;
      case 3:
        *(short *)((int)this + 10) = *(short *)((int)this + 10) + *(short *)(iVar1 + 2);
        break;
      case 4:
        *(short *)((int)this + 4) = *(short *)((int)this + 4) + *(short *)(iVar1 + 2) * -0x8000;
        break;
      case 0xc:
        *(short *)((int)this + 6) = *(short *)((int)this + 6) + *(short *)(iVar1 + 2) * -0x8000;
        break;
      case 0xf:
        *(short *)((int)this + 0x1e) = *(short *)((int)this + 0x1e) + *(short *)(iVar1 + 2);
        break;
      case 0x10:
        *(short *)((int)this + 0x1c) = *(short *)((int)this + 0x1c) + *(short *)(iVar1 + 2);
        break;
      case 0x11:
        *(short *)((int)this + 0x18) =
             *(short *)((int)this + 0x18) +
             (short)((int)((int)*(short *)(iVar1 + 2) + ((int)*(short *)(iVar1 + 2) >> 0x1f & 3U))
                    >> 2);
        break;
      case 0x22:
        fVar5 = (float10)1.4426950408889634 *
                (float10)(int)*(short *)(iVar1 + 2) * (float10)_DAT_21112360;
        fVar4 = ROUND(fVar5);
        fVar5 = (float10)f2xm1(fVar5 - fVar4);
        fscale((float10)1 + fVar5,fVar4);
        log2((float10)_DAT_21112358);
        lVar6 = __ftol();
        *(short *)((int)this + 0x20) = (short)lVar6;
        break;
      case 0x23:
        fVar5 = (float10)1.4426950408889634 *
                (float10)(int)*(short *)(iVar1 + 2) * (float10)_DAT_21112360;
        fVar4 = ROUND(fVar5);
        fVar5 = (float10)f2xm1(fVar5 - fVar4);
        fscale((float10)1 + fVar5,fVar4);
        log2((float10)_DAT_21112358);
        lVar6 = __ftol();
        *(short *)((int)this + 0x22) = (short)lVar6;
        break;
      case 0x24:
        fVar5 = (float10)1.4426950408889634 *
                (float10)(int)*(short *)(iVar1 + 2) * (float10)_DAT_21112360;
        fVar4 = ROUND(fVar5);
        fVar5 = (float10)f2xm1(fVar5 - fVar4);
        fscale((float10)1 + fVar5,fVar4);
        log2((float10)_DAT_21112358);
        lVar6 = __ftol();
        *(short *)((int)this + 0x24) = (short)lVar6;
        break;
      case 0x25:
        fVar5 = (float10)1.4426950408889634 *
                (float10)(int)*(short *)(iVar1 + 2) * (float10)_DAT_21112360;
        fVar4 = ROUND(fVar5);
        fVar5 = (float10)f2xm1(fVar5 - fVar4);
        fscale((float10)1 + fVar5,fVar4);
        log2((float10)_DAT_21112358);
        lVar6 = __ftol();
        *(short *)((int)this + 0x26) = (short)lVar6;
        break;
      case 0x26:
        fVar5 = (float10)1.4426950408889634 *
                (float10)(int)*(short *)(iVar1 + 2) * (float10)_DAT_21112360;
        fVar4 = ROUND(fVar5);
        fVar5 = (float10)f2xm1(fVar5 - fVar4);
        fscale((float10)1 + fVar5,fVar4);
        log2((float10)_DAT_21112358);
        lVar6 = __ftol();
        *(short *)((int)this + 0x28) = (short)lVar6;
        break;
      case 0x29:
        *(undefined2 *)this = *(undefined2 *)(iVar1 + 2);
        break;
      case 0x2b:
        *(ushort *)((int)this + 0xe) = (ushort)*(byte *)(iVar1 + 2);
        *(ushort *)((int)this + 0x10) = (ushort)*(byte *)(iVar1 + 3);
        break;
      case 0x2c:
        *(ushort *)((int)this + 0xe) = (ushort)*(byte *)(iVar1 + 2);
        *(ushort *)((int)this + 0x10) = (ushort)*(byte *)(iVar1 + 3);
        break;
      case 0x2d:
        *(short *)((int)this + 8) = *(short *)((int)this + 8) + *(short *)(iVar1 + 2) * -0x8000;
        break;
      case 0x30:
        *(short *)((int)this + 0x1a) = *(short *)(iVar1 + 2) * -10;
        break;
      case 0x32:
        *(short *)((int)this + 10) = *(short *)((int)this + 10) + *(short *)(iVar1 + 2) * -0x8000;
        break;
      case 0x33:
        *(undefined2 *)((int)this + 0x2a) = *(undefined2 *)(iVar1 + 2);
        break;
      case 0x34:
        *(undefined2 *)((int)this + 0x2c) = *(undefined2 *)(iVar1 + 2);
        break;
      case 0x35:
        *(undefined2 *)((int)this + 2) = *(undefined2 *)(iVar1 + 2);
        break;
      case 0x36:
        *(undefined2 *)((int)this + 0xc) = *(undefined2 *)(iVar1 + 2);
        break;
      case 0x3a:
        *(undefined2 *)((int)this + 0x12) = *(undefined2 *)(iVar1 + 2);
      }
      iVar3 = iVar3 + 1;
      param_1 = (ushort *)((int)param_1 + -1);
    } while (param_1 != (ushort *)0x0);
  }
  return;
}

