/* sub_42BF40 @ 0042bf40
 * Recovered x87 view-bound expressions from the original instruction listing.
 */
byte sub_42BF40(int param_1,int param_2)
{
  int *piVar1;
  byte bVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  byte local_29;
  undefined4 local_28;
  /* The original stack slots are contiguous from local_18 through local_4:
     [0, yaw, 0, x, y, z]. The two renderer paths receive pointers into this
     same block, so model that layout explicitly instead of relying on local
     variable placement by the C compiler. */
  float transform_block[6];
  double viewCenter;
  static uint trace_count;
  uint trace_frame = trace_count++;
  uint submitted_models = 0;

  viewCenter = (double)DAT_0057f90c + (double)DAT_0056e180;
  local_29 = 1;
  uVar3 = (uint)(int)(-((double)DAT_006d8408 + viewCenter));
  uVar3 = ((int)uVar3 < 0) - 1 & uVar3;
  uVar4 = (uint)(int)(viewCenter - (double)DAT_006d8408);
  uVar5 = *(int *)(param_1 + 0x18) - 1;
  if (uVar5 < uVar4) {
    uVar4 = uVar5;
  }
  uVar5 = (uint)(int)((double)DAT_006d8400 - viewCenter);
  local_28 = (undefined4)(uint)(int)(viewCenter + (double)DAT_006d8400);
  uVar6 = *(int *)(param_1 + 0x14) - 1;
  if (uVar6 < local_28) {
    local_28 = uVar6;
  }
  if (trace_frame < 3) {
    fprintf(stderr, "[clip] map=%p actors=%p dims=%u/%u cells=%p records=%p visibility=%p models=%p details=%p camera=%.3f extents=%.3f/%.3f\n",
            (void *)(UINT_PTR)param_1, (void *)(UINT_PTR)param_2,
            *(uint *)(param_1 + 0x14), *(uint *)(param_1 + 0x18),
            *(void **)(param_1 + 0x40), *(void **)(param_1 + 0x3c),
            *(void **)(param_1 + 0x48), *(void **)(param_1 + 0x4c),
            *(void **)(param_1 + 0x58), viewCenter,
            (double)DAT_006d8400, (double)DAT_006d8408);
    fprintf(stderr, "[clip-bounds] x=%u..%u y=%u..%u\n", uVar3, uVar4, uVar5, local_28);
  }
  for (; uVar6 = ((int)uVar5 < 0) - 1 & uVar5, (int)uVar3 <= (int)uVar4; uVar3 = uVar3 + 1) {
    for (; (int)uVar6 <= (int)local_28; uVar6 = uVar6 + 1) {
      for (piVar1 = *(int **)(*(int *)(param_1 + 0x40) +
                             (*(int *)(param_1 + 0x14) * uVar3 + uVar6) * 4); piVar1 != (int *)0x0;
          piVar1 = (int *)piVar1[1]) {
        if ((_DAT_0058642c &
            1 << ((byte)*(undefined4 *)
                         (*(int *)(param_1 + 0x48) + (*(int *)(param_1 + 0x14) * uVar3 + uVar6) * 4)
                 & 0x1f)) != 0) {
          iVar7 = *piVar1 * 0x20 + *(int *)(param_1 + 0x3c);
          transform_block[3] = (float)*(int *)(iVar7 + 0x10) * (float)_DAT_0056e020;
          transform_block[4] = (float)*(int *)(iVar7 + 0x14) * (float)_DAT_0056e020;
          transform_block[0] = 0.0f;
          transform_block[5] = -((float)*(int *)(iVar7 + 0x18) * (float)_DAT_0056e020);
          transform_block[2] = 0.0f;
          transform_block[1] = (float)*(int *)(iVar7 + 4) * (float)_DAT_0056e018;
          if (DAT_005865cc == 1) {
            bVar2 = sub_41FB30(param_2 + *(int *)(*(int *)(param_1 + 0x4c) + *piVar1 * 4) * 0x84,
                               (undefined4 *)transform_block,1.0f,1.0f,1.0f,1.0f,0,0,0,
                               0xffffffff,0xffffffff,0xffffffff,1,0);
            ++submitted_models;
          }
          else {
            iVar7 = *(int *)(param_1 + 0x58);
            iVar8 = *piVar1 * 4;
            uVar9 = *(uint *)(iVar7 + iVar8);
            if ((*(byte *)(uVar9 + 3) < 2) || (DAT_005865d4 != 1)) {
              uVar9 = -(uint)(iVar7 != 0) & uVar9;
            }
            else if (iVar7 == 0) {
              uVar9 = 0;
            }
            else {
              uVar9 = uVar9 + (uint)*(ushort *)
                                     (param_2 + 0x6c +
                                     *(int *)(*(int *)(param_1 + 0x4c) + iVar8) * 0x84) * 4;
            }
            if (trace_frame == 0 && submitted_models == 0) {
              float *source_matrix = (float *)&DAT_0057db20;
              fprintf(stderr,
                      "[camera-projection-source] %+.3f %+.3f %+.3f %+.3f | %+.3f %+.3f %+.3f %+.3f | %+.3f %+.3f %+.3f %+.3f | %+.3f %+.3f %+.3f %+.3f\n",
                      (double)source_matrix[0], (double)source_matrix[1],
                      (double)source_matrix[2], (double)source_matrix[3],
                      (double)source_matrix[4], (double)source_matrix[5],
                      (double)source_matrix[6], (double)source_matrix[7],
                      (double)source_matrix[8], (double)source_matrix[9],
                      (double)source_matrix[10], (double)source_matrix[11],
                      (double)source_matrix[12], (double)source_matrix[13],
                      (double)source_matrix[14], (double)source_matrix[15]);
              {
                float *projection_matrix = (float *)&DAT_0057db60;
                fprintf(stderr,
                        "[camera-projection-plane] z=%+.6f w=%+.6f tz=%+.6f tw=%+.6f\n",
                        (double)projection_matrix[10], (double)projection_matrix[11],
                        (double)projection_matrix[14], (double)projection_matrix[15]);
              }
            }
            bVar2 = sub_556510(param_2 + *(int *)(*(int *)(param_1 + 0x4c) + iVar8) * 0x84,
                               transform_block + 3,transform_block + 1,uVar9);
            ++submitted_models;
          }
          local_29 = local_29 & bVar2;
        }
      }
    }
  }
  if (trace_frame < 3) {
    fprintf(stderr, "[clip-result] call=%u submitted_models=%u result=%u\n",
            trace_frame + 1, submitted_models, local_29);
  }
  return local_29;
}
