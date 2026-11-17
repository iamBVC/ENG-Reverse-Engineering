/* sub_56D5AC @ 0056d5ac   28 bytes */

exception * __thiscall sub_56D5AC(exception *param_1,byte param_2)

{
  exception::~exception(param_1);
  if ((param_2 & 1) != 0) {
    sub_562941(param_1);
  }
  return param_1;
}

