/* Recover the median-cut palette builder used by texture upload. */
undefined4 sub_436E30(int start, int color_count, unsigned short *palette)
{
  typedef struct ColorBox {
    int min_red;
    int max_red;
    int min_green;
    int max_green;
    int min_blue;
    int max_blue;
    int volume;
  } ColorBox;

  ColorBox boxes[256] = {{0, 32, 0, 32, 0, 32, 0}};
  float split_error[256] = {0};
  int target_count = color_count;
  int box_count = 1;
  int selected_box = 0;
  int i;
  float largest_error;
  ColorBox *next_box = &boxes[1];
  float *next_error = &split_error[1];

  if (color_count > 256)
    return 0;

  if (DAT_006d76c8 != 0) {
    palette[start++] = 0;
    --target_count;
  }

  DAT_005ff730 = target_count;
  sub_4370C0();

  while (box_count < target_count) {
    if (sub_437460((int *)&boxes[selected_box], (int *)next_box) == 0) {
      --box_count;
      --next_box;
      --next_error;
      split_error[selected_box] = 0.0f;
    } else {
      split_error[selected_box] = (float)sub_437330((int *)&boxes[selected_box]);
      *next_error = (float)sub_437330((int *)next_box);
    }

    largest_error = split_error[0];
    selected_box = 0;
    for (i = 1; i <= box_count; ++i) {
      if (largest_error < split_error[i]) {
        largest_error = split_error[i];
        selected_box = i;
      }
    }

    if (largest_error <= 0.0f) {
      DAT_005ff730 = box_count + 1;
      break;
    }

    ++next_box;
    ++next_error;
    ++box_count;
  }

  for (i = 0; i < DAT_005ff730; ++i) {
    int count;
    int red_sum;
    int green_sum;
    int blue_sum;
    unsigned short color;

    sub_437A60((int *)&boxes[i], (unsigned char)i);
    count = sub_437290((int *)&boxes[i], (int *)&DAT_006b4544);
    if (count == 0)
      continue;

    red_sum = sub_437290((int *)&boxes[i], (int *)&DAT_0064b0b8);
    green_sum = sub_437290((int *)&boxes[i], (int *)&DAT_0066e23c);
    blue_sum = sub_437290((int *)&boxes[i], (int *)&DAT_006913c0);
    color = (unsigned short)((((red_sum / count) << 5) |
                              (green_sum / count)) << 5) |
                            (unsigned short)(blue_sum / count);
    palette[start + i] = color;
    if (DAT_006d76c8 != 0 && color == 0)
      palette[start + i] = 1;
  }

  return 1;
}
