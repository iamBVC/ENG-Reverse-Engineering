/* sub_569371 @ 00569371   53 bytes */

uint sub_569371(uint param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = sub_5693BC();
  uVar1 = uVar1 & ~param_2 | param_1 & param_2;
  sub_56944E(uVar1);
  return uVar1;
}

