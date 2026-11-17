/* sub_2110A170 @ 2110a170   134 bytes */

void __thiscall sub_2110A170(void *this,undefined4 param_1,uint *param_2)

{
  uint *puVar1;
  int iVar2;
  
  puVar1 = param_2;
  *(uint *)((int)this + 0x28) = param_2[1];
  *(uint *)((int)this + 0x2c) = param_2[2];
  *(uint *)((int)this + 0x30) = param_2[3];
  *(uint *)((int)this + 0x34) = param_2[4];
  if (*param_2 != *(uint *)((int)this + 0xb8)) {
    sub_2110A200(this,1,*param_2,*(int *)((int)this + 0x118));
  }
  if (*(int *)((int)this + 0xb4) != 0) {
    iVar2 = *(int *)(*(int *)((int)this + 0x5c) + 4);
    if (iVar2 != 0) {
      do {
        if (*(uint *)(iVar2 + 0x34) == *puVar1) goto LAB_2110a1cf;
        iVar2 = *(int *)(iVar2 + 0x3c);
      } while (iVar2 != 0);
    }
    iVar2 = 0;
LAB_2110a1cf:
    param_2 = (uint *)sub_2110A150(*(undefined4 *)((int)this + 0x28));
    (**(code **)(iVar2 + 0x2c))(*(undefined4 *)((int)this + 0xc0),0,&param_2);
  }
  return;
}

