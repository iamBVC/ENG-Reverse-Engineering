/* sub_40D450 @ 0040d450   42 bytes */

undefined1 sub_40D450(char param_1)

{
  if (((((param_1 != ']') && (param_1 != '[')) && (param_1 != '}')) &&
      ((param_1 != '{' && (param_1 != '<')))) &&
     ((param_1 != '>' && ((param_1 != '^' && (param_1 != '_')))))) {
    return 0;
  }
  return 1;
}

