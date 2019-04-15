import java.io.PrintStream;
import java.util.Hashtable;
import javax.microedition.lcdui.Graphics;
import javax.microedition.m3g.Appearance;
import javax.microedition.m3g.Background;
import javax.microedition.m3g.Camera;
import javax.microedition.m3g.CompositingMode;
import javax.microedition.m3g.Graphics3D;
import javax.microedition.m3g.Image2D;
import javax.microedition.m3g.Light;
import javax.microedition.m3g.Material;
import javax.microedition.m3g.Mesh;
import javax.microedition.m3g.PolygonMode;
import javax.microedition.m3g.Sprite3D;
import javax.microedition.m3g.Texture2D;
import javax.microedition.m3g.Transform;
import javax.microedition.m3g.TriangleStripArray;
import javax.microedition.m3g.VertexArray;
import javax.microedition.m3g.VertexBuffer;

public final class e
{
  public static int a;
  static final byte[] b = { 78, 76, 95, 77, 69, 83, 72 };
  static float c;
  public static int d;
  public static float[] e;
  public static Transform f;
  static Transform g;
  static Graphics3D h;
  static Transform i;
  public static Background j;
  public static Camera k;
  public static Light l;
  static int m;
  static Appearance n;
  static TriangleStripArray o;
  static VertexArray p;
  static VertexBuffer q;
  static int r;
  static Texture2D[] s;
  static String[] t;
  static Appearance u;
  static Transform v;
  static Sprite3D[] w;
  static boolean x = false;
  
  static
  {
    m = 0;
    c = 0.00390625F;
  }
  
  public e()
  {
    h = Graphics3D.getInstance();
    e();
    d();
  }
  
  public static final void a(Graphics paramGraphics)
  {
    h.bindTarget(paramGraphics);
    h.setCamera(k, f);
    h.clear(j);
  }
  
  public static final void a(float paramFloat1, float paramFloat2, float paramFloat3, float paramFloat4, float paramFloat5, float paramFloat6, float paramFloat7, float paramFloat8, float paramFloat9)
  {
    b.a(e, paramFloat1, paramFloat2, paramFloat3, paramFloat4, paramFloat5, paramFloat6, paramFloat7, paramFloat8, paramFloat9);
    f.set(e);
  }
  
  public static final void a(float paramFloat1, float paramFloat2, float paramFloat3)
  {
    float f1 = d;
    float f2 = a;
    k.setPerspective(paramFloat1, f1 / f2, paramFloat2, paramFloat3);
  }
  
  public static final void a()
  {
    m = 0;
    w = new Sprite3D[6];
  }
  
  public static final void a(float paramFloat1, float paramFloat2, float paramFloat3, float paramFloat4, int paramInt)
  {
    v.setIdentity();
    v.postTranslate(paramFloat1, paramFloat2, paramFloat3);
    v.postScale(paramFloat4, paramFloat4, paramFloat4);
    try
    {
      h.render(w[paramInt], v);
      return;
    }
    catch (Exception localException)
    {
      System.out.println("SPRITE - ERROR");
    }
  }
  
  static final void a(short[] paramArrayOfShort, float paramFloat, l paraml)
  {
    Transform localTransform = i;
    if (paraml != null) {
      localTransform = (Transform)paraml.a();
    }
    p.set(0, 4, paramArrayOfShort);
    q.setPositions(p, paramFloat, null);
    h.render(q, o, n, localTransform);
  }
  
  public static final void b()
  {
    h.releaseTarget();
  }
  
  private static void c()
  {
    new VertexArray(4, 3, 1);
    p = new VertexArray(4, 3, 2);
    q = new VertexBuffer();
    q.setDefaultColor(-1118482);
    int[] arrayOfInt;
    (arrayOfInt = new int[1])[0] = 4;
    o = new TriangleStripArray(0, arrayOfInt);
    n = new Appearance();
    CompositingMode localCompositingMode;
    (localCompositingMode = new CompositingMode()).setDepthTestEnable(false);
    localCompositingMode.setDepthWriteEnable(false);
    localCompositingMode.setBlending(66);
    n.setCompositingMode(localCompositingMode);
    PolygonMode localPolygonMode;
    (localPolygonMode = new PolygonMode()).setCulling(160);
    localPolygonMode.setShading(164);
    n.setPolygonMode(localPolygonMode);
    n.setTexture(0, null);
  }
  
  private static void d()
  {
    u = new Appearance();
    CompositingMode localCompositingMode;
    (localCompositingMode = new CompositingMode()).setBlending(64);
    localCompositingMode.setDepthWriteEnable(false);
    localCompositingMode.setDepthTestEnable(true);
    u.setCompositingMode(localCompositingMode);
    v = new Transform();
    w = new Sprite3D[6];
    m = 0;
  }
  
  private static void e()
  {
    g = new Transform();
    g.setIdentity();
    k = new Camera();
    f = new Transform();
    e = new float[16];
    i = new Transform();
    i.setIdentity();
    j = new Background();
    j.setColorClearEnable(false);
    l = new Light();
    l.setOrientation(-66.0F, 1.0F, 0.0F, 0.0F);
    l.postRotate(15.0F, 0.0F, 1.0F, 0.0F);
    new Transform();
    Appearance localAppearance;
    (localAppearance = new Appearance()).setTexture(0, null);
    PolygonMode localPolygonMode;
    (localPolygonMode = new PolygonMode()).setCulling(160);
    localPolygonMode.setShading(164);
    localAppearance.setPolygonMode(localPolygonMode);
    CompositingMode localCompositingMode;
    (localCompositingMode = new CompositingMode()).setBlending(66);
    localCompositingMode.setAlphaWriteEnable(false);
    localCompositingMode.setDepthWriteEnable(true);
    localCompositingMode.setDepthTestEnable(true);
    localCompositingMode.setDepthOffset(-4.0F, 0.0F);
    localAppearance.setCompositingMode(localCompositingMode);
    c();
  }
  
  private static final k[] a(byte[] paramArrayOfByte, int paramInt)
  {
    int i1 = paramInt;
    int i2 = 0;
    int i3 = paramArrayOfByte[(i1++)];
    int i4;
    k[] arrayOfk = new k[i4 = b.a(paramArrayOfByte[(i1++)], paramArrayOfByte[(i1++)])];
    Appearance[] arrayOfAppearance = new Appearance[i3];
    int[] arrayOfInt = new int[i4];
    t = new String[i3];
    s = new Texture2D[i3];
    r = 0;
    int i5 = 0;
    int i7;
    try
    {
      for (i6 = 0; i6 < i3; i6++) {
        if ((i2 = paramArrayOfByte[(i1++)] & 0xFF) == 225) {
          try
          {
            i1 = a(arrayOfAppearance, i5++, paramArrayOfByte, i1);
          }
          catch (Exception localException1) {}
        }
      }
      i5 = 0;
      for (i7 = 0; i7 < i4; i7++) {
        if ((i2 = paramArrayOfByte[(i1++)] & 0xFF) == 241) {
          try
          {
            i1 = a(arrayOfk, arrayOfInt, i5++, paramArrayOfByte, i1);
          }
          catch (Exception localException2) {}
        }
      }
    }
    catch (Exception localException3) {}
    for (int i6 = 0; i6 < i4; i6++) {
      if ((i7 = arrayOfInt[i6]) < 127)
      {
        arrayOfk[i6].e = arrayOfAppearance[i7];
        int i8;
        if (((i8 = arrayOfAppearance[i7].getUserID()) & 0x4) != 0) {
          arrayOfk[i6].a = true;
        }
      }
    }
    return arrayOfk;
  }
  
  private static final int a(Appearance[] paramArrayOfAppearance, int paramInt1, byte[] paramArrayOfByte, int paramInt2)
  {
    int i1 = paramInt2;
    Appearance localAppearance = new Appearance();
    new Material();
    i1 += 13;
    int i2 = b.c(paramArrayOfByte, i1);
    i1 += 4;
    char[] arrayOfChar = null;
    int i3;
    Object localObject;
    if ((i3 = paramArrayOfByte[(i1++)] & 0xFF) > 0)
    {
      localObject = new char[32];
      int i4 = 0;
      for (int i5 = paramArrayOfByte[(i1++)]; i5 != 0; i5 = paramArrayOfByte[(i1++)])
      {
        if (i5 < 0) {
          i5 = 256 + i5;
        }
        if ((i5 >= 192) && (i5 <= 255)) {
          i5 += 848;
        }
        if ((i5 >= 65) && (i5 <= 90)) {
          i5 += 32;
        }
        localObject[(i4++)] = ((char)i5);
      }
      arrayOfChar = new char[i4];
      System.arraycopy(localObject, 0, arrayOfChar, 0, i4);
    }
    (localObject = new PolygonMode()).setCulling(160);
    ((PolygonMode)localObject).setPerspectiveCorrectionEnable(false);
    localAppearance.setPolygonMode((PolygonMode)localObject);
    CompositingMode localCompositingMode;
    (localCompositingMode = new CompositingMode()).setDepthWriteEnable(true);
    localCompositingMode.setDepthTestEnable(true);
    localAppearance.setCompositingMode(localCompositingMode);
    localAppearance.setUserID(i2);
    if (arrayOfChar != null) {
      try
      {
        String str1 = new String(arrayOfChar);
        String str2 = "/" + str1;
        int i6 = 0;
        if (str1.endsWith("a.png")) {
          i6 = 1;
        }
        int i7 = -1;
        for (int i8 = 0; i8 < r; i8++) {
          if (str2.compareTo(t[i8]) == 0)
          {
            i7 = i8;
            break;
          }
        }
        Texture2D localTexture2D;
        if (i7 >= 0)
        {
          localTexture2D = s[i7];
        }
        else
        {
          int i9 = 99;
          if (i6 != 0) {
            i9 = 100;
          }
          Image2D localImage2D = new Image2D(i9, d.a(str2));
          localTexture2D = new Texture2D(localImage2D);
          s[r] = localTexture2D;
          t[r] = str2;
          r += 1;
        }
        if (i6 != 0)
        {
          localCompositingMode.setAlphaWriteEnable(true);
          localAppearance.getCompositingMode().setBlending(64);
        }
        localTexture2D.setBlending(228);
        localTexture2D.setFiltering(210, 210);
        localTexture2D.setWrapping(240, 240);
        localAppearance.setTexture(0, localTexture2D);
      }
      catch (Exception localException) {}
    }
    paramArrayOfAppearance[paramInt1] = localAppearance;
    return i1;
  }
  
  private static final int a(k[] paramArrayOfk, int[] paramArrayOfInt, int paramInt1, byte[] paramArrayOfByte, int paramInt2)
  {
    int i1 = paramInt2;
    int i2 = b.a(paramArrayOfByte[(i1++)], paramArrayOfByte[(i1++)]);
    i1++;
    i1++;
    int i3 = b.a(paramArrayOfByte[(i1++)], paramArrayOfByte[(i1++)]);
    int i4 = b.a(paramArrayOfByte[(i1++)], paramArrayOfByte[(i1++)]);
    int i5 = paramArrayOfByte[(i1++)] & 0xFF;
    float[] arrayOfFloat = new float[3];
    for (int i6 = 0; i6 < 3; i6++)
    {
      arrayOfFloat[i6] = b.a(paramArrayOfByte, i1);
      i1 += 4;
    }
    float f1 = b.a(paramArrayOfByte, i1);
    i1 += 4;
    paramArrayOfk[paramInt1] = new k();
    paramArrayOfk[paramInt1].h = b.a(paramArrayOfByte, i1);
    i1 += 4;
    b.a(paramArrayOfByte, i1);
    i1 += 4;
    paramArrayOfk[paramInt1].i = b.a(paramArrayOfByte, i1);
    i1 += 4;
    paramArrayOfk[paramInt1].f = b.a(paramArrayOfByte, i1);
    i1 += 4;
    paramArrayOfk[paramInt1].b = ((int)(paramArrayOfk[paramInt1].h * 4095.0F));
    paramArrayOfk[paramInt1].c = ((int)(paramArrayOfk[paramInt1].h * 4095.0F));
    VertexBuffer localVertexBuffer = new VertexBuffer();
    float f2 = 3.051851E-5F * f1;
    int i7 = paramArrayOfByte[(i1++)] & 0xFF;
    int i8 = 0;
    int i9;
    if (i7 == 242)
    {
      VertexArray localVertexArray1 = new VertexArray(i2, 3, 2);
      localObject = new short[i2 * 3];
      for (i9 = 0; i9 < i2 * 3; i9++)
      {
        i8 = b.a(paramArrayOfByte[(i1++)], paramArrayOfByte[(i1++)]) - 32767;
        localObject[i9] = ((short)i8);
      }
      localVertexArray1.set(0, i2, (short[])localObject);
      localVertexBuffer.setPositions(localVertexArray1, f2, arrayOfFloat);
      i7 = paramArrayOfByte[(i1++)] & 0xFF;
    }
    if (i7 == 244)
    {
      VertexArray localVertexArray2 = new VertexArray(i2, 2, 2);
      localObject = new short[i2 * 2];
      for (i9 = 0; i9 < i2; i9++)
      {
        localObject[(i9 * 2)] = ((short)(paramArrayOfByte[(i1++)] & 0xFF));
        localObject[(i9 * 2 + 1)] = ((short)(255 - (paramArrayOfByte[(i1++)] & 0xFF)));
      }
      localVertexArray2.set(0, i2, (short[])localObject);
      localVertexBuffer.setTexCoords(0, localVertexArray2, 0.003921569F, null);
      i7 = paramArrayOfByte[(i1++)] & 0xFF;
    }
    Object localObject = new int[i3];
    if (i7 == 245)
    {
      for (i9 = 0; i9 < i3; i9++) {
        localObject[i9] = b.a(paramArrayOfByte[(i1++)], paramArrayOfByte[(i1++)]);
      }
      i7 = paramArrayOfByte[(i1++)] & 0xFF;
    }
    int[] arrayOfInt = new int[i4];
    if (i7 == 246) {
      for (int i10 = 0; i10 < i4; i10++) {
        arrayOfInt[i10] = b.a(paramArrayOfByte[(i1++)], paramArrayOfByte[(i1++)]);
      }
    }
    TriangleStripArray localTriangleStripArray = new TriangleStripArray((int[])localObject, arrayOfInt);
    paramArrayOfk[paramInt1].d = new Mesh(localVertexBuffer, localTriangleStripArray, null);
    paramArrayOfInt[paramInt1] = i5;
    return i1;
  }
  
  public static final k[] a(String paramString)
  {
    byte[] arrayOfByte = null;
    arrayOfByte = b.b.b(paramString);
    for (int i1 = 0; i1 < b.length; i1++) {
      if (arrayOfByte[i1] != b[i1]) {
        return null;
      }
    }
    int i2 = b.length;
    return a(arrayOfByte, i2);
  }
  
  public static final int b(String paramString)
  {
    if (m >= 6) {
      return -1;
    }
    try
    {
      Image2D localImage2D = new Image2D(100, d.a(paramString));
      w[m] = new Sprite3D(true, localImage2D, u);
      return m++;
    }
    catch (Exception localException) {}
    return -1;
  }
  
  public static final void a(int paramInt)
  {
    x = false;
    if (paramInt > 0) {
      try
      {
        Boolean localBoolean;
        if ((localBoolean = (Boolean)Graphics3D.getProperties().get("supportPerspectiveCorrection")).booleanValue()) {
          x = true;
        }
        return;
      }
      catch (Exception localException) {}
    }
  }
  
  public static final void a(int paramInt1, int paramInt2)
  {
    d = paramInt1;
    a = paramInt2;
  }
}


/* Location:              E:\NET Lizard\3D其他\RacingEvolution3d240x320bySaNeC.jar!\e.class
 * Java compiler version: 4 (48.0)
 * JD-Core Version:       0.7.1
 */