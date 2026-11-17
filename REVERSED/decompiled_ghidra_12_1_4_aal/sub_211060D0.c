/* sub_211060D0 @ 211060d0   99 bytes */

void __thiscall sub_211060D0(void *this,int param_1,int param_2)

{
  undefined4 uVar1;
  
  if (*(int *)((int)this + 0x90) != 0) {
    param_1 = param_1 - param_2;
    if (param_1 != 0) {
      (**(code **)((int)this + 0xa4))(*(undefined4 *)((int)this + 0xac),3,&param_1);
    }
    uVar1 = (**(code **)((int)this + 0xa8))
                      (*(undefined4 *)((int)this + 0xac),*(undefined4 *)((int)this + 0xb0));
    *(undefined4 *)((int)this + *(int *)((int)this + 0x58) * 4 + 0x40) = uVar1;
    return;
  }
  *(int *)((int)this + *(int *)((int)this + 0x58) * 4 + 0x40) =
       param_1 - *(int *)((int)this + *(int *)((int)this + 0x58) * 4 + 0x38);
  return;
}

