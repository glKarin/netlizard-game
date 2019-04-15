import java.io.DataInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintStream;
import java.util.Random;
import javax.microedition.lcdui.Graphics;
import javax.microedition.lcdui.Image;
import javax.microedition.rms.RecordStore;

public final class b
{
  static boolean a = false;
  private static Random c = new Random();
  public static b b;
  
  private static float a(float paramFloat)
  {
    float f = paramFloat * 0.5F;
    int i;
    return (paramFloat = Float.intBitsToFloat(i = 1597462997 - (Float.floatToIntBits(paramFloat) >> 1))) * (1.5F - f * paramFloat * paramFloat);
  }
  
  private static String f(String paramString)
  {
    String str;
    return str = "/" + paramString + ".png";
  }
  
  public static final void a()
  {
    b = null;
  }
  
  private int g(String paramString)
  {
    int i = 0;
    int j = -1;
    try
    {
      InputStream localInputStream;
      if ((localInputStream = getClass().getResourceAsStream(paramString)) == null) {
        return -1;
      }
      while (i != -1)
      {
        i = localInputStream.read();
        j++;
      }
      localInputStream.close();
    }
    catch (Exception localException)
    {
      j = -1;
    }
    return j;
  }
  
  public static final float a(byte[] paramArrayOfByte, int paramInt)
  {
    int i = paramArrayOfByte[paramInt] & 0xFF;
    int j = paramArrayOfByte[(paramInt + 1)] & 0xFF;
    int k = paramArrayOfByte[(paramInt + 2)] & 0xFF;
    int m = paramArrayOfByte[(paramInt + 3)] & 0xFF;
    float f;
    return f = Float.intBitsToFloat(i + (j << 8) + (k << 16) + (m << 24));
  }
  
  public static final int a(byte paramByte1, byte paramByte2)
  {
    int i = paramByte1 & 0xFF;
    int j;
    return (((j = paramByte2 & 0xFF) & 0xFF) << 8) + (i & 0xFF);
  }
  
  public static final int b(byte[] paramArrayOfByte, int paramInt)
  {
    return ((paramArrayOfByte[(paramInt + 1)] & 0xFF) << 8) + (paramArrayOfByte[paramInt] & 0xFF);
  }
  
  public static final int c(byte[] paramArrayOfByte, int paramInt)
  {
    int i = paramArrayOfByte[paramInt] & 0xFF;
    int j = paramArrayOfByte[(paramInt + 1)] & 0xFF;
    int k = paramArrayOfByte[(paramInt + 2)] & 0xFF;
    int m = paramArrayOfByte[(paramInt + 3)] & 0xFF;
    return i + (j << 8) + (k << 16) + (m << 24);
  }
  
  public static final void b()
  {
    b = new b();
  }
  
  public final boolean a(String paramString)
  {
    try
    {
      InputStream localInputStream;
      if ((localInputStream = getClass().getResourceAsStream(paramString)) == null) {
        return false;
      }
      localInputStream.close();
    }
    catch (Exception localException)
    {
      return false;
    }
    return true;
  }
  
  public final byte[] b(String paramString)
  {
    return a(paramString, -1);
  }
  
  public static final byte[] c(String paramString)
  {
    byte[] arrayOfByte = null;
    try
    {
      RecordStore localRecordStore;
      if ((localRecordStore = RecordStore.openRecordStore(paramString, true)).getNumRecords() > 0)
      {
        arrayOfByte = localRecordStore.getRecord(1);
      }
      else
      {
        System.out.println("ERROR: can't get data from rms");
        localRecordStore.closeRecordStore();
        return null;
      }
      localRecordStore.closeRecordStore();
    }
    catch (Exception localException)
    {
      System.out.println(localException.getMessage());
    }
    return arrayOfByte;
  }
  
  public static final boolean a(Image[] paramArrayOfImage, int[][] paramArrayOfInt, int paramInt, String paramString)
  {
    String str = f(paramString);
    try
    {
      Image localImage = null;
      try
      {
        localImage = d.a(str);
      }
      catch (Exception localException1)
      {
        localImage = Image.createImage(str.substring(0, str.length() - 3) + "jpg");
      }
      if ((a) && (h.bJ))
      {
        paramArrayOfImage[paramInt] = Image.createImage(localImage.getWidth(), localImage.getHeight());
        Graphics localGraphics;
        (localGraphics = paramArrayOfImage[paramInt].getGraphics()).setColor(0);
        localGraphics.fillRect(0, 0, localImage.getWidth(), localImage.getHeight());
        localGraphics.drawImage(localImage, 0, 0, 20);
      }
      else
      {
        paramArrayOfImage[paramInt] = localImage;
      }
      if (paramArrayOfInt[paramInt] == null) {
        paramArrayOfInt[paramInt] = new int[6];
      }
      try
      {
        paramArrayOfInt[paramInt][0] = paramArrayOfImage[paramInt].getWidth();
        paramArrayOfInt[paramInt][1] = paramArrayOfImage[paramInt].getHeight();
      }
      catch (Exception localException2)
      {
        paramArrayOfInt[paramInt][0] = 0;
        paramArrayOfInt[paramInt][1] = 0;
      }
      paramArrayOfInt[paramInt][2] = 0;
      paramArrayOfInt[paramInt][3] = 0;
      paramArrayOfInt[paramInt][4] = 0;
      paramArrayOfInt[paramInt][5] = 0;
    }
    catch (IOException localIOException)
    {
      paramArrayOfImage[paramInt] = null;
      a = false;
      return false;
    }
    a = false;
    return true;
  }
  
  public static String d(String paramString)
  {
    return d.b.b(paramString);
  }
  
  public static String[][] e(String paramString)
  {
    String str;
    char[] arrayOfChar;
    int i;
    String[][] arrayOfString1;
    (arrayOfString1 = new String[i = (arrayOfChar = (str = d.b.b(paramString)).toCharArray()).length][])[0] = new String[i];
    int[] arrayOfInt = new int[i];
    int n = 0;
    int i1 = 0;
    int m = 0;
    for (int j = 0; j < i; j++)
    {
      if ((arrayOfChar[j] == '=') || (arrayOfChar[j] == '\r'))
      {
        arrayOfString1[n][i1] = new String();
        for (int k = m; k < j; k++)
        {
          int tmp103_101 = i1;
          String[] tmp103_100 = arrayOfString1[n];
          tmp103_100[tmp103_101] = (tmp103_100[tmp103_101] + arrayOfChar[k]);
        }
        m = j + 1;
        i1++;
      }
      if (arrayOfChar[j] == '\n')
      {
        arrayOfInt[n] = i1;
        n++;
        i1 = 0;
        arrayOfString1[n] = new String[i];
        m = j + 1;
      }
    }
    arrayOfInt[n] = i1;
    n++;
    String[][] arrayOfString2 = new String[n][];
    for (j = 0; j < n; j++)
    {
      arrayOfString2[j] = new String[arrayOfInt[j]];
      System.arraycopy(arrayOfString1[j], 0, arrayOfString2[j], 0, arrayOfInt[j]);
    }
    return arrayOfString2;
  }
  
  private byte[] a(String paramString, int paramInt)
  {
    paramString = f(paramString);
    if (paramInt < 0) {
      paramInt = g(paramString);
    }
    if (paramInt <= 0) {
      return null;
    }
    try
    {
      Class.forName("com.nokia.mid.ui.FullCanvas");
      return b(paramString, paramInt);
    }
    catch (Exception localException1)
    {
      byte[] arrayOfByte = new byte[paramInt];
      try
      {
        InputStream localInputStream;
        (localInputStream = getClass().getResourceAsStream(paramString)).read(arrayOfByte);
        localInputStream.close();
      }
      catch (Exception localException2) {}
      return arrayOfByte;
    }
  }
  
  private final byte[] b(String paramString, int paramInt)
  {
    byte[] arrayOfByte = new byte[paramInt];
    try
    {
      InputStream localInputStream;
      if ((localInputStream = getClass().getResourceAsStream(paramString)) == null) {
        return arrayOfByte;
      }
      DataInputStream localDataInputStream = new DataInputStream(localInputStream);
      int i = 0;
      int j = 0;
      for (;;)
      {
        i = localDataInputStream.read(arrayOfByte, j, arrayOfByte.length - j);
        j += i;
        if ((i == -1) || (j >= arrayOfByte.length)) {
          break;
        }
      }
      localDataInputStream.close();
    }
    catch (Exception localException) {}
    return arrayOfByte;
  }
  
  static final int a(int paramInt)
  {
    return Math.abs(c.nextInt() % paramInt);
  }
  
  public static final void a(int[][] paramArrayOfInt, int paramInt)
  {
    if (paramArrayOfInt[paramInt][4] != 0) {
      paramArrayOfInt[paramInt][0] /= paramArrayOfInt[paramInt][4];
    }
    if (paramArrayOfInt[paramInt][5] != 0) {
      paramArrayOfInt[paramInt][1] /= paramArrayOfInt[paramInt][5];
    }
  }
  
  public static final void a(int[][] paramArrayOfInt, int paramInt1, int paramInt2)
  {
    for (int i = paramInt1; i < paramInt2; i++) {
      a(paramArrayOfInt, i);
    }
  }
  
  public static final void a(int paramInt1, byte[] paramArrayOfByte, int paramInt2)
  {
    int i = paramInt1 >> 24 & 0xFF;
    int j = paramInt1 >> 16 & 0xFF;
    int k = paramInt1 >> 8 & 0xFF;
    int m = paramInt1 & 0xFF;
    paramArrayOfByte[paramInt2] = ((byte)m);
    paramArrayOfByte[(paramInt2 + 1)] = ((byte)k);
    paramArrayOfByte[(paramInt2 + 2)] = ((byte)j);
    paramArrayOfByte[(paramInt2 + 3)] = ((byte)i);
  }
  
  public static final void a(String paramString, byte[] paramArrayOfByte)
  {
    if (paramArrayOfByte == null) {
      return;
    }
    try
    {
      RecordStore localRecordStore;
      if ((localRecordStore = RecordStore.openRecordStore(paramString, true)).getNumRecords() > 0)
      {
        localRecordStore.closeRecordStore();
        if (RecordStore.listRecordStores() != null) {
          RecordStore.deleteRecordStore(paramString);
        }
        localRecordStore = RecordStore.openRecordStore(paramString, true);
      }
      localRecordStore.addRecord(paramArrayOfByte, 0, paramArrayOfByte.length);
      localRecordStore.closeRecordStore();
      return;
    }
    catch (Exception localException) {}
  }
  
  public static final void a(float[] paramArrayOfFloat, float paramFloat1, float paramFloat2, float paramFloat3, float paramFloat4, float paramFloat5, float paramFloat6, float paramFloat7, float paramFloat8, float paramFloat9)
  {
    float f1 = paramFloat4 - paramFloat1;
    float f2 = paramFloat5 - paramFloat2;
    float f3 = paramFloat6 - paramFloat3;
    float f4 = paramFloat7;
    float f5 = paramFloat8;
    float f6 = paramFloat9;
    float f7 = a(f1 * f1 + f3 * f3 + f2 * f2);
    f1 *= f7;
    f2 *= f7;
    f3 *= f7;
    float f8 = f2 * f6 - f3 * f5;
    float f9 = f3 * f4 - f1 * f6;
    float f10 = f1 * f5 - f2 * f4;
    f7 = a(f8 * f8 + f9 * f9 + f10 * f10);
    f8 *= f7;
    f9 *= f7;
    f10 *= f7;
    f4 = f9 * f3 - f10 * f2;
    f5 = f10 * f1 - f8 * f3;
    f6 = f8 * f2 - f9 * f1;
    paramArrayOfFloat[0] = f8;
    paramArrayOfFloat[1] = f4;
    paramArrayOfFloat[2] = (-f1);
    paramArrayOfFloat[3] = paramFloat1;
    paramArrayOfFloat[4] = f9;
    paramArrayOfFloat[5] = f5;
    paramArrayOfFloat[6] = (-f2);
    paramArrayOfFloat[7] = paramFloat2;
    paramArrayOfFloat[8] = f10;
    paramArrayOfFloat[9] = f6;
    paramArrayOfFloat[10] = (-f3);
    paramArrayOfFloat[11] = paramFloat3;
    paramArrayOfFloat[12] = 0.0F;
    paramArrayOfFloat[13] = 0.0F;
    paramArrayOfFloat[14] = 0.0F;
    paramArrayOfFloat[15] = 1.0F;
  }
  
  static final String[] a(String paramString, c paramc, int paramInt, boolean paramBoolean)
  {
    int i;
    String[] arrayOfString1 = new String[i = paramString.length()];
    int j = 0;
    int k = 0;
    int m = 0;
    int n = 0;
    int i1 = 0;
    int i2 = 0;
    int i3 = 0;
    int i4 = 1;
    int i5 = 0;
    char c2 = '\000';
    for (int i6 = 0; i6 < i + 1; i6++)
    {
      char c1;
      if (i6 >= i) {
        c1 = '\n';
      } else {
        c1 = paramString.charAt(i6);
      }
      n = c1;
      j = paramc.a(c1);
      if ((c1 != '\n') && (c1 != '\r'))
      {
        m += j;
        k += j;
      }
      switch (n)
      {
      case 32: 
        i4 = i6 + 1;
        k = 0;
        break;
      case 10: 
      case 13: 
        i4 = i6;
        m = paramInt + 1;
        k = 0;
        if (i6 < i)
        {
          i6++;
          if (i6 < i)
          {
            c2 = c1;
            if ((((c1 = paramString.charAt(i6)) == '\n') || (c1 == '\r')) && (c1 != c2)) {
              i6++;
            }
          }
          i5 = i6;
          i6--;
        }
        else
        {
          i5 = i;
        }
        c1 = '\n';
      }
      if (((m <= paramInt) || (!paramBoolean)) && (c1 != '\n'))
      {
        i1++;
      }
      else
      {
        if ((i4 == i3) && (i1 > 0))
        {
          i4 = i3 + i1;
          k = 0;
        }
        if (i4 > i3) {
          arrayOfString1[i2] = paramString.substring(i3, i4);
        } else {
          arrayOfString1[i2] = "";
        }
        if ((i3 = i4) < i5) {
          i3 = i5;
        }
        i4 = i3;
        m = k;
        i1 = i6 - i4 + 1;
        if ((arrayOfString1[i2] != null) && (arrayOfString1[i2].length() > 0)) {
          while ((arrayOfString1[i2].length() > 0) && (arrayOfString1[i2].charAt(arrayOfString1[i2].length() - 1) == ' ')) {
            arrayOfString1[i2] = arrayOfString1[i2].substring(0, arrayOfString1[i2].length() - 1);
          }
        }
        i2++;
      }
    }
    int i7 = i2;
    String[] arrayOfString2 = null;
    arrayOfString2 = new String[i7];
    System.arraycopy(arrayOfString1, 0, arrayOfString2, 0, i7);
    return arrayOfString2;
  }
}


/* Location:              E:\NET Lizard\3D其他\RacingEvolution3d240x320bySaNeC.jar!\b.class
 * Java compiler version: 4 (48.0)
 * JD-Core Version:       0.7.1
 */