/* sub_21106420 @ 21106420   54 bytes */

undefined4 __thiscall sub_21106420(void *this,uint *param_1,int param_2)

{
  undefined4 uVar1;
  
  if (param_1 == (uint *)0x0) {
    return 1;
  }
  uVar1 = sub_211066A0(this,param_1);
  if (param_2 != 0) {
    sub_211064A0(this,(byte)param_2);
  }
  return uVar1;
}

