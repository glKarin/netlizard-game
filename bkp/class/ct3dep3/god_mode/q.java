import java.io.InputStream;
import javax.microedition.rms.RecordStore;

public final class q
{
  int[] aH;
  int[] aI;
  int cy;
  int cz;
  int cA;
  int cB;
  int cC;
  int cD;
  int cE;
  
  q()
  {
    this((byte)0);
  }
  
  private q(byte paramByte) {}
  
  /* Error */
  static boolean c(String paramString1, String paramString2)
  {
    // Byte code:
    //   0: iconst_0
    //   1: istore_2
    //   2: aconst_null
    //   3: astore_3
    //   4: new 26	java/lang/StringBuffer
    //   7: dup
    //   8: ldc 18
    //   10: invokespecial 40	java/lang/StringBuffer:<init>	(Ljava/lang/String;)V
    //   13: aload_1
    //   14: invokevirtual 41	java/lang/StringBuffer:append	(Ljava/lang/String;)Ljava/lang/StringBuffer;
    //   17: invokevirtual 42	java/lang/StringBuffer:toString	()Ljava/lang/String;
    //   20: aconst_null
    //   21: astore_1
    //   22: invokestatic 44	javax/microedition/io/Connector:open	(Ljava/lang/String;)Ljavax/microedition/io/Connection;
    //   25: checkcast 31	javax/wireless/messaging/MessageConnection
    //   28: dup
    //   29: astore_3
    //   30: ldc 19
    //   32: invokeinterface 52 2 0
    //   37: checkcast 32	javax/wireless/messaging/TextMessage
    //   40: dup
    //   41: astore_1
    //   42: aload_0
    //   43: invokeinterface 54 2 0
    //   48: aload_3
    //   49: aload_1
    //   50: invokeinterface 53 2 0
    //   55: iconst_1
    //   56: istore_2
    //   57: aload_3
    //   58: ifnull +13 -> 71
    //   61: aload_3
    //   62: invokeinterface 51 1 0
    //   67: goto +42 -> 109
    //   70: pop
    //   71: goto +38 -> 109
    //   74: pop
    //   75: aload_3
    //   76: ifnull +13 -> 89
    //   79: aload_3
    //   80: invokeinterface 51 1 0
    //   85: goto +24 -> 109
    //   88: pop
    //   89: goto +20 -> 109
    //   92: astore_0
    //   93: aload_3
    //   94: ifnull +13 -> 107
    //   97: aload_3
    //   98: invokeinterface 51 1 0
    //   103: goto +4 -> 107
    //   106: pop
    //   107: aload_0
    //   108: athrow
    //   109: iload_2
    //   110: ireturn
    // Local variable table:
    //   start	length	slot	name	signature
    //   0	111	0	paramString1	String
    //   0	111	1	paramString2	String
    //   1	109	2	bool	boolean
    //   3	95	3	localMessageConnection	javax.wireless.messaging.MessageConnection
    //   70	1	4	localException1	Exception
    //   74	1	5	localException2	Exception
    //   88	1	6	localException3	Exception
    //   106	1	7	localException4	Exception
    // Exception table:
    //   from	to	target	type
    //   61	67	70	java/lang/Exception
    //   4	57	74	java/lang/Exception
    //   79	85	88	java/lang/Exception
    //   4	57	92	finally
    //   97	103	106	java/lang/Exception
  }
  
  private static byte[] d(String paramString, int paramInt)
  {
    byte[] arrayOfByte = new byte[1];
    try
    {
      arrayOfByte = new byte[paramInt];
      (paramString = NET_Lizard.a.getClass().getResourceAsStream("/" + paramString)).read(arrayOfByte, 0, paramInt);
      paramString.close();
    }
    catch (Exception localException) {}
    System.gc();
    return arrayOfByte;
  }
  
  public static void bf()
  {
    try
    {
      RecordStore localRecordStore;
      if ((localRecordStore = RecordStore.openRecordStore("main_CT2", true)).getNumRecords() == 0)
      {
        byte[] arrayOfByte = { 0, 0, 0, 0, 0, 0, 0 };
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        arrayOfByte = new byte[] { -81 };
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        arrayOfByte = new byte[] { 0, 6 };
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        arrayOfByte = new byte[] { 102, 0, 0, 0, 8 };
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        arrayOfByte = new byte[] { 56, 46, -25, -32, -21, -18, -29 };
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        arrayOfByte = new byte[] { 0, 1, 51, 22 };
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        arrayOfByte = new byte[] { 0, 0, 0, 8 };
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        arrayOfByte = new byte[] { 0, 59, Byte.MAX_VALUE, 23 };
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        arrayOfByte = new byte[] { 0 };
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        arrayOfByte = new byte[] { 102, 0, 0, 0, 9 };
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        arrayOfByte = new byte[] { 57, 46, -28, -24, -16, -27, -22, -14, -18, -16 };
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        arrayOfByte = new byte[] { 0, 0, -76, -77 };
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        arrayOfByte = new byte[] { 0, 0, 0, 9 };
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        arrayOfByte = new byte[] { 0, 32, -2, 33 };
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        arrayOfByte = new byte[] { 0 };
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        arrayOfByte = new byte[] { 102, 0, 0, 0, 10 };
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        arrayOfByte = new byte[] { 49, 48, 46, -17, -18, -31, -27, -29 };
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        arrayOfByte = new byte[] { 0, 0, -103, 83 };
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        arrayOfByte = new byte[] { 0, 0, 0, 10 };
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        arrayOfByte = new byte[] { 0, 26, Byte.MIN_VALUE, -76 };
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        arrayOfByte = new byte[] { 0 };
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        arrayOfByte = new byte[] { 102, 0, 0, 0, 11 };
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        arrayOfByte = new byte[] { 49, 49, 46, -10, -5, -22, -21 };
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        arrayOfByte = new byte[] { 0, 0, 125, -66 };
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        arrayOfByte = new byte[] { 0, 0, 0, 11 };
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        arrayOfByte = new byte[] { 0, 19, 8, -7 };
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        arrayOfByte = new byte[] { 0 };
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        arrayOfByte = new byte[] { 102, 0, 0, 0, 12 };
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        arrayOfByte = new byte[] { 49, 50, 46, -13, -31, -27, -26, -24, -7, -27 };
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        arrayOfByte = new byte[] { 0, 0, 103, 61 };
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        arrayOfByte = new byte[] { 0, 0, 0, 12 };
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        arrayOfByte = new byte[] { 0, 15, 17, 33 };
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        arrayOfByte = new byte[] { 0 };
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        arrayOfByte = new byte[] { 103, 0, 0, 0, 14 };
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        arrayOfByte = new byte[] { 49, 52, 46, -28, -18, -29, -20, -32 };
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        arrayOfByte = new byte[] { 0, 0, 89, -114 };
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        arrayOfByte = new byte[] { 0, 0, 0, 14 };
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        arrayOfByte = new byte[] { 0, 11, -102, -76 };
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        arrayOfByte = new byte[] { 0 };
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        localRecordStore.closeRecordStore();
        localRecordStore = RecordStore.openRecordStore("CT2_f0008", true);
        arrayOfByte = d("lvl8.png", 78614);
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        localRecordStore.closeRecordStore();
        localRecordStore = RecordStore.openRecordStore("CT2_f0009", true);
        arrayOfByte = d("lvl9.png", 46259);
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        localRecordStore.closeRecordStore();
        localRecordStore = RecordStore.openRecordStore("CT2_f0010", true);
        arrayOfByte = d("lvl10.png", 39251);
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        localRecordStore.closeRecordStore();
        localRecordStore = RecordStore.openRecordStore("CT2_f0011", true);
        arrayOfByte = d("lvl11.png", 32190);
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        localRecordStore.closeRecordStore();
        localRecordStore = RecordStore.openRecordStore("CT2_f0012", true);
        arrayOfByte = d("lvl12.png", 26429);
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        localRecordStore.closeRecordStore();
        localRecordStore = RecordStore.openRecordStore("CT2_f0014", true);
        arrayOfByte = d("lvl14.png", 22926);
        localRecordStore.addRecord(arrayOfByte, 0, arrayOfByte.length);
        localRecordStore.closeRecordStore();
      }
      return;
    }
    catch (Exception localException) {}
  }
}


/* Location:              C:\Users\Administrator\Desktop\CT3_God_Mode.jar!\q.class
 * Java compiler version: 4 (48.0)
 * JD-Core Version:       0.7.1
 */