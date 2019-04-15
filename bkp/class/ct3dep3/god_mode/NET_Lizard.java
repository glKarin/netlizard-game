import javax.microedition.midlet.MIDlet;

public final class NET_Lizard
  extends MIDlet
  implements Runnable
{
  static NET_Lizard a;
  private static int cP = 0;
  static i c;
  private static boolean bs = true;
  private static int cQ = 0;
  
  public static String g(String paramString)
  {
    if (paramString == "microedition.platform") {
      return "SonyEricssonW900i";
    }
    return System.getProperty(paramString);
  }
  
  public NET_Lizard()
  {
    new Thread(this).start();
    a = this;
    if (n.a == null) {
      n.be();
    }
    if (c == null) {
      c = new i();
    }
  }
  
  public final String h(String paramString)
  {
    if (++cQ == 1) {
      return "MIDP-2.0";
    }
    if (cQ == 2) {
      return "NET Lizard";
    }
    if (cQ == 3) {
      return "CT episode 3";
    }
    return getAppProperty(paramString);
  }
  
  public final void run()
  {
    try
    {
      for (;;)
      {
        Thread.sleep(1024L);
        for (int i = 0; i < i.l.length; i++) {
          i.l[i] = Byte.MAX_VALUE;
        }
        for (i = 0; i < i.m.length; i++) {
          i.m[i] = Byte.MAX_VALUE;
        }
        for (i = 0; i < i.b.length; i++) {
          i.b[i] = 0;
        }
        i.a[0].B = 1000;
      }
    }
    catch (Exception localException) {}
  }
  
  public final void destroyApp(boolean paramBoolean)
  {
    if (bs)
    {
      try
      {
        i.ae = false;
      }
      catch (Exception localException1) {}
      try
      {
        d.R();
      }
      catch (Exception localException2) {}
    }
    n.bd();
    try
    {
      c.d = null;
    }
    catch (Exception localException3) {}
    c = null;
    cP = 0;
    notifyDestroyed();
  }
  
  public final void pauseApp()
  {
    cP = 2;
    notifyPaused();
  }
  
  public static void bg()
  {
    bs = false;
    a.destroyApp(true);
    a.notifyDestroyed();
    a = null;
  }
  
  public final void startApp()
  {
    q.bf();
    a.b = true;
    if (cP == 0) {
      c.as();
    }
    cP = 1;
    bs = true;
  }
}


/* Location:              C:\Users\Administrator\Desktop\CT3_God_Mode.jar!\NET_Lizard.class
 * Java compiler version: 1 (45.3)
 * JD-Core Version:       0.7.1
 */