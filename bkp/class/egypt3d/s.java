public final class s
{
  public static final void a(int[] paramArrayOfInt, int paramInt1, int paramInt2, int paramInt3)
  {
    int i = e.bt[paramInt1][0];
    int j = e.bt[paramInt1][1];
    int k = i;
    paramInt3 = 260 - (paramInt3 * j >> 8) - 2;
    e.bv = (short)(paramInt2 = paramInt2 * (240 - i) >> 8);
    e.bx = (short)paramInt3;
    if ((paramInt2 >= 240) || (paramInt2 + i < 0) || (paramInt3 >= 260) || (paramInt3 + j < 0)) {
      return;
    }
    int[] arrayOfInt1 = e.a[paramInt1];
    byte[] arrayOfByte = e.b[paramInt1];
    int[] arrayOfInt2 = e.aq;
    int m = e.j[0].n;
    int n = arrayOfInt1.length;
    for (int i1 = 0; i1 < n; i1++)
    {
      int i2 = arrayOfInt1[i1];
      arrayOfInt2[i1] = ((i2 & 0xFF000000) + (((i2 & 0xFF0000) >> 16) * m >> 8 << 16) + (((i2 & 0xFF00) >> 8) * m >> 8 << 8) + ((i2 & 0xFF) * m >> 8));
    }
    int i3 = 0;
    int i4 = 0;
    int i5 = 0;
    int i6 = 240 - i;
    if (paramInt2 < 0)
    {
      i4 = -paramInt2;
      i6 -= paramInt2;
      paramInt2 = 0;
    }
    if (paramInt3 < 0)
    {
      i5 = -paramInt3;
      paramInt3 = 0;
    }
    if (paramInt2 + i > 240)
    {
      i = 240 - paramInt2;
      i6 = 240 - i;
    }
    if (paramInt3 + j > 260) {
      j = 260 - paramInt3;
    }
    int i7 = 0;
    int i8 = 0;
    int i9 = 0;
    i3 = paramInt3 * 240 + paramInt2;
    for (i1 = i5; i1 < j; i1++)
    {
      for (n = i4; n < i; n++)
      {
        if (i8 == 0)
        {
          if ((i9 = arrayOfByte[i7]) < 0)
          {
            i8 = -i9;
            i7++;
          }
          i9 = arrayOfInt2[arrayOfByte[i7]];
          i7++;
          if ((i9 == 0) && (i8 > 0))
          {
            if (n + i8 < k)
            {
              i3 += i8 + 1;
              n += i8;
              i8 = 0;
              continue;
            }
            i8 = i8 - (k - n) + 1;
            i3 += k - n;
            break;
          }
        }
        else
        {
          if ((i9 == 0) && (i8 > 0) && (n + i8 <= k))
          {
            i3 += i8;
            n += i8 - 1;
            i8 = 0;
            continue;
          }
          i8--;
        }
        if (i9 != 0) {
          paramArrayOfInt[i3] = i9;
        }
        i3++;
      }
      i3 += i6;
    }
  }
  
  public static int a(byte[] paramArrayOfByte, byte paramByte)
  {
    int j = 0;
    int k = 0;
    if (paramArrayOfByte[3] == 1) {
      k = 1;
    }
    if (paramByte == 2) {
      return paramArrayOfByte[4];
    }
    int i;
    if ((i = paramArrayOfByte[5]) < 0) {
      i += 256;
    }
    if (k != 0) {
      j = 5 + i * 4;
    } else {
      j = 5 + i * 3;
    }
    int m;
    int n;
    if (paramByte == 0)
    {
      if ((m = (short)paramArrayOfByte[(++j)]) < 0) {
        m = (short)(m + 256);
      }
      if ((n = (short)paramArrayOfByte[(++j)]) < 0) {
        n = (short)(n + 256);
      }
      i = m << 8 | n;
    }
    if (paramByte == 1)
    {
      j += 2;
      if ((m = (short)paramArrayOfByte[(++j)]) < 0) {
        m = (short)(m + 256);
      }
      if ((n = (short)paramArrayOfByte[(++j)]) < 0) {
        n = (short)(n + 256);
      }
      i = m << 8 | n;
    }
    return i;
  }
  
  public static final void a(byte[] paramArrayOfByte, int paramInt)
  {
    int j;
    int k = (j = (1 << paramInt) - 1) >> 1;
    for (int m = j; m >= 0; m--) {
      for (int n = k; n >= 0; n--)
      {
        int i = paramArrayOfByte[(n * (j + 1) + m)];
        paramArrayOfByte[(n * (j + 1) + m)] = paramArrayOfByte[((j - n) * (j + 1) + m)];
        paramArrayOfByte[((j - n) * (j + 1) + m)] = i;
      }
    }
  }
  
  public static final int[] a(byte[] paramArrayOfByte)
  {
    int j = 3;
    int k = 0;
    if (paramArrayOfByte[3] == 1) {
      k = 1;
    }
    j++;
    int i;
    if ((i = (j++)[5]) < 0) {
      i += 256;
    }
    int[] arrayOfInt = new int[i];
    if (k == 0)
    {
      int m = 0;
      tmpTernaryOp = paramArrayOfByte;
      while (m < i)
      {
        arrayOfInt[m] = ((paramArrayOfByte[(++j)] & 0xFF) << 16 | (paramArrayOfByte[(++j)] & 0xFF) << 8 | paramArrayOfByte[(++j)] & 0xFF);
        m++;
      }
    }
    else
    {
      for (int n = 0; n < i; n++) {
        if (paramArrayOfByte[(++j)] != 0)
        {
          arrayOfInt[n] = (0xFF000000 | (paramArrayOfByte[(++j)] & 0xFF) << 16 | (paramArrayOfByte[(++j)] & 0xFF) << 8 | paramArrayOfByte[(++j)] & 0xFF);
        }
        else
        {
          j += 3;
          arrayOfInt[n] = 0;
        }
      }
    }
    return arrayOfInt;
  }
  
  public static final byte[] a(byte[] paramArrayOfByte, boolean paramBoolean, int paramInt1, int paramInt2, int paramInt3, int paramInt4)
  {
    int j = 0;
    int k = 0;
    if (paramArrayOfByte[3] == 1) {
      k = 1;
    }
    int m = 0;
    if (paramArrayOfByte[4] == 1) {
      m = 1;
    }
    int n;
    if ((n = paramArrayOfByte[5]) < 0) {
      n += 256;
    }
    if (k != 0) {
      j = 5 + n * 4;
    } else {
      j = 5 + n * 3;
    }
    byte[] arrayOfByte = null;
    int i1;
    int i2;
    int i3;
    if (!paramBoolean)
    {
      i1 = paramArrayOfByte[(++j)] << 8 | paramArrayOfByte[(++j)];
      i2 = paramArrayOfByte[(++j)] << 8 | paramArrayOfByte[(++j)];
      if (i1 < 0) {
        i1 += 256;
      }
      if (i2 < 0) {
        i2 += 256;
      }
      j++;
      int i;
      if (m == 0)
      {
        arrayOfByte = new byte[i = i1 * i2];
        for (i3 = 0; i3 < i; i3++) {
          arrayOfByte[i3] = paramArrayOfByte[(++j)];
        }
      }
      else
      {
        j++;
        arrayOfByte = new byte[i = paramArrayOfByte.length - j];
        for (i3 = 0; i3 < i; i3++) {
          arrayOfByte[i3] = paramArrayOfByte[(j++)];
        }
      }
    }
    else
    {
      i1 = 0;
      i3 = paramArrayOfByte[(++j)] << 8 | paramArrayOfByte[(++j)];
      j++;
      j++;
      if (i3 < 0) {
        i3 += 256;
      }
      arrayOfByte = new byte[paramInt3 * paramInt4];
      j += paramInt2 * i3 + paramInt1;
      j++;
      j++;
      for (int i4 = 0; i4 < paramInt4; i4++)
      {
        i2 = i4 * i3 + j;
        for (int i5 = 0; i5 < paramInt3; i5++)
        {
          arrayOfByte[i1] = paramArrayOfByte[(i2 + i5)];
          i1++;
        }
      }
    }
    return arrayOfByte;
  }
}


/* Location:              E:\NET Lizard\3D射击\240x320(nok_v1)-3d_teni_egipta.jar!\s.class
 * Java compiler version: 4 (48.0)
 * JD-Core Version:       0.7.1
 */