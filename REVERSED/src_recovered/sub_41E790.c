/* Copy three float components; the original returns its ECX object in EAX. */
float *sub_41E790(float *param_1, float param_2, float param_3, float param_4)
{
    param_1[0] = param_2;
    param_1[1] = param_3;
    param_1[2] = param_4;
    return param_1;
}
