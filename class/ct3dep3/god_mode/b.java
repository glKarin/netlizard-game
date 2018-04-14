import java.io.InputStream;
import java.util.Vector;
import javax.microedition.io.Connector;
import javax.microedition.io.HttpConnection;
import javax.microedition.lcdui.Graphics;
import javax.microedition.lcdui.Image;
import javax.microedition.rms.RecordStore;

public final class b
  implements Runnable
{
  private static int jdField_i_of_type_Int;
  private static boolean jdField_d_of_type_Boolean;
  private static Vector jdField_a_of_type_JavaUtilVector;
  private static int jdField_j_of_type_Int = 0;
  private static m jdField_b_of_type_M;
  private static long jdField_a_of_type_Long;
  private static String jdField_b_of_type_JavaLangString;
  private static String jdField_c_of_type_JavaLangString;
  private static String jdField_d_of_type_JavaLangString;
  private static int jdField_k_of_type_Int;
  private static int jdField_l_of_type_Int;
  private static int jdField_m_of_type_Int;
  private static int n;
  private static int o;
  static int[] jdField_a_of_type_ArrayOfInt;
  private static int p;
  private static Vector jdField_b_of_type_JavaUtilVector;
  private static int q = 0;
  private static boolean jdField_e_of_type_Boolean;
  private static int r;
  private static int s;
  private static int t;
  private static byte jdField_j_of_type_Byte;
  private static Image[] jdField_c_of_type_ArrayOfJavaxMicroeditionLcduiImage;
  private static Image[] jdField_d_of_type_ArrayOfJavaxMicroeditionLcduiImage;
  private static byte[] jdField_d_of_type_ArrayOfByte;
  private static char jdField_a_of_type_Char;
  private static boolean jdField_f_of_type_Boolean;
  private static boolean jdField_g_of_type_Boolean;
  private static b jdField_a_of_type_B;
  private static Vector jdField_c_of_type_JavaUtilVector;
  static boolean jdField_h_of_type_Boolean = false;
  private static boolean jdField_i_of_type_Boolean;
  private static boolean jdField_j_of_type_Boolean;
  private static String jdField_e_of_type_JavaLangString;
  static int u;
  private static Image[] jdField_e_of_type_ArrayOfJavaxMicroeditionLcduiImage;
  private static int v;
  private static Vector jdField_d_of_type_JavaUtilVector;
  private static int w;
  private static long jdField_b_of_type_Long;
  private static Image[] jdField_f_of_type_ArrayOfJavaxMicroeditionLcduiImage;
  private static boolean jdField_k_of_type_Boolean;
  private static boolean jdField_l_of_type_Boolean;
  private static String[] jdField_b_of_type_ArrayOfJavaLangString;
  private static String jdField_f_of_type_JavaLangString;
  private static byte[] jdField_e_of_type_ArrayOfByte;
  private static Image[] jdField_g_of_type_ArrayOfJavaxMicroeditionLcduiImage;
  private static byte[] jdField_f_of_type_ArrayOfByte;
  private static byte jdField_k_of_type_Byte;
  private static String jdField_g_of_type_JavaLangString;
  private static Vector jdField_e_of_type_JavaUtilVector;
  private static int x;
  private static int y;
  private static int z;
  private static boolean jdField_m_of_type_Boolean;
  private static String jdField_h_of_type_JavaLangString;
  private static String[] jdField_c_of_type_ArrayOfJavaLangString;
  private static int[] jdField_b_of_type_ArrayOfInt;
  private static Thread jdField_a_of_type_JavaLangThread;
  private static int A;
  private static long jdField_c_of_type_Long = 0L;
  private static byte jdField_l_of_type_Byte;
  private static Vector jdField_f_of_type_JavaUtilVector;
  private static String jdField_i_of_type_JavaLangString;
  private static String jdField_j_of_type_JavaLangString;
  private static int B;
  
  static
  {
    s = 240;
    n = 320;
    jdField_a_of_type_Long = 0L;
    t = 0;
    y = 0;
    jdField_j_of_type_Boolean = false;
    jdField_g_of_type_Boolean = false;
    jdField_f_of_type_Boolean = true;
    jdField_l_of_type_Byte = 0;
    jdField_k_of_type_Byte = 0;
    jdField_h_of_type_JavaLangString = "";
    jdField_a_of_type_Char = '\000';
    jdField_f_of_type_JavaLangString = "";
    jdField_b_of_type_JavaLangString = "";
    A = 1;
    jdField_c_of_type_JavaLangString = "main_CT2";
    jdField_d_of_type_JavaLangString = "CT2_f";
    jdField_e_of_type_Boolean = true;
    jdField_k_of_type_Boolean = false;
    jdField_j_of_type_JavaLangString = "http://netlizard.net/levels/CT2/menu/down.png";
    r = s >> 5;
    jdField_l_of_type_Int = n >> 5;
    x = 0;
    z = 0;
    jdField_l_of_type_Boolean = false;
    w = 0;
    jdField_b_of_type_ArrayOfInt = new int[] { 56, 60, 23 };
  }
  
  public b()
  {
    jdField_a_of_type_JavaLangThread = new Thread(this);
  }
  
  private static int a(boolean paramBoolean)
  {
    if (jdField_d_of_type_ArrayOfJavaxMicroeditionLcduiImage == null) {
      return 0;
    }
    if (jdField_d_of_type_ArrayOfJavaxMicroeditionLcduiImage[0] == null) {
      return 0;
    }
    if (paramBoolean) {
      return jdField_d_of_type_ArrayOfJavaxMicroeditionLcduiImage[0].getWidth();
    }
    return jdField_d_of_type_ArrayOfJavaxMicroeditionLcduiImage[0].getHeight();
  }
  
  private static int a(boolean paramBoolean, int paramInt)
  {
    if (jdField_e_of_type_ArrayOfJavaxMicroeditionLcduiImage == null) {
      return 0;
    }
    if (jdField_e_of_type_ArrayOfJavaxMicroeditionLcduiImage[paramInt] == null) {
      return 0;
    }
    if (paramBoolean) {
      return jdField_e_of_type_ArrayOfJavaxMicroeditionLcduiImage[paramInt].getWidth();
    }
    return jdField_e_of_type_ArrayOfJavaxMicroeditionLcduiImage[paramInt].getHeight();
  }
  
  private static int a()
  {
    if (jdField_f_of_type_ArrayOfJavaxMicroeditionLcduiImage == null) {
      return 0;
    }
    if (jdField_f_of_type_ArrayOfJavaxMicroeditionLcduiImage[0] == null) {
      return 0;
    }
    return jdField_f_of_type_ArrayOfJavaxMicroeditionLcduiImage[0].getHeight();
  }
  
  private static int b(boolean paramBoolean, int paramInt)
  {
    if (jdField_g_of_type_ArrayOfJavaxMicroeditionLcduiImage == null) {
      return 0;
    }
    if (jdField_g_of_type_ArrayOfJavaxMicroeditionLcduiImage[paramInt] == null) {
      return 0;
    }
    if (paramBoolean) {
      return jdField_g_of_type_ArrayOfJavaxMicroeditionLcduiImage[paramInt].getWidth();
    }
    return jdField_g_of_type_ArrayOfJavaxMicroeditionLcduiImage[paramInt].getHeight();
  }
  
  private static void a(char paramChar)
  {
    if (jdField_g_of_type_JavaLangString == null) {
      jdField_g_of_type_JavaLangString = "";
    }
    if (jdField_g_of_type_JavaLangString.length() > 12) {
      return;
    }
    if (paramChar == '+')
    {
      jdField_g_of_type_JavaLangString += ';';
      return;
    }
    jdField_g_of_type_JavaLangString += paramChar;
  }
  
  private static void a(byte[] paramArrayOfByte, int paramInt)
  {
    jdField_g_of_type_Boolean = false;
    int i1 = paramInt + 1;
    if (paramInt == -1) {
      i1 = 0;
    }
    jdField_a_of_type_Char = '\000';
    int i2;
    int i3;
    Object localObject;
    byte[] arrayOfByte;
    switch (paramArrayOfByte[i1])
    {
    case 77: 
      paramInt = "http://";
      i2 = paramArrayOfByte.length;
      for (i3 = i1 + 2; i3 < i2; i3++)
      {
        if (paramArrayOfByte[i3] == 59) {
          break;
        }
        paramInt = paramInt + (char)paramArrayOfByte[i3];
      }
      jdField_a_of_type_B.a(paramInt);
      jdField_a_of_type_Char = (char)paramArrayOfByte[i1];
      return;
    case 85: 
      paramInt = "http://";
      i2 = paramArrayOfByte.length;
      for (i3 = i1 + 2; i3 < i2; i3++)
      {
        if (paramArrayOfByte[i3] == 124) {
          break;
        }
        paramInt = paramInt + (char)paramArrayOfByte[i3];
      }
      jdField_a_of_type_B.a(paramInt);
      jdField_a_of_type_Char = (char)paramArrayOfByte[i1];
      return;
    case 87: 
      i2 = paramArrayOfByte.length;
      paramInt = "";
      for (i3 = 2; i3 < i2; i3++) {
        paramInt = paramInt + a(paramArrayOfByte[i3]);
      }
      paramInt = n.a(paramInt, jdField_b_of_type_M, s - (r << 1), true);
      for (i2 = 0; i2 < paramInt.length; i2++) {
        jdField_d_of_type_JavaUtilVector.addElement(paramInt[i2]);
      }
      jdField_a_of_type_Char = (char)paramArrayOfByte[i1];
      return;
    case 68: 
      i2 = paramArrayOfByte.length;
      paramInt = "http://";
      i3 = -1;
      for (int i4 = i1 + 2; i4 < i2; i4++)
      {
        if (paramArrayOfByte[i4] == 124)
        {
          i2 = i4;
          break;
        }
        if ((i3 == -1) && (paramArrayOfByte[i4] == 61)) {
          i3 = i4;
        }
        paramInt = paramInt + (char)paramArrayOfByte[i4];
      }
      jdField_a_of_type_Char = (char)paramArrayOfByte[i1];
      jdField_h_of_type_JavaLangString = "";
      for (i1 = i3 + 1; i1 < i2; i1++)
      {
        if ((paramArrayOfByte[i1] == 124) || (paramArrayOfByte[i1] == 59)) {
          break;
        }
        jdField_h_of_type_JavaLangString += (char)paramArrayOfByte[i1];
      }
      if ((jdField_a_of_type_ArrayOfInt = a()) == null)
      {
        jdField_k_of_type_Byte = 20;
        jdField_a_of_type_B.a(paramInt);
        return;
      }
      i1 = 0;
      for (paramArrayOfByte = 0; paramArrayOfByte < jdField_a_of_type_ArrayOfInt.length; paramArrayOfByte++) {
        if (t == jdField_a_of_type_ArrayOfInt[paramArrayOfByte] - i.aL)
        {
          u = jdField_a_of_type_ArrayOfInt[paramArrayOfByte];
          a.b(jdField_a_of_type_ArrayOfInt[paramArrayOfByte]);
          i.as = true;
          jdField_h_of_type_Boolean = false;
          i1 = 1;
          break;
        }
      }
      if (i1 == 0)
      {
        jdField_k_of_type_Byte = 20;
        jdField_a_of_type_B.a(paramInt);
      }
      return;
    case 76: 
      i2 = paramArrayOfByte.length;
      jdField_f_of_type_JavaLangString = "";
      jdField_b_of_type_JavaLangString = "";
      i1 += 2;
      while (i1 < i2)
      {
        jdField_f_of_type_JavaLangString += (char)paramArrayOfByte[i1];
        jdField_b_of_type_JavaLangString += (char)paramArrayOfByte[i1];
        i1++;
      }
      paramArrayOfByte = jdField_c_of_type_JavaUtilVector.size();
      for (paramInt = 0; paramInt < paramArrayOfByte; paramInt++)
      {
        localObject = (byte[])jdField_c_of_type_JavaUtilVector.elementAt(paramInt);
        i2 = 0;
        for (i3 = 0; i3 < 20; i3++)
        {
          if (localObject[i3] == 0) {
            break;
          }
          i2++;
        }
        arrayOfByte = new byte[i2 + 1];
        for (i3 = 0; i3 < i2; i3++) {
          arrayOfByte[(i3 + 1)] = localObject[i3];
        }
        arrayOfByte[0] = 36;
        jdField_b_of_type_JavaUtilVector.addElement(arrayOfByte);
      }
      return;
    case 82: 
      if ((localObject = a()) != null)
      {
        for (i2 = 0; i2 < localObject.length; i2++)
        {
          arrayOfByte = new byte[(i3 = localObject[i2].length()) + 1];
          for (paramInt = 0; paramInt < i3; paramInt++) {
            arrayOfByte[(paramInt + 1)] = ((byte)localObject[i2].charAt(paramInt));
          }
          arrayOfByte[0] = 35;
          jdField_b_of_type_JavaUtilVector.addElement(arrayOfByte);
        }
        return;
      }
      break;
    case 84: 
      jdField_b_of_type_ArrayOfJavaLangString = n.a(jdField_c_of_type_ArrayOfJavaLangString[6], jdField_b_of_type_M, s - (r << 1), true);
      jdField_g_of_type_Boolean = true;
    }
  }
  
  private static void u()
  {
    Object localObject = n.a.f("on/down_empty");
    localObject = n.a((String)localObject, jdField_b_of_type_M, s - (r << 1), true);
    for (int i1 = 0; i1 < localObject.length; i1++) {
      jdField_d_of_type_JavaUtilVector.addElement(localObject[i1]);
    }
  }
  
  private static boolean a(int paramInt1, int paramInt2, int paramInt3, int paramInt4)
  {
    return ((paramInt1 = paramInt1) < i.bh) && (paramInt1 + paramInt3 > i.bh) && (paramInt2 < i.bi) && (paramInt2 + paramInt4 > i.bi);
  }
  
  static void v()
  {
    if (jdField_h_of_type_Boolean)
    {
      if (jdField_m_of_type_Int == 0) {
        try
        {
          j(null);
        }
        catch (Exception localException) {}
      }
      x += z;
      if (z > 0) {
        z -= 1;
      }
      if (z < 0) {
        z += 1;
      }
      if (z < -10) {
        z = -10;
      }
      if (z > 10) {
        z = 10;
      }
      int i1 = a(false);
      int i2 = a(false, 2);
      i2 = n - (jdField_l_of_type_Int + i2 << 1);
      i1 += jdField_l_of_type_Int;
      i1 = (i2 - jdField_l_of_type_Int - i1) / jdField_k_of_type_Int;
      i2 = x / jdField_k_of_type_Int;
      if (t - i2 > i1 >> 1) {
        z += 4;
      }
      if (t - i2 < i1 >> 1) {
        z -= 4;
      }
      jdField_a_of_type_Long += 1L;
      String str1;
      int i3;
      if (!jdField_a_of_type_JavaLangThread.isAlive())
      {
        int i9;
        switch (jdField_a_of_type_Char)
        {
        case 'M': 
          if (jdField_l_of_type_Byte == -1)
          {
            jdField_d_of_type_JavaUtilVector.removeAllElements();
            jdField_b_of_type_JavaUtilVector.removeAllElements();
            u();
            jdField_f_of_type_Boolean = false;
          }
          if (jdField_l_of_type_Byte == 1)
          {
            str1 = "";
            for (i2 = 0; i2 < jdField_d_of_type_ArrayOfByte.length; i2++) {
              str1 = str1 + a(jdField_d_of_type_ArrayOfByte[i2]);
            }
            jdField_e_of_type_JavaLangString = str1;
          }
          break;
        case 'U': 
          if (jdField_l_of_type_Byte == -1)
          {
            jdField_d_of_type_JavaUtilVector.removeAllElements();
            jdField_b_of_type_JavaUtilVector.removeAllElements();
            u();
            jdField_f_of_type_Boolean = false;
          }
          if (jdField_l_of_type_Byte == 1) {
            if (jdField_d_of_type_ArrayOfByte != null)
            {
              jdField_d_of_type_JavaUtilVector.removeAllElements();
              str1 = "";
              for (i2 = 0; i2 < jdField_d_of_type_ArrayOfByte.length; i2++) {
                str1 = str1 + a(jdField_d_of_type_ArrayOfByte[i2]);
              }
              String[] arrayOfString = n.a(str1, jdField_b_of_type_M, s - (r << 1), true);
              for (int i6 = 0; i6 < arrayOfString.length; i6++) {
                jdField_d_of_type_JavaUtilVector.addElement(arrayOfString[i6]);
              }
              if (jdField_a_of_type_JavaUtilVector.size() == 0)
              {
                int i8 = jdField_b_of_type_JavaUtilVector.size();
                for (i9 = 0; i9 < i8; i9++)
                {
                  str1 = "";
                  byte[] arrayOfByte1 = (byte[])jdField_b_of_type_JavaUtilVector.elementAt(i9);
                  for (int i4 = 0; i4 < arrayOfByte1.length; i4++)
                  {
                    if (arrayOfByte1[i4] == 45)
                    {
                      str1 = "#" + str1.substring(1, str1.length());
                      break;
                    }
                    str1 = str1 + a(arrayOfByte1[i4]);
                  }
                  jdField_d_of_type_JavaUtilVector.addElement(str1);
                }
              }
            }
          }
          break;
        case 'D': 
          if (jdField_l_of_type_Byte == -1)
          {
            jdField_d_of_type_JavaUtilVector.removeAllElements();
            jdField_b_of_type_JavaUtilVector.removeAllElements();
            u();
            jdField_f_of_type_Boolean = false;
          }
          if ((jdField_l_of_type_Byte == 1) && (jdField_d_of_type_ArrayOfByte != null))
          {
            i3 = 0;
            byte[] arrayOfByte2 = (byte[])jdField_b_of_type_JavaUtilVector.elementAt(t);
            String str2 = "";
            String str3 = "";
            for (i9 = 0; i9 < arrayOfByte2.length; i9++)
            {
              if (arrayOfByte2[(i9 + 1)] == 45) {
                break;
              }
              jdField_d_of_type_ArrayOfByte[i9] = arrayOfByte2[(i9 + 1)];
              if (i3 == 0) {
                str3 = str3 + (char)jdField_d_of_type_ArrayOfByte[i9];
              }
              if (arrayOfByte2[(i9 + 1)] == 46) {
                i3 = 1;
              }
              if (i3 == 0) {
                str2 = str2 + (char)arrayOfByte2[(i9 + 1)];
              } else if ((arrayOfByte2[(i9 + 1)] != 95) && (arrayOfByte2[(i9 + 1)] != 46)) {
                str3 = str3 + a(arrayOfByte2[(i9 + 1)]);
              }
            }
            i3 = Integer.parseInt(str2);
            i.m(0);
            int i5 = b();
            jdField_a_of_type_ArrayOfInt = a();
            switch (i5)
            {
            case 0: 
              jdField_h_of_type_Boolean = true;
              break;
            case 1: 
              a(jdField_d_of_type_ArrayOfByte, 20);
              u = i3;
              a.a(jdField_c_of_type_JavaUtilVector.size() - 1);
              jdField_h_of_type_Boolean = false;
              break;
            case 2: 
              g.e();
            }
          }
          break;
        }
        jdField_l_of_type_Byte = 0;
      }
      if ((jdField_a_of_type_JavaLangThread != null) && (!jdField_a_of_type_JavaLangThread.isAlive()) && (jdField_a_of_type_JavaUtilVector.size() > 0))
      {
        a((byte[])jdField_a_of_type_JavaUtilVector.elementAt(0), -1);
        jdField_a_of_type_JavaUtilVector.removeElementAt(0);
        if (jdField_a_of_type_JavaUtilVector.size() == 0)
        {
          jdField_b_of_type_Long = jdField_b_of_type_JavaUtilVector.size();
          for (i3 = 0; i3 < jdField_b_of_type_Long; i3++)
          {
            str1 = "";
            byte[] arrayOfByte3 = (byte[])jdField_b_of_type_JavaUtilVector.elementAt(i3);
            for (int i7 = 0; i7 < arrayOfByte3.length; i7++)
            {
              if (arrayOfByte3[i7] == 45)
              {
                str1 = "#" + str1.substring(1, str1.length());
                break;
              }
              str1 = str1 + a(arrayOfByte3[i7]);
            }
            jdField_d_of_type_JavaUtilVector.addElement(str1);
          }
        }
      }
    }
  }
  
  private static void w()
  {
    t = 0;
    jdField_d_of_type_JavaUtilVector.removeAllElements();
    jdField_f_of_type_JavaLangString = "";
    int i1 = jdField_f_of_type_JavaUtilVector.size();
    int i2 = 0;
    byte[] arrayOfByte1 = jdField_f_of_type_ArrayOfByte;
    int i3 = 0;
    int i6 = 0;
    int i7 = 0;
    int i4 = 0;
    int i8 = 0;
    int i10 = arrayOfByte1.length;
    Object localObject;
    int i9;
    if (i1 != 0)
    {
      byte[] arrayOfByte2 = (byte[])jdField_f_of_type_JavaUtilVector.elementAt(0);
      for (i5 = 0; i5 < arrayOfByte1.length; i5++)
      {
        if (((i4 = arrayOfByte1[i5]) == 64) && (i2 == i3))
        {
          i7 = 1;
          i6 = 0;
        }
        if (i7 != 0) {
          if (i4 == arrayOfByte2[i6])
          {
            i6++;
            if (arrayOfByte2.length == i6)
            {
              i2++;
              if (i2 == i1) {
                break;
              }
              arrayOfByte2 = (byte[])jdField_f_of_type_JavaUtilVector.elementAt(i2);
              i7 = 0;
            }
          }
          else
          {
            i7 = 0;
          }
        }
        if (i4 == 123) {
          i3++;
        }
        if (i4 == 125) {
          i3--;
        }
      }
      localObject = "";
      for (i4 = i9 = i5 + 2; i4 < arrayOfByte1.length; i4++)
      {
        if (arrayOfByte1[i4] == 125)
        {
          i10 = i4;
          break;
        }
        localObject = (String)localObject + (char)arrayOfByte1[i4];
      }
    }
    i3 = 0;
    for (int i5 = i9; i5 < i10; i5++)
    {
      if ((i4 = arrayOfByte1[i5]) == 123)
      {
        if (i3 == 0)
        {
          localObject = new byte[i5 - i9];
          System.arraycopy(arrayOfByte1, i9, localObject, 0, i5 - i9);
          jdField_e_of_type_JavaUtilVector.addElement(localObject);
          i9 = i5 + 1;
        }
        i3++;
      }
      if (i4 == 125)
      {
        i3--;
        if (i3 < 0) {
          break;
        }
      }
      if (i3 == 0) {
        switch (i4)
        {
        case 64: 
          i9 = i5;
          break;
        case 59: 
          localObject = new byte[i5 - i9];
          System.arraycopy(arrayOfByte1, i9, localObject, 0, i5 - i9);
          jdField_e_of_type_JavaUtilVector.addElement(localObject);
          i9 = i5 + 1;
        }
      }
    }
    jdField_b_of_type_JavaUtilVector.removeAllElements();
    jdField_a_of_type_JavaUtilVector.removeAllElements();
    for (i5 = 0; i5 < jdField_e_of_type_JavaUtilVector.size(); i5++)
    {
      byte[] arrayOfByte3;
      if ((arrayOfByte3 = (byte[])jdField_e_of_type_JavaUtilVector.elementAt(i5))[0] != 64) {
        jdField_a_of_type_JavaUtilVector.addElement(arrayOfByte3);
      } else {
        jdField_b_of_type_JavaUtilVector.addElement(arrayOfByte3);
      }
    }
    jdField_e_of_type_JavaUtilVector.removeAllElements();
  }
  
  private static byte[] a(byte[] paramArrayOfByte, int paramInt)
  {
    int i1 = paramArrayOfByte.length;
    int i2 = 105;
    while (paramInt < i1)
    {
      paramArrayOfByte[paramInt] = ((byte)(paramArrayOfByte[paramInt] ^ i2));
      i2 = (byte)(i2 + 1);
      paramInt++;
    }
    return paramArrayOfByte;
  }
  
  static void x()
  {
    jdField_c_of_type_ArrayOfJavaxMicroeditionLcduiImage = null;
    jdField_e_of_type_ArrayOfJavaxMicroeditionLcduiImage = null;
    jdField_d_of_type_ArrayOfJavaxMicroeditionLcduiImage = null;
    jdField_g_of_type_ArrayOfJavaxMicroeditionLcduiImage = null;
    jdField_f_of_type_ArrayOfJavaxMicroeditionLcduiImage = null;
  }
  
  private static void y()
  {
    if (jdField_m_of_type_Int == 0) {
      try
      {
        j(null);
      }
      catch (Exception localException) {}
    }
    int i1 = a(false);
    int i2 = a(false, 2);
    i2 = n - (jdField_l_of_type_Int + i2 << 1);
    i1 += jdField_l_of_type_Int;
    i1 = i2 - jdField_l_of_type_Int - i1;
    jdField_d_of_type_JavaUtilVector.size();
    i1 = jdField_d_of_type_JavaUtilVector.size() * jdField_k_of_type_Int - i1;
    z += 2;
    if (x > i1) {
      x = i1;
    }
    if (x < 0) {
      x = 0;
    }
  }
  
  static void h(Graphics paramGraphics)
  {
    if (jdField_l_of_type_Boolean)
    {
      localGraphics1 = paramGraphics;
      paramGraphics.setClip(0, 0, s, n);
      i3 = (i2 = jdField_b_of_type_M.i()) + (n >> 5);
      i5 = n - i3 * 3 >> 1;
      int[] arrayOfInt;
      i8 = Math.max(Math.max((arrayOfInt = new int[] { jdField_b_of_type_M.c(i.m[jdField_b_of_type_ArrayOfInt[0]]), jdField_b_of_type_M.c(i.m[jdField_b_of_type_ArrayOfInt[1]]), jdField_b_of_type_M.c(i.m[jdField_b_of_type_ArrayOfInt[2]]) })[0], arrayOfInt[1]), arrayOfInt[2]) + 7;
      i9 = i3 * 3 + 7;
      localGraphics1.setColor(0);
      localGraphics1.fillRect(s - i8 >> 1, n - i9 >> 1, i8, i9);
      localGraphics1.setColor(16777215);
      localGraphics1.drawRect(s - i8 >> 1, n - i9 >> 1, i8, i9);
      localGraphics1.setColor(11184810);
      i10 = arrayOfInt[jdField_j_of_type_Byte] + 3;
      localGraphics1.fillRect(s - i10 >> 1, i5 + i3 * jdField_j_of_type_Byte, i10 + 1, i3);
      i2 = i3 - i2 >> 1;
      for (i8 = 0; i8 < 3; i8++) {
        jdField_b_of_type_M.a(localGraphics1, i.m[jdField_b_of_type_ArrayOfInt[i8]], s - arrayOfInt[i8] >> 1, i5 + i3 * i8 + i2, 20);
      }
      return;
    }
    paramGraphics.setClip(0, 0, s, n);
    Graphics localGraphics1 = paramGraphics;
    int i2 = a(false);
    int i3 = b(jdField_e_of_type_Boolean, 2);
    int i5 = s / i3;
    if (s % i3 != 0) {
      i5++;
    }
    int i6 = (n - i2) / i3;
    if ((n - i2) % i3 != 0) {
      i6++;
    }
    for (int i8 = 0; i8 < i6; i8++) {
      for (i9 = 0; i9 < i5; i9++) {
        d(localGraphics1, 2, i9 * i3, i2 + i8 * i3);
      }
    }
    localGraphics1 = paramGraphics;
    i2 = b(jdField_e_of_type_Boolean, 3);
    i3 = b(false, 4);
    i5 = n / i3;
    for (i6 = 0; i6 < i5; i6++)
    {
      d(localGraphics1, 4, 0, i6 * i3);
      d(localGraphics1, 3, s - i2, i6 * i3);
    }
    int i10 = jdField_b_of_type_M.i();
    i2 = jdField_l_of_type_Int;
    a(jdField_e_of_type_Boolean);
    a(false);
    int i9 = 0;
    Object localObject = localGraphics1;
    if ((jdField_d_of_type_ArrayOfJavaxMicroeditionLcduiImage != null) && (jdField_d_of_type_ArrayOfJavaxMicroeditionLcduiImage[0] != null)) {
      ((Graphics)localObject).drawImage(jdField_d_of_type_ArrayOfJavaxMicroeditionLcduiImage[0], 0, 0, 20);
    }
    if ((jdField_b_of_type_JavaUtilVector.size() != 0) && (jdField_a_of_type_JavaLangThread != null) && (!jdField_a_of_type_JavaLangThread.isAlive()))
    {
      i8 = a(jdField_e_of_type_Boolean, 2);
      i9 = a(false, 2);
      localObject = null;
      if (jdField_b_of_type_JavaUtilVector.size() != 0) {
        localObject = (byte[])jdField_b_of_type_JavaUtilVector.elementAt(t);
      }
      if ((localObject != null) && (localObject[0] == 36))
      {
        c(localGraphics1, 10, r, n - (i2 + i9 >> 1) - (i9 >> 1));
        jdField_b_of_type_M.a(localGraphics1, jdField_c_of_type_ArrayOfJavaLangString[4], r + i8, n - (i2 + i9 >> 1) - (i10 >> 1), 20);
      }
      else
      {
        c(localGraphics1, 2, r, n - (i2 + i9 >> 1) - (i9 >> 1));
        jdField_b_of_type_M.a(localGraphics1, jdField_c_of_type_ArrayOfJavaLangString[0], r + i8, n - (i2 + i9 >> 1) - (i10 >> 1), 20);
      }
    }
    if (jdField_g_of_type_Boolean)
    {
      i8 = a(jdField_e_of_type_Boolean, 2);
      i9 = a(false, 2);
      if ((jdField_g_of_type_JavaLangString != null) && (jdField_g_of_type_JavaLangString.length() > 9))
      {
        c(localGraphics1, 2, r, n - (i2 + i9 >> 1) - (i9 >> 1));
        jdField_b_of_type_M.a(localGraphics1, jdField_c_of_type_ArrayOfJavaLangString[5], r + i8, n - (i2 + i9 >> 1) - (i10 >> 1), 20);
      }
      i4 = a(false);
      i5 = jdField_b_of_type_ArrayOfJavaLangString.length;
      for (i6 = 0; i6 < i5; i6++) {
        jdField_b_of_type_M.a(localGraphics1, jdField_b_of_type_ArrayOfJavaLangString[i6], 240 - jdField_b_of_type_M.c(jdField_b_of_type_ArrayOfJavaLangString[i6]) >> 1, i4 + jdField_b_of_type_M.i() * i6 + 1, 20);
      }
    }
    if ((jdField_a_of_type_JavaLangThread != null) && (!jdField_a_of_type_JavaLangThread.isAlive()))
    {
      i8 = a(jdField_e_of_type_Boolean, 0);
      i9 = a(false, 0);
      c(localGraphics1, 0, s - i8 - r, n - (i2 + i9 >> 1) - (i9 >> 1));
      jdField_b_of_type_M.a(localGraphics1, jdField_c_of_type_ArrayOfJavaLangString[1], s - jdField_b_of_type_M.c(jdField_c_of_type_ArrayOfJavaLangString[1]) - r - i8, n - (i2 + i9 >> 1) - (i10 >> 1), 20);
    }
    else
    {
      i8 = a(jdField_e_of_type_Boolean, 3);
      i9 = a(false, 3);
      c(localGraphics1, 3, s - i8 - r, n - (i2 + i9 >> 1) - (i9 >> 1));
      jdField_b_of_type_M.a(localGraphics1, jdField_c_of_type_ArrayOfJavaLangString[2], s - jdField_b_of_type_M.c(jdField_c_of_type_ArrayOfJavaLangString[2]) - r - i8, n - (i2 + i9 >> 1) - (i10 >> 1), 20);
    }
    localGraphics1.setColor(6589339);
    localGraphics1.fillRect(0, n - (i2 + i9), s, 1);
    localGraphics1.setColor(3101537);
    localGraphics1.fillRect(0, n - (i2 + i9) - 1, s, 1);
    int i4 = (int)(jdField_c_of_type_Long >> 10);
    i5 = (int)(jdField_c_of_type_Long & 0x3FF) * 100 >> 10;
    String str = jdField_c_of_type_ArrayOfJavaLangString[3] + " " + i4 + "." + (i5 > 9 ? String.valueOf(i5) : new StringBuffer("0").append(i5).toString()) + " kb";
    i8 = jdField_b_of_type_M.c(str);
    i4 = n - (i2 + i9) - (i2 + i9 + i10 >> 1);
    jdField_b_of_type_M.a(localGraphics1, str, s - i8 - r, i4, 20);
    localGraphics1.setColor(6589339);
    localGraphics1.fillRect(0, n - (i2 + i9 << 1), s, 1);
    localGraphics1.setColor(3101537);
    localGraphics1.fillRect(0, n - (i2 + i9 << 1) - 1, s, 1);
    if ((jdField_a_of_type_JavaLangThread != null) && (jdField_a_of_type_JavaLangThread.isAlive()))
    {
      int i7 = n - (i2 + i9) - (i2 + i9 + a() >> 1);
      i5 = s - i8 - r - a();
      Graphics localGraphics2 = localGraphics1;
      int i1 = (int)(jdField_a_of_type_Long & 0x7);
      i2 = jdField_f_of_type_ArrayOfJavaxMicroeditionLcduiImage[0].getHeight();
      localGraphics2.setClip(i5 - i2, i7, i2, i2);
      localGraphics2.drawImage(jdField_f_of_type_ArrayOfJavaxMicroeditionLcduiImage[0], i5 - i1 * i2 - i2, i7, 20);
      localGraphics2.setClip(0, 0, s, n);
    }
    j(paramGraphics);
    if (jdField_g_of_type_Boolean) {
      i(paramGraphics);
    }
  }
  
  private static void c(Graphics paramGraphics, int paramInt1, int paramInt2, int paramInt3)
  {
    if (jdField_e_of_type_ArrayOfJavaxMicroeditionLcduiImage == null) {
      return;
    }
    if (jdField_e_of_type_ArrayOfJavaxMicroeditionLcduiImage[paramInt1] == null) {
      return;
    }
    paramGraphics.drawImage(jdField_e_of_type_ArrayOfJavaxMicroeditionLcduiImage[paramInt1], paramInt2, paramInt3, 20);
  }
  
  private static void d(Graphics paramGraphics, int paramInt1, int paramInt2, int paramInt3)
  {
    if (jdField_g_of_type_ArrayOfJavaxMicroeditionLcduiImage == null) {
      return;
    }
    if (jdField_g_of_type_ArrayOfJavaxMicroeditionLcduiImage[paramInt1] == null) {
      return;
    }
    paramGraphics.setClip(0, 0, s, n);
    paramGraphics.drawImage(jdField_g_of_type_ArrayOfJavaxMicroeditionLcduiImage[paramInt1], paramInt2, paramInt3, 20);
  }
  
  /* Error */
  private static void i(Graphics arg0)
  {
    // Byte code:
    //   0: aload_0
    //   1: iconst_0
    //   2: iconst_0
    //   3: getstatic 151	b:s	I
    //   6: getstatic 146	b:n	I
    //   9: invokevirtual 249	javax/microedition/lcdui/Graphics:setClip	(IIII)V
    //   12: getstatic 118	b:jdField_e_of_type_Boolean	Z
    //   15: bipush 6
    //   17: invokestatic 195	b:b	(ZI)I
    //   20: istore_1
    //   21: iconst_0
    //   22: bipush 6
    //   24: invokestatic 195	b:b	(ZI)I
    //   27: istore_2
    //   28: getstatic 146	b:n	I
    //   31: getstatic 142	b:jdField_l_of_type_Int	I
    //   34: iconst_0
    //   35: iconst_3
    //   36: invokestatic 190	b:a	(ZI)I
    //   39: iadd
    //   40: iconst_1
    //   41: ishl
    //   42: isub
    //   43: istore_3
    //   44: getstatic 151	b:s	I
    //   47: iload_1
    //   48: iconst_3
    //   49: imul
    //   50: isub
    //   51: iconst_1
    //   52: ishr
    //   53: istore 4
    //   55: iload_3
    //   56: iload_2
    //   57: iconst_2
    //   58: ishl
    //   59: isub
    //   60: iload_2
    //   61: isub
    //   62: istore_3
    //   63: iconst_0
    //   64: istore 5
    //   66: iconst_0
    //   67: istore 7
    //   69: goto +252 -> 321
    //   72: iconst_0
    //   73: istore 8
    //   75: goto +237 -> 312
    //   78: aload_0
    //   79: bipush 6
    //   81: iload 4
    //   83: iload 8
    //   85: iload_1
    //   86: imul
    //   87: iadd
    //   88: iload_3
    //   89: iload 7
    //   91: iload_2
    //   92: imul
    //   93: iadd
    //   94: invokestatic 199	b:d	(Ljavax/microedition/lcdui/Graphics;III)V
    //   97: iload 5
    //   99: iconst_1
    //   100: iadd
    //   101: dup
    //   102: istore 6
    //   104: bipush 9
    //   106: if_icmplt +47 -> 153
    //   109: iload 6
    //   111: tableswitch	default:+42->153, 10:+31->142, 11:+25->136, 12:+38->149
    //   136: iconst_0
    //   137: istore 6
    //   139: goto +14 -> 153
    //   142: bipush 11
    //   144: istore 6
    //   146: goto +7 -> 153
    //   149: bipush 10
    //   151: istore 6
    //   153: aload_0
    //   154: iload 6
    //   156: iload 4
    //   158: iload 8
    //   160: iload_1
    //   161: imul
    //   162: iadd
    //   163: iload_1
    //   164: iconst_1
    //   165: ishr
    //   166: iadd
    //   167: getstatic 119	b:jdField_e_of_type_ArrayOfByte	[B
    //   170: iload 6
    //   172: bipush 7
    //   174: imul
    //   175: iconst_2
    //   176: iadd
    //   177: baload
    //   178: iconst_1
    //   179: ishr
    //   180: isub
    //   181: iload_3
    //   182: iload 7
    //   184: iload_2
    //   185: imul
    //   186: iadd
    //   187: iload_2
    //   188: iconst_1
    //   189: ishr
    //   190: iadd
    //   191: getstatic 119	b:jdField_e_of_type_ArrayOfByte	[B
    //   194: iload 6
    //   196: bipush 7
    //   198: imul
    //   199: iconst_3
    //   200: iadd
    //   201: baload
    //   202: iconst_1
    //   203: ishr
    //   204: isub
    //   205: istore 11
    //   207: istore 10
    //   209: istore 9
    //   211: astore 6
    //   213: getstatic 128	b:jdField_g_of_type_ArrayOfJavaxMicroeditionLcduiImage	[Ljavax/microedition/lcdui/Image;
    //   216: iconst_5
    //   217: aaload
    //   218: astore 12
    //   220: getstatic 119	b:jdField_e_of_type_ArrayOfByte	[B
    //   223: astore 13
    //   225: iload 9
    //   227: bipush 7
    //   229: imul
    //   230: istore 9
    //   232: iload 10
    //   234: aload 13
    //   236: iload 9
    //   238: iconst_4
    //   239: iadd
    //   240: baload
    //   241: iadd
    //   242: istore 10
    //   244: iload 11
    //   246: aload 13
    //   248: iload 9
    //   250: iconst_5
    //   251: iadd
    //   252: baload
    //   253: iadd
    //   254: istore 11
    //   256: aload 6
    //   258: iload 10
    //   260: iload 11
    //   262: aload 13
    //   264: iload 9
    //   266: iconst_2
    //   267: iadd
    //   268: baload
    //   269: aload 13
    //   271: iload 9
    //   273: iconst_3
    //   274: iadd
    //   275: baload
    //   276: invokevirtual 249	javax/microedition/lcdui/Graphics:setClip	(IIII)V
    //   279: aload 6
    //   281: aload 12
    //   283: iload 10
    //   285: aload 13
    //   287: iload 9
    //   289: baload
    //   290: isub
    //   291: iload 11
    //   293: aload 13
    //   295: iload 9
    //   297: iconst_1
    //   298: iadd
    //   299: baload
    //   300: isub
    //   301: bipush 20
    //   303: invokevirtual 242	javax/microedition/lcdui/Graphics:drawImage	(Ljavax/microedition/lcdui/Image;III)V
    //   306: iinc 5 1
    //   309: iinc 8 1
    //   312: iload 8
    //   314: iconst_3
    //   315: if_icmplt -237 -> 78
    //   318: iinc 7 1
    //   321: iload 7
    //   323: iconst_4
    //   324: if_icmplt -252 -> 72
    //   327: aload_0
    //   328: iconst_0
    //   329: iconst_0
    //   330: getstatic 151	b:s	I
    //   333: getstatic 146	b:n	I
    //   336: invokevirtual 249	javax/microedition/lcdui/Graphics:setClip	(IIII)V
    //   339: aload_0
    //   340: ldc 5
    //   342: invokevirtual 250	javax/microedition/lcdui/Graphics:setColor	(I)V
    //   345: getstatic 119	b:jdField_e_of_type_ArrayOfByte	[B
    //   348: iconst_3
    //   349: baload
    //   350: getstatic 119	b:jdField_e_of_type_ArrayOfByte	[B
    //   353: iconst_3
    //   354: baload
    //   355: iconst_1
    //   356: ishr
    //   357: iadd
    //   358: istore 8
    //   360: aload_0
    //   361: iconst_0
    //   362: iload_3
    //   363: getstatic 119	b:jdField_e_of_type_ArrayOfByte	[B
    //   366: iconst_3
    //   367: baload
    //   368: isub
    //   369: getstatic 119	b:jdField_e_of_type_ArrayOfByte	[B
    //   372: iconst_3
    //   373: baload
    //   374: iconst_1
    //   375: ishr
    //   376: isub
    //   377: iload 8
    //   379: iconst_1
    //   380: ishr
    //   381: isub
    //   382: getstatic 151	b:s	I
    //   385: iload 8
    //   387: invokevirtual 244	javax/microedition/lcdui/Graphics:fillRect	(IIII)V
    //   390: aload_0
    //   391: ldc 6
    //   393: invokevirtual 250	javax/microedition/lcdui/Graphics:setColor	(I)V
    //   396: aload_0
    //   397: iconst_0
    //   398: iload_3
    //   399: getstatic 119	b:jdField_e_of_type_ArrayOfByte	[B
    //   402: iconst_3
    //   403: baload
    //   404: isub
    //   405: getstatic 119	b:jdField_e_of_type_ArrayOfByte	[B
    //   408: iconst_3
    //   409: baload
    //   410: iconst_1
    //   411: ishr
    //   412: isub
    //   413: iload 8
    //   415: iconst_1
    //   416: ishr
    //   417: isub
    //   418: getstatic 151	b:s	I
    //   421: iload 8
    //   423: invokevirtual 243	javax/microedition/lcdui/Graphics:drawRect	(IIII)V
    //   426: getstatic 126	b:jdField_g_of_type_JavaLangString	Ljava/lang/String;
    //   429: ifnull +233 -> 662
    //   432: aload_0
    //   433: getstatic 126	b:jdField_g_of_type_JavaLangString	Ljava/lang/String;
    //   436: getstatic 151	b:s	I
    //   439: getstatic 126	b:jdField_g_of_type_JavaLangString	Ljava/lang/String;
    //   442: dup
    //   443: astore 6
    //   445: invokevirtual 219	java/lang/String:length	()I
    //   448: ifne +7 -> 455
    //   451: iconst_0
    //   452: goto +59 -> 511
    //   455: aload 6
    //   457: invokevirtual 219	java/lang/String:length	()I
    //   460: istore 9
    //   462: iconst_0
    //   463: istore 10
    //   465: getstatic 119	b:jdField_e_of_type_ArrayOfByte	[B
    //   468: astore 11
    //   470: iconst_0
    //   471: istore 12
    //   473: goto +29 -> 502
    //   476: iload 10
    //   478: aload 11
    //   480: aload 6
    //   482: iload 12
    //   484: invokevirtual 216	java/lang/String:charAt	(I)C
    //   487: bipush 48
    //   489: isub
    //   490: bipush 7
    //   492: imul
    //   493: iconst_2
    //   494: iadd
    //   495: baload
    //   496: iadd
    //   497: istore 10
    //   499: iinc 12 1
    //   502: iload 12
    //   504: iload 9
    //   506: if_icmplt -30 -> 476
    //   509: iload 10
    //   511: isub
    //   512: iconst_1
    //   513: ishr
    //   514: iload_3
    //   515: getstatic 119	b:jdField_e_of_type_ArrayOfByte	[B
    //   518: iconst_3
    //   519: baload
    //   520: iconst_1
    //   521: ishl
    //   522: isub
    //   523: istore 11
    //   525: istore 10
    //   527: astore 9
    //   529: astore 6
    //   531: getstatic 128	b:jdField_g_of_type_ArrayOfJavaxMicroeditionLcduiImage	[Ljavax/microedition/lcdui/Image;
    //   534: pop
    //   535: getstatic 119	b:jdField_e_of_type_ArrayOfByte	[B
    //   538: astore 13
    //   540: aload 9
    //   542: ifnull +120 -> 662
    //   545: aload 9
    //   547: invokevirtual 219	java/lang/String:length	()I
    //   550: istore_0
    //   551: iconst_0
    //   552: istore 4
    //   554: goto +102 -> 656
    //   557: aload 9
    //   559: iload 4
    //   561: invokevirtual 216	java/lang/String:charAt	(I)C
    //   564: bipush 48
    //   566: isub
    //   567: bipush 7
    //   569: imul
    //   570: istore_1
    //   571: iload 10
    //   573: aload 13
    //   575: iload_1
    //   576: iconst_4
    //   577: iadd
    //   578: baload
    //   579: iadd
    //   580: istore_2
    //   581: iload 11
    //   583: aload 13
    //   585: iload_1
    //   586: iconst_5
    //   587: iadd
    //   588: baload
    //   589: iadd
    //   590: istore_3
    //   591: aload 6
    //   593: iload_2
    //   594: iload_3
    //   595: aload 13
    //   597: iload_1
    //   598: iconst_2
    //   599: iadd
    //   600: baload
    //   601: aload 13
    //   603: iload_1
    //   604: iconst_3
    //   605: iadd
    //   606: baload
    //   607: invokevirtual 249	javax/microedition/lcdui/Graphics:setClip	(IIII)V
    //   610: aload 6
    //   612: getstatic 128	b:jdField_g_of_type_ArrayOfJavaxMicroeditionLcduiImage	[Ljavax/microedition/lcdui/Image;
    //   615: aload 13
    //   617: iload_1
    //   618: bipush 6
    //   620: iadd
    //   621: baload
    //   622: aaload
    //   623: iload_2
    //   624: aload 13
    //   626: iload_1
    //   627: baload
    //   628: isub
    //   629: iload_3
    //   630: aload 13
    //   632: iload_1
    //   633: iconst_1
    //   634: iadd
    //   635: baload
    //   636: isub
    //   637: bipush 20
    //   639: invokevirtual 242	javax/microedition/lcdui/Graphics:drawImage	(Ljavax/microedition/lcdui/Image;III)V
    //   642: iload 10
    //   644: aload 13
    //   646: iload_1
    //   647: iconst_2
    //   648: iadd
    //   649: baload
    //   650: iadd
    //   651: istore 10
    //   653: iinc 4 1
    //   656: iload 4
    //   658: iload_0
    //   659: if_icmplt -102 -> 557
    //   662: return
  }
  
  static void z()
  {
    jdField_h_of_type_Boolean = true;
    jdField_m_of_type_Boolean = true;
    if ((!jdField_k_of_type_Boolean) && ((jdField_f_of_type_ArrayOfByte = a(jdField_j_of_type_JavaLangString)) != null))
    {
      a(jdField_f_of_type_ArrayOfByte, 0);
      byte[] arrayOfByte2 = new byte[(arrayOfByte1 = jdField_f_of_type_ArrayOfByte).length];
      int i1 = 0;
      int i2 = arrayOfByte1.length;
      int i3 = 0;
      for (int i5 = 0; i5 < i2; i5++)
      {
        if (arrayOfByte1[i5] == 39) {
          i1 ^= 0x1;
        }
        if ((arrayOfByte1[i5] == 32) && (i1 == 1))
        {
          arrayOfByte2[i3] = arrayOfByte1[i5];
          i3++;
        }
        else
        {
          int i4;
          if (((i4 = arrayOfByte1[i5]) != 13) && (i4 != 10) && (i4 != 32) && (i4 != 9))
          {
            arrayOfByte2[i3] = arrayOfByte1[i5];
            i3++;
          }
        }
      }
      byte[] arrayOfByte1 = new byte[i3];
      System.arraycopy(arrayOfByte2, 0, arrayOfByte1, 0, i3);
      jdField_f_of_type_ArrayOfByte = arrayOfByte1;
      w();
      jdField_k_of_type_Boolean = true;
    }
    jdField_m_of_type_Boolean = false;
    if (!jdField_f_of_type_Boolean)
    {
      w();
      jdField_f_of_type_Boolean = true;
    }
  }
  
  /* Error */
  private static byte[] a(String paramString)
  {
    // Byte code:
    //   0: aconst_null
    //   1: astore_1
    //   2: aconst_null
    //   3: astore_2
    //   4: aconst_null
    //   5: astore 5
    //   7: aload_0
    //   8: iconst_3
    //   9: iconst_1
    //   10: invokestatic 241	javax/microedition/io/Connector:open	(Ljava/lang/String;IZ)Ljavax/microedition/io/Connection;
    //   13: checkcast 69	javax/microedition/io/HttpConnection
    //   16: dup
    //   17: astore_1
    //   18: ldc 23
    //   20: invokeinterface 274 2 0
    //   25: aload_1
    //   26: invokeinterface 273 1 0
    //   31: astore_2
    //   32: aload_1
    //   33: invokeinterface 272 1 0
    //   38: dup2
    //   39: lstore_3
    //   40: lconst_0
    //   41: lcmp
    //   42: ifle +16 -> 58
    //   45: lload_3
    //   46: l2i
    //   47: newarray <illegal type>
    //   49: astore 5
    //   51: aload_2
    //   52: aload 5
    //   54: invokevirtual 211	java/io/InputStream:read	([B)I
    //   57: pop
    //   58: aload_2
    //   59: invokevirtual 209	java/io/InputStream:close	()V
    //   62: aload_1
    //   63: invokeinterface 271 1 0
    //   68: goto +45 -> 113
    //   71: pop
    //   72: goto +41 -> 113
    //   75: pop
    //   76: aconst_null
    //   77: astore 5
    //   79: aload_2
    //   80: invokevirtual 209	java/io/InputStream:close	()V
    //   83: aload_1
    //   84: invokeinterface 271 1 0
    //   89: goto +24 -> 113
    //   92: pop
    //   93: goto +20 -> 113
    //   96: astore_0
    //   97: aload_2
    //   98: invokevirtual 209	java/io/InputStream:close	()V
    //   101: aload_1
    //   102: invokeinterface 271 1 0
    //   107: goto +4 -> 111
    //   110: pop
    //   111: aload_0
    //   112: athrow
    //   113: aload 5
    //   115: areturn
    // Local variable table:
    //   start	length	slot	name	signature
    //   0	116	0	paramString	String
    //   1	101	1	localHttpConnection	HttpConnection
    //   3	95	2	localInputStream	InputStream
    //   39	7	3	l1	long
    //   5	109	5	arrayOfByte	byte[]
    //   71	1	5	localException1	Exception
    //   75	1	6	localException2	Exception
    //   92	1	7	localException3	Exception
    //   110	1	8	localException4	Exception
    // Exception table:
    //   from	to	target	type
    //   58	68	71	java/lang/Exception
    //   7	58	75	java/lang/Exception
    //   79	89	92	java/lang/Exception
    //   7	58	96	finally
    //   97	107	110	java/lang/Exception
  }
  
  private static String[] a()
  {
    String[] arrayOfString = null;
    Object localObject1 = jdField_b_of_type_JavaLangString = "level";
    int i2;
    try
    {
      RecordStore localRecordStore1;
      localObject2 = (localRecordStore1 = RecordStore.openRecordStore((String)localObject1, false)).getRecord(1);
      long l1 = localRecordStore1.getLastModified() / 1000L;
      long l2 = (localObject2[0] & 0xFF) << 56 | (localObject2[1] & 0xFF) << 48 | (localObject2[2] & 0xFF) << 40 | (localObject2[3] & 0xFF) << 32 | (localObject2[4] & 0xFF) << 24 | (localObject2[5] & 0xFF) << 16 | (localObject2[6] & 0xFF) << 8 | localObject2[7] & 0xFF;
      i2 = localObject2.length - 8;
      String str1 = "";
      if (i2 != 0) {
        for (int i4 = 0; i4 < i2; i4++) {
          str1 = str1 + (char)localObject2[(i4 + 8)];
        }
      }
      if (!NET_Lizard.g("microedition.platform").equals(str1)) {
        i.ae = false;
      }
      if (Math.abs(l1 - l2) > 3L) {
        i.ae = false;
      }
      localRecordStore1.closeRecordStore();
    }
    catch (Exception localException1)
    {
      try
      {
        Object localObject2 = RecordStore.openRecordStore((String)localObject1, true);
        String str2 = NET_Lizard.g("microedition.platform");
        byte[] arrayOfByte = new byte[8 + str2.length()];
        ((RecordStore)localObject2).addRecord(arrayOfByte, 0, arrayOfByte.length);
        a((RecordStore)localObject2);
        ((RecordStore)localObject2).closeRecordStore();
      }
      catch (Exception localException2) {}
    }
    if (jdField_b_of_type_JavaLangString.length() == 0) {
      return null;
    }
    try
    {
      RecordStore localRecordStore2;
      int i1;
      arrayOfString = new String[i1 = (localRecordStore2 = RecordStore.openRecordStore(jdField_b_of_type_JavaLangString, true)).getNumRecords() - A];
      for (i2 = 0; i2 < i1; i2++)
      {
        localRecordStore2.getRecordSize(i2 + 1 + A);
        localObject1 = new byte[localRecordStore2.getRecordSize(i2 + 1 + A)];
        localRecordStore2.getRecord(i2 + 1 + A, (byte[])localObject1, 0);
        arrayOfString[i2] = "";
        for (int i3 = 0; i3 < 20; i3++)
        {
          if (localObject1[i3] == 0) {
            break;
          }
          int tmp390_388 = i2;
          arrayOfString[tmp390_388] = (arrayOfString[tmp390_388] + a(localObject1[i3]));
        }
      }
      localRecordStore2.closeRecordStore();
    }
    catch (Exception localException3) {}
    return arrayOfString;
  }
  
  private static char a(int paramInt)
  {
    if (paramInt < 0) {
      paramInt += 256;
    }
    if (paramInt >= 192) {
      paramInt += 848;
    }
    return (char)paramInt;
  }
  
  private static byte[] a(String paramString, int paramInt)
  {
    Object localObject = "";
    if (paramInt <= 999) {
      if (paramInt > 99) {
        localObject = (String)localObject + "0";
      } else if (paramInt > 9) {
        localObject = (String)localObject + "00";
      } else {
        localObject = (String)localObject + "000";
      }
    }
    try
    {
      localObject = (paramInt = RecordStore.openRecordStore(jdField_d_of_type_JavaLangString + (String)localObject + paramInt, false)).getRecord(1);
      paramInt.closeRecordStore();
      paramInt = 0;
      int i1 = paramString.length();
      for (int i2 = 0; i2 < localObject.length; i2++)
      {
        localObject[i2] = ((byte)(localObject[i2] ^ (byte)paramString.charAt(paramInt)));
        paramInt++;
        if (paramInt >= i1) {
          paramInt = 0;
        }
      }
      return (byte[])localObject;
    }
    catch (Exception localException) {}
    return null;
  }
  
  static byte[] a()
  {
    return jdField_d_of_type_ArrayOfByte;
  }
  
  static byte[] a(int paramInt)
  {
    return b(paramInt);
  }
  
  private static String a()
  {
    String str = "";
    Object localObject = null;
    try
    {
      if ((localObject = NET_Lizard.g("phone.imei")) != null) {
        str = str + (String)localObject;
      }
    }
    catch (Exception localException1) {}
    if (localObject == null) {
      try
      {
        if ((localObject = NET_Lizard.g("com.nokia.IMEI")) != null) {
          str = str + (String)localObject;
        }
      }
      catch (Exception localException2) {}
    }
    if (localObject == null) {
      try
      {
        if ((localObject = NET_Lizard.g("com.sonyericsson.imei")) != null) {
          str = str + (String)localObject;
        }
      }
      catch (Exception localException3) {}
    }
    if (localObject == null) {
      try
      {
        if ((localObject = NET_Lizard.g("IMEI")) != null) {
          str = str + (String)localObject;
        }
      }
      catch (Exception localException4) {}
    }
    if (localObject == null) {
      try
      {
        if ((localObject = NET_Lizard.g("com.motorola.IMEI")) != null) {
          str = str + (String)localObject;
        }
      }
      catch (Exception localException5) {}
    }
    if (localObject == null) {
      try
      {
        if ((localObject = NET_Lizard.g("com.samsung.imei")) != null) {
          str = str + (String)localObject;
        }
      }
      catch (Exception localException6) {}
    }
    if (localObject == null) {
      try
      {
        if ((localObject = NET_Lizard.g("com.siemens.imei")) != null) {
          str = str + (String)localObject;
        }
      }
      catch (Exception localException7) {}
    }
    if ((str == null) || (str.length() <= 0)) {
      str = "null";
    }
    if (str != null)
    {
      localObject = str.getBytes();
      str = "";
      for (int i1 = 0; i1 < localObject.length; i1++)
      {
        if (localObject[i1] == 32) {
          localObject[i1] = 95;
        }
        str = str + (char)localObject[i1];
      }
    }
    return str;
  }
  
  static byte[] b(int paramInt)
  {
    try
    {
      RecordStore localRecordStore;
      int i2 = (localRecordStore = RecordStore.openRecordStore(jdField_c_of_type_JavaLangString, false)).getRecord(2)[0] & 0xFF;
      byte[] arrayOfByte;
      int i1 = ((arrayOfByte = localRecordStore.getRecord(3))[0] & 0xFF) << 8 | arrayOfByte[1] & 0xFF;
      String str = NET_Lizard.g("microedition.platform");
      byte[][] arrayOfByte1 = new byte[i1][];
      for (int i4 = 0; i4 < i1; i4++)
      {
        int i3 = 4 + i4 * 6;
        arrayOfByte1[i4] = localRecordStore.getRecord(i3 + 3);
        if ((arrayOfByte1[i4][0] & 0xFF000000 | arrayOfByte1[i4][1] & 0xFF0000 | arrayOfByte1[i4][2] & 0xFF00 | arrayOfByte1[i4][3] & 0xFF) == paramInt)
        {
          localRecordStore.closeRecordStore();
          return a(str + i2, paramInt);
        }
      }
      localRecordStore.closeRecordStore();
    }
    catch (Exception localException) {}
    return null;
  }
  
  static int[] a()
  {
    try
    {
      RecordStore localRecordStore;
      byte[] arrayOfByte;
      int i1 = ((arrayOfByte = (localRecordStore = RecordStore.openRecordStore(jdField_c_of_type_JavaLangString, false)).getRecord(3))[0] & 0xFF) << 8 | arrayOfByte[1] & 0xFF;
      NET_Lizard.g("microedition.platform");
      byte[][] arrayOfByte1 = new byte[i1][];
      int[] arrayOfInt = new int[i1];
      for (int i3 = 0; i3 < i1; i3++)
      {
        int i2 = 4 + i3 * 6;
        arrayOfByte1[i3] = localRecordStore.getRecord(i2 + 3);
        i2 = arrayOfByte1[i3][0] & 0xFF000000 | arrayOfByte1[i3][1] & 0xFF0000 | arrayOfByte1[i3][2] & 0xFF00 | arrayOfByte1[i3][3] & 0xFF;
        arrayOfInt[i3] = i2;
      }
      localRecordStore.closeRecordStore();
      return arrayOfInt;
    }
    catch (Exception localException) {}
    return null;
  }
  
  static String[] b()
  {
    try
    {
      RecordStore localRecordStore;
      byte[] arrayOfByte;
      int i1 = ((arrayOfByte = (localRecordStore = RecordStore.openRecordStore(jdField_c_of_type_JavaLangString, false)).getRecord(3))[0] & 0xFF) << 8 | arrayOfByte[1] & 0xFF;
      NET_Lizard.g("microedition.platform");
      byte[][] arrayOfByte1 = new byte[i1][];
      String[] arrayOfString = new String[i1];
      for (int i3 = 0; i3 < i1; i3++)
      {
        int i2 = 4 + i3 * 6;
        arrayOfByte1[i3] = localRecordStore.getRecord(i2 + 1);
        arrayOfString[i3] = "";
        for (i2 = 0; i2 < arrayOfByte1[i3].length; i2++)
        {
          int tmp98_96 = i3;
          String[] tmp98_94 = arrayOfString;
          tmp98_94[tmp98_96] = (tmp98_94[tmp98_96] + a(arrayOfByte1[i3][i2]));
        }
      }
      localRecordStore.closeRecordStore();
      return arrayOfString;
    }
    catch (Exception localException) {}
    return null;
  }
  
  private static void j(Graphics paramGraphics)
  {
    int i1 = jdField_l_of_type_Int >> 1;
    jdField_k_of_type_Int = (jdField_m_of_type_Int = jdField_b_of_type_M.i() - jdField_b_of_type_M.cb) + i1 + 1;
    if (s >= 240) {
      jdField_k_of_type_Int += 2;
    }
    if (i.aR) {
      jdField_k_of_type_Int += 5;
    }
    i1 = paramGraphics.getClipX();
    int i2 = paramGraphics.getClipY();
    int i3 = paramGraphics.getClipWidth();
    int i4 = paramGraphics.getClipHeight();
    int i5 = a(false);
    a(false, 2);
    int i6 = n - (jdField_l_of_type_Int + a(false, 0) << 1);
    int i7 = i5 + jdField_l_of_type_Int;
    int i8;
    int i9 = (i8 = i6 - jdField_l_of_type_Int - i7) / jdField_k_of_type_Int;
    int i10 = jdField_k_of_type_Int - (jdField_b_of_type_M.i() - jdField_b_of_type_M.cb) >> 1;
    paramGraphics.setClip(0, i7, s, i8 + 1);
    int i11 = jdField_d_of_type_JavaUtilVector.size();
    int i12 = jdField_d_of_type_JavaUtilVector.size() * jdField_k_of_type_Int - i8;
    if (i11 > i9) {
      i11 = i9;
    }
    if (x > i12) {
      x = i12;
    }
    if (x < 0) {
      x = 0;
    }
    i7 -= x;
    int i13;
    int i14;
    if ((i14 = (i13 = x / jdField_k_of_type_Int) + i9) > jdField_d_of_type_JavaUtilVector.size()) {
      i14 = jdField_d_of_type_JavaUtilVector.size();
    }
    if (i13 < 0) {
      i13 = 0;
    }
    int i15 = jdField_d_of_type_JavaUtilVector.size() - jdField_b_of_type_JavaUtilVector.size();
    if (i11 == i9) {
      i14++;
    }
    int i16 = -1;
    int i18;
    int i19;
    int i20;
    for (int i17 = i13; i17 <= i14; i17++)
    {
      String str;
      if ((i17 >= jdField_d_of_type_JavaUtilVector.size()) || ((str = (String)jdField_d_of_type_JavaUtilVector.elementAt(i17)).length() == 0)) {
        break;
      }
      if ((str.charAt(0) == '@') || (str.charAt(0) == '#') || (str.charAt(0) == '$')) {
        i16++;
      } else {
        i15--;
      }
      if ((i16 >= 0) && (i16 + i13 - i15 == t))
      {
        paramGraphics.setColor(6853025);
        paramGraphics.fillRect(0, i7 + jdField_k_of_type_Int * i17, s, jdField_k_of_type_Int);
        B = i7 + jdField_k_of_type_Int * i17;
        o = jdField_k_of_type_Int;
      }
      i18 = r;
      if (str.charAt(0) == '@')
      {
        c(paramGraphics, 4, i18, i7 + jdField_k_of_type_Int * i17 + (jdField_k_of_type_Int - a(false, 4) >> 1));
        i18 += a(true, 4);
        str = str.substring(1, str.length());
      }
      if (str.charAt(0) == '#')
      {
        i19 = 6;
        if (jdField_a_of_type_ArrayOfInt != null) {
          for (i20 = 0; i20 < jdField_a_of_type_ArrayOfInt.length; i20++) {
            if (i16 + i.aL == jdField_a_of_type_ArrayOfInt[i20])
            {
              i19 = 2;
              break;
            }
          }
        }
        c(paramGraphics, i19, i18, i7 + jdField_k_of_type_Int * i17 + (jdField_k_of_type_Int - a(false, i19) >> 1));
        i18 += a(true, i19);
        str = str.substring(1, str.length());
      }
      if (str.charAt(0) == '$')
      {
        c(paramGraphics, 10, i18, i7 + jdField_k_of_type_Int * i17 + (jdField_k_of_type_Int - a(false, 10) >> 1));
        i18 += a(true, 10);
        str = str.substring(1, str.length());
      }
      i19 = str.length();
      for (i20 = 0; i20 < i19; i20++) {
        if (str.charAt(i20) == '_')
        {
          str = str.substring(0, i20) + " " + str.substring(i20 + 1, i19);
          break;
        }
      }
      jdField_b_of_type_M.a(paramGraphics, str, i18 + r, i7 + jdField_k_of_type_Int * i17 + i10, 20);
    }
    paramGraphics.setClip(i1, i2, i3, i4);
    if (i11 == i9)
    {
      i6 -= i5;
      paramGraphics.setColor(16777215);
      paramGraphics.fillRect(s - 2, i5, 2, i6);
      paramGraphics.setColor(8947848);
      i18 = i9 * i8 / jdField_b_of_type_JavaUtilVector.size();
      i19 = x * (i6 - i18) / i12;
      paramGraphics.fillRect(s - 2, i5 + i19, 2, i18);
    }
    if ((i13 == 0) && (i14 == 0) && (!jdField_k_of_type_Boolean) && (!jdField_a_of_type_JavaLangThread.isAlive()) && (!jdField_m_of_type_Boolean))
    {
      String[] arrayOfString = n.a(i.m[28], jdField_b_of_type_M, 219, true);
      i19 = jdField_b_of_type_M.i();
      i20 = 320 - arrayOfString.length * i19 >> 1;
      for (i1 = 0; i1 < arrayOfString.length; i1++) {
        jdField_b_of_type_M.a(paramGraphics, arrayOfString[i1], 240 - jdField_b_of_type_M.c(arrayOfString[i1]) >> 1, i20 + i1 * i19, 20);
      }
    }
  }
  
  static void A()
  {
    if (!jdField_h_of_type_Boolean) {
      return;
    }
    if (p == 0)
    {
      jdField_j_of_type_Int = 0;
      return;
    }
    if (jdField_j_of_type_Int <= 0)
    {
      jdField_j_of_type_Int = 13;
    }
    else if (jdField_j_of_type_Int == 10)
    {
      jdField_j_of_type_Int = 10;
    }
    else
    {
      jdField_j_of_type_Int -= 1;
      return;
    }
    int i1 = 0;
    int i2;
    switch (p)
    {
    case -1: 
      i1 = n * 34 / 100 / jdField_b_of_type_M.i();
      t -= 1;
      i2 = jdField_b_of_type_JavaUtilVector.size();
      if (t < 0)
      {
        t = i2 - 1;
        if (i2 > i1) {
          y = i2 - i1;
        }
      }
      if (t < 0) {
        t = 0;
      }
      if (t < y)
      {
        y -= 1;
        return;
      }
      break;
    case -2: 
      i1 = n * 34 / 100 / jdField_b_of_type_M.i();
      if (++t >= jdField_b_of_type_JavaUtilVector.size())
      {
        t = 0;
        y = 0;
      }
      if (t > i1 + y - 1)
      {
        y += 1;
        return;
      }
      break;
    case -3: 
      
    case -4: 
      
    case -6: 
      if (jdField_g_of_type_Boolean)
      {
        if ((jdField_g_of_type_JavaLangString != null) && (jdField_g_of_type_JavaLangString.length() > 9))
        {
          if (q.c(jdField_e_of_type_JavaLangString, jdField_g_of_type_JavaLangString)) {
            jdField_b_of_type_ArrayOfJavaLangString = n.a(jdField_c_of_type_ArrayOfJavaLangString[7] + " " + jdField_g_of_type_JavaLangString, jdField_b_of_type_M, s - (r << 1), true);
          } else {
            jdField_b_of_type_ArrayOfJavaLangString = n.a(jdField_c_of_type_ArrayOfJavaLangString[8], jdField_b_of_type_M, s - (r << 1), true);
          }
          jdField_g_of_type_JavaLangString = "";
        }
      }
      else {
        d(t);
      }
      p = 0;
      return;
    case -7: 
      D();
      p = 0;
      return;
    case -5: 
      d(t);
      p = 0;
      return;
    case 49: 
      if (jdField_g_of_type_Boolean)
      {
        a('1');
        return;
      }
      break;
    case 50: 
      if (jdField_g_of_type_Boolean)
      {
        a('2');
        return;
      }
      i1 = n * 34 / 100 / jdField_b_of_type_M.i();
      t -= 1;
      i2 = jdField_b_of_type_JavaUtilVector.size();
      if (t < 0)
      {
        t = i2 - 1;
        if (i2 > i1) {
          y = i2 - i1;
        }
      }
      if (t < 0) {
        t = 0;
      }
      if (t < y) {
        y -= 1;
      }
      if (jdField_m_of_type_Int == 0) {
        try
        {
          j(null);
        }
        catch (Exception localException) {}
      }
      i1 = a(false);
      i2 = a(false, 2);
      i2 = n - (jdField_l_of_type_Int + i2 << 1);
      i1 += jdField_l_of_type_Int;
      i1 = i2 - jdField_l_of_type_Int - i1;
      jdField_d_of_type_JavaUtilVector.size();
      i1 = jdField_d_of_type_JavaUtilVector.size() * jdField_k_of_type_Int - i1;
      z -= 2;
      if (x > i1) {
        x = i1;
      }
      if (x < 0) {
        x = 0;
      }
      return;
    case 51: 
      if (jdField_g_of_type_Boolean)
      {
        a('3');
        return;
      }
      break;
    case 52: 
      if (jdField_g_of_type_Boolean)
      {
        a('4');
        return;
      }
      break;
    case 53: 
      if (jdField_g_of_type_Boolean)
      {
        a('5');
        return;
      }
      d(t);
      return;
    case 54: 
      if (jdField_g_of_type_Boolean)
      {
        a('6');
        return;
      }
      break;
    case 55: 
      if (jdField_g_of_type_Boolean)
      {
        a('7');
        return;
      }
      break;
    case 56: 
      if (jdField_g_of_type_Boolean)
      {
        a('8');
        return;
      }
      i1 = n * 34 / 100 / jdField_b_of_type_M.i();
      if (++t >= jdField_b_of_type_JavaUtilVector.size())
      {
        t = 0;
        y = 0;
      }
      if (t > i1 + y - 1) {
        y += 1;
      }
      y();
      return;
    case 57: 
      if (jdField_g_of_type_Boolean)
      {
        a('9');
        return;
      }
      break;
    case 48: 
      if (jdField_g_of_type_Boolean)
      {
        a('0');
        return;
      }
      break;
    case 35: 
      if (jdField_g_of_type_Boolean)
      {
        E();
        return;
      }
      D();
      return;
    case 42: 
      a('+');
    }
  }
  
  static void c(int paramInt)
  {
    if (!jdField_h_of_type_Boolean) {
      return;
    }
    if (jdField_l_of_type_Boolean)
    {
      w = paramInt;
      return;
    }
    p = paramInt;
  }
  
  static void B()
  {
    if (!jdField_h_of_type_Boolean) {
      return;
    }
    if (jdField_l_of_type_Boolean) {
      w = 0;
    }
    p = 0;
  }
  
  static void a(m paramm)
  {
    jdField_b_of_type_M = paramm;
    s = 240;
    n = 320;
    C();
    jdField_e_of_type_ArrayOfByte = n.a.b("on/oc", -1);
    paramm = n.a.f("on/t");
    jdField_c_of_type_ArrayOfJavaLangString = n.a(paramm, jdField_b_of_type_M, 0, false);
    jdField_a_of_type_B = new b();
    jdField_f_of_type_JavaUtilVector = new Vector();
    jdField_e_of_type_JavaUtilVector = new Vector();
    jdField_b_of_type_JavaUtilVector = new Vector();
    jdField_a_of_type_JavaUtilVector = new Vector();
    jdField_d_of_type_JavaUtilVector = new Vector();
    jdField_c_of_type_JavaUtilVector = new Vector();
    jdField_a_of_type_ArrayOfInt = a();
  }
  
  static void C()
  {
    if (jdField_c_of_type_ArrayOfJavaxMicroeditionLcduiImage == null)
    {
      (jdField_c_of_type_ArrayOfJavaxMicroeditionLcduiImage = new Image[2])[0] = n.a("on/u");
      jdField_c_of_type_ArrayOfJavaxMicroeditionLcduiImage[1] = n.a("on/d");
    }
    int i1;
    if (jdField_e_of_type_ArrayOfJavaxMicroeditionLcduiImage == null)
    {
      jdField_e_of_type_ArrayOfJavaxMicroeditionLcduiImage = new Image[11];
      for (i1 = 0; i1 < 11; i1++) {
        jdField_e_of_type_ArrayOfJavaxMicroeditionLcduiImage[i1] = n.a("on/i" + i1);
      }
    }
    if (jdField_d_of_type_ArrayOfJavaxMicroeditionLcduiImage == null)
    {
      jdField_d_of_type_ArrayOfJavaxMicroeditionLcduiImage = new Image[1];
      for (i1 = 0; i1 <= 0; i1++)
      {
        jdField_d_of_type_ArrayOfJavaxMicroeditionLcduiImage[0] = n.a("on/b0");
        if ((jdField_d_of_type_ArrayOfJavaxMicroeditionLcduiImage[0] != null) && (jdField_d_of_type_ArrayOfJavaxMicroeditionLcduiImage[0].getWidth() != s)) {
          jdField_d_of_type_ArrayOfJavaxMicroeditionLcduiImage[0] = n.b(jdField_d_of_type_ArrayOfJavaxMicroeditionLcduiImage[0], jdField_d_of_type_ArrayOfJavaxMicroeditionLcduiImage[0].getWidth(), jdField_d_of_type_ArrayOfJavaxMicroeditionLcduiImage[0].getHeight(), s, jdField_d_of_type_ArrayOfJavaxMicroeditionLcduiImage[0].getHeight() * s / jdField_d_of_type_ArrayOfJavaxMicroeditionLcduiImage[0].getWidth(), false);
        }
      }
    }
    if (jdField_g_of_type_ArrayOfJavaxMicroeditionLcduiImage == null)
    {
      jdField_g_of_type_ArrayOfJavaxMicroeditionLcduiImage = new Image[7];
      for (i1 = 0; i1 < 7; i1++) {
        jdField_g_of_type_ArrayOfJavaxMicroeditionLcduiImage[i1] = n.a("on/o" + i1);
      }
    }
    if (jdField_f_of_type_ArrayOfJavaxMicroeditionLcduiImage == null) {
      (jdField_f_of_type_ArrayOfJavaxMicroeditionLcduiImage = new Image[1])[0] = n.a("on/l0");
    }
  }
  
  private static int b()
  {
    jdField_l_of_type_Boolean = true;
    w = 0;
    for (;;)
    {
      long l1 = System.currentTimeMillis();
      if (w != 0)
      {
        switch (w)
        {
        case -1: 
        case 50: 
          if ((jdField_j_of_type_Byte = (byte)(jdField_j_of_type_Byte - 1)) < 0) {
            jdField_j_of_type_Byte = 2;
          }
          break;
        case -2: 
        case 56: 
          if ((jdField_j_of_type_Byte = (byte)(jdField_j_of_type_Byte + 1)) > 2) {
            jdField_j_of_type_Byte = 0;
          }
          break;
        case -5: 
        case 53: 
          switch (jdField_j_of_type_Byte)
          {
          case 0: 
            jdField_j_of_type_Byte = 0;
            jdField_l_of_type_Boolean = false;
            w = 0;
            return 1;
          case 1: 
            jdField_j_of_type_Byte = 0;
            jdField_l_of_type_Boolean = false;
            w = 0;
            return 2;
          case 2: 
            jdField_j_of_type_Byte = 0;
            jdField_l_of_type_Boolean = false;
            w = 0;
            return 0;
          }
          break;
        }
        w = 0;
      }
      G();
      NET_Lizard.c.repaint();
      NET_Lizard.c.serviceRepaints();
      long l2;
      if ((l2 = System.currentTimeMillis() - l1) < 77L) {
        try
        {
          Thread.sleep(77L - l2);
        }
        catch (Exception localException) {}
      }
    }
  }
  
  private static void D()
  {
    if (!jdField_f_of_type_Boolean)
    {
      jdField_h_of_type_Boolean = false;
      a.d = -1;
      a.c();
      return;
    }
    if (jdField_a_of_type_JavaLangThread.isAlive())
    {
      jdField_d_of_type_Boolean = true;
      return;
    }
    if (jdField_f_of_type_JavaUtilVector.size() != 0)
    {
      jdField_f_of_type_JavaUtilVector.removeElementAt(jdField_f_of_type_JavaUtilVector.size() - 1);
      w();
      return;
    }
    jdField_h_of_type_Boolean = false;
    a.d = -1;
    a.c();
  }
  
  private static void d(int paramInt)
  {
    if (jdField_a_of_type_JavaLangThread.isAlive()) {
      return;
    }
    if (jdField_b_of_type_JavaUtilVector.size() > paramInt)
    {
      byte[] arrayOfByte = (byte[])jdField_b_of_type_JavaUtilVector.elementAt(paramInt);
      for (int i1 = 1; i1 < arrayOfByte.length; i1++) {
        if (arrayOfByte[i1] == 45)
        {
          a(arrayOfByte, i1);
          return;
        }
      }
      jdField_f_of_type_JavaUtilVector.addElement(jdField_b_of_type_JavaUtilVector.elementAt(paramInt));
      w();
    }
  }
  
  public final void run()
  {
    HttpConnection localHttpConnection = null;
    InputStream localInputStream = null;
    try
    {
      if (jdField_d_of_type_Boolean) {
        v /= 0;
      }
      if (!jdField_j_of_type_Boolean)
      {
        Object localObject1 = null;
        jdField_i_of_type_JavaLangString = jdField_i_of_type_JavaLangString + "?g=CT3&c=UA&n=" + NET_Lizard.g("microedition.platform") + "&i=" + a() + "&r=" + s + "x" + n;
      }
      (localHttpConnection = (HttpConnection)Connector.open(jdField_i_of_type_JavaLangString, 3, true)).setRequestMethod("GET");
      jdField_j_of_type_Boolean = true;
      localInputStream = localHttpConnection.openInputStream();
      if ((jdField_b_of_type_Long = localHttpConnection.getLength()) == -1L)
      {
        jdField_d_of_type_ArrayOfByte = new byte[0];
        jdField_b_of_type_Long = 0L;
        jdField_c_of_type_Long += jdField_i_of_type_JavaLangString.length();
      }
      else
      {
        if (jdField_d_of_type_Boolean) {
          v /= 0;
        }
        jdField_d_of_type_ArrayOfByte = new byte[(int)jdField_b_of_type_Long + jdField_k_of_type_Byte];
        int i1 = 0;
        for (v = jdField_k_of_type_Byte;; v += 1)
        {
          if (jdField_d_of_type_Boolean) {
            v /= 0;
          }
          if ((i1 = localInputStream.read()) == -1) {
            break;
          }
          jdField_d_of_type_ArrayOfByte[v] = ((byte)i1);
          jdField_c_of_type_Long += 1L;
        }
        jdField_l_of_type_Byte = 1;
      }
      try
      {
        localInputStream.close();
        localHttpConnection.close();
      }
      catch (Exception localException2) {}
      jdField_c_of_type_Long += jdField_i_of_type_JavaLangString.length();
    }
    catch (Exception localException1)
    {
      jdField_l_of_type_Byte = -1;
    }
    finally
    {
      try
      {
        localInputStream.close();
        localHttpConnection.close();
      }
      catch (Exception localException4) {}
    }
    if (jdField_d_of_type_Boolean)
    {
      jdField_d_of_type_Boolean = false;
      v = 0;
      jdField_b_of_type_Long = 0L;
    }
    jdField_k_of_type_Byte = 0;
  }
  
  private static void a(RecordStore paramRecordStore)
  {
    try
    {
      long l1 = paramRecordStore.getLastModified() / 1000L;
      String str = NET_Lizard.g("microedition.platform");
      byte[] arrayOfByte;
      (arrayOfByte = new byte[8 + str.length()])[0] = ((byte)(int)(l1 >> 56 & 0xFF));
      arrayOfByte[1] = ((byte)(int)(l1 >> 48 & 0xFF));
      arrayOfByte[2] = ((byte)(int)(l1 >> 40 & 0xFF));
      arrayOfByte[3] = ((byte)(int)(l1 >> 32 & 0xFF));
      arrayOfByte[4] = ((byte)(int)(l1 >> 24 & 0xFF));
      arrayOfByte[5] = ((byte)(int)(l1 >> 16 & 0xFF));
      arrayOfByte[6] = ((byte)(int)(l1 >> 8 & 0xFF));
      arrayOfByte[7] = ((byte)(int)(l1 & 0xFF));
      for (int i1 = 0; i1 < str.length(); i1++) {
        arrayOfByte[(i1 + 8)] = ((byte)str.charAt(i1));
      }
      paramRecordStore.setRecord(1, arrayOfByte, 0, arrayOfByte.length);
      return;
    }
    catch (Exception localException) {}
  }
  
  private void a(String paramString)
  {
    jdField_d_of_type_ArrayOfByte = null;
    jdField_i_of_type_JavaLangString = paramString;
    v = 0;
    jdField_b_of_type_Long = 0L;
    jdField_d_of_type_Boolean = false;
    (jdField_a_of_type_JavaLangThread = new Thread(this)).setPriority(1);
    jdField_a_of_type_JavaLangThread.start();
    jdField_a_of_type_JavaLangThread.setPriority(1);
    jdField_h_of_type_Boolean = true;
  }
  
  private static void E()
  {
    if ((jdField_g_of_type_JavaLangString != null) && (jdField_g_of_type_JavaLangString.length() != 0)) {
      jdField_g_of_type_JavaLangString = jdField_g_of_type_JavaLangString.substring(0, jdField_g_of_type_JavaLangString.length() - 1);
    }
  }
  
  private static int c()
  {
    int i6;
    if (jdField_l_of_type_Boolean)
    {
      i1 = jdField_b_of_type_M.i() + (n >> 5);
      i2 = n - i1 * 3 >> 1;
      i4 = new int[] { jdField_b_of_type_M.c(i.m[jdField_b_of_type_ArrayOfInt[0]]), jdField_b_of_type_M.c(i.m[jdField_b_of_type_ArrayOfInt[1]]), jdField_b_of_type_M.c(i.m[jdField_b_of_type_ArrayOfInt[2]]) }[jdField_j_of_type_Byte] + 3;
      i5 = s - i4 >> 1;
      i3 = i4 + 1;
      i4 = -1;
      for (i6 = 0; i6 < 3; i6++) {
        if (a(i5, i2 + i1 * i6, i3, i1))
        {
          i4 = i6;
          break;
        }
      }
      if (i4 == jdField_j_of_type_Byte) {
        w = 53;
      } else if (i4 != -1) {
        jdField_j_of_type_Byte = (byte)i4;
      } else if (i.bi < n >> 1) {
        w = 50;
      } else {
        w = 56;
      }
      return -100;
    }
    if (a(0, n - 30, s >> 1, 30)) {
      return 1;
    }
    if (a(s >> 1, n - 30, s >> 1, 30)) {
      return 2;
    }
    int i1 = a(false);
    int i2 = n - (jdField_l_of_type_Int + a(false, 0) << 1);
    int i3 = i1 + jdField_l_of_type_Int;
    int i4 = 0;
    int i5 = i2 - jdField_l_of_type_Int - i3;
    if ((i.bi <= i3) || (i.bi >= i3 + i5 + 1))
    {
      if (i.bi < i3 + (i5 >> 1)) {
        return 3;
      }
      return 4;
    }
    if (!jdField_g_of_type_Boolean)
    {
      if (i.bi < B)
      {
        while (i.bi < B)
        {
          i1 = n * 34 / 100 / jdField_b_of_type_M.i();
          t -= 1;
          i2 = jdField_b_of_type_JavaUtilVector.size();
          if (t < 0)
          {
            t = i2 - 1;
            if (i2 > i1) {
              y = i2 - i1;
            }
          }
          if (t < 0) {
            t = 0;
          }
          if (t < y) {
            y -= 1;
          }
          B -= o;
        }
        return 3;
      }
      if (B + o < i.bi)
      {
        while (B + o < i.bi)
        {
          i1 = n * 34 / 100 / jdField_b_of_type_M.i();
          if (++t >= jdField_b_of_type_JavaUtilVector.size())
          {
            t = 0;
            y = 0;
          }
          if (t > i1 + y - 1) {
            y += 1;
          }
          B += o;
        }
        return 4;
      }
      if ((B < i.bi) && (B + o > i.bi)) {
        return 5;
      }
    }
    if (jdField_g_of_type_Boolean)
    {
      i1 = b(jdField_e_of_type_Boolean, 6);
      i4 = b(false, 6);
      i6 = n - (jdField_l_of_type_Int + a(false, 3) << 1);
      i2 = s - i1 * 3 >> 1;
      i3 = i6 - (i4 << 2) - i4;
      i5 = 6;
      for (i6 = 0; i6 < 4; i6++) {
        for (int i7 = 0; i7 < 3; i7++)
        {
          if (a(i2 + i7 * i1, i3 + i6 * i4, i1, i4)) {
            return i5;
          }
          i5++;
        }
      }
    }
    return 0;
  }
  
  static void F()
  {
    if (!jdField_h_of_type_Boolean) {
      return;
    }
    q = 1;
    jdField_i_of_type_Boolean = true;
  }
  
  static void G()
  {
    if (!jdField_h_of_type_Boolean) {
      return;
    }
    if ((q == 1) && (jdField_i_of_type_Boolean))
    {
      jdField_i_of_type_Int = c();
      jdField_i_of_type_Boolean = false;
      if (jdField_l_of_type_Boolean)
      {
        q = 0;
        return;
      }
    }
    if (q == 1)
    {
      int i1 = c();
      if ((jdField_i_of_type_Int == i1) && (i1 != 0)) {
        switch (jdField_i_of_type_Int)
        {
        case 1: 
          if (jdField_g_of_type_Boolean)
          {
            p = -6;
            A();
            p = 0;
          }
          else
          {
            d(t);
            p = 0;
          }
          break;
        case 2: 
          D();
          break;
        case 3: 
          i1 = n * 34 / 100 / jdField_b_of_type_M.i();
          t -= 1;
          int i2 = jdField_b_of_type_JavaUtilVector.size();
          if (t < 0)
          {
            t = i2 - 1;
            if (i2 > i1) {
              y = i2 - i1;
            }
          }
          if (t < 0) {
            t = 0;
          }
          if (t < y) {
            y -= 1;
          }
          break;
        case 4: 
          i1 = n * 34 / 100 / jdField_b_of_type_M.i();
          if (++t >= jdField_b_of_type_JavaUtilVector.size())
          {
            t = 0;
            y = 0;
          }
          if (t > i1 + y - 1) {
            y += 1;
          }
          break;
        case 5: 
          d(t);
          break;
        case 6: 
          a('1');
          break;
        case 7: 
          a('2');
          break;
        case 8: 
          a('3');
          break;
        case 9: 
          a('4');
          break;
        case 10: 
          a('5');
          break;
        case 11: 
          a('6');
          break;
        case 12: 
          a('7');
          break;
        case 13: 
          a('8');
          break;
        case 14: 
          a('9');
          break;
        case 15: 
          a('+');
          break;
        case 16: 
          a('0');
          break;
        case 17: 
          E();
        }
      }
      q = 0;
    }
  }
  
  static void H()
  {
    if (!jdField_h_of_type_Boolean) {
      return;
    }
    q = 2;
  }
  
  static void I()
  {
    if (!jdField_h_of_type_Boolean) {
      return;
    }
    q = 3;
  }
}


/* Location:              C:\Users\Administrator\Desktop\CT3_God_Mode.jar!\b.class
 * Java compiler version: 4 (48.0)
 * JD-Core Version:       0.7.1
 */