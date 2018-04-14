import java.util.Random;
import javax.microedition.lcdui.Display;
import javax.microedition.lcdui.Graphics;
import javax.microedition.lcdui.Image;

public final class k
  extends b
  implements Runnable
{
  byte[] a;
  byte[][] b;
  static final int[] c;
  static final int[] d;
  static byte e;
  static byte f;
  static int g;
  int h = 35;
  boolean i = false;
  static int[] j;
  private static final int[][] dO;
  static o[] k;
  static j[] l;
  boolean m = true;
  static int[] n;
  static c[] o;
  static short p;
  static g[] q;
  String r;
  static m[] s;
  static final int[] t;
  static final int[] u;
  static final int[] v;
  static final int[] w;
  static final int[] x;
  static final int[] y;
  static final int[] z;
  static final int[] A;
  static final int[] B;
  static final int[] C;
  static final int[] D;
  static final int[] E;
  static final int[] F;
  static final int[] G;
  static final int[] H;
  static final int[] I;
  static final int[] J;
  static final int[] K;
  static final int[] L;
  static final int[] M;
  static final int[] N;
  static final int[] O;
  static final int[] P;
  final int[] Q;
  static int R;
  byte S;
  static byte[][] T;
  static final byte[] U;
  static final byte[][] V;
  byte W;
  static byte[] X;
  static int Y = 0;
  byte[] Z;
  static Image aa;
  static byte[][] ab;
  static byte[][] ac;
  byte[][] ad;
  static byte ae;
  static boolean af;
  static j ag;
  String ah = "";
  boolean ai = false;
  static boolean aj;
  static boolean ak;
  static boolean al;
  boolean am = false;
  boolean an = true;
  static final int[] ao;
  static int[] ap;
  static final int[] aq;
  static short[][] ar;
  static byte as;
  static short[][] at;
  short au = 256;
  static byte[] av;
  static int aw;
  static boolean ax;
  static byte ay;
  static int[] az;
  static int[] aA;
  static int aB;
  static int[] aC;
  static boolean aD;
  static e aE;
  static byte aF;
  static boolean aG;
  static boolean aH;
  static boolean aI;
  d aJ;
  static byte aK;
  int aL;
  static byte[] aM;
  Image aN;
  int aO;
  static l[] aP;
  static int[] aQ;
  static int[] aR;
  static l[] aS;
  static byte aT;
  static short aU;
  Image aV;
  static boolean aW;
  short aX;
  static int aY;
  static int[] aZ;
  static int[] ba;
  short bb = 0;
  boolean bc = false;
  boolean bd = false;
  int be = 0;
  byte bf = 0;
  static e bg;
  boolean bh = true;
  static boolean bi;
  int bj = -1;
  static int bk;
  static int bl;
  static final int[] bm;
  static byte bn;
  int bo;
  static short[] bp;
  static boolean bq;
  boolean br = false;
  byte bs = 0;
  Image bt;
  static boolean[] bu;
  static boolean[] bv;
  static boolean[] bw;
  final int[] bx;
  static final int[] by;
  n bz;
  static boolean bA;
  static final byte[] bB;
  int bC = -1;
  byte bD = 0;
  byte bE;
  byte bF;
  byte bG;
  byte bH;
  static byte bI;
  static final byte[] bJ;
  private static Random dP = new Random();
  short bK = 0;
  byte bL = 2;
  static byte bM;
  static String bN;
  boolean bO = false;
  Image bP;
  static final byte[][] bQ;
  static byte bR;
  static short bS;
  static short bT;
  static int bU;
  static int bV;
  static int bW;
  static byte[] bX;
  private static final int[] dQ;
  Image bY;
  long bZ;
  static int[][] ca;
  static int[] cb;
  static int[] cc;
  static int[] cd;
  static int[][] ce;
  static int[][] cf;
  short cg;
  static final int[][] ch;
  static boolean ci;
  static boolean cj;
  static boolean ck;
  static final int[] cl;
  static byte cm;
  static byte[] cn;
  static final byte[] co;
  static int cp;
  static int cq;
  static short cr;
  static final byte[] cs;
  static final byte[] ct;
  boolean cu = false;
  static int cv;
  static final byte[] cw;
  static int cx;
  static int cy;
  static int cz;
  static int cA;
  static short cB;
  static int cC;
  static int cD;
  static int cE;
  static int[] cF;
  static byte cG;
  static byte cH;
  byte cI = 0;
  byte cJ = 0;
  byte cK = 0;
  short cL = 0;
  short cM = 0;
  byte cN = 0;
  static short[][] cO;
  short cP = 0;
  static byte cQ;
  static int[][] cR;
  static short cS;
  static int cT;
  static final int[] cU;
  int cV = 0;
  boolean cW;
  int cX = 0;
  static byte[] cY;
  static byte cZ;
  String[][] da;
  static boolean db;
  String[] dc;
  static boolean dd;
  int de;
  static short df;
  static int[][] dg;
  static int dh;
  static boolean di;
  int dj = 77;
  static e dk;
  static byte dl;
  static int[] dm;
  static int dn;
  static byte[][] jdField_do;
  static byte[][] dp;
  static byte[] dq;
  static byte[][] dr;
  static byte[][] ds;
  Thread dt;
  static boolean du;
  static int dv;
  static int[] dw;
  static boolean dx;
  static boolean dy;
  static byte dz;
  static byte dA;
  static byte dB;
  static byte dC;
  static final short[] dD;
  static final short[] dE;
  static byte dF;
  static short dG;
  static int dH;
  static short dI;
  static int dJ;
  static short dK;
  static int dL;
  static byte dM;
  static byte dN;
  
  static
  {
    aW = false;
    ax = false;
    al = false;
    ak = false;
    aj = false;
    bl = 301;
    bN = "rm";
    aI = false;
    cQ = 0;
    bA = true;
    bM = 0;
    aD = true;
    dx = true;
    dd = true;
    dN = -1;
    dM = 0;
    dQ = new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 1, 2, 3, 4, 0, 1, 2, 3, 4, 1, 2, 3, 4, 5, 0, 1, 2, 3, 1, 2, 3, 4, 5, 6, 0, 1, 2, 1, 2, 3, 4, 5, 6, 7, 0, 1, 1, 2, 3, 4, 5, 6, 7, 8, 0 };
    aq = new int[] { 65536, 65526, 65496, 65446, 65376, 65287, 65177, 65048, 64898, 64729, 64540, 64332, 64104, 63856, 63589, 63303, 62997, 62672, 62328, 61966, 61584, 61183, 60764, 60326, 59870, 59396, 58903, 58393, 57865, 57319, 56756, 56175, 55578, 54963, 54332, 53684, 53020, 52339, 51643, 50931, 50203, 49461, 48703, 47930, 47143, 46341, 45525, 44695, 43852, 42995, 42126, 41243, 40348, 39441, 38521, 37590, 36647, 35693, 34729, 33754, 32768, 31772, 30767, 29753, 28729, 27697, 26656, 25607, 24550, 23486, 22415, 21336, 20252, 19161, 18064, 16962, 15855, 14742, 13626, 12505, 11380, 10252, 9121, 7987, 6850, 5712, 4572, 3430, 2287, 1144, 0, 64392, 63249, 62106, 60964, 59824, 58686, 57549, 56415, 55284, 54156, 53031, 51910, 50794, 49681, 48574, 47472, 46375, 45284, 44200, 43121, 42050, 40986, 39929, 38880, 37839, 36807, 35783, 34769, 33764, 32768, -33754, -34729, -35693, -36647, -37590, -38521, -39441, -40348, -41243, -42126, -42995, -43852, -44695, -45525, -46341, -47143, -47930, -48703, -49461, -50203, -50931, -51643, -52339, -53020, -53684, -54332, -54963, -55578, -56175, -56756, -57319, -57865, -58393, -58903, -59396, -59870, -60326, -60764, -61183, -61584, -61966, -62328, -62672, -62997, -63303, -63589, -63856, -64104, -64332, -64540, -64729, -64898, -65048, -65177, -65287, -65376, -65446, -65496, -65526, -65536, -65526, -65496, -65446, -65376, -65287, -65177, -65048, -64898, -64729, -64540, -64332, -64104, -63856, -63589, -63303, -62997, -62672, -62328, -61966, -61584, -61183, -60764, -60326, -59870, -59396, -58903, -58393, -57865, -57319, -56756, -56175, -55578, -54963, -54332, -53684, -53020, -52339, -51643, -50931, -50203, -49461, -48703, -47930, -47143, -46341, -45525, -44695, -43852, -42995, -42126, -41243, -40348, -39441, -38521, -37590, -36647, -35693, -34729, -33754, 32768, 33764, 34769, 35783, 36807, 37839, 38880, 39929, 40986, 42050, 43121, 44200, 45284, 46375, 47472, 48574, 49681, 50794, 51910, 53031, 54156, 55284, 56415, 57549, 58686, 59824, 60964, 62106, 63249, 64392, 0, 1144, 2287, 3430, 4572, 5712, 6850, 7987, 9121, 10252, 11380, 12505, 13626, 14742, 15855, 16962, 18064, 19161, 20252, 21336, 22415, 23486, 24550, 25607, 26656, 27697, 28729, 29753, 30767, 31772, 32768, 33754, 34729, 35693, 36647, 37590, 38521, 39441, 40348, 41243, 42126, 42995, 43852, 44695, 45525, 46341, 47143, 47930, 48703, 49461, 50203, 50931, 51643, 52339, 53020, 53684, 54332, 54963, 55578, 56175, 56756, 57319, 57865, 58393, 58903, 59396, 59870, 60326, 60764, 61183, 61584, 61966, 62328, 62672, 62997, 63303, 63589, 63856, 64104, 64332, 64540, 64729, 64898, 65048, 65177, 65287, 65376, 65446, 65496, 65526 };
    cU = new int[] { 0, 1144, 2287, 3430, 4572, 5712, 6850, 7987, 9121, 10252, 11380, 12505, 13626, 14742, 15855, 16962, 18064, 19161, 20252, 21336, 22415, 23486, 24550, 25607, 26656, 27697, 28729, 29753, 30767, 31772, 32768, 33754, 34729, 35693, 36647, 37590, 38521, 39441, 40348, 41243, 42126, 42995, 43852, 44695, 45525, 46341, 47143, 47930, 48703, 49461, 50203, 50931, 51643, 52339, 53020, 53684, 54332, 54963, 55578, 56175, 56756, 57319, 57865, 58393, 58903, 59396, 59870, 60326, 60764, 61183, 61584, 61966, 62328, 62672, 62997, 63303, 63589, 63856, 64104, 64332, 64540, 64729, 64898, 65048, 65177, 65287, 65376, 65446, 65496, 65526, 65536, 65526, 65496, 65446, 65376, 65287, 65177, 65048, 64898, 64729, 64540, 64332, 64104, 63856, 63589, 63303, 62997, 62672, 62328, 61966, 61584, 61183, 60764, 60326, 59870, 59396, 58903, 58393, 57865, 57319, 56756, 56175, 55578, 54963, 54332, 53684, 53020, 52339, 51643, 50931, 50203, 49461, 48703, 47930, 47143, 46341, 45525, 44695, 43852, 42995, 42126, 41243, 40348, 39441, 38521, 37590, 36647, 35693, 34729, 33754, 32768, 31772, 30767, 29753, 28729, 27697, 26656, 25607, 24550, 23486, 22415, 21336, 20252, 19161, 18064, 16962, 15855, 14742, 13626, 12505, 11380, 10252, 9121, 7987, 6850, 5712, 4572, 3430, 2287, 1144, 0, 64392, 63249, 62106, 60964, 59824, 58686, 57549, 56415, 55284, 54156, 53031, 51910, 50794, 49681, 48574, 47472, 46375, 45284, 44200, 43121, 42050, 40986, 39929, 38880, 37839, 36807, 35783, 34769, 33764, 32768, -33754, -34729, -35693, -36647, -37590, -38521, -39441, -40348, -41243, -42126, -42995, -43852, -44695, -45525, -46341, -47143, -47930, -48703, -49461, -50203, -50931, -51643, -52339, -53020, -53684, -54332, -54963, -55578, -56175, -56756, -57319, -57865, -58393, -58903, -59396, -59870, -60326, -60764, -61183, -61584, -61966, -62328, -62672, -62997, -63303, -63589, -63856, -64104, -64332, -64540, -64729, -64898, -65048, -65177, -65287, -65376, -65446, -65496, -65526, -65536, -65526, -65496, -65446, -65376, -65287, -65177, -65048, -64898, -64729, -64540, -64332, -64104, -63856, -63589, -63303, -62997, -62672, -62328, -61966, -61584, -61183, -60764, -60326, -59870, -59396, -58903, -58393, -57865, -57319, -56756, -56175, -55578, -54963, -54332, -53684, -53020, -52339, -51643, -50931, -50203, -49461, -48703, -47930, -47143, -46341, -45525, -44695, -43852, -42995, -42126, -41243, -40348, -39441, -38521, -37590, -36647, -35693, -34729, -33754, 32768, 33764, 34769, 35783, 36807, 37839, 38880, 39929, 40986, 42050, 43121, 44200, 45284, 46375, 47472, 48574, 49681, 50794, 51910, 53031, 54156, 55284, 56415, 57549, 58686, 59824, 60964, 62106, 63249, 64392 };
    cv = 0;
    bT = -1;
    g = 0;
    cy = 0;
    cz = 0;
    cA = 0;
    cC = 270;
    cD = 270;
    cE = 0;
    dy = false;
    dz = 16;
    dA = 0;
    dB = 4;
    bV = 240;
    bW = bV << 16;
    cF = new int[3];
    cl = new int[] { 150, 151, 120, 121 };
    ch = new int[][] { { 0, 0, bV }, { 0, -bV, 150 }, { 0, bV, 151 }, { bV, 0, 120 }, { -bV, 0, 121 } };
    cH = 0;
    cG = 0;
    f = 0;
    aB = 0;
    dF = 0;
    dC = 0;
    dG = 0;
    ae = 0;
    af = false;
    cZ = 0;
    cY = new byte[] { 0, 0, 0, 0 };
    dE = new short[] { 130, 2000, 3000, 4000, 5000, 5000, 4000 };
    co = new byte[] { 2, 4, 2, 3, 4, 12, 10 };
    ct = new byte[] { 5, 3, 1, 2, 2, 12, 10 };
    U = new byte[] { -1, 7, 30, 30, 30, 6, 3 };
    new byte[] { -1, 21, 30, 60, 60, 6 }[6] = 0;
    T = new byte[][] { { -1, 7, 30, 30, 30, 6, 3 }, { -1, 21, 30, 60, 60, 6, 0 } };
    dD = new short[] { 100, 80, 35, 50, 70, 170, 400 };
    by = new int[] { 20, 40, 200, 70 };
    bq = true;
    bB = new byte[] { 26, 27, 28, 29, 22 };
    as = 0;
    db = false;
    t = new int[] { 1744830464 };
    D = new int[] { 1819700224 };
    L = new int[] { 795881072, 1852243968 };
    M = new int[] { 795832878, 1886283520 };
    N = new int[] { 1865379584 };
    O = new int[] { 795438128, 779120231 };
    P = new int[] { 795765806, 1886283520 };
    u = new int[] { 779120231 };
    v = new int[] { 796340087 };
    w = new int[] { 796065792 };
    x = new int[] { 796196864 };
    y = new int[] { 795638272 };
    z = new int[] { 795632640 };
    A = new int[] { 1767964672 };
    B = new int[] { 1768882176 };
    C = new int[] { 1953300480 };
    E = new int[] { 1667432448 };
    F = new int[] { 1660944384 };
    G = new int[] { 1953693696 };
    H = new int[] { 1667301376 };
    I = new int[] { 1667694592 };
    J = new int[] { 1734934528 };
    K = new int[] { 1768124270, 1932487011, 1862270976 };
    new int[] { 1296389185, 759778886, 793592142, 1229342035 }[4] = 1412320582;
    new int[] { 1399874915, 1768319331, 1635019119 }[3] = 1845493760;
    new int[] { 1296647248 }[1] = 758263344;
    new int[1][0] = 1684368640;
    new int[1][0] = 1919746048;
    new int[] { 1399353202, 1949126261 }[2] = 1835165042;
    new int[1][0] = 1131373669;
    new int[] { 1348565357, 1701737517 }[2] = 1415936116;
    new int[] { 1197567333 }[1] = 754974720;
    new int[] { 1852798035 }[1] = 1297285120;
    c = new int[] { 1399420005, 1431456768 };
    d = new int[] { 1296647276, 1702112585, 1852206893, 1431456768 };
    new int[] { 1784772193, 2016311145, 1919249509, 1936928365, 1702064993, 1734962791, 776824179 }[7] = 1935763301;
    new int[] { 1668246830, 1935764851, 1970169646, 1970563436 }[4] = 777211219;
    new int[] { 1668246830, 1936287085, 1701737262, 1836068455, 1936535123 }[5] = 1297285120;
    bi = false;
    bk = 9;
    ck = true;
    di = false;
    bJ = new byte[] { 0, 14, 14, 14, 28, 14, 42, 14, 56, 3, 59, 7 };
    bQ = new byte[][] { { 0 }, { 1, 0, 1, 1, 1, 2, 1, 3, 4, 4, 2, 8, 2, 10, 2, 12, 1, 14, 3, 15, 1, 18 }, { 1, 0, 1, 1, 1, 2, 1, 3, 4, 4, 2, 8, 2, 10, 2, 12, 1, 14, 3, 15, 1, 18 }, { 1, 0, 1, 1, 1, 2, 1, 3, 4, 4, 2, 8, 2, 10, 2, 12, 1, 14, 3, 15, 1, 18 }, { 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 4, 2, 2, 6, 2, 8, 2, 10, 1, 12, 3, 13, 1, 16 }, { 1, 0, 2, 1 }, { 1, 0, 4, 1, 6, 5, 1, 10 } };
    V = new byte[][] { { 0 }, { 0, 2, 9, 9, 3, 4, 5, 6, 7, 8, 9, 10, 9, 10, 1, 11, 12, 13, 13 }, { 14, 16, 23, 23, 17, 18, 19, 20, 21, 22, 23, 24, 23, 24, 15, 25, 26, 27, 27 }, { 28, 30, 37, 37, 31, 32, 33, 34, 35, 36, 37, 38, 37, 38, 29, 39, 40, 41, 41 }, { 42, 43, 45, 46, 47, 48, 49, 50, 51, 52, 51, 52, 44, 53, 54, 55, 55 }, { 56, 57, 58 }, { 59, 60, 61, 62, 63, 59, 59, 64, 64, 65, 65 } };
    R = 256;
    dn = 0;
    ao = new int[] { 13027014, 11382189, 10395294, 9079434, 9868950, 0, 16777215, 7037537, 8167333, 10533310, 12832469, 7310483, 9455640, 7682836, 6500882, 12972031, 7980013, 4299480, 3895715 };
    cB = 0;
    dO = new int[][] { { 13, 14, 15, 16, 17 }, { 7, 8, 9 }, { 2, 2 }, { 3, 3 }, { 4, 4 }, { 2, 2 }, { 5 }, { 6 }, { 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12 }, { 12, 12 } };
    bR = 0;
    dh = 0;
    cT = 0;
    dw = new int[3];
    aU = 0;
    p = 1;
    dk = new e(null);
    aE = new e(null);
    bg = new e(null);
    aK = 0;
    du = false;
    aw = 0;
    cp = 0;
    cq = 0;
    ay = 0;
    cs = new byte[] { 8, 5 };
    cj = false;
    e = 0;
    bm = new int[] { 58982400, 137625600, 216268800, 275251200, 98304000 };
    cw = new byte[] { 19, 18, 20, 20 };
  }
  
  public k()
  {
    new e(null);
    new e(null);
    new e(null);
    this.de = 0;
    this.aL = 32768;
    this.aO = 65536;
    this.Q = new int[] { 10, 6 };
    this.bx = new int[] { 64000000, 100000000 };
    this.bG = 0;
    this.bE = 0;
    this.bF = 0;
    this.bH = 0;
    this.bo = -983040;
    this.dt = new Thread(this);
  }
  
  private final void a(m paramm)
  {
    switch (paramm.y)
    {
    case 0: 
      
    case 1: 
      c(paramm);
      return;
    case 2: 
      e(paramm);
      return;
    case 3: 
      e(paramm);
      return;
    case 4: 
      b(paramm);
      return;
    case 5: 
      
    case 6: 
      
    case 7: 
      d(paramm);
    }
  }
  
  private final void b(m paramm)
  {
    byte[] arrayOfByte1 = this.Z;
    m localm;
    if ((localm = s[0]).o < 163840000) {
      return;
    }
    int i1;
    switch (arrayOfByte1[0])
    {
    case 0: 
      int tmp58_57 = 1;
      byte[] tmp58_56 = arrayOfByte1;
      tmp58_56[tmp58_57] = ((byte)(tmp58_56[tmp58_57] - 1));
      if (a(paramm, localm))
      {
        arrayOfByte1[0] = 1;
        arrayOfByte1[1] = 10;
        return;
      }
      if (arrayOfByte1[1] <= 0)
      {
        arrayOfByte1[0] = 3;
        arrayOfByte1[1] = 90;
        arrayOfByte1[2] = ((byte)e(4));
        paramm.v = (this.a[(arrayOfByte1[3] << 1)] * 100 << 16);
        paramm.w = (this.a[((arrayOfByte1[3] << 1) + 1)] * 100 << 16);
        return;
      }
      break;
    case 1: 
      int tmp150_149 = 1;
      byte[] tmp150_148 = arrayOfByte1;
      tmp150_148[tmp150_149] = ((byte)(tmp150_148[tmp150_149] - 1));
      if (arrayOfByte1[1] <= 0)
      {
        if (b(localm.r - 10, paramm.r - 10))
        {
          if ((i1 = (short)arrayOfByte1[1]) < 0) {
            i1 = (short)(i1 + 256);
          }
          int i2 = this.b[i1][(arrayOfByte1[2] + 1)];
          paramm.v = (this.a[(i2 << 1)] * 100 << 16);
          paramm.w = (this.a[((i2 << 1) + 1)] * 100 << 16);
          arrayOfByte1[0] = 2;
          return;
        }
        arrayOfByte1[1] = 10;
        return;
      }
      if (a(paramm, localm))
      {
        b(paramm, localm.n, localm.o, localm.p, 4);
        i(paramm);
        return;
      }
      break;
    case 2: 
      if (!a(paramm, paramm.v, paramm.w, 200, 0))
      {
        byte[] tmp320_317 = arrayOfByte1;
        tmp320_317[7] = ((byte)(tmp320_317[7] + 1));
        if ((i1 = (short)arrayOfByte1[1]) < 0) {
          i1 = (short)(i1 + 256);
        }
        byte[] arrayOfByte2 = this.b[i1];
        int i3 = arrayOfByte1[2];
        int i4 = arrayOfByte2[i3];
        if (arrayOfByte1[7] > i4)
        {
          this.Z[0] = 0;
          this.Z[1] = 50;
        }
        else
        {
          int i5 = arrayOfByte2[(i3 + arrayOfByte1[7])];
          paramm.v = (this.a[(i5 << 1)] * 100 << 16);
          paramm.w = (this.a[((i5 << 1) + 1)] * 100 << 16);
          return;
        }
      }
      break;
    case 3: 
      int tmp448_447 = 1;
      byte[] tmp448_446 = arrayOfByte1;
      tmp448_446[tmp448_447] = ((byte)(tmp448_446[tmp448_447] - 1));
      if (a(paramm, localm))
      {
        arrayOfByte1[0] = 1;
        arrayOfByte1[1] = 10;
        return;
      }
      if (!a(paramm, paramm.v, paramm.w, 200, 0)) {
        arrayOfByte1[1] = 0;
      }
      if (arrayOfByte1[1] <= 0)
      {
        arrayOfByte1[1] = 90;
        int tmp508_507 = 2;
        byte[] tmp508_506 = arrayOfByte1;
        tmp508_506[tmp508_507] = ((byte)(tmp508_506[tmp508_507] + 1));
        if (arrayOfByte1[2] > 3) {
          arrayOfByte1[2] = 0;
        }
        paramm.v = (this.a[(arrayOfByte1[(3 + arrayOfByte1[2])] << 1)] * 100 << 16);
        paramm.w = (this.a[((arrayOfByte1[(3 + arrayOfByte1[2])] << 1) + 1)] * 100 << 16);
      }
      break;
    }
  }
  
  private final void c(m paramm)
  {
    m localm1 = s[0];
    if (paramm.u)
    {
      if (!paramm.A) {
        return;
      }
      if ((a(paramm, localm1)) && (b(paramm, localm1))) {
        paramm.u = false;
      }
      return;
    }
    m[] arrayOfm = s;
    m tmp50_49 = paramm;
    tmp50_49.d = ((short)(tmp50_49.d - 1));
    if (paramm.d <= 0) {
      paramm.d = 0;
    }
    if ((paramm.j >= 0) && ((!a(paramm, arrayOfm[paramm.j])) || (arrayOfm[paramm.j].i))) {
      paramm.j = -1;
    }
    if (paramm.d == 0)
    {
      int i1;
      m localm3;
      for (int i2 = i1 = Math.abs(dP.nextInt() % dv); i2 < dv; i2++) {
        if ((!(localm3 = arrayOfm[i2]).i) && (localm3.y > 1) && (localm3.y < 3) && (a(paramm, localm3))) {
          paramm.j = ((byte)i2);
        }
      }
      for (int i3 = 0; i3 < i1; i3++) {
        if ((!(localm3 = arrayOfm[i3]).i) && (localm3.y > 1) && (localm3.y < 3) && (a(paramm, localm3))) {
          paramm.j = ((byte)i3);
        }
      }
      paramm.d = ((short)(byte)(f(7) + 2));
    }
    if ((cj) && (a(paramm, localm1)))
    {
      paramm.a = e;
      if (e == 2)
      {
        paramm.j = -1;
        paramm.d = 25;
      }
    }
    if (paramm.j >= 0)
    {
      m localm2 = arrayOfm[paramm.j];
      b(paramm, localm2.n, localm2.o, localm2.p, (short)this.Q[ay]);
      i(paramm);
      return;
    }
    switch (paramm.a)
    {
    case -1: 
      
    case 0: 
      
    case 1: 
      
    case 2: 
      a(paramm, localm1.n, localm1.o, 350, 200);
      return;
    case 3: 
      a(paramm, localm1.v, localm1.w, 350, 200);
    }
  }
  
  private static final boolean a(m paramm, int paramInt1, int paramInt2, int paramInt3, int paramInt4)
  {
    int i1 = paramm.n - paramInt1 >> 16;
    int i2 = paramm.o - paramInt2 >> 16;
    int i3 = i1 * i1 + i2 * i2;
    int i6 = 0;
    int i7 = 65536;
    while (i7 >>= 1 > 0) {
      if ((i6 + i7) * (i6 + i7) <= i3) {
        i6 += i7;
      }
    }
    if (i6 == 0) {
      i6 = 1;
    }
    int i4 = -i1 * 65536 / i6;
    int i5 = -i2 * 65536 / i6;
    paramm.s[0] = i4;
    paramm.s[1] = i5;
    if (i6 > paramInt3)
    {
      paramm.b[0] = i4;
      paramm.b[1] = i5;
      return true;
    }
    if (i6 < paramInt4)
    {
      paramm.b[0] = (-i4);
      paramm.b[1] = (-i5);
      return true;
    }
    return false;
  }
  
  private static void d(m paramm)
  {
    int i1 = l.length;
    j[] arrayOfj = l;
    j localj1 = null;
    j localj2 = null;
    if (paramm.u) {
      return;
    }
    for (int i2 = 0; i2 < i1; i2++)
    {
      if (arrayOfj[i2].t == 50) {
        localj1 = arrayOfj[i2];
      }
      if (arrayOfj[i2].t == 49) {
        localj2 = arrayOfj[i2];
      }
    }
    if (localj1.f <= 0)
    {
      if (localj1.o != 0)
      {
        localj1.g -= 50;
        if (localj1.g < 0) {
          localj1.g = 0;
        }
        paramm.f = ((short)(paramm.f + 2));
        if (paramm.f >= 360) {
          paramm.f = ((short)(paramm.f - 360));
        }
        localj1.q += 8;
        if (localj1.q >= 360) {
          localj1.q -= 360;
        }
        j tmp177_176 = localj1;
        tmp177_176.e = ((short)(tmp177_176.e - 2));
        if (localj1.e < 0) {
          localj1.e = 0;
        }
        j tmp201_199 = localj2;
        tmp201_199.e = ((short)(tmp201_199.e - 2));
        if (localj2.e < 0) {
          localj2.e = 0;
        }
        localj1.m = (-aq[paramm.f] * localj1.g);
        localj1.n = (-cU[paramm.f] * localj1.g);
        localj1.o -= 983040;
        if (localj1.o < 0) {
          localj1.o = 0;
        }
        localj2.m = localj1.m;
        localj2.n = localj1.n;
        localj2.o = localj1.o;
        paramm.n = localj2.m;
        paramm.o = localj2.n;
        paramm.p = localj2.o;
        localj2.q += 31;
        if (localj2.q >= 360) {
          localj2.q -= 360;
        }
        dG = (short)(dG + 3);
        if (dG >= 150)
        {
          aD = true;
          NET_Lizard.b.cP = 0;
          NET_Lizard.b.bb = 0;
          NET_Lizard.b.aX = 0;
          NET_Lizard.b.i = false;
          g = 1;
          aD = true;
          cm = -1;
          b1 = bM;
          bM = 11;
          R();
          bM = b1;
        }
        for (byte b1 = 0; b1 < 2; b1++) {
          a(-aq[paramm.f] * localj1.g + (256 - Math.abs(dP.nextInt() & 0x1FF) << 16), -cU[paramm.f] * localj1.g + (256 - Math.abs(dP.nextInt() & 0x1FF) << 16), localj1.o + (256 - Math.abs(dP.nextInt() & 0xFF) << 16), (byte)9, localj1.r);
        }
        a(-aq[paramm.f] * localj1.g + (256 - Math.abs(dP.nextInt() & 0x1FF) << 16), -cU[paramm.f] * localj1.g + (256 - Math.abs(dP.nextInt() & 0x1FF) << 16), localj1.o + (256 - Math.abs(dP.nextInt() & 0x1FF) << 16), (byte)0, localj1.r);
        localj1.r = 2;
        localj2.r = 2;
      }
      return;
    }
    if (paramm.d <= 0)
    {
      paramm.d = ((short)(Math.abs(dP.nextInt() & 0xFF) + 70));
      paramm.a = ((byte)Math.abs(dP.nextInt() & 0x1));
      if (paramm.a == 0)
      {
        paramm.v = (localj1.q + 180);
        if (paramm.v >= 360) {
          paramm.v -= 360;
        }
      }
      if (paramm.a == 1)
      {
        paramm.v = (localj1.q - 180);
        if (paramm.v < 0) {
          paramm.v += 360;
        }
      }
      if ((paramm.w != 1) && (paramm.w != -1)) {
        paramm.w = 1;
      }
      paramm.w = (-paramm.w);
    }
    if (paramm.v != localj1.q)
    {
      if (paramm.v > localj1.q)
      {
        localj1.q += 10;
        if (paramm.v < localj1.q) {
          localj1.q = paramm.v;
        }
      }
      else
      {
        localj1.q -= 10;
        if (paramm.v > localj1.q) {
          localj1.q = paramm.v;
        }
      }
    }
    else
    {
      paramm.f = ((short)(paramm.f + paramm.w));
      localj1.q += paramm.w;
      if (paramm.f < 0) {
        paramm.f = ((short)(paramm.f + 360));
      }
      if (paramm.f >= 360) {
        paramm.f = ((short)(paramm.f - 360));
      }
      if (localj1.q >= 360) {
        localj1.q -= 360;
      }
      if (localj1.q < 0) {
        localj1.q += 360;
      }
      paramm.v = localj1.q;
      localj1.m = (-aq[paramm.f] * localj1.g);
      localj1.n = (-cU[paramm.f] * localj1.g);
      localj1.o = 104857600;
      paramm.d = ((short)(paramm.d - 1));
      if ((paramm.a = (byte)(paramm.a - 1)) <= 0)
      {
        c(paramm, s[0]);
        paramm.a = ((byte)(Math.abs(dP.nextInt() & 0x1F) + 40));
      }
    }
    if (localj1.q >= 360) {
      localj1.q -= 360;
    }
    if (localj1.q < 0) {
      localj1.q += 360;
    }
    if (paramm.f >= 360) {
      paramm.f = ((short)(paramm.f - 360));
    }
    if (paramm.f < 0) {
      paramm.f = ((short)(paramm.f + 360));
    }
    localj2.m = localj1.m;
    localj2.n = localj1.n;
    localj2.o = localj1.o;
    paramm.n = localj2.m;
    paramm.o = localj2.n;
    paramm.p = localj2.o;
    localj2.q += 61;
    localj2.p = localj1.p;
    if (localj2.q >= 360) {
      localj2.q -= 360;
    }
    if (localj2.q < 0) {
      localj2.q += 360;
    }
  }
  
  private final void e(m paramm)
  {
    Object localObject1 = s[0];
    if (paramm.u)
    {
      if (!paramm.A) {
        return;
      }
      if ((a(paramm, (m)localObject1)) && (b(paramm, (m)localObject1))) {
        paramm.u = false;
      }
      return;
    }
    g localg1 = q[paramm.r];
    Object localObject2 = localObject1;
    m[] arrayOfm = s;
    int i1 = 0;
    m tmp65_64 = paramm;
    tmp65_64.d = ((short)(tmp65_64.d - 1));
    if (paramm.d <= 0) {
      paramm.d = 0;
    }
    int i2;
    if (paramm.j < 0)
    {
      int i3;
      m localm;
      for (i2 = i3 = Math.abs(dP.nextInt() % dv); i2 < dv; i2++) {
        if ((!(localm = arrayOfm[i2]).i) && (localm.y < 2) && (a(paramm, localm))) {
          paramm.j = ((byte)i2);
        }
      }
      for (i2 = 0; i2 < i3; i2++) {
        if ((!(localm = arrayOfm[i2]).i) && (localm.y < 2) && (a(paramm, localm))) {
          paramm.j = ((byte)i2);
        }
      }
    }
    if ((paramm.j >= 0) && (((localObject2 = s[paramm.j]).i) || (!a(paramm, (m)localObject2)))) {
      paramm.j = -1;
    }
    if (paramm.j >= 0)
    {
      localObject1 = localObject2;
      if (paramm.j == 0)
      {
        if (b(paramm, (m)localObject1))
        {
          i1 = 1;
          paramm.v = ((m)localObject1).n;
          paramm.w = ((m)localObject1).o;
        }
        else if ((aH) && (Math.abs(((m)localObject1).n - paramm.n >> 16) + Math.abs(((m)localObject1).o - paramm.o >> 16) + Math.abs(((m)localObject1).p - paramm.p >> 16) < 1200))
        {
          i1 = 1;
          paramm.v = ((m)localObject1).n;
          paramm.w = ((m)localObject1).o;
        }
      }
      else
      {
        i1 = 1;
        paramm.v = ((m)localObject1).n;
        paramm.w = ((m)localObject1).o;
      }
    }
    c localc;
    g localg2;
    switch (paramm.a)
    {
    case 0: 
    case 1: 
      if (i1 != 0)
      {
        paramm.d = ((short)(byte)(f(15) + 2));
        if (paramm.d < 2)
        {
          if (f(1) == 0)
          {
            paramm.a = 3;
          }
          else
          {
            paramm.a = 5;
            break;
          }
        }
        else
        {
          if (paramm.d < 5)
          {
            paramm.a = 4;
            paramm.d = 0;
            break;
          }
          paramm.a = 2;
        }
      }
      else
      {
        if (paramm.d == 0) {
          if (f(7) == 0)
          {
            paramm.a = 1;
            localc = o[localg1.o[e(localg1.p)]];
            if (paramm.r == localc.c)
            {
              if (localc.d != 999) {
                localg2 = q[localc.d];
              } else {
                localg2 = q[localc.c];
              }
              paramm.v = localg2.c;
              paramm.w = localg2.d;
            }
            else
            {
              if (localc.c != 999) {
                localg2 = q[localc.c];
              } else {
                localg2 = q[localc.d];
              }
              paramm.v = localg2.c;
              paramm.w = localg2.d;
            }
            paramm.d = ((short)(byte)(f(15) + 20));
          }
          else
          {
            paramm.d = ((short)(byte)(f(15) + 2));
          }
        }
        if (paramm.a == 1) {
          a(paramm, paramm.v, paramm.w, 350, 200);
        }
        return;
      }
      break;
    case 2: 
      if (i1 != 0)
      {
        b(paramm, ((m)localObject1).n, ((m)localObject1).o, ((m)localObject1).p, (short)this.Q[ay]);
        i(paramm);
        if (paramm.d == 0)
        {
          if (f(7) == 0)
          {
            paramm.a = 4;
            paramm.d = 0;
            break;
          }
          if (f(1) == 0) {
            paramm.a = 3;
          } else {
            paramm.a = 5;
          }
          paramm.d = ((short)(byte)f(15));
        }
      }
      else if (f(3) != 0)
      {
        paramm.d = ((short)(byte)(f(31) + 10));
        paramm.a = 1;
        return;
      }
      break;
    case 3: 
      b(paramm, ((m)localObject1).n, ((m)localObject1).o, ((m)localObject1).p, (short)this.Q[ay]);
      paramm.b[0] = paramm.s[1];
      paramm.b[1] = (-paramm.s[0]);
      if (paramm.d == 0)
      {
        paramm.a = 2;
        paramm.d = ((short)(byte)(f(7) + 2));
        return;
      }
      break;
    case 4: 
      if (paramm.d == 0)
      {
        i1 = 0;
        for (i2 = 0; i2 < localg1.p; i2++)
        {
          if (((localc = o[localg1.o[i2]]).c != 999) && (localc.c != paramm.r))
          {
            localg2 = q[localc.c];
            aE.a = localg2.c;
            aE.b = localg2.d;
            aE.c = ((m)localObject1).p;
            dk.a = ((m)localObject1).n;
            dk.b = ((m)localObject1).o;
            dk.c = ((m)localObject1).p;
            if (!a(localc.c, ((m)localObject1).r))
            {
              paramm.v = localg2.c;
              paramm.w = localg2.d;
              i1 = 1;
              break;
            }
          }
          if ((localc.d != 999) && (localc.d != paramm.r))
          {
            localg2 = q[localc.d];
            aE.a = localg2.c;
            aE.b = localg2.d;
            aE.c = ((m)localObject1).p;
            dk.a = ((m)localObject1).n;
            dk.b = ((m)localObject1).o;
            dk.c = ((m)localObject1).p;
            if (!a(localc.d, ((m)localObject1).r))
            {
              paramm.v = localg2.c;
              paramm.w = localg2.d;
              i1 = 1;
              break;
            }
          }
        }
        if (i1 == 0)
        {
          if (f(1) == 0) {
            paramm.a = 3;
          } else {
            paramm.a = 5;
          }
          paramm.d = ((short)(byte)(f(15) + 2));
        }
        else
        {
          paramm.d = ((short)(byte)(f(31) + 14));
        }
      }
      else
      {
        a(paramm, paramm.v, paramm.w, 350, 200);
      }
      if (paramm.d < 2)
      {
        b(paramm, ((m)localObject1).n, ((m)localObject1).o, ((m)localObject1).p, (short)this.Q[ay]);
        paramm.a = 0;
        paramm.d = ((short)(byte)(f(3) + 5));
        return;
      }
      break;
    case 5: 
      b(paramm, ((m)localObject1).n, ((m)localObject1).o, ((m)localObject1).p, (short)this.Q[ay]);
      paramm.b[0] = (-paramm.s[1]);
      paramm.b[1] = paramm.s[0];
      if (paramm.d == 0)
      {
        paramm.a = 2;
        paramm.d = ((short)(byte)(f(7) + 2));
      }
      break;
    }
  }
  
  private static final void a(int paramInt1, int paramInt2, int paramInt3, byte paramByte, short paramShort)
  {
    if (dh >= 25) {
      return;
    }
    int[][] arrayOfInt = dg;
    int i1 = 0;
    dh += 1;
    for (;;)
    {
      if (arrayOfInt[i1][4] < 1)
      {
        arrayOfInt[i1][0] = paramInt1;
        arrayOfInt[i1][1] = paramInt2;
        arrayOfInt[i1][2] = paramInt3;
        arrayOfInt[i1][3] = paramByte;
        arrayOfInt[i1][4] = (dO[paramByte].length + 1);
        arrayOfInt[i1][5] = paramShort;
        return;
      }
      i1++;
    }
  }
  
  private static final void c(int paramInt)
  {
    bV = 240 + paramInt;
    ch[0][2] = bV;
    ch[1][1] = (-bV);
    ch[2][1] = bV;
    ch[3][0] = bV;
    ch[4][0] = (-bV);
    bW = bV << 16;
  }
  
  private final void h()
  {
    m localm = s[0];
    af = false;
    int i1 = localm.n;
    int i2 = localm.o;
    int i3 = localm.p;
    j[] arrayOfj = l;
    if (this.aO > 327680) {
      this.aL = 32768;
    }
    if (this.aO < 65536) {
      this.aL = 32768;
    }
    this.de += this.aL;
    if (this.de < -131072) {
      this.de = -131072;
    }
    if (this.de > 131072) {
      this.de = 131072;
    }
    this.aO += this.de;
    int i4 = this.aO - 196608;
    for (int i5 = bU - 1; i5 >= 0; i5--)
    {
      j localj;
      if ((localj = arrayOfj[i5]).u) {
        if (((localj.t > 0) && (localj.t < 12)) || (localj.t >= 120))
        {
          localj.q += 15;
          if (localj.q >= 360) {
            localj.q -= 360;
          }
          localj.o += i4;
          if (Math.abs(localj.m - i1) + Math.abs(localj.n - i2) + Math.abs(localj.o - i3) < 19005440) {
            b(localj);
          }
        }
        else
        {
          if (localj.t == 35)
          {
            localj.p += 28;
            if (localj.p >= 360) {
              localj.p -= 360;
            }
          }
          if (localj.t == 34)
          {
            localj.q += 28;
            if (localj.q >= 360) {
              localj.q -= 360;
            }
          }
        }
      }
    }
  }
  
  private static final void a(m paramm, boolean paramBoolean, e parame)
  {
    if (paramBoolean)
    {
      if (dN > 0)
      {
        dM = (byte)(Math.abs(dP.nextInt() & 0xF) + 30);
        m tmp36_35 = s[dN];
        tmp36_35.l = ((short)(tmp36_35.l - (byte)(Math.abs(dP.nextInt() & 0xF) + 10)));
        if (s[dN].l <= 0)
        {
          s[dN].r = s[0].r;
          s[dN].l = 0;
          s[dN].A = true;
          dN = -1;
        }
        return;
      }
      l();
      if (!al)
      {
        paramm.l = ((short)(paramm.l - 1));
        paramm.l = ((short)(paramm.l - ((Math.abs(parame.a - paramm.n) + Math.abs(parame.b - paramm.o) >> 16 >> 2 & 0x3) + 3)));
      }
      else
      {
        return;
      }
    }
    if (!paramBoolean)
    {
      if (paramm.y == 7) {
        return;
      }
      if ((paramm.y > 5) && (Math.abs(parame.c - (paramm.p + 8192000)) < 8355840)) {
        paramm.l = ((short)(paramm.l - 100));
      }
      if (Math.abs(parame.c - (paramm.p + 8192000)) < 5570560)
      {
        paramm.l = ((short)(paramm.l - 100));
      }
      else
      {
        int i1 = Math.abs(parame.a - paramm.n) + Math.abs(parame.b - paramm.o) >> 16 >> 1 & 0x3F;
        paramm.l = ((short)(paramm.l - (dD[dF] * i1 >> 6)));
        paramm.u = false;
        if (((paramm.y == 2) || (paramm.y == 3)) && (dF != 0) && (a(s[0], paramm))) {
          a(paramm, s[0].n, s[0].o, 350, 30);
        }
      }
    }
    if (paramm.l <= 0)
    {
      paramm.i = true;
      paramm.u = false;
      if (((dP.nextInt() & 0x3) == 0) || (paramBoolean)) {
        l(8);
      }
      paramm.l = 0;
      if (!paramBoolean)
      {
        if (paramm.y < 4) {
          paramm.x = 9;
        } else if (paramm.y == 4) {
          paramm.x = 10;
        } else {
          paramm.x = 2;
        }
        paramm.h = -1;
      }
    }
  }
  
  private static final void a(int paramInt1, int paramInt2, int paramInt3)
  {
    l(6);
    m[] arrayOfm = s;
    for (int i5 = dv - 1; i5 >= 0; i5--)
    {
      m localm;
      if ((!(localm = arrayOfm[i5]).i) && (localm.A) && (localm.y != 7))
      {
        int i2 = localm.n - paramInt1 >> 16;
        int i3 = localm.o - paramInt2 >> 16;
        int i4 = localm.p - paramInt3 >> 16;
        int i1 = i2 * i2 + i3 * i3 + i4 * i4;
        if (i5 == 0)
        {
          d(Math.abs(i2) + Math.abs(i3) + Math.abs(i4));
          if (al) {}
        }
        else if (i1 < 801025)
        {
          int i6 = 0;
          int i7 = 65536;
          while (i7 >>= 1 > 0) {
            if ((i6 + i7) * (i6 + i7) <= i1) {
              i6 += i7;
            }
          }
          if (localm.y == 6)
          {
            m tmp206_204 = localm;
            tmp206_204.l = ((short)(tmp206_204.l - (895 - i6 >> 2 << 1)));
          }
          else
          {
            m tmp230_228 = localm;
            tmp230_228.l = ((short)(tmp230_228.l - (895 - i6 >> 2)));
          }
          if (i5 == 0) {
            l();
          }
          if (localm.l <= 0)
          {
            localm.l = 0;
            localm.i = true;
            if (i5 != 0)
            {
              if (localm.y < 4) {
                localm.x = 9;
              } else if (localm.y == 4) {
                localm.x = 10;
              } else {
                localm.x = 2;
              }
              localm.h = -1;
              localm.u = false;
            }
            else
            {
              l(4);
            }
          }
          else if (i6 != 0)
          {
            i1 = i6;
            if (i6 > 160) {
              i1 = 160;
            }
            localm.e[0] += i2 * 65536 / i6 * i1;
            localm.e[1] += i3 * 65536 / i6 * i1;
            localm.e[2] += i4 * 65536 / i6 * i1;
            localm.c = true;
          }
        }
      }
    }
  }
  
  private static final void i()
  {
    int i2 = bR;
    m[] arrayOfm;
    m localm1;
    if ((localm1 = (arrayOfm = s)[i2]).i) {
      return;
    }
    int[] arrayOfInt = ap;
    for (int i1 = 1; i1 < dv; i1++)
    {
      m localm2;
      if ((!(localm2 = s[i1]).i) && (localm2.A) && (i1 != i2))
      {
        int i5 = localm1.n - localm2.n >> 16;
        int i6 = localm1.o - localm2.o >> 16;
        int i7 = localm1.p - localm2.p >> 16;
        int i8 = i5 * i5 + i6 * i6 + i7 * i7;
        if (19600 > i8)
        {
          int i3 = 0;
          int i4 = 65536;
          while (i4 >>= 1 > 0) {
            if ((i3 + i4) * (i3 + i4) <= i8) {
              i3 += i4;
            }
          }
          localm2.b[0] -= (int)((localm1.n - localm2.n) * arrayOfInt[i3] >> 16);
          localm2.b[1] -= (int)((localm1.o - localm2.o) * arrayOfInt[i3] >> 16);
        }
      }
    }
  }
  
  private static final void a(m paramm, int paramInt)
  {
    m localm = s[paramInt];
    int i1 = paramm.n - localm.n >> 16;
    int i2 = paramm.o - localm.o >> 16;
    int i3 = paramm.p - localm.p >> 16;
    int i4 = i1 * i1 + i2 * i2 + i3 * i3;
    if (19600 > i4)
    {
      int i5 = 0;
      int i6 = 65536;
      while (i6 >>= 1 > 0) {
        if ((i5 + i6) * (i5 + i6) <= i4) {
          i5 += i6;
        }
      }
      localm.n -= i1 * ap[i5] * (140 - i5);
      localm.o -= i2 * ap[i5] * (140 - i5);
      localm.p -= i3 * ap[i5] * (140 - i5);
    }
  }
  
  private final boolean f(m paramm)
  {
    j[] arrayOfj = l;
    if ((paramm.e[0] == 0) && (paramm.e[1] == 0) && (paramm.e[2] == 0)) {
      return false;
    }
    int i1 = paramm.n - paramm.e[0];
    int i2 = paramm.o - paramm.e[1];
    int i3 = paramm.p - paramm.e[2];
    int i4 = 0;
    boolean bool = false;
    for (int i5 = 0; i5 < bU; i5++)
    {
      j localj;
      if (((localj = arrayOfj[i5]).l) && (localj.u) && ((i4 = a(i1, i2, i3, paramm.n, paramm.o, paramm.p, localj.f + localj.m + 8192000, localj.g + localj.n + 8192000, localj.h + localj.o + 8192000, localj.i + localj.m - 8192000, localj.j + localj.n - 8192000, localj.k + localj.o - 8192000, paramm)) >= 0))
      {
        bool = true;
        paramm.e[i4] = 0;
      }
    }
    return bool;
  }
  
  private static final int a(int paramInt, e parame1, e parame2)
  {
    int i4 = -1;
    int[] arrayOfInt1 = aA;
    int[] arrayOfInt2 = q[paramInt].l;
    int[] arrayOfInt3 = q[paramInt].a;
    int[] arrayOfInt4 = j;
    for (int i7 = arrayOfInt2.length - 2; i7 >= 0; i7 -= 2)
    {
      int i5 = arrayOfInt2[i7];
      int i6 = arrayOfInt2[(i7 + 1)];
      int i1 = (int)((parame1.a - arrayOfInt3[i6] >> 16) * arrayOfInt4[i5] + (parame1.b - arrayOfInt3[(i6 + 1)] >> 16) * arrayOfInt4[(i5 + 1)] + (parame1.c - arrayOfInt3[(i6 + 2)] >> 16) * arrayOfInt4[(i5 + 2)] >> 16);
      int i2;
      int i3;
      long l1;
      long l2;
      if ((i3 = (i2 = (int)((parame2.a - arrayOfInt3[i6] >> 16) * arrayOfInt4[i5] + (parame2.b - arrayOfInt3[(i6 + 1)] >> 16) * arrayOfInt4[(i5 + 1)] + (parame2.c - arrayOfInt3[(i6 + 2)] >> 16) * arrayOfInt4[(i5 + 2)] >> 16)) - i1) > 0)
      {
        l1 = i2 * arrayOfInt1[i3];
        l2 = -i1 * arrayOfInt1[i3];
      }
      else
      {
        l1 = -i2 * arrayOfInt1[(-i3)];
        l2 = i1 * arrayOfInt1[(-i3)];
      }
      if (i2 <= 0)
      {
        parame2.a = ((int)(parame1.a * l1 + parame2.a * l2 >> 18));
        parame2.b = ((int)(parame1.b * l1 + parame2.b * l2 >> 18));
        parame2.c = ((int)(parame1.c * l1 + parame2.c * l2 >> 18));
        i4 = i7;
      }
    }
    return i4;
  }
  
  private final boolean b(m paramm, int paramInt)
  {
    int[] arrayOfInt1 = paramm.e;
    int[] arrayOfInt2 = dw;
    boolean bool = false;
    if ((paramm.r == 7) || (paramm.r == 11)) {
      paramm.r = paramm.r;
    }
    int[] arrayOfInt4 = q[paramm.r].a;
    int[] arrayOfInt3 = q[paramm.r].l;
    int[] arrayOfInt5 = j;
    long l1;
    for (int i6 = arrayOfInt3.length - 2; tmp202_201 >= 0; tmp202_201 -= 2)
    {
      int i1 = arrayOfInt3[i6];
      int i3 = arrayOfInt5[i1];
      int i4 = arrayOfInt5[(i1 + 1)];
      int i5 = arrayOfInt5[(i1 + 2)];
      int i2 = arrayOfInt3[(i6 + 1)];
      if ((l1 = i3 * (paramm.n - arrayOfInt4[i2]) + i4 * (paramm.o - arrayOfInt4[(i2 + 1)]) + i5 * (paramm.p - arrayOfInt4[(i2 + 2)]) >> 16) < 8192000L)
      {
        if (i5 > 0) {
          bool = true;
        }
        long l2 = 8192000L - l1;
        m tmp202_201 = paramm;
        tmp202_201.n = ((int)(tmp202_201.n + (i3 * l2 >> 16)));
        m tmp222_221 = paramm;
        tmp222_221.o = ((int)(tmp222_221.o + (i4 * l2 >> 16)));
        m tmp242_241 = paramm;
        tmp242_241.p = ((int)(tmp242_241.p + (i5 * l2 >> 16)));
        l1 = i3 * arrayOfInt2[0] + i4 * arrayOfInt2[1] + i5 * arrayOfInt2[2] >> 16;
        int tmp298_297 = 0;
        int[] tmp298_295 = arrayOfInt2;
        tmp298_295[tmp298_297] = ((int)(tmp298_295[tmp298_297] - (i3 * l1 >> 16)));
        int tmp316_315 = 1;
        int[] tmp316_313 = arrayOfInt2;
        tmp316_313[tmp316_315] = ((int)(tmp316_313[tmp316_315] - (i4 * l1 >> 16)));
        int tmp334_333 = 2;
        int[] tmp334_331 = arrayOfInt2;
        tmp334_331[tmp334_333] = ((int)(tmp334_331[tmp334_333] - (i5 * l1 >> 16)));
        arrayOfInt2[0] *= paramInt;
        arrayOfInt2[1] *= paramInt;
        arrayOfInt2[2] *= paramInt;
      }
    }
    if (ci)
    {
      int[] arrayOfInt6;
      if (((arrayOfInt6 = n)[3] > paramm.n) && (arrayOfInt6[5] < paramm.n) && (arrayOfInt6[4] > paramm.o) && (arrayOfInt6[6] < paramm.o) && ((l1 = paramm.p - arrayOfInt6[2]) < 8192000L))
      {
        m tmp460_459 = paramm;
        tmp460_459.p = ((int)(tmp460_459.p + (8192000L - l1)));
        arrayOfInt1[2] = 0;
        bool = true;
      }
      if ((bM == 4) && (paramm.y > 0) && (227737600 < paramm.o)) {
        paramm.o = 227737600;
      }
    }
    if (f(paramm)) {
      bool = true;
    }
    return bool;
  }
  
  private static void c(m paramm, int paramInt)
  {
    int[] arrayOfInt1 = j;
    int[] arrayOfInt2 = q[paramInt].l;
    int[] arrayOfInt3 = q[paramInt].a;
    for (int i3 = arrayOfInt2.length - 2; i3 >= 0; i3 -= 2)
    {
      int i1 = arrayOfInt2[i3];
      int i2 = arrayOfInt2[(i3 + 1)];
      long l1;
      if ((l1 = arrayOfInt1[i1] * (paramm.n - arrayOfInt3[i2]) + arrayOfInt1[(i1 + 1)] * (paramm.o - arrayOfInt3[(i2 + 1)]) + arrayOfInt1[(i1 + 2)] * (paramm.p - arrayOfInt3[(i2 + 2)]) >> 16) < 8192000L)
      {
        long l2 = 8192000L - l1;
        paramm.n = ((int)(paramm.n + (arrayOfInt1[i1] * l2 >> 16)));
        paramm.o = ((int)(paramm.o + (arrayOfInt1[(i1 + 1)] * l2 >> 16)));
        paramm.p = ((int)(paramm.p + (arrayOfInt1[(i1 + 2)] * l2 >> 16)));
      }
    }
  }
  
  private static byte a(int paramInt1, int paramInt2, int paramInt3, int paramInt4, int paramInt5, int paramInt6, int paramInt7, int paramInt8, int paramInt9, int paramInt10, int paramInt11, int paramInt12, m paramm)
  {
    int[] arrayOfInt = aA;
    byte b1 = -1;
    int i1 = paramInt7 - paramInt1 >> 16;
    int i2;
    long l1;
    long l2;
    int i3;
    int i4;
    int i5;
    if (((i2 = paramInt7 - paramInt4 >> 16) >= 0) && (i1 <= 0))
    {
      if (i2 - i1 > 0)
      {
        l1 = i2 * arrayOfInt[(i2 - i1)];
        l2 = -i1 * arrayOfInt[(i2 - i1)];
      }
      else
      {
        l1 = -i2 * arrayOfInt[(i1 - i2)];
        l2 = i1 * arrayOfInt[(i1 - i2)];
      }
      i3 = (int)(paramInt1 * l1 + paramInt4 * l2 >> 18);
      i4 = (int)(paramInt2 * l1 + paramInt5 * l2 >> 18);
      i5 = (int)(paramInt3 * l1 + paramInt6 * l2 >> 18);
      if ((paramInt11 <= i4) && (paramInt12 <= i5) && (paramInt8 >= i4) && (paramInt9 >= i5))
      {
        if ((l1 == l2) && (l1 == 0L)) {
          paramInt4 = paramInt7 + 65536;
        } else {
          paramInt4 = i3 + 65536;
        }
        b1 = 0;
      }
    }
    i1 = paramInt8 - paramInt2 >> 16;
    if (((i2 = paramInt8 - paramInt5 >> 16) >= 0) && (i1 <= 0))
    {
      if (i2 - i1 > 0)
      {
        l1 = i2 * arrayOfInt[(i2 - i1)];
        l2 = -i1 * arrayOfInt[(i2 - i1)];
      }
      else
      {
        l1 = -i2 * arrayOfInt[(i1 - i2)];
        l2 = i1 * arrayOfInt[(i1 - i2)];
      }
      i3 = (int)(paramInt1 * l1 + paramInt4 * l2 >> 18);
      i4 = (int)(paramInt2 * l1 + paramInt5 * l2 >> 18);
      i5 = (int)(paramInt3 * l1 + paramInt6 * l2 >> 18);
      if ((paramInt10 <= i3) && (paramInt12 <= i5) && (paramInt7 >= i3) && (paramInt9 >= i5))
      {
        if ((l1 == l2) && (l1 == 0L)) {
          paramInt4 = paramInt8 + 65536;
        } else {
          paramInt5 = i4 + 65536;
        }
        b1 = 1;
      }
    }
    i1 = paramInt1 - paramInt10 >> 16;
    if (((i2 = paramInt4 - paramInt10 >> 16) >= 0) && (i1 <= 0))
    {
      if (i2 - i1 > 0)
      {
        l1 = i2 * arrayOfInt[(i2 - i1)];
        l2 = -i1 * arrayOfInt[(i2 - i1)];
      }
      else
      {
        l1 = -i2 * arrayOfInt[(i1 - i2)];
        l2 = i1 * arrayOfInt[(i1 - i2)];
      }
      i3 = (int)(paramInt1 * l1 + paramInt4 * l2 >> 18);
      i4 = (int)(paramInt2 * l1 + paramInt5 * l2 >> 18);
      i5 = (int)(paramInt3 * l1 + paramInt6 * l2 >> 18);
      if ((paramInt11 <= i4) && (paramInt12 <= i5) && (paramInt8 >= i4) && (paramInt9 >= i5))
      {
        if ((l1 == l2) && (l1 == 0L)) {
          paramInt4 = paramInt7 - 65536;
        } else {
          paramInt4 = i3 - 65536;
        }
        b1 = 0;
      }
    }
    i1 = paramInt2 - paramInt11 >> 16;
    if (((i2 = paramInt5 - paramInt11 >> 16) >= 0) && (i1 <= 0))
    {
      if (i2 - i1 > 0)
      {
        l1 = i2 * arrayOfInt[(i2 - i1)];
        l2 = -i1 * arrayOfInt[(i2 - i1)];
      }
      else
      {
        l1 = -i2 * arrayOfInt[(i1 - i2)];
        l2 = i1 * arrayOfInt[(i1 - i2)];
      }
      i3 = (int)(paramInt1 * l1 + paramInt4 * l2 >> 18);
      i4 = (int)(paramInt2 * l1 + paramInt5 * l2 >> 18);
      i5 = (int)(paramInt3 * l1 + paramInt6 * l2 >> 18);
      if ((paramInt10 <= i3) && (paramInt12 <= i5) && (paramInt7 >= i3) && (paramInt9 >= i5))
      {
        if ((l1 == l2) && (l1 == 0L)) {
          paramInt4 = paramInt11 - 65536;
        } else {
          paramInt5 = i4 - 65536;
        }
        b1 = 1;
      }
    }
    i1 = paramInt3 - paramInt12 >> 16;
    if (((i2 = paramInt6 - paramInt12 >> 16) >= 0) && (i1 <= 0))
    {
      if (i2 - i1 > 0)
      {
        l1 = i2 * arrayOfInt[(i2 - i1)];
        l2 = -i1 * arrayOfInt[(i2 - i1)];
      }
      else
      {
        l1 = -i2 * arrayOfInt[(i1 - i2)];
        l2 = i1 * arrayOfInt[(i1 - i2)];
      }
      i3 = (int)(paramInt1 * l1 + paramInt4 * l2 >> 18);
      i4 = (int)(paramInt2 * l1 + paramInt5 * l2 >> 18);
      i5 = (int)(paramInt3 * l1 + paramInt6 * l2 >> 18);
      if ((paramInt10 <= i3) && (paramInt11 <= i4) && (paramInt7 >= i3) && (paramInt8 >= i4))
      {
        if ((l1 == l2) && (l1 == 0L)) {
          paramInt4 = paramInt12 - 65536;
        } else {
          paramInt6 = i5 - 65536;
        }
        b1 = 2;
      }
    }
    i1 = paramInt9 - paramInt3 >> 16;
    if (((i2 = paramInt9 - paramInt6 >> 16) >= 0) && (i1 <= 0))
    {
      if (i2 - i1 > 0)
      {
        l1 = i2 * arrayOfInt[(i2 - i1)];
        l2 = -i1 * arrayOfInt[(i2 - i1)];
      }
      else
      {
        l1 = -i2 * arrayOfInt[(i1 - i2)];
        l2 = i1 * arrayOfInt[(i1 - i2)];
      }
      i3 = (int)(paramInt1 * l1 + paramInt4 * l2 >> 18);
      i4 = (int)(paramInt2 * l1 + paramInt5 * l2 >> 18);
      i5 = (int)(paramInt3 * l1 + paramInt6 * l2 >> 18);
      if ((paramInt10 <= i3) && (paramInt11 <= i4) && (paramInt7 >= i3) && (paramInt8 >= i4))
      {
        if ((l1 == l2) && (l1 == 0L)) {
          paramInt4 = paramInt12 + 65536;
        } else {
          paramInt6 = i5 + 65536;
        }
        b1 = 2;
      }
    }
    paramm.n = paramInt4;
    paramm.o = paramInt5;
    paramm.p = paramInt6;
    return b1;
  }
  
  private final void j()
  {
    try
    {
      this.bt = null;
      int i1 = 0;
      this.bt = f.a(f.a(y) + f.a(u));
      if (this.bt == null)
      {
        this.an = false;
        return;
      }
      this.aV = f.a(f.a(z) + f.a(u));
      this.bY = f.a(f.a(L));
      this.bs = 0;
      m();
      Thread.sleep(5000L);
      this.bs = 0;
    }
    catch (Exception localException1)
    {
      this.an = false;
      return;
    }
    try
    {
      Y = 2;
      this.bt = null;
      String str = f.a(M);
      try
      {
        this.bt = f.a(str);
      }
      catch (Exception localException2) {}
      try
      {
        this.aV = f.a("nl");
      }
      catch (Exception localException3)
      {
        this.an = false;
        return;
      }
      if (this.aV == null)
      {
        this.an = false;
        return;
      }
      try
      {
        this.bY = f.a("or_f");
      }
      catch (Exception localException4) {}
      this.bs = 8;
      while (this.bs > 0)
      {
        m();
        this.bs = ((byte)(this.bs - 1));
        Thread.sleep(77L);
      }
      Y = 3;
      this.bs = 4;
      while (this.bs > 0)
      {
        m();
        this.bs = ((byte)(this.bs - 1));
        Thread.sleep(77L);
      }
      Y = 4;
      this.be = 0;
      while (this.be != 53)
      {
        if (this.bs == -1) {
          this.bs = -2;
        } else {
          this.bs = -1;
        }
        m();
        Thread.sleep(300L);
      }
      return;
    }
    catch (Exception localException5)
    {
      this.bt = null;
      this.aV = null;
      this.bY = null;
      Y = -1;
    }
  }
  
  private final void k()
  {
    A();
    ac();
    m localm2 = s[0];
    m[] arrayOfm = s;
    bR = (byte)(bR + 1);
    if (bR >= dv) {
      if (dv > 1) {
        bR = 1;
      } else {
        bR = 0;
      }
    }
    if (dN > 0)
    {
      arrayOfm[dN].n = localm2.n;
      arrayOfm[dN].o = localm2.o;
      arrayOfm[dN].p = localm2.p;
      if (dM > 0)
      {
        dM = (byte)(dM - 5);
        if (dM < 0) {
          dM = 0;
        }
      }
    }
    G();
    i();
    for (int i1 = dv - 1; i1 >= 0; i1--)
    {
      if (localm2.i) {
        break;
      }
      m localm1;
      if (!(localm1 = arrayOfm[i1]).i)
      {
        if (localm1.q > 0)
        {
          m tmp174_173 = localm1;
          tmp174_173.q = ((byte)(tmp174_173.q - 1));
        }
        aU = (short)i1;
        if ((!aD) && (i1 > 0)) {
          a(localm1);
        }
        h(s[i1]);
        if ((i1 != 0) && (arrayOfm[i1].A)) {
          a(localm1, 0);
        }
      }
    }
    s();
    ah();
    n();
    h();
    if (aD)
    {
      ae();
      v();
    }
    else
    {
      if (this.W > 0) {
        this.W = ((byte)(this.W - 1));
      }
      aa();
      t();
      if (ae > 0)
      {
        ae = (byte)(ae - 1);
        if (ae == 4) {
          dF = dC;
        }
      }
    }
    if (aD) {
      ae = 4;
    }
    o();
    if (ci) {
      F();
    }
    du = false;
    cj = false;
    if (s[0].i)
    {
      if (dG < 255)
      {
        dG = (short)(dG + 5);
        cA -= 2;
        if (cA < 0) {
          cA = 0;
        }
      }
      if (dG > 254) {
        dG = 254;
      }
      if (ax) {
        h.D -= 65557L;
      }
    }
  }
  
  private static final void l()
  {
    g();
    cA += 20 - e(40);
    if (cA < -30) {
      cA = -30;
    }
    if (cA > 30) {
      cA = 30;
    }
    g = 0;
    c(g);
  }
  
  private static final void d(int paramInt)
  {
    p = (short)(40 - (paramInt >> 6));
    if (p < 0) {
      p = 0;
    }
  }
  
  private static final int e(int paramInt)
  {
    return Math.abs(dP.nextInt() % paramInt);
  }
  
  private static final int f(int paramInt)
  {
    return Math.abs(dP.nextInt() & paramInt);
  }
  
  private void m()
  {
    Object localObject1 = null;
    long l5 = 0L;
    Object localObject2 = null;
    l5 = h._n();
    long l1 = l5;
    if (!this.m)
    {
      k();
      a(cl, cv);
      a(aC);
    }
    repaint();
    serviceRepaints();
    localObject1 = null;
    l5 = 0L;
    localObject2 = null;
    l5 = h._n();
    long l2 = l5;
    this.bZ = (l2 - l1);
    long l3 = l2 - l1;
    long l4 = this.dj;
    if (l3 < l4) {
      try
      {
        Thread.sleep(l4 - l3);
        return;
      }
      catch (Exception localException) {}
    }
  }
  
  private static void n()
  {
    int[][] arrayOfInt = cR;
    int[] arrayOfInt3 = ap;
    e locale1 = dk;
    e locale2 = aE;
    int i12 = 0;
    int[] arrayOfInt4 = j;
    for (int i1 = 19; i1 >= 0; i1--)
    {
      int[] arrayOfInt1;
      if ((arrayOfInt1 = arrayOfInt[i1])[6] != 0)
      {
        arrayOfInt1[6] -= 1;
        if (arrayOfInt1[9] > 1)
        {
          if ((arrayOfInt1[6] & 0x1) == 0) {
            a(arrayOfInt1[0], arrayOfInt1[1], arrayOfInt1[2], (byte)8, (short)arrayOfInt1[7]);
          }
          arrayOfInt1[0] += arrayOfInt1[3] * 100;
          arrayOfInt1[1] += arrayOfInt1[4] * 100;
          arrayOfInt1[2] += arrayOfInt1[5] * 100;
          arrayOfInt1[9] = (11 - arrayOfInt1[9]);
        }
        if ((arrayOfInt1[6] == 0) || ((arrayOfInt1[9] > 1) && (arrayOfInt1[2] < 0)))
        {
          cT -= 1;
          if (arrayOfInt1[2] < 0) {
            arrayOfInt1[2] = 8192000;
          }
          a(arrayOfInt1[0], arrayOfInt1[1], arrayOfInt1[2], (byte)0, (short)arrayOfInt1[7]);
          a(arrayOfInt1[0], arrayOfInt1[1], arrayOfInt1[2]);
          arrayOfInt1[6] = 0;
        }
        else if (arrayOfInt1[9] <= 1)
        {
          int i13 = arrayOfInt1[7];
          int i5 = arrayOfInt1[3] * arrayOfInt1[8];
          int i6 = arrayOfInt1[4] * arrayOfInt1[8];
          int i7 = (i7 = arrayOfInt1[5] * arrayOfInt1[8]) - 524288;
          int i8 = i5 >> 16;
          int i9 = i6 >> 16;
          int i10 = i7 >> 16;
          int i11 = i8 * i8 + i9 * i9 + i10 * i10;
          int i3 = 0;
          int i4 = 65536;
          while (i4 >>= 1 > 0) {
            if ((i3 + i4) * (i3 + i4) <= i11) {
              i3 += i4;
            }
          }
          int i14 = arrayOfInt3[i3];
          arrayOfInt1[3] = ((int)(i5 * i14 >> 16));
          arrayOfInt1[4] = ((int)(i6 * i14 >> 16));
          arrayOfInt1[5] = ((int)(i7 * i14 >> 16));
          if (i3 > 160) {
            arrayOfInt1[8] = 160;
          } else {
            arrayOfInt1[8] = i3;
          }
          locale1.a = arrayOfInt1[0];
          locale1.b = arrayOfInt1[1];
          locale1.c = arrayOfInt1[2];
          i14 = arrayOfInt1[8];
          locale2.a = (arrayOfInt1[0] + arrayOfInt1[3] * i14);
          locale2.b = (arrayOfInt1[1] + arrayOfInt1[4] * i14);
          locale2.c = (arrayOfInt1[2] + arrayOfInt1[5] * i14);
          i12 = -1;
          for (;;)
          {
            if ((i4 = b(i13, locale1, locale2)) != -1)
            {
              switch (i4)
              {
              case 1: 
                arrayOfInt1[3] = (-arrayOfInt1[3]);
                break;
              case 2: 
                arrayOfInt1[4] = (-arrayOfInt1[4]);
                break;
              case 3: 
                arrayOfInt1[5] = (-arrayOfInt1[5]);
              }
              arrayOfInt1[8] >>= 2;
              break label689;
            }
            if ((i12 = a(i13, locale1, locale2, i12)) == -1) {
              break;
            }
            if (o[i12].c == i13)
            {
              if (o[i12].d != 999) {
                i13 = o[i12].d;
              }
            }
            else if (o[i12].c != 999) {
              i13 = o[i12].c;
            }
          }
          arrayOfInt1[7] = i13;
          label689:
          g localg;
          int[] arrayOfInt2 = (localg = q[i13]).l;
          int[] arrayOfInt5 = localg.a;
          for (int i2 = arrayOfInt2.length - 2; i2 >= 0; i2 -= 2)
          {
            int i15 = arrayOfInt2[i2];
            int i16 = arrayOfInt2[(i2 + 1)];
            long l1;
            if ((l1 = (locale2.a - arrayOfInt5[i16]) * arrayOfInt4[i15] + (locale2.b - arrayOfInt5[(i16 + 1)]) * arrayOfInt4[(i15 + 1)] + (locale2.c - arrayOfInt5[(i16 + 2)]) * arrayOfInt4[(i15 + 2)] >> 16) <= 0L)
            {
              e tmp813_811 = locale2;
              tmp813_811.a = ((int)(tmp813_811.a + -(l1 >> 16) * tmp813_811[i15]));
              e tmp838_836 = locale2;
              tmp838_836.b = ((int)(tmp838_836.b + -(l1 >> 16) * tmp813_811[(i15 + 1)]));
              e tmp865_863 = locale2;
              tmp865_863.c = ((int)(tmp865_863.c + -(l1 >> 16) * tmp813_811[(i15 + 2)]));
              l1 = tmp813_811[i15] * arrayOfInt1[3] + tmp813_811[(i15 + 1)] * arrayOfInt1[4] + tmp813_811[(i15 + 2)] * arrayOfInt1[5] >> 16 << 1;
              int tmp938_937 = 3;
              int[] tmp938_936 = arrayOfInt1;
              tmp938_936[tmp938_937] = ((int)(tmp938_936[tmp938_937] - (tmp813_811[i15] * l1 >> 16)));
              int tmp958_957 = 4;
              int[] tmp958_956 = arrayOfInt1;
              tmp958_956[tmp958_957] = ((int)(tmp958_956[tmp958_957] - (tmp813_811[(i15 + 1)] * l1 >> 16)));
              int tmp980_979 = 5;
              int[] tmp980_978 = arrayOfInt1;
              tmp980_978[tmp980_979] = ((int)(tmp980_978[tmp980_979] - (tmp813_811[(i15 + 2)] * l1 >> 16)));
              arrayOfInt1[8] >>= 2;
            }
          }
          arrayOfInt1[0] = locale2.a;
          arrayOfInt1[1] = locale2.b;
          arrayOfInt1[2] = locale2.c;
        }
      }
    }
  }
  
  private static void o()
  {
    int[][] arrayOfInt = dg;
    int i1 = 0;
    int i2 = 0;
    while (i1 < dh) {
      if (arrayOfInt[i2][4] < 1)
      {
        i2++;
      }
      else
      {
        arrayOfInt[i2][4] -= 1;
        if (arrayOfInt[i2][4] < 1)
        {
          dh -= 1;
        }
        else
        {
          i1++;
          i2++;
        }
      }
    }
  }
  
  private static final int a(int paramInt, e parame1, e parame2, m paramm, boolean paramBoolean)
  {
    e locale;
    (locale = bg).a = parame2.a;
    locale.b = parame2.b;
    locale.c = parame2.c;
    j[] arrayOfj = l;
    m[] arrayOfm = s;
    int i1 = -1;
    int i2 = q[paramInt].e;
    int i3 = -1;
    int i4 = 0;
    j localj;
    for (int i5 = q[paramInt].q; i5 < i2; i5++) {
      if ((localj = arrayOfj[i5]).u) {
        if (i1 == -1)
        {
          if ((i1 = a(locale, parame1, parame2, localj.f + localj.m, localj.g + localj.n, localj.h + localj.o, localj.i + localj.m, localj.j + localj.n, localj.k + localj.o)) != -1) {
            i3 = i5;
          }
        }
        else if (a(locale, parame1, parame2, localj.f + localj.m, localj.g + localj.n, localj.h + localj.o, localj.i + localj.m, localj.j + localj.n, localj.k + localj.o) != -1) {
          i3 = i5;
        }
      }
    }
    if (bM == 10)
    {
      localj = arrayOfj[10];
      if (i1 == -1)
      {
        if ((i1 = a(locale, parame1, parame2, localj.m + 29491200, localj.n + 29491200, localj.o + 29491200, localj.m - 29491200, localj.n - 29491200, localj.o - 29491200)) != -1) {
          i3 = 10;
        }
      }
      else if (a(locale, parame1, parame2, localj.m + 29491200, localj.n + 29491200, localj.o + 29491200, localj.m - 29491200, localj.n - 29491200, localj.o - 29491200) != -1) {
        i3 = 10;
      }
    }
    for (int i6 = dv - 1; i6 >= 0; i6--)
    {
      m localm;
      if ((!(localm = arrayOfm[i6]).i) && (localm.r == paramInt) && (aU != i6) && (localm.A) && (paramm.y != localm.y)) {
        if (i1 == -1)
        {
          if ((i1 = a(locale, parame1, parame2, localm.n + 2621440, localm.o + 2621440, localm.p + 4915200, localm.n - 2621440, localm.o - 2621440, localm.p - 8192000)) != -1)
          {
            i3 = i6;
            i4 = 1;
          }
        }
        else if (a(locale, parame1, parame2, localm.n + 2621440, localm.o + 2621440, localm.p + 4915200, localm.n - 2621440, localm.o - 2621440, localm.p - 8192000) != -1)
        {
          i3 = i6;
          i4 = 1;
        }
      }
    }
    if ((paramBoolean) && (i1 != -1)) {
      if (i4 != 0)
      {
        aU = (short)(byte)i3;
        if (arrayOfm[i3].y != 7) {
          a(locale.a, locale.b, locale.c, (byte)(e(4) + 2), (short)paramInt);
        }
        if (i3 == 0)
        {
          a(arrayOfm[i3], true, locale);
        }
        else
        {
          a(arrayOfm[i3], false, locale);
          if (dF == 5)
          {
            a(locale.a, locale.b, locale.c, (byte)0, (short)paramInt);
            a(locale.a, locale.b, locale.c);
          }
        }
      }
      else
      {
        if (arrayOfj[i3].t == 50) {
          arrayOfj[i3].f -= (dD[dF] >> 1);
        }
        if (dF == 5) {
          a(locale.a, locale.b, locale.c, (byte)0, (short)paramInt);
        } else {
          a(locale.a, locale.b, locale.c, (byte)1, (short)paramInt);
        }
      }
    }
    parame2.a = locale.a;
    parame2.b = locale.b;
    parame2.c = locale.c;
    return i1;
  }
  
  private static final int b(int paramInt, e parame1, e parame2)
  {
    e locale;
    (locale = bg).a = parame2.a;
    locale.b = parame2.b;
    locale.c = parame2.c;
    j[] arrayOfj = l;
    int i1 = -1;
    int i2 = 0;
    int i3 = q[paramInt].e;
    for (int i4 = q[paramInt].q; i4 < i3; i4++)
    {
      j localj;
      if (((localj = arrayOfj[i4]).u) && ((i2 = a(locale, parame1, parame2, localj.f + localj.m, localj.g + localj.n, localj.h + localj.o, localj.i + localj.m, localj.j + localj.n, localj.k + localj.o)) != -1)) {
        i1 = i2;
      }
    }
    parame2.a = locale.a;
    parame2.b = locale.b;
    parame2.c = locale.c;
    return i1;
  }
  
  private static final int a(int paramInt1, e parame1, e parame2, int paramInt2)
  {
    c[] arrayOfc = o;
    int[] arrayOfInt1 = q[paramInt1].o;
    int i1 = q[paramInt1].p;
    int[] arrayOfInt2 = aA;
    int i2 = 0;
    int i3 = 0;
    int i7 = 0;
    int i8 = 0;
    int i9 = 0;
    int i10 = 0;
    int i11 = 0;
    int i12 = 0;
    for (int i13 = 0; i13 < i1; i13++) {
      if (arrayOfInt1[i13] != paramInt2)
      {
        c localc;
        l[] arrayOfl;
        l locall = (arrayOfl = (localc = arrayOfc[arrayOfInt1[i13]]).b)[0];
        switch (localc.a)
        {
        case 1: 
          i2 = parame1.a - locall.j >> 16;
          i3 = parame2.a - locall.j >> 16;
          i8 = Math.max(locall.k, Math.max(arrayOfl[1].k, arrayOfl[2].k));
          i11 = Math.min(locall.k, Math.min(arrayOfl[1].k, arrayOfl[2].k));
          i9 = Math.max(locall.l, Math.max(arrayOfl[1].l, arrayOfl[2].l));
          i12 = Math.min(locall.l, Math.min(arrayOfl[1].l, arrayOfl[2].l));
          break;
        case 2: 
          i2 = parame1.b - locall.k >> 16;
          i3 = parame2.b - locall.k >> 16;
          i7 = Math.max(locall.j, Math.max(arrayOfl[1].j, arrayOfl[2].j));
          i10 = Math.min(locall.j, Math.min(arrayOfl[1].j, arrayOfl[2].j));
          i9 = Math.max(locall.l, Math.max(arrayOfl[1].l, arrayOfl[2].l));
          i12 = Math.min(locall.l, Math.min(arrayOfl[1].l, arrayOfl[2].l));
          break;
        case 3: 
          i2 = parame1.c - locall.l >> 16;
          i3 = parame2.c - locall.l >> 16;
          i7 = Math.max(locall.j, Math.max(arrayOfl[1].j, arrayOfl[2].j));
          i10 = Math.min(locall.j, Math.min(arrayOfl[1].j, arrayOfl[2].j));
          i8 = Math.max(locall.k, Math.max(arrayOfl[1].k, arrayOfl[2].k));
          i11 = Math.min(locall.k, Math.min(arrayOfl[1].k, arrayOfl[2].k));
        }
        if (((i3 >= 0) && (i2 <= 0)) || ((i2 >= 0) && (i3 <= 0)))
        {
          long l1;
          long l2;
          if (i3 - i2 > 0)
          {
            l1 = i3 * arrayOfInt2[(i3 - i2)];
            l2 = -i2 * arrayOfInt2[(i3 - i2)];
          }
          else
          {
            l1 = -i3 * arrayOfInt2[(i2 - i3)];
            l2 = i2 * arrayOfInt2[(i2 - i3)];
          }
          int i4 = (int)(parame1.a * l1 + parame2.a * l2 >> 18);
          int i5 = (int)(parame1.b * l1 + parame2.b * l2 >> 18);
          int i6 = (int)(parame1.c * l1 + parame2.c * l2 >> 18);
          switch (localc.a)
          {
          case 1: 
            if ((i12 <= i6) && (i11 <= i5) && (i9 >= i6) && (i8 >= i5))
            {
              parame1.a = i4;
              parame1.b = i5;
              parame1.c = i6;
              return arrayOfInt1[i13];
            }
            break;
          case 2: 
            if ((i12 <= i6) && (i10 <= i4) && (i9 >= i6) && (i7 >= i4))
            {
              parame1.a = i4;
              parame1.b = i5;
              parame1.c = i6;
              return arrayOfInt1[i13];
            }
            break;
          case 3: 
            if ((i10 <= i4) && (i11 <= i5) && (i7 >= i4) && (i8 >= i5))
            {
              parame1.a = i4;
              parame1.b = i5;
              parame1.c = i6;
              return arrayOfInt1[i13];
            }
            break;
          }
        }
      }
    }
    return -1;
  }
  
  private static final void p()
  {
    m[] arrayOfm = s;
    for (int i1 = 1; i1 < dv; i1++) {
      arrayOfm[i1].A = true;
    }
  }
  
  private static final void a(boolean paramBoolean1, boolean paramBoolean2)
  {
    m[] arrayOfm = s;
    for (int i1 = 1; i1 < dv; i1++)
    {
      arrayOfm[i1].u = paramBoolean1;
      arrayOfm[i1].A = paramBoolean2;
    }
  }
  
  private static final void a(int paramInt, boolean paramBoolean1, boolean paramBoolean2)
  {
    s[paramInt].u = paramBoolean1;
    s[paramInt].A = paramBoolean2;
  }
  
  private void q()
  {
    G();
    for (int i1 = 0; i1 < dv; i1++) {
      h(s[i1]);
    }
    s();
    a(cl, cv);
    a(aC);
  }
  
  private static byte r()
  {
    m[] arrayOfm;
    m localm = (arrayOfm = s)[0];
    int i1 = 0;
    int i2 = 0;
    byte b1 = 0;
    int i3 = 0;
    for (int i4 = 1; i4 < dv; i4++)
    {
      if ((!arrayOfm[i4].i) && (X[i4] >= 1) && (arrayOfm[i4].y != 6) && (arrayOfm[i4].y > 1))
      {
        i1 = Math.abs(arrayOfm[i4].n - localm.n) + Math.abs(arrayOfm[i4].o - localm.o) + Math.abs(arrayOfm[i4].p - localm.p);
        if (i3 == 0)
        {
          i2 = i1;
          b1 = X[i4];
          i3 = 1;
        }
        else if (i1 < i2)
        {
          i2 = i1;
          b1 = X[i4];
        }
      }
      X[i4] = 0;
    }
    return b1;
  }
  
  private static void s()
  {
    m[] arrayOfm = s;
    byte[][] arrayOfByte1 = V;
    byte[][] arrayOfByte2 = bQ;
    int i6 = cF[0];
    int i7 = cF[1];
    for (int i9 = dv - 1; i9 > 0; i9--)
    {
      m localm;
      (localm = arrayOfm[i9]).k = false;
      if ((localm.g) && (localm.y != 7))
      {
        int i8;
        if ((localm.b[0] == 0) && (localm.b[1] == 0) && (localm.b[2] == 0)) {
          i8 = 0;
        } else {
          i8 = 4;
        }
        if (!localm.i) {
          if (localm.y < 5)
          {
            int i1 = i6 - localm.n >> 16;
            int i2 = i7 - localm.o >> 16;
            int i5 = i1 * i1 + i2 * i2;
            int i4 = 0;
            int i3 = 65536;
            while (i3 >>= 1 > 0) {
              if ((i4 + i3) * (i4 + i3) <= i5) {
                i4 += i3;
              }
            }
            if (i4 == 0) {
              i4 = 1;
            }
            i1 = i1 * 65536 / i4;
            i2 = i2 * 65536 / i4;
            if ((i3 = (int)(localm.s[0] * i1 + localm.s[1] * i2 >> 16)) < 0) {
              i5 = 1;
            } else {
              i5 = 0;
            }
            if ((i3 <= 46341) && (i3 >= -46341))
            {
              i3 = (int)(localm.s[0] * i2 + -localm.s[1] * i1 >> 16);
              i5 = 3;
              if (i3 < 0)
              {
                localm.k = true;
                i5 = 2;
              }
            }
            if (localm.y == 4) {
              i5++;
            }
            localm.x = ((byte)(i5 + i8));
            if (localm.q == cs[ay])
            {
              if (localm.x == 0) {
                localm.x = 8;
              }
              if (localm.y == 4) {
                localm.x = 9;
              }
            }
          }
          else
          {
            localm.x = 0;
            if (i8 > 0) {
              localm.x = 1;
            }
          }
        }
        m tmp412_411 = localm;
        tmp412_411.h = ((byte)(tmp412_411.h + 1));
        if (localm.h >= arrayOfByte2[localm.y][(localm.x << 1)])
        {
          localm.h = 0;
          if (localm.i)
          {
            m tmp455_454 = localm;
            tmp455_454.x = ((byte)(tmp455_454.x + 1));
            localm.g = false;
          }
        }
        localm.f = ((short)arrayOfByte1[localm.y][(arrayOfByte2[localm.y][((localm.x << 1) + 1)] + localm.h)]);
      }
    }
  }
  
  public final void a()
  {
    bA = false;
    this.br = false;
    aW = true;
    h.c();
  }
  
  private final void t()
  {
    m localm = null;
    if (h._a0()) {
      return;
    }
    if (cr > 4) {
      cr = (short)(cr - 1);
    }
    if (aw > 0) {
      aw -= 1;
    }
    if (cp < 0)
    {
      cp += 16;
      if (cp > 0) {
        cp = 0;
      }
    }
    if (cq < 0)
    {
      cq += 16;
      if (cq > 0) {
        cq = 0;
      }
    }
    if (cp > 0)
    {
      cp -= 16;
      if (cp < 0) {
        cp = 0;
      }
    }
    if (cq > 0)
    {
      cq -= 16;
      if (cq < 0) {
        cq = 0;
      }
    }
    cv = (localm = s[0]).r;
    cF[0] = localm.n;
    cF[1] = localm.o;
    cF[2] = (localm.p + 2293760);
    if (localm.i) {
      cF[2] -= (dG >> 2 << 16);
    }
    if (p > 1)
    {
      if ((i1 = (byte)e(2)) == 0) {
        i1 = -1;
      } else {
        i1 = 1;
      }
      cF[0] += e(p) * aq[cE] * i1;
      if ((i1 = (byte)e(2)) == 0) {
        i1 = -1;
      } else {
        i1 = 1;
      }
      cF[1] += e(p) * cU[cE] * i1;
      if ((i1 = (byte)e(2)) == 0) {
        i1 = -1;
      } else {
        i1 = 1;
      }
      cF[2] += e(p) * cU[cE] * i1;
      p = (short)(p - 4);
    }
    localm.s[0] = cC;
    localm.s[1] = cE;
    if (dy)
    {
      dA = (byte)(dA + dB);
      if ((dz <= dA) || (dA <= 0))
      {
        dB = (byte)-dB;
        dA = (byte)(dA + (dB << 1));
      }
    }
    else
    {
      if (dB < 0) {
        dB = (byte)-dB;
      }
      if (dA > 0) {
        dA = (byte)(dA - dB);
      }
      if (dA < 0) {
        dA = 0;
      }
    }
    cF[2] += (dA << 16);
    dy = false;
    int i1 = r();
    if (g == 0)
    {
      if ((i1 == 0) && (!localm.i))
      {
        if (cA > 0)
        {
          cA -= cy;
          cy += 1;
          if (cA < 0) {
            cA = 0;
          }
        }
        if (cA < 0)
        {
          cA += cy;
          cy += 1;
          if (cA > 0) {
            cA = 0;
          }
        }
      }
      else
      {
        if (i1 == 1) {
          cA += 1;
        }
        if (i1 == 2) {
          cA -= 1;
        }
      }
      if (cA == 0) {
        cy = 0;
      }
    }
    if (cA > 60) {
      cA = 60;
    }
    if (cA < -60) {
      cA = -60;
    }
    cC = cD + cA;
    if (cz > 0) {
      if (du)
      {
        cz -= 1;
      }
      else
      {
        cz -= 8;
        if (cz < 0) {
          cz = 0;
        }
      }
    }
    if (cz < 0) {
      if (du)
      {
        cz += 1;
      }
      else
      {
        cz += 8;
        if (cz > 0) {
          cz = 0;
        }
      }
    }
    cE += cz;
    if (cE < 0) {
      cE += 360;
    }
    if (cE >= 360) {
      cE -= 360;
    }
    if (cC >= 360) {
      cC = 360;
    }
    if (cC < 180) {
      cC = 180;
    }
    if ((g == 0) && (cA == 0))
    {
      cD = 270;
      cC = 270;
    }
    if (aK > 0) {
      aK = (byte)(aK - 1);
    }
  }
  
  private static final int g(int paramInt)
  {
    int i1;
    if ((i1 = paramInt >> 16 << 16) < paramInt) {
      return (i1 >> 16) + 1;
    }
    return i1 >> 16;
  }
  
  private final void u()
  {
    Object localObject = null;
    if (h._a0()) {
      return;
    }
    this.bC = this.bD;
    n.a(this.bD);
  }
  
  private final boolean g(m paramm)
  {
    int[] arrayOfInt = dw;
    g localg1 = q[paramm.r];
    g localg2 = null;
    int i1;
    if ((localg1.f < paramm.n) || (localg1.i > paramm.n) || (localg1.g < paramm.o) || (localg1.j > paramm.o) || (localg1.h < paramm.p) || (localg1.k > paramm.p)) {
      for (i1 = cx - 1; i1 >= 0; i1--) {
        if (((localg2 = q[i1]).f > paramm.n) && (localg2.i < paramm.n) && (localg2.g > paramm.o) && (localg2.j < paramm.o) && (localg2.h > paramm.p) && (localg2.k < paramm.p))
        {
          paramm.r = ((short)i1);
          break;
        }
      }
    }
    if ((arrayOfInt[0] == 0) && (arrayOfInt[1] == 0) && (arrayOfInt[2] == 0)) {
      return false;
    }
    arrayOfInt[0] = (paramm.n + arrayOfInt[0] * 125);
    arrayOfInt[1] = (paramm.o + arrayOfInt[1] * 125);
    arrayOfInt[2] = (paramm.p + arrayOfInt[2] * 125);
    if ((localg1.f < arrayOfInt[0]) || (localg1.i > arrayOfInt[0]) || (localg1.g < arrayOfInt[1]) || (localg1.j > arrayOfInt[1]) || (localg1.h < arrayOfInt[2]) || (localg1.k > arrayOfInt[2]))
    {
      for (i1 = cx - 1; i1 >= 0; i1--) {
        if (((localg2 = q[i1]).f > arrayOfInt[0]) && (localg2.i < arrayOfInt[0]) && (localg2.g > arrayOfInt[1]) && (localg2.j < arrayOfInt[1]) && (localg2.h > arrayOfInt[2]) && (localg2.k < arrayOfInt[2]))
        {
          c(paramm, i1);
          return false;
        }
      }
      if (arrayOfInt[0] > localg1.f) {
        paramm.n += localg1.f - arrayOfInt[0];
      }
      if (arrayOfInt[0] < localg1.i) {
        paramm.n += localg1.i - arrayOfInt[0];
      }
      if (arrayOfInt[1] > localg1.g) {
        paramm.o += localg1.g - arrayOfInt[1];
      }
      if (arrayOfInt[1] < localg1.j) {
        paramm.o += localg1.j - arrayOfInt[1];
      }
      if (arrayOfInt[2] > localg1.h) {
        paramm.p += localg1.h - arrayOfInt[2];
      }
      if (arrayOfInt[2] < localg1.k) {
        paramm.p += localg1.k - arrayOfInt[2];
      }
    }
    return true;
  }
  
  private static void v()
  {
    g localg1;
    if (((localg1 = q[cv]).f < cF[0]) || (localg1.i > cF[0]) || (localg1.g < cF[1]) || (localg1.j > cF[1]) || (localg1.h < cF[2]) || (localg1.k > cF[2])) {
      for (int i1 = cx - 1; i1 >= 0; i1--)
      {
        g localg2;
        if (((localg2 = q[i1]).f > cF[0]) && (localg2.i < cF[0]) && (localg2.g > cF[1]) && (localg2.j < cF[1]) && (localg2.h > cF[2]) && (localg2.k < cF[2]))
        {
          cv = (short)i1;
          return;
        }
      }
    }
  }
  
  private static void w()
  {
    if ((af) && ((cZ == 1) || (cZ == 2)))
    {
      byte b1 = cY[cZ];
      ae = 8;
      dC = ag.t;
      cY[cZ] = dC;
      ag.t = b1;
      ag.a = k[b1].a;
      ag.b = k[b1].b;
      return;
    }
    ae = 8;
    cZ = (byte)(cZ + 1);
    if (cZ >= 4) {
      cZ = 0;
    }
    if ((dN > 0) && (cZ > 1)) {
      cZ = 0;
    }
    if (cZ > 0)
    {
      switch (cZ)
      {
      case 1: 
        if (cY[1] != 0) {
          dC = cY[1];
        }
        break;
      case 2: 
        if (cY[2] != 0)
        {
          dC = cY[2];
          cZ = 2;
        }
        break;
      case 3: 
        if (cY[3] != 0)
        {
          dC = cY[3];
          cZ = 3;
        }
        break;
      case 4: 
        cZ = 0;
        dC = cY[cZ];
      }
      return;
    }
    dC = cY[cZ];
  }
  
  private static final byte a(l[] paramArrayOfl1, l[] paramArrayOfl2, int[][] paramArrayOfInt)
  {
    int[] arrayOfInt1 = aA;
    int i1 = -2097152;
    int i2 = 3;
    byte b1 = 0;
    int[] arrayOfInt2 = dQ;
    for (int i11 = 0; i11 < 5; i11++)
    {
      int[] arrayOfInt3;
      int i8 = (arrayOfInt3 = paramArrayOfInt[i11])[0];
      int i9 = arrayOfInt3[1];
      int i10 = arrayOfInt3[2];
      b1 = 0;
      int i6 = i2 * 9;
      for (int i3 = 0; i3 < i2; i3++)
      {
        l locall1 = paramArrayOfl2[i3];
        l locall2 = paramArrayOfl2[arrayOfInt2[(i6++)]];
        l locall3 = paramArrayOfl1[b1];
        int i4 = (int)(locall1.a * i8 + locall1.b * i9 + (locall1.c + i1) * i10 >> 22);
        int i5 = (int)(locall2.a * i8 + locall2.b * i9 + (locall2.c + i1) * i10 >> 22);
        if (i4 >= 0)
        {
          locall3.a = locall1.a;
          locall3.b = locall1.b;
          locall3.c = locall1.c;
          locall3.f = locall1.f;
          locall3.h = locall1.h;
          b1 = (byte)(b1 + 1);
          locall3 = paramArrayOfl1[b1];
        }
        int i7;
        long l1;
        long l2;
        if (i5 - i4 > 0)
        {
          i7 = arrayOfInt1[(i5 - i4)];
          l1 = i5 * i7;
          l2 = -i4 * i7;
        }
        else
        {
          i7 = arrayOfInt1[(i4 - i5)];
          l1 = -i5 * i7;
          l2 = i4 * i7;
        }
        if (((i4 > 0) && (i5 < 0)) || ((i5 > 0) && (i4 < 0)))
        {
          locall3.a = ((int)(locall1.a * l1 + locall2.a * l2 >> 18));
          locall3.b = ((int)(locall1.b * l1 + locall2.b * l2 >> 18));
          locall3.c = ((int)(locall1.c * l1 + locall2.c * l2 >> 18));
          locall3.f = ((short)(int)(locall1.f * l1 + locall2.f * l2 >> 18));
          locall3.h = ((short)(int)(locall1.h * l1 + locall2.h * l2 >> 18));
          b1 = (byte)(b1 + 1);
        }
      }
      if (b1 == 0) {
        return 0;
      }
      if (i11 == 0) {
        i1 = 0;
      }
      l[] arrayOfl = paramArrayOfl1;
      paramArrayOfl1 = paramArrayOfl2;
      paramArrayOfl2 = arrayOfl;
      i2 = b1;
    }
    return b1;
  }
  
  private static int a(l[] paramArrayOfl1, l[] paramArrayOfl2, int paramInt1, int paramInt2)
  {
    int[] arrayOfInt1 = aA;
    int i2 = 0;
    int i5 = paramInt2 * 9;
    int[] arrayOfInt2 = dQ;
    int i6 = bV;
    for (int i1 = 0; i1 < paramInt2; i1++)
    {
      l locall1 = paramArrayOfl2[i1];
      l locall2 = paramArrayOfl2[arrayOfInt2[(i5 + i1)]];
      int i3 = (int)(locall1.a * -i6 + locall1.c * paramInt1 >> 24);
      int i4 = (int)(locall2.a * -i6 + locall2.c * paramInt1 >> 24);
      l locall3 = paramArrayOfl1[i2];
      if (i3 >= 0)
      {
        locall3.a = locall1.a;
        locall3.b = locall1.b;
        locall3.c = locall1.c;
        locall3.f = locall1.f;
        locall3.h = locall1.h;
        i2++;
        locall3 = paramArrayOfl1[i2];
      }
      long l1;
      long l2;
      if (i4 - i3 > 0)
      {
        l1 = i4 * arrayOfInt1[(i4 - i3)];
        l2 = -i3 * arrayOfInt1[(i4 - i3)];
      }
      else
      {
        l1 = -i4 * arrayOfInt1[(i3 - i4)];
        l2 = i3 * arrayOfInt1[(i3 - i4)];
      }
      if (((i3 > 0) && (i4 < 0)) || ((i4 > 0) && (i3 < 0)))
      {
        locall3.a = ((int)(locall1.a * l1 + locall2.a * l2 >> 18));
        locall3.b = ((int)(locall1.b * l1 + locall2.b * l2 >> 18));
        locall3.c = ((int)(locall1.c * l1 + locall2.c * l2 >> 18));
        locall3.f = ((short)(int)(locall1.f * l1 + locall2.f * l2 >> 18));
        locall3.h = ((short)(int)(locall1.h * l1 + locall2.h * l2 >> 18));
        i2++;
      }
    }
    return i2;
  }
  
  private static int b(l[] paramArrayOfl1, l[] paramArrayOfl2, int paramInt1, int paramInt2)
  {
    int[] arrayOfInt1 = aA;
    int i2 = 0;
    int i5 = paramInt2 * 9;
    int[] arrayOfInt2 = dQ;
    int i6 = bV;
    for (int i1 = 0; i1 < paramInt2; i1++)
    {
      l locall1 = paramArrayOfl2[i1];
      l locall2 = paramArrayOfl2[arrayOfInt2[(i5 + i1)]];
      int i3 = (int)(locall1.b * -i6 + locall1.c * paramInt1 >> 24);
      int i4 = (int)(locall2.b * -i6 + locall2.c * paramInt1 >> 24);
      l locall3 = paramArrayOfl1[i2];
      if (i3 >= 0)
      {
        locall3.a = locall1.a;
        locall3.b = locall1.b;
        locall3.c = locall1.c;
        locall3.f = locall1.f;
        locall3.h = locall1.h;
        i2++;
        locall3 = paramArrayOfl1[i2];
      }
      long l1;
      long l2;
      if (i4 - i3 > 0)
      {
        l1 = i4 * arrayOfInt1[(i4 - i3)];
        l2 = -i3 * arrayOfInt1[(i4 - i3)];
      }
      else
      {
        l1 = -i4 * arrayOfInt1[(i3 - i4)];
        l2 = i3 * arrayOfInt1[(i3 - i4)];
      }
      if (((i3 > 0) && (i4 < 0)) || ((i4 > 0) && (i3 < 0)))
      {
        locall3.a = ((int)(locall1.a * l1 + locall2.a * l2 >> 18));
        locall3.b = ((int)(locall1.b * l1 + locall2.b * l2 >> 18));
        locall3.c = ((int)(locall1.c * l1 + locall2.c * l2 >> 18));
        locall3.f = ((short)(int)(locall1.f * l1 + locall2.f * l2 >> 18));
        locall3.h = ((short)(int)(locall1.h * l1 + locall2.h * l2 >> 18));
        i2++;
      }
    }
    return i2;
  }
  
  private static int c(l[] paramArrayOfl1, l[] paramArrayOfl2, int paramInt1, int paramInt2)
  {
    int[] arrayOfInt1 = aA;
    int i2 = 0;
    int i5 = paramInt2 * 9;
    int[] arrayOfInt2 = dQ;
    int i6 = bV;
    for (int i1 = 0; i1 < paramInt2; i1++)
    {
      l locall1 = paramArrayOfl2[i1];
      l locall2 = paramArrayOfl2[arrayOfInt2[(i5 + i1)]];
      int i3 = (int)(locall1.a * i6 + locall1.c * paramInt1 >> 24);
      int i4 = (int)(locall2.a * i6 + locall2.c * paramInt1 >> 24);
      l locall3 = paramArrayOfl1[i2];
      if (i3 >= 0)
      {
        locall3.a = locall1.a;
        locall3.b = locall1.b;
        locall3.c = locall1.c;
        locall3.f = locall1.f;
        locall3.h = locall1.h;
        i2++;
        locall3 = paramArrayOfl1[i2];
      }
      long l1;
      long l2;
      if (i4 - i3 > 0)
      {
        l1 = i4 * arrayOfInt1[(i4 - i3)];
        l2 = -i3 * arrayOfInt1[(i4 - i3)];
      }
      else
      {
        l1 = -i4 * arrayOfInt1[(i3 - i4)];
        l2 = i3 * arrayOfInt1[(i3 - i4)];
      }
      if (((i3 > 0) && (i4 < 0)) || ((i4 > 0) && (i3 < 0)))
      {
        locall3.a = ((int)(locall1.a * l1 + locall2.a * l2 >> 18));
        locall3.b = ((int)(locall1.b * l1 + locall2.b * l2 >> 18));
        locall3.c = ((int)(locall1.c * l1 + locall2.c * l2 >> 18));
        locall3.f = ((short)(int)(locall1.f * l1 + locall2.f * l2 >> 18));
        locall3.h = ((short)(int)(locall1.h * l1 + locall2.h * l2 >> 18));
        i2++;
      }
    }
    return i2;
  }
  
  private static int d(l[] paramArrayOfl1, l[] paramArrayOfl2, int paramInt1, int paramInt2)
  {
    int[] arrayOfInt1 = aA;
    int i2 = 0;
    int i5 = paramInt2 * 9;
    int[] arrayOfInt2 = dQ;
    int i6 = bV;
    for (int i1 = 0; i1 < paramInt2; i1++)
    {
      l locall1 = paramArrayOfl2[i1];
      l locall2 = paramArrayOfl2[arrayOfInt2[(i5 + i1)]];
      int i3 = (int)(locall1.b * i6 + locall1.c * paramInt1 >> 24);
      int i4 = (int)(locall2.b * i6 + locall2.c * paramInt1 >> 24);
      l locall3 = paramArrayOfl1[i2];
      if (i3 >= 0)
      {
        locall3.a = locall1.a;
        locall3.b = locall1.b;
        locall3.c = locall1.c;
        locall3.f = locall1.f;
        locall3.h = locall1.h;
        i2++;
        locall3 = paramArrayOfl1[i2];
      }
      long l1;
      long l2;
      if (i4 - i3 > 0)
      {
        l1 = i4 * arrayOfInt1[(i4 - i3)];
        l2 = -i3 * arrayOfInt1[(i4 - i3)];
      }
      else
      {
        l1 = -i4 * arrayOfInt1[(i3 - i4)];
        l2 = i3 * arrayOfInt1[(i3 - i4)];
      }
      if (((i3 > 0) && (i4 < 0)) || ((i4 > 0) && (i3 < 0)))
      {
        locall3.a = ((int)(locall1.a * l1 + locall2.a * l2 >> 18));
        locall3.b = ((int)(locall1.b * l1 + locall2.b * l2 >> 18));
        locall3.c = ((int)(locall1.c * l1 + locall2.c * l2 >> 18));
        locall3.f = ((short)(int)(locall1.f * l1 + locall2.f * l2 >> 18));
        locall3.h = ((short)(int)(locall1.h * l1 + locall2.h * l2 >> 18));
        i2++;
      }
    }
    return i2;
  }
  
  private final void a(byte paramByte, short[] paramArrayOfShort)
  {
    m localm;
    j localj;
    switch (paramByte)
    {
    case 97: 
      cF[0] = (paramArrayOfShort[1] << 16);
      cF[1] = (paramArrayOfShort[2] << 16);
      cF[2] = (paramArrayOfShort[3] << 16);
      cC = paramArrayOfShort[4];
      cE = paramArrayOfShort[5];
      return;
    case 98: 
      (localm = s[paramArrayOfShort[1]]).n = (paramArrayOfShort[2] << 16);
      localm.o = (paramArrayOfShort[3] << 16);
      localm.p = (paramArrayOfShort[4] << 16);
      localm.e[0] = 0;
      localm.e[1] = 0;
      localm.e[2] = 0;
      h(localm);
      g(localm);
      return;
    case 99: 
      (localj = l[paramArrayOfShort[1]]).m = (paramArrayOfShort[2] << 16);
      localj.n = (paramArrayOfShort[3] << 16);
      localj.o = (paramArrayOfShort[4] << 16);
      localj.p = paramArrayOfShort[5];
      localj.q = paramArrayOfShort[6];
      return;
    case 100: 
      i(-1);
      this.i = false;
      this.cL = 0;
      this.cN = 0;
      this.cP = 0;
      this.bb = 0;
      this.cI = 2;
      return;
    case 101: 
      a(paramArrayOfShort[3] << 16, paramArrayOfShort[4] << 16, paramArrayOfShort[5] << 16, (byte)paramArrayOfShort[1], paramArrayOfShort[2]);
      return;
    case 102: 
      a(cl, cv);
      a(aC);
      return;
    case 103: 
      aD = false;
      return;
    case 104: 
      int i1 = q[paramArrayOfShort[1]].b.length;
      int[] arrayOfInt = q[paramArrayOfShort[1]].b;
      for (int i3 = 0; i3 < i1; i3 += 7)
      {
        int i2;
        if ((i2 = ((arrayOfInt[(i3 + 6)] & 0xFF00) >> 8) + paramArrayOfShort[2]) > 255) {
          i2 = 255;
        }
        if (i2 < 0) {
          i2 = 0;
        }
        arrayOfInt[(i3 + 6)] = ((i2 << 8) + (arrayOfInt[(i3 + 6)] & 0xFF));
      }
      return;
    case 105: 
      this.au = paramArrayOfShort[1];
      if (this.au > 256) {
        this.au = 256;
      }
      if (this.au < 0)
      {
        this.au = 0;
        return;
      }
      break;
    case 106: 
      this.i = true;
      this.bb = paramArrayOfShort[1];
      this.aX = ((short)(paramArrayOfShort[2] + this.cP));
      return;
    case 107: 
      localm = s[0];
      if (paramArrayOfShort[1] == 0)
      {
        cC += paramArrayOfShort[2];
        if (cC >= 360) {
          cC -= 360;
        }
        if (cC < 0) {
          cC += 360;
        }
        return;
      }
      cE += paramArrayOfShort[2];
      if (cE >= 360) {
        cE -= 360;
      }
      if (cE < 0) {
        cE += 360;
      }
      localm.s[0] = (-cU[cE]);
      localm.s[1] = (-aq[cE]);
      return;
    case 108: 
      switch (paramArrayOfShort[1])
      {
      case 0: 
        cF[0] += (int)(-cU[cE] * -cU[cC] >> 16) * paramArrayOfShort[2];
        cF[1] += (int)(-aq[cE] * -cU[cC] >> 16) * paramArrayOfShort[2];
        cF[2] += -aq[cC] * paramArrayOfShort[2];
        break;
      case 1: 
        cF[0] -= aq[cE] * paramArrayOfShort[2];
        cF[1] -= cU[cE] * paramArrayOfShort[2];
        break;
      case 2: 
        cF[2] += (paramArrayOfShort[2] << 16);
      }
      break;
    case 109: 
      localm = s[paramArrayOfShort[1]];
      switch (paramArrayOfShort[2])
      {
      case 0: 
        localm.b[0] = (-localm.s[0] * paramArrayOfShort[3]);
        localm.b[1] = (-localm.s[1] * paramArrayOfShort[3]);
        break;
      case 1: 
        localm.b[0] = (-localm.s[1] * paramArrayOfShort[3]);
        localm.b[1] = (-localm.s[0] * paramArrayOfShort[3]);
      }
      break;
    case 110: 
      this.au = ((short)(this.au + paramArrayOfShort[1]));
      if (this.au > 256) {
        this.au = 256;
      }
      if (this.au < 0)
      {
        this.au = 0;
        return;
      }
      break;
    case 111: 
      a(s[paramArrayOfShort[1]], paramArrayOfShort[2] << 16, paramArrayOfShort[3] << 16, 45, 0);
      return;
    case 112: 
      localj = l[paramArrayOfShort[1]];
      switch (paramArrayOfShort[2])
      {
      case 1: 
        localj.m += (paramArrayOfShort[3] << 16);
        break;
      case 2: 
        localj.n += (paramArrayOfShort[3] << 16);
        break;
      case 3: 
        localj.o += (paramArrayOfShort[3] << 16);
      }
      break;
    case 113: 
      this.cI = ((byte)paramArrayOfShort[1]);
      this.cN = 0;
      this.cK = 0;
      this.cL = 0;
      return;
    case 114: 
      cm = (byte)paramArrayOfShort[1];
      this.cg = ((short)(byte)paramArrayOfShort[2]);
      aD = false;
      return;
    case 115: 
      
    case 116: 
      if (paramArrayOfShort[1] >= 1)
      {
        a(false, true);
        return;
      }
      a(true, false);
      return;
    case 117: 
      if (paramArrayOfShort[2] >= 1)
      {
        a(paramArrayOfShort[1], false, true);
        return;
      }
      a(paramArrayOfShort[1], true, false);
      return;
    case 118: 
      for (int i4 = q[paramArrayOfShort[1]].q; i4 < q[paramArrayOfShort[1]].e; i4++) {
        l[i4].u = (!l[i4].u);
      }
      return;
    case 119: 
      bX[paramArrayOfShort[1]] = 10;
      for (int i5 = q[paramArrayOfShort[1]].q; i5 < q[paramArrayOfShort[1]].e; i5++) {
        if ((l[i5].t == 40) || (l[i5].t == 43)) {
          l[i5].o += (paramArrayOfShort[2] << 16);
        } else {
          l[i5].o -= (paramArrayOfShort[2] << 16);
        }
      }
      return;
    case 120: 
      (localj = l[paramArrayOfShort[1]]).m += (paramArrayOfShort[2] << 16);
      localj.n += (paramArrayOfShort[3] << 16);
      localj.o += (paramArrayOfShort[4] << 16);
      localj.p += paramArrayOfShort[5];
      if (localj.p >= 360) {
        localj.p -= 360;
      }
      if (localj.p < 0) {
        localj.p += 360;
      }
      localj.q += paramArrayOfShort[6];
      if (localj.q >= 360) {
        localj.q -= 360;
      }
      if (localj.q < 0)
      {
        localj.q += 360;
        return;
      }
      break;
    case 121: 
      p();
      return;
    case 122: 
      bA = true;
      this.m = true;
      this.bD = 9;
      di = true;
    }
  }
  
  private final void x()
  {
    if (!dd) {
      return;
    }
    if (!ck) {
      return;
    }
    try
    {
      if (p.k == null) {
        p.a(NET_Lizard.b);
      }
      if (ck) {
        p.a = 0;
      } else {
        p.a = -1;
      }
      String str = "/mm";
      if (this.bj < 0) {
        for (this.bj = 0; f.g.b(str + this.bj + ".mid") > 0; this.bj += 1) {}
      }
      if (this.bj > 0)
      {
        int i1 = (bM - 1) % 5;
        while (i1 >= this.bj) {
          i1 -= this.bj;
        }
        try
        {
          p.b(0);
        }
        catch (Exception localException1) {}
        p.a(str + i1 + ".mid", 0);
      }
    }
    catch (Exception localException2) {}
    Y = -1;
  }
  
  private static final boolean a(int paramInt1, int paramInt2)
  {
    if (paramInt1 == paramInt2) {
      return true;
    }
    int i1 = -1;
    e locale1 = dk;
    e locale2 = aE;
    int i2 = paramInt1;
    while ((i1 = a(i2, locale1, locale2, i1)) != -1)
    {
      if (o[i1].c == i2) {
        i2 = o[i1].d;
      } else {
        i2 = o[i1].c;
      }
      if (paramInt2 == i2) {
        return true;
      }
      if ((bX[i2] == 1) || (bX[i2] < 0)) {
        return false;
      }
    }
    return false;
  }
  
  private static void a(short paramShort)
  {
    if ((paramShort >= 255) || (paramShort < 0)) {
      return;
    }
    int i1 = 72000;
    int[] arrayOfInt = az;
    int i3 = paramShort;
    int i4 = 8;
    if (s[0].i)
    {
      i3 = 1;
      i4 = 0;
    }
    if (paramShort != 0)
    {
      do
      {
        int i2 = arrayOfInt[i1];
        arrayOfInt[i1] = ((((i2 & 0xFF0000) >> 16) * i3 >> i4 << 16) + (((i2 & 0xFF00) >> 8) * paramShort >> 8 << 8) + ((i2 & 0xFF) * paramShort >> 8));
        i1--;
      } while (i1 >= 0);
      return;
    }
    do
    {
      arrayOfInt[i1] = 0;
      i1--;
    } while (i1 >= 0);
  }
  
  public final void a(int[] paramArrayOfInt, int paramInt)
  {
    int[] arrayOfInt1 = new int[4];
    int i1 = q[paramInt].p;
    int[] arrayOfInt2 = null;
    int[] arrayOfInt3 = aC;
    int i2 = 0;
    int i3 = 0;
    do
    {
      arrayOfInt2 = q[paramInt].o;
      if ((i2 = a(paramArrayOfInt, arrayOfInt2[i1], arrayOfInt3, paramInt)) >= 0)
      {
        if ((i2 < 999) && ((bX[i2] == 1) || (bX[i2] < 0)))
        {
          o[q[i2].o[0]].e = true;
          o[q[i2].o[1]].e = true;
        }
        i3 = aB - 5;
        arrayOfInt1[0] = arrayOfInt3[i3];
        arrayOfInt1[1] = arrayOfInt3[(i3 + 1)];
        arrayOfInt1[2] = arrayOfInt3[(i3 + 2)];
        arrayOfInt1[3] = arrayOfInt3[(i3 + 3)];
        if (arrayOfInt3[(i3 + 4)] == 999) {
          arrayOfInt3[(i3 + 4)] = -1;
        } else {
          a(arrayOfInt1, i2);
        }
      }
      i1--;
    } while (i1 >= 0);
  }
  
  public final void a(int[] paramArrayOfInt)
  {
    int[][] arrayOfInt = null;
    if (h._a1()) {
      return;
    }
    arrayOfInt = new int[][] { { 0, 0, 1 }, { 0, -bV, 0 }, { 0, bV, 0 }, { bV, 0, 0 }, { -bV, 0, 0 } };
    if (bM == 2) {
      if (this.cW) {
        z();
      } else {
        y();
      }
    }
    c[] arrayOfc = o;
    for (int i2 = o.length - 1; i2 >= 0; i2--) {
      arrayOfc[i2].e = false;
    }
    for (int i3 = aB - 5; i3 >= 0; i3 -= 5)
    {
      arrayOfInt[1][2] = paramArrayOfInt[i3];
      arrayOfInt[2][2] = paramArrayOfInt[(i3 + 1)];
      arrayOfInt[3][2] = paramArrayOfInt[(i3 + 2)];
      arrayOfInt[4][2] = paramArrayOfInt[(i3 + 3)];
      if ((paramArrayOfInt[(i3 + 4)] == 999) || (paramArrayOfInt[(i3 + 4)] < 0))
      {
        if (!this.cW) {
          a(arrayOfInt, false);
        } else {
          a(arrayOfInt, true);
        }
      }
      else {
        a(paramArrayOfInt[(i3 + 4)], arrayOfInt);
      }
    }
    a(cv, ch);
    if (bT >= 0) {
      a(l[bT]);
    }
    aB = 0;
    if ((!s[0].i) && (!aD))
    {
      if (!bA) {
        cB = (short)(cB + 6);
      }
      if (cB >= 360) {
        cB = (short)(cB - 360);
      }
      int i1 = dA << 2;
      i2 = cB << 1;
      i3 = cB * 3;
      if (i2 >= 360) {
        i2 -= 360;
      }
      if ((i3 >= 360) && (i3 -= 360 >= 360)) {
        i3 -= 360;
      }
      if (ae > 0)
      {
        i1 = 4 - Math.abs(4 - ae) << 6;
        if (dN > 0) {
          a(s[dN].y + 5, 256, 256 - dM, true);
        }
      }
      else if (dN > 0)
      {
        a(s[dN].y + 5, 256, 256 - i1 - dM, true);
      }
      if (dF != 0) {
        a(dF, 256 - cp - (13 + (cU[i2] * 12 >> 16)), 256 - i1 - cq - (13 + (aq[i3] * 12 >> 16)), false);
      } else {
        a(dF, 128 + cp - (13 + (cU[i2] * 12 >> 16)), 128 + cq - i1 - (13 + (aq[i3] * 12 >> 16)), false);
      }
    }
    if (dG != 0) {
      a((short)(255 - dG));
    }
  }
  
  private static final void a(l paraml1, l paraml2, l paraml3, int paramInt1, int paramInt2)
  {
    byte[] arrayOfByte = do[aY];
    int[] arrayOfInt1 = ca[aY];
    int[] arrayOfInt2 = az;
    int[] arrayOfInt3 = ap;
    int i2 = paraml1.e * 240;
    int i6 = paraml1.d << 16;
    int i7 = paraml2.d << 16;
    int i8 = paraml1.d << 16;
    int i9 = paraml1.f << 16;
    int i10 = paraml2.f << 16;
    int i11 = paraml1.f << 16;
    int i12 = paraml1.h << 16;
    int i13 = paraml2.h << 16;
    int i14 = paraml1.h << 16;
    int i15 = (paraml3.d - paraml1.d) * arrayOfInt3[(paraml3.e - paraml1.e)];
    int i16 = (paraml2.d - paraml1.d) * arrayOfInt3[(paraml2.e - paraml1.e)];
    int i17 = (paraml3.d - paraml2.d) * arrayOfInt3[(paraml3.e - paraml2.e)];
    int i18 = (paraml3.f - paraml1.f) * arrayOfInt3[(paraml3.e - paraml1.e)];
    int i19 = (paraml2.f - paraml1.f) * arrayOfInt3[(paraml2.e - paraml1.e)];
    int i20 = (paraml3.f - paraml2.f) * arrayOfInt3[(paraml3.e - paraml2.e)];
    int i21 = (paraml3.h - paraml1.h) * arrayOfInt3[(paraml3.e - paraml1.e)];
    int i22 = (paraml2.h - paraml1.h) * arrayOfInt3[(paraml2.e - paraml1.e)];
    int i23 = (paraml3.h - paraml2.h) * arrayOfInt3[(paraml3.e - paraml2.e)];
    int i5;
    int i24;
    int i25;
    int i4;
    int i3;
    int i1;
    int i26;
    int i27;
    if (i15 < i16) {
      for (i5 = paraml1.e; i5 <= paraml2.e; i5++)
      {
        i24 = i9;
        i25 = i12;
        i4 = i2 + (i6 >> 16);
        i3 = g(i8 - i6);
        do
        {
          if ((i1 = arrayOfInt1[arrayOfByte[((i25 += paramInt2 >> 16 << 6) + (i24 += paramInt1 >> 16) & 0xFFF)]]) != 0) {
            arrayOfInt2[i4] = i1;
          }
          i4++;
          i3--;
        } while (i3 >= 0);
        i6 += i15;
        i8 += i16;
        i9 += i18;
        i12 += i21;
        i2 += 240;
      }
    } else {
      for (i5 = paraml1.e; i5 <= paraml2.e; i5++)
      {
        i26 = i11;
        i27 = i14;
        i4 = i2 + (i8 >> 16);
        i3 = g(i6 - i8);
        do
        {
          if ((i1 = arrayOfInt1[arrayOfByte[((i27 += paramInt2 >> 16 << 6) + (i26 += paramInt1 >> 16) & 0xFFF)]]) != 0) {
            arrayOfInt2[i4] = i1;
          }
          i4++;
          i3--;
        } while (i3 >= 0);
        i6 += i15;
        i8 += i16;
        i11 += i19;
        i14 += i22;
        i2 += 240;
      }
    }
    if (i15 + i6 < i17 + i7)
    {
      while (i5 < paraml3.e)
      {
        i24 = i9;
        i25 = i12;
        i4 = i2 + (i6 >> 16);
        i3 = g(i7 - i6);
        do
        {
          if ((i1 = arrayOfInt1[arrayOfByte[((i25 += paramInt2 >> 16 << 6) + (i24 += paramInt1 >> 16) & 0xFFF)]]) != 0) {
            arrayOfInt2[i4] = i1;
          }
          i4++;
          i3--;
        } while (i3 >= 0);
        i6 += i15;
        i7 += i17;
        i9 += i18;
        i12 += i21;
        i2 += 240;
        i5++;
      }
      return;
    }
    while (i5 < paraml3.e)
    {
      i26 = i10;
      i27 = i13;
      i4 = i2 + (i7 >> 16);
      i3 = g(i6 - i7);
      do
      {
        if ((i1 = arrayOfInt1[arrayOfByte[((i27 += paramInt2 >> 16 << 6) + (i26 += paramInt1 >> 16) & 0xFFF)]]) != 0) {
          arrayOfInt2[i4] = i1;
        }
        i4++;
        i3--;
      } while (i3 >= 0);
      i6 += i15;
      i7 += i17;
      i10 += i20;
      i13 += i23;
      i2 += 240;
      i5++;
    }
  }
  
  private static final void a(int[][] paramArrayOfInt, int paramInt)
  {
    int[][] arrayOfInt1 = dg;
    int[][] arrayOfInt2 = cR;
    int[][] arrayOfInt3 = dO;
    j[] arrayOfj = l;
    int[] arrayOfInt4 = null;
    l[] arrayOfl1 = aS;
    l[] arrayOfl2 = aP;
    l locall1 = arrayOfl1[0];
    l locall2 = arrayOfl1[1];
    l locall3 = arrayOfl1[2];
    l locall4 = arrayOfl2[0];
    int[] arrayOfInt6 = aZ;
    int[] arrayOfInt7 = ba;
    int i9 = bS;
    int i10 = df;
    int i11 = cS;
    int[] arrayOfInt8 = cU;
    int[] arrayOfInt9 = aq;
    boolean bool1 = false;
    boolean bool2 = false;
    boolean bool3 = false;
    for (int i12 = paramInt - 1; i12 >= 0; i12--)
    {
      int i6;
      if (arrayOfInt6[i12] >= i11)
      {
        i6 = arrayOfInt6[i12] - i11;
        a(arrayOfInt2[i6][8] > 1 ? 1 : arrayOfInt2[i6][9], arrayOfInt2[i6][0], arrayOfInt2[i6][1], arrayOfInt2[i6][2], paramArrayOfInt);
      }
      else if (arrayOfInt6[i12] >= i10)
      {
        i6 = arrayOfInt6[i12] - i10;
        a(arrayOfInt3[arrayOfInt1[i6][3]][(arrayOfInt1[i6][4] - 1)], arrayOfInt1[i6][0], arrayOfInt1[i6][1], arrayOfInt1[i6][2], paramArrayOfInt);
      }
      else
      {
        int[] arrayOfInt5;
        int i5;
        if (arrayOfInt6[i12] >= i9)
        {
          i6 = arrayOfInt6[i12] - i9;
          j localj;
          bool1 = (localj = arrayOfj[i6]).c;
          bool2 = localj.d;
          bool3 = localj.s;
          arrayOfInt5 = localj.b;
          arrayOfInt4 = localj.a;
          if (localj.t >= 120)
          {
            a(localj.t - 110, localj.m, localj.n, localj.o, paramArrayOfInt);
            continue;
          }
          i5 = localj.b.length >> 4;
          c(localj);
          R = localj.e;
          if (aG)
          {
            int i7 = dH - localj.m >> 16;
            int i8 = dJ - localj.n >> 16;
            if ((i7 = (int)(65536L * (i7 * i7 + i8 * i8) >> 28)) > 255) {
              i7 = 255;
            }
            R += 255 - i7;
            if (R > 255) {
              R = 255;
            }
          }
        }
        else
        {
          i6 = arrayOfInt6[i12];
          if (s[i6].y != 7)
          {
            d(i6, paramArrayOfInt);
            continue;
          }
          c(i6, paramArrayOfInt);
          continue;
        }
        a(arrayOfInt5, arrayOfInt4);
        for (int i14 = i5 - 1; i14 >= 0; i14--)
        {
          int i13 = arrayOfInt7[i14] << 4;
          int i2;
          if (bool2)
          {
            i2 = arrayOfInt5[(i13 + 13)];
            int i3 = arrayOfInt5[(i13 + 14)];
            int i4 = arrayOfInt5[(i13 + 15)];
            arrayOfInt5[(i13 + 13)] = ((int)(i2 * arrayOfInt9[cE] - i3 * arrayOfInt8[cE] >> 16));
            arrayOfInt5[(i13 + 14)] = ((int)(i2 * arrayOfInt8[cE] + i3 * arrayOfInt9[cE] >> 16));
            arrayOfInt5[(i13 + 15)] = ((int)(i4 * arrayOfInt9[cC] - arrayOfInt5[(i13 + 14)] * arrayOfInt8[cC] >> 16));
            arrayOfInt5[(i13 + 14)] = ((int)(i4 * arrayOfInt8[cC] + arrayOfInt5[(i13 + 14)] * arrayOfInt9[cC] >> 16));
            if (arrayOfInt5[(i13 + 13)] * arrayOfInt4[(arrayOfInt5[i13] + 3)] + arrayOfInt5[(i13 + 14)] * arrayOfInt4[(arrayOfInt5[i13] + 4)] + arrayOfInt5[(i13 + 15)] * arrayOfInt4[(arrayOfInt5[i13] + 5)] <= 0L) {}
          }
          else
          {
            i2 = arrayOfInt5[i13] + 3;
            locall1.a = arrayOfInt4[i2];
            locall1.b = arrayOfInt4[(++i2)];
            locall1.c = arrayOfInt4[(++i2)];
            i2 = arrayOfInt5[(i13 + 1)] + 3;
            locall2.a = arrayOfInt4[i2];
            locall2.b = arrayOfInt4[(++i2)];
            locall2.c = arrayOfInt4[(++i2)];
            i2 = arrayOfInt5[(i13 + 2)] + 3;
            locall3.a = arrayOfInt4[i2];
            locall3.b = arrayOfInt4[(++i2)];
            locall3.c = arrayOfInt4[(++i2)];
            i13 += 3;
            locall1.f = ((short)arrayOfInt5[i13]);
            locall1.h = ((short)arrayOfInt5[(++i13)]);
            locall2.f = ((short)arrayOfInt5[(++i13)]);
            locall2.h = ((short)arrayOfInt5[(++i13)]);
            locall3.f = ((short)arrayOfInt5[(++i13)]);
            locall3.h = ((short)arrayOfInt5[(++i13)]);
            i13++;
            aY = arrayOfInt5[i13];
            byte tmp1029_1027 = (i1 = a(arrayOfl2, arrayOfl1, paramArrayOfInt));
            int i1 = tmp1029_1027 - 1;
            if (tmp1029_1027 != 0)
            {
              aY = arrayOfInt5[i13];
              if (bool1)
              {
                aY = arrayOfInt5[i13];
                i1--;
                do
                {
                  b(locall4, arrayOfl2[(i1 + 1)], arrayOfl2[(i1 + 2)], false);
                  i1--;
                } while (i1 >= 0);
              }
              else if (bool3)
              {
                i1--;
                do
                {
                  a(locall4, arrayOfl2[(i1 + 1)], arrayOfl2[(i1 + 2)], false);
                  i1--;
                } while (i1 >= 0);
              }
              else
              {
                i1--;
                do
                {
                  a(locall4, arrayOfl2[(i1 + 1)], arrayOfl2[(i1 + 2)]);
                  i1--;
                } while (i1 >= 0);
              }
            }
          }
        }
      }
    }
  }
  
  private final void y()
  {
    int i1 = 0;
    int i4;
    if ((i4 = 150 - (cC - 270) * 150 / 90) > 300) {
      i4 = 300;
    }
    int[] arrayOfInt = az;
    for (int i2 = 0; i2 < i4; i2++)
    {
      for (int i3 = 0; i3 < 240; i3++) {
        arrayOfInt[(i1 + i3)] = 11002879;
      }
      i1 += 240;
    }
  }
  
  private final void a(int[][] paramArrayOfInt, boolean paramBoolean)
  {
    int[] arrayOfInt1 = az;
    byte[] arrayOfByte = dq;
    int[] arrayOfInt2 = cd;
    if (paramArrayOfInt[0][2] > 150) {
      paramArrayOfInt[0][2] = '';
    }
    if (paramArrayOfInt[1][2] > 150) {
      paramArrayOfInt[1][2] = '';
    }
    if (paramArrayOfInt[2][2] >= 120) {
      paramArrayOfInt[2][2] = 119;
    }
    if (paramArrayOfInt[3][2] >= 120) {
      paramArrayOfInt[3][2] = 119;
    }
    int i3 = 150 - paramArrayOfInt[1][2];
    int i4 = 150 + paramArrayOfInt[2][2];
    int i5 = 120 - paramArrayOfInt[3][2];
    int i6 = 120 + paramArrayOfInt[4][2];
    if (i5 < 0) {
      i5 = 0;
    }
    if (i3 < 0) {
      i3 = 0;
    }
    int i7 = cE * 240 / 360;
    int i8 = this.cX - 1;
    int i9 = this.cX;
    int i2;
    if (paramBoolean)
    {
      if (i4 > this.cV - 1) {
        i4 = this.cV - 1;
      }
      for (i1 = i5; i1 < i6; i1++) {
        for (i2 = i3; i2 < i4; i2++) {
          arrayOfInt1[(i2 * 240 + i1)] = arrayOfInt2[arrayOfByte[(i2 * i9 + (i1 + i7 & i8))]];
        }
      }
      return;
    }
    for (int i1 = i5; i1 < i6; i1++) {
      for (i2 = i3; i2 < i4; i2++) {
        arrayOfInt1[(i2 * 240 + i1)] = 11002879;
      }
    }
  }
  
  private final void a(Graphics paramGraphics)
  {
    if (aj)
    {
      this.aJ.a(paramGraphics, "time = " + this.bZ + " tex= " + dn, 0, 22, 20);
      this.aJ.a(paramGraphics, "rot_x=" + cC + " rot_z=" + cE, 0, 37, 20);
      this.aJ.a(paramGraphics, "difficult=" + ay, 0, 50, 20);
    }
    if (af) {
      this.aJ.a(paramGraphics, this.dc[25], 240 - this.aJ.a(this.dc[25]) >> 1, 160 - this.aJ.b() >> 1, 20);
    }
    int i1 = 0;
    if (db) {
      e(paramGraphics);
    }
    if ((dF != 0) && (aH))
    {
      switch (dF)
      {
      case 1: 
        i1 = 0;
        break;
      case 2: 
        i1 = aF;
        break;
      case 3: 
        i1 = (byte)(aF + 2);
        break;
      case 4: 
        i1 = (byte)(aF + 4);
        break;
      case 5: 
        i1 = 7;
      }
      b(paramGraphics, i1, dI + 0, dK + 10);
    }
    if (aD) {
      return;
    }
    int i2 = 108;
    int i3 = 27;
    if (this.ad[0][0] == 70)
    {
      i2 = 93;
      i3 = 19;
    }
    int i4 = 0;
    if (dF != 0)
    {
      paramGraphics.setColor(19821);
      paramGraphics.fillRect(0, 10, i2, i3);
    }
    else
    {
      paramGraphics.setColor(19821);
      paramGraphics.fillRect(0, 10, i2 - 50, i3);
    }
    paramGraphics.setColor(8221806);
    paramGraphics.drawRect(4, 10 + (i3 - this.ad[0][3] >> 2) - 2, this.ad[0][2] + 3, this.ad[0][3] + 3);
    paramGraphics.drawRect(4, 10 + i3 - (i3 - this.ad[0][3] >> 2) - this.ad[0][3] - 2, this.ad[0][2] + 3, this.ad[0][3] + 3);
    if (bM > 4)
    {
      if (((this.bf == 1) || (this.bf == 3) || (bM > 7)) && ((this.bF & 0x1) == 0)) {
        a(paramGraphics, 0, 6, 10 + (i3 - this.ad[0][3] >> 2));
      }
      if (((this.bf == 2) || (this.bf == 3) || (bM > 7)) && ((this.bE & 0x1) == 0)) {
        a(paramGraphics, 1, 6, 10 + i3 - (i3 - this.ad[0][3] >> 2) - this.ad[0][3]);
      }
    }
    paramGraphics.setColor(14157);
    i4 = 6 + (this.ad[0][2] + 4);
    paramGraphics.fillRect(i4, 10, this.ad[2][2], i3);
    a(paramGraphics, 2, i4, 10 + (i3 - this.ad[2][3] >> 1));
    i4 += this.ad[2][2] + 4;
    a(paramGraphics, "" + s[0].l, i4, 10 + (i3 - this.ad[5][3] >> 1), (byte)((this.bG & 0x1) == 0 ? 1 : 2));
    if (dF != 0)
    {
      i4 += (this.ad[5][2] + 1) * 3 + 2;
      paramGraphics.fillRect(i4, 10, this.ad[3][2], i3);
      a(paramGraphics, 3, i4, 10 + (i3 - this.ad[3][3] >> 1));
      i4 += this.ad[3][2] + 3;
      a(paramGraphics, "" + T[0][dF], i4, 10 + (i3 - this.ad[5][3] >> 1), (byte)0);
      i4 += (this.ad[5][2] + 1) * 2 + 3;
      paramGraphics.fillRect(i4, 10, this.ad[4][2], i3);
      a(paramGraphics, 4, i4, 10 + (i3 - this.ad[4][3] >> 1));
      i4 += this.ad[4][2] + 3;
      a(paramGraphics, "" + T[1][dF], i4, 10 + (i3 - this.ad[5][3] >> 1), (byte)((this.bH & 0x1) == 0 ? 0 : 3));
      paramGraphics.setColor(16777215);
      paramGraphics.drawRect(0, 10, i2, i3);
    }
    else
    {
      paramGraphics.setColor(16777215);
      paramGraphics.drawRect(0, 10, i2 - 50, i3);
    }
    if (this.bE > 0) {
      this.bE = ((byte)(this.bE - 1));
    }
    if (this.bF > 0) {
      this.bF = ((byte)(this.bF - 1));
    }
    if (this.bG > 0) {
      this.bG = ((byte)(this.bG - 1));
    }
    if (this.bH > 0) {
      this.bH = ((byte)(this.bH - 1));
    }
  }
  
  private void b(Graphics paramGraphics)
  {
    Object localObject = null;
    if (h._a0()) {
      return;
    }
    paramGraphics.setClip(0, 0, 240, 320);
    paramGraphics.setColor(0);
    paramGraphics.fillRect(0, 0, 240, 320);
    int i1 = 120 - (this.bt.getHeight() >> 1);
    if (Y >= 2) {
      i1 = 160 - (this.bt.getHeight() >> 1);
    }
    paramGraphics.drawImage(this.bt, 120 - (this.bt.getWidth() >> 1), i1, 20);
    if (Y == 2)
    {
      paramGraphics.drawImage(this.bY, 120 - (this.bY.getWidth() >> 1), 320 - ((8 - this.bs) * (this.bY.getHeight() + this.aV.getHeight()) >> 3), 20);
      return;
    }
    if (Y == 3)
    {
      paramGraphics.drawImage(this.aV, 120 - (this.aV.getWidth() >> 1), 320 - ((4 - this.bs) * this.aV.getHeight() >> 2), 20);
      paramGraphics.drawImage(this.bY, 120 - (this.bY.getWidth() >> 1), 320 - this.bY.getHeight() - this.aV.getHeight(), 20);
      return;
    }
    if (Y == 4)
    {
      paramGraphics.drawImage(this.aV, 120 - (this.aV.getWidth() >> 1), 320 - this.aV.getHeight(), 20);
      paramGraphics.drawImage(this.bY, 120 - (this.bY.getWidth() >> 1), 320 - this.bY.getHeight() - this.aV.getHeight(), 20);
    }
    if (this.bs == -1) {
      this.aJ.a(paramGraphics, this.dc[48], 240 - this.aJ.a(this.dc[48]) >> 1, 320 - this.aJ.b() >> 1, 20);
    }
    if (this.bs < 0) {
      return;
    }
    if (Y == 0) {
      paramGraphics.drawImage(this.aV, 120 - (this.aV.getWidth() >> 1), 320 - this.bY.getHeight() - this.bY.getHeight() - this.aV.getHeight(), 20);
    }
  }
  
  private final void c(Graphics paramGraphics)
  {
    paramGraphics.setColor(0);
    paramGraphics.fillRect(0, 0, 240, 320);
    this.aJ.a(paramGraphics, this.dc[13], 240 - this.aJ.a(this.dc[13]) >> 1, 320 - this.aJ.b() >> 1, 20);
  }
  
  private final void d(Graphics paramGraphics)
  {
    int i1 = this.aJ.b();
    int i2 = (320 - i1 >> 1) - (i1 >> 1);
    paramGraphics.setColor(0);
    paramGraphics.fillRect(0, i2, 240, i1 << 1);
    paramGraphics.setColor(16777215);
    paramGraphics.drawLine(0, i2, 240, i2);
    paramGraphics.drawLine(0, i2 + i1 * 2, 240, i2 + i1 * 2);
    this.aJ.a(paramGraphics, this.dc[(29 + bM)] + "...", 240 - this.aJ.a(this.dc[(29 + bM)] + "...") >> 1, 320 - i1 >> 1, 20);
  }
  
  public static final void a(j paramj)
  {
    int[] arrayOfInt1 = paramj.a;
    int[] arrayOfInt2 = paramj.b;
    int i1 = paramj.b.length;
    l[] arrayOfl;
    l locall1 = (arrayOfl = aS)[0];
    l locall2 = arrayOfl[1];
    l locall3 = arrayOfl[2];
    R = 256;
    c(paramj);
    for (int i6 = 0; i6 < i1; i6 += 16)
    {
      int i2 = arrayOfInt2[(i6 + 13)];
      int i3 = arrayOfInt2[(i6 + 14)];
      int i4 = arrayOfInt2[(i6 + 15)];
      arrayOfInt2[(i6 + 13)] = ((int)(i2 * aq[cE] - i3 * cU[cE] >> 16));
      arrayOfInt2[(i6 + 14)] = ((int)(i2 * cU[cE] + i3 * aq[cE] >> 16));
      arrayOfInt2[(i6 + 15)] = ((int)(i4 * aq[cC] - arrayOfInt2[(i6 + 14)] * cU[cC] >> 16));
      arrayOfInt2[(i6 + 14)] = ((int)(i4 * cU[cC] + arrayOfInt2[(i6 + 14)] * aq[cC] >> 16));
      if (arrayOfInt2[(i6 + 13)] * arrayOfInt1[(arrayOfInt2[i6] + 3)] + arrayOfInt2[(i6 + 14)] * arrayOfInt1[(arrayOfInt2[i6] + 4)] + arrayOfInt2[(i6 + 15)] * arrayOfInt1[(arrayOfInt2[i6] + 5)] > 0L)
      {
        int i5 = arrayOfInt2[i6] + 3;
        locall1.a = arrayOfInt1[(i5++)];
        locall1.b = arrayOfInt1[(i5++)];
        locall1.c = arrayOfInt1[i5];
        i5 = arrayOfInt2[(i6 + 1)] + 3;
        locall2.a = arrayOfInt1[(i5++)];
        locall2.b = arrayOfInt1[(i5++)];
        locall2.c = arrayOfInt1[i5];
        i5 = arrayOfInt2[(i6 + 2)] + 3;
        locall3.a = arrayOfInt1[(i5++)];
        locall3.b = arrayOfInt1[(i5++)];
        locall3.c = arrayOfInt1[i5];
        locall1.f = ((short)arrayOfInt2[(i6 + 3)]);
        locall1.h = ((short)arrayOfInt2[(i6 + 4)]);
        locall2.f = ((short)arrayOfInt2[(i6 + 5)]);
        locall2.h = ((short)arrayOfInt2[(i6 + 6)]);
        locall3.f = ((short)arrayOfInt2[(i6 + 7)]);
        locall3.h = ((short)arrayOfInt2[(i6 + 8)]);
        aY = arrayOfInt2[(i6 + 9)];
        b(locall1, locall2, locall3, false);
      }
    }
  }
  
  private static final void a(l paraml1, l paraml2, l paraml3, boolean paramBoolean)
  {
    int[] arrayOfInt1 = ap;
    int[] arrayOfInt2 = aA;
    int i1 = bW;
    paraml1.d = ((short)(int)(7864320L + paraml1.a * i1 / paraml1.c >> 16));
    paraml1.e = ((short)(int)(9830400L - paraml1.b * i1 / paraml1.c >> 16));
    paraml2.d = ((short)(int)(7864320L + paraml2.a * i1 / paraml2.c >> 16));
    paraml2.e = ((short)(int)(9830400L - paraml2.b * i1 / paraml2.c >> 16));
    paraml3.d = ((short)(int)(7864320L + paraml3.a * i1 / paraml3.c >> 16));
    paraml3.e = ((short)(int)(9830400L - paraml3.b * i1 / paraml3.c >> 16));
    l locall;
    if (paraml1.e > paraml2.e)
    {
      locall = paraml1;
      paraml1 = paraml2;
      paraml2 = locall;
    }
    if (paraml1.e > paraml3.e)
    {
      locall = paraml1;
      paraml1 = paraml3;
      paraml3 = locall;
    }
    if (paraml2.e > paraml3.e)
    {
      locall = paraml2;
      paraml2 = paraml3;
      paraml3 = locall;
    }
    int i2;
    if ((i2 = paraml1.c >> 16) < 0) {
      paraml1.m = (-arrayOfInt2[(-i2)]);
    } else {
      paraml1.m = arrayOfInt2[i2];
    }
    paraml1.g = (paraml1.f * paraml1.m);
    paraml1.i = (paraml1.h * paraml1.m);
    if ((i2 = paraml2.c >> 16) < 0) {
      paraml2.m = (-arrayOfInt2[(-i2)]);
    } else {
      paraml2.m = arrayOfInt2[i2];
    }
    paraml2.g = (paraml2.f * paraml2.m);
    paraml2.i = (paraml2.h * paraml2.m);
    if ((i2 = paraml3.c >> 16) < 0) {
      paraml3.m = (-arrayOfInt2[(-i2)]);
    } else {
      paraml3.m = arrayOfInt2[i2];
    }
    paraml3.g = (paraml3.f * paraml3.m);
    paraml3.i = (paraml3.h * paraml3.m);
    int i3 = (paraml2.e - paraml1.e) * arrayOfInt1[(paraml3.e - paraml1.e)];
    int i4;
    int i5;
    if ((i2 = paraml1.d + (int)((paraml3.d - paraml1.d) * i3 >> 16) - paraml2.d) < 0)
    {
      i2 = arrayOfInt1[(-i2)];
      i4 = -(int)((paraml1.g + (int)((paraml3.g - paraml1.g) * i3 >> 16) - paraml2.g) * i2 >> 12);
      i5 = -(int)((paraml1.i + (int)((paraml3.i - paraml1.i) * i3 >> 16) - paraml2.i) * i2 >> 12);
      i3 = -(int)((paraml1.m + (int)((paraml3.m - paraml1.m) * i3 >> 16) - paraml2.m) * i2 >> 12);
    }
    else
    {
      i2 = arrayOfInt1[i2];
      i4 = (int)((paraml1.g + (int)((paraml3.g - paraml1.g) * i3 >> 16) - paraml2.g) * i2 >> 12);
      i5 = (int)((paraml1.i + (int)((paraml3.i - paraml1.i) * i3 >> 16) - paraml2.i) * i2 >> 12);
      i3 = (int)((paraml1.m + (int)((paraml3.m - paraml1.m) * i3 >> 16) - paraml2.m) * i2 >> 12);
    }
    if (paramBoolean)
    {
      if ((paraml3.d - paraml1.d) * arrayOfInt2[(paraml3.e - paraml1.e)] < (paraml2.d - paraml1.d) * arrayOfInt2[(paraml2.e - paraml1.e)]) {
        a(paraml1, paraml2, paraml3, i4, i5, i3);
      } else {
        c(paraml1, paraml2, paraml3, i4, i5, i3);
      }
      if ((paraml3.d - paraml1.d) * arrayOfInt2[(paraml3.e - paraml1.e)] > (paraml3.d - paraml2.d) * arrayOfInt2[(paraml3.e - paraml2.e)]) {
        e(paraml1, paraml2, paraml3, i4, i5, i3);
      } else {
        g(paraml1, paraml2, paraml3, i4, i5, i3);
      }
    }
    else
    {
      if ((paraml3.d - paraml1.d) * arrayOfInt2[(paraml3.e - paraml1.e)] < (paraml2.d - paraml1.d) * arrayOfInt2[(paraml2.e - paraml1.e)]) {
        b(paraml1, paraml2, paraml3, i4, i5, i3);
      } else {
        d(paraml1, paraml2, paraml3, i4, i5, i3);
      }
      if ((paraml3.d - paraml1.d) * arrayOfInt2[(paraml3.e - paraml1.e)] > (paraml3.d - paraml2.d) * arrayOfInt2[(paraml3.e - paraml2.e)])
      {
        f(paraml1, paraml2, paraml3, i4, i5, i3);
        return;
      }
      h(paraml1, paraml2, paraml3, i4, i5, i3);
    }
  }
  
  private static final void a(l paraml1, l paraml2, l paraml3)
  {
    int[] arrayOfInt = ap;
    int i1 = bW;
    paraml1.d = ((short)(int)(7864320L + paraml1.a * i1 / paraml1.c >> 16));
    paraml1.e = ((short)(int)(9830400L - paraml1.b * i1 / paraml1.c >> 16));
    paraml2.d = ((short)(int)(7864320L + paraml2.a * i1 / paraml2.c >> 16));
    paraml2.e = ((short)(int)(9830400L - paraml2.b * i1 / paraml2.c >> 16));
    paraml3.d = ((short)(int)(7864320L + paraml3.a * i1 / paraml3.c >> 16));
    paraml3.e = ((short)(int)(9830400L - paraml3.b * i1 / paraml3.c >> 16));
    l locall;
    if (paraml1.e > paraml2.e)
    {
      locall = paraml1;
      paraml1 = paraml2;
      paraml2 = locall;
    }
    if (paraml1.e > paraml3.e)
    {
      locall = paraml1;
      paraml1 = paraml3;
      paraml3 = locall;
    }
    if (paraml2.e > paraml3.e)
    {
      locall = paraml2;
      paraml2 = paraml3;
      paraml3 = locall;
    }
    int i2 = (paraml2.e - paraml1.e) * arrayOfInt[(paraml3.e - paraml1.e)];
    int i3;
    if ((i3 = paraml1.d + ((paraml3.d - paraml1.d) * i2 >> 16) - paraml2.d) < 0)
    {
      a(paraml1, paraml2, paraml3, -(paraml1.f + ((paraml3.f - paraml1.f) * i2 >> 16) - paraml2.f) * arrayOfInt[(-i3)], -(paraml1.h + ((paraml3.h - paraml1.h) * i2 >> 16) - paraml2.h) * arrayOfInt[(-i3)]);
      return;
    }
    a(paraml1, paraml2, paraml3, (paraml1.f + ((paraml3.f - paraml1.f) * i2 >> 16) - paraml2.f) * arrayOfInt[i3], (paraml1.h + ((paraml3.h - paraml1.h) * i2 >> 16) - paraml2.h) * arrayOfInt[i3]);
  }
  
  private static final void b(l paraml1, l paraml2, l paraml3, boolean paramBoolean)
  {
    int[] arrayOfInt1 = ap;
    int i1 = bW;
    int i2 = ao[(aY - 39)];
    paraml1.d = ((short)(int)(7864320L + paraml1.a * i1 / paraml1.c >> 16));
    paraml1.e = ((short)(int)(9830400L - paraml1.b * i1 / paraml1.c >> 16));
    paraml2.d = ((short)(int)(7864320L + paraml2.a * i1 / paraml2.c >> 16));
    paraml2.e = ((short)(int)(9830400L - paraml2.b * i1 / paraml2.c >> 16));
    paraml3.d = ((short)(int)(7864320L + paraml3.a * i1 / paraml3.c >> 16));
    paraml3.e = ((short)(int)(9830400L - paraml3.b * i1 / paraml3.c >> 16));
    l locall;
    if (paraml1.e > paraml2.e)
    {
      locall = paraml1;
      paraml1 = paraml2;
      paraml2 = locall;
    }
    if (paraml1.e > paraml3.e)
    {
      locall = paraml1;
      paraml1 = paraml3;
      paraml3 = locall;
    }
    if (paraml2.e > paraml3.e)
    {
      locall = paraml2;
      paraml2 = paraml3;
      paraml3 = locall;
    }
    int i3 = 0;
    int[] arrayOfInt2 = az;
    int i7 = 0;
    int i8 = (paraml3.d - paraml1.d) * arrayOfInt1[(paraml3.e - paraml1.e)];
    int i9;
    int i10 = (i9 = (paraml3.d - paraml2.d) * arrayOfInt1[(paraml3.e - paraml2.e)]) * (paraml1.e - paraml2.e);
    int i11 = (paraml2.d - paraml1.d) * arrayOfInt1[(paraml2.e - paraml1.e)];
    int i12 = 0;
    int i14 = R;
    int i5;
    int i6;
    int i13;
    if (!paramBoolean)
    {
      for (i4 = paraml1.e; i4 < paraml3.e; i4++)
      {
        i5 = paraml1.d + (i7 >> 16);
        if (i4 >= paraml2.e) {
          i6 = paraml2.d + (i10 >> 16);
        } else {
          i6 = paraml1.d + (i12 >> 16);
        }
        i7 += i8;
        i10 += i9;
        i12 += i11;
        if (i5 > i6)
        {
          i3 = i5;
          i5 = i6;
          i6 = i3;
        }
        i3 = i4 * 240 + i5;
        for (i13 = i5; i13 < i6; i13++) {
          arrayOfInt2[(i3++)] = i2;
        }
      }
      return;
    }
    i1 = (i4 = 255 * i14 >> 8) << 16 | i4 << 8 | i4;
    for (int i4 = paraml1.e; i4 < paraml3.e; i4++)
    {
      i5 = paraml1.d + (i7 >> 16);
      if (i4 >= paraml2.e) {
        i6 = paraml2.d + (i10 >> 16);
      } else {
        i6 = paraml1.d + (i12 >> 16);
      }
      i7 += i8;
      i10 += i9;
      i12 += i11;
      if (i5 > i6)
      {
        i3 = i5;
        i5 = i6;
        i6 = i3;
      }
      i3 = i4 * 240 + i5;
      for (i13 = i5; i13 < i6; i13++) {
        arrayOfInt2[(i3++)] = i1;
      }
    }
  }
  
  private static final void a(int paramInt, int[][] paramArrayOfInt)
  {
    if (paramArrayOfInt[1][2] > 150) {
      paramArrayOfInt[1][2] = '';
    }
    if (paramArrayOfInt[2][2] > 150) {
      paramArrayOfInt[2][2] = '';
    }
    if (paramArrayOfInt[3][2] > 120) {
      paramArrayOfInt[3][2] = 120;
    }
    b(paramInt, paramArrayOfInt);
    a(paramArrayOfInt, k(paramInt));
  }
  
  private static final void b(int paramInt, int[][] paramArrayOfInt)
  {
    int[] arrayOfInt1 = q[paramInt].a;
    int[] arrayOfInt2 = q[paramInt].b;
    int i1 = q[paramInt].n * 7;
    l[] arrayOfl1 = aS;
    l[] arrayOfl2 = aP;
    l locall1 = arrayOfl1[0];
    l locall2 = arrayOfl1[1];
    l locall3 = arrayOfl1[2];
    l locall4 = arrayOfl2[0];
    int i3 = 0;
    int i4 = 0;
    int[] arrayOfInt3 = dm;
    int i5 = dH;
    int i6 = dJ;
    b(arrayOfInt1, q[paramInt].m);
    for (int i7 = 0; i7 < i1; i7 += 7)
    {
      i3 = arrayOfInt2[i7] + 3;
      locall1.a = arrayOfInt1[i3];
      locall1.b = arrayOfInt1[(++i3)];
      locall1.c = arrayOfInt1[(++i3)];
      i3 = arrayOfInt2[(i7 + 1)] + 3;
      locall2.a = arrayOfInt1[i3];
      locall2.b = arrayOfInt1[(++i3)];
      locall2.c = arrayOfInt1[(++i3)];
      i3 = arrayOfInt2[(i7 + 2)] + 3;
      locall3.a = arrayOfInt1[i3];
      locall3.b = arrayOfInt1[(++i3)];
      locall3.c = arrayOfInt1[(++i3)];
      i3 = arrayOfInt2[(i7 + 3)];
      locall1.f = ((short)arrayOfInt3[i3]);
      locall1.h = ((short)arrayOfInt3[(++i3)]);
      i3 = arrayOfInt2[(i7 + 4)];
      locall2.f = ((short)arrayOfInt3[i3]);
      locall2.h = ((short)arrayOfInt3[(++i3)]);
      i3 = arrayOfInt2[(i7 + 5)];
      locall3.f = ((short)arrayOfInt3[i3]);
      locall3.h = ((short)arrayOfInt3[(++i3)]);
      int i2;
      if ((i2 = a(arrayOfl2, arrayOfl1, paramArrayOfInt)) > 0)
      {
        R = (arrayOfInt2[(i7 + 6)] & 0xFF00) >> 8;
        if (aG)
        {
          i3 = i5 - arrayOfInt1[arrayOfInt2[i7]] >> 16;
          i4 = i6 - arrayOfInt1[(arrayOfInt2[i7] + 1)] >> 16;
          if ((i3 = (int)(65536L * (i3 * i3 + i4 * i4) >> 28)) > 255) {
            i3 = 255;
          }
          R += 255 - i3;
          if (R > 255) {
            R = 255;
          }
        }
      }
      if (i2-- > 0)
      {
        aY = arrayOfInt2[(i7 + 6)] & 0xFF;
        if (aY > 38)
        {
          i2 = (byte)(i2 - 1);
          while ((i2 = (byte)(i2 - 1)) >= 0) {
            b(locall4, arrayOfl2[(i2 + 1)], arrayOfl2[(i2 + 2)], true);
          }
        }
        else
        {
          i2 = (byte)(i2 - 1);
          while ((i2 = (byte)(i2 - 1)) >= 0) {
            a(locall4, arrayOfl2[(i2 + 1)], arrayOfl2[(i2 + 2)], true);
          }
        }
      }
    }
  }
  
  private final void z()
  {
    int[] arrayOfInt1 = az;
    byte[] arrayOfByte = dq;
    int[] arrayOfInt2 = cd;
    int i1 = cE * (this.cX << 2) / 360;
    int i2 = this.cX - 1;
    int i3 = 0;
    int i4 = 0;
    int i5 = 150;
    int i6;
    if ((i6 = 270 - cC) > 90) {
      i6 = 90;
    }
    if (i6 > 0) {
      i5 = 150 + i6 * 150 / 90;
    }
    for (int i7 = 0; i7 < i5; i7++)
    {
      i3 = (i7 & i2) * this.cX;
      for (int i8 = 0; i8 < 239; i8++) {
        arrayOfInt1[(i4++)] = arrayOfInt2[arrayOfByte[(i3 + (i8 + i1 & i2))]];
      }
      i4++;
    }
  }
  
  private final void e(Graphics paramGraphics)
  {
    int i1 = (byte)bB.length;
    int i2 = this.aJ.b() + 5;
    int i3 = 320 - i1 * i2 >> 1;
    int i4 = i2 - this.aJ.b() >> 1;
    paramGraphics.setColor(0);
    paramGraphics.fillRect(0, i3, 120, i1 * i2);
    paramGraphics.setColor(65280);
    paramGraphics.drawRect(0, i3 + as * i2, 120, i2);
    for (int i5 = 0; i5 < i1; i5++) {
      this.aJ.a(paramGraphics, this.dc[bB[i5]], 120 - this.aJ.a(this.dc[bB[i5]]) >> 1, i3 + i5 * i2 + i4, 20);
    }
  }
  
  private static final void a(int paramInt1, int paramInt2, int paramInt3, int paramInt4, int[][] paramArrayOfInt)
  {
    int[] arrayOfInt1 = az;
    byte[] arrayOfByte = dp[paramInt1];
    int[] arrayOfInt2 = cc;
    int[] arrayOfInt3 = aA;
    l locall1 = new l(null);
    l locall2 = new l(null);
    locall1.j = paramInt2;
    locall1.k = paramInt3;
    locall1.l = paramInt4;
    b(locall1);
    if (locall1.c <= 0) {
      return;
    }
    int i1 = ar[paramInt1][2];
    int i2 = ar[paramInt1][3];
    locall1.a += (ar[paramInt1][4] << 16);
    locall1.b += (ar[paramInt1][5] << 16);
    locall2.c = locall1.c;
    locall1.d = ((short)(int)(120L + locall1.a * bV / locall1.c));
    locall1.e = ((short)(int)(150L - locall1.b * bV / locall1.c));
    locall2.d = ((short)(int)(120L + locall2.a * bV / locall1.c));
    locall2.e = ((short)(int)(150L - locall2.b * bV / locall1.c));
    int i3 = 0;
    int i4 = 0;
    int i5 = Math.abs(locall1.e - locall2.e << 1);
    int i6 = Math.abs(locall1.d - locall2.d << 1);
    if ((33600 <= i6) || (33600 <= i5)) {
      return;
    }
    int i7 = i1 * arrayOfInt3[i6];
    int i8 = i2 * arrayOfInt3[i5];
    int i9 = locall2.d - i6;
    int i10 = locall1.e;
    if ((paramInt1 < 7) || (paramInt1 > 9)) {
      i10 -= (i5 >> 1);
    }
    int i11 = i9 + i6;
    int i12 = i10 + i5;
    if ((i9 > paramArrayOfInt[4][2] + 120) || (i10 > paramArrayOfInt[2][2] + 150) || (i11 < 120 - paramArrayOfInt[3][2]) || (i12 < 150 - paramArrayOfInt[1][2])) {
      return;
    }
    if (i9 <= 120 - paramArrayOfInt[3][2])
    {
      i3 = i7 * (120 - paramArrayOfInt[3][2] - i9);
      i9 = 120 - paramArrayOfInt[3][2];
    }
    if (i10 <= 150 - paramArrayOfInt[1][2])
    {
      i4 = i8 * (150 - paramArrayOfInt[1][2] - i10);
      i10 = 150 - paramArrayOfInt[1][2];
    }
    if (i11 >= paramArrayOfInt[4][2] + 120) {
      i11 = paramArrayOfInt[4][2] + 120 - 2;
    }
    if (i12 >= paramArrayOfInt[2][2] + 150) {
      i12 = paramArrayOfInt[2][2] + 150 - 3;
    }
    int i13 = 0;
    int i14 = i4;
    int i15 = i10 * 240 + i9;
    int i17 = i12 - i10;
    int i18 = i11 - i9;
    int i19 = 0;
    int i20 = 0;
    if (paramInt1 != 12)
    {
      while (i17-- > 0)
      {
        i15 += 240;
        i16 = i18;
        i19 = i15;
        i13 = i3 + ((i14 >> 18) * i1 << 18);
        while (i16-- > 0)
        {
          i20 = arrayOfInt2[arrayOfByte[(i13 >> 18)]];
          i19++;
          if (i20 != 0) {
            arrayOfInt1[i19] = i20;
          }
          i13 += i7;
        }
        i14 += i8;
      }
      return;
    }
    while (i17-- > 0)
    {
      i15 += 240;
      int i16 = i18;
      i19 = i15;
      i13 = i3 + ((i14 >> 18) * i1 << 18);
      while (i16-- > 0)
      {
        i20 = arrayOfInt2[arrayOfByte[(i13 >> 18)]];
        i19++;
        if (i20 != 0)
        {
          paramInt1 = arrayOfInt1[i19];
          arrayOfInt1[i19] = (((paramInt1 & 0xFF0000) + (i20 & 0xFF0000) >> 17 << 16) + ((paramInt1 & 0xFF00) + (i20 & 0xFF00) >> 9 << 8) + ((paramInt1 & 0xFF) + (i20 & 0xFF) >> 1));
        }
        i13 += i7;
      }
      i14 += i8;
    }
  }
  
  private final void a(Graphics paramGraphics, String paramString, int paramInt1, int paramInt2, byte paramByte)
  {
    Object localObject = null;
    if (h._a1()) {
      return;
    }
    int i1 = paramString.length();
    int i2 = 0;
    if (paramByte == 2)
    {
      while (i2 < 3)
      {
        a(paramGraphics, 5, paramInt1, paramInt2);
        paramInt1 += this.ad[5][2] + 1;
        i2++;
      }
      return;
    }
    if (paramByte == 3)
    {
      while (i2 < 2)
      {
        a(paramGraphics, 5, paramInt1, paramInt2);
        paramInt1 += this.ad[5][2] + 1;
        i2++;
      }
      return;
    }
    if (((paramByte == 1 ? 1 : 0) & (i1 < 3 ? 1 : 0)) != 0)
    {
      a(paramGraphics, 5, paramInt1, paramInt2);
      paramInt1 += this.ad[5][2] + 1;
    }
    if (i1 < 2)
    {
      a(paramGraphics, 5, paramInt1, paramInt2);
      paramInt1 += this.ad[5][2] + 1;
    }
    while (i2 < i1)
    {
      a(paramGraphics, paramString.charAt(i2) - '0' + 6, paramInt1, paramInt2);
      paramInt1 += this.ad[5][2] + 1;
      i2++;
    }
  }
  
  private static final void c(int paramInt, int[][] paramArrayOfInt)
  {
    m localm = s[paramInt];
    l locall;
    (locall = new l(null)).j = localm.n;
    locall.k = localm.o;
    locall.l = localm.p;
    b(locall);
    if (locall.c <= 0) {
      return;
    }
    locall.d = ((short)(int)(120L + locall.a * bV / locall.c));
    locall.e = ((short)(int)(150L - locall.b * bV / locall.c));
    if ((locall.d > paramArrayOfInt[4][2] + 120) || (locall.e > paramArrayOfInt[2][2] + 150) || (locall.d < 120 - paramArrayOfInt[3][2]) || (locall.e < 150 - paramArrayOfInt[1][2])) {
      return;
    }
    X[paramInt] = 3;
    if (locall.e - 5 > 150) {
      X[paramInt] = 1;
    }
    if (locall.e + 5 < 150) {
      X[paramInt] = 2;
    }
  }
  
  private static final void d(int paramInt, int[][] paramArrayOfInt)
  {
    m localm;
    boolean bool = (localm = s[paramInt]).k;
    int[] arrayOfInt1 = az;
    byte[] arrayOfByte = dr[localm.f];
    int[] arrayOfInt2 = ce[localm.y];
    int[] arrayOfInt3 = aA;
    l locall1 = new l(null);
    l locall2 = new l(null);
    locall1.j = localm.n;
    locall1.k = localm.o;
    locall1.l = (localm.p - 8192000);
    b(locall1);
    if (locall1.c <= 0) {
      return;
    }
    int i1 = aM[(localm.f * 5)];
    int i2 = aM[(localm.f * 5 + 1)];
    locall1.a += (aM[(localm.f * 5 + 2)] << 16);
    locall1.b += (aM[(localm.f * 5 + 3)] << 16);
    locall2.c = locall1.c;
    locall1.d = ((short)(int)(120L + locall1.a * bV / locall1.c));
    locall1.e = ((short)(int)(150L - locall1.b * bV / locall1.c));
    locall2.d = ((short)(int)(120L + locall2.a * bV / locall2.c));
    locall2.e = ((short)(int)(150L - locall2.b * bV / locall2.c));
    int i3 = 0;
    int i4 = 0;
    int i5 = Math.abs(locall1.e - locall2.e << 1);
    int i6 = Math.abs(locall1.d - locall2.d << 1);
    if ((33600 <= i6) || (33600 <= i5)) {
      return;
    }
    int i7 = i1 * arrayOfInt3[i6];
    int i8 = i2 * arrayOfInt3[i5];
    int i9 = locall2.d - i6;
    int i10 = locall1.e - i5;
    int i11 = i9 + i6;
    int i12 = i10 + i5;
    if ((i9 > paramArrayOfInt[4][2] + 120) || (i10 > paramArrayOfInt[2][2] + 150) || (i11 < 120 - paramArrayOfInt[3][2]) || (i12 < 150 - paramArrayOfInt[1][2])) {
      return;
    }
    if (i9 <= 120 - paramArrayOfInt[3][2])
    {
      i3 = i7 * (120 - paramArrayOfInt[3][2] - i9);
      i9 = 120 - paramArrayOfInt[3][2];
    }
    if (i10 <= 150 - paramArrayOfInt[1][2])
    {
      i4 = i8 * (150 - paramArrayOfInt[1][2] - i10);
      i10 = 150 - paramArrayOfInt[1][2];
    }
    if (i11 >= paramArrayOfInt[4][2] + 120) {
      i11 = paramArrayOfInt[4][2] + 120 - 2;
    }
    if (i12 >= paramArrayOfInt[2][2] + 150) {
      i12 = paramArrayOfInt[2][2] + 150 - 2;
    }
    X[paramInt] = 3;
    if (i10 + (i5 >> 3) > 150) {
      X[paramInt] = 1;
    }
    if (i10 + (i5 >> 2) < 150) {
      X[paramInt] = 2;
    }
    int i13 = 0;
    int i14 = i4;
    int i15 = 0;
    int i16 = i10 * 240 + i9;
    int i18 = i12 - i10;
    int i19 = i11 - i9;
    i15 = 240 - i19;
    int i20 = 0;
    int i17;
    if (!bool)
    {
      while (i18-- > 0)
      {
        i17 = i19;
        i13 = i3 + ((i14 >> 18) * i1 << 18);
        while (i17-- > 0)
        {
          i20 = arrayOfInt2[arrayOfByte[(i13 >> 18)]];
          i16++;
          if (i20 != 0) {
            arrayOfInt1[i16] = i20;
          }
          i13 += i7;
        }
        i14 += i8;
        i16 += i15;
      }
      return;
    }
    int i21 = i1 - 1 << 18;
    int i22 = i10 * 240 + i9;
    while (i18-- > 0)
    {
      i13 = i3;
      i17 = i19;
      i16 = i22;
      i5 = (i14 >> 18) * i1;
      while (i17-- > 0)
      {
        i20 = arrayOfInt2[arrayOfByte[(i5 + (Math.abs(i21 - i13) >> 18))]];
        i16++;
        if (i20 != 0) {
          arrayOfInt1[i16] = i20;
        }
        i13 += i7;
      }
      i14 += i8;
      i22 += 240;
    }
  }
  
  private static void a(int paramInt1, int paramInt2, int paramInt3, boolean paramBoolean)
  {
    int[] arrayOfInt1 = cf[paramInt1];
    byte[] arrayOfByte = ds[paramInt1];
    int[] arrayOfInt2 = az;
    int[] arrayOfInt3 = cb;
    int i4 = s[0].m;
    int i2 = arrayOfInt1.length;
    for (int i1 = 0; i1 < i2; i1++)
    {
      i3 = arrayOfInt1[i1];
      arrayOfInt3[i1] = ((i3 & 0xFF000000) + (((i3 & 0xFF0000) >> 16) * i4 >> 8 << 16) + (((i3 & 0xFF00) >> 8) * i4 >> 8 << 8) + ((i3 & 0xFF) * i4 >> 8));
    }
    int i5 = av[(paramInt1 << 1)];
    int i6 = 0;
    int i7 = 0;
    int i9 = av[((paramInt1 << 1) + 1)];
    if (i5 < 0) {
      i5 += 256;
    }
    if (i9 < 0) {
      i9 += 256;
    }
    i9 -= ((256 - paramInt3) * i9 >> 8);
    int i3 = i5 - ((256 - paramInt2) * i5 >> 8);
    int i8 = 240 - i3;
    paramInt2 = i5 - i3;
    dI = (short)(240 - i3);
    dK = (short)(300 - i9 - 2);
    i6 = 240 * (300 - i9 - 2) + (paramBoolean ? 0 : 240 - i3);
    for (i2 = 0; i2 < i9; i2++)
    {
      for (i1 = 0; i1 < i3; i1++)
      {
        if ((paramInt1 = arrayOfInt3[arrayOfByte[(i7++)]]) != 0) {
          arrayOfInt2[i6] = paramInt1;
        }
        i6++;
      }
      i6 += i8;
      i7 += paramInt2;
    }
  }
  
  private final void f(Graphics paramGraphics)
  {
    if (g == 0) {
      paramGraphics.drawRGB(az, 0, 240, 0, 10, 240, 298, false);
    }
    paramGraphics.setColor(0);
    paramGraphics.fillRect(0, 0, 240, 10);
    paramGraphics.fillRect(0, 308, 240, 14);
    paramGraphics.setClip(0, 0, 240, 320);
    int i1;
    if ((aD) && (this.cI >= 0))
    {
      if (this.W != 0)
      {
        i1 = (320 - n.g[30]) * (4 - this.W) >> 2;
        int i2 = this.cM + i1;
        int i3;
        if ((i3 = this.cN) >= this.cJ) {
          i3 = this.cJ;
        }
        String[] arrayOfString = this.da[this.cI];
        n.b(paramGraphics, 0, -(n.g[31] * (3 - this.W) >> 2));
        n.a(paramGraphics, 0, (320 - n.g[30]) * (3 - this.W) >> 2);
        for (int i4 = this.cK; i4 < i3 + this.cK; i4++) {
          this.aJ.a(paramGraphics, arrayOfString[i4], 0, i2 + (i4 - this.cK) * n.u, 20);
        }
        if (this.cL > 0) {
          this.aJ.a(paramGraphics, arrayOfString[this.cN], 0, this.cL, 0, i2 + (this.cN - this.cK) * n.u, 20);
        }
        paramGraphics.setColor(16777215);
        paramGraphics.drawLine(239, 319, 234, 314);
        paramGraphics.drawLine(239, 314, 234, 319);
      }
      return;
    }
    if (this.W != 0)
    {
      i1 = 320 - n.g[30];
      n.b(paramGraphics, 0, -(n.g[31] * (3 - this.W) >> 2));
      n.a(paramGraphics, 0, i1 * (3 - this.W) >> 2);
      return;
    }
    if (!s[0].i)
    {
      i1 = aw >> 1;
      paramGraphics.setColor(16777215);
      paramGraphics.drawLine(120, 152 - i1, 120, 157 - i1);
      paramGraphics.drawLine(120, 168 + i1, 120, 163 + i1);
      paramGraphics.drawLine(112 - i1, 160, 117 - i1, 160);
      paramGraphics.drawLine(128 + i1, 160, 123 + i1, 160);
    }
  }
  
  static void b(int paramInt)
  {
    int i1 = 76800;
    int[] arrayOfInt = az;
    do
    {
      arrayOfInt[i1] = paramInt;
      i1--;
    } while (i1 >= 0);
  }
  
  private void A()
  {
    if (cn == null) {
      return;
    }
    for (int i1 = 0; i1 < cn.length; i1++) {
      if (s[0].r == cn[i1])
      {
        if ((ax) && (bM >= 2))
        {
          if (ax) {
            h.D -= 65557L;
          }
          return;
        }
        i(cn[i1]);
        return;
      }
    }
  }
  
  private final boolean b(int paramInt1, int paramInt2)
  {
    byte[][] arrayOfByte = this.b;
    byte[] arrayOfByte1 = this.Z;
    int i1 = 0;
    int i2 = 0;
    if (paramInt1 == 0) {
      paramInt1 = 21;
    }
    if (paramInt2 == 0) {
      paramInt2 = 21;
    }
    for (int i3 = 0; i3 < arrayOfByte.length; i3 = (short)(i3 + 1)) {
      if (arrayOfByte[i3][0] == paramInt1)
      {
        i2 = 1;
        if (arrayOfByte[i3][1] == paramInt2)
        {
          arrayOfByte1[1] = ((byte)i3);
          i1 = 1;
          break;
        }
      }
      else
      {
        if (i2 != 0) {
          break;
        }
      }
    }
    if (i1 != 0)
    {
      if (arrayOfByte[i3][6] != 0)
      {
        if (e(2) == 0) {
          arrayOfByte1[2] = 2;
        } else {
          arrayOfByte1[2] = 6;
        }
      }
      else {
        arrayOfByte1[2] = 2;
      }
      arrayOfByte1[7] = 1;
      return true;
    }
    return false;
  }
  
  private final void B()
  {
    if (db)
    {
      db = false;
      this.m = false;
      a(as);
      return;
    }
    b(s[0].z);
    aU = 0;
    j(s[0]);
  }
  
  final void b()
  {
    Display.getDisplay(NET_Lizard.a).setCurrent(this);
    this.dt.start();
  }
  
  private static int a(byte[] paramArrayOfByte, boolean paramBoolean)
  {
    int i1 = 0;
    int i2 = 0;
    if (paramArrayOfByte[3] == 1) {
      i2 = 1;
    }
    int i3;
    if ((i3 = paramArrayOfByte[4]) < 0) {
      i3 += 256;
    }
    if (i2 != 0) {
      i1 = 4 + i3 * 4;
    } else {
      i1 = 4 + i3 * 3;
    }
    int i4 = paramArrayOfByte[(++i1)];
    int i5 = paramArrayOfByte[(++i1)];
    if (i4 < 0) {
      i4 += 256;
    }
    if (i5 < 0) {
      i5 += 256;
    }
    if (paramBoolean) {
      return i4;
    }
    return i5;
  }
  
  private final void b(j paramj)
  {
    if (paramj.t < 6)
    {
      if ((cY[1] != 0) && (cY[2] != 0))
      {
        if ((cZ == 1) || (cZ == 2))
        {
          ag = paramj;
          af = true;
        }
        return;
      }
      if (cY[1] == 0)
      {
        cY[1] = paramj.t;
        if (dN < 0) {
          cZ = 1;
        }
      }
      else
      {
        cY[2] = paramj.t;
        if (dN < 0) {
          cZ = 2;
        }
      }
      if (dN < 0)
      {
        dC = cY[cZ];
        ae = 8;
      }
      if (paramj.t == 1)
      {
        T[0][1] = 7;
        T[1][2] = 7;
      }
      paramj.u = false;
      return;
    }
    switch (paramj.t)
    {
    case 6: 
      m tmp233_232 = s[0];
      tmp233_232.l = ((short)(tmp233_232.l + 50));
      if (s[0].l > 100) {
        s[0].l = 100;
      }
      paramj.u = false;
      this.bG = 30;
      return;
    case 7: 
      int tmp285_284 = 1;
      byte[] tmp285_283 = T[1];
      tmp285_283[tmp285_284] = ((byte)(tmp285_283[tmp285_284] + 14));
      if (T[1][1] > 35) {
        T[1][1] = 35;
      }
      paramj.u = false;
      return;
    case 8: 
      int tmp325_324 = 2;
      byte[] tmp325_323 = T[1];
      tmp325_323[tmp325_324] = ((byte)(tmp325_323[tmp325_324] + 30));
      int tmp338_337 = 3;
      byte[] tmp338_336 = T[1];
      tmp338_336[tmp338_337] = ((byte)(tmp338_336[tmp338_337] + 30));
      int tmp351_350 = 4;
      byte[] tmp351_349 = T[1];
      tmp351_349[tmp351_350] = ((byte)(tmp351_349[tmp351_350] + 30));
      if (T[1][2] > 90) {
        T[1][2] = 90;
      }
      if (T[1][3] > 90) {
        T[1][3] = 90;
      }
      if (T[1][4] > 90) {
        T[1][4] = 90;
      }
      if ((dF > 1) && (dF < 5)) {
        this.bH = 30;
      }
      paramj.u = false;
      return;
    case 9: 
      cY[3] = 6;
      byte[] tmp461_458 = T[0];
      tmp461_458[6] = ((byte)(tmp461_458[6] + 3));
      if (T[0][6] > 6) {
        T[0][6] = 6;
      }
      paramj.u = false;
      return;
    case 10: 
      int tmp502_501 = 5;
      byte[] tmp502_500 = T[1];
      tmp502_500[tmp502_501] = ((byte)(tmp502_500[tmp502_501] + 3));
      if (T[1][5] > 12) {
        T[1][5] = 12;
      }
      paramj.u = false;
      if (dF == 5)
      {
        this.bH = 30;
        return;
      }
      break;
    case 11: 
      
    case 120: 
      if (this.bf == 0) {
        this.bf = 2;
      }
      if (this.bf == 1) {
        this.bf = 3;
      }
      this.bE = 30;
      paramj.u = false;
      return;
    case 121: 
      if (this.bf == 0) {
        this.bf = 1;
      }
      if (this.bf == 2) {
        this.bf = 3;
      }
      this.bF = 30;
      paramj.u = false;
    }
  }
  
  public final void hideNotify()
  {
    super.hideNotify();
    if ((!bA) && (!this.m))
    {
      bA = true;
      this.m = true;
      this.bD = 2;
      n.s = 11;
      n.f = 16;
    }
  }
  
  private static void a(byte[] paramArrayOfByte)
  {
    for (int i2 = 63; i2 >= 0; i2--) {
      for (int i3 = 31; i3 >= 0; i3--)
      {
        int i1 = paramArrayOfByte[(i3 * 64 + i2)];
        paramArrayOfByte[(i3 * 64 + i2)] = paramArrayOfByte[((63 - i3) * 64 + i2)];
        paramArrayOfByte[((63 - i3) * 64 + i2)] = i1;
      }
    }
  }
  
  protected final void keyPressed(int paramInt)
  {
    Object localObject = null;
    if (h._a1()) {
      return;
    }
    if (h.a(paramInt = b.a(paramInt))) {
      return;
    }
    this.am = false;
    if (paramInt == -1)
    {
      paramInt = 50;
      this.am = true;
    }
    if (paramInt == -2)
    {
      paramInt = 56;
      this.am = true;
    }
    if (paramInt == -3)
    {
      paramInt = 52;
      this.am = true;
    }
    if (paramInt == -4)
    {
      paramInt = 54;
      this.am = true;
    }
    if (paramInt == -6) {
      this.am = true;
    }
    if ((paramInt == -6) || (paramInt == -5)) {
      paramInt = 53;
    }
    if (paramInt == -7)
    {
      paramInt = this.h;
      this.am = true;
    }
    if (paramInt == 50) {
      this.bK = ((short)(this.bK | 0x1));
    }
    if (paramInt == 56) {
      this.bK = ((short)(this.bK | 0x2));
    }
    if (paramInt == 52) {
      this.bK = ((short)(this.bK | 0x4));
    }
    if (paramInt == 54) {
      this.bK = ((short)(this.bK | 0x8));
    }
    if (paramInt == 49) {
      this.bK = ((short)(this.bK | 0x10));
    }
    if (paramInt == 51) {
      this.bK = ((short)(this.bK | 0x20));
    }
    if (paramInt == 53) {
      this.bK = ((short)(this.bK | 0x40));
    }
    if (paramInt == 55) {
      this.bK = ((short)(this.bK | 0x80));
    }
    if (paramInt == 57) {
      this.bK = ((short)(this.bK | 0x100));
    }
    if ((paramInt == 42) || (paramInt == this.h) || (paramInt == 48))
    {
      this.bc = true;
      this.bd = false;
    }
    else
    {
      this.bd = true;
      this.bc = false;
    }
    this.bh = false;
    this.be = paramInt;
  }
  
  protected final void keyReleased(int paramInt)
  {
    paramInt = b.a(paramInt);
    if (h.b()) {
      return;
    }
    if (this.bh) {
      this.be = 0;
    } else {
      bi = true;
    }
    switch (paramInt)
    {
    case -1: 
    case 50: 
      this.bK = ((short)(this.bK & 0x1FE));
      return;
    case -2: 
    case 56: 
      this.bK = ((short)(this.bK & 0x1FD));
      return;
    case -3: 
    case 52: 
      this.bK = ((short)(this.bK & 0x1FB));
      return;
    case -4: 
    case 54: 
      this.bK = ((short)(this.bK & 0x1F7));
      return;
    case 49: 
      this.bK = ((short)(this.bK & 0x1EF));
      return;
    case 51: 
      this.bK = ((short)(this.bK & 0x1DF));
      return;
    case -6: 
    case -5: 
    case 53: 
      this.bK = ((short)(this.bK & 0x1BF));
      return;
    case 55: 
      this.bK = ((short)(this.bK & 0x152));
      return;
    case 57: 
      this.bK = ((short)(this.bK & 0xFF));
    }
  }
  
  private final void C()
  {
    if ((!bA) && (!aD) && (s != null) && (!s[0].i))
    {
      if ((this.bK & 0x1) != 0) {
        Y();
      }
      if ((this.bK & 0x2) != 0) {
        V();
      }
      if ((this.bK & 0x4) != 0) {
        b((byte)(cQ + 1));
      }
      if ((this.bK & 0x8) != 0) {
        c((byte)(cQ + 1));
      }
      if ((this.bK & 0x10) != 0) {
        b(cQ);
      }
      if ((this.bK & 0x20) != 0) {
        c(cQ);
      }
      if ((this.bK & 0x40) != 0) {
        B();
      }
      if ((this.bK & 0x80) != 0) {
        W();
      }
      if ((this.bK & 0x100) != 0) {
        X();
      }
    }
  }
  
  private final void D()
  {
    this.bh = true;
    int i1 = 0;
    int i2 = 0;
    int i3 = 0;
    int i4 = 0;
    int i5 = 0;
    if (this.bD == 5)
    {
      this.ai = false;
      if ((this.be == 35) && (!this.am))
      {
        this.ah += "#";
      }
      else if (!this.am)
      {
        this.ah += this.be - 48;
        bi = true;
      }
      if (this.ah.length() >= 4) {
        this.ah = "";
      }
    }
    switch (this.be)
    {
    case 49: 
      break;
    case 50: 
      i3 = 1;
      break;
    case 52: 
      i1 = 1;
      break;
    case 53: 
      i5 = 1;
      this.ai = true;
      break;
    case 54: 
      i2 = 1;
      break;
    case 55: 
      break;
    case 56: 
      i4 = 1;
    }
    if (this.be == 35)
    {
      if (this.bD == 11)
      {
        if (db)
        {
          db = false;
          this.m = false;
          return;
        }
        if ((bA) && (this.m))
        {
          bA = false;
          this.m = false;
          this.bD = 11;
          n.s = 2;
          n.f = 16;
          return;
        }
        if (aD)
        {
          if (bM != 1) {
            while (aD)
            {
              for (int i6 = 0; i6 < dv; i6++) {
                h(s[i6]);
              }
              ah();
              ae();
              v();
            }
          }
          i(-1);
          return;
        }
        bA = true;
        this.m = true;
        this.bD = 2;
        n.s = 11;
        n.f = 16;
        return;
      }
      if (this.bD != 5) {
        n.b();
      } else if (this.am) {
        n.b();
      }
    }
    if ((this.be == 42) && (bM == 2)) {
      if (db)
      {
        db = false;
        this.m = false;
      }
      else
      {
        db = true;
        this.m = true;
      }
    }
    if ((this.be == 48) && (!this.m)) {
      w();
    }
    if (bA)
    {
      if (i3 != 0) {
        n.f();
      }
      if (i4 != 0) {
        n.c();
      }
      if (i1 != 0)
      {
        n.d();
        bi = true;
      }
      if (i2 != 0)
      {
        n.e();
        bi = true;
      }
      if (i5 != 0)
      {
        this.bz.a();
        bi = true;
      }
      return;
    }
    if ((s[0].i) && (dG >= 254) && ((i3 != 0) || (i4 != 0) || (i1 != 0) || (i2 != 0) || (i5 != 0)))
    {
      this.cu = true;
      this.bD = 9;
      e();
    }
  }
  
  private final void E()
  {
    D();
    if (bi)
    {
      this.be = 0;
      bi = false;
    }
  }
  
  private static void F()
  {
    m[] arrayOfm = s;
    if (bM == 10)
    {
      j localj1 = l[0];
      if (l[1].m < 157286400)
      {
        l[1].m += 6553600;
      }
      else if (n[2] < 0)
      {
        n[2] += 655360;
        localj1.o += 655360;
        localj1.r = arrayOfm[0].r;
      }
      else
      {
        o[0].e = true;
        localj1.r = 1;
      }
    }
    g localg;
    if (bM == 9)
    {
      localg = q[l[4].r];
      if (bn < 0)
      {
        if (arrayOfm[0].o < 6553600) {
          bn = 0;
        }
        return;
      }
      bI = -1;
      if (bm[bn] > n[2])
      {
        if (localg.h <= l[4].o) {
          for (i1 = 0; i1 < q.length; i1++) {
            if (q[i1].k == l[4].o)
            {
              l[4].r = ((short)i1);
              break;
            }
          }
        }
        n[2] += 655360;
        l[4].o += 655360;
      }
      else
      {
        bI = bn;
      }
      int i1 = 20 - (l[4].r - 8);
      for (int i2 = 19; i2 >= i1; i2--) {
        o[i2].e = true;
      }
      if (bn == 3) {
        return;
      }
      if ((bn == 0) && (arrayOfm[6].i) && (arrayOfm[7].i) && (arrayOfm[8].i) && (arrayOfm[9].i) && (arrayOfm[10].i)) {
        bn = (byte)(bn + 1);
      }
      if ((bn == 1) && (arrayOfm[11].i) && (arrayOfm[12].i) && (arrayOfm[13].i) && (arrayOfm[14].i) && (arrayOfm[15].i)) {
        bn = (byte)(bn + 1);
      }
      if ((bn == 2) && (arrayOfm[1].i) && (arrayOfm[2].i) && (arrayOfm[3].i) && (arrayOfm[4].i) && (arrayOfm[5].i)) {
        bn = (byte)(bn + 1);
      }
    }
    if (bM == 4)
    {
      j localj2 = l[14];
      localg = null;
      if (bn < 0)
      {
        if (arrayOfm[0].o > 262144000) {
          bn = 4;
        }
        return;
      }
      if (bm[bn] > n[2])
      {
        n[2] += 655360;
        localj2.o += 655360;
        localj2.r = arrayOfm[0].r;
      }
    }
  }
  
  private final void G()
  {
    int i1 = this.bo * 3;
    m localm = s[0];
    short[] arrayOfShort = bp;
    int i2 = s[0].n >> 16;
    int i3 = s[0].o >> 16;
    int i4 = s[0].p >> 16;
    if (aH)
    {
      localm.m = 255;
      return;
    }
    localm.m = 0;
    for (int i8 = 0; i8 < i1; i8 += 3)
    {
      int i5 = i2 - arrayOfShort[i8];
      int i6 = i3 - arrayOfShort[(i8 + 1)];
      int i7 = i4 - arrayOfShort[(i8 + 2)];
      if ((i5 = (int)(65536L * (i5 * i5 + i6 * i6 + i7 * i7) >> 30)) > 255) {
        i5 = 255;
      }
      m tmp153_152 = localm;
      tmp153_152.m = ((short)(tmp153_152.m + (255 - i5)));
      if (localm.m > 255) {
        localm.m = 255;
      }
      if (localm.m < 20) {
        localm.m = 20;
      }
    }
    if (localm.m < 0) {
      localm.m = 0;
    }
  }
  
  private static final boolean a(m paramm1, m paramm2)
  {
    if (paramm1.r == paramm2.r) {
      return true;
    }
    int i1 = -1;
    e locale1 = dk;
    e locale2 = aE;
    locale1.a = paramm1.n;
    locale1.b = paramm1.o;
    locale1.c = paramm1.p;
    locale2.a = paramm2.n;
    locale2.b = paramm2.o;
    locale2.c = paramm2.p;
    int i2 = paramm1.r;
    while ((i1 = a(i2, locale1, locale2, i1)) != -1)
    {
      if (o[i1].c == i2) {
        i2 = o[i1].d;
      } else {
        i2 = o[i1].c;
      }
      if (paramm2.r == i2) {
        return true;
      }
      if ((bX[i2] == 1) || (bX[i2] < 0)) {
        return false;
      }
    }
    return false;
  }
  
  private final void H()
  {
    String str = null;
    if (h._a0()) {
      return;
    }
    this.aJ = d.a();
    az = new int[76800];
    Q();
    this.bz = new n(this);
    str = f.g.d(f.a(C));
    this.dc = f.g.a(str, this.aJ, 0, false);
    this.cJ = ((byte)((320 - n.g[32] - 5) / this.aJ.b()));
    this.cM = ((short)(n.g[32] + (320 - n.g[32] - this.cJ * this.aJ.b() >> 1)));
    this.cJ = ((byte)(this.cJ - 1));
    String[] arrayOfString = f.g.a(f.g.d(f.a(G)), this.aJ, 0, false);
    this.da = new String[arrayOfString.length][];
    for (int i1 = 0; i1 < arrayOfString.length; i1++) {
      this.da[i1] = f.g.a(arrayOfString[i1], this.aJ, 240, true);
    }
    j();
    if (!this.an) {
      return;
    }
    try
    {
      try
      {
        this.bt = f.a(f.a(O));
      }
      catch (OutOfMemoryError localOutOfMemoryError) {}
      a(false);
    }
    catch (Exception localException) {}
    this.be = 0;
  }
  
  private final void I()
  {
    this.Z = new byte[8];
    this.Z[0] = 0;
    this.Z[1] = 50;
    this.Z[3] = 27;
    this.Z[4] = 26;
    this.Z[5] = 3;
    this.Z[6] = 12;
    byte[] arrayOfByte = f.g.a(f.a(A), -1);
    this.a = new byte[100];
    int i1 = 0;
    for (int i2 = 1; i2 < 50; i2++)
    {
      this.a[(i2 << 1)] = arrayOfByte[i1];
      this.a[((i2 << 1) + 1)] = arrayOfByte[(i1 + 1)];
      i1 += 2;
    }
    int i3 = (arrayOfByte.length - i1) / 10;
    this.b = new byte[i3][];
    for (int i4 = 0; i4 < i3; i4++)
    {
      this.b[i4] = new byte[10];
      for (int i5 = 0; i5 < 10; i5++) {
        this.b[i4][i5] = arrayOfByte[(i1 + i5)];
      }
      i1 += 10;
    }
  }
  
  private static int[] b(byte[] paramArrayOfByte)
  {
    int i2 = 3;
    int i3 = 0;
    if (paramArrayOfByte[3] == 1) {
      i3 = 1;
    }
    int i1;
    if ((i1 = (i2++)[4]) < 0) {
      i1 += 256;
    }
    int[] arrayOfInt = new int[i1];
    if (i3 == 0)
    {
      int i4 = 0;
      tmpTernaryOp = paramArrayOfByte;
      while (i4 < i1)
      {
        arrayOfInt[i4] = ((paramArrayOfByte[(++i2)] << 16) + (paramArrayOfByte[(++i2)] << 8) + paramArrayOfByte[(++i2)]);
        i4++;
      }
    }
    else
    {
      for (int i5 = 0; i5 < i1; i5++) {
        if (paramArrayOfByte[(++i2)] != 0)
        {
          arrayOfInt[i5] = (-16777216 + (paramArrayOfByte[(++i2)] << 16) + (paramArrayOfByte[(++i2)] << 8) + paramArrayOfByte[(++i2)]);
        }
        else
        {
          i2 += 3;
          arrayOfInt[i5] = 0;
        }
      }
    }
    return arrayOfInt;
  }
  
  private static byte[] a(byte[] paramArrayOfByte, boolean paramBoolean, int paramInt1, int paramInt2, int paramInt3, int paramInt4)
  {
    int i2 = 0;
    int i3 = 0;
    if (paramArrayOfByte[3] == 1) {
      i3 = 1;
    }
    int i4;
    if ((i4 = paramArrayOfByte[4]) < 0) {
      i4 += 256;
    }
    if (i3 != 0) {
      i2 = 4 + i4 * 4;
    } else {
      i2 = 4 + i4 * 3;
    }
    int i5;
    int i6;
    byte[] arrayOfByte;
    int i7;
    if (!paramBoolean)
    {
      i5 = paramArrayOfByte[(++i2)];
      i6 = paramArrayOfByte[(++i2)];
      if (i5 < 0) {
        i5 += 256;
      }
      if (i6 < 0) {
        i6 += 256;
      }
      if (i5 == 0) {
        i5 = 256;
      }
      if (i6 == 0) {
        i6 = 256;
      }
      int i1;
      arrayOfByte = new byte[i1 = i5 * i6];
      for (i7 = 0; i7 < i1; i7++) {
        arrayOfByte[i7] = paramArrayOfByte[(++i2)];
      }
    }
    else
    {
      i5 = paramArrayOfByte[(++i2)];
      i2++;
      i6 = 0;
      if (i5 < 0) {
        i5 += 256;
      }
      i7 = 0;
      arrayOfByte = new byte[paramInt3 * paramInt4];
      i2 += paramInt2 * i5 + paramInt1;
      i2++;
      for (int i9 = 0; i9 < paramInt4; i9++)
      {
        int i8 = i9 * i5 + i2;
        for (int i10 = 0; i10 < paramInt3; i10++)
        {
          arrayOfByte[i7] = paramArrayOfByte[(i8 + i10)];
          i7++;
        }
      }
    }
    return arrayOfByte;
  }
  
  private static void J()
  {
    byte[] arrayOfByte;
    int i1;
    ab = new byte[i1 = (arrayOfByte = f.g.a(f.a(H), -1)).length / 6][6];
    for (int i2 = 0; i2 < i1; i2++)
    {
      int i4 = i2 * 6;
      for (int i3 = 0; i3 < 6; i3++) {
        ab[i2][i3] = arrayOfByte[(i4 + i3)];
      }
    }
  }
  
  private static void K()
  {
    byte[] arrayOfByte;
    int i1;
    ac = new byte[i1 = (arrayOfByte = f.g.a(f.a(E), -1)).length / 6][6];
    for (int i2 = 0; i2 < i1; i2++)
    {
      int i4 = i2 * 6;
      for (int i3 = 0; i3 < 6; i3++) {
        ac[i2][i3] = arrayOfByte[(i4 + i3)];
      }
    }
    try
    {
      aa = f.a(f.a(F));
      return;
    }
    catch (Exception localException) {}
  }
  
  private final void L()
  {
    byte[] arrayOfByte;
    int i1 = (arrayOfByte = f.g.a(f.a(I), -1)).length / 4;
    this.ad = new byte[i1][4];
    for (int i2 = 0; i2 < i1; i2++)
    {
      int i4 = i2 * 4;
      for (int i3 = 0; i3 < 4; i3++) {
        this.ad[i2][i3] = arrayOfByte[(i4 + i3)];
      }
    }
    try
    {
      this.aN = f.a(f.a(J));
      return;
    }
    catch (Exception localException) {}
  }
  
  private static int M()
  {
    byte[] arrayOfByte;
    int i1;
    int i5 = (short)(i1 = (arrayOfByte = f.g.a("cu", -1)).length / 7);
    ar = new short[i1][7];
    for (int i2 = 0; i2 < i1; i2++)
    {
      int i4 = i2 * 7;
      for (int i3 = 0; i3 < 7; i3++)
      {
        ar[i2][i3] = ((short)arrayOfByte[(i4 + i3)]);
        if (ar[i2][i3] < 0)
        {
          int tmp77_76 = i3;
          short[] tmp77_75 = ar[i2];
          tmp77_75[tmp77_76] = ((short)(tmp77_75[tmp77_76] + 256));
        }
      }
    }
    return i5;
  }
  
  private static int N()
  {
    byte[] arrayOfByte;
    int i1;
    int i5 = (short)(i1 = (arrayOfByte = f.g.a("cuu", -1)).length / 7);
    at = new short[i1][7];
    for (int i2 = 0; i2 < i1; i2++)
    {
      int i4 = i2 * 7;
      for (int i3 = 0; i3 < 7; i3++)
      {
        at[i2][i3] = ((short)arrayOfByte[(i4 + i3)]);
        if (at[i2][i3] < 0)
        {
          int tmp77_76 = i3;
          short[] tmp77_75 = at[i2];
          tmp77_75[tmp77_76] = ((short)(tmp77_75[tmp77_76] + 256));
        }
      }
    }
    return i5;
  }
  
  private final void h(int paramInt)
  {
    int i1 = -2;
    byte[] arrayOfByte = f.g.a(f.a(D) + paramInt, -1);
    i1 += 2;
    int i2;
    if ((i2 = c(arrayOfByte[0], arrayOfByte[1])) != 0) {
      cn = new byte[i2];
    }
    for (int i5 = 0; i5 < i2; i5++)
    {
      i1 += 2;
      cn[i5] = ((byte)c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
    }
    i1 += 2;
    cF[0] = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
    i1 += 2;
    cF[1] = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
    i1 += 2;
    cF[2] = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
    i1 += 2;
    cC = c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
    i1 += 2;
    cE = c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
    if (cE > 361) {
      cE -= 65536;
    }
    if (cC > 361) {
      cC -= 65536;
    }
    if (cE < 0) {
      cE = -cE;
    } else {
      cE = 360 - cE;
    }
    if (cE == 360) {
      cE = 0;
    }
    if (cC < 0) {
      cC = 270 + cC;
    } else {
      cC = 270 - cC;
    }
    if (cC == 360) {
      cC = 0;
    }
    i1 += 2;
    cx = c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
    i1 += 2;
    int i6;
    j = new int[i6 = c(arrayOfByte[i1], arrayOfByte[(i1 + 1)])];
    for (int i7 = 0; i7 < i6; i7 += 3)
    {
      i1 += 2;
      j[i7] = ((int)(65536 * c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 10000L));
      i1 += 2;
      j[(i7 + 1)] = ((int)(65536 * c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 10000L));
      i1 += 2;
      j[(i7 + 2)] = ((int)(65536 * c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 10000L));
    }
    i1 += 2;
    dm = new int[i6 = c(arrayOfByte[i1], arrayOfByte[(i1 + 1)])];
    for (int i8 = 0; i8 < i6; i8 += 2)
    {
      i1 += 2;
      dm[i8] = ((int)(64 * c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 100L));
      i1 += 2;
      dm[(i8 + 1)] = ((int)(64 * c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 100L));
    }
    q = new g[cx];
    bX = new byte[cx];
    for (int i9 = 0; i9 < cx; i9++) {
      q[i9] = new g(null);
    }
    int i18;
    int i24;
    int i22;
    for (int i13 = 0; i13 < cx; i13++)
    {
      i1 += 2;
      q[i13].f = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
      i1 += 2;
      q[i13].g = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
      i1 += 2;
      q[i13].h = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
      i1 += 2;
      q[i13].i = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
      i1 += 2;
      q[i13].j = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
      i1 += 2;
      q[i13].k = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
      i1 += 2;
      int i11 = c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
      i1 += 2;
      int i10 = c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
      q[i13].a = new int[i11 * 6];
      q[i13].m = i11;
      q[i13].b = new int[i10 * 7];
      q[i13].n = i10;
      for (i14 = 0; i14 < i11; i14++)
      {
        i1 += 2;
        q[i13].a[(i14 * 6)] = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
        i1 += 2;
        q[i13].a[(i14 * 6 + 1)] = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
        i1 += 2;
        q[i13].a[(i14 * 6 + 2)] = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
      }
      int[] arrayOfInt = q[i13].b;
      for (i17 = 0; i17 < i10; i17++)
      {
        i16 = i17 * 7;
        i1 += 2;
        q[i13].b[i16] = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 6);
        i1 += 2;
        q[i13].b[(i16 + 1)] = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 6);
        i1 += 2;
        q[i13].b[(i16 + 2)] = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 6);
      }
      i1 += 2;
      i18 = c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
      q[i13].l = new int[i18 * 2];
      for (i19 = 0; i19 < i18; i19++)
      {
        i1 += 2;
        q[i13].l[(i19 * 2)] = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 3);
        i1 += 2;
        q[i13].l[(i19 * 2 + 1)] = arrayOfInt[(c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 7)];
      }
      q[i13].c = (q[i13].f + q[i13].i >> 1);
      q[i13].d = (q[i13].g + q[i13].j >> 1);
      for (i20 = 0; i20 < i10; i20++)
      {
        i16 = i20 * 7;
        i1 += 2;
        q[i13].b[(i16 + 3)] = ((short)c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2);
        i1 += 2;
        q[i13].b[(i16 + 4)] = ((short)c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2);
        i1 += 2;
        q[i13].b[(i16 + 5)] = ((short)c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2);
      }
      i1++;
      for (i23 = 0; i23 < i10; i23++)
      {
        i1++;
        if ((i21 = arrayOfByte[i1]) < 0) {
          i21 += 256;
        }
        q[i13].b[(i23 * 7 + 6)] = i21;
        bv[q[i13].b[(i23 * 7 + 6)]] = true;
      }
      for (i24 = 0; i24 < i10; i24++)
      {
        i1++;
        if ((i22 = c(arrayOfByte[i1], arrayOfByte[(i1 + 1)])) < 0) {
          i22 += 256;
        }
        i21 = q[i13].b[(i24 * 7 + 6)] & 0xFF;
        q[i13].b[(i24 * 7 + 6)] = ((i22 << 8) + i21);
      }
      i1--;
    }
    i1 += 2;
    int i12;
    o = new c[i12 = c(arrayOfByte[i1], arrayOfByte[(i1 + 1)])];
    for (int i14 = 0; i14 < i12; i14++)
    {
      o[i14] = new c(null);
      o[i14].b[0] = new l(null);
      o[i14].b[1] = new l(null);
      o[i14].b[2] = new l(null);
      o[i14].b[3] = new l(null);
    }
    for (int i15 = 0; i15 < i12; i15++)
    {
      for (i16 = 0; i16 < 4; i16++)
      {
        i1 += 2;
        o[i15].b[i16].j = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
        i1 += 2;
        o[i15].b[i16].k = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
        i1 += 2;
        o[i15].b[i16].l = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
      }
      i1 += 2;
      i2 = (int)(65536 * c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 10000L);
      i1 += 2;
      int i3 = (int)(65536 * c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 10000L);
      i1 += 2;
      int i4 = (int)(65536 * c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 10000L);
      i1 += 2;
      o[i15].c = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) - 1);
      i1 += 2;
      o[i15].d = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) - 1);
      if ((o[i15].c == 999) || (o[i15].d == 999)) {
        this.cW = true;
      }
      if (i2 != 0) {
        o[i15].a = 1;
      } else if (i3 != 0) {
        o[i15].a = 2;
      } else if (i4 != 0) {
        o[i15].a = 3;
      }
    }
    for (int i16 = 0; i16 < i12; i16++)
    {
      if (o[i16].c < 999)
      {
        q[o[i16].c].o[q[o[i16].c].p] = i16;
        q[o[i16].c].p += 1;
      }
      if (o[i16].d < 999)
      {
        q[o[i16].d].o[q[o[i16].d].p] = i16;
        q[o[i16].d].p += 1;
      }
    }
    i1 += 2;
    bU = c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
    l = new j[bU];
    for (int i17 = 0; i17 < bU; i17++) {
      l[i17] = new j(null);
    }
    int i19 = 0;
    for (int i20 = 0; i20 < cx; i20++)
    {
      i1 += 2;
      i18 = c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
      q[i20].q = i19;
      q[i20].e = (i19 + i18);
      for (i21 = 0; i21 < i18; i21++)
      {
        l[i19].r = ((short)i20);
        i1 += 2;
        l[i19].m = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
        i1 += 2;
        l[i19].n = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
        i1 += 2;
        l[i19].o = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
        i1 += 2;
        l[i19].p = c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
        i1 += 2;
        l[i19].q = c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
        if (l[i19].q > 360) {
          l[i19].q = (65536 - l[i19].q);
        }
        if (l[i19].p > 360) {
          l[i19].p = (65536 - l[i19].p);
        }
        if (l[i19].q < 0) {
          l[i19].q = (-l[i19].q);
        }
        if (l[i19].q == 360) {
          l[i19].q = 0;
        }
        if (l[i19].p < 0) {
          l[i19].p = (360 + l[i19].p);
        } else {
          l[i19].p = (360 - l[i19].p);
        }
        if (l[i19].p == 360) {
          l[i19].p = 0;
        }
        i1 += 2;
        l[i19].t = ((byte)c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
        if (l[i19].t < 120)
        {
          if ((l[i19].t > 39) && (l[i19].t < 44)) {
            bX[i20] = 1;
          }
          if (l[i19].t >= 90)
          {
            j tmp2767_2766 = l[i19];
            tmp2767_2766.t = ((byte)(tmp2767_2766.t - 50));
            bX[i20] = -1;
          }
          bu[l[i19].t] = true;
        }
        i1 += 2;
        l[i19].e = ((short)c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
        if (l[i19].e < 0)
        {
          j tmp2841_2840 = l[i19];
          tmp2841_2840.e = ((short)(tmp2841_2840.e + 256));
        }
        i1 += 2;
        i19++;
      }
    }
    i1 += 2;
    dv = c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) + 1;
    X = new byte[dv];
    s = new m[dv];
    for (int i21 = 0; i21 < dv; i21++) {
      s[i21] = new m(null);
    }
    i19 = 1;
    if ((bM == 5) && (f.a[3] != 0))
    {
      cF[1] = 0;
      cF[2] = 51511296;
      if (f.a[3] == 1)
      {
        cE = 90;
        cF[0] = 380108800;
      }
      else
      {
        cE = 270;
        cF[0] = -380108800;
      }
    }
    s[0].n = cF[0];
    s[0].o = cF[1];
    s[0].p = cF[2];
    for (int i25 = 0; i25 < cx; i25++)
    {
      i1 += 2;
      i22 = c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
      for (i26 = 0; i26 < i22; i26++)
      {
        i1 += 2;
        s[i19].n = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
        s[i19].v = s[i19].n;
        i1 += 2;
        s[i19].o = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
        s[i19].w = s[i19].o;
        i1 += 2;
        s[i19].p = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
        i1 += 2;
        s[i19].y = ((byte)c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
        if ((i23 = s[i19].y) > 20)
        {
          i23 -= 20;
          s[i19].u = true;
          s[i19].A = false;
        }
        else if (i23 > 10)
        {
          i23 -= 10;
          s[i19].u = true;
        }
        s[i19].y = ((byte)i23);
        if (i23 != 7) {
          bw[i23] = true;
        }
        i1 += 2;
        if ((i24 = c(arrayOfByte[i1], arrayOfByte[(i1 + 1)])) > 360) {
          i24 -= 65536;
        }
        if (i24 < 0) {
          i24 = -i24;
        } else {
          i24 = 360 - i24;
        }
        if (i24 == 360) {
          i24 = 0;
        }
        s[i19].s[0] = (-cU[i24]);
        s[i19].s[1] = (-aq[i24]);
        s[i19].z[0] = (-cU[i24]);
        s[i19].z[1] = (-aq[i24]);
        if ((i23 == 4) || (i23 == 5)) {
          aT = (byte)(aT + 1);
        } else {
          dl = (byte)(dl + 1);
        }
        s[i19].r = ((short)i25);
        i19++;
      }
    }
    i1 += 2;
    int i23 = (byte)c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
    this.bo = i23;
    bp = new short[i23 * 3];
    for (int i26 = 0; i26 < i23; i26++)
    {
      i1 += 2;
      bp[(i26 * 3)] = ((short)c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
      i1 += 2;
      bp[(i26 * 3 + 1)] = ((short)c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
      i1 += 2;
      bp[(i26 * 3 + 2)] = ((short)c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
    }
    i1 += 2;
    i23 = c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
    ci = false;
    if (i23 == 1)
    {
      ci = true;
      n = new int[7];
      i1 += 2;
      n[0] = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
      i1 += 2;
      n[1] = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
      i1 += 2;
      n[2] = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
      i1 += 2;
      n[3] = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
      i1 += 2;
      n[4] = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
      i1 += 2;
      n[5] = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
      i1 += 2;
      n[6] = (c(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
    }
    for (int i27 = dv - 1; i27 >= 0; i27--)
    {
      g(s[i27]);
      if (i27 == 0)
      {
        cv = s[i27].r;
        b(s[i27].z);
      }
      if (s[i27].y == 4) {
        s[i27].l = 1250;
      }
    }
    s[0].r = ((short)cv);
    x();
    if (ck) {
      l(0);
    }
  }
  
  private final void O()
  {
    int i1 = 0;
    if (s != null) {
      i1 = s.length;
    }
    j(15);
    ba = new int[''];
    aR = new int[''];
    aZ = new int[45 + i1 + bU];
    aQ = new int[45 + i1 + bU];
    aC = new int['È'];
    aS = new l[10];
    aP = new l[10];
    for (int i2 = 0; i2 < 10; i2++)
    {
      aS[i2] = new l(null);
      aP[i2] = new l(null);
    }
    j(17);
    ap = new int['ʁ'];
    for (int i3 = 1; i3 < 641; i3++) {
      ap[i3] = (65536 / i3);
    }
    aA = new int[33600];
    for (int i4 = 1; i4 < 33600; i4++) {
      aA[i4] = (262144 / i4);
    }
    j(19);
  }
  
  private static void P()
  {
    if (cY[1] != 0) {
      bu[cY[1]] = true;
    }
    if (cY[2] != 0) {
      bu[cY[2]] = true;
    }
    k = new o[56];
    int i8;
    for (int i5 = 0; i5 < 56; i5++) {
      if (bu[i5] != 0)
      {
        int i1 = -2;
        byte[] arrayOfByte1 = f.g.a(f.a(N) + i5, -1);
        k[i5] = new o(null);
        i1 += 2;
        k[i5].c = (c(arrayOfByte1[0], arrayOfByte1[1]) << 16);
        i1 += 2;
        k[i5].d = (c(arrayOfByte1[2], arrayOfByte1[3]) << 16);
        i1 += 2;
        k[i5].e = (c(arrayOfByte1[4], arrayOfByte1[5]) << 16);
        i1 += 2;
        k[i5].f = (c(arrayOfByte1[6], arrayOfByte1[7]) << 16);
        i1 += 2;
        k[i5].g = (c(arrayOfByte1[8], arrayOfByte1[9]) << 16);
        i1 += 2;
        k[i5].h = (c(arrayOfByte1[10], arrayOfByte1[11]) << 16);
        i1 += 2;
        i1 += 2;
        i1 += 2;
        i1 += 2;
        i1 += 2;
        int i3 = c(arrayOfByte1[20], arrayOfByte1[21]);
        i1 += 2;
        int i2 = c(arrayOfByte1[22], arrayOfByte1[23]);
        i1 += 2;
        int i4 = c(arrayOfByte1[24], arrayOfByte1[25]);
        k[i5].i = i3;
        k[i5].a = new int[i3 * 6];
        k[i5].b = new int[i2 * 16];
        int[] arrayOfInt = new int[i4 *= 2];
        for (int i6 = 0; i6 < i3; i6++)
        {
          i1 += 2;
          k[i5].a[(i6 * 6)] = (c(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) << 16);
          i1 += 2;
          k[i5].a[(i6 * 6 + 1)] = (c(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) << 16);
          i1 += 2;
          k[i5].a[(i6 * 6 + 2)] = (c(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) << 16);
        }
        for (int i7 = 0; i7 < i2; i7++)
        {
          i1 += 2;
          k[i5].b[(i7 * 16)] = (c(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 6);
          i1 += 2;
          k[i5].b[(i7 * 16 + 1)] = (c(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 6);
          i1 += 2;
          k[i5].b[(i7 * 16 + 2)] = (c(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 6);
        }
        for (i8 = 0; i8 < i2; i8++)
        {
          i1 += 2;
          k[i5].b[(i8 * 16 + 10)] = ((int)(65536 * c(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) / 10000L));
          i1 += 2;
          k[i5].b[(i8 * 16 + 11)] = ((int)(65536 * c(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) / 10000L));
          i1 += 2;
          k[i5].b[(i8 * 16 + 12)] = ((int)(65536 * c(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) / 10000L));
        }
        for (int i9 = 0; i9 < i4; i9 += 2)
        {
          i1 += 2;
          arrayOfInt[i9] = ((int)(64 * c(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) / 100L));
          i1 += 2;
          arrayOfInt[(i9 + 1)] = ((int)(64 * c(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) / 100L));
        }
        for (i10 = 0; i10 < i2; i10++)
        {
          i1 += 2;
          k[i5].b[(i10 * 16 + 3)] = ((short)arrayOfInt[(c(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 2)]);
          k[i5].b[(i10 * 16 + 4)] = ((short)arrayOfInt[(c(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 2 + 1)]);
          i1 += 2;
          k[i5].b[(i10 * 16 + 5)] = ((short)arrayOfInt[(c(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 2)]);
          k[i5].b[(i10 * 16 + 6)] = ((short)arrayOfInt[(c(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 2 + 1)]);
          i1 += 2;
          k[i5].b[(i10 * 16 + 7)] = ((short)arrayOfInt[(c(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 2)]);
          k[i5].b[(i10 * 16 + 8)] = ((short)arrayOfInt[(c(arrayOfByte1[i1], arrayOfByte1[(i1 + 1)]) * 2 + 1)]);
        }
        i1 += 2;
        for (int i11 = 0; i11 < i2; i11++)
        {
          k[i5].b[(i11 * 16 + 9)] = arrayOfByte1[i1];
          bv[k[i5].b[(i11 * 16 + 9)]] = true;
          i1++;
        }
      }
    }
    byte[] arrayOfByte2 = f.g.a(f.a(B), -1);
    for (int i10 = 0; i10 < l.length; i10++)
    {
      j localj;
      if ((localj = l[i10]).t < 120)
      {
        i8 = localj.t << 2;
        if (arrayOfByte2[i8] == 1) {
          localj.d = true;
        }
        if (arrayOfByte2[(i8 + 1)] == 1) {
          localj.s = true;
        }
        if (arrayOfByte2[(i8 + 2)] == 1) {
          localj.c = true;
        }
        if (arrayOfByte2[(i8 + 3)] == 1) {
          localj.l = true;
        }
        o localo = k[localj.t];
        localj.a = localo.a;
        localj.b = localo.b;
        localj.f = localo.c;
        localj.i = localo.f;
        localj.g = localo.d;
        localj.j = localo.g;
        localj.h = localo.e;
        localj.k = localo.h;
        if (localj.t == 50)
        {
          localj.f = 1300;
          localj.g = 4000;
        }
      }
    }
  }
  
  private final void Q()
  {
    cC = 270;
    cE = 0;
    cF[0] = 0;
    cF[1] = 0;
    cF[2] = 0;
    bu = new boolean[56];
    bv = new boolean[72];
    bu[0] = true;
    l = new j[1];
    l[0] = new j(null);
    l[0].t = 0;
    l[0].m = 0;
    l[0].n = -262144000;
    O();
    P();
    bu = null;
    bv = null;
  }
  
  final void a(boolean paramBoolean)
  {
    f.e = true;
    f.a();
    int i1;
    int i2;
    if (paramBoolean)
    {
      if (bM == 0) {
        bM = 1;
      }
      i1 = (bM - 1) * 22 + 11;
      cY[1] = f.a[i1];
      cY[2] = f.a[(i1 + 1)];
      cY[3] = f.a[(i1 + 2)];
      for (i2 = 0; i2 < 7; i2++) {
        T[0][i2] = f.a[(i1 + 3 + i2)];
      }
      for (i2 = 0; i2 < 7; i2++) {
        T[1][i2] = f.a[(i1 + 10 + i2)];
      }
      cZ = f.a[(i1 + 18)];
      dF = f.a[(i1 + 19)];
      return;
    }
    if (aI)
    {
      this.bL = 2;
      cQ = 0;
      dx = true;
      aI = false;
      f.a[0] = 1;
      f.a[1] = 1;
      f.a[2] = 1;
      f.a[8] = 0;
      f.a[10] = 0;
      for (i2 = 0; i2 < 2; i2++)
      {
        i1 = 11 + i2 * 22;
        f.a[i1] = 3;
        f.a[(i1 + 1)] = 0;
        f.a[(i1 + 2)] = 6;
        f.a[(i1 + 3)] = -1;
        f.a[(i1 + 4)] = 7;
        f.a[(i1 + 5)] = 0;
        f.a[(i1 + 6)] = 30;
        f.a[(i1 + 7)] = 0;
        f.a[(i1 + 8)] = 0;
        f.a[(i1 + 9)] = 3;
        f.a[(i1 + 10)] = -1;
        f.a[(i1 + 11)] = 28;
        f.a[(i1 + 12)] = 0;
        f.a[(i1 + 13)] = 60;
        f.a[(i1 + 14)] = 0;
        f.a[(i1 + 15)] = 0;
        f.a[(i1 + 16)] = 0;
        f.a[(i1 + 17)] = 100;
        f.a[(i1 + 18)] = 1;
        f.a[(i1 + 19)] = 3;
      }
      for (int i3 = 2; i3 < 10; i3++)
      {
        i1 = 11 + i3 * 22;
        f.a[i1] = 0;
        f.a[(i1 + 1)] = 0;
        f.a[(i1 + 2)] = 0;
        f.a[(i1 + 3)] = -1;
        f.a[(i1 + 4)] = 0;
        f.a[(i1 + 5)] = 0;
        f.a[(i1 + 6)] = 0;
        f.a[(i1 + 7)] = 0;
        f.a[(i1 + 8)] = 0;
        f.a[(i1 + 9)] = 0;
        f.a[(i1 + 10)] = -1;
        f.a[(i1 + 11)] = 0;
        f.a[(i1 + 12)] = 0;
        f.a[(i1 + 13)] = 0;
        f.a[(i1 + 14)] = 0;
        f.a[(i1 + 15)] = 0;
        f.a[(i1 + 16)] = 0;
        f.a[(i1 + 17)] = 100;
      }
      c(false);
      return;
    }
    if (f.a[0] == 1) {
      dx = true;
    } else {
      dx = false;
    }
    this.bf = f.a[2];
    ay = f.a[5];
    cQ = f.a[6];
  }
  
  private static void R()
  {
    String str = new String();
    str = str + 's';
    str = str + bM;
    byte[] arrayOfByte = f.g.a(str, -1);
    int i1 = 0;
    for (int i2 = 0; i2 < arrayOfByte.length; i2++) {
      if (arrayOfByte[i2] == 13) {
        i1 = (short)(i1 + 1);
      }
    }
    cO = new short[i1][];
    int i3 = 0;
    int i7 = 0;
    int i8 = 1;
    for (int i12 = 0; i12 < i1; i12++)
    {
      int i6 = 1;
      for (int i13 = i3; i13 < arrayOfByte.length; i13++)
      {
        if (arrayOfByte[i13] == 13) {
          break;
        }
        if (arrayOfByte[i13] == 44) {
          i6++;
        }
      }
      cO[i12] = new short[i6 + 1];
      cO[i12][0] = ((short)arrayOfByte[i3]);
      i3 += 2;
      i7 = 0;
      int i11 = 0;
      i6 = 1;
      for (;;)
      {
        if ((arrayOfByte[i3] == 44) || (arrayOfByte[i3] == 13))
        {
          int i9 = 1;
          int i10 = Math.abs(i7 - i11);
          int i4 = 0;
          do
          {
            i9 *= 10;
            i10--;
          } while (i10 > 0);
          int i5 = i3 - i7;
          for (int i14 = 0; i14 < i7; i14++)
          {
            if (arrayOfByte[(i5 + i14)] == 45)
            {
              i14++;
              i8 = -1;
            }
            if ((arrayOfByte[(i5 + i14)] < 48) || (arrayOfByte[(i5 + i14)] > 57))
            {
              i5++;
              i14--;
            }
            else
            {
              i4 += (arrayOfByte[(i5 + i14)] - 48) * i9;
              i9 /= 10;
            }
          }
          cO[i12][i6] = ((short)(i4 * i8));
          i8 = 1;
          i6++;
          i7 = -1;
          i11 = -1;
          if (arrayOfByte[i3] == 13)
          {
            i3 += 2;
            break;
          }
        }
        if ((arrayOfByte[i3] < 48) || (arrayOfByte[i3] > 57)) {
          i11++;
        }
        if (i11 == -1) {
          i11 = 0;
        }
        i7 = (byte)(i7 + 1);
        i3++;
      }
    }
  }
  
  private final void S()
  {
    dq = null;
    this.cW = true;
    if ((bM == 2) || (bM == 10))
    {
      byte[] arrayOfByte;
      if ((arrayOfByte = f.g.a(f.a(w), -1)) != null)
      {
        try
        {
          cd = b(arrayOfByte);
          dq = a(arrayOfByte, false, 0, 0, 0, 0);
          this.cX = a(arrayOfByte, true);
          if (this.cX == 0) {
            this.cX = 256;
          }
          this.cV = a(arrayOfByte, false);
          if (this.cV == 0) {
            this.cV = 256;
          }
        }
        catch (Exception localException)
        {
          this.bL = 0;
          this.cW = false;
          return;
        }
      }
      else
      {
        this.bL = 0;
        this.cW = false;
        return;
      }
      return;
    }
    this.cW = false;
  }
  
  private final void T()
  {
    this.S = 0;
    do = new byte[72][];
    ca = new int[72][];
    S();
    j(55);
    for (int i1 = 0; i1 < 72; i1++) {
      if (bv[i1] != 0)
      {
        this.S = ((byte)(this.S + 1));
        try
        {
          arrayOfByte1 = f.g.a(f.a(v) + i1, -1);
          ca[i1] = b(arrayOfByte1);
          do[i1] = a(arrayOfByte1, false, 0, 0, 0, 0);
          a(do[i1]);
        }
        catch (Exception localException) {}
      }
    }
    j(60);
    cb = new int[''];
    dp = new byte[91][];
    byte[] arrayOfByte1 = f.g.a(f.a(x) + 0, -1);
    int i2 = M();
    cc = b(arrayOfByte1);
    j(65);
    for (int i3 = 1; i3 < i2; i3++) {
      dp[i3] = a(arrayOfByte1, true, ar[i3][0], ar[i3][1], ar[i3][2], ar[i3][3]);
    }
    j(70);
    dr = new byte[91][];
    N();
    ce = new int[7][];
    j(75);
    aM = new byte['Ŋ'];
    int i5 = 0;
    int i7 = 0;
    for (int i8 = 1; i8 < 7; i8++) {
      if (bw[i8] != 0)
      {
        int[] arrayOfInt = b(arrayOfByte1 = f.g.a(f.a(x) + i8, -1));
        int i4 = 0;
        for (int i6 = 0; i6 < 128; i6++)
        {
          if (arrayOfInt[i6] == 0) {
            i4++;
          }
          if (i4 == 2) {
            break;
          }
        }
        i4 = i6;
        ce[i8] = new int[i4];
        for (i6 = 0; i6 < i4; i6++) {
          ce[i8][i6] = arrayOfInt[i6];
        }
        i7 = bJ[(i8 - 1 << 1)];
        for (i6 = 0; i6 < bJ[((i8 - 1 << 1) + 1)]; i6++)
        {
          i5 = ab[i7][2];
          if (ab[i7][3] != 0)
          {
            byte[] arrayOfByte2 = a(arrayOfByte1, true, at[i5][0], at[i5][1], at[i5][2], at[i5][3]);
            byte b1 = (byte)at[i5][2];
            byte b2 = (byte)at[i5][3];
            byte b3 = ab[i7][0];
            byte b4 = ab[i7][1];
            i5 = ab[i7][5];
            byte[] arrayOfByte3 = a(arrayOfByte1, true, at[i5][0], at[i5][1], at[i5][2], at[i5][3]);
            dr[i7] = a(i7, arrayOfByte2, b1, b2, b3, b4, arrayOfByte3, (byte)at[i5][2], (byte)at[i5][3], ab[i7][3], ab[i7][4]);
          }
          else
          {
            dr[i7] = a(arrayOfByte1, true, at[i5][0], at[i5][1], at[i5][2], at[i5][3]);
            aM[(i7 * 5)] = ((byte)at[i5][2]);
            aM[(i7 * 5 + 1)] = ((byte)at[i5][3]);
            aM[(i7 * 5 + 4)] = ((byte)(ab[i7][1] - at[i5][3]));
            if (((i7 < 11) && (i7 > 6)) || ((i7 < 25) && (i7 > 20)) || (i7 == 30) || ((i7 < 39) && (i7 > 34)) || ((i7 < 53) && (i7 > 48)))
            {
              aM[(i7 * 5 + 2)] = ((byte)(int)(at[i5][2] * 115998L >> 16));
              aM[(i7 * 5 + 3)] = ((byte)(int)(at[i5][3] * 115998L >> 16));
            }
            else
            {
              aM[(i7 * 5 + 2)] = ((byte)at[i5][2]);
              aM[(i7 * 5 + 3)] = ((byte)at[i5][3]);
            }
          }
          i7++;
        }
      }
    }
    j(80);
    j(85);
    j(87);
  }
  
  private void U()
  {
    ds = new byte[9][];
    cf = new int[9][];
    av = new byte[18];
    for (int i3 = 0; i3 < 9; i3++)
    {
      byte[] arrayOfByte = f.g.a(f.a(t) + i3, -1);
      av[(i3 << 1)] = ((byte)a(arrayOfByte, true));
      av[((i3 << 1) + 1)] = ((byte)a(arrayOfByte, false));
      ds[i3] = a(arrayOfByte, false, 0, 0, 0, 0);
      int[] arrayOfInt = b(arrayOfByte);
      int i1 = 0;
      for (int i2 = 0; i2 < 128; i2++)
      {
        if (arrayOfInt[i2] == 0) {
          i1++;
        }
        if (i1 == 2) {
          break;
        }
      }
      i1 = i2;
      cf[i3] = new int[i1];
      for (i2 = 0; i2 < i1; i2++) {
        cf[i3][i2] = arrayOfInt[i2];
      }
    }
  }
  
  public final void b(boolean paramBoolean)
  {
    g = 0;
    c(g);
    this.br = true;
    a(true);
    if (paramBoolean)
    {
      Object localObject1 = null;
      long l3 = 0L;
      Object localObject2 = null;
      l3 = h._n();
      long l1 = l3;
      if (bM == 7) {
        I();
      }
      this.bt = null;
      try
      {
        try
        {
          this.aV = f.a(f.a(O));
        }
        catch (OutOfMemoryError localOutOfMemoryError1) {}
        try
        {
          this.bP = f.a(f.a(P));
        }
        catch (Exception localException2) {}
      }
      catch (Exception localException1) {}
      if (this.bP == null)
      {
        this.an = (!this.an);
        return;
      }
      this.bP.getHeight();
      j(0);
      ad();
      try
      {
        this.bY = f.a(f.a(D));
      }
      catch (Exception localException3) {}
      cv = 0;
      l = null;
      k = null;
      az = null;
      j(5);
      ap = null;
      aA = null;
      j(9);
      bv = new boolean[72];
      j(3);
      bu = new boolean[56];
      j(6);
      bw = new boolean[7];
      j(8);
      dw = new int[3];
      j(10);
      az = new int[72480];
      j(12);
      U();
      R();
      j(15);
      h(bM);
      j(20);
      P();
      j(30);
      bS = (short)s.length;
      df = (short)(bS + bU);
      cS = (short)(df + 25);
      O();
      j(40);
      K();
      L();
      J();
      j(50);
      T();
      j(90);
      bv = null;
      bu = null;
      bw = null;
      j(100);
      this.bs = 0;
      q();
      s[0].l = ((short)f.a[((bM - 1) * 22 + 11 + 17)]);
      if ((!aW) && (!this.bO))
      {
        n.s = 10;
        this.bD = 11;
        n.f = 16;
        aW = true;
      }
      localObject1 = null;
      l3 = 0L;
      localObject2 = null;
      l3 = h._n();
      long l2 = l3;
      try
      {
        if (l2 - l1 < 2500L) {
          Thread.sleep(2500L - (l2 - l1));
        }
      }
      catch (Exception localException4) {}
      if (al)
      {
        cY[1] = 4;
        T[0][4] = 1;
        cY[2] = 5;
        T[0][5] = 1;
      }
    }
    else
    {
      this.bs = 0;
      try
      {
        this.aV = f.a(f.a(O));
      }
      catch (Exception localException5) {}
      try
      {
        this.bP = f.a(f.a(P));
      }
      catch (Exception localException6) {}
      if (this.bP == null)
      {
        this.an = (!this.an);
        return;
      }
      this.bP.getHeight();
      j(0);
      try
      {
        this.bY = f.a(f.a(D));
      }
      catch (Exception localException7) {}
      az = null;
      j(7);
      this.aN = null;
      this.ad = null;
      ap = null;
      j(14);
      aA = null;
      j(21);
      aS = null;
      j(28);
      aP = null;
      j(35);
      q = null;
      j(42);
      o = null;
      j(49);
      s = null;
      j(63);
      l = null;
      j(70);
      k = null;
      this.a = null;
      this.b = null;
      this.Z = null;
      ba = null;
      j = null;
      aM = null;
      ds = null;
      cf = null;
      j(77);
      av = null;
      dm = null;
      aR = null;
      j(80);
      aZ = null;
      aQ = null;
      cR = null;
      X = null;
      aC = null;
      ca = null;
      cb = null;
      bX = null;
      do = null;
      dq = null;
      cd = null;
      j(85);
      cc = null;
      dp = null;
      ce = null;
      cO = null;
      dr = null;
      j(92);
      at = null;
      ar = null;
      aa = null;
      ac = null;
      ab = null;
      j(91);
      az = new int[76800];
      Q();
      bp = null;
      j(100);
      this.bY = null;
      this.bP = null;
      if (!this.bO)
      {
        this.m = true;
        bA = true;
        n.s = 10;
        if (di)
        {
          this.bD = 5;
          di = false;
        }
        else
        {
          this.bD = 1;
        }
        n.f = 16;
        aW = false;
        d();
      }
      try
      {
        try
        {
          this.bt = f.a(f.a(O));
        }
        catch (OutOfMemoryError localOutOfMemoryError2) {}
        this.br = false;
      }
      catch (Exception localException8) {}
    }
    this.bs = 0;
    System.gc();
    bq = true;
  }
  
  public final void c()
  {
    try
    {
      NET_Lizard.a.platformRequest(this.r);
      this.an = false;
      return;
    }
    catch (Exception localException)
    {
      this.bD = 6;
    }
  }
  
  private static final void V()
  {
    if (db)
    {
      as = (byte)(as + 1);
      if (as >= bB.length) {
        as = 0;
      }
      return;
    }
    if (g == 0)
    {
      s[0].b[0] = cU[cE];
      s[0].b[1] = aq[cE];
      dy = true;
      return;
    }
    if (cA < 30) {
      cA += 1;
    }
  }
  
  private static final void W()
  {
    s[0].b[0] = aq[cE];
    s[0].b[1] = (-cU[cE]);
  }
  
  private static final void X()
  {
    s[0].b[0] = (-aq[cE]);
    s[0].b[1] = cU[cE];
  }
  
  private static final void Y()
  {
    if (db)
    {
      if (f <= 0)
      {
        f = 13;
      }
      else if (f == 10)
      {
        f = 10;
      }
      else
      {
        f = (byte)(f - 1);
        return;
      }
      as = (byte)(as - 1);
      if (as < 0) {
        as = 4;
      }
      return;
    }
    if (g == 0)
    {
      s[0].b[0] = (-cU[cE]);
      s[0].b[1] = (-aq[cE]);
      dy = true;
      return;
    }
    if (cA > -30) {
      cA -= 1;
    }
  }
  
  public static void d()
  {
    a(bk, true);
  }
  
  static final void a(int paramInt1, int paramInt2, int paramInt3, int paramInt4, int paramInt5, int paramInt6, int paramInt7, int paramInt8, int paramInt9)
  {
    int i1 = paramInt5 & 0xFF0000;
    int i2 = paramInt5 & 0xFF00;
    int i3 = paramInt5 & 0xFF;
    int[] arrayOfInt = az;
    paramInt2 = paramInt2 * 240 + paramInt1;
    int i6 = 0;
    int i7 = paramInt4;
    do
    {
      int i5 = paramInt3;
      do
      {
        if ((i5 + i6 >= paramInt8) && (paramInt3 - i5 + i6 >= paramInt7) && (paramInt3 - i5 + (i7 - i6) >= paramInt6) && (i5 + (i7 - i6) >= paramInt9))
        {
          int i4 = arrayOfInt[(paramInt2 + i5)];
          arrayOfInt[(paramInt2 + i5)] = (((i4 & 0xFF0000) + i1 >> 17 << 16) + ((i4 & 0xFF00) + i2 >> 9 << 8) + ((i4 & 0xFF) + i3 >> 1));
        }
        i5--;
      } while (i5 >= 0);
      paramInt2 += 240;
      i6++;
      paramInt4--;
    } while (paramInt4 >= 0);
  }
  
  private static void a(byte paramByte)
  {
    cj = true;
    e = paramByte;
    switch (paramByte)
    {
    case 3: 
      Z();
    }
  }
  
  private static void Z()
  {
    ab();
    e locale = aE;
    s[0].v = locale.a;
    s[0].w = locale.b;
  }
  
  private void i(int paramInt)
  {
    if (s[0].i) {
      return;
    }
    if (bM == 5)
    {
      switch (paramInt)
      {
      case 24: 
        if ((this.bf == 2) || (this.bf == 3)) {
          return;
        }
        break;
      case 13: 
        if ((this.bf == 1) || (this.bf == 3)) {
          return;
        }
        bM = 6;
        break;
      case 48: 
        if (this.bf != 3) {
          return;
        }
        bM = 7;
      }
    }
    else if (bM == 6)
    {
      if (this.bf < 2) {
        return;
      }
      bM = 4;
      f.a[3] = 1;
    }
    else if (bM == 7)
    {
      if ((this.bf != 1) && (this.bf != 3)) {
        return;
      }
      bM = 4;
      f.a[3] = 2;
    }
    if ((bM == 9) && (bm[bn] != n[2])) {
      return;
    }
    this.bO = true;
    bM = (byte)(bM + 1);
    f.a[10] = bM;
    if (f.a[8] < bM) {
      f.a[8] = bM;
    }
    c(true);
    b(false);
    b(true);
    this.bO = false;
    bA = false;
    this.m = false;
  }
  
  private static void aa()
  {
    g[] arrayOfg = q;
    j[] arrayOfj = l;
    byte[] arrayOfByte = bX;
    int i1 = arrayOfg.length;
    m localm = s[0];
    boolean bool = ci;
    int i6 = 0;
    for (int i7 = 0; i7 < i1; i7++)
    {
      if ((bool) && (bI >= 0) && (cw[bI] == i7))
      {
        i6 = 1;
        if (arrayOfByte[i7] < 0) {
          arrayOfByte[i7] = 1;
        }
      }
      else
      {
        i6 = 0;
      }
      if ((arrayOfByte[i7] > 0) || (i6 != 0))
      {
        int i2 = localm.n - arrayOfg[i7].c >> 16;
        int i3 = localm.o - arrayOfg[i7].d >> 16;
        int i4 = localm.p - (arrayOfg[i7].h + arrayOfg[i7].k >> 1) >> 16;
        int i5;
        if ((i2 * i2 + i3 * i3 + i4 * i4 < 250000) || (i6 != 0))
        {
          if (arrayOfByte[i7] == 1) {
            l(7);
          }
          for (i5 = arrayOfg[i7].q; i5 < arrayOfg[i7].e; i5++) {
            if (arrayOfj[i5].u) {
              if ((arrayOfj[i5].t == 40) || (arrayOfj[i5].t == 43))
              {
                if (arrayOfByte[i7] < 61) {
                  arrayOfj[i5].o += 1966080;
                }
              }
              else if (arrayOfByte[i7] < 61) {
                arrayOfj[i5].o -= 1966080;
              }
            }
          }
          if (arrayOfByte[i7] < 61)
          {
            int tmp324_322 = i7;
            byte[] tmp324_321 = arrayOfByte;
            tmp324_321[tmp324_322] = ((byte)(tmp324_321[tmp324_322] + 10));
          }
        }
        else
        {
          if (arrayOfByte[i7] == 61) {
            l(7);
          }
          for (i5 = arrayOfg[i7].q; i5 < arrayOfg[i7].e; i5++) {
            if (arrayOfj[i5].u) {
              if ((arrayOfj[i5].t == 40) || (arrayOfj[i5].t == 43))
              {
                if (arrayOfByte[i7] > 1) {
                  arrayOfj[i5].o -= 1966080;
                }
              }
              else if (arrayOfByte[i7] > 1) {
                arrayOfj[i5].o += 1966080;
              }
            }
          }
          if (arrayOfByte[i7] > 1)
          {
            int tmp472_470 = i7;
            byte[] tmp472_469 = arrayOfByte;
            tmp472_469[tmp472_470] = ((byte)(tmp472_469[tmp472_470] - 10));
          }
        }
      }
    }
  }
  
  public final void paint(Graphics paramGraphics)
  {
    if (h.a(paramGraphics)) {
      return;
    }
    try
    {
      if (Y >= 0)
      {
        if ((Y == 0) || (Y == 2) || (Y == 3) || (Y == 4)) {
          b(paramGraphics);
        }
        if (Y == 1) {
          c(paramGraphics);
        }
        return;
      }
      if (this.br)
      {
        if (!this.bO)
        {
          this.bz.a(paramGraphics);
          return;
        }
        d(paramGraphics);
        return;
      }
      if (bA)
      {
        this.bz.a(paramGraphics);
        return;
      }
      f(paramGraphics);
      a(paramGraphics);
      return;
    }
    catch (Exception localException) {}
  }
  
  private static final int a(int[] paramArrayOfInt1, int[] paramArrayOfInt2, int paramInt1, int paramInt2)
  {
    int i1 = paramInt1;
    for (int i2 = paramInt1; i2 <= paramInt2; i2++) {
      if (paramArrayOfInt1[i2] <= paramArrayOfInt1[paramInt2])
      {
        int i3 = paramArrayOfInt1[i1];
        paramArrayOfInt1[i1] = paramArrayOfInt1[i2];
        paramArrayOfInt1[i2] = i3;
        i3 = paramArrayOfInt2[i1];
        paramArrayOfInt2[i1] = paramArrayOfInt2[i2];
        paramArrayOfInt2[i2] = i3;
        i1++;
      }
    }
    return i1 - 1;
  }
  
  private final void h(m paramm)
  {
    int[] arrayOfInt1 = null;
    if (h._a1()) {
      return;
    }
    if (paramm.y == 7) {
      return;
    }
    arrayOfInt1 = paramm.b;
    int[] arrayOfInt2 = paramm.e;
    int[] arrayOfInt3 = dw;
    int i1 = 0;
    int[] arrayOfInt4 = ap;
    int i3 = (short)paramm.t;
    if (!paramm.c)
    {
      arrayOfInt2[0] += arrayOfInt1[0] * 40;
      arrayOfInt2[1] += arrayOfInt1[1] * 40;
      arrayOfInt2[2] += arrayOfInt1[2] * 40;
    }
    else
    {
      arrayOfInt2[2] -= 1048576;
      i3 = 2;
    }
    int i4 = arrayOfInt2[0] >> 16;
    int i5 = arrayOfInt2[1] >> 16;
    int i6 = arrayOfInt2[2] >> 16;
    int i2 = i4 * i4 + i5 * i5 + i6 * i6;
    i1 = 0;
    int i7 = 65536;
    while (i7 >>= 1 > 0) {
      if ((i1 + i7) * (i1 + i7) <= i2) {
        i1 += i7;
      }
    }
    arrayOfInt3[0] = ((int)(arrayOfInt2[0] * arrayOfInt4[i1] >> 16));
    arrayOfInt3[1] = ((int)(arrayOfInt2[1] * arrayOfInt4[i1] >> 16));
    arrayOfInt3[2] = ((int)(arrayOfInt2[2] * arrayOfInt4[i1] >> 16));
    if (paramm.y == 4) {
      i3 = 3;
    }
    if (by[i3] < i1)
    {
      i1 = by[i3];
      arrayOfInt3[0] *= i1;
      arrayOfInt3[1] *= i1;
      arrayOfInt3[2] *= i1;
    }
    else if ((!paramm.c) && (i1 > 0))
    {
      arrayOfInt2[0] += -arrayOfInt3[0] * 12;
      arrayOfInt2[1] += -arrayOfInt3[1] * 12;
      arrayOfInt2[2] += -arrayOfInt3[2] * 12;
    }
    if (i1 < 15)
    {
      arrayOfInt2[0] = 0;
      arrayOfInt2[1] = 0;
      arrayOfInt2[2] = 0;
    }
    paramm.n += arrayOfInt2[0];
    paramm.o += arrayOfInt2[1];
    paramm.p += arrayOfInt2[2];
    if (b(paramm, i1)) {
      paramm.c = false;
    } else {
      paramm.c = true;
    }
    g(paramm);
  }
  
  private final boolean b(m paramm1, m paramm2)
  {
    int i1 = paramm1.n - paramm2.n >> 16;
    int i2 = paramm1.o - paramm2.o >> 16;
    int i3 = paramm1.p - paramm2.p >> 16;
    if (i1 * paramm1.s[0] + i2 * paramm1.s[1] > 0L) {
      return false;
    }
    return i1 * i1 + i2 * i2 + i3 * i3 < this.bx[ay];
  }
  
  private static void ab()
  {
    b(s[0].z);
    m localm = s[0];
    e locale1 = dk;
    e locale2 = aE;
    locale1.a = cF[0];
    locale1.b = cF[1];
    locale1.c = cF[2];
    locale1.a += localm.z[0] * 7000;
    locale1.b += localm.z[1] * 7000;
    locale1.c += localm.z[2] * 7000;
    int i1 = localm.r;
    int i2 = -1;
    for (;;)
    {
      if (i1 == 999) {
        return;
      }
      if (a(i1, locale1, locale2, localm, false) != -1) {
        return;
      }
      if ((i2 = a(i1, locale1, locale2, i2)) == -1) {
        break;
      }
      if (o[i2].c == i1) {
        i1 = o[i2].d;
      } else {
        i1 = o[i2].c;
      }
    }
    if (a(i1, locale1, locale2) != -1) {}
  }
  
  private static final void a(l paraml)
  {
    paraml.d = ((short)(int)(7864320L + paraml.a * bW / paraml.c >> 16));
    paraml.e = ((short)(int)(9830400L - paraml.b * bW / paraml.c >> 16));
  }
  
  private final void ac()
  {
    if (cm >= 0) {
      switch (cm)
      {
      case 0: 
        if (cv == this.cg)
        {
          aD = true;
          cm = -1;
          return;
        }
        break;
      case 1: 
        if (s[this.cg].i)
        {
          aD = true;
          cm = -1;
          for (int i1 = 0; i1 < l.length; i1++) {
            if (l[i1].t >= 120)
            {
              l[i1].m = s[this.cg].n;
              l[i1].n = s[this.cg].o;
              l[i1].o = s[this.cg].p;
              l[i1].r = s[this.cg].r;
              break;
            }
          }
          return;
        }
        break;
      case 2: 
        this.cg = ((short)(this.cg - 1));
        if (this.cg <= 0)
        {
          aD = true;
          cm = -1;
          return;
        }
        break;
      case 3: 
        if (!l[this.cg].u)
        {
          aD = true;
          cm = -1;
        }
        break;
      }
    }
  }
  
  private static final void b(int[] paramArrayOfInt1, int[] paramArrayOfInt2, int paramInt1, int paramInt2)
  {
    if (paramInt1 >= paramInt2) {
      return;
    }
    int i1 = a(paramArrayOfInt1, paramArrayOfInt2, paramInt1, paramInt2);
    b(paramArrayOfInt1, paramArrayOfInt2, paramInt1, i1 - 1);
    b(paramArrayOfInt1, paramArrayOfInt2, i1 + 1, paramInt2);
  }
  
  public final void e()
  {
    Object localObject1 = null;
    long l3 = 0L;
    Object localObject2 = null;
    l3 = h._n();
    long l1 = l3;
    this.br = true;
    if (bM == 7) {
      switch (this.bf)
      {
      case 1: 
        this.bf = 0;
        break;
      case 3: 
        this.bf = 2;
      }
    }
    if (bM == 6) {
      switch (this.bf)
      {
      case 2: 
        this.bf = 0;
        break;
      case 3: 
        this.bf = 1;
      }
    }
    j(0);
    a(true);
    try
    {
      this.bY = f.a(f.a(D));
    }
    catch (Exception localException1) {}
    ad();
    if (bM == 7) {
      I();
    }
    q = null;
    j(10);
    o = null;
    j(20);
    s = null;
    j(40);
    k = null;
    j(50);
    l = null;
    j(60);
    dw = new int[3];
    dg = new int[25][6];
    bv = new boolean[72];
    bu = new boolean[56];
    bw = new boolean[7];
    j(65);
    h(bM);
    j(70);
    P();
    j(80);
    j(90);
    S();
    j(100);
    this.bY = null;
    bv = null;
    bu = null;
    bw = null;
    this.br = false;
    this.m = false;
    bA = false;
    localObject1 = null;
    l3 = 0L;
    localObject2 = null;
    l3 = h._n();
    long l2 = l3;
    try
    {
      if (l2 - l1 < 1500L) {
        Thread.sleep(1500L - (l2 - l1));
      }
    }
    catch (Exception localException2) {}
    s[0].l = ((short)f.a[((bM - 1) * 22 + 11 + 17)]);
    this.bs = 0;
    q();
    n.s = 10;
    this.bD = 11;
    n.f = 16;
    aW = true;
    this.cu = false;
  }
  
  private void ad()
  {
    cm = -1;
    bn = -1;
    bI = -1;
    this.W = 0;
    this.de = 0;
    this.aL = 32768;
    this.aO = 65536;
    af = false;
    aD = true;
    this.cP = 0;
    this.bb = 0;
    this.aX = 0;
    this.i = false;
    dN = -1;
    dM = 0;
    bT = -1;
    p = 1;
    g = 0;
    c(g);
    cA = 0;
    aF = 0;
    cr = 4;
    cp = 0;
    cq = 0;
    aT = 0;
    dl = 0;
    aw = 0;
    dG = 0;
    ae = 0;
    cz = 0;
    dh = 0;
    cT = 0;
    cR = new int[20][10];
    dg = new int[25][6];
    g = 0;
  }
  
  private final void a(Graphics paramGraphics, int paramInt1, int paramInt2, int paramInt3)
  {
    paramGraphics.setClip(paramInt2, paramInt3, this.ad[paramInt1][2], this.ad[paramInt1][3]);
    paramGraphics.drawImage(this.aN, paramInt2 - this.ad[paramInt1][0], paramInt3 - this.ad[paramInt1][1], 20);
    paramGraphics.setClip(0, 0, 240, 320);
  }
  
  private static void b(Graphics paramGraphics, int paramInt1, int paramInt2, int paramInt3)
  {
    paramInt2 += ac[paramInt1][4];
    paramInt3 += ac[paramInt1][5];
    paramGraphics.setClip(paramInt2, paramInt3, ac[paramInt1][2], ac[paramInt1][3]);
    paramGraphics.drawImage(aa, paramInt2 - ac[paramInt1][0], paramInt3 - ac[paramInt1][1], 20);
    paramGraphics.setClip(0, 0, 240, 320);
  }
  
  private static final void c(j paramj)
  {
    int[] arrayOfInt1 = paramj.a;
    int[] arrayOfInt2 = paramj.b;
    int i1 = cF[0];
    int i2 = cF[1];
    int i3 = cF[2];
    int i4 = cE;
    int i5 = cC;
    int i6 = 0;
    int i7 = 0;
    int i10 = aq[paramj.q];
    int i11 = cU[paramj.q];
    int i12 = aq[paramj.p];
    int i13 = cU[paramj.p];
    int i14 = ((i8 = k[paramj.t].i) - 1) * 6;
    int i9;
    do
    {
      arrayOfInt1[(i14 + 3)] = ((int)(arrayOfInt1[i14] * i10 - arrayOfInt1[(i14 + 1)] * i11 >> 16));
      i9 = (int)(arrayOfInt1[i14] * i11 + arrayOfInt1[(i14 + 1)] * i10 >> 16);
      arrayOfInt1[(i14 + 5)] = ((int)(arrayOfInt1[(i14 + 2)] * i12 - i9 * i13 >> 16));
      i9 = (int)(arrayOfInt1[(i14 + 2)] * i13 + i9 * i12 >> 16);
      i6 = i3 - (arrayOfInt1[(i14 + 5)] + paramj.o);
      i7 = i1 - (arrayOfInt1[(i14 + 3)] + paramj.m);
      arrayOfInt1[(i14 + 3)] = ((int)(i7 * aq[i4] - (i2 - (i9 + paramj.n)) * cU[i4] >> 16));
      i9 = (int)(i7 * cU[i4] + (i2 - (i9 + paramj.n)) * aq[i4] >> 16);
      arrayOfInt1[(i14 + 5)] = ((int)(i6 * aq[i5] - i9 * cU[i5] >> 16));
      arrayOfInt1[(i14 + 4)] = ((int)(i6 * cU[i5] + i9 * aq[i5] >> 16));
      i14 -= 6;
      i8--;
    } while (i8 >= 0);
    int i8 = arrayOfInt2.length >> 4;
    do
    {
      i14 = i8 << 4;
      i6 = arrayOfInt2[(i14 + 10)];
      i7 = arrayOfInt2[(i14 + 11)];
      arrayOfInt2[(i14 + 13)] = ((int)(i6 * i10 - i7 * i11 >> 16));
      i9 = (int)(i6 * i11 + i7 * i10 >> 16);
      arrayOfInt2[(i14 + 15)] = ((int)(arrayOfInt2[(i14 + 12)] * i12 - i9 * i13 >> 16));
      arrayOfInt2[(i14 + 14)] = ((int)(arrayOfInt2[(i14 + 12)] * i13 + i9 * i12 >> 16));
      i8--;
    } while (i8 >= 0);
  }
  
  public final synchronized void run()
  {
    h.a(this, this.aJ);
    if (this.r == null) {
      try
      {
        this.r = NET_Lizard.a.getAppProperty(f.a(c));
      }
      catch (Exception localException1) {}
    }
    if (this.r == null) {
      try
      {
        this.r = NET_Lizard.a.getAppProperty(f.a(d));
      }
      catch (Exception localException2) {}
    }
    if (!ai()) {
      ax = true;
    }
    H();
    int i1 = 0;
    int i2 = 0;
    int i3 = 0;
    long l1 = 0L;
    while (this.an)
    {
      if (ax) {
        if (h.a((!aW) || (this.br)))
        {
          this.bC = -1;
          bq = false;
          aW = false;
          b(false);
        }
      }
      if (h.e())
      {
        repaint();
        serviceRepaints();
        try
        {
          Thread.sleep(7L);
        }
        catch (Exception localException3) {}
      }
      else
      {
        try
        {
          Thread.sleep(3L);
        }
        catch (Exception localException4) {}
        aG = false;
        aH = false;
        if (this.bK != 0) {
          C();
        }
        if (this.be != 0)
        {
          if ((this.bc) || (this.bd))
          {
            E();
            this.bc = false;
          }
        }
        else {
          f = 0;
        }
        if (!h.d())
        {
          i2 = 0;
          if ((bA) && (h.D > 10L) && ((this.bD == 1) || (this.bD == 13))) {
            i2 = 1;
          }
          Object localObject1;
          long l6;
          Object localObject2;
          if (i2 != i3)
          {
            if (i2 != 0)
            {
              localObject1 = null;
              l6 = 0L;
              localObject2 = null;
              l6 = h._n();
              l1 = l6 - h.D;
            }
            else
            {
              localObject1 = null;
              l6 = 0L;
              localObject2 = null;
              l6 = h._n();
              h.D = l6 - l1;
            }
            i3 = i2;
          }
          if (i2 != 0) {
            h.D = 0L;
          }
          if (this.bC != this.bD) {
            u();
          }
          if (h.ah != null)
          {
            localObject1 = null;
            l6 = 0L;
            localObject2 = null;
            l6 = h._n();
            long l2 = l6;
            repaint();
            serviceRepaints();
            localObject1 = null;
            l6 = 0L;
            localObject2 = null;
            l6 = h._n();
            long l3;
            long l4 = (l3 = l6) - l2;
            long l5 = 88L;
            if (l4 < l5) {
              try
              {
                Thread.sleep(l5 - l4);
              }
              catch (Exception localException5) {}
            }
          }
          else
          {
            m();
          }
        }
      }
    }
    c(false);
    ag();
    NET_Lizard.a();
  }
  
  private final void ae()
  {
    if (this.cI >= 0)
    {
      String[] arrayOfString = this.da[this.cI];
      this.cL = ((short)(this.cL + 2));
      if (arrayOfString.length <= this.cN)
      {
        this.cL = 0;
      }
      else if (this.cL > arrayOfString[this.cN].length())
      {
        this.cL = 0;
        this.cN = ((byte)(this.cN + 1));
        if (this.cJ < this.cN) {
          this.cK = ((byte)(this.cK + 1));
        }
      }
    }
    if (this.W < 4) {
      this.W = ((byte)(this.W + 1));
    }
    int i1 = cO.length;
    if (this.bb < 0)
    {
      this.bb = 0;
      this.cP = ((short)(this.cP + (cO[this.cP][2] + 1)));
      this.i = false;
    }
    if (!this.i)
    {
      while (this.cP < i1)
      {
        a((byte)cO[this.cP][0], cO[this.cP]);
        if (this.i) {
          break;
        }
        if (cm >= 0)
        {
          this.cP = ((short)(this.cP + 1));
          break;
        }
        this.cP = ((short)(this.cP + 1));
      }
    }
    else
    {
      for (int i2 = this.cP + 1; i2 <= this.aX; i2++) {
        a((byte)cO[i2][0], cO[i2]);
      }
      this.bb = ((short)(this.bb - 1));
    }
    if (this.cP >= i1 - 1) {
      aD = false;
    }
  }
  
  private void j(int paramInt)
  {
    if (bq)
    {
      this.bs = ((byte)paramInt);
      repaint();
      serviceRepaints();
    }
  }
  
  final void c(boolean paramBoolean)
  {
    Object localObject = null;
    if (h._a0()) {
      return;
    }
    if (bM == 3) {
      return;
    }
    f.a[2] = this.bf;
    f.a[5] = ay;
    f.a[6] = cQ;
    if (paramBoolean)
    {
      int i1 = (bM - 1) * 22 + 11;
      f.a[i1] = cY[1];
      f.a[(i1 + 1)] = cY[2];
      f.a[(i1 + 2)] = cY[3];
      for (int i2 = 0; i2 < 7; i2++) {
        f.a[(i1 + 3 + i2)] = T[0][i2];
      }
      for (i2 = 0; i2 < 7; i2++) {
        f.a[(i1 + 10 + i2)] = T[1][i2];
      }
      f.a[(i1 + 17)] = ((byte)s[0].l);
      f.a[(i1 + 18)] = cZ;
      f.a[(i1 + 19)] = dF;
    }
    f.f = true;
    f.b();
  }
  
  private final int a(int[] paramArrayOfInt1, int paramInt1, int[] paramArrayOfInt2, int paramInt2)
  {
    c localc = o[paramInt1];
    if (o[paramInt1].e) {
      return -1;
    }
    l[] arrayOfl1 = aS;
    l[] arrayOfl2 = aP;
    int i1 = 0;
    int[] arrayOfInt = cF;
    arrayOfl1[0] = localc.b[3];
    arrayOfl1[1] = localc.b[1];
    arrayOfl1[2] = localc.b[0];
    arrayOfl1[3] = localc.b[2];
    int i3;
    switch (i3 = localc.a)
    {
    case 1: 
      if ((Math.max(arrayOfl1[0].k, Math.max(arrayOfl1[1].k, arrayOfl1[2].k)) > arrayOfInt[1]) && (Math.max(arrayOfl1[0].l, Math.max(arrayOfl1[1].l, arrayOfl1[2].l)) > arrayOfInt[2])) {
        i3 = Math.abs(arrayOfInt[(i3 - 1)] - arrayOfl1[0].j);
      } else {
        i3 = 9830401;
      }
      break;
    case 2: 
      if ((Math.max(arrayOfl1[0].j, Math.max(arrayOfl1[1].j, arrayOfl1[2].j)) > arrayOfInt[0]) && (Math.max(arrayOfl1[0].l, Math.max(arrayOfl1[1].l, arrayOfl1[2].l)) > arrayOfInt[2])) {
        i3 = Math.abs(arrayOfInt[(i3 - 1)] - arrayOfl1[0].k);
      } else {
        i3 = 9830401;
      }
      break;
    case 3: 
      if ((Math.max(arrayOfl1[0].k, Math.max(arrayOfl1[1].k, arrayOfl1[2].k)) > arrayOfInt[1]) && (Math.max(arrayOfl1[0].j, Math.max(arrayOfl1[1].j, arrayOfl1[2].j)) > arrayOfInt[0])) {
        i3 = Math.abs(arrayOfInt[(i3 - 1)] - arrayOfl1[0].l);
      } else {
        i3 = 9830401;
      }
      break;
    }
    if (i3 <= 9830400)
    {
      localc.e = true;
      paramArrayOfInt2[aB] = paramArrayOfInt1[0];
      paramArrayOfInt2[(aB + 1)] = paramArrayOfInt1[1];
      paramArrayOfInt2[(aB + 2)] = paramArrayOfInt1[2];
      paramArrayOfInt2[(aB + 3)] = paramArrayOfInt1[3];
      if (localc.c == paramInt2)
      {
        paramArrayOfInt2[(aB + 4)] = localc.d;
        aB += 5;
        return localc.d;
      }
      paramArrayOfInt2[(aB + 4)] = localc.c;
      aB += 5;
      return localc.c;
    }
    for (int i2 = 3; i2 >= 0; i2--) {
      b(arrayOfl1[i2]);
    }
    if ((i1 = c(arrayOfl2, arrayOfl1, paramArrayOfInt1[2], 4)) == 0) {
      return -1;
    }
    if ((i1 = a(arrayOfl1, arrayOfl2, paramArrayOfInt1[3], i1)) == 0) {
      return -1;
    }
    if ((i1 = d(arrayOfl2, arrayOfl1, paramArrayOfInt1[1], i1)) == 0) {
      return -1;
    }
    if ((i1 = b(arrayOfl1, arrayOfl2, paramArrayOfInt1[0], i1)) == 0) {
      return -1;
    }
    for (i2 = i1 - 1; i2 >= 0; i2--) {
      a(arrayOfl1[i2]);
    }
    int i6 = arrayOfl1[0].e;
    int i7 = arrayOfl1[0].e;
    int i4 = arrayOfl1[0].d;
    int i5 = arrayOfl1[0].d;
    for (i2 = i1 - 1; i2 > 0; i2--)
    {
      if (i4 < arrayOfl1[i2].d) {
        i4 = arrayOfl1[i2].d;
      }
      if (i5 > arrayOfl1[i2].d) {
        i5 = arrayOfl1[i2].d;
      }
      if (i6 < arrayOfl1[i2].e) {
        i6 = arrayOfl1[i2].e;
      }
      if (i7 > arrayOfl1[i2].e) {
        i7 = arrayOfl1[i2].e;
      }
    }
    paramArrayOfInt2[aB] = (150 - i7);
    paramArrayOfInt2[(aB + 1)] = (i6 - 150 + 1);
    paramArrayOfInt2[(aB + 2)] = (120 - i5 + 1);
    paramArrayOfInt2[(aB + 3)] = (i4 - 120 + 1);
    if (localc.c == paramInt2)
    {
      paramArrayOfInt2[(aB + 4)] = localc.d;
      aB += 5;
      localc.e = true;
      return localc.d;
    }
    paramArrayOfInt2[(aB + 4)] = localc.c;
    aB += 5;
    localc.e = true;
    return localc.c;
  }
  
  private static void af()
  {
    switch (dF)
    {
    case 1: 
      l(1);
      return;
    case 2: 
      l(2);
      return;
    case 3: 
      l(3);
      return;
    case 4: 
      l(5);
    }
  }
  
  private static final void i(m paramm)
  {
    if (paramm.q != 0) {
      return;
    }
    if (!aG)
    {
      dH = paramm.n;
      dJ = paramm.o;
      dL = paramm.p;
      aG = true;
    }
    paramm.q = cs[ay];
    e locale1 = dk;
    e locale2 = aE;
    locale1.a = paramm.n;
    locale1.b = paramm.o;
    locale1.c = paramm.p;
    locale1.a += paramm.z[0] * 3000;
    locale1.b += paramm.z[1] * 3000;
    locale1.c += paramm.z[2] * 3000;
    int i1 = paramm.r;
    int i2 = -1;
    for (;;)
    {
      if (i1 == 999) {
        return;
      }
      if (a(i1, locale1, locale2, paramm, true) != -1) {
        return;
      }
      if ((i2 = a(i1, locale1, locale2, i2)) == -1) {
        break;
      }
      if (o[i2].c == i1) {
        i1 = o[i2].d;
      } else {
        i1 = o[i2].c;
      }
    }
    if (a(i1, locale1, locale2) != -1)
    {
      a(locale2.a, locale2.b, locale2.c, (byte)1, (short)i1);
      return;
    }
  }
  
  private final void j(m paramm)
  {
    if ((paramm.q != 0) || (ae != 0)) {
      return;
    }
    if (dF == 6) {
      ae = 4;
    }
    byte[] arrayOfByte1 = T[0];
    byte[] arrayOfByte2 = T[1];
    int i1 = dF;
    paramm.q = ct[dF];
    if (arrayOfByte1[i1] == 0)
    {
      if (arrayOfByte2[i1] != 0)
      {
        if (U[i1] > arrayOfByte2[i1])
        {
          arrayOfByte1[i1] = arrayOfByte2[i1];
          arrayOfByte2[i1] = 0;
        }
        else
        {
          arrayOfByte1[i1] = U[i1];
          int tmp110_108 = i1;
          byte[] tmp110_107 = arrayOfByte2;
          tmp110_107[tmp110_108] = ((byte)(tmp110_107[tmp110_108] - U[i1]));
        }
        paramm.q = 10;
        return;
      }
      w();
      return;
    }
    if ((arrayOfByte1[i1] > 0) && (!al))
    {
      int tmp148_146 = i1;
      byte[] tmp148_145 = arrayOfByte1;
      tmp148_145[tmp148_146] = ((byte)(tmp148_145[tmp148_146] - 1));
    }
    if (dd) {
      af();
    }
    if (dF == 0) {
      cr = 9;
    }
    Object localObject;
    int i4;
    if (cZ != 3)
    {
      aG = true;
      aH = true;
      aF = (byte)(aF + 1);
      if (aF > 2) {
        aF = 1;
      }
      aw += co[dF];
      if (aw > 20) {
        aw = 20;
      }
      if (cZ != 0)
      {
        dH = cF[0];
        dJ = cF[1];
        dL = cF[2];
        cp = e(32) + 24;
        cq = cp;
        paramm.m = 256;
      }
      else
      {
        aG = false;
        aH = false;
        cp = 128;
        cq = 128;
      }
      int i2 = 0;
      localObject = dk;
      e locale = aE;
      ((e)localObject).a = cF[0];
      ((e)localObject).b = cF[1];
      ((e)localObject).c = cF[2];
      i4 = dE[dF];
      locale.a = (((e)localObject).a + s[0].z[0] * i4);
      locale.b = (((e)localObject).b + s[0].z[1] * i4);
      locale.c = (((e)localObject).c + s[0].z[2] * i4);
      int i5 = s[0].r;
      int i6 = -1;
      if ((dF == 0) && (dN > 0))
      {
        s[dN].r = s[0].r;
        s[dN].A = true;
        dN = -1;
        return;
      }
      for (;;)
      {
        if (i5 == 999) {
          return;
        }
        if (a(i5, (e)localObject, locale, paramm, true) != -1)
        {
          if ((dF != 0) || (aU == 0)) {
            break;
          }
          if (((s[aU].y == 2) || (s[aU].y == 3)) && (!b(s[aU], paramm)))
          {
            s[aU].g = false;
            s[aU].i = true;
            s[aU].f = ((short)V[s[aU].y][18]);
            s[aU].A = false;
            dN = (byte)aU;
          }
          return;
        }
        if ((i6 = a(i5, (e)localObject, locale, i6)) != -1)
        {
          if (o[i6].c == i5) {
            i5 = o[i6].d;
          } else {
            i5 = o[i6].c;
          }
        }
        else
        {
          if (a(i5, (e)localObject, locale) == -1) {
            break;
          }
          if (dF == 5)
          {
            a(locale.a, locale.b, locale.c, (byte)0, (short)i5);
            a(locale.a, locale.b, locale.c);
            break;
          }
          a(locale.a, locale.b, locale.c, (byte)1, (short)i5);
          return;
        }
      }
      return;
    }
    if (arrayOfByte1[i1] == 0)
    {
      dC = 0;
      cZ = 0;
      ae = 5;
      cY[3] = 0;
    }
    if (cT >= 19) {
      return;
    }
    cT += 1;
    int[][] arrayOfInt = cR;
    for (int i3 = 19; i3 >= 0; i3--) {
      if (arrayOfInt[i3][6] == 0)
      {
        localObject = arrayOfInt[i3];
        if ((i4 = cC - 15) < 0) {
          i4 = 0;
        }
        localObject[3] = ((int)(-cU[cE] * -cU[i4] >> 16));
        localObject[4] = ((int)(-aq[cE] * -cU[i4] >> 16));
        localObject[5] = (-aq[i4]);
        localObject[8] = 160;
        localObject[0] = (paramm.n + localObject[3] * 160);
        localObject[1] = (paramm.o + localObject[4] * 160);
        localObject[2] = (paramm.p + localObject[5] * 160);
        localObject[6] = 30;
        localObject[7] = paramm.r;
        localObject[9] = 1;
        return;
      }
    }
  }
  
  private static final void c(m paramm1, m paramm2)
  {
    if (cT >= 19) {
      return;
    }
    cT += 1;
    int[][] arrayOfInt = cR;
    int i6 = 65536;
    for (int i7 = 19; i7 >= 0; i7--) {
      if (arrayOfInt[i7][6] == 0)
      {
        int[] arrayOfInt1 = arrayOfInt[i7];
        int i1 = paramm1.n - paramm2.n >> 16;
        int i2 = paramm1.o - paramm2.o >> 16;
        int i3 = paramm1.p - (paramm2.p - 8192000) >> 16;
        int i4 = i1 * i1 + i2 * i2 + i3 * i3;
        int i5 = 0;
        while (i6 >>= 1 > 0) {
          if ((i5 + i6) * (i5 + i6) <= i4) {
            i5 += i6;
          }
        }
        if (i5 == 0) {
          i5 = 1;
        }
        arrayOfInt1[3] = ((int)(-i1 * 65536L / i5));
        arrayOfInt1[4] = ((int)(-i2 * 65536L / i5));
        arrayOfInt1[5] = ((int)(-i3 * 65536L / i5));
        arrayOfInt1[0] = (paramm1.n + arrayOfInt1[3] * 100);
        arrayOfInt1[1] = (paramm1.o + arrayOfInt1[4] * 100);
        arrayOfInt1[2] = (paramm1.p + arrayOfInt1[5] * 100);
        arrayOfInt1[6] = 70;
        arrayOfInt1[7] = 2;
        arrayOfInt1[8] = 1;
        arrayOfInt1[9] = 5;
        return;
      }
    }
  }
  
  public final void showNotify()
  {
    super.showNotify();
  }
  
  private static byte[] a(int paramInt, byte[] paramArrayOfByte1, byte paramByte1, byte paramByte2, byte paramByte3, byte paramByte4, byte[] paramArrayOfByte2, byte paramByte5, byte paramByte6, byte paramByte7, byte paramByte8)
  {
    int i1 = paramByte3;
    int i2 = paramByte1 + paramByte3;
    int i3 = paramByte7;
    int i4 = paramByte5 + paramByte7;
    byte b1 = Math.abs(Math.max(Math.max(i1, i2), Math.max(i3, i4)) - Math.min(Math.min(i1, i2), Math.min(i3, i4)));
    byte b2 = -Math.min(i1, i3);
    i1 = paramByte4;
    i3 = paramByte8;
    byte b3;
    int i5 = (b3 = paramByte8) - Math.max(i1, i3);
    if (b1 == 0) {
      b1 = Math.max(paramByte1, paramByte5);
    }
    byte[] arrayOfByte = new byte[b1 * b3];
    aM[(paramInt * 5)] = ((byte)b1);
    aM[(paramInt * 5 + 1)] = ((byte)b3);
    aM[(paramInt * 5 + 4)] = ((byte)(ab[paramInt][4] - b3));
    if (((paramInt < 11) && (paramInt > 6)) || ((paramInt < 25) && (paramInt > 20)) || (paramInt == 30) || ((paramInt < 39) && (paramInt > 34)) || ((paramInt < 53) && (paramInt > 48)))
    {
      aM[(paramInt * 5 + 2)] = ((byte)(int)(b1 * 115998L >> 16));
      aM[(paramInt * 5 + 3)] = ((byte)(int)(b3 * 115998L >> 16));
    }
    else
    {
      aM[(paramInt * 5 + 2)] = ((byte)b1);
      aM[(paramInt * 5 + 3)] = ((byte)b3);
    }
    int i6 = (b3 - paramByte4 - i5) * b1;
    int i7 = 0;
    int i8 = 0;
    for (byte b4 = 0; b4 < paramByte2; b4++)
    {
      i8 = b4 * b1 + (b2 + paramByte3) + i6;
      for (b5 = 0; b5 < paramByte1; b5++)
      {
        arrayOfByte[(i8 + b5)] = paramArrayOfByte1[i7];
        i7++;
      }
    }
    i6 = (b3 - paramByte8 - i5) * b1;
    i7 = 0;
    for (byte b5 = 0; b5 < paramByte6; b5++)
    {
      i8 = i6 + b5 * b1 + (b2 + paramByte7);
      for (byte b6 = 0; b6 < paramByte5; b6++)
      {
        if (paramArrayOfByte2[i7] != 0) {
          arrayOfByte[(i8 + b6)] = paramArrayOfByte2[i7];
        }
        i7++;
      }
    }
    return arrayOfByte;
  }
  
  private static final void a(int[] paramArrayOfInt1, int[] paramArrayOfInt2)
  {
    int[] arrayOfInt1 = ba;
    int[] arrayOfInt2 = aR;
    int i1 = paramArrayOfInt1.length >> 4;
    for (int i3 = 0; i3 < i1; i3++)
    {
      int i2 = i3 << 4;
      arrayOfInt2[i3] = (paramArrayOfInt2[(paramArrayOfInt1[i2] + 5)] + paramArrayOfInt2[(paramArrayOfInt1[(i2 + 1)] + 5)] + paramArrayOfInt2[(paramArrayOfInt1[(i2 + 2)] + 5)]);
      arrayOfInt1[i3] = i3;
    }
    b(arrayOfInt2, arrayOfInt1, 0, i1 - 1);
  }
  
  private static final int k(int paramInt)
  {
    int[] arrayOfInt1 = aZ;
    int[] arrayOfInt2 = aQ;
    int i1 = cF[0];
    int i2 = cF[1];
    int i3 = cF[2];
    int i4 = bS;
    int i5 = 0;
    int[][] arrayOfInt3 = dg;
    int[][] arrayOfInt4 = cR;
    int i6 = 0;
    int i7 = 0;
    for (int i8 = dv - 1; i8 > 0; i8--)
    {
      m localm;
      if (((localm = s[i8]).A) && (paramInt == localm.r))
      {
        arrayOfInt1[i5] = i8;
        arrayOfInt2[i5] = (Math.abs(localm.n - i1) + Math.abs(localm.o - i2) + Math.abs(localm.p - i3));
        i5++;
      }
    }
    for (int i9 = 0; i9 < bU; i9++)
    {
      j localj;
      if (((localj = l[i9]).u) && (localj.r == paramInt) && (bT != i9))
      {
        arrayOfInt1[i5] = (i9 + i4);
        arrayOfInt2[i5] = (Math.abs(localj.m - i1) + Math.abs(localj.n - i2) + Math.abs(localj.o - i3));
        i5++;
      }
    }
    i4 += bU;
    while (i6 < dh) {
      if (arrayOfInt3[i7][4] == 0)
      {
        i7++;
      }
      else
      {
        if (arrayOfInt3[i7][5] == paramInt)
        {
          arrayOfInt1[i5] = (i7 + i4);
          arrayOfInt2[i5] = (Math.abs(arrayOfInt3[i7][0] - i1) + Math.abs(arrayOfInt3[i7][1] - i2) + Math.abs(arrayOfInt3[i7][2] - i3));
          i5++;
        }
        i6++;
        i7++;
      }
    }
    i4 += 25;
    i6 = 0;
    i7 = 0;
    while (i6 < cT) {
      if (arrayOfInt4[i7][6] == 0)
      {
        i7++;
      }
      else
      {
        if (arrayOfInt4[i7][7] == paramInt)
        {
          arrayOfInt1[i5] = (i7 + i4);
          arrayOfInt2[i5] = (Math.abs(arrayOfInt4[i7][0] - i1) + Math.abs(arrayOfInt4[i7][1] - i2) + Math.abs(arrayOfInt4[i7][2] - i3));
          i5++;
        }
        i6++;
        i7++;
      }
    }
    b(arrayOfInt2, arrayOfInt1, 0, i5 - 1);
    return i5;
  }
  
  private static void a(int paramInt, boolean paramBoolean)
  {
    if ((bM < 1) && (paramInt < bk)) {
      return;
    }
    if ((!paramBoolean) && (paramInt >= bk)) {
      return;
    }
    if (dd)
    {
      if (p.k == null)
      {
        Y = 1;
        NET_Lizard.b.repaint();
        NET_Lizard.b.serviceRepaints();
        p.a(NET_Lizard.b);
      }
      if (ck) {
        p.a = 0;
      } else {
        p.a = -1;
      }
      if (paramBoolean) {
        paramInt = bk;
      }
      p.a(paramInt);
      Y = -1;
    }
  }
  
  private static void l(int paramInt)
  {
    if ((ck) && (paramInt != 0) && (paramInt != 4) && (paramInt < bk)) {
      return;
    }
    a(paramInt, false);
  }
  
  private static void ag() {}
  
  public static void f() {}
  
  private static void ah()
  {
    m[] arrayOfm = s;
    for (int i1 = 0; i1 < dv; i1++)
    {
      m localm;
      (localm = arrayOfm[i1]).b[0] = 0;
      localm.b[1] = 0;
      localm.b[2] = 0;
    }
  }
  
  private static void b(m paramm, int paramInt1, int paramInt2, int paramInt3, int paramInt4)
  {
    int[] arrayOfInt1 = aq;
    int[] arrayOfInt2 = cU;
    int i1 = paramInt1 - paramm.n >> 16;
    int i2 = paramInt2 - paramm.o >> 16;
    int i3 = paramInt3 - paramm.p >> 16;
    int i4 = i1 * i1 + i2 * i2 + i3 * i3;
    int i5 = 0;
    int i6 = 65536;
    while (i6 >>= 1 > 0) {
      if ((i5 + i6) * (i5 + i6) <= i4) {
        i5 += i6;
      }
    }
    if (i5 == 0) {
      i5 = 1;
    }
    paramm.z[0] = (i1 * 65536 / i5);
    paramm.z[1] = (i2 * 65536 / i5);
    paramm.z[2] = (i3 * 65536 / i5);
    i4 = i1 * i1 + i2 * i2;
    i6 = 65536;
    i5 = 0;
    while (i6 >>= 1 > 0) {
      if ((i5 + i6) * (i5 + i6) <= i4) {
        i5 += i6;
      }
    }
    if (i5 == 0) {
      i5 = 1;
    }
    paramm.s[0] = (i1 * 65536 / i5);
    paramm.s[1] = (i2 * 65536 / i5);
    if (paramInt4 == 0) {
      return;
    }
    if (paramInt4 -= e(paramInt4 << 1) < 0) {
      paramInt4 += 360;
    }
    paramm.z[0] = ((int)(paramm.z[0] * arrayOfInt1[paramInt4] - paramm.z[1] * arrayOfInt2[paramInt4] >> 16));
    paramm.z[1] = ((int)(paramm.z[0] * arrayOfInt2[paramInt4] + paramm.z[1] * arrayOfInt1[paramInt4] >> 16));
  }
  
  private static final int a(e parame1, e parame2, e parame3, int paramInt1, int paramInt2, int paramInt3, int paramInt4, int paramInt5, int paramInt6)
  {
    int[] arrayOfInt = aA;
    int i6 = -1;
    long l3 = Math.abs(parame1.a - parame2.a) + Math.abs(parame1.b - parame2.b) + Math.abs(parame1.c - parame2.c);
    int i1 = paramInt1 - parame2.a >> 16;
    int i2;
    long l1;
    long l2;
    int i3;
    int i4;
    int i5;
    if ((((i2 = paramInt1 - parame3.a >> 16) >= 0) && (i1 <= 0)) || ((i1 >= 0) && (i2 <= 0)))
    {
      if (i2 - i1 > 0)
      {
        l1 = i2 * arrayOfInt[(i2 - i1)];
        l2 = -i1 * arrayOfInt[(i2 - i1)];
      }
      else
      {
        l1 = -i2 * arrayOfInt[(i1 - i2)];
        l2 = i1 * arrayOfInt[(i1 - i2)];
      }
      i3 = (int)(parame2.a * l1 + parame3.a * l2 >> 18);
      i4 = (int)(parame2.b * l1 + parame3.b * l2 >> 18);
      i5 = (int)(parame2.c * l1 + parame3.c * l2 >> 18);
      if ((paramInt5 <= i4) && (paramInt6 <= i5) && (paramInt2 >= i4) && (paramInt3 >= i5))
      {
        parame3.a = (i3 + 65536);
        parame3.b = i4;
        parame3.c = i5;
        i6 = 1;
      }
    }
    i1 = paramInt2 - parame2.b >> 16;
    if ((((i2 = paramInt2 - parame3.b >> 16) >= 0) && (i1 <= 0)) || ((i1 >= 0) && (i2 <= 0)))
    {
      if (i2 - i1 > 0)
      {
        l1 = i2 * arrayOfInt[(i2 - i1)];
        l2 = -i1 * arrayOfInt[(i2 - i1)];
      }
      else
      {
        l1 = -i2 * arrayOfInt[(i1 - i2)];
        l2 = i1 * arrayOfInt[(i1 - i2)];
      }
      i3 = (int)(parame2.a * l1 + parame3.a * l2 >> 18);
      i4 = (int)(parame2.b * l1 + parame3.b * l2 >> 18);
      i5 = (int)(parame2.c * l1 + parame3.c * l2 >> 18);
      if ((paramInt4 <= i3) && (paramInt6 <= i5) && (paramInt1 >= i3) && (paramInt3 >= i5))
      {
        parame3.a = i3;
        parame3.b = (i4 + 65536);
        parame3.c = i5;
        i6 = 2;
      }
    }
    i1 = paramInt3 - parame2.c >> 16;
    if ((((i2 = paramInt3 - parame3.c >> 16) >= 0) && (i1 <= 0)) || ((i1 >= 0) && (i2 <= 0)))
    {
      if (i2 - i1 > 0)
      {
        l1 = i2 * arrayOfInt[(i2 - i1)];
        l2 = -i1 * arrayOfInt[(i2 - i1)];
      }
      else
      {
        l1 = -i2 * arrayOfInt[(i1 - i2)];
        l2 = i1 * arrayOfInt[(i1 - i2)];
      }
      i3 = (int)(parame2.a * l1 + parame3.a * l2 >> 18);
      i4 = (int)(parame2.b * l1 + parame3.b * l2 >> 18);
      i5 = (int)(parame2.c * l1 + parame3.c * l2 >> 18);
      if ((paramInt4 <= i3) && (paramInt5 <= i4) && (paramInt1 >= i3) && (paramInt2 >= i4))
      {
        parame3.a = i3;
        parame3.b = i4;
        parame3.c = (i5 + 65536);
        i6 = 3;
      }
    }
    i1 = parame2.a - paramInt4 >> 16;
    if ((((i2 = parame3.a - paramInt4 >> 16) >= 0) && (i1 <= 0)) || ((i1 >= 0) && (i2 <= 0)))
    {
      if (i2 - i1 > 0)
      {
        l1 = i2 * arrayOfInt[(i2 - i1)];
        l2 = -i1 * arrayOfInt[(i2 - i1)];
      }
      else
      {
        l1 = -i2 * arrayOfInt[(i1 - i2)];
        l2 = i1 * arrayOfInt[(i1 - i2)];
      }
      i3 = (int)(parame2.a * l1 + parame3.a * l2 >> 18);
      i4 = (int)(parame2.b * l1 + parame3.b * l2 >> 18);
      i5 = (int)(parame2.c * l1 + parame3.c * l2 >> 18);
      if ((paramInt5 <= i4) && (paramInt6 <= i5) && (paramInt2 >= i4) && (paramInt3 >= i5))
      {
        parame3.a = i3;
        parame3.b = i4;
        parame3.c = i5;
        i6 = 1;
      }
    }
    i1 = parame2.b - paramInt5 >> 16;
    if ((((i2 = parame3.b - paramInt5 >> 16) >= 0) && (i1 <= 0)) || ((i1 >= 0) && (i2 <= 0)))
    {
      if (i2 - i1 > 0)
      {
        l1 = i2 * arrayOfInt[(i2 - i1)];
        l2 = -i1 * arrayOfInt[(i2 - i1)];
      }
      else
      {
        l1 = -i2 * arrayOfInt[(i1 - i2)];
        l2 = i1 * arrayOfInt[(i1 - i2)];
      }
      i3 = (int)(parame2.a * l1 + parame3.a * l2 >> 18);
      i4 = (int)(parame2.b * l1 + parame3.b * l2 >> 18);
      i5 = (int)(parame2.c * l1 + parame3.c * l2 >> 18);
      if ((paramInt4 <= i3) && (paramInt6 <= i5) && (paramInt1 >= i3) && (paramInt3 >= i5))
      {
        parame3.a = i3;
        parame3.b = i4;
        parame3.c = i5;
        i6 = 2;
      }
    }
    i1 = parame2.c - paramInt6 >> 16;
    if ((((i2 = parame3.c - paramInt6 >> 16) >= 0) && (i1 <= 0)) || ((i1 >= 0) && (i2 <= 0)))
    {
      if (i2 - i1 > 0)
      {
        l1 = i2 * arrayOfInt[(i2 - i1)];
        l2 = -i1 * arrayOfInt[(i2 - i1)];
      }
      else
      {
        l1 = -i2 * arrayOfInt[(i1 - i2)];
        l2 = i1 * arrayOfInt[(i1 - i2)];
      }
      i3 = (int)(parame2.a * l1 + parame3.a * l2 >> 18);
      i4 = (int)(parame2.b * l1 + parame3.b * l2 >> 18);
      i5 = (int)(parame2.c * l1 + parame3.c * l2 >> 18);
      if ((paramInt4 <= i3) && (paramInt5 <= i4) && (paramInt1 >= i3) && (paramInt2 >= i4))
      {
        parame3.a = i3;
        parame3.b = i4;
        parame3.c = i5;
        i6 = 3;
      }
    }
    if (Math.abs(parame3.a - parame2.a) + Math.abs(parame3.b - parame2.b) + Math.abs(parame3.c - parame2.c) < l3)
    {
      parame1.a = parame3.a;
      parame1.b = parame3.b;
      parame1.c = parame3.c;
      Math.abs(parame1.a - parame2.a);
      Math.abs(parame1.b - parame2.b);
      Math.abs(parame1.c - parame2.c);
    }
    return i6;
  }
  
  private static final boolean ai()
  {
    byte[] arrayOfByte;
    if ((arrayOfByte = f.g.a(f.a(K), -1)) == null) {
      return false;
    }
    int i1 = 0;
    int i2 = 0;
    int i3 = arrayOfByte.length;
    for (int i4 = 0; i4 < arrayOfByte.length; i4++)
    {
      i1 += (arrayOfByte[i4] < 0 ? arrayOfByte[i4] + 256 : arrayOfByte[i4]);
      i2 += arrayOfByte[i4];
    }
    a locala;
    return (locala = new a()).a == i1 + i2 + i3;
  }
  
  private static final int c(int paramInt1, int paramInt2)
  {
    if (paramInt1 < 0) {
      paramInt1 += 256;
    }
    if (paramInt2 < 0) {
      paramInt2 += 256;
    }
    return paramInt1 + paramInt2 * 256;
  }
  
  private static final void b(byte paramByte)
  {
    du = true;
    cz -= paramByte + 1;
    if (cz < -5 << paramByte) {
      cz = -5 << paramByte;
    }
    cp += 2;
  }
  
  private static final void c(byte paramByte)
  {
    du = true;
    cz += paramByte + 1;
    if (cz > 5 << paramByte) {
      cz = 5 << paramByte;
    }
  }
  
  private static final void b(int[] paramArrayOfInt)
  {
    int[] arrayOfInt1 = cU;
    int[] arrayOfInt2 = aq;
    paramArrayOfInt[0] = ((int)(-arrayOfInt1[cE] * -arrayOfInt1[cC] >> 16));
    paramArrayOfInt[1] = ((int)(-arrayOfInt2[cE] * -arrayOfInt1[cC] >> 16));
    paramArrayOfInt[2] = (-aq[cC]);
    int i1;
    if ((i1 = aw >> 1) != 0)
    {
      if (i1 -= e(i1 << 1) < 0) {
        i1 += 360;
      }
      paramArrayOfInt[0] = ((int)(paramArrayOfInt[0] * arrayOfInt2[i1] - paramArrayOfInt[1] * arrayOfInt1[i1] >> 16));
      paramArrayOfInt[1] = ((int)(paramArrayOfInt[0] * arrayOfInt1[i1] + paramArrayOfInt[1] * arrayOfInt2[i1] >> 16));
    }
  }
  
  private static final void a(l paraml1, l paraml2, l paraml3, int paramInt1, int paramInt2, int paramInt3)
  {
    byte[] arrayOfByte = do[aY];
    int[] arrayOfInt1 = ca[aY];
    int[] arrayOfInt2 = aA;
    int[] arrayOfInt3 = ap;
    int[] arrayOfInt4 = az;
    int i17 = R;
    int i18 = arrayOfInt3[(paraml3.e - paraml1.e)];
    int i19 = arrayOfInt3[(paraml2.e - paraml1.e)];
    for (int i2 = paraml1.e; i2 < paraml2.e; i2++)
    {
      int i5 = (i2 - paraml1.e) * i18;
      int i6 = paraml1.d + (int)((paraml3.d - paraml1.d) * i5 >> 16);
      int i7 = paraml1.g + (int)((paraml3.g - paraml1.g) * i5 >> 16);
      int i8 = paraml1.i + (int)((paraml3.i - paraml1.i) * i5 >> 16);
      int i9 = paraml1.m + (int)((paraml3.m - paraml1.m) * i5 >> 16);
      i5 = (i2 - paraml1.e) * i19;
      int i10 = paraml1.m + (int)((paraml2.m - paraml1.m) * i5 >> 16);
      int i1 = i2 * 240 + i6;
      int i3 = paraml1.d + (int)((paraml2.d - paraml1.d) * i5 >> 16) - i6;
      i6 = arrayOfInt2[i9];
      int i11 = i7 * i6;
      int i14;
      int i15;
      int i16;
      int i4;
      for (int i12 = i8 * i6; i3 >= 16; i12 = i14)
      {
        i7 += paramInt1;
        i8 += paramInt2;
        i9 += paramInt3;
        i6 = arrayOfInt2[i9];
        int i13 = i7 * i6;
        i14 = i8 * i6;
        i15 = i13 - i11 >> 4;
        i16 = i14 - i12 >> 4;
        i4 = 16;
        while (i4-- > 0)
        {
          i6 = arrayOfInt1[arrayOfByte[((i12 >> 18 << 6) + (i11 >> 18) & 0xFFF)]];
          arrayOfInt4[(i1++)] = ((((i6 & 0xFF0000) >> 16) * i17 >> 8 << 16) + (((i6 & 0xFF00) >> 8) * i17 >> 8 << 8) + ((i6 & 0xFF) * i17 >> 8));
          i11 += i15;
          i12 += i16;
        }
        i3 -= 16;
        i11 = i13;
      }
      if (i3 > 0)
      {
        i6 = arrayOfInt2[i10];
        i4 = arrayOfInt3[i3];
        i15 = (int)(((paraml1.g + (int)((paraml2.g - paraml1.g) * i5 >> 16)) * i6 - i11) * i4 >> 16);
        i16 = (int)(((paraml1.i + (int)((paraml2.i - paraml1.i) * i5 >> 16)) * i6 - i12) * i4 >> 16);
        while (i3-- > 0)
        {
          i6 = arrayOfInt1[arrayOfByte[((i12 >> 18 << 6) + (i11 >> 18) & 0xFFF)]];
          arrayOfInt4[(i1++)] = ((((i6 & 0xFF0000) >> 16) * i17 >> 8 << 16) + (((i6 & 0xFF00) >> 8) * i17 >> 8 << 8) + ((i6 & 0xFF) * i17 >> 8));
          i11 += i15;
          i12 += i16;
        }
      }
    }
  }
  
  private static final void b(l paraml1, l paraml2, l paraml3, int paramInt1, int paramInt2, int paramInt3)
  {
    byte[] arrayOfByte = do[aY];
    int[] arrayOfInt1 = ca[aY];
    int[] arrayOfInt2 = aA;
    int[] arrayOfInt3 = ap;
    int[] arrayOfInt4 = az;
    int i17 = R;
    int i18 = arrayOfInt3[(paraml3.e - paraml1.e)];
    int i19 = arrayOfInt3[(paraml2.e - paraml1.e)];
    for (int i2 = paraml1.e; i2 < paraml2.e; i2++)
    {
      int i5 = (i2 - paraml1.e) * i18;
      int i6 = paraml1.d + (int)((paraml3.d - paraml1.d) * i5 >> 16);
      int i7 = paraml1.g + (int)((paraml3.g - paraml1.g) * i5 >> 16);
      int i8 = paraml1.i + (int)((paraml3.i - paraml1.i) * i5 >> 16);
      int i9 = paraml1.m + (int)((paraml3.m - paraml1.m) * i5 >> 16);
      i5 = (i2 - paraml1.e) * i19;
      int i10 = paraml1.m + (int)((paraml2.m - paraml1.m) * i5 >> 16);
      int i1 = i2 * 240 + i6;
      int i3 = paraml1.d + (int)((paraml2.d - paraml1.d) * i5 >> 16) - i6;
      i6 = arrayOfInt2[i9];
      int i11 = i7 * i6;
      int i14;
      int i15;
      int i16;
      int i4;
      for (int i12 = i8 * i6; i3 >= 16; i12 = i14)
      {
        i7 += paramInt1;
        i8 += paramInt2;
        i9 += paramInt3;
        i6 = arrayOfInt2[i9];
        int i13 = i7 * i6;
        i14 = i8 * i6;
        i15 = i13 - i11 >> 4;
        i16 = i14 - i12 >> 4;
        i4 = 16;
        while (i4-- > 0)
        {
          if ((i6 = arrayOfInt1[arrayOfByte[((i12 >> 18 << 6) + (i11 >> 18) & 0xFFF)]]) != 0) {
            arrayOfInt4[i1] = ((((i6 & 0xFF0000) >> 16) * i17 >> 8 << 16) + (((i6 & 0xFF00) >> 8) * i17 >> 8 << 8) + ((i6 & 0xFF) * i17 >> 8));
          }
          i1++;
          i11 += i15;
          i12 += i16;
        }
        i3 -= 16;
        i11 = i13;
      }
      if (i3 > 0)
      {
        i6 = arrayOfInt2[i10];
        i4 = arrayOfInt3[i3];
        i15 = (int)(((paraml1.g + (int)((paraml2.g - paraml1.g) * i5 >> 16)) * i6 - i11) * i4 >> 16);
        i16 = (int)(((paraml1.i + (int)((paraml2.i - paraml1.i) * i5 >> 16)) * i6 - i12) * i4 >> 16);
        while (i3-- > 0)
        {
          if ((i6 = arrayOfInt1[arrayOfByte[((i12 >> 18 << 6) + (i11 >> 18) & 0xFFF)]]) != 0) {
            arrayOfInt4[i1] = ((((i6 & 0xFF0000) >> 16) * i17 >> 8 << 16) + (((i6 & 0xFF00) >> 8) * i17 >> 8 << 8) + ((i6 & 0xFF) * i17 >> 8));
          }
          i1++;
          i11 += i15;
          i12 += i16;
        }
      }
    }
  }
  
  private static final void c(l paraml1, l paraml2, l paraml3, int paramInt1, int paramInt2, int paramInt3)
  {
    byte[] arrayOfByte = do[aY];
    int[] arrayOfInt1 = ca[aY];
    int[] arrayOfInt2 = aA;
    int[] arrayOfInt3 = ap;
    int[] arrayOfInt4 = az;
    int i17 = R;
    int i18 = arrayOfInt3[(paraml2.e - paraml1.e)];
    int i19 = arrayOfInt3[(paraml3.e - paraml1.e)];
    for (int i2 = paraml1.e; i2 < paraml2.e; i2++)
    {
      int i5 = (i2 - paraml1.e) * i18;
      int i6 = paraml1.d + (int)((paraml2.d - paraml1.d) * i5 >> 16);
      int i7 = paraml1.g + (int)((paraml2.g - paraml1.g) * i5 >> 16);
      int i8 = paraml1.i + (int)((paraml2.i - paraml1.i) * i5 >> 16);
      int i10 = paraml1.m + (int)((paraml2.m - paraml1.m) * i5 >> 16);
      i5 = (i2 - paraml1.e) * i19;
      int i9 = paraml1.m + (int)((paraml3.m - paraml1.m) * i5 >> 16);
      int i1 = i2 * 240 + i6;
      int i3 = paraml1.d + (int)((paraml3.d - paraml1.d) * i5 >> 16) - i6;
      i6 = arrayOfInt2[i10];
      int i11 = i7 * i6;
      int i14;
      int i15;
      int i16;
      int i4;
      for (int i12 = i8 * i6; i3 >= 16; i12 = i14)
      {
        i7 += paramInt1;
        i8 += paramInt2;
        i10 += paramInt3;
        i6 = arrayOfInt2[i10];
        int i13 = i7 * i6;
        i14 = i8 * i6;
        i15 = i13 - i11 >> 4;
        i16 = i14 - i12 >> 4;
        i4 = 16;
        while (i4-- > 0)
        {
          i6 = arrayOfInt1[arrayOfByte[((i12 >> 18 << 6) + (i11 >> 18) & 0xFFF)]];
          arrayOfInt4[(i1++)] = ((((i6 & 0xFF0000) >> 16) * i17 >> 8 << 16) + (((i6 & 0xFF00) >> 8) * i17 >> 8 << 8) + ((i6 & 0xFF) * i17 >> 8));
          i11 += i15;
          i12 += i16;
        }
        i3 -= 16;
        i11 = i13;
      }
      if (i3 > 0)
      {
        i6 = arrayOfInt2[i9];
        i4 = arrayOfInt3[i3];
        i15 = (int)(((paraml1.g + (int)((paraml3.g - paraml1.g) * i5 >> 16)) * i6 - i11) * i4 >> 16);
        i16 = (int)(((paraml1.i + (int)((paraml3.i - paraml1.i) * i5 >> 16)) * i6 - i12) * i4 >> 16);
        while (i3-- > 0)
        {
          i6 = arrayOfInt1[arrayOfByte[((i12 >> 18 << 6) + (i11 >> 18) & 0xFFF)]];
          arrayOfInt4[(i1++)] = ((((i6 & 0xFF0000) >> 16) * i17 >> 8 << 16) + (((i6 & 0xFF00) >> 8) * i17 >> 8 << 8) + ((i6 & 0xFF) * i17 >> 8));
          i11 += i15;
          i12 += i16;
        }
      }
    }
  }
  
  private static final void d(l paraml1, l paraml2, l paraml3, int paramInt1, int paramInt2, int paramInt3)
  {
    byte[] arrayOfByte = do[aY];
    int[] arrayOfInt1 = ca[aY];
    int[] arrayOfInt2 = aA;
    int[] arrayOfInt3 = ap;
    int[] arrayOfInt4 = az;
    int i17 = R;
    int i18 = arrayOfInt3[(paraml2.e - paraml1.e)];
    int i19 = arrayOfInt3[(paraml3.e - paraml1.e)];
    for (int i2 = paraml1.e; i2 < paraml2.e; i2++)
    {
      int i5 = (i2 - paraml1.e) * i18;
      int i6 = paraml1.d + (int)((paraml2.d - paraml1.d) * i5 >> 16);
      int i7 = paraml1.g + (int)((paraml2.g - paraml1.g) * i5 >> 16);
      int i8 = paraml1.i + (int)((paraml2.i - paraml1.i) * i5 >> 16);
      int i10 = paraml1.m + (int)((paraml2.m - paraml1.m) * i5 >> 16);
      i5 = (i2 - paraml1.e) * i19;
      int i9 = paraml1.m + (int)((paraml3.m - paraml1.m) * i5 >> 16);
      int i1 = i2 * 240 + i6;
      int i3 = paraml1.d + (int)((paraml3.d - paraml1.d) * i5 >> 16) - i6;
      i6 = arrayOfInt2[i10];
      int i11 = i7 * i6;
      int i14;
      int i15;
      int i16;
      int i4;
      for (int i12 = i8 * i6; i3 >= 16; i12 = i14)
      {
        i7 += paramInt1;
        i8 += paramInt2;
        i10 += paramInt3;
        i6 = arrayOfInt2[i10];
        int i13 = i7 * i6;
        i14 = i8 * i6;
        i15 = i13 - i11 >> 4;
        i16 = i14 - i12 >> 4;
        i4 = 16;
        while (i4-- > 0)
        {
          if ((i6 = arrayOfInt1[arrayOfByte[((i12 >> 18 << 6) + (i11 >> 18) & 0xFFF)]]) != 0) {
            arrayOfInt4[i1] = ((((i6 & 0xFF0000) >> 16) * i17 >> 8 << 16) + (((i6 & 0xFF00) >> 8) * i17 >> 8 << 8) + ((i6 & 0xFF) * i17 >> 8));
          }
          i1++;
          i11 += i15;
          i12 += i16;
        }
        i3 -= 16;
        i11 = i13;
      }
      if (i3 > 0)
      {
        i6 = arrayOfInt2[i9];
        i4 = arrayOfInt3[i3];
        i15 = (int)(((paraml1.g + (int)((paraml3.g - paraml1.g) * i5 >> 16)) * i6 - i11) * i4 >> 16);
        i16 = (int)(((paraml1.i + (int)((paraml3.i - paraml1.i) * i5 >> 16)) * i6 - i12) * i4 >> 16);
        while (i3-- > 0)
        {
          if ((i6 = arrayOfInt1[arrayOfByte[((i12 >> 18 << 6) + (i11 >> 18) & 0xFFF)]]) != 0) {
            arrayOfInt4[i1] = ((((i6 & 0xFF0000) >> 16) * i17 >> 8 << 16) + (((i6 & 0xFF00) >> 8) * i17 >> 8 << 8) + ((i6 & 0xFF) * i17 >> 8));
          }
          i1++;
          i11 += i15;
          i12 += i16;
        }
      }
    }
  }
  
  private static final void e(l paraml1, l paraml2, l paraml3, int paramInt1, int paramInt2, int paramInt3)
  {
    byte[] arrayOfByte = do[aY];
    int[] arrayOfInt1 = ca[aY];
    int[] arrayOfInt2 = aA;
    int[] arrayOfInt3 = ap;
    int[] arrayOfInt4 = az;
    int i17 = R;
    int i18 = arrayOfInt3[(paraml3.e - paraml1.e)];
    int i19 = arrayOfInt3[(paraml3.e - paraml2.e)];
    for (int i2 = paraml2.e; i2 < paraml3.e; i2++)
    {
      int i5 = (i2 - paraml1.e) * i18;
      int i6 = paraml1.d + (int)((paraml3.d - paraml1.d) * i5 >> 16);
      int i7 = paraml1.g + (int)((paraml3.g - paraml1.g) * i5 >> 16);
      int i8 = paraml1.i + (int)((paraml3.i - paraml1.i) * i5 >> 16);
      int i9 = paraml1.m + (int)((paraml3.m - paraml1.m) * i5 >> 16);
      i5 = (i2 - paraml2.e) * i19;
      int i10 = paraml2.m + (int)((paraml3.m - paraml2.m) * i5 >> 16);
      int i1 = i2 * 240 + i6;
      int i3 = paraml2.d + (int)((paraml3.d - paraml2.d) * i5 >> 16) - i6;
      i6 = arrayOfInt2[i9];
      int i11 = i7 * i6;
      int i14;
      int i15;
      int i16;
      int i4;
      for (int i12 = i8 * i6; i3 >= 16; i12 = i14)
      {
        i7 += paramInt1;
        i8 += paramInt2;
        i9 += paramInt3;
        i6 = arrayOfInt2[i9];
        int i13 = i7 * i6;
        i14 = i8 * i6;
        i15 = i13 - i11 >> 4;
        i16 = i14 - i12 >> 4;
        i4 = 16;
        while (i4-- > 0)
        {
          i6 = arrayOfInt1[arrayOfByte[((i12 >> 18 << 6) + (i11 >> 18) & 0xFFF)]];
          arrayOfInt4[(i1++)] = ((((i6 & 0xFF0000) >> 16) * i17 >> 8 << 16) + (((i6 & 0xFF00) >> 8) * i17 >> 8 << 8) + ((i6 & 0xFF) * i17 >> 8));
          i11 += i15;
          i12 += i16;
        }
        i3 -= 16;
        i11 = i13;
      }
      if (i3 > 0)
      {
        i6 = arrayOfInt2[i10];
        i4 = arrayOfInt3[i3];
        i15 = (int)(((paraml2.g + (int)((paraml3.g - paraml2.g) * i5 >> 16)) * i6 - i11) * i4 >> 16);
        i16 = (int)(((paraml2.i + (int)((paraml3.i - paraml2.i) * i5 >> 16)) * i6 - i12) * i4 >> 16);
        while (i3-- > 0)
        {
          i6 = arrayOfInt1[arrayOfByte[((i12 >> 18 << 6) + (i11 >> 18) & 0xFFF)]];
          arrayOfInt4[(i1++)] = ((((i6 & 0xFF0000) >> 16) * i17 >> 8 << 16) + (((i6 & 0xFF00) >> 8) * i17 >> 8 << 8) + ((i6 & 0xFF) * i17 >> 8));
          i11 += i15;
          i12 += i16;
        }
      }
    }
  }
  
  private static final void f(l paraml1, l paraml2, l paraml3, int paramInt1, int paramInt2, int paramInt3)
  {
    byte[] arrayOfByte = do[aY];
    int[] arrayOfInt1 = ca[aY];
    int[] arrayOfInt2 = aA;
    int[] arrayOfInt3 = ap;
    int[] arrayOfInt4 = az;
    int i17 = R;
    int i18 = arrayOfInt3[(paraml3.e - paraml1.e)];
    int i19 = arrayOfInt3[(paraml3.e - paraml2.e)];
    for (int i2 = paraml2.e; i2 < paraml3.e; i2++)
    {
      int i5 = (i2 - paraml1.e) * i18;
      int i6 = paraml1.d + (int)((paraml3.d - paraml1.d) * i5 >> 16);
      int i7 = paraml1.g + (int)((paraml3.g - paraml1.g) * i5 >> 16);
      int i8 = paraml1.i + (int)((paraml3.i - paraml1.i) * i5 >> 16);
      int i9 = paraml1.m + (int)((paraml3.m - paraml1.m) * i5 >> 16);
      i5 = (i2 - paraml2.e) * i19;
      int i10 = paraml2.m + (int)((paraml3.m - paraml2.m) * i5 >> 16);
      int i1 = i2 * 240 + i6;
      int i3 = paraml2.d + (int)((paraml3.d - paraml2.d) * i5 >> 16) - i6;
      i6 = arrayOfInt2[i9];
      int i11 = i7 * i6;
      int i14;
      int i15;
      int i16;
      int i4;
      for (int i12 = i8 * i6; i3 >= 16; i12 = i14)
      {
        i7 += paramInt1;
        i8 += paramInt2;
        i9 += paramInt3;
        i6 = arrayOfInt2[i9];
        int i13 = i7 * i6;
        i14 = i8 * i6;
        i15 = i13 - i11 >> 4;
        i16 = i14 - i12 >> 4;
        i4 = 16;
        while (i4-- > 0)
        {
          if ((i6 = arrayOfInt1[arrayOfByte[((i12 >> 18 << 6) + (i11 >> 18) & 0xFFF)]]) != 0) {
            arrayOfInt4[i1] = ((((i6 & 0xFF0000) >> 16) * i17 >> 8 << 16) + (((i6 & 0xFF00) >> 8) * i17 >> 8 << 8) + ((i6 & 0xFF) * i17 >> 8));
          }
          i1++;
          i11 += i15;
          i12 += i16;
        }
        i3 -= 16;
        i11 = i13;
      }
      if (i3 > 0)
      {
        i6 = arrayOfInt2[i10];
        i4 = arrayOfInt3[i3];
        i15 = (int)(((paraml2.g + (int)((paraml3.g - paraml2.g) * i5 >> 16)) * i6 - i11) * i4 >> 16);
        i16 = (int)(((paraml2.i + (int)((paraml3.i - paraml2.i) * i5 >> 16)) * i6 - i12) * i4 >> 16);
        while (i3-- > 0)
        {
          if ((i6 = arrayOfInt1[arrayOfByte[((i12 >> 18 << 6) + (i11 >> 18) & 0xFFF)]]) != 0) {
            arrayOfInt4[i1] = ((((i6 & 0xFF0000) >> 16) * i17 >> 8 << 16) + (((i6 & 0xFF00) >> 8) * i17 >> 8 << 8) + ((i6 & 0xFF) * i17 >> 8));
          }
          i1++;
          i11 += i15;
          i12 += i16;
        }
      }
    }
  }
  
  private static final void g(l paraml1, l paraml2, l paraml3, int paramInt1, int paramInt2, int paramInt3)
  {
    byte[] arrayOfByte = do[aY];
    int[] arrayOfInt1 = ca[aY];
    int[] arrayOfInt2 = aA;
    int[] arrayOfInt3 = ap;
    int[] arrayOfInt4 = az;
    int i1 = R;
    int i18 = arrayOfInt3[(paraml3.e - paraml2.e)];
    int i19 = arrayOfInt3[(paraml3.e - paraml1.e)];
    for (int i3 = paraml2.e; i3 < paraml3.e; i3++)
    {
      int i6 = (i3 - paraml2.e) * i18;
      int i7 = paraml2.d + (int)((paraml3.d - paraml2.d) * i6 >> 16);
      int i8 = paraml2.g + (int)((paraml3.g - paraml2.g) * i6 >> 16);
      int i9 = paraml2.i + (int)((paraml3.i - paraml2.i) * i6 >> 16);
      int i11 = paraml2.m + (int)((paraml3.m - paraml2.m) * i6 >> 16);
      i6 = (i3 - paraml1.e) * i19;
      int i10 = paraml1.m + (int)((paraml3.m - paraml1.m) * i6 >> 16);
      int i2 = i3 * 240 + i7;
      int i4 = paraml1.d + (int)((paraml3.d - paraml1.d) * i6 >> 16) - i7;
      i7 = arrayOfInt2[i11];
      int i12 = i8 * i7;
      int i15;
      int i16;
      int i17;
      int i5;
      for (int i13 = i9 * i7; i4 >= 16; i13 = i15)
      {
        i8 += paramInt1;
        i9 += paramInt2;
        i11 += paramInt3;
        i7 = arrayOfInt2[i11];
        int i14 = i8 * i7;
        i15 = i9 * i7;
        i16 = i14 - i12 >> 4;
        i17 = i15 - i13 >> 4;
        i5 = 16;
        while (i5-- > 0)
        {
          i7 = arrayOfInt1[arrayOfByte[((i13 >> 18 << 6) + (i12 >> 18) & 0xFFF)]];
          arrayOfInt4[(i2++)] = ((((i7 & 0xFF0000) >> 16) * i1 >> 8 << 16) + (((i7 & 0xFF00) >> 8) * i1 >> 8 << 8) + ((i7 & 0xFF) * i1 >> 8));
          i12 += i16;
          i13 += i17;
        }
        i4 -= 16;
        i12 = i14;
      }
      if (i4 > 0)
      {
        i7 = arrayOfInt2[i10];
        i5 = arrayOfInt3[i4];
        i16 = (int)(((paraml1.g + (int)((paraml3.g - paraml1.g) * i6 >> 16)) * i7 - i12) * i5 >> 16);
        i17 = (int)(((paraml1.i + (int)((paraml3.i - paraml1.i) * i6 >> 16)) * i7 - i13) * i5 >> 16);
        while (i4-- > 0)
        {
          i7 = arrayOfInt1[arrayOfByte[((i13 >> 18 << 6) + (i12 >> 18) & 0xFFF)]];
          arrayOfInt4[(i2++)] = ((((i7 & 0xFF0000) >> 16) * i1 >> 8 << 16) + (((i7 & 0xFF00) >> 8) * i1 >> 8 << 8) + ((i7 & 0xFF) * i1 >> 8));
          i12 += i16;
          i13 += i17;
        }
      }
    }
  }
  
  private static final void h(l paraml1, l paraml2, l paraml3, int paramInt1, int paramInt2, int paramInt3)
  {
    byte[] arrayOfByte = do[aY];
    int[] arrayOfInt1 = ca[aY];
    int[] arrayOfInt2 = aA;
    int[] arrayOfInt3 = ap;
    int[] arrayOfInt4 = az;
    int i1 = R;
    int i18 = arrayOfInt3[(paraml3.e - paraml2.e)];
    int i19 = arrayOfInt3[(paraml3.e - paraml1.e)];
    for (int i3 = paraml2.e; i3 < paraml3.e; i3++)
    {
      int i6 = (i3 - paraml2.e) * i18;
      int i7 = paraml2.d + (int)((paraml3.d - paraml2.d) * i6 >> 16);
      int i8 = paraml2.g + (int)((paraml3.g - paraml2.g) * i6 >> 16);
      int i9 = paraml2.i + (int)((paraml3.i - paraml2.i) * i6 >> 16);
      int i11 = paraml2.m + (int)((paraml3.m - paraml2.m) * i6 >> 16);
      i6 = (i3 - paraml1.e) * i19;
      int i10 = paraml1.m + (int)((paraml3.m - paraml1.m) * i6 >> 16);
      int i2 = i3 * 240 + i7;
      int i4 = paraml1.d + (int)((paraml3.d - paraml1.d) * i6 >> 16) - i7;
      i7 = arrayOfInt2[i11];
      int i12 = i8 * i7;
      int i15;
      int i16;
      int i17;
      int i5;
      for (int i13 = i9 * i7; i4 >= 16; i13 = i15)
      {
        i8 += paramInt1;
        i9 += paramInt2;
        i11 += paramInt3;
        i7 = arrayOfInt2[i11];
        int i14 = i8 * i7;
        i15 = i9 * i7;
        i16 = i14 - i12 >> 4;
        i17 = i15 - i13 >> 4;
        i5 = 16;
        while (i5-- > 0)
        {
          if ((i7 = arrayOfInt1[arrayOfByte[((i13 >> 18 << 6) + (i12 >> 18) & 0xFFF)]]) != 0) {
            arrayOfInt4[i2] = ((((i7 & 0xFF0000) >> 16) * i1 >> 8 << 16) + (((i7 & 0xFF00) >> 8) * i1 >> 8 << 8) + ((i7 & 0xFF) * i1 >> 8));
          }
          i2++;
          i12 += i16;
          i13 += i17;
        }
        i4 -= 16;
        i12 = i14;
      }
      if (i4 > 0)
      {
        i7 = arrayOfInt2[i10];
        i5 = arrayOfInt3[i4];
        i16 = (int)(((paraml1.g + (int)((paraml3.g - paraml1.g) * i6 >> 16)) * i7 - i12) * i5 >> 16);
        i17 = (int)(((paraml1.i + (int)((paraml3.i - paraml1.i) * i6 >> 16)) * i7 - i13) * i5 >> 16);
        while (i4-- > 0)
        {
          if ((i7 = arrayOfInt1[arrayOfByte[((i13 >> 18 << 6) + (i12 >> 18) & 0xFFF)]]) != 0) {
            arrayOfInt4[i2] = ((((i7 & 0xFF0000) >> 16) * i1 >> 8 << 16) + (((i7 & 0xFF00) >> 8) * i1 >> 8 << 8) + ((i7 & 0xFF) * i1 >> 8));
          }
          i2++;
          i12 += i16;
          i13 += i17;
        }
      }
    }
  }
  
  static final void g()
  {
    if (dx) {
      try
      {
        p.d();
        return;
      }
      catch (Exception localException) {}
    }
  }
  
  private static final void b(l paraml)
  {
    int[] arrayOfInt1 = cU;
    int[] arrayOfInt2 = aq;
    int[] arrayOfInt3 = cF;
    paraml.a = ((int)((arrayOfInt3[0] - paraml.j) * arrayOfInt2[cE] - (arrayOfInt3[1] - paraml.k) * arrayOfInt1[cE] >> 16));
    paraml.b = ((int)((arrayOfInt3[0] - paraml.j) * arrayOfInt1[cE] + (arrayOfInt3[1] - paraml.k) * arrayOfInt2[cE] >> 16));
    paraml.c = ((int)((arrayOfInt3[2] - paraml.l) * arrayOfInt2[cC] - paraml.b * arrayOfInt1[cC] >> 16));
    paraml.b = ((int)((arrayOfInt3[2] - paraml.l) * arrayOfInt1[cC] + paraml.b * arrayOfInt2[cC] >> 16));
  }
  
  private static final void b(int[] paramArrayOfInt, int paramInt)
  {
    int[] arrayOfInt;
    int i1 = (arrayOfInt = cF)[0];
    int i2 = arrayOfInt[1];
    int i3 = arrayOfInt[2];
    int i4 = aq[cE];
    int i5 = cU[cE];
    int i6 = aq[cC];
    int i7 = cU[cC];
    do
    {
      int i8 = paramInt * 6;
      int i9 = i2 - paramArrayOfInt[(i8 + 1)];
      int i10 = i1 - paramArrayOfInt[i8];
      paramArrayOfInt[(i8 + 3)] = ((int)(i10 * i4 - i9 * i5 >> 16));
      paramArrayOfInt[(i8 + 4)] = ((int)(i10 * i5 + i9 * i4 >> 16));
      i9 = i3 - paramArrayOfInt[(i8 + 2)];
      i10 = paramArrayOfInt[(i8 + 4)];
      paramArrayOfInt[(i8 + 5)] = ((int)(i9 * i6 - i10 * i7 >> 16));
      paramArrayOfInt[(i8 + 4)] = ((int)(i9 * i7 + i10 * i6 >> 16));
      paramInt--;
    } while (paramInt >= 0);
  }
}


/* Location:              C:\Users\Administrator\Desktop\3d_army_ranger.jar!\k.class
 * Java compiler version: 4 (48.0)
 * JD-Core Version:       0.7.1
 */