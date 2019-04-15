import java.util.Random;
import javax.microedition.lcdui.Display;
import javax.microedition.lcdui.Graphics;
import javax.microedition.lcdui.Image;

public final class h
  extends a
  implements Runnable
{
  static final int[] a;
  static int b;
  short c;
  int d;
  static final int[] e;
  final short[] f;
  private static final int[][] ej;
  static l[] g;
  static g[] h;
  boolean i;
  static b[] j;
  static short k;
  static f[] l;
  String m;
  static j[] n;
  short o;
  static final int[] p;
  static final int[] q;
  static final int[] r;
  static final int[] s;
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
  static final int[] Q;
  static final int[] R;
  static final int[] S;
  static final int[] T;
  static final int[] U;
  static final int[] V;
  static final int[] W;
  static final int[] X;
  static final int[] Y;
  static final int[] Z;
  static final int[] aa;
  static final int[] ab;
  static final int[] ac;
  final int[] ad;
  static int ae;
  static byte af;
  byte ag;
  static final byte[][] ah;
  static byte[] ai;
  static byte[] aj;
  String ak = "Company NET Lizard LTD www.NetLizard.net =) +) :) It is just a game! Life is good!";
  static byte[] al;
  int am;
  static byte an;
  static byte[][] ao;
  static byte ap;
  String aq;
  boolean ar;
  static boolean as;
  static boolean at;
  static boolean au;
  boolean av;
  boolean aw;
  static short[][] ax;
  int ay;
  static int[] az;
  static final int[] aA;
  static short[][] aB;
  static short[][] aC;
  static short[][] aD;
  long aE;
  boolean aF;
  static int aG;
  String[][] aH;
  static boolean aI;
  static byte aJ;
  static byte aK;
  int aL;
  static byte aM = 0;
  static int[] aN;
  static int[] aO;
  static int aP;
  static int[] aQ;
  int aR;
  int aS;
  long aT;
  static byte aU;
  int aV;
  int aW;
  int aX;
  int aY;
  boolean aZ;
  boolean ba;
  static d bb;
  boolean bc;
  static byte bd;
  static boolean be;
  static boolean bf;
  boolean bg;
  boolean bh;
  c bi;
  static byte bj;
  String[] bk;
  static i[] bl;
  byte bm;
  static byte bn;
  static int[] bo;
  static int[] bp;
  String[][] bq;
  static i[] br;
  static final byte[] bs;
  static byte bt;
  int bu;
  static short bv;
  Image bw;
  static int bx;
  static int[] by;
  static int[] bz;
  static d bA;
  int bB;
  boolean bC;
  boolean bD;
  int bE;
  static byte bF;
  boolean bG;
  boolean bH;
  int bI;
  static int bJ;
  static byte bK;
  byte bL;
  static int bM;
  String bN;
  boolean bO;
  byte bP;
  Image bQ;
  static final int[] bR;
  static boolean[] bS;
  String[] bT;
  static boolean[] bU;
  static boolean[] bV;
  byte bW;
  static byte[] bX;
  static byte[] bY;
  final int[] bZ;
  static final int ca;
  static final int[] cb;
  boolean cc;
  k cd;
  static boolean ce;
  int cf;
  byte cg;
  int ch;
  final byte[] ci;
  static int cj;
  static byte[][] ck;
  private static Random ek = new Random();
  byte cl = 2;
  String[] cm;
  static byte cn;
  int co;
  static String cp;
  byte cq;
  byte cr;
  byte cs;
  byte ct;
  Image cu;
  String[] cv;
  Image[] cw;
  Image[] cx;
  Image[] cy;
  static short cz;
  static int cA;
  static int cB;
  static int cC;
  static byte cD;
  private static final int[] el;
  Image cE;
  long cF;
  static int[][] cG;
  static int[] cH;
  static int[] cI;
  static int[][] cJ;
  String[] cK;
  static final int[][] cL;
  static int cM;
  static final int[] cN;
  byte cO;
  static boolean cP;
  static final byte[] cQ;
  static int cR;
  static int cS;
  static int cT;
  static int cU;
  static short cV;
  static final byte[] cW = { 9, 8, 5 };
  static final byte[] cX;
  static int cY;
  static int cZ;
  static int da;
  static int db;
  static int dc;
  static int dd;
  static int de;
  static int df;
  static int[] dg;
  byte dh;
  byte di;
  boolean dj;
  static int[][] dk;
  static short dl;
  static int dm;
  static final int[] dn;
  String[] jdField_do;
  boolean dp;
  int dq;
  boolean dr;
  int ds;
  static byte[] dt;
  int du;
  static byte[] dv;
  static byte dw;
  static boolean dx;
  static final int[] dy;
  static short dz;
  static int[][] dA;
  static int dB;
  byte dC;
  static boolean dD;
  byte dE;
  int dF;
  int dG;
  static d dH;
  int dI;
  static boolean dJ = false;
  static byte dK;
  static byte[][] dL;
  static byte[][] dM;
  static byte[] dN;
  static byte[][] dO;
  Thread dP;
  static boolean dQ;
  static int dR;
  static int[] dS;
  static boolean dT;
  boolean dU;
  boolean dV;
  static boolean dW;
  static byte dX;
  static byte dY;
  static byte dZ;
  short ea;
  short eb;
  final byte[][] ec;
  static final short[] ed;
  static final short[] ee;
  final short[][] ef;
  static byte eg;
  static short eh;
  byte ei;
  
  static
  {
    aI = false;
    au = false;
    at = false;
    as = false;
    bR = new int[] { 1296389185, 759778886, 793592142, 1229342035, 1412320582 };
    dy = new int[] { 1399874915, 1768319331, 1635019119, 1845493760 };
    e = new int[] { 1296647248, 758263344 };
    a = new int[] { 1684368640 };
    new int[1][0] = 1819934720;
    p = new int[] { 795881072, 1852243968 };
    z = new int[] { 795832878, 1886283520 };
    I = new int[] { 795638318, 1886283520 };
    T = new int[] { 795438128, 779120231 };
    Y = new int[] { 1819700224 };
    Z = new int[] { 795632686, 1886283520 };
    aa = new int[] { 795765806, 1886283520 };
    ab = new int[] { 1868720687, 1868720640 };
    ac = new int[] { 1668481024 };
    q = new int[] { 1668612096 };
    r = new int[] { 1668642048 };
    s = new int[] { 1667432448 };
    t = new int[] { 1836409088 };
    u = new int[] { 1668087808 };
    v = new int[] { 1946157056 };
    w = new int[] { 1949433856 };
    x = new int[] { 1949368320 };
    y = new int[] { 1949892608 };
    A = new int[] { 587202560 };
    new int[1][0] = 1919746048;
    B = new int[] { 1399353202, 1949126261, 1835165042 };
    C = new int[] { 1131373669 };
    D = new int[] { 1348565357, 1701737517, 1415936116 };
    E = new int[] { 1197567333, 754974720 };
    F = new int[] { 1852798035, 1297285120 };
    G = new int[] { 1949630464 };
    H = new int[] { 1949564928 };
    J = new int[] { 1949761536 };
    K = new int[] { 796355840 };
    L = new int[] { 779120231 };
    M = new int[] { 795672576 };
    N = new int[] { 1399420005, 1431456768 };
    O = new int[] { 1296647276, 1702112585, 1852206893, 1431456768 };
    P = new int[] { 796093305, 1596981248 };
    Q = new int[] { 1952806959, 1811939328 };
    R = new int[] { 796209152 };
    S = new int[] { 796196864 };
    U = new int[] { 795029104, 1852243968 };
    V = new int[] { 795029809, 779120231 };
    W = new int[] { 795017216 };
    X = new int[] { 1784772193, 2016311145, 1919249509, 1936928365, 1702064993, 1734962791, 776824179, 1935763301 };
    new int[] { 1668246830, 1935764851, 1970169646, 1970563436 }[4] = 777211219;
    new int[] { 1668246830, 1936287085, 1701737262, 1836068455, 1936535123 }[5] = 1297285120;
    bM = 256;
    cp = "rm";
    bf = false;
    aJ = 0;
    aK = 3;
    bK = 0;
    ce = true;
    cD = 1;
    cn = 0;
    dT = true;
    dx = true;
    an = 0;
    bs = new byte[] { 30, 30 };
    bJ = 9;
    el = new int[] { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 1, 2, 3, 4, 0, 1, 2, 3, 4, 1, 2, 3, 4, 5, 0, 1, 2, 3, 1, 2, 3, 4, 5, 6, 0, 1, 2, 1, 2, 3, 4, 5, 6, 7, 0, 1, 1, 2, 3, 4, 5, 6, 7, 8, 0 };
    aA = new int[] { 65536, 65526, 65496, 65446, 65376, 65287, 65177, 65048, 64898, 64729, 64540, 64332, 64104, 63856, 63589, 63303, 62997, 62672, 62328, 61966, 61584, 61183, 60764, 60326, 59870, 59396, 58903, 58393, 57865, 57319, 56756, 56175, 55578, 54963, 54332, 53684, 53020, 52339, 51643, 50931, 50203, 49461, 48703, 47930, 47143, 46341, 45525, 44695, 43852, 42995, 42126, 41243, 40348, 39441, 38521, 37590, 36647, 35693, 34729, 33754, 32768, 31772, 30767, 29753, 28729, 27697, 26656, 25607, 24550, 23486, 22415, 21336, 20252, 19161, 18064, 16962, 15855, 14742, 13626, 12505, 11380, 10252, 9121, 7987, 6850, 5712, 4572, 3430, 2287, 1144, 0, 64392, 63249, 62106, 60964, 59824, 58686, 57549, 56415, 55284, 54156, 53031, 51910, 50794, 49681, 48574, 47472, 46375, 45284, 44200, 43121, 42050, 40986, 39929, 38880, 37839, 36807, 35783, 34769, 33764, 32768, -33754, -34729, -35693, -36647, -37590, -38521, -39441, -40348, -41243, -42126, -42995, -43852, -44695, -45525, -46341, -47143, -47930, -48703, -49461, -50203, -50931, -51643, -52339, -53020, -53684, -54332, -54963, -55578, -56175, -56756, -57319, -57865, -58393, -58903, -59396, -59870, -60326, -60764, -61183, -61584, -61966, -62328, -62672, -62997, -63303, -63589, -63856, -64104, -64332, -64540, -64729, -64898, -65048, -65177, -65287, -65376, -65446, -65496, -65526, -65536, -65526, -65496, -65446, -65376, -65287, -65177, -65048, -64898, -64729, -64540, -64332, -64104, -63856, -63589, -63303, -62997, -62672, -62328, -61966, -61584, -61183, -60764, -60326, -59870, -59396, -58903, -58393, -57865, -57319, -56756, -56175, -55578, -54963, -54332, -53684, -53020, -52339, -51643, -50931, -50203, -49461, -48703, -47930, -47143, -46341, -45525, -44695, -43852, -42995, -42126, -41243, -40348, -39441, -38521, -37590, -36647, -35693, -34729, -33754, 32768, 33764, 34769, 35783, 36807, 37839, 38880, 39929, 40986, 42050, 43121, 44200, 45284, 46375, 47472, 48574, 49681, 50794, 51910, 53031, 54156, 55284, 56415, 57549, 58686, 59824, 60964, 62106, 63249, 64392, 0, 1144, 2287, 3430, 4572, 5712, 6850, 7987, 9121, 10252, 11380, 12505, 13626, 14742, 15855, 16962, 18064, 19161, 20252, 21336, 22415, 23486, 24550, 25607, 26656, 27697, 28729, 29753, 30767, 31772, 32768, 33754, 34729, 35693, 36647, 37590, 38521, 39441, 40348, 41243, 42126, 42995, 43852, 44695, 45525, 46341, 47143, 47930, 48703, 49461, 50203, 50931, 51643, 52339, 53020, 53684, 54332, 54963, 55578, 56175, 56756, 57319, 57865, 58393, 58903, 59396, 59870, 60326, 60764, 61183, 61584, 61966, 62328, 62672, 62997, 63303, 63589, 63856, 64104, 64332, 64540, 64729, 64898, 65048, 65177, 65287, 65376, 65446, 65496, 65526 };
    dn = new int[] { 0, 1144, 2287, 3430, 4572, 5712, 6850, 7987, 9121, 10252, 11380, 12505, 13626, 14742, 15855, 16962, 18064, 19161, 20252, 21336, 22415, 23486, 24550, 25607, 26656, 27697, 28729, 29753, 30767, 31772, 32768, 33754, 34729, 35693, 36647, 37590, 38521, 39441, 40348, 41243, 42126, 42995, 43852, 44695, 45525, 46341, 47143, 47930, 48703, 49461, 50203, 50931, 51643, 52339, 53020, 53684, 54332, 54963, 55578, 56175, 56756, 57319, 57865, 58393, 58903, 59396, 59870, 60326, 60764, 61183, 61584, 61966, 62328, 62672, 62997, 63303, 63589, 63856, 64104, 64332, 64540, 64729, 64898, 65048, 65177, 65287, 65376, 65446, 65496, 65526, 65536, 65526, 65496, 65446, 65376, 65287, 65177, 65048, 64898, 64729, 64540, 64332, 64104, 63856, 63589, 63303, 62997, 62672, 62328, 61966, 61584, 61183, 60764, 60326, 59870, 59396, 58903, 58393, 57865, 57319, 56756, 56175, 55578, 54963, 54332, 53684, 53020, 52339, 51643, 50931, 50203, 49461, 48703, 47930, 47143, 46341, 45525, 44695, 43852, 42995, 42126, 41243, 40348, 39441, 38521, 37590, 36647, 35693, 34729, 33754, 32768, 31772, 30767, 29753, 28729, 27697, 26656, 25607, 24550, 23486, 22415, 21336, 20252, 19161, 18064, 16962, 15855, 14742, 13626, 12505, 11380, 10252, 9121, 7987, 6850, 5712, 4572, 3430, 2287, 1144, 0, 64392, 63249, 62106, 60964, 59824, 58686, 57549, 56415, 55284, 54156, 53031, 51910, 50794, 49681, 48574, 47472, 46375, 45284, 44200, 43121, 42050, 40986, 39929, 38880, 37839, 36807, 35783, 34769, 33764, 32768, -33754, -34729, -35693, -36647, -37590, -38521, -39441, -40348, -41243, -42126, -42995, -43852, -44695, -45525, -46341, -47143, -47930, -48703, -49461, -50203, -50931, -51643, -52339, -53020, -53684, -54332, -54963, -55578, -56175, -56756, -57319, -57865, -58393, -58903, -59396, -59870, -60326, -60764, -61183, -61584, -61966, -62328, -62672, -62997, -63303, -63589, -63856, -64104, -64332, -64540, -64729, -64898, -65048, -65177, -65287, -65376, -65446, -65496, -65526, -65536, -65526, -65496, -65446, -65376, -65287, -65177, -65048, -64898, -64729, -64540, -64332, -64104, -63856, -63589, -63303, -62997, -62672, -62328, -61966, -61584, -61183, -60764, -60326, -59870, -59396, -58903, -58393, -57865, -57319, -56756, -56175, -55578, -54963, -54332, -53684, -53020, -52339, -51643, -50931, -50203, -49461, -48703, -47930, -47143, -46341, -45525, -44695, -43852, -42995, -42126, -41243, -40348, -39441, -38521, -37590, -36647, -35693, -34729, -33754, 32768, 33764, 34769, 35783, 36807, 37839, 38880, 39929, 40986, 42050, 43121, 44200, 45284, 46375, 47472, 48574, 49681, 50794, 51910, 53031, 54156, 55284, 56415, 57549, 58686, 59824, 60964, 62106, 63249, 64392 };
    cY = 0;
    b = 0;
    da = 0;
    db = 0;
    dc = 0;
    dd = 270;
    de = 270;
    df = 250;
    dW = false;
    dX = 16;
    dY = 0;
    dZ = 4;
    cB = 240;
    cC = cB << 16;
    ca = 3 * cB - 240;
    dg = new int[3];
    cN = new int[] { 130, 131, 120, 121 };
    cL = new int[][] { { 0, 0, cB }, { 0, -cB, 130 }, { 0, cB, 131 }, { cB, 0, 120 }, { -cB, 0, 121 } };
    cj = 10000;
    cU = 0;
    cT = 0;
    aP = 0;
    eh = 0;
    ap = 0;
    dw = 0;
    dv = new byte[] { -1, -1, -1, -1, -1 };
    dt = new byte[] { 0, 2, 0, 4 };
    ee = new short[] { 130, 2000, 2500, 3000, 1700, 2700, 3200, 3500, 4000 };
    cQ = new byte[] { 2, 4, 7, 7, 1, 4, 5, 10, 15, 12, 10 };
    cX = new byte[] { 5, 2, 5, 4, 1, 2, 3, 10, 15, 12, 10 };
    ai = new byte[] { -1, 20, 30, 10 };
    aj = new byte[] { -1, 20, 30, 0 };
    ah = new byte[][] { { -1, 12, 6, 7, 30, 30, 30, 10, 10, 3, 3 }, { -1, 36, 36, 21, 60, 60, 60, 20, 30, 0, 0 } };
    bX = new byte[] { 0, 20, 30, 30 };
    bY = new byte[] { 0, 40, 60, 60 };
    ed = new short[] { 100, 40, 80, 120, 40, 60, 90, 140, 400, 1, 1 };
    eg = 1;
    aU = 0;
    cb = new int[] { 20, 40, 200 };
    ao = new byte[][] { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 }, { 0, 0, 0, 0 } };
    bn = 0;
    dD = false;
    ej = new int[][] { { 3, 3, 2, 2, 1, 1 }, { 6, 5, 4 }, { 8, 8 }, { 7, 7 }, { 9, 9 }, { 7, 7 } };
    cM = 0;
    dA = new int[20][6];
    dB = 0;
    dm = 0;
    dS = new int[3];
    bv = 0;
    k = 1;
    dH = new d(null);
    bb = new d(null);
    bA = new d(null);
    bj = 0;
    dQ = false;
    aG = 0;
    cR = 0;
    cS = 0;
  }
  
  public h()
  {
    new int[1][0] = 1949696000;
    new int[1][0] = 1949827072;
    this.cg = 15;
    this.bO = false;
    this.bP = 0;
    this.dE = 0;
    this.dI = 1300;
    this.bL = 0;
    this.bc = false;
    this.i = true;
    this.ba = false;
    this.dC = 0;
    this.dV = false;
    this.dU = false;
    this.aw = true;
    this.cf = -1;
    this.aT = 0L;
    this.aE = 0L;
    this.bh = true;
    this.dj = false;
    this.bI = 1;
    this.cK = new String[] { e.a(B), e.a(C), e.a(D) };
    this.bk = new String[this.cK.length];
    this.aZ = false;
    this.aX = 3;
    this.aV = 236;
    this.aL = (310 - this.aX);
    this.aW = (240 - this.aV >> 1);
    this.aY = (320 - this.aL >> 1);
    this.bu = 0;
    this.aS = 2;
    this.aR = 0;
    this.dF = 77;
    this.d = 35;
    this.bD = false;
    this.bC = false;
    this.bE = 0;
    this.av = false;
    this.ar = false;
    this.aq = "";
    this.bG = true;
    this.bH = false;
    this.cr = 0;
    this.cs = 0;
    this.ct = 0;
    this.cq = 0;
    this.di = 1;
    this.dh = 1;
    this.ec = new byte[][] { { 0, 1, 2 }, { 3, 4, 5, 6, 7 }, { 8, 9 } };
    this.ef = new short[][] { { 500, 700, 1000 }, { 1300, 2000, 3000, 7500, 12500 }, { 200, 150 } };
    this.ay = 7;
    this.bB = 0;
    this.bW = 2;
    this.eb = 240;
    this.ea = 122;
    this.bm = 0;
    this.ds = 0;
    this.dq = 0;
    new d(null);
    new d(null);
    new d(null);
    this.ei = 0;
    this.f = new short[] { 22, 16, 8 };
    this.ad = new int[] { 25, 19, 10 };
    this.ci = new byte[] { 10, 5, 4 };
    this.bZ = new int[] { 1440000, 4000000, 9000000 };
    this.dp = false;
    this.dG = 0;
    this.ch = 0;
    this.du = 0;
    this.bg = true;
    this.am = 0;
    this.dP = new Thread(this);
  }
  
  private final void a(j paramj)
  {
    switch (paramj.C)
    {
    case 0: 
      
    case 1: 
    case 2: 
    case 3: 
      c(paramj);
    case 4: 
    case 5: 
      b(paramj);
    }
  }
  
  private static boolean a(j paramj, int paramInt1, int paramInt2, int paramInt3, int paramInt4)
  {
    int i1 = paramj.p - paramInt1 >> 16;
    int i2 = paramj.q - paramInt2 >> 16;
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
    paramj.u[0] = i4;
    paramj.u[1] = i5;
    if (i6 > paramInt3)
    {
      paramj.d[0] = i4;
      paramj.d[1] = i5;
      return true;
    }
    if (i6 < paramInt4)
    {
      paramj.d[0] = (-i4);
      paramj.d[1] = (-i5);
      return true;
    }
    return false;
  }
  
  private final void b(j paramj)
  {
    if (paramj.x)
    {
      if (a(paramj, dg[0], dg[1], 300, 200))
      {
        paramj.B = 1;
        return;
      }
      paramj.B = 0;
    }
  }
  
  private final void c(j paramj)
  {
    f localf = l[paramj.t];
    j localj = n[0];
    if (paramj.e > 0)
    {
      paramj.B = 0;
      j tmp29_28 = paramj;
      tmp29_28.e = ((short)(tmp29_28.e - 1));
      return;
    }
    if (paramj.w < 0)
    {
      j tmp48_47 = paramj;
      tmp48_47.w = ((short)(tmp48_47.w + 1));
      paramj.v = 1;
      paramj.B = 0;
      if (a(paramj, paramj.z, paramj.A, 200, 0))
      {
        paramj.B = 1;
        return;
      }
      paramj.w = 0;
    }
    j tmp99_98 = paramj;
    if ((tmp99_98.g = (short)(tmp99_98.g - 1)) <= 0)
    {
      if ((a(paramj, localj)) && (!localj.k) && (b(paramj, localj)))
      {
        a(paramj, localj.p, localj.q, 25000, 0);
        paramj.B = 0;
        c(paramj, localj.p, localj.q, localj.r, (short)this.ad[aM]);
        h(paramj);
        if (!paramj.o)
        {
          j tmp204_203 = paramj;
          tmp204_203.w = ((short)(tmp204_203.w + 1));
          if (paramj.w >= this.ci[aM]) {
            paramj.w = ((short)-(10 + g(15)));
          }
        }
        paramj.o = false;
        if (paramj.l == 0)
        {
          paramj.v = 0;
          paramj.l = ((short)(300 + g(100)));
        }
        paramj.z = localj.p;
        paramj.A = localj.q;
        paramj.g = 0;
        return;
      }
      paramj.g = this.f[aM];
    }
    if (paramj.l > 0)
    {
      j tmp318_317 = paramj;
      tmp318_317.l = ((short)(tmp318_317.l - 1));
      paramj.B = 0;
      if (a(paramj, paramj.z, paramj.A, 45, 0)) {
        paramj.B = 1;
      }
      return;
    }
    paramj.v = 0;
    j tmp363_362 = paramj;
    i[] arrayOfi;
    b localb;
    if ((tmp363_362.y = (short)(tmp363_362.y - 1)) <= 0) {
      switch (paramj.a)
      {
      case 0: 
        paramj.a = 1;
        paramj.y = ((short)(g(100) + 25));
        paramj.b = ((short)g(localf.q));
        paramj.c = paramj.t;
        arrayOfi = j[localf.p[paramj.b]].b;
        paramj.z = (arrayOfi[0].j + arrayOfi[1].j + arrayOfi[2].j + arrayOfi[3].j >> 2);
        paramj.A = (arrayOfi[0].k + arrayOfi[1].k + arrayOfi[2].k + arrayOfi[3].k >> 2);
        paramj.B = 1;
        break;
      case 1: 
        paramj.a = 0;
        paramj.y = ((short)(g(100) + 25));
        if (((localb = j[localf.p[paramj.b]]).d != 999) && (localb.c != 999)) {
          if (localb.c == paramj.t) {
            localf = l[localb.d];
          } else {
            localf = l[localb.c];
          }
        }
        paramj.z = localf.c;
        paramj.A = localf.d;
        break;
      case 2: 
        paramj.a = 0;
      }
    }
    if (paramj.a == 2) {
      return;
    }
    if (!a(paramj, paramj.z, paramj.A, 45, 0)) {
      switch (paramj.a)
      {
      case 0: 
        if (g(3) == 2)
        {
          paramj.a = 2;
          paramj.B = 0;
          return;
        }
        paramj.a = 1;
        paramj.y = ((short)(g(100) + 25));
        paramj.b = ((short)g(localf.q));
        paramj.c = paramj.t;
        arrayOfi = j[localf.p[paramj.b]].b;
        paramj.z = (arrayOfi[0].j + arrayOfi[1].j + arrayOfi[2].j + arrayOfi[3].j >> 2);
        paramj.A = (arrayOfi[0].k + arrayOfi[1].k + arrayOfi[2].k + arrayOfi[3].k >> 2);
        paramj.B = 1;
        return;
      case 1: 
        paramj.a = 0;
        paramj.y = ((short)(g(100) + 25));
        if (((localb = j[localf.p[paramj.b]]).d != 999) && (localb.c != 999)) {
          if (localb.c == paramj.c) {
            localf = l[localb.d];
          } else {
            localf = l[localb.c];
          }
        }
        paramj.z = localf.c;
        paramj.A = localf.d;
      }
    }
  }
  
  private static final void a(int paramInt1, int paramInt2, int paramInt3, byte paramByte, short paramShort)
  {
    if (dB >= 20) {
      return;
    }
    int[][] arrayOfInt = dA;
    int i1 = 0;
    dB += 1;
    for (;;)
    {
      if (arrayOfInt[i1][4] < 1)
      {
        arrayOfInt[i1][0] = paramInt1;
        arrayOfInt[i1][1] = paramInt2;
        arrayOfInt[i1][2] = paramInt3;
        arrayOfInt[i1][3] = paramByte;
        arrayOfInt[i1][4] = (ej[paramByte].length + 1);
        arrayOfInt[i1][5] = paramShort;
        return;
      }
      i1++;
    }
  }
  
  private static final void a(int paramInt1, int paramInt2, int paramInt3, int paramInt4)
  {
    j[] arrayOfj = n;
    for (int i4 = dR - 1; i4 >= 0; i4--)
    {
      j localj;
      if ((!(localj = arrayOfj[i4]).k) && (b(localj, paramInt1, paramInt2, paramInt3, paramInt4))) {
        if (i4 == 0)
        {
          int i1 = localj.p - paramInt1 >> 16;
          int i2 = localj.q - paramInt2 >> 16;
          int i3 = localj.r - paramInt3 >> 16;
          localj.e = ((short)(2900 - (Math.abs(i1) + Math.abs(i2) + Math.abs(i3))));
          if (localj.e > 320) {
            localj.e = 320;
          }
          if (i1 * dn[df] + i2 * aA[df] < 0L)
          {
            j tmp163_161 = localj;
            tmp163_161.e = ((short)(tmp163_161.e >> 1));
          }
          if (localj.e < 0) {
            localj.e = 0;
          }
        }
        else
        {
          localj.e = 120;
        }
      }
    }
  }
  
  private static final void e(int paramInt)
  {
    cB = 240 + paramInt;
    cL[0][2] = cB;
    cL[1][1] = (-cB);
    cL[2][1] = cB;
    cL[3][0] = cB;
    cL[4][0] = (-cB);
    cC = cB << 16;
  }
  
  private final void m()
  {
    j localj = n[0];
    j[] arrayOfj = n;
    int i1 = 102400;
    if (cn == 2)
    {
      localj = n[this.ei];
      i1 = 307200;
    }
    int i2 = 0;
    int i3 = 0;
    int i4 = 0;
    for (int i5 = cA - 1; i5 >= 0; i5--)
    {
      g localg;
      if ((localg = h[i5]).t)
      {
        if ((localg.s == 23) && (localg.l < 0))
        {
          i2 = localj.p - localg.m >> 16;
          i3 = localj.q - localg.n >> 16;
          i4 = localj.r - localg.o >> 16;
          if (i2 * i2 + i3 * i3 + i4 * i4 < 102400)
          {
            localg.l = 10;
            if (dt[3] != 0)
            {
              int tmp176_175 = 3;
              byte[] tmp176_172 = ai;
              tmp176_172[tmp176_175] = ((byte)(tmp176_172[tmp176_175] + 3));
              this.du = 3;
              this.ch = 20;
            }
          }
        }
        if ((localg.s > 51) && (localg.s < 56)) {
          if (cn == 2)
          {
            i2 = localj.p - localg.m >> 16;
            i3 = localj.q - localg.n >> 16;
            if (i2 * i2 + i3 * i3 < i1)
            {
              localg.l = 25;
              if (localg.l != 25) {
                d(6);
              }
            }
          }
          else
          {
            for (int i6 = 0; i6 < dR; i6++) {
              if (!arrayOfj[i6].k)
              {
                i2 = arrayOfj[i6].p - localg.m >> 16;
                i3 = arrayOfj[i6].q - localg.n >> 16;
                if (i2 * i2 + i3 * i3 < i1)
                {
                  localg.l = 25;
                  if ((localg.l != 25) && (i6 == 0)) {
                    d(6);
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  
  private static final void a(j paramj, boolean paramBoolean, d paramd)
  {
    if (paramBoolean)
    {
      p();
      if (!au)
      {
        paramj.m = ((short)(paramj.m - 1));
        paramj.m = ((short)(paramj.m - ((Math.abs(paramd.a - paramj.p) + Math.abs(paramd.b - paramj.q) >> 16 >> 2 & 0xF) + 3)));
      }
    }
    if (!paramBoolean)
    {
      if ((paramj.C > 3) && (Math.abs(paramd.c - (paramj.r + 8192000)) < 8355840)) {
        paramj.m = ((short)(paramj.m - 100));
      }
      if (Math.abs(paramd.c - (paramj.r + 8192000)) < 5570560)
      {
        paramj.m = ((short)(paramj.m - 100));
      }
      else
      {
        int i1 = Math.abs(paramd.a - paramj.p) + Math.abs(paramd.b - paramj.q) >> 16 >> 1 & 0x3F;
        if (paramj.C > 3) {
          paramj.m = ((short)(paramj.m - (ed[eg] * i1 >> 6 << 2)));
        } else {
          paramj.m = ((short)(paramj.m - (ed[eg] * i1 >> 6)));
        }
      }
    }
    if (paramj.m <= 0)
    {
      paramj.k = true;
      paramj.x = false;
      paramj.m = 0;
      if (!paramBoolean)
      {
        paramj.B = 6;
        paramj.i = ((short)(byte)((ck[paramj.C][((paramj.B << 1) + 1)] << 1) - 1));
        if (paramj.i <= 0) {
          paramj.i = 0;
        }
        return;
      }
      d(4);
    }
  }
  
  private static final void a(int paramInt1, int paramInt2, int paramInt3)
  {
    d(7);
    j[] arrayOfj = n;
    for (int i5 = dR - 1; i5 >= 0; i5--)
    {
      j localj;
      if (!(localj = arrayOfj[i5]).k)
      {
        int i2 = localj.p - paramInt1 >> 16;
        int i3 = localj.q - paramInt2 >> 16;
        int i4 = localj.r - paramInt3 >> 16;
        int i1 = i2 * i2 + i3 * i3 + i4 * i4;
        if (i5 == 0)
        {
          f(Math.abs(i2) + Math.abs(i3) + Math.abs(i4));
          if (au) {}
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
          if ((localj.C == 4) || (localj.C == 5))
          {
            j tmp196_194 = localj;
            tmp196_194.m = ((short)(tmp196_194.m - (895 - i6 >> 2 << 1)));
          }
          else
          {
            j tmp220_218 = localj;
            tmp220_218.m = ((short)(tmp220_218.m - (895 - i6 >> 2)));
          }
          if (i5 == 0) {
            p();
          }
          if (localj.m <= 0)
          {
            localj.m = 0;
            localj.k = true;
            if (i5 != 0)
            {
              localj.B = 6;
              localj.i = ((short)(byte)((ck[localj.C][((localj.B << 1) + 1)] << 1) - 1));
              if (localj.i <= 0) {
                localj.i = 0;
              }
            }
            else
            {
              d(4);
            }
          }
          else if (i6 != 0)
          {
            i1 = i6;
            if (i6 > 160) {
              i1 = 160;
            }
            localj.h[0] += i2 * 65536 / i6 * i1;
            localj.h[1] += i3 * 65536 / i6 * i1;
            localj.h[2] += i4 * 65536 / i6 * i1;
            localj.f = true;
          }
        }
      }
    }
  }
  
  private static final void d(j paramj)
  {
    j localj = n[0];
    int i1 = paramj.p - localj.p >> 16;
    int i2 = paramj.q - localj.q >> 16;
    int i3 = paramj.r - localj.r >> 16;
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
      localj.p -= i1 * az[i5] * (140 - i5);
      localj.q -= i2 * az[i5] * (140 - i5);
      localj.r -= i3 * az[i5] * (140 - i5);
    }
  }
  
  private final boolean e(j paramj)
  {
    g[] arrayOfg = h;
    if ((paramj.h[0] == 0) && (paramj.h[1] == 0) && (paramj.h[2] == 0)) {
      return false;
    }
    int i1 = paramj.p - paramj.h[0];
    int i2 = paramj.q - paramj.h[1];
    int i3 = paramj.r - paramj.h[2];
    int i4 = 0;
    boolean bool = false;
    for (int i5 = 0; i5 < cA; i5++)
    {
      g localg;
      if (((localg = arrayOfg[i5]).t) && ((i4 = a(i1, i2, i3, paramj.p, paramj.q, paramj.r, localg.f + localg.m + 8192000, localg.g + localg.n + 8192000, localg.h + localg.o + 8192000, localg.i + localg.m - 8192000, localg.j + localg.n - 8192000, localg.k + localg.o - 8192000, paramj)) >= 0))
      {
        bool = true;
        paramj.h[i4] = 0;
      }
    }
    return bool;
  }
  
  private static final int a(int paramInt, d paramd1, d paramd2)
  {
    int i4 = -1;
    int[] arrayOfInt1 = aO;
    int[] arrayOfInt2 = l[paramInt].l;
    for (int i5 = l[paramInt].m; i5 >= 0; i5 -= 6)
    {
      int i1 = (int)((paramd1.a - arrayOfInt2[i5] >> 16) * arrayOfInt2[(i5 + 3)] + (paramd1.b - arrayOfInt2[(i5 + 1)] >> 16) * arrayOfInt2[(i5 + 4)] + (paramd1.c - arrayOfInt2[(i5 + 2)] >> 16) * arrayOfInt2[(i5 + 5)] >> 16);
      int i2;
      int i3;
      long l1;
      long l2;
      if ((i3 = (i2 = (int)((paramd2.a - arrayOfInt2[i5] >> 16) * arrayOfInt2[(i5 + 3)] + (paramd2.b - arrayOfInt2[(i5 + 1)] >> 16) * arrayOfInt2[(i5 + 4)] + (paramd2.c - arrayOfInt2[(i5 + 2)] >> 16) * arrayOfInt2[(i5 + 5)] >> 16)) - i1) > 0)
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
        paramd2.a = ((int)(paramd1.a * l1 + paramd2.a * l2 >> 18));
        paramd2.b = ((int)(paramd1.b * l1 + paramd2.b * l2 >> 18));
        paramd2.c = ((int)(paramd1.c * l1 + paramd2.c * l2 >> 18));
        i4 = i5;
      }
    }
    return i4;
  }
  
  private final boolean a(j paramj, int paramInt)
  {
    int[] arrayOfInt1 = paramj.h;
    int[] arrayOfInt2 = dS;
    boolean bool = false;
    int[] arrayOfInt3 = l[paramj.t].l;
    for (int i1 = l[paramj.t].m; tmp172_171 >= 0; tmp172_171 -= 6)
    {
      long l1;
      if ((l1 = arrayOfInt3[(i1 + 3)] * (paramj.p - arrayOfInt3[i1]) + arrayOfInt3[(i1 + 4)] * (paramj.q - arrayOfInt3[(i1 + 1)]) + (arrayOfInt3[(i1 + 5)] << aU) * (paramj.r - arrayOfInt3[(i1 + 2)]) >> 16) < 8192000L)
      {
        if (arrayOfInt3[(i1 + 5)] > 0) {
          bool = true;
        }
        long l2 = 8192000L - l1;
        j tmp147_146 = paramj;
        tmp147_146.p = ((int)(tmp147_146.p + (tmp147_146[(i1 + 3)] * l2 >> 16)));
        j tmp172_171 = paramj;
        tmp172_171.q = ((int)(tmp172_171.q + (tmp147_146[(tmp172_171 + 4)] * l2 >> 16)));
        j tmp197_196 = paramj;
        tmp197_196.r = ((int)(tmp197_196.r + (tmp147_146[(tmp172_171 + 5)] * l2 >> 16)));
        l1 = tmp147_146[(tmp172_171 + 3)] * arrayOfInt2[0] + tmp147_146[(tmp172_171 + 4)] * arrayOfInt2[1] + tmp147_146[(tmp172_171 + 5)] * arrayOfInt2[2] >> 16;
        int tmp273_272 = 0;
        int[] tmp273_270 = arrayOfInt2;
        tmp273_270[tmp273_272] = ((int)(tmp273_270[tmp273_272] - (tmp147_146[(tmp172_171 + 3)] * l1 >> 16)));
        int tmp296_295 = 1;
        int[] tmp296_293 = arrayOfInt2;
        tmp296_293[tmp296_295] = ((int)(tmp296_293[tmp296_295] - (tmp147_146[(tmp172_171 + 4)] * l1 >> 16)));
        int tmp319_318 = 2;
        int[] tmp319_316 = arrayOfInt2;
        tmp319_316[tmp319_318] = ((int)(tmp319_316[tmp319_318] - (tmp147_146[(tmp172_171 + 5)] * l1 >> 16)));
        arrayOfInt2[0] *= paramInt;
        arrayOfInt2[1] *= paramInt;
        arrayOfInt2[2] *= paramInt;
      }
    }
    if (e(paramj)) {
      bool = true;
    }
    return bool;
  }
  
  private static void b(j paramj, int paramInt)
  {
    int[] arrayOfInt = l[paramInt].l;
    for (int i1 = l[paramInt].m; i1 >= 0; i1 -= 6)
    {
      long l1;
      if ((l1 = arrayOfInt[(i1 + 3)] * (paramj.p - arrayOfInt[i1]) + arrayOfInt[(i1 + 4)] * (paramj.q - arrayOfInt[(i1 + 1)]) + (arrayOfInt[(i1 + 5)] << aU) * (paramj.r - arrayOfInt[(i1 + 2)]) >> 16) < 8192000L)
      {
        long l2 = 8192000L - l1;
        paramj.p = ((int)(paramj.p + (arrayOfInt[(i1 + 3)] * l2 >> 16)));
        paramj.q = ((int)(paramj.q + (arrayOfInt[(i1 + 4)] * l2 >> 16)));
        paramj.r = ((int)(paramj.r + (arrayOfInt[(i1 + 5)] * l2 >> 16)));
      }
    }
  }
  
  private static byte a(int paramInt1, int paramInt2, int paramInt3, int paramInt4, int paramInt5, int paramInt6, int paramInt7, int paramInt8, int paramInt9, int paramInt10, int paramInt11, int paramInt12, j paramj)
  {
    int[] arrayOfInt = aO;
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
        paramInt4 = i3 + 65536;
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
        paramInt5 = i4 + 65536;
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
        paramInt4 = i3 - 65536;
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
        paramInt5 = i4 - 65536;
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
        paramInt6 = i5 - 65536;
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
        paramInt6 = i5 + 65536;
        b1 = 2;
      }
    }
    paramj.p = paramInt4;
    paramj.q = paramInt5;
    paramj.r = paramInt6;
    return b1;
  }
  
  private final void n()
  {
    int i1;
    try
    {
      this.bQ = null;
      i1 = 0;
      try
      {
        this.bQ = e.a(e.a(I));
      }
      catch (Exception localException1) {}
      try
      {
        this.bw = e.a(e.a(Z));
      }
      catch (Exception localException2) {}
      if (this.bQ == null)
      {
        this.aw = false;
        return;
      }
      try
      {
        this.cE = e.a(e.a(p));
      }
      catch (Exception localException3) {}
      this.bP = 0;
      long l1 = 30L;
      int i2 = -1;
      while (this.bP < 100)
      {
        repaint();
        serviceRepaints();
        Thread.sleep(l1);
        if ((l1 += i2 < 20L) && (i2 == -1))
        {
          l1 = 330L;
          i2 = -10;
        }
        if (l1 < 10L) {
          l1 = 10L;
        }
        this.bP = ((byte)(this.bP + 1));
      }
      a();
      Thread.sleep(100L);
      this.bP = 0;
    }
    catch (Exception localException4)
    {
      this.aw = false;
      return;
    }
    try
    {
      this.bQ = null;
      i1 = 1;
      String str = e.a(z);
      while (i1 != 0) {
        try
        {
          this.bQ = e.a(str);
          i1 = 0;
        }
        catch (Exception localException5)
        {
          i1 = 0;
        }
      }
      String[][] arrayOfString = e.l.b(e.a(H));
      this.bN = new String(arrayOfString[1][0]);
      this.bE = 0;
      while (this.bE != 53)
      {
        if (this.bP == -1) {
          this.bP = -2;
        } else {
          this.bP = -1;
        }
        a();
        Thread.sleep(300L);
      }
      this.bN = null;
    }
    catch (Exception localException6) {}
    this.bQ = null;
    this.bw = null;
    this.am = -1;
  }
  
  private final void o()
  {
    j localj2 = n[0];
    if (cM >= this.ds) {
      cM -= this.ds;
    }
    if (cM <= -this.ds) {
      cM += this.ds;
    }
    this.cc = false;
    if ((b != 0) && (bs[0] > 0))
    {
      this.bm = 0;
      if (bn == 0)
      {
        int tmp84_83 = 0;
        byte[] tmp84_80 = bs;
        tmp84_80[tmp84_83] = ((byte)(tmp84_80[tmp84_83] - 1));
        bn = 15;
      }
    }
    for (int i4 = dR - 1; i4 >= 0; i4--)
    {
      if (localj2.k) {
        break;
      }
      j localj1;
      if ((localj1 = n[i4]).k)
      {
        if ((i4 != 0) && (localj1.C < 4) && (!localj1.x)) {
          if (j(localj1))
          {
            localj1.x = true;
            ac();
          }
        }
      }
      else
      {
        if (localj1.s > 0)
        {
          j tmp184_182 = localj1;
          tmp184_182.s = ((byte)(tmp184_182.s - 1));
        }
        bv = (short)i4;
        a(localj1);
        if (i4 == 0) {
          this.cc = true;
        }
        g(n[i4]);
        if (i4 != 0)
        {
          d(localj1);
          if ((localj1.C > 3) && (!localj1.x) && (bs[1] > 0))
          {
            int i1 = localj2.p - localj1.p >> 16;
            int i2 = localj2.q - localj1.q >> 16;
            int i3 = localj2.r - localj1.r >> 16;
            if (i1 * i1 + i2 * i2 + i3 * i3 < 40000)
            {
              this.bm = 1;
              if (bn == 0)
              {
                int tmp338_337 = 1;
                byte[] tmp338_334 = bs;
                tmp338_334[tmp338_337] = ((byte)(tmp338_334[tmp338_337] - 1));
                bn = 15;
              }
            }
          }
        }
      }
    }
    if (ap > 0)
    {
      ap = (byte)(ap - 1);
      if (ap == 4) {
        eg = n[0].F;
      }
    }
    u();
    q();
    r();
    m();
    v();
    dQ = false;
    if (n[0].k)
    {
      n[0].e = 0;
      if (eh < 128)
      {
        eh = (short)(eh + 6);
        dc -= 5;
      }
      if (eh > 128)
      {
        b((byte)0);
        eh = 128;
      }
      return;
    }
    if (n[0].e > 0)
    {
      j tmp496_495 = n[0];
      tmp496_495.e = ((short)(tmp496_495.e - 10));
      if (n[0].e < 0) {
        n[0].e = 0;
      }
    }
    if (eh > 0)
    {
      eh = (short)(eh - 10);
      if (eh < 0) {
        eh = 0;
      }
    }
  }
  
  private static final void p()
  {
    l();
    dc += 20 - g(40);
    if (dc < -30) {
      dc = -30;
    }
    if (dc > 30) {
      dc = 30;
    }
    b = 0;
    e(b);
    eh = (short)(eh + 64);
    if (eh > 220) {
      eh = 220;
    }
  }
  
  private static final void f(int paramInt)
  {
    k = (short)(40 - (paramInt >> 6));
    if (k < 0) {
      k = 0;
    }
  }
  
  private static final int g(int paramInt)
  {
    return Math.abs(ek.nextInt() % paramInt);
  }
  
  public final void a()
  {
    long l1 = System.currentTimeMillis();
    if (!this.i)
    {
      o();
      a(cN, cY);
      a(aQ);
      if (cP) {
        b(0, 0, 93, 8);
      }
    }
    repaint();
    serviceRepaints();
    long l2 = System.currentTimeMillis();
    this.cF = (l2 - l1);
    long l3 = l2 - l1;
    long l4 = this.dF;
    if (l3 < l4) {
      try
      {
        Thread.sleep(l4 - l3);
        return;
      }
      catch (Exception localException) {}
    }
  }
  
  private static void q()
  {
    int[][] arrayOfInt = dk;
    int[] arrayOfInt3 = az;
    d locald1 = dH;
    d locald2 = bb;
    int i12 = 0;
    for (int i1 = 19; i1 >= 0; i1--)
    {
      int[] arrayOfInt1;
      if ((arrayOfInt1 = arrayOfInt[i1])[6] != 0)
      {
        arrayOfInt1[6] -= 1;
        if (arrayOfInt1[6] == 0)
        {
          dm -= 1;
          a(arrayOfInt1[0], arrayOfInt1[1], arrayOfInt1[2], (byte)0, (short)arrayOfInt1[7]);
          if (dk[i1][11] == 9) {
            a(arrayOfInt1[0], arrayOfInt1[1], arrayOfInt1[2], arrayOfInt1[7]);
          } else {
            a(arrayOfInt1[0], arrayOfInt1[1], arrayOfInt1[2]);
          }
        }
        else
        {
          int i13 = arrayOfInt1[7];
          if (dk[i1][8] > 4)
          {
            arrayOfInt1[9] += 20;
            if (arrayOfInt1[9] >= 360) {
              arrayOfInt1[9] -= 360;
            }
            arrayOfInt1[10] += 20;
            if (arrayOfInt1[10] >= 360) {
              arrayOfInt1[10] -= 360;
            }
          }
          int i5 = arrayOfInt1[3] * dk[i1][8];
          int i6 = arrayOfInt1[4] * dk[i1][8];
          int i7 = (i7 = arrayOfInt1[5] * dk[i1][8]) - 524288;
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
          arrayOfInt1[3] = ((int)(i5 * arrayOfInt3[i3] >> 16));
          arrayOfInt1[4] = ((int)(i6 * arrayOfInt3[i3] >> 16));
          arrayOfInt1[5] = ((int)(i7 * arrayOfInt3[i3] >> 16));
          if (i3 > 160) {
            dk[i1][8] = ' ';
          } else {
            dk[i1][8] = i3;
          }
          locald1.a = arrayOfInt1[0];
          locald1.b = arrayOfInt1[1];
          locald1.c = arrayOfInt1[2];
          locald2.a = (arrayOfInt1[0] + arrayOfInt1[3] * dk[i1][8]);
          locald2.b = (arrayOfInt1[1] + arrayOfInt1[4] * dk[i1][8]);
          locald2.c = (arrayOfInt1[2] + arrayOfInt1[5] * dk[i1][8]);
          i12 = -1;
          for (;;)
          {
            if ((i4 = b(i13, locald1, locald2)) != -1)
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
              dk[i1][8] >>= 2;
              break label675;
            }
            if ((i12 = a(i13, locald1, locald2, i12)) == -1) {
              break;
            }
            if (j[i12].c == i13) {
              i13 = j[i12].d;
            } else {
              i13 = j[i12].c;
            }
          }
          dk[i1][7] = i13;
          label675:
          f localf = l[i13];
          arrayOfInt1[0] = locald2.a;
          arrayOfInt1[1] = locald2.b;
          arrayOfInt1[2] = locald2.c;
          int[] arrayOfInt2 = localf.l;
          for (int i2 = localf.m; i2 >= 0; i2 -= 6)
          {
            long l1;
            if ((l1 = (arrayOfInt1[0] - arrayOfInt2[i2]) * arrayOfInt2[(i2 + 3)] + (arrayOfInt1[1] - arrayOfInt2[(i2 + 1)]) * arrayOfInt2[(i2 + 4)] + (arrayOfInt1[2] - arrayOfInt2[(i2 + 2)]) * arrayOfInt2[(i2 + 5)] >> 16) <= 0L)
            {
              int tmp793_792 = 0;
              int[] tmp793_791 = arrayOfInt1;
              tmp793_791[tmp793_792] = ((int)(tmp793_791[tmp793_792] + -(l1 >> 16) * arrayOfInt2[(i2 + 3)]));
              int tmp815_814 = 1;
              int[] tmp815_813 = arrayOfInt1;
              tmp815_813[tmp815_814] = ((int)(tmp815_813[tmp815_814] + -(l1 >> 16) * arrayOfInt2[(i2 + 4)]));
              int tmp837_836 = 2;
              int[] tmp837_835 = arrayOfInt1;
              tmp837_835[tmp837_836] = ((int)(tmp837_835[tmp837_836] + -(l1 >> 16) * arrayOfInt2[(i2 + 5)]));
              l1 = arrayOfInt2[(i2 + 3)] * arrayOfInt1[3] + arrayOfInt2[(i2 + 4)] * arrayOfInt1[4] + arrayOfInt2[(i2 + 5)] * arrayOfInt1[5] >> 16 << 1;
              int tmp904_903 = 3;
              int[] tmp904_902 = arrayOfInt1;
              tmp904_902[tmp904_903] = ((int)(tmp904_902[tmp904_903] - (arrayOfInt2[(i2 + 3)] * l1 >> 16)));
              int tmp925_924 = 4;
              int[] tmp925_923 = arrayOfInt1;
              tmp925_923[tmp925_924] = ((int)(tmp925_923[tmp925_924] - (arrayOfInt2[(i2 + 4)] * l1 >> 16)));
              int tmp946_945 = 5;
              int[] tmp946_944 = arrayOfInt1;
              tmp946_944[tmp946_945] = ((int)(tmp946_944[tmp946_945] - (arrayOfInt2[(i2 + 5)] * l1 >> 16)));
              dk[i1][8] >>= 2;
            }
          }
        }
      }
    }
  }
  
  private static void r()
  {
    int[][] arrayOfInt = dA;
    int i1 = 0;
    int i2 = 0;
    while (i1 < dB) {
      if (arrayOfInt[i2][4] < 1)
      {
        i2++;
      }
      else
      {
        arrayOfInt[i2][4] -= 1;
        if (arrayOfInt[i2][4] < 1)
        {
          dB -= 1;
        }
        else
        {
          i1++;
          i2++;
        }
      }
    }
  }
  
  private void h(int paramInt)
  {
    if (paramInt < 4) {
      this.dG += 200;
    }
    switch (cn)
    {
    case 1: 
      
    case 2: 
      if (paramInt > 3)
      {
        b((byte)14);
        return;
      }
      break;
    case 3: 
      bF = (byte)(bF + 1);
      if (bF >= dK)
      {
        b((byte)1);
        return;
      }
      break;
    case 4: 
      if (paramInt < 4)
      {
        bF = (byte)(bF + 1);
        if (bF >= dK) {
          b((byte)1);
        }
        return;
      }
      bt = (byte)(bt - 1);
      if (bt <= 0) {
        b((byte)0);
      }
      return;
    case 5: 
      
    case 6: 
      if (paramInt > 3)
      {
        b((byte)14);
        return;
      }
      bF = (byte)(bF + 1);
      if (bF >= dK) {
        b((byte)1);
      }
      return;
    case 7: 
      
    case 8: 
      if (paramInt > 3)
      {
        b((byte)14);
        return;
      }
      break;
    case 9: 
      if (paramInt > 3)
      {
        b((byte)15);
        return;
      }
      break;
    case 10: 
      if (paramInt > 3) {
        b((byte)15);
      }
      break;
    }
  }
  
  private static final int a(int paramInt, d paramd1, d paramd2, j paramj)
  {
    d locald;
    (locald = bA).a = paramd2.a;
    locald.b = paramd2.b;
    locald.c = paramd2.c;
    g[] arrayOfg = h;
    j[] arrayOfj = n;
    int i1 = -1;
    int i2 = l[paramInt].e;
    int i3 = -1;
    int i4 = 0;
    for (int i5 = l[paramInt].r; i5 < i2; i5++)
    {
      g localg;
      if (((localg = arrayOfg[i5]).t) && (localg.s != 45) && (localg.s != 46)) {
        if (i1 == -1)
        {
          if ((i1 = a(locald, paramd1, paramd2, localg.f + localg.m, localg.g + localg.n, localg.h + localg.o, localg.i + localg.m, localg.j + localg.n, localg.k + localg.o)) != -1) {
            i3 = i5;
          }
        }
        else if (a(locald, paramd1, paramd2, localg.f + localg.m, localg.g + localg.n, localg.h + localg.o, localg.i + localg.m, localg.j + localg.n, localg.k + localg.o) != -1) {
          i3 = i5;
        }
      }
    }
    for (int i6 = dR - 1; i6 >= 0; i6--)
    {
      j localj;
      if ((!(localj = arrayOfj[i6]).k) && (localj.t == paramInt) && (bv != i6)) {
        if (i1 == -1)
        {
          if ((i1 = a(locald, paramd1, paramd2, localj.p + 2621440, localj.q + 2621440, localj.r + 4915200, localj.p - 2621440, localj.q - 2621440, localj.r - 8192000)) != -1)
          {
            i3 = i6;
            i4 = 1;
          }
        }
        else if (a(locald, paramd1, paramd2, localj.p + 2621440, localj.q + 2621440, localj.r + 4915200, localj.p - 2621440, localj.q - 2621440, localj.r - 8192000) != -1)
        {
          i3 = i6;
          i4 = 1;
        }
      }
    }
    if (i1 != -1) {
      if (i4 != 0)
      {
        a(locald.a, locald.b, locald.c, (byte)(g(4) + 2), (short)paramInt);
        if (i3 == 0)
        {
          paramj.w = 0;
          paramj.o = true;
          a(arrayOfj[i3], true, locald);
        }
        else
        {
          a(arrayOfj[i3], false, locald);
          arrayOfj[i3].g = 0;
          arrayOfj[i3].z = n[0].p;
          arrayOfj[i3].A = n[0].q;
        }
      }
      else if (arrayOfg[i3].s == 35)
      {
        a(arrayOfg[i3].m, arrayOfg[i3].n, arrayOfg[i3].o + 8192000, (byte)0, (short)paramInt);
        a(arrayOfg[i3].m, arrayOfg[i3].n, arrayOfg[i3].o);
        arrayOfg[i3].t = false;
      }
      else
      {
        a(locald.a, locald.b, locald.c, (byte)1, (short)paramInt);
      }
    }
    return i1;
  }
  
  private static final int b(int paramInt, d paramd1, d paramd2)
  {
    d locald;
    (locald = bA).a = paramd2.a;
    locald.b = paramd2.b;
    locald.c = paramd2.c;
    g[] arrayOfg = h;
    int i1 = -1;
    int i2 = 0;
    int i3 = l[paramInt].e;
    for (int i4 = l[paramInt].r; i4 < i3; i4++)
    {
      g localg;
      if (((localg = arrayOfg[i4]).t) && ((i2 = a(locald, paramd1, paramd2, localg.f + localg.m, localg.g + localg.n, localg.h + localg.o, localg.i + localg.m, localg.j + localg.n, localg.k + localg.o)) != -1)) {
        i1 = i2;
      }
    }
    paramd2.a = locald.a;
    paramd2.b = locald.b;
    paramd2.c = locald.c;
    return i1;
  }
  
  private static final int a(int paramInt1, d paramd1, d paramd2, int paramInt2)
  {
    b[] arrayOfb = j;
    int[] arrayOfInt1 = l[paramInt1].p;
    int i1 = l[paramInt1].q;
    int[] arrayOfInt2 = aO;
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
        b localb;
        i[] arrayOfi = (localb = arrayOfb[arrayOfInt1[i13]]).b;
        switch (localb.a)
        {
        case 1: 
          i2 = paramd1.a - arrayOfi[0].j >> 16;
          i3 = paramd2.a - arrayOfi[0].j >> 16;
          i8 = Math.max(arrayOfi[0].k, Math.max(arrayOfi[1].k, arrayOfi[2].k));
          i11 = Math.min(arrayOfi[0].k, Math.min(arrayOfi[1].k, arrayOfi[2].k));
          i9 = Math.max(arrayOfi[0].l, Math.max(arrayOfi[1].l, arrayOfi[2].l));
          i12 = Math.min(arrayOfi[0].l, Math.min(arrayOfi[1].l, arrayOfi[2].l));
          break;
        case 2: 
          i2 = paramd1.b - arrayOfi[0].k >> 16;
          i3 = paramd2.b - arrayOfi[0].k >> 16;
          i7 = Math.max(arrayOfi[0].j, Math.max(arrayOfi[1].j, arrayOfi[2].j));
          i10 = Math.min(arrayOfi[0].j, Math.min(arrayOfi[1].j, arrayOfi[2].j));
          i9 = Math.max(arrayOfi[0].l, Math.max(arrayOfi[1].l, arrayOfi[2].l));
          i12 = Math.min(arrayOfi[0].l, Math.min(arrayOfi[1].l, arrayOfi[2].l));
          break;
        case 3: 
          i2 = paramd1.c - arrayOfi[0].l >> 16;
          i3 = paramd2.c - arrayOfi[0].l >> 16;
          i7 = Math.max(arrayOfi[0].j, Math.max(arrayOfi[1].j, arrayOfi[2].j));
          i10 = Math.min(arrayOfi[0].j, Math.min(arrayOfi[1].j, arrayOfi[2].j));
          i8 = Math.max(arrayOfi[0].k, Math.max(arrayOfi[1].k, arrayOfi[2].k));
          i11 = Math.min(arrayOfi[0].k, Math.min(arrayOfi[1].k, arrayOfi[2].k));
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
          int i4 = (int)(paramd1.a * l1 + paramd2.a * l2 >> 18);
          int i5 = (int)(paramd1.b * l1 + paramd2.b * l2 >> 18);
          int i6 = (int)(paramd1.c * l1 + paramd2.c * l2 >> 18);
          switch (localb.a)
          {
          case 1: 
            if ((i12 <= i6) && (i11 <= i5) && (i9 >= i6) && (i8 >= i5))
            {
              paramd1.a = i4;
              paramd1.b = i5;
              paramd1.c = i6;
              return arrayOfInt1[i13];
            }
            break;
          case 2: 
            if ((i12 <= i6) && (i10 <= i4) && (i9 >= i6) && (i7 >= i4))
            {
              paramd1.a = i4;
              paramd1.b = i5;
              paramd1.c = i6;
              return arrayOfInt1[i13];
            }
            break;
          case 3: 
            if ((i10 <= i4) && (i11 <= i5) && (i7 >= i4) && (i8 >= i5))
            {
              paramd1.a = i4;
              paramd1.b = i5;
              paramd1.c = i6;
              return arrayOfInt1[i13];
            }
            break;
          }
        }
      }
    }
    return -1;
  }
  
  private static byte s()
  {
    j[] arrayOfj;
    j localj = (arrayOfj = n)[0];
    int i1 = 0;
    int i2 = 0;
    byte b1 = 0;
    int i3 = 0;
    for (int i4 = 1; i4 < dR; i4++)
    {
      if ((!arrayOfj[i4].k) && (al[i4] > 0) && (arrayOfj[i4].C < 4))
      {
        i1 = Math.abs(arrayOfj[i4].p - localj.p) + Math.abs(arrayOfj[i4].q - localj.q) + Math.abs(arrayOfj[i4].r - localj.r);
        if (i3 == 0)
        {
          i2 = i1;
          b1 = al[i4];
          i3 = 1;
        }
        else if (i1 < i2)
        {
          i2 = i1;
          b1 = al[i4];
        }
      }
      al[i4] = 0;
    }
    return b1;
  }
  
  private final void t()
  {
    for (int i1 = cA - 1; i1 >= 0; i1--)
    {
      g localg;
      switch ((localg = h[i1]).s)
      {
      case 23: 
        if (localg.l > 0)
        {
          g tmp100_99 = localg;
          tmp100_99.l = ((byte)(tmp100_99.l - 1));
          localg.p += 7;
          if (localg.p >= 360) {
            localg.p = 0;
          }
        }
        break;
      case 16: 
        localg.q += 18;
        if (localg.q >= 360) {
          localg.q -= 360;
        }
        break;
      case 26: 
        localg.q += 10;
        if (localg.q >= 360) {
          localg.q -= 360;
        }
        break;
      case 21: 
        if (this.dp)
        {
          localg.q += 5;
          if (localg.q >= 360) {
            localg.q -= 360;
          }
        }
        else
        {
          localg.q -= 5;
          if (localg.q < 0) {
            localg.q += 360;
          }
        }
        this.dp = (!this.dp);
        break;
      case 53: 
      case 55: 
        if (localg.l > 0)
        {
          g tmp309_308 = localg;
          tmp309_308.l = ((byte)(tmp309_308.l - 1));
          if (localg.o > localg.e) {
            localg.o -= 524288;
          }
        }
        else if (localg.o < localg.e + localg.h + 8192000)
        {
          localg.o += 524288;
        }
        break;
      case 52: 
      case 54: 
        if (localg.l > 0)
        {
          g tmp388_387 = localg;
          tmp388_387.l = ((byte)(tmp388_387.l - 1));
          if (localg.o < localg.e) {
            localg.o += 524288;
          }
        }
        else if (localg.o > localg.e - localg.h - 8192000)
        {
          localg.o -= 524288;
        }
        break;
      }
    }
  }
  
  private final void u()
  {
    t();
    byte b1 = 0;
    byte[][] arrayOfByte = ck;
    for (int i9 = dR - 1; tmp458_457 > 0; tmp458_457--)
    {
      j localj;
      if ((localj = n[i9]).j)
      {
        localj.n = false;
        int i1;
        int i2;
        if (localj.C < 4)
        {
          if ((localj.B >= 0) && (localj.B <= 4))
          {
            int i6 = n[0].p - localj.p >> 16;
            int i7 = n[0].q - localj.q >> 16;
            int i8 = i6 * i6 + i7 * i7;
            int i4 = 0;
            int i5 = 65536;
            while (i5 >>= 1 > 0) {
              if ((i4 + i5) * (i4 + i5) <= i8) {
                i4 += i5;
              }
            }
            if (i4 == 0) {
              i4 = 1;
            }
            i6 = i6 * 65536 / i4;
            i7 = i7 * 65536 / i4;
            int i3;
            if ((i3 = (int)(localj.u[0] * i6 + localj.u[1] * i7 >> 16)) < 0) {
              b1 = 2;
            } else {
              b1 = 1;
            }
            if ((i3 <= 46341) && (i3 >= -46341))
            {
              i3 = (int)(localj.u[0] * i7 + -localj.u[1] * i6 >> 16);
              b1 = 3;
              if (i3 > 0) {
                b1 = 4;
              }
            }
          }
          if ((localj.B == 0) && (b1 > 0)) {}
          switch (b1)
          {
          case 1: 
            localj.i = 0;
            break;
          case 2: 
            localj.i = 12;
            break;
          case 3: 
            localj.i = 15;
            localj.n = true;
            break;
          case 4: 
            localj.i = 20;
          default: 
            continue;
            if ((localj.B == 1) || (localj.B == 2) || (localj.B == 3) || (localj.B == 4))
            {
              if (localj.B == 3) {
                localj.n = true;
              }
              localj.B = b1;
            }
            i1 = arrayOfByte[localj.C][((localj.B << 1) + 1)];
            i2 = arrayOfByte[localj.C][((localj.B << 1) + 2)];
            j tmp458_457 = localj;
            tmp458_457.i = ((short)(tmp458_457.i + 1));
            if (localj.B == 5) {
              localj.i = ((short)(byte)(i1 << 1));
            }
            break;
          }
        }
        else
        {
          i1 = arrayOfByte[localj.C][((localj.B << 1) + 1)];
          i2 = arrayOfByte[localj.C][((localj.B << 1) + 2)];
          j tmp523_522 = localj;
          tmp523_522.i = ((short)(tmp523_522.i + 1));
          if (localj.i >> 1 >= i1 + i2) {
            if (localj.B != 6)
            {
              localj.i = ((short)(byte)(i1 << 1));
            }
            else
            {
              j tmp567_566 = localj;
              tmp567_566.i = ((short)(tmp567_566.i - 1));
              localj.n = false;
              localj.j = false;
              localj.x = false;
              h(localj.C);
            }
          }
        }
      }
    }
  }
  
  private static int a(byte paramByte)
  {
    int i1 = paramByte;
    if (paramByte < 0) {
      i1 = 256 + paramByte;
    }
    return i1;
  }
  
  public final void b()
  {
    ce = false;
    this.bO = false;
    this.bT = null;
    this.aT = 1L;
  }
  
  private final void v()
  {
    if (cV > 4) {
      cV = (short)(cV - 1);
    }
    if (aG > 0) {
      aG -= 1;
    }
    if (cR < 0) {
      cR += 1;
    }
    if (cS < 0) {
      cS += 1;
    }
    if (cR > 0) {
      cR -= 1;
    }
    if (cS > 0) {
      cS -= 1;
    }
    if (cR > 17) {
      cR = 17;
    }
    if (cR < -17) {
      cR = -17;
    }
    j localj;
    cY = (localj = n[0]).t;
    dg[0] = localj.p;
    dg[1] = localj.q;
    dg[2] = (localj.r + 2293760);
    if (localj.k) {
      dg[2] -= (eh >> 1 << 16);
    }
    if (k > 1)
    {
      if ((i1 = (byte)g(2)) == 0) {
        i1 = -1;
      } else {
        i1 = 1;
      }
      dg[0] += g(k) * aA[df] * i1;
      if ((i1 = (byte)g(2)) == 0) {
        i1 = -1;
      } else {
        i1 = 1;
      }
      dg[1] += g(k) * dn[df] * i1;
      if ((i1 = (byte)g(2)) == 0) {
        i1 = -1;
      } else {
        i1 = 1;
      }
      dg[2] += g(k) * dn[df] * i1;
      k = (short)(k - 4);
    }
    localj.u[0] = dd;
    localj.u[1] = df;
    if (dW)
    {
      dY = (byte)(dY + dZ);
      if ((dX <= dY) || (dY <= 0))
      {
        dZ = (byte)-dZ;
        dY = (byte)(dY + (dZ << 1));
      }
    }
    else
    {
      if (dZ < 0) {
        dZ = (byte)-dZ;
      }
      if (dY > 0) {
        dY = (byte)(dY - dZ);
      }
      if (dY < 0) {
        dY = 0;
      }
    }
    dg[2] += (dY << 16);
    dW = false;
    int i1 = s();
    if (b == 0)
    {
      if ((i1 == 0) && (!localj.k))
      {
        if (dc > 0)
        {
          dc -= da;
          da += 1;
          if (dc < 0) {
            dc = 0;
          }
        }
        if (dc < 0)
        {
          dc += da;
          da += 1;
          if (dc > 0) {
            dc = 0;
          }
        }
      }
      else
      {
        if (i1 == 1) {
          dc += 1;
        }
        if (i1 == 2) {
          dc -= 1;
        }
      }
      if (dc == 0) {
        da = 0;
      }
    }
    if (dc > 60) {
      dc = 60;
    }
    if (dc < -60) {
      dc = -60;
    }
    dd = de + dc;
    if (((cn == 3) || (cn == 4)) && (dd < 270)) {
      dd = 270;
    }
    if (db > 0) {
      if (dQ)
      {
        db -= 1;
      }
      else
      {
        db -= 8;
        if (db < 0) {
          db = 0;
        }
      }
    }
    if (db < 0) {
      if (dQ)
      {
        db += 1;
      }
      else
      {
        db += 8;
        if (db > 0) {
          db = 0;
        }
      }
    }
    df += db;
    cM += db;
    if (df < 0) {
      df += 359;
    }
    if (df > 359) {
      df -= 359;
    }
    if (dd > 359) {
      dd = 359;
    }
    if (dd < 180) {
      dd = 180;
    }
    if ((b == 0) && (dc == 0))
    {
      de = 270;
      dd = 270;
    }
    if (bj > 0) {
      bj = (byte)(bj - 1);
    }
  }
  
  private static final int i(int paramInt)
  {
    int i1;
    if ((i1 = paramInt >> 16 << 16) < paramInt) {
      return (i1 >> 16) + 1;
    }
    return i1 >> 16;
  }
  
  private final void w()
  {
    if ((aI) && ((this.cg == 4) || (this.cg == 8)) && (this.bB >= 2))
    {
      this.dF = 77;
      b();
      return;
    }
    if (this.cg == 3) {
      if ((aI) && (this.m != null))
      {
        this.cg = 14;
        this.cf = 14;
      }
      else if (aI)
      {
        this.cg = 17;
        this.cf = 17;
      }
      else if (this.m != null)
      {
        if (cn > 0)
        {
          this.cg = 19;
          this.cf = 19;
        }
        else
        {
          this.cg = 16;
          this.cf = 16;
        }
      }
      else if (cn > 0)
      {
        this.cf = 0;
        this.cg = 0;
      }
    }
    this.cd = null;
    if ((this.cg <= 9) || ((this.cg >= 13) && (this.cg <= 17)) || (this.cg == 19)) {
      try
      {
        this.cd = new k(this, c(e.a(v)));
        return;
      }
      catch (OutOfMemoryError localOutOfMemoryError)
      {
        this.eb = 240;
        this.ea = 122;
        for (int i1 = 0; i1 < 10; i1++) {
          this.cy[i1] = null;
        }
        this.cd = new k(this, c(e.a(v)));
        return;
      }
    }
    switch (this.cg)
    {
    case 10: 
      this.cd = new k(this, d(e.a(w)));
      return;
    case 11: 
      this.cd = new k(this, d(e.a(x)));
      return;
    case 18: 
      this.cd = new k(this, d(e.a(y)));
      return;
    case 12: 
      this.cd = new k(this, I());
    }
  }
  
  private final boolean f(j paramj)
  {
    int[] arrayOfInt = dS;
    f localf1 = l[paramj.t];
    f localf2 = null;
    int i1;
    if ((localf1.f < paramj.p) || (localf1.i > paramj.p) || (localf1.g < paramj.q) || (localf1.j > paramj.q) || (localf1.h < paramj.r) || (localf1.k > paramj.r)) {
      for (i1 = cZ - 1; i1 >= 0; i1--) {
        if (((localf2 = l[i1]).f > paramj.p) && (localf2.i < paramj.p) && (localf2.g > paramj.q) && (localf2.j < paramj.q) && (localf2.h > paramj.r) && (localf2.k < paramj.r))
        {
          paramj.t = ((short)i1);
          if ((this.cc) && (cn == 2) && (i1 == 28) && (!n[this.ei].x)) {
            b((byte)18);
          }
          if ((!this.cc) || (this.cO != i1)) {
            break;
          }
          if ((cn != 3) && (cn != 4) && (cn != 7) && (cn != 6) && (cn != 8) && (cn != 10)) {
            b((byte)1);
          }
          int i2;
          if (cn == 7)
          {
            for (i2 = 1; i2 < dR; i2++) {
              if ((n[i2].B > 3) && (n[i2].x)) {
                this.dG += 5000;
              }
            }
            b((byte)1);
          }
          if (cn == 8)
          {
            i2 = 0;
            int i3 = 0;
            for (int i4 = 1; i4 < dR; i4++) {
              if ((n[i4].C > 3) && (n[i4].k) && (n[i4].x)) {
                i3++;
              }
            }
            for (int i5 = 1; i5 < dR; i5++) {
              if ((n[i5].C > 3) && (!n[i5].k) && (n[i5].x))
              {
                n[i5].k = true;
                n[i5].E = false;
                n[i5].m = 0;
                i2++;
              }
            }
            if (i2 + i3 >= 3) {
              b((byte)13);
            } else if (i2 > 0) {
              b((byte)12);
            }
          }
          if (cn == 10) {
            if (n[this.ei].x) {
              b((byte)1);
            } else {
              b((byte)16);
            }
          }
          break;
        }
      }
    }
    if ((arrayOfInt[0] == 0) && (arrayOfInt[1] == 0) && (arrayOfInt[2] == 0)) {
      return false;
    }
    arrayOfInt[0] = (paramj.p + arrayOfInt[0] * 125);
    arrayOfInt[1] = (paramj.q + arrayOfInt[1] * 125);
    arrayOfInt[2] = (paramj.r + arrayOfInt[2] * 125);
    if ((localf1.f < arrayOfInt[0]) || (localf1.i > arrayOfInt[0]) || (localf1.g < arrayOfInt[1]) || (localf1.j > arrayOfInt[1]) || (localf1.h < arrayOfInt[2]) || (localf1.k > arrayOfInt[2]))
    {
      for (i1 = cZ - 1; i1 >= 0; i1--) {
        if (((localf2 = l[i1]).f > arrayOfInt[0]) && (localf2.i < arrayOfInt[0]) && (localf2.g > arrayOfInt[1]) && (localf2.j < arrayOfInt[1]) && (localf2.h > arrayOfInt[2]) && (localf2.k < arrayOfInt[2]))
        {
          b(paramj, i1);
          return false;
        }
      }
      if (arrayOfInt[0] > localf1.f) {
        paramj.p += localf1.f - arrayOfInt[0];
      }
      if (arrayOfInt[0] < localf1.i) {
        paramj.p += localf1.i - arrayOfInt[0];
      }
      if (arrayOfInt[1] > localf1.g) {
        paramj.q += localf1.g - arrayOfInt[1];
      }
      if (arrayOfInt[1] < localf1.j) {
        paramj.q += localf1.j - arrayOfInt[1];
      }
      if (arrayOfInt[2] > localf1.h) {
        paramj.r += localf1.h - arrayOfInt[2];
      }
      if (arrayOfInt[2] < localf1.k) {
        paramj.r += localf1.k - arrayOfInt[2];
      }
    }
    return true;
  }
  
  private static void x()
  {
    if (b > 0)
    {
      b = 0;
      e(b);
      return;
    }
    if (ap != 0) {
      return;
    }
    j localj = n[0];
    for (;;)
    {
      dw = (byte)(dw + 1);
      if (dw >= 4)
      {
        dw = 0;
        localj.F = dt[dw];
        break;
      }
      if (dt[dw] != 0) {
        if ((dw != 3) || (ai[3] != 0))
        {
          localj.F = dt[dw];
          break;
        }
      }
    }
    ap = 8;
  }
  
  private static final byte a(i[] paramArrayOfi1, i[] paramArrayOfi2, int[][] paramArrayOfInt)
  {
    int[] arrayOfInt1 = aO;
    int i1 = -2097152;
    int i2 = 3;
    int i7 = 0;
    int[] arrayOfInt2 = el;
    for (int i8 = 0; i8 < 5; i8++)
    {
      int[] arrayOfInt3 = paramArrayOfInt[i8];
      i7 = 0;
      int i6 = i2 * 9;
      for (int i3 = 0; i3 < i2; i3++)
      {
        i locali1 = paramArrayOfi2[i3];
        i locali2 = paramArrayOfi2[arrayOfInt2[(i6 + i3)]];
        int i4 = (int)(locali1.a * arrayOfInt3[0] + locali1.b * arrayOfInt3[1] + (locali1.c + i1) * arrayOfInt3[2] >> 22);
        int i5 = (int)(locali2.a * arrayOfInt3[0] + locali2.b * arrayOfInt3[1] + (locali2.c + i1) * arrayOfInt3[2] >> 22);
        if (i4 >= 0)
        {
          paramArrayOfi1[i7].a = locali1.a;
          paramArrayOfi1[i7].b = locali1.b;
          paramArrayOfi1[i7].c = locali1.c;
          paramArrayOfi1[i7].f = locali1.f;
          paramArrayOfi1[i7].h = locali1.h;
          i7 = (byte)(i7 + 1);
        }
        long l1;
        long l2;
        if (i5 - i4 > 0)
        {
          l1 = i5 * arrayOfInt1[(i5 - i4)];
          l2 = -i4 * arrayOfInt1[(i5 - i4)];
        }
        else
        {
          l1 = -i5 * arrayOfInt1[(i4 - i5)];
          l2 = i4 * arrayOfInt1[(i4 - i5)];
        }
        if (((i4 > 0) && (i5 < 0)) || ((i5 > 0) && (i4 < 0)))
        {
          paramArrayOfi1[i7].a = ((int)(locali1.a * l1 + locali2.a * l2 >> 18));
          paramArrayOfi1[i7].b = ((int)(locali1.b * l1 + locali2.b * l2 >> 18));
          paramArrayOfi1[i7].c = ((int)(locali1.c * l1 + locali2.c * l2 >> 18));
          paramArrayOfi1[i7].f = ((short)(int)(locali1.f * l1 + locali2.f * l2 >> 18));
          paramArrayOfi1[i7].h = ((short)(int)(locali1.h * l1 + locali2.h * l2 >> 18));
          i7 = (byte)(i7 + 1);
        }
      }
      if (i7 == 0) {
        return 0;
      }
      if (i8 == 0) {
        i1 = 0;
      }
      i[] arrayOfi = paramArrayOfi1;
      paramArrayOfi1 = paramArrayOfi2;
      paramArrayOfi2 = arrayOfi;
      i2 = i7;
    }
    return i7;
  }
  
  private static int a(i[] paramArrayOfi1, i[] paramArrayOfi2, int paramInt1, int paramInt2)
  {
    int[] arrayOfInt1 = aO;
    int i2 = 0;
    int i5 = paramInt2 * 9;
    int[] arrayOfInt2 = el;
    int i6 = cB;
    for (int i1 = 0; i1 < paramInt2; i1++)
    {
      i locali1 = paramArrayOfi2[i1];
      i locali2 = paramArrayOfi2[arrayOfInt2[(i5 + i1)]];
      int i3 = (int)(locali1.a * -i6 + locali1.c * paramInt1 >> 24);
      int i4 = (int)(locali2.a * -i6 + locali2.c * paramInt1 >> 24);
      if (i3 >= 0)
      {
        paramArrayOfi1[i2].a = locali1.a;
        paramArrayOfi1[i2].b = locali1.b;
        paramArrayOfi1[i2].c = locali1.c;
        paramArrayOfi1[i2].f = locali1.f;
        paramArrayOfi1[i2].h = locali1.h;
        i2++;
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
        paramArrayOfi1[i2].a = ((int)(locali1.a * l1 + locali2.a * l2 >> 18));
        paramArrayOfi1[i2].b = ((int)(locali1.b * l1 + locali2.b * l2 >> 18));
        paramArrayOfi1[i2].c = ((int)(locali1.c * l1 + locali2.c * l2 >> 18));
        paramArrayOfi1[i2].f = ((short)(int)(locali1.f * l1 + locali2.f * l2 >> 18));
        paramArrayOfi1[i2].h = ((short)(int)(locali1.h * l1 + locali2.h * l2 >> 18));
        i2++;
      }
    }
    return i2;
  }
  
  private static int b(i[] paramArrayOfi1, i[] paramArrayOfi2, int paramInt1, int paramInt2)
  {
    int[] arrayOfInt1 = aO;
    int i2 = 0;
    int i5 = paramInt2 * 9;
    int[] arrayOfInt2 = el;
    int i6 = cB;
    for (int i1 = 0; i1 < paramInt2; i1++)
    {
      i locali1 = paramArrayOfi2[i1];
      i locali2 = paramArrayOfi2[arrayOfInt2[(i5 + i1)]];
      int i3 = (int)(locali1.b * -i6 + locali1.c * paramInt1 >> 24);
      int i4 = (int)(locali2.b * -i6 + locali2.c * paramInt1 >> 24);
      if (i3 >= 0)
      {
        paramArrayOfi1[i2].a = locali1.a;
        paramArrayOfi1[i2].b = locali1.b;
        paramArrayOfi1[i2].c = locali1.c;
        paramArrayOfi1[i2].f = locali1.f;
        paramArrayOfi1[i2].h = locali1.h;
        i2++;
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
        paramArrayOfi1[i2].a = ((int)(locali1.a * l1 + locali2.a * l2 >> 18));
        paramArrayOfi1[i2].b = ((int)(locali1.b * l1 + locali2.b * l2 >> 18));
        paramArrayOfi1[i2].c = ((int)(locali1.c * l1 + locali2.c * l2 >> 18));
        paramArrayOfi1[i2].f = ((short)(int)(locali1.f * l1 + locali2.f * l2 >> 18));
        paramArrayOfi1[i2].h = ((short)(int)(locali1.h * l1 + locali2.h * l2 >> 18));
        i2++;
      }
    }
    return i2;
  }
  
  private static int c(i[] paramArrayOfi1, i[] paramArrayOfi2, int paramInt1, int paramInt2)
  {
    int[] arrayOfInt1 = aO;
    int i2 = 0;
    int i5 = paramInt2 * 9;
    int[] arrayOfInt2 = el;
    int i6 = cB;
    for (int i1 = 0; i1 < paramInt2; i1++)
    {
      i locali1 = paramArrayOfi2[i1];
      i locali2 = paramArrayOfi2[arrayOfInt2[(i5 + i1)]];
      int i3 = (int)(locali1.a * i6 + locali1.c * paramInt1 >> 24);
      int i4 = (int)(locali2.a * i6 + locali2.c * paramInt1 >> 24);
      if (i3 >= 0)
      {
        paramArrayOfi1[i2].a = locali1.a;
        paramArrayOfi1[i2].b = locali1.b;
        paramArrayOfi1[i2].c = locali1.c;
        paramArrayOfi1[i2].f = locali1.f;
        paramArrayOfi1[i2].h = locali1.h;
        i2++;
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
        paramArrayOfi1[i2].a = ((int)(locali1.a * l1 + locali2.a * l2 >> 18));
        paramArrayOfi1[i2].b = ((int)(locali1.b * l1 + locali2.b * l2 >> 18));
        paramArrayOfi1[i2].c = ((int)(locali1.c * l1 + locali2.c * l2 >> 18));
        paramArrayOfi1[i2].f = ((short)(int)(locali1.f * l1 + locali2.f * l2 >> 18));
        paramArrayOfi1[i2].h = ((short)(int)(locali1.h * l1 + locali2.h * l2 >> 18));
        i2++;
      }
    }
    return i2;
  }
  
  private static int d(i[] paramArrayOfi1, i[] paramArrayOfi2, int paramInt1, int paramInt2)
  {
    int[] arrayOfInt1 = aO;
    int i2 = 0;
    int i5 = paramInt2 * 9;
    int[] arrayOfInt2 = el;
    int i6 = cB;
    for (int i1 = 0; i1 < paramInt2; i1++)
    {
      i locali1 = paramArrayOfi2[i1];
      i locali2 = paramArrayOfi2[arrayOfInt2[(i5 + i1)]];
      int i3 = (int)(locali1.b * i6 + locali1.c * paramInt1 >> 24);
      int i4 = (int)(locali2.b * i6 + locali2.c * paramInt1 >> 24);
      if (i3 >= 0)
      {
        paramArrayOfi1[i2].a = locali1.a;
        paramArrayOfi1[i2].b = locali1.b;
        paramArrayOfi1[i2].c = locali1.c;
        paramArrayOfi1[i2].f = locali1.f;
        paramArrayOfi1[i2].h = locali1.h;
        i2++;
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
        paramArrayOfi1[i2].a = ((int)(locali1.a * l1 + locali2.a * l2 >> 18));
        paramArrayOfi1[i2].b = ((int)(locali1.b * l1 + locali2.b * l2 >> 18));
        paramArrayOfi1[i2].c = ((int)(locali1.c * l1 + locali2.c * l2 >> 18));
        paramArrayOfi1[i2].f = ((short)(int)(locali1.f * l1 + locali2.f * l2 >> 18));
        paramArrayOfi1[i2].h = ((short)(int)(locali1.h * l1 + locali2.h * l2 >> 18));
        i2++;
      }
    }
    return i2;
  }
  
  private static final boolean a(int[][] paramArrayOfInt, g paramg)
  {
    int[] arrayOfInt1 = aA;
    int[] arrayOfInt2 = dn;
    l locall = g[paramg.s];
    int i1 = (int)((dg[0] - paramg.m) * arrayOfInt1[df] - (dg[1] - paramg.n) * arrayOfInt2[df] >> 16);
    int i2 = (int)((dg[0] - paramg.m) * arrayOfInt2[df] + (dg[1] - paramg.n) * arrayOfInt1[df] >> 16);
    int i3 = (int)((dg[2] - paramg.o) * arrayOfInt1[dd] - i2 * arrayOfInt2[dd] >> 16);
    i2 = (int)((dg[2] - paramg.o) * arrayOfInt2[dd] + i2 * arrayOfInt1[dd] >> 16);
    i1 >>= 16;
    i2 >>= 16;
    return ((i3 >>= 16) * paramArrayOfInt[0][2] <= 0L) || (i2 * paramArrayOfInt[1][1] + i3 * paramArrayOfInt[1][2] <= -locall.c) || (i2 * paramArrayOfInt[2][1] + i3 * paramArrayOfInt[2][2] <= -locall.c) || (i1 * paramArrayOfInt[3][0] + i3 * paramArrayOfInt[3][2] <= -locall.d) || (i1 * paramArrayOfInt[4][0] + i3 * paramArrayOfInt[4][2] <= -locall.d);
  }
  
  final void c()
  {
    this.bg = true;
    cn = 0;
    cj = this.dI;
    cU = 0;
    cT = 0;
    for (int i1 = 0; i1 < dv.length; i1++) {
      dv[i1] = -1;
    }
  }
  
  private static String a(String paramString)
  {
    if (paramString != null)
    {
      do
      {
        paramString = paramString.substring(1, paramString.length());
        if (paramString.length() <= 0) {
          break;
        }
      } while (paramString.charAt(0) == ' ');
      while ((paramString.length() > 0) && (paramString.charAt(paramString.length() - 1) == ' ')) {
        paramString = paramString.substring(0, paramString.length() - 1);
      }
    }
    return paramString;
  }
  
  private final void b(String paramString)
  {
    try
    {
      this.bT = e.a(paramString, this.bi, this.aV, true);
      this.aR = 0;
      return;
    }
    catch (Exception localException)
    {
      this.bT = null;
    }
  }
  
  private final void y()
  {
    int i1;
    if ((i1 = (i1 = (ce) && (this.cg != 1) && (this.cg != 13) && (this.cg != 9) ? 1 : 0) | this.bO) != 0)
    {
      this.aT = 0L;
      this.bT = null;
      return;
    }
    if (this.bT != null) {
      return;
    }
    long l1 = 65777L;
    long l2 = System.currentTimeMillis();
    if ((this.aT == 0L) || (this.aT > l2)) {
      this.aT = l2;
    }
    if (l2 < this.aT + l1) {
      return;
    }
    if (this.aT > 2L) {
      this.bB += 1;
    }
    this.aT = 2L;
    this.aT = 0L;
    this.aZ = D();
    this.bh = true;
    C();
    this.aE = (System.currentTimeMillis() + 1500L);
  }
  
  public final void a(int[] paramArrayOfInt, int paramInt)
  {
    int[] arrayOfInt1 = new int[4];
    int i1 = l[paramInt].q;
    int[] arrayOfInt2 = null;
    int[] arrayOfInt3 = aQ;
    int i2 = 0;
    int i3 = 0;
    do
    {
      arrayOfInt2 = l[paramInt].p;
      if ((i2 = a(paramArrayOfInt, arrayOfInt2[i1], arrayOfInt3, paramInt)) >= 0)
      {
        i3 = aP - 5;
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
    int[][] arrayOfInt = { { 0, 0, 1 }, { 0, -cB, 0 }, { 0, cB, 0 }, { cB, 0, 0 }, { -cB, 0, 0 } };
    int i1 = this.cl;
    if ((cn == 3) || (cn == 4)) {
      if (i1 == 2) {
        A();
      } else {
        z();
      }
    }
    for (int i2 = j.length - 1; i2 >= 0; i2--) {
      j[i2].e = false;
    }
    for (int i3 = aP - 5; i3 >= 0; i3 -= 5)
    {
      arrayOfInt[1][2] = paramArrayOfInt[i3];
      arrayOfInt[2][2] = paramArrayOfInt[(i3 + 1)];
      arrayOfInt[3][2] = paramArrayOfInt[(i3 + 2)];
      arrayOfInt[4][2] = paramArrayOfInt[(i3 + 3)];
      if ((paramArrayOfInt[(i3 + 4)] == 999) || (paramArrayOfInt[(i3 + 4)] < 0))
      {
        if (i1 == 2) {
          a(arrayOfInt, true);
        } else {
          a(arrayOfInt, false);
        }
      }
      else {
        a(paramArrayOfInt[(i3 + 4)], arrayOfInt);
      }
    }
    a(cY, cL);
    aP = 0;
    j localj;
    if ((localj = n[0]).e > 0)
    {
      if (localj.e > 255) {
        a(0, 0, 240, 260, 16777215, 255);
      } else {
        a(0, 0, 240, 260, 16777215, localj.e);
      }
    }
    else if (eh > 0) {
      a(0, 0, 240, 260, 16711680, eh);
    }
  }
  
  private static final void a(i parami1, i parami2, i parami3, int paramInt1, int paramInt2)
  {
    byte[] arrayOfByte = dL[bx];
    int[] arrayOfInt1 = cG[bx];
    int[] arrayOfInt2 = aN;
    int[] arrayOfInt3 = az;
    int i2 = parami1.e * 240;
    int i6 = parami1.d << 16;
    int i7 = parami2.d << 16;
    int i8 = parami1.d << 16;
    int i9 = parami1.f << 16;
    int i10 = parami2.f << 16;
    int i11 = parami1.f << 16;
    int i12 = parami1.h << 16;
    int i13 = parami2.h << 16;
    int i14 = parami1.h << 16;
    int i15 = (parami3.d - parami1.d) * arrayOfInt3[(parami3.e - parami1.e)];
    int i16 = (parami2.d - parami1.d) * arrayOfInt3[(parami2.e - parami1.e)];
    int i17 = (parami3.d - parami2.d) * arrayOfInt3[(parami3.e - parami2.e)];
    int i18 = (parami3.f - parami1.f) * arrayOfInt3[(parami3.e - parami1.e)];
    int i19 = (parami2.f - parami1.f) * arrayOfInt3[(parami2.e - parami1.e)];
    int i20 = (parami3.f - parami2.f) * arrayOfInt3[(parami3.e - parami2.e)];
    int i21 = (parami3.h - parami1.h) * arrayOfInt3[(parami3.e - parami1.e)];
    int i22 = (parami2.h - parami1.h) * arrayOfInt3[(parami2.e - parami1.e)];
    int i23 = (parami3.h - parami2.h) * arrayOfInt3[(parami3.e - parami2.e)];
    int i5;
    int i24;
    int i25;
    int i4;
    int i3;
    int i1;
    int i26;
    int i27;
    if (i15 < i16) {
      for (i5 = parami1.e; i5 <= parami2.e; i5++)
      {
        i24 = i9;
        i25 = i12;
        i4 = i2 + (i6 >> 16);
        i3 = i(i8 - i6);
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
      for (i5 = parami1.e; i5 <= parami2.e; i5++)
      {
        i26 = i11;
        i27 = i14;
        i4 = i2 + (i8 >> 16);
        i3 = i(i6 - i8);
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
      while (i5 < parami3.e)
      {
        i24 = i9;
        i25 = i12;
        i4 = i2 + (i6 >> 16);
        i3 = i(i7 - i6);
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
    while (i5 < parami3.e)
    {
      i26 = i10;
      i27 = i13;
      i4 = i2 + (i7 >> 16);
      i3 = i(i6 - i7);
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
    int[][] arrayOfInt1 = dA;
    int[][] arrayOfInt2 = dk;
    int[][] arrayOfInt3 = ej;
    int i1 = cA;
    g[] arrayOfg = h;
    int[] arrayOfInt4 = null;
    i[] arrayOfi1 = br;
    i[] arrayOfi2 = bl;
    int[] arrayOfInt6 = by;
    int[] arrayOfInt7 = bz;
    int i8 = cz;
    int i9 = dz;
    int i10 = dl;
    int[] arrayOfInt8 = dn;
    int[] arrayOfInt9 = aA;
    for (int i11 = paramInt - 1; i11 >= 0; i11--)
    {
      int i7;
      int[] arrayOfInt5;
      int i6;
      if (arrayOfInt6[i11] >= i10)
      {
        i7 = arrayOfInt6[i11] - i10;
        arrayOfInt5 = arrayOfg[i1].b;
        arrayOfInt4 = arrayOfg[i1].a;
        i6 = arrayOfg[i1].b.length >> 4;
        arrayOfg[i1].m = arrayOfInt2[i7][0];
        arrayOfg[i1].n = arrayOfInt2[i7][1];
        arrayOfg[i1].o = arrayOfInt2[i7][2];
        arrayOfg[i1].p = arrayOfInt2[i7][9];
        arrayOfg[i1].q = arrayOfInt2[i7][10];
        g.a(arrayOfg[i1]);
        i7 = i1;
      }
      else
      {
        if (arrayOfInt6[i11] >= i9)
        {
          i7 = arrayOfInt6[i11] - i9;
          a(arrayOfInt3[arrayOfInt1[i7][3]][(arrayOfInt1[i7][4] - 1)], arrayOfInt1[i7][0], arrayOfInt1[i7][1], arrayOfInt1[i7][2], paramArrayOfInt);
          continue;
        }
        if (arrayOfInt6[i11] >= i8)
        {
          i7 = arrayOfInt6[i11] - i8;
          arrayOfInt5 = arrayOfg[i7].b;
          arrayOfInt4 = arrayOfg[i7].a;
          i6 = arrayOfg[i7].b.length >> 4;
          if (a(paramArrayOfInt, arrayOfg[i7])) {
            continue;
          }
          g.a(arrayOfg[i7]);
        }
        else
        {
          i7 = arrayOfInt6[i11];
          if (n[i7].n)
          {
            a(i7, n[i7].p, n[i7].q, n[i7].r, paramArrayOfInt, true);
            continue;
          }
          a(i7, n[i7].p, n[i7].q, n[i7].r, paramArrayOfInt, false);
          continue;
        }
      }
      a(arrayOfInt5, arrayOfInt4);
      int i13 = 0;
      int i14 = 1;
      if ((arrayOfg[i7].s == 45) || (arrayOfg[i7].s == 46)) {
        i13 = 1;
      }
      if (arrayOfg[i7].s == 51)
      {
        i13 = 1;
        i14 = 0;
      }
      bx = arrayOfInt5[9];
      for (int i15 = i6 - 1; i15 >= 0; i15--)
      {
        int i12 = arrayOfInt7[i15] << 4;
        int i3 = arrayOfInt5[(i12 + 13)];
        int i4 = arrayOfInt5[(i12 + 14)];
        int i5 = arrayOfInt5[(i12 + 15)];
        arrayOfInt5[(i12 + 13)] = ((int)(i3 * arrayOfInt9[df] - i4 * arrayOfInt8[df] >> 16));
        arrayOfInt5[(i12 + 14)] = ((int)(i3 * arrayOfInt8[df] + i4 * arrayOfInt9[df] >> 16));
        arrayOfInt5[(i12 + 15)] = ((int)(i5 * arrayOfInt9[dd] - arrayOfInt5[(i12 + 14)] * arrayOfInt8[dd] >> 16));
        arrayOfInt5[(i12 + 14)] = ((int)(i5 * arrayOfInt8[dd] + arrayOfInt5[(i12 + 14)] * arrayOfInt9[dd] >> 16));
        if ((i14 == 0) || (arrayOfInt5[(i12 + 13)] * arrayOfInt4[(arrayOfInt5[i12] + 3)] + arrayOfInt5[(i12 + 14)] * arrayOfInt4[(arrayOfInt5[i12] + 4)] + arrayOfInt5[(i12 + 15)] * arrayOfInt4[(arrayOfInt5[i12] + 5)] > 0L))
        {
          arrayOfi1[0].a = arrayOfInt4[(arrayOfInt5[i12] + 3)];
          arrayOfi1[0].b = arrayOfInt4[(arrayOfInt5[i12] + 4)];
          arrayOfi1[0].c = arrayOfInt4[(arrayOfInt5[i12] + 5)];
          arrayOfi1[1].a = arrayOfInt4[(arrayOfInt5[(i12 + 1)] + 3)];
          arrayOfi1[1].b = arrayOfInt4[(arrayOfInt5[(i12 + 1)] + 4)];
          arrayOfi1[1].c = arrayOfInt4[(arrayOfInt5[(i12 + 1)] + 5)];
          arrayOfi1[2].a = arrayOfInt4[(arrayOfInt5[(i12 + 2)] + 3)];
          arrayOfi1[2].b = arrayOfInt4[(arrayOfInt5[(i12 + 2)] + 4)];
          arrayOfi1[2].c = arrayOfInt4[(arrayOfInt5[(i12 + 2)] + 5)];
          arrayOfi1[0].f = ((short)arrayOfInt5[(i12 + 3)]);
          arrayOfi1[0].h = ((short)arrayOfInt5[(i12 + 4)]);
          arrayOfi1[1].f = ((short)arrayOfInt5[(i12 + 5)]);
          arrayOfi1[1].h = ((short)arrayOfInt5[(i12 + 6)]);
          arrayOfi1[2].f = ((short)arrayOfInt5[(i12 + 7)]);
          arrayOfi1[2].h = ((short)arrayOfInt5[(i12 + 8)]);
          byte tmp1070_1068 = (i2 = a(arrayOfi2, arrayOfi1, paramArrayOfInt));
          int i2 = (byte)(tmp1070_1068 - 1);
          if (tmp1070_1068 != 0) {
            if (i13 == 0)
            {
              i2 = (byte)(i2 - 1);
              while ((i2 = (byte)(i2 - 1)) >= 0) {
                a(arrayOfi2[0], arrayOfi2[(i2 + 1)], arrayOfi2[(i2 + 2)]);
              }
            }
            else
            {
              bx = arrayOfInt5[(i12 + 9)];
              i2 = (byte)(i2 - 1);
              while ((i2 = (byte)(i2 - 1)) >= 0) {
                b(arrayOfi2[0], arrayOfi2[(i2 + 1)], arrayOfi2[(i2 + 2)]);
              }
            }
          }
        }
      }
    }
  }
  
  final void d()
  {
    this.dC = 40;
    this.ba = true;
    while (this.dC >= 0)
    {
      long l1 = System.currentTimeMillis();
      repaint();
      serviceRepaints();
      long l2;
      long l3 = (l2 = System.currentTimeMillis()) - l1;
      long l4 = this.dF;
      if (l3 < l4) {
        try
        {
          Thread.sleep(l4 - l3);
        }
        catch (Exception localException1) {}
      }
      this.dC = ((byte)(this.dC - 2));
    }
    try
    {
      Thread.sleep(1000L);
    }
    catch (Exception localException2) {}
    this.ba = false;
  }
  
  private void a(Graphics paramGraphics)
  {
    paramGraphics.setColor(0);
    paramGraphics.fillRect(0, 0, 240, 320);
    paramGraphics.setColor(16711680);
    this.bc = false;
  }
  
  private static void z()
  {
    int i1 = 0;
    int[] arrayOfInt = aN;
    for (int i2 = 0; i2 < 130; i2++)
    {
      for (int i3 = 0; i3 < 240; i3++) {
        arrayOfInt[(i1 + i3)] = 11002879;
      }
      i1 += 240;
    }
  }
  
  private final void a(int[][] paramArrayOfInt, boolean paramBoolean)
  {
    int[] arrayOfInt1 = aN;
    byte[] arrayOfByte = dN;
    int[] arrayOfInt2 = cI;
    if (paramArrayOfInt[0][2] > 130) {
      paramArrayOfInt[0][2] = '';
    }
    if (paramArrayOfInt[1][2] > 130) {
      paramArrayOfInt[1][2] = '';
    }
    if (paramArrayOfInt[2][2] >= 120) {
      paramArrayOfInt[2][2] = 119;
    }
    if (paramArrayOfInt[3][2] >= 120) {
      paramArrayOfInt[3][2] = 119;
    }
    int i3 = 130 - paramArrayOfInt[1][2];
    int i4 = 130 + paramArrayOfInt[2][2];
    int i5 = 120 - paramArrayOfInt[3][2];
    int i6 = 120 + paramArrayOfInt[4][2];
    if (i5 < 0) {
      i5 = 0;
    }
    if (i3 < 0) {
      i3 = 0;
    }
    int i7 = cM;
    int i8 = this.ds - 1;
    int i9 = this.ds;
    int i2;
    if (paramBoolean)
    {
      if (i3 > this.dq - 1) {
        return;
      }
      if (i4 > this.dq - 1) {
        i4 = this.dq - 1;
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
  
  private final void b(Graphics paramGraphics)
  {
    int i1 = 240 - af * (ax[26][2] + 2) >> 1;
    int i2 = 0;
    int i3 = 0;
    if (this.ch > 0) {
      this.ch -= 1;
    }
    i3 = this.ch & 0x1;
    paramGraphics.setColor(0);
    paramGraphics.fillRect(0, 288, 240, 34);
    paramGraphics.fillRect(0, 0, 240, 30);
    for (int i4 = 1; i4 < 4; i4++) {
      if ((dt[i4] != 0) && ((ai[i4] != 0) || (aj[i4] != 0))) {
        if ((this.du == i4) && (i3 == 1))
        {
          i2++;
        }
        else
        {
          a(paramGraphics, dw == i4 ? 25 + i4 : 21 + i4, i1 + i2 * (ax[26][2] + 3), 30 - ax[26][3] >> 1);
          i2++;
        }
      }
    }
    a(paramGraphics, 2, 297);
    paramGraphics.setColor(12207616);
    paramGraphics.drawLine(0, 291, 240, 291);
    paramGraphics.drawLine(0, 318, 240, 318);
    paramGraphics.drawLine(0, 292, 0, 296);
    paramGraphics.drawLine(0, 317, 0, 313);
    if (dw == 0) {
      a(paramGraphics, 25, 240 - ax[21][2], 320 - (30 + ax[21][3] >> 1) - 1);
    } else {
      a(paramGraphics, 21 + dw, 240 - ax[21][2], 320 - (30 + ax[21][3] >> 1) - 1);
    }
    if (as)
    {
      this.bi.a(paramGraphics, aM + "", 0, 0, 20);
      this.bi.a(paramGraphics, this.cF + ae + "", 0, 22, 20);
    }
    if (((this.du != dw) || (i3 != 1)) && (dw != 0)) {
      this.bi.a(paramGraphics, ai[dw] + "/ " + aj[dw], 240 - ax[26][2] - this.bi.a(ai[dw] + "/ " + aj[dw] + " ") - 1, 320 - (this.bi.b() + 30 >> 1), 20);
    }
    a(paramGraphics, "" + n[0].m, 25, 320 - (30 + this.c >> 1));
    if (bn != 0)
    {
      bn = (byte)(bn - 1);
      if (bn > 3)
      {
        String[] arrayOfString = this.bq[this.bm];
        for (int i6 = 0; i6 < arrayOfString.length; i6++) {
          this.bi.a(paramGraphics, arrayOfString[i6], 240 - this.bi.a(arrayOfString[i6]) >> 1, 290 - this.bi.b() * (arrayOfString.length - i6), 20);
        }
      }
    }
    int i5 = aG >> 1;
    paramGraphics.setColor(16777215);
    paramGraphics.drawLine(120, 152 - i5, 120, 157 - i5);
    paramGraphics.drawLine(120, 168 + i5, 120, 163 + i5);
    paramGraphics.drawLine(112 - i5, 160, 117 - i5, 160);
    paramGraphics.drawLine(128 + i5, 160, 123 + i5, 160);
    ae = 0;
  }
  
  private static void a(Graphics paramGraphics, int paramInt1, int paramInt2)
  {
    paramGraphics.setColor(2949120);
    paramGraphics.fillRect(paramInt1, paramInt2, 19, 17);
    paramGraphics.setColor(15007744);
    paramGraphics.drawRect(paramInt1 + 7, paramInt2 + 2, 4, 5);
    paramGraphics.drawRect(paramInt1 + 3, paramInt2 + 6, 5, 4);
    paramGraphics.drawRect(paramInt1 + 7, paramInt2 + 9, 4, 5);
    paramGraphics.drawRect(paramInt1 + 10, paramInt2 + 6, 5, 4);
    paramGraphics.setColor(0);
    paramGraphics.fillRect(paramInt1 + 8, paramInt2 + 3, 3, 11);
    paramGraphics.fillRect(paramInt1 + 4, paramInt2 + 7, 11, 3);
  }
  
  private void c(Graphics paramGraphics)
  {
    paramGraphics.setColor(0);
    paramGraphics.fillRect(0, 0, 240, 320);
    if (this.bQ != null)
    {
      i1 = 120 - (this.bQ.getHeight() >> 1);
      if (this.bP < 0) {
        i1 = 160 - (this.bQ.getHeight() >> 1);
      }
      paramGraphics.drawImage(this.bQ, 120 - (this.bQ.getWidth() >> 1), i1, 20);
    }
    if (this.bP == -1) {
      this.bi.a(paramGraphics, this.bN, 240 - this.bi.a(this.bN) >> 1, 320 - this.bi.b() >> 1, 20);
    }
    if (this.bP < 0) {
      return;
    }
    int i1 = (240 - (this.cE.getWidth() << 2)) / (this.cE.getWidth() + 2);
    int i2 = 120 - (i1 * (this.cE.getWidth() + 2) >> 1);
    i1 = i1 * this.bP / 100;
    for (int i3 = 0; i3 < i1; i3++) {
      paramGraphics.drawImage(this.cE, i2 + (this.cE.getWidth() + 2) * i3, 320 - this.cE.getHeight() - (this.cE.getHeight() >> 1), 20);
    }
    paramGraphics.drawImage(this.bw, 120 - (this.bw.getWidth() >> 1), 320 - this.cE.getHeight() - this.cE.getHeight() - this.bw.getHeight(), 20);
  }
  
  private void d(Graphics paramGraphics)
  {
    if (this.bw != null)
    {
      paramGraphics.drawImage(this.bw, 120 - (this.bw.getWidth() >> 1), 160 - (this.bw.getHeight() >> 1), 20);
      this.bw = null;
    }
    if (this.cu != null)
    {
      paramGraphics.drawImage(this.cu, 120 - (this.cu.getWidth() >> 1), 320 - this.cu.getHeight(), 20);
      this.cu = null;
    }
    if (this.cE != null)
    {
      int i1 = (240 - (this.cE.getWidth() << 2)) / (this.cE.getWidth() + 2);
      int i2 = 120 - (i1 * (this.cE.getWidth() + 2) >> 1);
      i1 = i1 * this.bP / 100;
      for (int i3 = 0; i3 < i1; i3++) {
        paramGraphics.drawImage(this.cE, i2 + (this.cE.getWidth() + 2) * i3, 320 - this.cE.getHeight() - this.dE - (this.bi.b() >> 1), 20);
      }
    }
    else
    {
      paramGraphics.setColor(16711680);
      paramGraphics.fillRect(0, 315, 240 * this.bP / 100, 5);
    }
    this.bi.a(paramGraphics, this.bN, 120 - (this.bi.a(this.bN) >> 1), 320 - this.cE.getHeight() - this.dE - (this.bi.b() << 1), 20);
  }
  
  private void e(Graphics paramGraphics)
  {
    int i1 = 130 * (40 - this.dC) / 40;
    int i2;
    if ((i2 = 130 - ((this.cd.N + 1) * this.cd.v + this.bi.b() >> 1)) > i1)
    {
      a(0, 0, 240, i1, 0, 32);
      a(0, 260 - i1, 240, i1, 0, 32);
    }
    else
    {
      a(0, 0, 240, i2, 0, 32);
      a(0, 260 - i2, 240, i2, 0, 32);
      a(0, 0, 3, i1, 0, 32);
      a(237, 0, 3, i1, 0, 32);
      a(0, 260 - i1, 3, i1, 0, 32);
      a(237, 260 - i1, 3, i1, 0, 32);
    }
    paramGraphics.drawRGB(aN, 0, 240, 0, 30, 240, 258, false);
    this.cd.a(paramGraphics, this.cg);
  }
  
  private static final void a(i parami1, i parami2, i parami3)
  {
    ae += 1;
    int[] arrayOfInt1 = az;
    int[] arrayOfInt2 = aO;
    int i1 = cC;
    parami1.d = ((short)(int)(7864320L + parami1.a * i1 / parami1.c >> 16));
    parami1.e = ((short)(int)(8519680L - parami1.b * i1 / parami1.c >> 16));
    parami2.d = ((short)(int)(7864320L + parami2.a * i1 / parami2.c >> 16));
    parami2.e = ((short)(int)(8519680L - parami2.b * i1 / parami2.c >> 16));
    parami3.d = ((short)(int)(7864320L + parami3.a * i1 / parami3.c >> 16));
    parami3.e = ((short)(int)(8519680L - parami3.b * i1 / parami3.c >> 16));
    i locali;
    if (parami1.e > parami2.e)
    {
      locali = parami1;
      parami1 = parami2;
      parami2 = locali;
    }
    if (parami1.e > parami3.e)
    {
      locali = parami1;
      parami1 = parami3;
      parami3 = locali;
    }
    if (parami2.e > parami3.e)
    {
      locali = parami2;
      parami2 = parami3;
      parami3 = locali;
    }
    int i2;
    if ((i2 = parami1.c >> 16) < 0) {
      parami1.m = (-arrayOfInt2[(-i2)]);
    } else {
      parami1.m = arrayOfInt2[i2];
    }
    parami1.g = (parami1.f * parami1.m);
    parami1.i = (parami1.h * parami1.m);
    if ((i2 = parami2.c >> 16) < 0) {
      parami2.m = (-arrayOfInt2[(-i2)]);
    } else {
      parami2.m = arrayOfInt2[i2];
    }
    parami2.g = (parami2.f * parami2.m);
    parami2.i = (parami2.h * parami2.m);
    if ((i2 = parami3.c >> 16) < 0) {
      parami3.m = (-arrayOfInt2[(-i2)]);
    } else {
      parami3.m = arrayOfInt2[i2];
    }
    parami3.g = (parami3.f * parami3.m);
    parami3.i = (parami3.h * parami3.m);
    int i3 = (parami2.e - parami1.e) * arrayOfInt1[(parami3.e - parami1.e)];
    int i4;
    int i5;
    int i6;
    if ((i2 = parami1.d + (int)((parami3.d - parami1.d) * i3 >> 16) - parami2.d) < 0)
    {
      i2 = -i2;
      i4 = -(int)((parami1.g + (int)((parami3.g - parami1.g) * i3 >> 16) - parami2.g) * arrayOfInt1[i2] >> 12);
      i5 = -(int)((parami1.i + (int)((parami3.i - parami1.i) * i3 >> 16) - parami2.i) * arrayOfInt1[i2] >> 12);
      i6 = -(int)((parami1.m + (int)((parami3.m - parami1.m) * i3 >> 16) - parami2.m) * arrayOfInt1[i2] >> 12);
    }
    else
    {
      i4 = (int)((parami1.g + (int)((parami3.g - parami1.g) * i3 >> 16) - parami2.g) * arrayOfInt1[i2] >> 12);
      i5 = (int)((parami1.i + (int)((parami3.i - parami1.i) * i3 >> 16) - parami2.i) * arrayOfInt1[i2] >> 12);
      i6 = (int)((parami1.m + (int)((parami3.m - parami1.m) * i3 >> 16) - parami2.m) * arrayOfInt1[i2] >> 12);
    }
    if ((parami3.d - parami1.d) * arrayOfInt2[(parami3.e - parami1.e)] < (parami2.d - parami1.d) * arrayOfInt2[(parami2.e - parami1.e)]) {
      a(parami1, parami2, parami3, i4, i5, i6);
    } else {
      c(parami1, parami2, parami3, i4, i5, i6);
    }
    if ((parami3.d - parami1.d) * arrayOfInt2[(parami3.e - parami1.e)] > (parami3.d - parami2.d) * arrayOfInt2[(parami3.e - parami2.e)])
    {
      e(parami1, parami2, parami3, i4, i5, i6);
      return;
    }
    g(parami1, parami2, parami3, i4, i5, i6);
  }
  
  private static final void b(i parami1, i parami2, i parami3)
  {
    ae += 1;
    int[] arrayOfInt = az;
    int i1 = cC;
    parami1.d = ((short)(int)(7864320L + parami1.a * i1 / parami1.c >> 16));
    parami1.e = ((short)(int)(8519680L - parami1.b * i1 / parami1.c >> 16));
    parami2.d = ((short)(int)(7864320L + parami2.a * i1 / parami2.c >> 16));
    parami2.e = ((short)(int)(8519680L - parami2.b * i1 / parami2.c >> 16));
    parami3.d = ((short)(int)(7864320L + parami3.a * i1 / parami3.c >> 16));
    parami3.e = ((short)(int)(8519680L - parami3.b * i1 / parami3.c >> 16));
    i locali;
    if (parami1.e > parami2.e)
    {
      locali = parami1;
      parami1 = parami2;
      parami2 = locali;
    }
    if (parami1.e > parami3.e)
    {
      locali = parami1;
      parami1 = parami3;
      parami3 = locali;
    }
    if (parami2.e > parami3.e)
    {
      locali = parami2;
      parami2 = parami3;
      parami3 = locali;
    }
    int i2 = (parami2.e - parami1.e) * arrayOfInt[(parami3.e - parami1.e)];
    int i3;
    if ((i3 = parami1.d + ((parami3.d - parami1.d) * i2 >> 16) - parami2.d) < 0)
    {
      a(parami1, parami2, parami3, -(parami1.f + ((parami3.f - parami1.f) * i2 >> 16) - parami2.f) * arrayOfInt[(-i3)], -(parami1.h + ((parami3.h - parami1.h) * i2 >> 16) - parami2.h) * arrayOfInt[(-i3)]);
      return;
    }
    a(parami1, parami2, parami3, (parami1.f + ((parami3.f - parami1.f) * i2 >> 16) - parami2.f) * arrayOfInt[i3], (parami1.h + ((parami3.h - parami1.h) * i2 >> 16) - parami2.h) * arrayOfInt[i3]);
  }
  
  private static final void c(i parami1, i parami2, i parami3)
  {
    ae += 1;
    int[] arrayOfInt1 = az;
    int[] arrayOfInt2 = aO;
    a(parami1);
    a(parami2);
    a(parami3);
    i locali;
    if (parami1.e > parami2.e)
    {
      locali = parami1;
      parami1 = parami2;
      parami2 = locali;
    }
    if (parami1.e > parami3.e)
    {
      locali = parami1;
      parami1 = parami3;
      parami3 = locali;
    }
    if (parami2.e > parami3.e)
    {
      locali = parami2;
      parami2 = parami3;
      parami3 = locali;
    }
    int i1;
    if ((i1 = parami1.c >> 16) < 0) {
      parami1.m = (-arrayOfInt2[(-i1)]);
    } else {
      parami1.m = arrayOfInt2[i1];
    }
    parami1.g = (parami1.f * parami1.m);
    parami1.i = (parami1.h * parami1.m);
    if ((i1 = parami2.c >> 16) < 0) {
      parami2.m = (-arrayOfInt2[(-i1)]);
    } else {
      parami2.m = arrayOfInt2[i1];
    }
    parami2.g = (parami2.f * parami2.m);
    parami2.i = (parami2.h * parami2.m);
    if ((i1 = parami3.c >> 16) < 0) {
      parami3.m = (-arrayOfInt2[(-i1)]);
    } else {
      parami3.m = arrayOfInt2[i1];
    }
    parami3.g = (parami3.f * parami3.m);
    parami3.i = (parami3.h * parami3.m);
    int i2 = (parami2.e - parami1.e) * arrayOfInt1[(parami3.e - parami1.e)];
    int i3;
    int i4;
    int i5;
    if ((i1 = parami1.d + (int)((parami3.d - parami1.d) * i2 >> 16) - parami2.d) < 0)
    {
      i1 = -i1;
      i3 = -(int)((parami1.g + (int)((parami3.g - parami1.g) * i2 >> 16) - parami2.g) * arrayOfInt1[i1] >> 12);
      i4 = -(int)((parami1.i + (int)((parami3.i - parami1.i) * i2 >> 16) - parami2.i) * arrayOfInt1[i1] >> 12);
      i5 = -(int)((parami1.m + (int)((parami3.m - parami1.m) * i2 >> 16) - parami2.m) * arrayOfInt1[i1] >> 12);
    }
    else
    {
      i3 = (int)((parami1.g + (int)((parami3.g - parami1.g) * i2 >> 16) - parami2.g) * arrayOfInt1[i1] >> 12);
      i4 = (int)((parami1.i + (int)((parami3.i - parami1.i) * i2 >> 16) - parami2.i) * arrayOfInt1[i1] >> 12);
      i5 = (int)((parami1.m + (int)((parami3.m - parami1.m) * i2 >> 16) - parami2.m) * arrayOfInt1[i1] >> 12);
    }
    if ((parami3.d - parami1.d) * arrayOfInt2[(parami3.e - parami1.e)] < (parami2.d - parami1.d) * arrayOfInt2[(parami2.e - parami1.e)]) {
      b(parami1, parami2, parami3, i3, i4, i5);
    } else {
      d(parami1, parami2, parami3, i3, i4, i5);
    }
    if ((parami3.d - parami1.d) * arrayOfInt2[(parami3.e - parami1.e)] > (parami3.d - parami2.d) * arrayOfInt2[(parami3.e - parami2.e)])
    {
      f(parami1, parami2, parami3, i3, i4, i5);
      return;
    }
    h(parami1, parami2, parami3, i3, i4, i5);
  }
  
  private static void b(int paramInt1, int paramInt2, int paramInt3, int paramInt4)
  {
    int[] arrayOfInt1 = aN;
    if (an == 0) {
      an = (byte)(an + 1);
    } else {
      an = 0;
    }
    int i1 = an;
    int i3 = paramInt3 >> 1;
    int i4 = 240 * paramInt2 + paramInt1;
    int i5 = i3 * i3;
    int i2;
    for (int i6 = 0; i6 <= paramInt3; i6++)
    {
      for (int i7 = 0; i7 <= paramInt3; i7++)
      {
        i2 = arrayOfInt1[i4];
        if ((i7 - i3) * (i7 - i3) + (i6 - i3) * (i6 - i3) < i5) {
          arrayOfInt1[i4] = (((i2 & 0xFF0000) >> 17 << 16) + ((i2 & 0xFF00) >> 9 << 8) + ((i2 & 0xFF) >> 1));
        }
        i4++;
      }
      i4 += 240 - paramInt3 - 1;
    }
    j[] arrayOfj = n;
    paramInt3 >>= 1;
    int[] arrayOfInt2 = dg;
    int i10 = paramInt1 + i3;
    int i11 = paramInt2 + i3;
    int i12 = (i3 - 2) * (i3 - 2);
    int i13 = aA[(359 - df)];
    int i14 = dn[(359 - df)];
    paramInt3 = paramInt3 * dn[45] >> 16;
    i5 = 240 * i11 + i10;
    for (int i15 = 0; i15 <= paramInt3; i15++)
    {
      arrayOfInt1[(i5 - i15)] = 16776960;
      arrayOfInt1[(i5 + i15)] = 16776960;
      i5 -= 240;
    }
    for (int i16 = 1; i16 < dR; i16++) {
      if (!arrayOfj[i16].k)
      {
        j localj;
        int i8 = -(int)(((localj = arrayOfj[i16]).p - arrayOfInt2[0]) * i13 - (arrayOfInt2[1] - localj.q) * i14 >> 32) >> paramInt4;
        int i9 = -(int)((localj.p - arrayOfInt2[0]) * i14 + (arrayOfInt2[1] - localj.q) * i13 >> 32) >> paramInt4;
        if (i12 > i8 * i8 + i9 * i9)
        {
          i8 += i10;
          i9 += i11;
          if (localj.C < 4) {
            i2 = 16711680;
          } else {
            i2 = 65280;
          }
          i5 = i9 * 240 + i8;
          arrayOfInt1[i5] = i2;
          if (i1 != 0)
          {
            arrayOfInt1[(i5 + 240 + 1)] = i2;
            arrayOfInt1[(i5 + 240 - 1)] = i2;
            arrayOfInt1[(i5 - 240 + 1)] = i2;
            arrayOfInt1[(i5 - 240 - 1)] = i2;
          }
        }
      }
    }
  }
  
  private static final void a(int paramInt, int[][] paramArrayOfInt)
  {
    if (paramArrayOfInt[1][2] > 130) {
      paramArrayOfInt[1][2] = '';
    }
    if (paramArrayOfInt[2][2] > 130) {
      paramArrayOfInt[2][2] = '';
    }
    if (paramArrayOfInt[3][2] > 120) {
      paramArrayOfInt[3][2] = 120;
    }
    b(paramInt, paramArrayOfInt);
    a(paramArrayOfInt, n(paramInt));
  }
  
  private static final void b(int paramInt, int[][] paramArrayOfInt)
  {
    int[] arrayOfInt1 = l[paramInt].a;
    int[] arrayOfInt2 = l[paramInt].b;
    int i1 = l[paramInt].o * 10;
    i[] arrayOfi1 = br;
    i[] arrayOfi2 = bl;
    boolean bool = dJ;
    c(arrayOfInt1, l[paramInt].n);
    for (int i3 = 0; i3 < i1; i3 += 10)
    {
      arrayOfi1[0].a = arrayOfInt1[(arrayOfInt2[i3] + 3)];
      arrayOfi1[0].b = arrayOfInt1[(arrayOfInt2[i3] + 4)];
      arrayOfi1[0].c = arrayOfInt1[(arrayOfInt2[i3] + 5)];
      arrayOfi1[1].a = arrayOfInt1[(arrayOfInt2[(i3 + 1)] + 3)];
      arrayOfi1[1].b = arrayOfInt1[(arrayOfInt2[(i3 + 1)] + 4)];
      arrayOfi1[1].c = arrayOfInt1[(arrayOfInt2[(i3 + 1)] + 5)];
      arrayOfi1[2].a = arrayOfInt1[(arrayOfInt2[(i3 + 2)] + 3)];
      arrayOfi1[2].b = arrayOfInt1[(arrayOfInt2[(i3 + 2)] + 4)];
      arrayOfi1[2].c = arrayOfInt1[(arrayOfInt2[(i3 + 2)] + 5)];
      arrayOfi1[0].f = ((short)arrayOfInt2[(i3 + 3)]);
      arrayOfi1[0].h = ((short)arrayOfInt2[(i3 + 4)]);
      arrayOfi1[1].f = ((short)arrayOfInt2[(i3 + 5)]);
      arrayOfi1[1].h = ((short)arrayOfInt2[(i3 + 6)]);
      arrayOfi1[2].f = ((short)arrayOfInt2[(i3 + 7)]);
      arrayOfi1[2].h = ((short)arrayOfInt2[(i3 + 8)]);
      byte tmp309_307 = (i2 = a(arrayOfi2, arrayOfi1, paramArrayOfInt));
      int i2 = (byte)(tmp309_307 - 1);
      if (tmp309_307 > 0)
      {
        bx = arrayOfInt2[(i3 + 9)];
        if (!bool)
        {
          i2 = (byte)(i2 - 1);
          while ((i2 = (byte)(i2 - 1)) >= 0) {
            a(arrayOfi2[0], arrayOfi2[(i2 + 1)], arrayOfi2[(i2 + 2)]);
          }
        }
        else
        {
          i2 = (byte)(i2 - 1);
          while ((i2 = (byte)(i2 - 1)) >= 0) {
            c(arrayOfi2[0], arrayOfi2[(i2 + 1)], arrayOfi2[(i2 + 2)]);
          }
        }
      }
    }
  }
  
  private final void A()
  {
    int[] arrayOfInt1 = aN;
    byte[] arrayOfByte = dN;
    int[] arrayOfInt2 = cI;
    int i1 = cM * (this.ds << 2) / 360;
    int i2 = this.ds - 1;
    int i3 = 0;
    int i4 = 0;
    int i5 = 130;
    if (130 >= this.dq) {
      i5 = this.dq - 1;
    }
    for (int i6 = 0; i6 < i5; i6++)
    {
      for (int i7 = 0; i7 < 239; i7++) {
        arrayOfInt1[(i4 + i7)] = arrayOfInt2[arrayOfByte[(i3 + (i7 + i1 & i2))]];
      }
      i3 += this.ds;
      i4 += 240;
    }
  }
  
  private static final void a(int paramInt1, int paramInt2, int paramInt3, int paramInt4, int[][] paramArrayOfInt)
  {
    int[] arrayOfInt1 = aN;
    byte[] arrayOfByte = dM[paramInt1];
    int[] arrayOfInt2 = cH;
    int[] arrayOfInt3 = aO;
    i locali1 = new i(null);
    i locali2 = new i(null);
    locali1.j = paramInt2;
    locali1.k = paramInt3;
    locali1.l = paramInt4;
    b(locali1);
    if (locali1.c <= 0) {
      return;
    }
    int i1 = aC[paramInt1][2];
    int i2 = aC[paramInt1][3];
    locali1.a += (aC[paramInt1][4] << 16);
    locali1.b += (aC[paramInt1][5] << 16);
    locali2.c = locali1.c;
    locali1.d = ((short)(int)(120L + locali1.a * cB / locali1.c));
    locali1.e = ((short)(int)(130L - locali1.b * cB / locali1.c));
    locali2.d = ((short)(int)(120L + locali2.a * cB / locali1.c));
    locali2.e = ((short)(int)(130L - locali2.b * cB / locali1.c));
    int i3 = 0;
    int i4 = 0;
    if (paramInt1 == 1) {
      paramInt1 = 3;
    } else {
      paramInt1 = 2;
    }
    int i5 = Math.abs(locali1.e - locali2.e << paramInt1);
    int i6 = Math.abs(locali1.d - locali2.d << paramInt1);
    if ((38400 <= i6) || (38400 <= i5)) {
      return;
    }
    int i7 = i1 * arrayOfInt3[i6];
    int i8 = i2 * arrayOfInt3[i5];
    int i9 = locali2.d - i6;
    int i10 = locali1.e - (i5 >> 1);
    int i11 = i9 + i6;
    int i12 = i10 + i5;
    if ((i9 > paramArrayOfInt[4][2] + 120) || (i10 > paramArrayOfInt[2][2] + 130) || (i11 < 120 - paramArrayOfInt[3][2]) || (i12 < 130 - paramArrayOfInt[1][2])) {
      return;
    }
    if (i9 <= 120 - paramArrayOfInt[3][2])
    {
      i3 = i7 * (120 - paramArrayOfInt[3][2] - i9);
      i9 = 120 - paramArrayOfInt[3][2];
    }
    if (i10 <= 130 - paramArrayOfInt[1][2])
    {
      i4 = i8 * (130 - paramArrayOfInt[1][2] - i10);
      i10 = 130 - paramArrayOfInt[1][2];
    }
    if (i11 >= paramArrayOfInt[4][2] + 120) {
      i11 = paramArrayOfInt[4][2] + 120 - 2;
    }
    if (i12 >= paramArrayOfInt[2][2] + 130) {
      i12 = paramArrayOfInt[2][2] + 130 - 3;
    }
    int i13 = 0;
    int i14 = i4;
    int i15 = i10 * 240 + i9;
    int i17 = i12 - i10;
    int i18 = i11 - i9;
    int i19 = 0;
    int i20 = 0;
    while (i17-- > 0)
    {
      i13 = i3;
      i15 += 240;
      int i16 = i18;
      i19 = i15;
      i5 = (i14 >> 18) * i1;
      while (i16-- > 0)
      {
        i20 = arrayOfInt2[arrayOfByte[(i5 + (i13 >> 18))]];
        i19++;
        if (i20 != 0) {
          arrayOfInt1[i19] = (((arrayOfInt1[i19] & 0xFF0000) + (i20 & 0xFF0000) >> 17 << 16) + ((arrayOfInt1[i19] & 0xFF00) + (i20 & 0xFF00) >> 9 << 8) + ((arrayOfInt1[i19] & 0xFF) + (i20 & 0xFF) >> 1));
        }
        i13 += i7;
      }
      i14 += i8;
    }
  }
  
  private static final void a(int paramInt1, int paramInt2, int paramInt3, int paramInt4, int[][] paramArrayOfInt, boolean paramBoolean)
  {
    j localj = n[paramInt1];
    int[] arrayOfInt1 = aN;
    if (localj.i < 0) {
      localj.i = 0;
    }
    int i1;
    if (paramBoolean) {
      i1 = (localj.i + 2 >> 1) + ck[localj.C][0];
    } else {
      i1 = (localj.i >> 1) + ck[localj.C][0];
    }
    if ((i1 == 8) || (i1 == 9)) {
      i1 += 2;
    }
    byte[] arrayOfByte = dO[i1];
    int[] arrayOfInt2 = cJ[localj.C];
    int[] arrayOfInt3 = aO;
    short[] arrayOfShort = aD[i1];
    i locali1 = new i(null);
    i locali2 = new i(null);
    locali1.j = paramInt2;
    locali1.k = paramInt3;
    locali1.l = (paramInt4 - 8192000);
    b(locali1);
    if (locali1.c <= 0) {
      return;
    }
    int i2 = arrayOfShort[2];
    int i3 = arrayOfShort[3];
    locali1.a += (arrayOfShort[4] << 16);
    locali1.b += (arrayOfShort[5] << 16);
    locali2.c = locali1.c;
    locali1.d = ((short)(int)(120L + locali1.a * cB / locali1.c));
    locali1.e = ((short)(int)(130L - locali1.b * cB / locali1.c));
    locali2.d = ((short)(int)(120L + locali2.a * cB / locali2.c));
    locali2.e = ((short)(int)(130L - locali2.b * cB / locali2.c));
    int i4 = 0;
    int i5 = 0;
    int i6 = Math.abs(locali1.e - locali2.e << 1);
    int i7 = Math.abs(locali1.d - locali2.d << 1);
    if ((38400 <= i7) || (38400 <= i6)) {
      return;
    }
    int i8 = i2 * arrayOfInt3[i7];
    int i9 = i3 * arrayOfInt3[i6];
    int i10 = locali2.d - i7;
    int i11 = locali1.e - i6;
    int i12 = i10 + i7;
    int i13 = i11 + i6;
    if ((i10 > paramArrayOfInt[4][2] + 120) || (i11 > paramArrayOfInt[2][2] + 130) || (i12 < 120 - paramArrayOfInt[3][2]) || (i13 < 130 - paramArrayOfInt[1][2])) {
      return;
    }
    if (i10 <= 120 - paramArrayOfInt[3][2])
    {
      i4 = i8 * (120 - paramArrayOfInt[3][2] - i10);
      i10 = 120 - paramArrayOfInt[3][2];
    }
    if (i11 <= 130 - paramArrayOfInt[1][2])
    {
      i5 = i9 * (130 - paramArrayOfInt[1][2] - i11);
      i11 = 130 - paramArrayOfInt[1][2];
    }
    if (i12 >= paramArrayOfInt[4][2] + 120) {
      i12 = paramArrayOfInt[4][2] + 120 - 2;
    }
    if (i13 >= paramArrayOfInt[2][2] + 130) {
      i13 = paramArrayOfInt[2][2] + 130 - 2;
    }
    al[paramInt1] = 3;
    if (i11 + (i6 >> 3) > 130) {
      al[paramInt1] = 1;
    }
    if (i11 + (i6 >> 2) < 130) {
      al[paramInt1] = 2;
    }
    int i14 = 0;
    int i15 = i5;
    int i16 = i11 * 240 + i10;
    int i18 = i13 - i11;
    int i19 = i12 - i10;
    int i20 = 0;
    int i21 = 0;
    int i22;
    if (paramBoolean) {
      i22 = i2 - 1 << 18;
    } else {
      i22 = 0;
    }
    while (i18-- > 0)
    {
      i14 = i4;
      i16 += 240;
      int i17 = i19;
      i20 = i16;
      i6 = (i15 >> 18) * i2;
      while (i17-- > 0)
      {
        i21 = arrayOfInt2[arrayOfByte[(i6 + (Math.abs(i22 - i14) >> 18))]];
        i20++;
        if (i21 != 0) {
          arrayOfInt1[i20] = i21;
        }
        i14 += i8;
      }
      i15 += i9;
    }
  }
  
  private final void f(Graphics paramGraphics)
  {
    if (b != 0)
    {
      b(aN, 0);
      paramGraphics.drawRGB(aN, 0, 240, 0, 30, 240, 258, false);
      return;
    }
    paramGraphics.drawRGB(aN, 0, 240, 0, 30, 240, 258, false);
    int i1 = this.cx[eg].getHeight();
    int i2 = this.cx[eg].getWidth();
    paramGraphics.setClip(0, 30, 240, 260);
    int i3 = 0;
    if (eg == 0)
    {
      i1 = (i1 >>= 1) * cV >> 2;
      i2 = i2 * cV >> 2;
      i3 = this.cx[eg].getWidth() >> 1;
    }
    int i4 = 240 - i2 + cR + i3;
    int i5;
    if (ap == 0) {
      i5 = 320 - i1 + Math.abs(dY) - 30 - cS;
    } else {
      i5 = 320 - (i1 - (i1 * (4 - Math.abs(4 - ap)) >> 2)) - 30 + cS;
    }
    switch (eg)
    {
    case 1: 
    case 2: 
    case 3: 
      if ((be) && (bd != 0)) {
        c(paramGraphics, 2, i4 + ao[(eg - 1)][0], i5 + ao[(eg - 1)][1]);
      }
      break;
    case 4: 
    case 5: 
    case 6: 
      if ((be) && (bd != 0)) {
        c(paramGraphics, bd - 1, i4 + ao[(eg - 1)][(bd - 1 << 1)], i5 + ao[(eg - 1)][((bd - 1 << 1) + 1)]);
      }
      break;
    default: 
      bd = 0;
    }
    if ((n[0].e == 0) && (!n[0].k)) {
      paramGraphics.drawImage(this.cx[eg], i4, i5, 20);
    }
    paramGraphics.setClip(0, 0, 240, 320);
  }
  
  private static void b(int[] paramArrayOfInt, int paramInt)
  {
    for (int i1 = 0; i1 < 130; i1++) {
      for (int i2 = 0; i2 < 120; i2++)
      {
        if ((i1 - 130) * (i1 - 130) + (i2 - 120) * (i2 - 120) <= 14400) {
          break;
        }
        paramArrayOfInt[(i1 * 240 + i2)] = paramInt;
        paramArrayOfInt[(i1 * 240 + (240 - i2))] = paramInt;
        paramArrayOfInt[((260 - i1 - 1) * 240 + i2)] = paramInt;
        paramArrayOfInt[((260 - i1 - 1) * 240 + (240 - i2 - 1))] = paramInt;
      }
    }
    int i3 = 31200;
    int i4 = 120;
    for (int i5 = 0; i5 < 240; i5++) {
      paramArrayOfInt[(i3++)] = 16711680;
    }
    for (int i6 = 0; i6 < 260; i6++) {
      paramArrayOfInt[(i4 += 240)] = 16711680;
    }
  }
  
  private static boolean a(String paramString1, String paramString2)
  {
    String str;
    int i1 = (str = new String(paramString2)).length();
    byte[] arrayOfByte;
    if (((arrayOfByte = e.l.a(paramString1, -1)) == null) || (paramString2 == null) || (str == "")) {
      return false;
    }
    int i2 = arrayOfByte.length;
    if (i1 > i2) {
      return false;
    }
    int i3 = i2 - i1;
    for (int i5 = 0; i5 <= i3; i5++)
    {
      int i4 = 0;
      for (int i6 = 0; i6 < i1; i6++)
      {
        if (str.charAt(i6) != arrayOfByte[(i5 + i6)]) {
          break;
        }
        i4++;
      }
      if (i4 == i1) {
        return true;
      }
    }
    return false;
  }
  
  private static void B()
  {
    if (((eg == 7) || (eg == 8)) && ((b == 0) || (bj > 0)))
    {
      bj = 2;
      if (b < ca) {
        b += 50;
      }
      e(b);
      return;
    }
    b(n[0].D);
    bv = 0;
    i(n[0]);
  }
  
  final void e()
  {
    Display.getDisplay(NET_Lizard.a).setCurrent(this);
    this.dP.start();
  }
  
  private final void C()
  {
    if (this.bi == null) {
      this.bi = c.a();
    }
    this.dj = false;
    this.aZ = D();
    this.jdField_do = this.aH[2];
    String str1 = e.a(E);
    this.bT = null;
    this.aF = false;
    this.aV = 232;
    this.aL = (315 - 2 * this.aX - (this.bi.b() + this.aS));
    if (!this.aF) {
      this.aL -= 2 * (this.bi.b() + this.aS);
    }
    String[] arrayOfString = new String[3];
    int i1 = 0;
    for (int i2 = 0; i2 < 3; i2++)
    {
      arrayOfString[i2] = NET_Lizard.a.getAppProperty(str1 + (i2 + 1));
      if (arrayOfString[i2] != null) {
        i1 = 1;
      }
    }
    for (int i3 = 0; i3 < this.bk.length; i3++) {
      try
      {
        this.bk[i3] = null;
        this.bk[i3] = NET_Lizard.a.getAppProperty(this.cK[i3]);
      }
      catch (Exception localException1)
      {
        this.bk[i3] = null;
      }
    }
    int i4 = (this.bk[0] == null) || (this.bk[1] == null) ? 1 : 0;
    String str2 = null;
    if (i4 != 0)
    {
      for (i5 = 0; i5 < this.bk.length; i5++) {
        try
        {
          this.bk[i5] = this.aH[(4 + this.co)][(i5 + 1)];
        }
        catch (Exception localException2)
        {
          this.bk[i5] = null;
        }
      }
      try
      {
        str2 = this.aH[(4 + this.co)][(this.bk.length + 1)];
      }
      catch (Exception localException3) {}
      if ((this.bh) && (this.bk[0] != null) && (this.bk[1] != null))
      {
        this.co = 0;
        this.dj = true;
        for (int i6 = 0; i6 < this.bk.length; i6++) {
          this.bk[i6] = null;
        }
        str2 = null;
      }
    }
    int i5 = 0;
    String str3 = this.aH[0][0] + '\r' + this.aH[0][1];
    if (!this.bh) {
      str3 = this.aH[0][1];
    }
    int i7;
    if ((this.bk[0] != null) && (this.bk[0].length() > 0) && (this.bk[1] != null) && (this.bk[1].length() > 0))
    {
      str3 = str3 + this.aH[0][2] + this.bk[0] + this.aH[0][3] + this.bk[1] + '\r';
      i5 = 1;
    }
    else if (this.dj)
    {
      str3 = str3 + this.aH[2][3] + '\r' + '\r' + this.aH[2][4] + '\r' + '\r';
      i7 = 0;
      int i8 = 0;
      while (i7 < this.aH.length)
      {
        try
        {
          if ((this.aH[(4 + i7)] != null) && (this.aH[(4 + i7)].length >= 3) && (this.aH[(4 + i7)][0] != null) && (this.aH[(4 + i7)][0].charAt(0) == '*'))
          {
            str3 = str3 + this.aH[(4 + i7)][0] + '\r';
            i8++;
          }
        }
        catch (Exception localException4)
        {
          break;
        }
        i7++;
      }
      this.bI = i8;
      i5 = 1;
      this.aZ = true;
    }
    else
    {
      str3 = str3 + this.aH[3][0] + '\r' + this.aH[3][1];
    }
    if ((this.bk[2] != null) && (this.bk[2].length() > 0)) {
      str3 = str3 + '\r' + this.bk[2] + '\r';
    }
    if (str2 != null) {
      str3 = str3 + '\r' + str2 + '\r';
    }
    if (i5 == 0) {
      this.aZ = false;
    }
    if (i1 != 0)
    {
      str3 = str3 + '\r' + this.aH[1][0] + this.aH[1][1] + this.aH[1][2] + NET_Lizard.a.getAppProperty(this.cK[0]) + this.aH[1][3] + '\r' + '\r';
      for (i7 = 0; i7 < 3; i7++) {
        if (arrayOfString[i7] != null) {
          str3 = str3 + arrayOfString[i7] + '\r';
        }
      }
    }
    b(str3);
    this.aR = 0;
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
  
  private static boolean D()
  {
    boolean bool;
    if (((bool = af() > 0 ? 1 : 0) != 0) && (NET_Lizard.a.getAppProperty(e.a(F)) != null)) {
      bool = false;
    }
    return bool;
  }
  
  public final void hideNotify()
  {
    super.hideNotify();
    if ((this.cg == 1) && (!ce) && (!this.i))
    {
      ce = true;
      this.i = true;
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
  
  private static byte j(int paramInt)
  {
    int i1 = paramInt;
    if (paramInt > 127) {
      i1 = paramInt - 256;
    }
    return (byte)i1;
  }
  
  protected final void keyPressed(int paramInt)
  {
    paramInt = a.a(paramInt);
    this.av = false;
    if (paramInt == -1)
    {
      paramInt = 50;
      this.av = true;
    }
    if (paramInt == -2)
    {
      paramInt = 56;
      this.av = true;
    }
    if (paramInt == -3)
    {
      paramInt = 52;
      this.av = true;
    }
    if (paramInt == -4)
    {
      paramInt = 54;
      this.av = true;
    }
    if ((paramInt == -6) && (this.cg == 4)) {
      this.av = true;
    }
    if ((paramInt == -6) || (paramInt == -5)) {
      paramInt = 53;
    }
    if (paramInt == -7)
    {
      paramInt = this.d;
      this.av = true;
    }
    if ((paramInt == 42) || (paramInt == this.d) || (paramInt == 48))
    {
      this.bC = true;
      this.bD = false;
    }
    else
    {
      this.bD = true;
      this.bC = false;
    }
    this.bG = false;
    this.bE = paramInt;
  }
  
  protected final void keyReleased(int paramInt)
  {
    if (this.bG)
    {
      this.bE = 0;
      return;
    }
    this.bH = true;
  }
  
  private final void E()
  {
    int i1 = System.currentTimeMillis() > this.aE ? 1 : 0;
    if (this.bT == null) {
      return;
    }
    switch (this.bE)
    {
    case 50: 
      if ((this.dj) && (this.co > 0))
      {
        this.co -= 1;
        return;
      }
      if (this.aR > 0)
      {
        this.aR -= 1;
        return;
      }
      break;
    case 56: 
      if (this.aR < this.bT.length - this.aL / (this.bi.b() + this.aS))
      {
        this.aR += 1;
        return;
      }
      if ((this.dj) && (this.co < this.bI - 1))
      {
        this.co += 1;
        return;
      }
      break;
    case 53: 
      if (i1 == 0) {
        return;
      }
      if (!this.aZ) {
        return;
      }
      if (this.dj)
      {
        this.dj = false;
        this.bh = false;
        C();
        this.bE = 0;
        this.bH = false;
        this.aE = (System.currentTimeMillis() + 2000L);
        return;
      }
      try
      {
        String str1 = this.bk[0];
        String str2;
        n.a(str2 = this.bk[1], str1);
      }
      catch (Exception localException) {}
    case -7: 
    case 35: 
      if (i1 == 0) {
        return;
      }
      this.bT = null;
      a(false);
      this.bE = 0;
      this.bH = false;
    }
  }
  
  private final void F()
  {
    this.bG = true;
    E();
    if (this.bH)
    {
      this.bE = 0;
      this.bH = false;
    }
  }
  
  private final void G()
  {
    this.bG = true;
    int i1 = 0;
    int i2 = 0;
    int i3 = 0;
    int i4 = 0;
    int i5 = 0;
    if (this.cg == 11)
    {
      this.ar = false;
      if ((this.bE == 35) && (!this.av))
      {
        this.aq += e.a(A);
      }
      else if (!this.av)
      {
        this.aq += this.bE - 48;
        this.bH = true;
      }
      if (this.aq.length() >= 4) {
        this.aq = "";
      }
    }
    switch (this.bE)
    {
    case 49: 
      if (!this.i) {
        if (ae()) {
          this.bH = true;
        }
      }
      break;
    case 50: 
      i3 = 1;
      break;
    case 52: 
      i1 = 1;
      break;
    case 53: 
      i5 = 1;
      this.ar = true;
      break;
    case 54: 
      i2 = 1;
      break;
    case 56: 
      i4 = 1;
    }
    if (this.bE == 35)
    {
      if (this.cg == 1)
      {
        if ((ce) && (this.i))
        {
          ce = false;
          this.i = false;
          return;
        }
        ce = true;
        this.i = true;
        a(0, 0, 240, 260, 0, 128);
        return;
      }
      this.cd.b();
    }
    if (this.bE == 42) {
      cP = !cP;
    }
    if ((this.bE == 48) && (!this.i)) {
      x();
    }
    if (!ce)
    {
      if (!n[0].k)
      {
        dQ = false;
        if (i2 != 0) {
          d((byte)1);
        }
        if (i1 != 0) {
          c((byte)1);
        }
        if (i3 != 0) {
          aa();
        }
        if (i4 != 0) {
          X();
        }
        if (this.bE == 55) {
          Y();
        }
        if (this.bE == 57) {
          Z();
        }
        if (this.bE == 49) {
          c((byte)0);
        }
        if (this.bE == 51) {
          d((byte)0);
        }
        if (this.bE == 48) {
          dD = !dD;
        }
        if (i5 != 0) {
          B();
        }
      }
      return;
    }
    if (i3 != 0) {
      this.cd.f();
    }
    if (i4 != 0) {
      this.cd.c();
    }
    if (i1 != 0)
    {
      this.cd.d();
      this.bH = true;
    }
    if (i2 != 0)
    {
      this.cd.e();
      this.bH = true;
    }
    if (i5 != 0)
    {
      this.cd.a();
      this.bH = true;
    }
  }
  
  private final void H()
  {
    G();
    if (this.bH)
    {
      this.bE = 0;
      this.bH = false;
    }
  }
  
  private final String[] I()
  {
    String[][] arrayOfString = e.l.b(e.a(G));
    String[] arrayOfString1 = new String[cD + 1];
    for (int i1 = 0; i1 < cD; i1++) {
      arrayOfString1[i1] = arrayOfString[1][(i1 + 1)];
    }
    arrayOfString1[cD] = this.cm[1];
    return arrayOfString1;
  }
  
  private static final boolean a(j paramj1, j paramj2)
  {
    if (paramj1.t == paramj2.t) {
      return true;
    }
    int i1 = -1;
    d locald1 = dH;
    d locald2 = bb;
    locald1.a = paramj1.p;
    locald1.b = paramj1.q;
    locald1.c = paramj1.r;
    locald2.a = paramj2.p;
    locald2.b = paramj2.q;
    locald2.c = paramj2.r;
    int i2 = paramj1.t;
    while ((i1 = a(i2, locald1, locald2, i1)) != -1)
    {
      if (j[i1].c == i2) {
        i2 = j[i1].d;
      } else {
        i2 = j[i1].c;
      }
      if (paramj2.t == i2) {
        return true;
      }
    }
    return false;
  }
  
  private static final boolean b(j paramj, int paramInt1, int paramInt2, int paramInt3, int paramInt4)
  {
    if (paramj.t == paramInt4) {
      return true;
    }
    int i1 = -1;
    d locald1 = dH;
    d locald2 = bb;
    locald1.a = paramj.p;
    locald1.b = paramj.q;
    locald1.c = paramj.r;
    locald2.a = paramInt1;
    locald2.b = paramInt2;
    locald2.c = paramInt3;
    int i2 = paramj.t;
    while ((i1 = a(i2, locald1, locald2, i1)) != -1)
    {
      if (j[i1].c == i2) {
        i2 = j[i1].d;
      } else {
        i2 = j[i1].c;
      }
      if (paramInt4 == i2) {
        return true;
      }
    }
    return false;
  }
  
  private final void J()
  {
    this.bi = c.a();
    this.bi.c = 0;
    if (this.m == null) {
      try
      {
        this.m = NET_Lizard.a.getAppProperty(e.a(N));
      }
      catch (Exception localException1) {}
    }
    if (this.m == null) {
      try
      {
        this.m = NET_Lizard.a.getAppProperty(e.a(O));
      }
      catch (Exception localException2) {}
    }
    n();
    if (!this.aw) {
      return;
    }
    String[][] arrayOfString = e.l.b(e.a(H));
    String[] arrayOfString1 = e.a(e.l.c(e.a(J)), this.bi, 10000, false);
    this.bq = new String[arrayOfString1.length][];
    for (int i1 = 0; i1 < arrayOfString1.length; i1++) {
      this.bq[i1] = e.a(arrayOfString1[i1], this.bi, 240, true);
    }
    this.cm = null;
    this.cm = new String[arrayOfString[0].length];
    for (int i2 = 0; i2 < arrayOfString[0].length; i2++) {
      this.cm[i2] = new String(arrayOfString[0][i2]);
    }
    L();
    this.o = ax[29][2];
    this.c = ax[29][3];
    P();
    W();
    try
    {
      try
      {
        this.bQ = e.a(e.a(T));
      }
      catch (OutOfMemoryError localOutOfMemoryError) {}
      T();
    }
    catch (Exception localException3) {}
    this.bE = 0;
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
  
  private static void K()
  {
    byte[] arrayOfByte = e.l.a(e.a(s), -1);
    ao[0][0] = arrayOfByte[0];
    ao[0][1] = arrayOfByte[1];
    ao[1][0] = arrayOfByte[2];
    ao[1][1] = arrayOfByte[3];
    ao[2][0] = arrayOfByte[4];
    ao[2][1] = arrayOfByte[5];
    ao[3][0] = arrayOfByte[6];
    ao[3][1] = arrayOfByte[7];
    ao[3][2] = arrayOfByte[8];
    ao[3][3] = arrayOfByte[9];
    ao[4][0] = arrayOfByte[10];
    ao[4][1] = arrayOfByte[11];
    ao[4][2] = arrayOfByte[12];
    ao[4][3] = arrayOfByte[13];
    ao[5][0] = arrayOfByte[14];
    ao[5][1] = arrayOfByte[15];
    ao[5][2] = arrayOfByte[16];
    ao[5][3] = arrayOfByte[17];
  }
  
  private final void L()
  {
    byte[] arrayOfByte;
    int i1;
    ax = new short[i1 = (arrayOfByte = e.l.a(e.a(u), -1)).length / this.ay][this.ay];
    for (int i2 = 0; i2 < i1; i2++)
    {
      int i4 = i2 * this.ay;
      for (int i3 = 0; i3 < this.ay; i3++)
      {
        ax[i2][i3] = ((short)arrayOfByte[(i4 + i3)]);
        if (ax[i2][i3] < 0)
        {
          int tmp87_85 = i3;
          short[] tmp87_84 = ax[i2];
          tmp87_84[tmp87_85] = ((short)(tmp87_84[tmp87_85] + 256));
        }
      }
    }
  }
  
  private final void M()
  {
    byte[] arrayOfByte;
    int i1;
    aB = new short[i1 = (arrayOfByte = e.l.a(e.a(ac), -1)).length / this.ay][this.ay];
    for (int i2 = 0; i2 < i1; i2++)
    {
      int i4 = i2 * this.ay;
      for (int i3 = 0; i3 < this.ay; i3++)
      {
        aB[i2][i3] = ((short)arrayOfByte[(i4 + i3)]);
        if (aB[i2][i3] < 0)
        {
          int tmp87_85 = i3;
          short[] tmp87_84 = aB[i2];
          tmp87_84[tmp87_85] = ((short)(tmp87_84[tmp87_85] + 256));
        }
      }
    }
  }
  
  private final int N()
  {
    byte[] arrayOfByte;
    int i1;
    int i5 = (short)(i1 = (arrayOfByte = e.l.a(e.a(q), -1)).length / this.ay);
    aC = new short[i1][this.ay];
    for (int i2 = 0; i2 < i1; i2++)
    {
      int i4 = i2 * this.ay;
      for (int i3 = 0; i3 < this.ay; i3++)
      {
        aC[i2][i3] = ((short)arrayOfByte[(i4 + i3)]);
        if (aC[i2][i3] < 0)
        {
          int tmp91_89 = i3;
          short[] tmp91_88 = aC[i2];
          tmp91_88[tmp91_89] = ((short)(tmp91_88[tmp91_89] + 256));
        }
      }
    }
    return i5;
  }
  
  private final int O()
  {
    byte[] arrayOfByte;
    int i1;
    int i5 = (short)(i1 = (arrayOfByte = e.l.a(e.a(r), -1)).length / this.ay);
    aD = new short[i1][this.ay];
    for (int i2 = 0; i2 < i1; i2++)
    {
      int i4 = i2 * this.ay;
      for (int i3 = 0; i3 < this.ay; i3++)
      {
        aD[i2][i3] = ((short)arrayOfByte[(i4 + i3)]);
        if (aD[i2][i3] < 0)
        {
          int tmp91_89 = i3;
          short[] tmp91_88 = aD[i2];
          tmp91_88[tmp91_89] = ((short)(tmp91_88[tmp91_89] + 256));
        }
      }
    }
    return i5;
  }
  
  private final void k(int paramInt)
  {
    this.dr = false;
    if ((paramInt == 3) || (paramInt == 4) || (paramInt == 5) || (paramInt == 7)) {
      this.dr = true;
    }
    int i1 = -2;
    byte[] arrayOfByte = e.l.a(e.a(Y) + paramInt, -1);
    i1 += 2;
    this.cO = ((byte)(a(arrayOfByte[0], arrayOfByte[1]) - 1));
    i1 += 2;
    dg[0] = (a(arrayOfByte[2], arrayOfByte[3]) << 16);
    i1 += 2;
    dg[1] = (a(arrayOfByte[4], arrayOfByte[5]) << 16);
    i1 += 2;
    dg[2] = (a(arrayOfByte[6], arrayOfByte[7]) << 16);
    i1 += 2;
    dd = a(arrayOfByte[8], arrayOfByte[9]);
    i1 += 2;
    df = a(arrayOfByte[10], arrayOfByte[11]);
    if (df > 361) {
      df -= 65536;
    }
    if (dd > 361) {
      dd -= 65536;
    }
    if (df < 0) {
      df = -df;
    } else {
      df = 360 - df;
    }
    if (df == 360) {
      df = 0;
    }
    if (dd < 0) {
      dd = 270 + dd;
    } else {
      dd = 270 - dd;
    }
    if (dd == 360) {
      dd = 0;
    }
    i1 += 2;
    cZ = a(arrayOfByte[12], arrayOfByte[13]);
    l = new f[cZ];
    for (int i7 = 0; i7 < cZ; i7++) {
      l[i7] = new f(null);
    }
    int i20;
    int i25;
    for (int i15 = 0; i15 < cZ; i15++)
    {
      int i13 = 0;
      i1 += 2;
      l[i15].f = (a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
      i1 += 2;
      l[i15].g = (a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
      i1 += 2;
      l[i15].h = (a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
      i1 += 2;
      l[i15].i = (a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
      i1 += 2;
      l[i15].j = (a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
      i1 += 2;
      l[i15].k = (a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
      i1 += 2;
      int i9 = a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
      i1 += 2;
      int i8 = a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
      i1 += 2;
      int i10 = a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
      l[i15].a = new int[i9 * 6];
      l[i15].n = i9;
      l[i15].b = new int[i8 * 10];
      l[i15].o = i8;
      int[] arrayOfInt2 = new int[i8 * 3];
      int[] arrayOfInt1 = new int[i10 *= 2];
      for (i16 = 0; i16 < i9; i16++)
      {
        i1 += 2;
        l[i15].a[(i16 * 6)] = (a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
        i1 += 2;
        l[i15].a[(i16 * 6 + 1)] = (a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
        i1 += 2;
        l[i15].a[(i16 * 6 + 2)] = (a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
      }
      for (i17 = 0; i17 < i8; i17++)
      {
        i1 += 2;
        l[i15].b[(i17 * 10)] = (a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 6);
        i1 += 2;
        l[i15].b[(i17 * 10 + 1)] = (a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 6);
        i1 += 2;
        l[i15].b[(i17 * 10 + 2)] = (a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 6);
      }
      for (i18 = 0; i18 < i8; i18++)
      {
        i1 += 2;
        arrayOfInt2[(i18 * 3)] = ((int)(65536 * a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 10000L));
        i1 += 2;
        arrayOfInt2[(i18 * 3 + 1)] = ((int)(65536 * a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 10000L));
        i1 += 2;
        arrayOfInt2[(i18 * 3 + 2)] = ((int)(65536 * a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 10000L));
      }
      int i12 = 0;
      for (i19 = 0; i19 < i8; i19++)
      {
        int i14 = 1;
        for (i20 = i19 + 1; i20 < i8; i20++) {
          if ((arrayOfInt2[(i19 * 3)] == arrayOfInt2[(i20 * 3)]) && (arrayOfInt2[(i19 * 3 + 1)] == arrayOfInt2[(i20 * 3 + 1)]) && (arrayOfInt2[(i19 * 3 + 2)] == arrayOfInt2[(i20 * 3 + 2)]))
          {
            arrayOfInt2[(i19 * 3)] = 0;
            arrayOfInt2[(i19 * 3 + 1)] = 0;
            arrayOfInt2[(i19 * 3 + 2)] = 0;
            i14 = 0;
            break;
          }
        }
        if (i14 != 0) {
          i12++;
        }
      }
      l[i15].l = new int[i12 * 6];
      l[i15].m = (i12 * 6 - 6);
      for (i20 = 0; i20 < i8; i20++) {
        if ((arrayOfInt2[(i20 * 3)] != 0) || (arrayOfInt2[(i20 * 3 + 1)] != 0) || (arrayOfInt2[(i20 * 3 + 2)] != 0))
        {
          l[i15].l[(i13 * 6)] = l[i15].a[l[i15].b[(i20 * 10)]];
          l[i15].l[(i13 * 6 + 1)] = l[i15].a[(l[i15].b[(i20 * 10)] + 1)];
          l[i15].l[(i13 * 6 + 2)] = l[i15].a[(l[i15].b[(i20 * 10)] + 2)];
          l[i15].l[(i13 * 6 + 3)] = arrayOfInt2[(i20 * 3)];
          l[i15].l[(i13 * 6 + 4)] = arrayOfInt2[(i20 * 3 + 1)];
          l[i15].l[(i13 * 6 + 5)] = arrayOfInt2[(i20 * 3 + 2)];
          i13++;
        }
      }
      l[i15].c = (l[i15].f + l[i15].i >> 1);
      l[i15].d = (l[i15].g + l[i15].j >> 1);
      int[] arrayOfInt3 = l[i15].l;
      for (i25 = l[i15].m; i25 >= 0; i25 -= 6)
      {
        long l1;
        if ((l1 = arrayOfInt3[(i25 + 3)] * (l[i15].c - arrayOfInt3[i25]) + arrayOfInt3[(i25 + 4)] * (l[i15].d - arrayOfInt3[(i25 + 1)]) >> 16) < 8192000L)
        {
          long l2 = 8192000L - l1;
          f tmp1584_1583 = l[i15];
          tmp1584_1583.c = ((int)(tmp1584_1583.c + (arrayOfInt3[(i25 + 3)] * l2 >> 16)));
          f tmp1614_1613 = l[i15];
          tmp1614_1613.d = ((int)(tmp1614_1613.d + (arrayOfInt3[(i25 + 4)] * l2 >> 16)));
        }
      }
      for (i26 = 0; i26 < i10; i26 += 2)
      {
        i1 += 2;
        arrayOfInt1[i26] = ((int)(64 * a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 100L));
        i1 += 2;
        arrayOfInt1[(i26 + 1)] = ((int)(64 * a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 100L));
      }
      for (i27 = 0; i27 < i8; i27++)
      {
        i1 += 2;
        l[i15].b[(i27 * 10 + 3)] = ((short)arrayOfInt1[(a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2)]);
        l[i15].b[(i27 * 10 + 4)] = ((short)arrayOfInt1[(a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2 + 1)]);
        i1 += 2;
        l[i15].b[(i27 * 10 + 5)] = ((short)arrayOfInt1[(a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2)]);
        l[i15].b[(i27 * 10 + 6)] = ((short)arrayOfInt1[(a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2 + 1)]);
        i1 += 2;
        l[i15].b[(i27 * 10 + 7)] = ((short)arrayOfInt1[(a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2)]);
        l[i15].b[(i27 * 10 + 8)] = ((short)arrayOfInt1[(a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2 + 1)]);
      }
      for (int i28 = 0; i28 < i8; i28++)
      {
        i1 += 2;
        l[i15].b[(i28 * 10 + 9)] = ((byte)a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
        bU[l[i15].b[(i28 * 10 + 9)]] = true;
      }
    }
    i1 += 2;
    int i11;
    j = new b[i11 = a(arrayOfByte[i1], arrayOfByte[(i1 + 1)])];
    for (int i16 = 0; i16 < i11; i16++)
    {
      j[i16] = new b(null);
      j[i16].b[0] = new i(null);
      j[i16].b[1] = new i(null);
      j[i16].b[2] = new i(null);
      j[i16].b[3] = new i(null);
    }
    int i2;
    int i3;
    int i4;
    for (int i17 = 0; i17 < i11; i17++)
    {
      for (i18 = 0; i18 < 4; i18++)
      {
        i1 += 2;
        j[i17].b[i18].j = (a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
        i1 += 2;
        j[i17].b[i18].k = (a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
        i1 += 2;
        j[i17].b[i18].l = (a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
      }
      i1 += 2;
      i2 = (int)(65536 * a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 10000L);
      i1 += 2;
      i3 = (int)(65536 * a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 10000L);
      i1 += 2;
      i4 = (int)(65536 * a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 10000L);
      i1 += 2;
      j[i17].c = (a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) - 1);
      i1 += 2;
      j[i17].d = (a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) - 1);
      if ((j[i17].c == 999) || (j[i17].d == 999)) {
        this.dr = true;
      }
      if (i2 != 0) {
        j[i17].a = 1;
      } else if (i3 != 0) {
        j[i17].a = 2;
      } else if (i4 != 0) {
        j[i17].a = 3;
      }
    }
    for (int i18 = 0; i18 < i11; i18++)
    {
      if (j[i18].c < 999)
      {
        l[j[i18].c].p[l[j[i18].c].q] = i18;
        l[j[i18].c].q += 1;
      }
      if (j[i18].d < 999)
      {
        l[j[i18].d].p[l[j[i18].d].q] = i18;
        l[j[i18].d].q += 1;
      }
    }
    i1 += 2;
    cA = a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
    h = new g[cA + 1];
    for (int i19 = 0; i19 < cA + 1; i19++)
    {
      h[i19] = new g(null);
      if (i19 == cA)
      {
        h[i19].s = 49;
        bS[49] = true;
      }
    }
    int i21 = 0;
    int i24;
    for (int i22 = 0; i22 < cZ; i22++)
    {
      i1 += 2;
      i20 = a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
      l[i22].r = i21;
      l[i22].e = (i21 + i20);
      for (i23 = 0; i23 < i20; i23++)
      {
        h[i21].r = ((short)i22);
        i1 += 2;
        h[i21].m = (a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
        i1 += 2;
        h[i21].n = (a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
        i1 += 2;
        h[i21].o = (a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
        i1 += 2;
        h[i21].p = a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
        i1 += 2;
        h[i21].q = a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
        if (h[i21].q > 360) {
          h[i21].q = (65536 - h[i21].q);
        }
        if (h[i21].p > 360) {
          h[i21].p = (65536 - h[i21].p);
        }
        if (h[i21].q < 0) {
          h[i21].q = (-h[i21].q);
        }
        if (h[i21].q == 360) {
          h[i21].q = 0;
        }
        if (h[i21].p < 0) {
          h[i21].p = (360 + h[i21].p);
        } else {
          h[i21].p = (360 - h[i21].p);
        }
        if (h[i21].p == 360) {
          h[i21].p = 0;
        }
        i1 += 2;
        h[i21].s = ((byte)a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
        bS[h[i21].s] = true;
        i1 += 2;
        h[i21].d = ((short)(byte)a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
        if (h[i21].d != 0)
        {
          h[i21].c = new int[h[i21].d][];
          for (i24 = 0; i24 < h[i21].d; i24++) {
            h[i21].c[i24] = new int[4];
          }
          for (i25 = 0; i25 < h[i21].d; i25++)
          {
            i1 += 2;
            h[i21].c[i25][0] = (a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
            i1 += 2;
            h[i21].c[i25][1] = (a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
            i1 += 2;
            h[i21].c[i25][2] = (a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
            i1 += 2;
            h[i21].c[i25][3] = a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
          }
          for (i26 = 0; i26 < h[i21].d - 1; i26++)
          {
            int i6;
            if ((i6 = h[i21].c[(i26 + 1)][3] - h[i21].c[i26][3]) > 1)
            {
              i2 = h[i21].c[i26][0];
              i3 = h[i21].c[i26][1];
              i4 = h[i21].c[i26][2];
              int i5 = h[i21].c[i26][3];
              h[i21].c[i26] = new int[7];
              h[i21].c[i26][0] = i2;
              h[i21].c[i26][1] = i3;
              h[i21].c[i26][2] = i4;
              h[i21].c[i26][3] = i5;
              h[i21].c[i26][4] = ((h[i21].c[(i26 + 1)][0] - h[i21].c[i26][0]) / i6);
              h[i21].c[i26][5] = ((h[i21].c[(i26 + 1)][1] - h[i21].c[i26][1]) / i6);
              h[i21].c[i26][6] = ((h[i21].c[(i26 + 1)][2] - h[i21].c[i26][2]) / i6);
            }
          }
        }
        i21++;
      }
    }
    i1 += 2;
    dR = a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) + 1;
    al = new byte[dR];
    n = new j[dR];
    for (int i23 = 0; i23 < dR; i23++) {
      n[i23] = new j(null);
    }
    i21 = 1;
    n[0].p = dg[0];
    n[0].q = dg[1];
    n[0].r = dg[2];
    for (int i26 = 0; i26 < cZ; i26++)
    {
      i1 += 2;
      i24 = a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]);
      for (i27 = 0; i27 < i24; i27++)
      {
        i1 += 2;
        n[i21].p = (a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
        n[i21].z = n[i21].p;
        i1 += 2;
        n[i21].q = (a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
        n[i21].A = n[i21].q;
        i1 += 2;
        n[i21].r = (a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
        i1 += 2;
        n[i21].C = ((byte)a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
        i25 = n[i21].C;
        bV[i25] = true;
        if ((i25 == 4) || (i25 == 5))
        {
          bt = (byte)(bt + 1);
          this.ei = ((byte)i21);
        }
        else
        {
          dK = (byte)(dK + 1);
        }
        n[i21].t = ((short)i26);
        i21++;
      }
    }
    for (int i27 = dR - 1; i27 >= 0; i27--)
    {
      f(n[i27]);
      if (i27 == 0)
      {
        cY = n[i27].t;
        b(n[i27].D);
      }
      else
      {
        c(n[i27], 10, 0, 0, 1);
      }
    }
    n[0].t = ((short)cY);
  }
  
  private final void P()
  {
    this.cw = null;
    this.cw = new Image[3];
    for (int i1 = 0; i1 < 3; i1++) {
      try
      {
        this.cw[i1] = e.a(e.a(M) + i1 + e.a(L));
      }
      catch (Exception localException) {}
    }
  }
  
  private final void Q()
  {
    m(15);
    bz = new int[''];
    bp = new int[''];
    by = new int[40 + n.length + cA];
    bo = new int[40 + n.length + cA];
    aQ = new int['È'];
    br = new i[10];
    bl = new i[10];
    for (int i1 = 0; i1 < 10; i1++)
    {
      br[i1] = new i(null);
      bl[i1] = new i(null);
    }
    m(17);
    az = new int['ʁ'];
    for (int i2 = 1; i2 < 641; i2++) {
      az[i2] = (65536 / i2);
    }
    aO = new int[38400];
    for (int i3 = 1; i3 < 38400; i3++) {
      aO[i3] = (262144 / i3);
    }
    m(19);
  }
  
  private static void R()
  {
    byte[] arrayOfByte;
    int i1;
    ck = new byte[i1 = (arrayOfByte = e.l.a(e.a(t), -1)).length / 15][15];
    for (int i2 = 0; i2 < i1; i2++)
    {
      int i4 = i2 * 15;
      for (int i3 = 0; i3 < 15; i3++)
      {
        ck[i2][i3] = arrayOfByte[(i4 + i3)];
        if (ck[i2][i3] < 0)
        {
          int tmp75_74 = i3;
          byte[] tmp75_73 = ck[i2];
          tmp75_73[tmp75_74] = ((byte)(tmp75_73[tmp75_74] + 256));
        }
      }
    }
  }
  
  private static void S()
  {
    g = new l[56];
    for (int i11 = 0; i11 < 56; i11++) {
      if ((bS[i11] != 0) || (i11 == 55))
      {
        int i1 = -2;
        byte[] arrayOfByte = e.l.a(e.a(ab) + i11, -1);
        g[i11] = new l(null);
        i1 += 2;
        g[i11].e = (a(arrayOfByte[0], arrayOfByte[1]) << 16);
        i1 += 2;
        g[i11].f = (a(arrayOfByte[2], arrayOfByte[3]) << 16);
        i1 += 2;
        g[i11].g = (a(arrayOfByte[4], arrayOfByte[5]) << 16);
        i1 += 2;
        g[i11].h = (a(arrayOfByte[6], arrayOfByte[7]) << 16);
        i1 += 2;
        g[i11].i = (a(arrayOfByte[8], arrayOfByte[9]) << 16);
        i1 += 2;
        g[i11].j = (a(arrayOfByte[10], arrayOfByte[11]) << 16);
        int i2 = g[i11].e >> 16;
        int i3 = g[i11].f >> 16;
        int i4 = g[i11].g >> 16;
        int i5 = i2 * i2 + i3 * i3 + i4 * i4;
        int i6 = 65536;
        int i7 = 0;
        while (i6 >>= 1 > 0) {
          if ((i7 + i6) * (i7 + i6) <= i5) {
            i7 += i6;
          }
        }
        g[i11].d = ((i7 << 1) * 240);
        g[i11].c = ((i7 << 1) * 320);
        i1 += 2;
        i1 += 2;
        i1 += 2;
        i1 += 2;
        i1 += 2;
        int i9 = a(arrayOfByte[20], arrayOfByte[21]);
        i1 += 2;
        int i8 = a(arrayOfByte[22], arrayOfByte[23]);
        i1 += 2;
        int i10 = a(arrayOfByte[24], arrayOfByte[25]);
        g[i11].k = i9;
        g[i11].a = new int[i9 * 6];
        g[i11].b = new int[i8 * 16];
        int[] arrayOfInt = new int[i10 *= 2];
        for (i12 = 0; i12 < i9; i12++)
        {
          i1 += 2;
          g[i11].a[(i12 * 6)] = (a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
          i1 += 2;
          g[i11].a[(i12 * 6 + 1)] = (a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
          i1 += 2;
          g[i11].a[(i12 * 6 + 2)] = (a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) << 16);
        }
        for (int i13 = 0; i13 < i8; i13++)
        {
          i1 += 2;
          g[i11].b[(i13 * 16)] = (a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 6);
          i1 += 2;
          g[i11].b[(i13 * 16 + 1)] = (a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 6);
          i1 += 2;
          g[i11].b[(i13 * 16 + 2)] = (a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 6);
        }
        for (int i14 = 0; i14 < i8; i14++)
        {
          i1 += 2;
          g[i11].b[(i14 * 16 + 10)] = ((int)(65536 * a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 10000L));
          i1 += 2;
          g[i11].b[(i14 * 16 + 11)] = ((int)(65536 * a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 10000L));
          i1 += 2;
          g[i11].b[(i14 * 16 + 12)] = ((int)(65536 * a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 10000L));
        }
        for (int i15 = 0; i15 < i10; i15 += 2)
        {
          i1 += 2;
          arrayOfInt[i15] = ((int)(64 * a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 100L));
          i1 += 2;
          arrayOfInt[(i15 + 1)] = ((int)(64 * a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) / 100L));
        }
        for (int i16 = 0; i16 < i8; i16++)
        {
          i1 += 2;
          g[i11].b[(i16 * 16 + 3)] = ((short)arrayOfInt[(a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2)]);
          g[i11].b[(i16 * 16 + 4)] = ((short)arrayOfInt[(a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2 + 1)]);
          i1 += 2;
          g[i11].b[(i16 * 16 + 5)] = ((short)arrayOfInt[(a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2)]);
          g[i11].b[(i16 * 16 + 6)] = ((short)arrayOfInt[(a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2 + 1)]);
          i1 += 2;
          g[i11].b[(i16 * 16 + 7)] = ((short)arrayOfInt[(a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2)]);
          g[i11].b[(i16 * 16 + 8)] = ((short)arrayOfInt[(a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]) * 2 + 1)]);
        }
        for (int i17 = 0; i17 < i8; i17++)
        {
          i1 += 2;
          g[i11].b[(i17 * 16 + 9)] = ((byte)a(arrayOfByte[i1], arrayOfByte[(i1 + 1)]));
          bU[g[i11].b[(i17 * 16 + 9)]] = true;
        }
      }
    }
    bU[60] = true;
    for (int i12 = 0; i12 < h.length; i12++) {
      if (i12 == h.length - 1)
      {
        h[i12].a = g[49].a;
        h[i12].b = g[49].b;
        h[i12].f = g[49].e;
        h[i12].i = g[49].h;
        h[i12].g = g[49].f;
        h[i12].j = g[49].i;
        h[i12].h = g[49].g;
        h[i12].k = g[49].j;
      }
      else
      {
        h[i12].a = g[h[i12].s].a;
        h[i12].b = g[h[i12].s].b;
        h[i12].f = g[h[i12].s].e;
        h[i12].i = g[h[i12].s].h;
        h[i12].g = g[h[i12].s].f;
        h[i12].j = g[h[i12].s].i;
        h[i12].h = g[h[i12].s].g;
        h[i12].k = g[h[i12].s].j;
        if ((h[i12].s == 55) || (h[i12].s == 53)) {
          h[i12].e = (h[i12].o - h[i12].h - 8192000);
        }
        if ((h[i12].s == 54) || (h[i12].s == 52)) {
          h[i12].e = (h[i12].o + h[i12].h + 8192000);
        }
      }
    }
  }
  
  private void T()
  {
    e.i = true;
    e.a();
    if (bf)
    {
      dJ = true;
      this.cl = 2;
      dT = true;
      cD = 1;
      j();
      return;
    }
    if (e.a[13] == 0) {
      this.bg = true;
    } else {
      this.bg = false;
    }
    if (e.a[14] == 1) {
      dJ = true;
    } else {
      dJ = false;
    }
    this.cl = e.a[27];
    if (e.a[16] == 1) {
      dT = true;
    } else {
      dT = false;
    }
    cn = e.a[17];
    aM = e.a[18];
    cj = a(e.a[19], e.a[20]);
    if (cn != 0) {
      for (int i1 = 1; i1 < 5; i1++) {
        dv[i1] = e.a[(20 + i1)];
      }
    } else {
      for (int i2 = 1; i2 < 5; i2++) {
        dv[i2] = -1;
      }
    }
    this.bL = e.a[25];
    cD = e.a[26];
    if (cD == 0) {
      cD = 1;
    }
  }
  
  private final void U()
  {
    dN = null;
    if ((this.cl == 2) && (this.dr) && ((cn == 3) || (cn == 4) || (cn == 5) || (cn == 7)))
    {
      byte[] arrayOfByte;
      if ((arrayOfByte = e.l.a(e.a(P), -1)) != null)
      {
        try
        {
          cI = b(arrayOfByte);
          dN = a(arrayOfByte, false, 0, 0, 0, 0);
          this.ds = a(arrayOfByte, true);
          if (this.ds == 0) {
            this.ds = 256;
          }
          this.dq = a(arrayOfByte, false);
          if (this.dq == 0) {
            this.dq = 256;
          }
        }
        catch (Exception localException)
        {
          this.cl = 0;
          this.dr = false;
        }
      }
      else
      {
        this.cl = 0;
        this.dr = false;
        return;
      }
      this.cl = 2;
      this.dr = true;
    }
  }
  
  private static String b(boolean paramBoolean)
  {
    String[][] arrayOfString = e.l.b(e.a(G));
    if (paramBoolean) {
      return arrayOfString[1][cn];
    }
    return arrayOfString[0][0];
  }
  
  /* Error */
  private final void V()
  {
    // Byte code:
    //   0: aload_0
    //   1: iconst_0
    //   2: putfield 112	h:ag	B
    //   5: bipush 72
    //   7: anewarray 2	[B
    //   10: putstatic 273	h:dL	[[B
    //   13: bipush 72
    //   15: anewarray 3	[I
    //   18: putstatic 208	h:cG	[[I
    //   21: aload_0
    //   22: invokespecial 455	h:U	()V
    //   25: aload_0
    //   26: bipush 55
    //   28: invokespecial 635	h:m	(I)V
    //   31: iconst_0
    //   32: istore 6
    //   34: goto +96 -> 130
    //   37: getstatic 161	h:bU	[Z
    //   40: iload 6
    //   42: baload
    //   43: ifeq +84 -> 127
    //   46: aload_0
    //   47: dup
    //   48: getfield 112	h:ag	B
    //   51: iconst_1
    //   52: iadd
    //   53: i2b
    //   54: putfield 112	h:ag	B
    //   57: getstatic 372	e:l	Le;
    //   60: new 25	java/lang/StringBuffer
    //   63: dup
    //   64: invokespecial 425	java/lang/StringBuffer:<init>	()V
    //   67: getstatic 60	h:Q	[I
    //   70: invokestatic 461	e:a	([I)Ljava/lang/String;
    //   73: invokevirtual 536	java/lang/StringBuffer:append	(Ljava/lang/String;)Ljava/lang/StringBuffer;
    //   76: iload 6
    //   78: invokevirtual 535	java/lang/StringBuffer:append	(I)Ljava/lang/StringBuffer;
    //   81: invokevirtual 667	java/lang/StringBuffer:toString	()Ljava/lang/String;
    //   84: iconst_m1
    //   85: invokevirtual 476	e:a	(Ljava/lang/String;I)[B
    //   88: astore_3
    //   89: getstatic 208	h:cG	[[I
    //   92: iload 6
    //   94: aload_3
    //   95: invokestatic 554	h:b	([B)[I
    //   98: aastore
    //   99: getstatic 273	h:dL	[[B
    //   102: iload 6
    //   104: aload_3
    //   105: iconst_0
    //   106: iconst_0
    //   107: iconst_0
    //   108: iconst_0
    //   109: iconst_0
    //   110: invokestatic 495	h:a	([BZIIII)[B
    //   113: aastore
    //   114: getstatic 273	h:dL	[[B
    //   117: iload 6
    //   119: aaload
    //   120: invokestatic 497	h:a	([B)V
    //   123: goto +4 -> 127
    //   126: pop
    //   127: iinc 6 1
    //   130: iload 6
    //   132: bipush 72
    //   134: if_icmplt -97 -> 37
    //   137: aload_0
    //   138: bipush 60
    //   140: invokespecial 635	h:m	(I)V
    //   143: iconst_0
    //   144: istore 7
    //   146: bipush 61
    //   148: anewarray 2	[B
    //   151: putstatic 274	h:dM	[[B
    //   154: getstatic 372	e:l	Le;
    //   157: getstatic 61	h:R	[I
    //   160: invokestatic 461	e:a	([I)Ljava/lang/String;
    //   163: iconst_m1
    //   164: invokevirtual 476	e:a	(Ljava/lang/String;I)[B
    //   167: astore_3
    //   168: aload_0
    //   169: invokespecial 448	h:N	()I
    //   172: istore 9
    //   174: aload_3
    //   175: invokestatic 554	h:b	([B)[I
    //   178: putstatic 209	h:cH	[I
    //   181: aload_0
    //   182: bipush 65
    //   184: invokespecial 635	h:m	(I)V
    //   187: iconst_1
    //   188: istore 10
    //   190: goto +49 -> 239
    //   193: getstatic 274	h:dM	[[B
    //   196: iload 10
    //   198: aload_3
    //   199: iconst_1
    //   200: getstatic 82	h:aC	[[S
    //   203: iload 10
    //   205: aaload
    //   206: iconst_0
    //   207: saload
    //   208: getstatic 82	h:aC	[[S
    //   211: iload 10
    //   213: aaload
    //   214: iconst_1
    //   215: saload
    //   216: getstatic 82	h:aC	[[S
    //   219: iload 10
    //   221: aaload
    //   222: iconst_2
    //   223: saload
    //   224: getstatic 82	h:aC	[[S
    //   227: iload 10
    //   229: aaload
    //   230: iconst_3
    //   231: saload
    //   232: invokestatic 495	h:a	([BZIIII)[B
    //   235: aastore
    //   236: iinc 10 1
    //   239: iload 10
    //   241: iload 9
    //   243: if_icmplt -50 -> 193
    //   246: aload_0
    //   247: bipush 70
    //   249: invokespecial 635	h:m	(I)V
    //   252: bipush 61
    //   254: anewarray 2	[B
    //   257: putstatic 276	h:dO	[[B
    //   260: aload_0
    //   261: invokespecial 449	h:O	()I
    //   264: istore 9
    //   266: bipush 6
    //   268: anewarray 3	[I
    //   271: putstatic 211	h:cJ	[[I
    //   274: aload_0
    //   275: bipush 75
    //   277: invokespecial 635	h:m	(I)V
    //   280: iconst_0
    //   281: istore 11
    //   283: iconst_1
    //   284: istore 13
    //   286: goto +229 -> 515
    //   289: getstatic 162	h:bV	[Z
    //   292: iload 13
    //   294: baload
    //   295: ifeq +217 -> 512
    //   298: getstatic 372	e:l	Le;
    //   301: new 25	java/lang/StringBuffer
    //   304: dup
    //   305: invokespecial 425	java/lang/StringBuffer:<init>	()V
    //   308: getstatic 62	h:S	[I
    //   311: invokestatic 461	e:a	([I)Ljava/lang/String;
    //   314: invokevirtual 536	java/lang/StringBuffer:append	(Ljava/lang/String;)Ljava/lang/StringBuffer;
    //   317: iload 13
    //   319: invokevirtual 535	java/lang/StringBuffer:append	(I)Ljava/lang/StringBuffer;
    //   322: invokevirtual 667	java/lang/StringBuffer:toString	()Ljava/lang/String;
    //   325: iconst_m1
    //   326: invokevirtual 476	e:a	(Ljava/lang/String;I)[B
    //   329: astore_3
    //   330: getstatic 211	h:cJ	[[I
    //   333: iload 13
    //   335: aload_3
    //   336: invokestatic 554	h:b	([B)[I
    //   339: aastore
    //   340: iload 13
    //   342: iconst_5
    //   343: if_icmpne +10 -> 353
    //   346: iload 9
    //   348: istore 11
    //   350: goto +15 -> 365
    //   353: getstatic 238	h:ck	[[B
    //   356: iload 13
    //   358: iconst_1
    //   359: iadd
    //   360: aaload
    //   361: iconst_0
    //   362: baload
    //   363: istore 11
    //   365: getstatic 238	h:ck	[[B
    //   368: iload 13
    //   370: aaload
    //   371: iconst_0
    //   372: baload
    //   373: istore 12
    //   375: goto +130 -> 505
    //   378: iload 13
    //   380: tableswitch	default:+79->459, 1:+28->408, 2:+45->425, 3:+62->442
    //   408: iload 12
    //   410: bipush 8
    //   412: if_icmpeq +90 -> 502
    //   415: iload 12
    //   417: bipush 9
    //   419: if_icmpne +40 -> 459
    //   422: goto +80 -> 502
    //   425: iload 12
    //   427: bipush 8
    //   429: if_icmpeq +73 -> 502
    //   432: iload 12
    //   434: bipush 9
    //   436: if_icmpne +23 -> 459
    //   439: goto +63 -> 502
    //   442: iload 12
    //   444: bipush 8
    //   446: if_icmpeq +56 -> 502
    //   449: iload 12
    //   451: bipush 9
    //   453: if_icmpne +6 -> 459
    //   456: goto +46 -> 502
    //   459: getstatic 276	h:dO	[[B
    //   462: iload 12
    //   464: aload_3
    //   465: iconst_1
    //   466: getstatic 83	h:aD	[[S
    //   469: iload 12
    //   471: aaload
    //   472: iconst_0
    //   473: saload
    //   474: getstatic 83	h:aD	[[S
    //   477: iload 12
    //   479: aaload
    //   480: iconst_1
    //   481: saload
    //   482: getstatic 83	h:aD	[[S
    //   485: iload 12
    //   487: aaload
    //   488: iconst_2
    //   489: saload
    //   490: getstatic 83	h:aD	[[S
    //   493: iload 12
    //   495: aaload
    //   496: iconst_3
    //   497: saload
    //   498: invokestatic 495	h:a	([BZIIII)[B
    //   501: aastore
    //   502: iinc 12 1
    //   505: iload 12
    //   507: iload 11
    //   509: if_icmplt -131 -> 378
    //   512: iinc 13 1
    //   515: iload 13
    //   517: bipush 6
    //   519: if_icmplt -230 -> 289
    //   522: aload_0
    //   523: bipush 80
    //   525: invokespecial 635	h:m	(I)V
    //   528: aload_0
    //   529: aconst_null
    //   530: putfield 251	h:cx	[Ljavax/microedition/lcdui/Image;
    //   533: invokestatic 445	h:K	()V
    //   536: aload_0
    //   537: bipush 12
    //   539: anewarray 31	javax/microedition/lcdui/Image
    //   542: putfield 251	h:cx	[Ljavax/microedition/lcdui/Image;
    //   545: aload_0
    //   546: getfield 251	h:cx	[Ljavax/microedition/lcdui/Image;
    //   549: iconst_0
    //   550: getstatic 64	h:U	[I
    //   553: invokestatic 461	e:a	([I)Ljava/lang/String;
    //   556: invokestatic 466	e:a	(Ljava/lang/String;)Ljavax/microedition/lcdui/Image;
    //   559: aastore
    //   560: goto +4 -> 564
    //   563: pop
    //   564: aload_0
    //   565: getfield 251	h:cx	[Ljavax/microedition/lcdui/Image;
    //   568: bipush 11
    //   570: getstatic 65	h:V	[I
    //   573: invokestatic 461	e:a	([I)Ljava/lang/String;
    //   576: invokestatic 466	e:a	(Ljava/lang/String;)Ljavax/microedition/lcdui/Image;
    //   579: aastore
    //   580: goto +4 -> 584
    //   583: pop
    //   584: aload_0
    //   585: bipush 85
    //   587: invokespecial 635	h:m	(I)V
    //   590: iconst_0
    //   591: istore 14
    //   593: goto +73 -> 666
    //   596: getstatic 307	h:dt	[B
    //   599: iload 14
    //   601: baload
    //   602: ifge +6 -> 608
    //   605: goto +58 -> 663
    //   608: aload_0
    //   609: getfield 251	h:cx	[Ljavax/microedition/lcdui/Image;
    //   612: getstatic 307	h:dt	[B
    //   615: iload 14
    //   617: baload
    //   618: new 25	java/lang/StringBuffer
    //   621: dup
    //   622: invokespecial 425	java/lang/StringBuffer:<init>	()V
    //   625: getstatic 66	h:W	[I
    //   628: invokestatic 461	e:a	([I)Ljava/lang/String;
    //   631: invokevirtual 536	java/lang/StringBuffer:append	(Ljava/lang/String;)Ljava/lang/StringBuffer;
    //   634: getstatic 307	h:dt	[B
    //   637: iload 14
    //   639: baload
    //   640: invokevirtual 535	java/lang/StringBuffer:append	(I)Ljava/lang/StringBuffer;
    //   643: getstatic 54	h:L	[I
    //   646: invokestatic 461	e:a	([I)Ljava/lang/String;
    //   649: invokevirtual 536	java/lang/StringBuffer:append	(Ljava/lang/String;)Ljava/lang/StringBuffer;
    //   652: invokevirtual 667	java/lang/StringBuffer:toString	()Ljava/lang/String;
    //   655: invokestatic 466	e:a	(Ljava/lang/String;)Ljavax/microedition/lcdui/Image;
    //   658: aastore
    //   659: goto +4 -> 663
    //   662: pop
    //   663: iinc 14 1
    //   666: iload 14
    //   668: getstatic 307	h:dt	[B
    //   671: arraylength
    //   672: if_icmplt -76 -> 596
    //   675: aload_0
    //   676: bipush 87
    //   678: invokespecial 635	h:m	(I)V
    //   681: aload_0
    //   682: invokespecial 447	h:M	()V
    //   685: return
    // Local variable table:
    //   start	length	slot	name	signature
    //   0	686	0	this	h
    //   88	377	3	arrayOfByte	byte[]
    //   32	103	6	i1	int
    //   144	1	7	i2	int
    //   172	175	9	i3	int
    //   126	1	10	localException1	Exception
    //   188	56	10	i4	int
    //   281	229	11	i5	int
    //   563	1	11	localException2	Exception
    //   373	137	12	i6	int
    //   583	1	12	localException3	Exception
    //   284	236	13	i7	int
    //   662	1	13	localException4	Exception
    //   591	82	14	i8	int
    // Exception table:
    //   from	to	target	type
    //   57	123	126	java/lang/Exception
    //   545	560	563	java/lang/Exception
    //   564	580	583	java/lang/Exception
    //   608	659	662	java/lang/Exception
  }
  
  static void b(int paramInt)
  {
    int i1 = 27 + (paramInt - 1) * 8;
    for (int i2 = 0; i2 < 5; i2++)
    {
      dv[i2] = e.a[i1];
      i1++;
    }
    if ((dv[0] == 0) && (dv[1] == 0) && (dv[2] == 0) && (dv[3] == 0) && (dv[4] == 0)) {
      for (int i3 = 0; i3 < 5; i3++) {
        dv[0] = -1;
      }
    }
    cj = a(e.a[i1], e.a[(i1 + 1)]);
    i1 += 2;
    aM = e.a[i1];
  }
  
  private final void W()
  {
    this.cy = null;
    this.cy = new Image[10];
    int i1 = 0;
    while (i1 < 10) {
      try
      {
        try
        {
          this.cy[i1] = e.a(e.a(K) + i1 + e.a(L));
          this.cy[i1] = a(this.cy[i1]);
        }
        catch (OutOfMemoryError localOutOfMemoryError)
        {
          this.eb = 240;
          this.ea = 122;
          for (i1 = 0; i1 < 10; i1++) {
            this.cy[i1] = null;
          }
          return;
        }
        i1++;
      }
      catch (Exception localException)
      {
        this.eb = 240;
        this.ea = 122;
        for (i1 = 0; i1 < 10; i1++) {
          this.cy[i1] = null;
        }
        return;
      }
    }
  }
  
  public final void a(boolean paramBoolean)
  {
    b = 0;
    e(b);
    this.bO = true;
    this.bc = true;
    if (paramBoolean)
    {
      long l1 = System.currentTimeMillis();
      this.cy = null;
      this.bQ = null;
      this.cw[1] = null;
      try
      {
        try
        {
          this.bw = e.a(e.a(T));
        }
        catch (OutOfMemoryError localOutOfMemoryError1) {}
        try
        {
          this.cu = e.a(e.a(aa));
        }
        catch (Exception localException2) {}
      }
      catch (Exception localException1) {}
      if (this.cu == null)
      {
        this.aw = (!this.aw);
        return;
      }
      this.dE = ((byte)(this.cu.getHeight() + 2));
      this.bN = b(true);
      m(0);
      ab();
      try
      {
        this.cE = e.a(e.a(p));
      }
      catch (Exception localException3) {}
      cY = 0;
      bU = new boolean[72];
      m(3);
      bS = new boolean[56];
      m(6);
      bV = new boolean[7];
      m(8);
      dS = new int[3];
      m(10);
      aN = new int[62880];
      m(12);
      k(cn);
      m(20);
      S();
      m(30);
      cz = (short)n.length;
      dz = (short)(cz + cA);
      dl = (short)(dz + 20);
      Q();
      m(40);
      R();
      m(50);
      V();
      m(90);
      bU = null;
      bS = null;
      bV = null;
      m(100);
      long l2;
      if ((l2 = System.currentTimeMillis()) - l1 < 3000L)
      {
        l1 = l2 - l1;
        try
        {
          Thread.sleep(3000L - l1);
        }
        catch (Exception localException4) {}
      }
      this.i = false;
      ce = false;
      this.cE = null;
      this.cu = null;
      b((byte)(1 + cn));
      o();
      a(cN, cY);
      a(aQ);
      d(2);
      this.bL = 0;
    }
    else
    {
      this.bN = b(false);
      try
      {
        this.bw = e.a(e.a(T));
      }
      catch (Exception localException5) {}
      try
      {
        this.cu = e.a(e.a(aa));
      }
      catch (Exception localException6) {}
      if (this.cu == null)
      {
        this.aw = (!this.aw);
        return;
      }
      this.dE = ((byte)(this.cu.getHeight() + 2));
      m(0);
      try
      {
        this.cE = e.a(e.a(p));
      }
      catch (Exception localException7) {}
      this.cg = 3;
      aN = null;
      this.cx = null;
      m(7);
      az = null;
      m(14);
      aO = null;
      m(21);
      br = null;
      m(28);
      bl = null;
      m(35);
      l = null;
      m(42);
      j = null;
      m(49);
      n = null;
      m(63);
      h = null;
      m(70);
      g = null;
      m(77);
      bz = null;
      bp = null;
      m(80);
      by = null;
      bo = null;
      dk = null;
      al = null;
      aQ = null;
      cG = null;
      dL = null;
      dN = null;
      cI = null;
      m(85);
      cH = null;
      dM = null;
      cJ = null;
      dO = null;
      m(92);
      aD = null;
      aC = null;
      aB = null;
      ck = null;
      m(99);
      P();
      W();
      m(100);
      this.cE = null;
      this.cu = null;
      this.i = true;
      ce = true;
      try
      {
        try
        {
          this.bQ = e.a(e.a(T));
        }
        catch (OutOfMemoryError localOutOfMemoryError2) {}
        this.bO = false;
      }
      catch (Exception localException8) {}
    }
    this.bP = 0;
  }
  
  private void b(byte paramByte)
  {
    if ((paramByte == 1) || (paramByte == 13)) {
      d(3);
    }
    ce = true;
    this.i = true;
    this.cg = 13;
    this.cf = 13;
    this.bW = paramByte;
    w();
  }
  
  public final void f()
  {
    try
    {
      NET_Lizard.a.platformRequest(this.m);
      this.aw = false;
      return;
    }
    catch (Exception localException)
    {
      this.cg = 18;
    }
  }
  
  private static final void X()
  {
    if (b == 0)
    {
      n[0].d[0] = dn[df];
      n[0].d[1] = aA[df];
      dW = true;
      return;
    }
    if (dc < 30) {
      dc += 1;
    }
  }
  
  private static final void Y()
  {
    n[0].d[0] = aA[df];
    n[0].d[1] = (-dn[df]);
  }
  
  private static final void Z()
  {
    n[0].d[0] = (-aA[df]);
    n[0].d[1] = dn[df];
  }
  
  private static final void aa()
  {
    if (b == 0)
    {
      n[0].d[0] = (-dn[df]);
      n[0].d[1] = (-aA[df]);
      dW = true;
      return;
    }
    if (dc > -30) {
      dc -= 1;
    }
  }
  
  public static final void g()
  {
    a(bJ, true);
  }
  
  private static Image a(Image paramImage)
  {
    Image localImage;
    Graphics localGraphics;
    (localGraphics = (localImage = Image.createImage(paramImage.getWidth(), paramImage.getHeight())).getGraphics()).drawImage(paramImage, 0, 0, 20);
    return localImage;
  }
  
  static final void a(int paramInt1, int paramInt2, int paramInt3, int paramInt4, int paramInt5, int paramInt6)
  {
    int i1 = ((paramInt5 & 0xFF0000) >> 16) * paramInt6;
    int i2 = ((paramInt5 & 0xFF00) >> 8) * paramInt6;
    int i3 = (paramInt5 & 0xFF) * paramInt6;
    int i4 = (short)(255 - paramInt6);
    int[] arrayOfInt = aN;
    paramInt2 = paramInt2 * 240 + paramInt1;
    do
    {
      int i6 = paramInt3;
      do
      {
        int i5 = arrayOfInt[(paramInt2 + i6)];
        if (i4 == 0) {
          arrayOfInt[(paramInt2 + i6)] = paramInt5;
        } else {
          arrayOfInt[(paramInt2 + i6)] = ((((i5 & 0xFF0000) >> 16) * i4 + i1 >> 8 << 16) + (((i5 & 0xFF00) >> 8) * i4 + i2 >> 8 << 8) + ((i5 & 0xFF) * i4 + i3 >> 8));
        }
        i6--;
      } while (i6 >= 0);
      paramInt2 += 240;
      paramInt4--;
    } while (paramInt4 >= 0);
  }
  
  private final void g(Graphics paramGraphics)
  {
    paramGraphics.setClip(0, 0, 240, 320);
    paramGraphics.setColor(16777215);
    paramGraphics.fillRect(0, 0, 240, 320);
    paramGraphics.drawImage(this.bQ, 120 - (this.bQ.getWidth() >> 1), 160 - (this.bQ.getHeight() >> 1), 20);
    int i1 = 0;
    int i2 = 160 - (this.cv.length * this.bi.b() >> 1);
    if (this.cv != null) {
      for (int i3 = 0; i3 < this.cv.length; i3++)
      {
        i1 = 120 - (this.bi.a(this.cv[i3]) >> 1);
        if (this.cv[i3] != null) {
          this.bi.a(paramGraphics, this.cv[i3], i1, i2, 20);
        }
        i2 += this.bi.b() + 1;
      }
    }
  }
  
  public final void paint(Graphics paramGraphics)
  {
    if (this.dU)
    {
      g(paramGraphics);
      return;
    }
    if (this.bT != null) {
      try
      {
        paramGraphics.setClip(0, 0, 240, 320);
        h(paramGraphics);
        return;
      }
      catch (Exception localException1)
      {
        return;
      }
    }
    try
    {
      if (this.am >= 0)
      {
        c(paramGraphics);
        return;
      }
      if (this.dV)
      {
        paramGraphics.setColor(0);
        paramGraphics.fillRect(0, 0, 240, 320);
        this.bi.a(paramGraphics, this.bN, 240 - this.bi.a(this.bN) >> 1, 320 - this.bi.b() >> 1, 20);
        return;
      }
      if (this.ba)
      {
        e(paramGraphics);
        return;
      }
      if (this.bO)
      {
        if (this.bc) {
          a(paramGraphics);
        }
        d(paramGraphics);
        return;
      }
      if (ce)
      {
        paramGraphics.setColor(0);
        paramGraphics.fillRect(0, 288, 240, 34);
        paramGraphics.fillRect(0, 0, 240, 30);
        if ((this.cg == 1) || (this.cg == 9) || (this.cg == 13)) {
          paramGraphics.drawRGB(aN, 0, 240, 0, 30, 240, 258, false);
        }
        this.cd.a(paramGraphics, this.cg);
        return;
      }
      f(paramGraphics);
      b(paramGraphics);
      return;
    }
    catch (Exception localException2) {}
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
  
  private final void g(j paramj)
  {
    int[] arrayOfInt1 = paramj.d;
    int[] arrayOfInt2 = paramj.h;
    int[] arrayOfInt3 = dS;
    int i1 = 0;
    int[] arrayOfInt4 = az;
    int i3 = (short)paramj.v;
    if (!paramj.f)
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
    if (cb[i3] < i1)
    {
      i1 = cb[i3];
      arrayOfInt3[0] *= i1;
      arrayOfInt3[1] *= i1;
      arrayOfInt3[2] *= i1;
    }
    else if ((!paramj.f) && (i1 > 0))
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
    paramj.p += arrayOfInt2[0];
    paramj.q += arrayOfInt2[1];
    paramj.r += arrayOfInt2[2];
    if (a(paramj, i1)) {
      paramj.f = false;
    } else {
      paramj.f = true;
    }
    f(paramj);
    arrayOfInt1[0] = 0;
    arrayOfInt1[1] = 0;
    arrayOfInt1[2] = 0;
  }
  
  private final boolean b(j paramj1, j paramj2)
  {
    int i1 = paramj1.p - paramj2.p >> 16;
    int i2 = paramj1.q - paramj2.q >> 16;
    int i3 = paramj1.r - paramj2.r >> 16;
    if (i1 * paramj1.u[0] + i2 * paramj1.u[1] > 0L) {
      return false;
    }
    return i1 * i1 + i2 * i2 + i3 * i3 < this.bZ[aM];
  }
  
  private static final void a(i parami)
  {
    parami.d = ((short)(int)(7864320L + parami.a * cC / parami.c >> 16));
    parami.e = ((short)(int)(8519680L - parami.b * cC / parami.c >> 16));
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
  
  private final void a(long paramLong, boolean paramBoolean)
  {
    long l1 = System.currentTimeMillis();
    a();
    long l2 = System.currentTimeMillis();
    if ((this.cg != 10) && (this.cg != 11) && (this.cg != 4) && (this.cg != 18) && (paramBoolean))
    {
      if (paramLong == 0L) {
        paramLong = 300L;
      } else {
        paramLong = 77L;
      }
      if (l2 - l1 < paramLong) {
        try
        {
          long l3 = (paramLong - (l2 - l1)) / 10L;
          for (int i1 = 0; i1 < l3; i1++)
          {
            Thread.sleep(10L);
            if (this.bE == 0) {
              break;
            }
          }
          return;
        }
        catch (Exception localException) {}
      }
    }
  }
  
  public final void h()
  {
    if (this.cl == 0) {
      this.cl = 2;
    } else {
      this.cl = 0;
    }
    this.bO = true;
    m(0);
    U();
    m(50);
    m(100);
    this.bO = false;
  }
  
  public final void i()
  {
    this.bO = true;
    this.bc = true;
    m(0);
    try
    {
      this.cE = e.a(e.a(p));
    }
    catch (Exception localException) {}
    ab();
    l = null;
    m(10);
    j = null;
    m(20);
    n = null;
    m(40);
    g = null;
    m(50);
    h = null;
    m(60);
    dS = new int[3];
    dA = new int[20][6];
    bU = new boolean[72];
    bS = new boolean[56];
    bV = new boolean[7];
    m(65);
    k(cn);
    m(70);
    S();
    m(80);
    m(90);
    m(100);
    this.cE = null;
    bU = null;
    bS = null;
    bV = null;
    this.bO = false;
    this.i = false;
    ce = false;
    b((byte)(1 + cn));
    o();
    a(cN, cY);
    a(aQ);
    d(2);
  }
  
  private void ab()
  {
    this.ak.length();
    k = 1;
    b = 0;
    e(b);
    this.ch = 0;
    dc = 0;
    bd = 0;
    cV = 4;
    cR = 0;
    cS = 0;
    bt = 0;
    dK = 0;
    bF = 0;
    aG = 0;
    cP = false;
    this.dG = 0;
    eh = 0;
    ap = 0;
    dw = 0;
    eg = 0;
    db = 0;
    dB = 0;
    dm = 0;
    dk = new int[20][12];
    dA = new int[20][6];
    b = 0;
    for (int i1 = 1; i1 < dt.length; i1++)
    {
      dt[i1] = ((byte)(dv[i1] + 1));
      bX[i1] = ah[0][dt[i1]];
      bY[i1] = ah[1][dt[i1]];
      ai[i1] = bX[i1];
      aj[i1] = bY[i1];
    }
    af = 0;
    for (int i2 = 1; i2 < 4; i2++) {
      if (dt[i2] != 0)
      {
        af = (byte)(af + 1);
        if (i2 != 3)
        {
          eg = dt[i2];
          dw = (byte)i2;
        }
      }
    }
  }
  
  private final void a(Graphics paramGraphics, String paramString, int paramInt1, int paramInt2)
  {
    int i1 = paramString.length();
    for (int i2 = 0; i2 < i1; i2++) {
      b(paramGraphics, paramString.charAt(i2) - '\023', paramInt1 + i2 * (this.o + 1), paramInt2);
    }
  }
  
  private void b(Graphics paramGraphics, int paramInt1, int paramInt2, int paramInt3)
  {
    paramInt2 += ax[paramInt1][4];
    paramInt3 += ax[paramInt1][5];
    paramGraphics.setClip(paramInt2, paramInt3, ax[paramInt1][2], ax[paramInt1][3]);
    paramGraphics.drawImage(this.cw[ax[paramInt1][6]], paramInt2 - ax[paramInt1][0], paramInt3 - ax[paramInt1][1], 20);
    paramGraphics.setClip(0, 0, 240, 320);
  }
  
  public final void a(Graphics paramGraphics, int paramInt1, int paramInt2, int paramInt3)
  {
    paramGraphics.setClip(paramInt2, paramInt3, ax[paramInt1][2], ax[paramInt1][3]);
    paramGraphics.drawImage(this.cw[ax[paramInt1][6]], paramInt2 - ax[paramInt1][0], paramInt3 - ax[paramInt1][1], 20);
    paramGraphics.setClip(0, 0, 240, 320);
  }
  
  private final void c(Graphics paramGraphics, int paramInt1, int paramInt2, int paramInt3)
  {
    paramGraphics.setClip(paramInt2, paramInt3, aB[paramInt1][2], aB[paramInt1][3]);
    paramGraphics.drawImage(this.cx[aB[paramInt1][6]], paramInt2 - aB[paramInt1][0], paramInt3 - aB[paramInt1][1], 20);
    paramGraphics.setClip(0, 0, 240, 320);
  }
  
  private void ac()
  {
    if (this.bg) {
      b((byte)17);
    }
    if (g(4) < 2) {
      return;
    }
    int i1 = g(2) + 1;
    if (dt[i1] == 0)
    {
      if (i1 == 1) {
        i1 = 2;
      } else {
        i1 = 1;
      }
      if (dt[i1] == 0) {
        return;
      }
      d(1);
      int tmp66_65 = i1;
      byte[] tmp66_62 = aj;
      tmp66_62[tmp66_65] = ((byte)(tmp66_62[tmp66_65] + (g(5) + 3) * i1));
      if (aj[i1] > bY[i1]) {
        aj[i1] = bY[i1];
      }
    }
    else
    {
      d(1);
      int tmp113_112 = i1;
      byte[] tmp113_109 = aj;
      tmp113_109[tmp113_112] = ((byte)(tmp113_109[tmp113_112] + (g(5) + 3) * i1));
      if (aj[i1] > bY[i1]) {
        aj[i1] = bY[i1];
      }
    }
    this.du = i1;
    this.ch = 20;
  }
  
  private static byte[] l(int paramInt)
  {
    byte[] arrayOfByte = new byte[2];
    int i1 = paramInt / 256;
    int i2 = paramInt - 256 * i1;
    arrayOfByte[0] = j(i1);
    arrayOfByte[1] = j(i2);
    return arrayOfByte;
  }
  
  private static int a(byte paramByte1, byte paramByte2)
  {
    return 256 * a(paramByte1) + a(paramByte2);
  }
  
  public final void run()
  {
    String str = null;
    try
    {
      str = NET_Lizard.a.getAppProperty(e.a(dy));
    }
    catch (Exception localException1) {}
    str = a(str);
    if (!aI) {
      aI = a(e.a(bR), e.a(dy));
    }
    if (!aI) {
      try
      {
        if ((str == null) || (str.length() < 1) || (!b(str, e.a(e)))) {
          aI = true;
        }
      }
      catch (Exception localException2)
      {
        aI = true;
      }
    }
    if (aI) {
      try
      {
        this.aH = e.l.b(e.a(a));
        if ((this.aH == null) || (this.aH[0] == null) || (this.aH[0].length <= 0)) {
          this.aw = false;
        }
      }
      catch (Exception localException3)
      {
        this.aw = false;
      }
    }
    aI = false;
    long l1 = 0L;
    if (this.aw) {
      J();
    }
    boolean bool = false;
    long l2 = 7L;
    long l3 = 0L;
    int i1 = 0;
    int i2 = 0;
    long l4 = 0L;
    while (this.aw)
    {
      if (aI) {
        y();
      }
      try
      {
        Thread.sleep(l2);
      }
      catch (Exception localException4) {}
      l3 = l2;
      l2 = 7L;
      bool = false;
      be = false;
      if (this.bE != 0)
      {
        if ((this.bC) || (this.bD)) {
          if (this.bT == null)
          {
            H();
            this.bC = false;
          }
          else
          {
            this.bG = true;
            F();
            l2 = 500L;
            if (l3 > 7L) {
              l2 = 35L;
            }
          }
        }
        bool = true;
      }
      if (this.aT != 1L)
      {
        i1 = 0;
        if ((ce) && (this.aT > 10L) && ((this.cg == 1) || (this.cg == 13))) {
          i1 = 1;
        }
        if (i1 != i2)
        {
          if (i1 != 0) {
            l4 = System.currentTimeMillis() - this.aT;
          } else {
            this.aT = (System.currentTimeMillis() - l4);
          }
          i2 = i1;
        }
        if (i1 != 0) {
          this.aT = 0L;
        }
        if (this.cf != this.cg)
        {
          this.cf = this.cg;
          w();
        }
        if (!ce) {
          a();
        } else {
          a(0L, bool);
        }
      }
    }
    j();
    ad();
    NET_Lizard.a();
  }
  
  private void m(int paramInt)
  {
    this.bP = ((byte)paramInt);
    repaint();
    serviceRepaints();
  }
  
  final void j()
  {
    e.a[12] = (this.bg == true ? 0 : 1);
    e.a[27] = this.cl;
    if (dJ) {
      e.a[14] = 1;
    } else {
      e.a[14] = 0;
    }
    if (dx) {
      e.a[15] = 1;
    } else {
      e.a[15] = 0;
    }
    if (dT) {
      e.a[16] = 1;
    } else {
      e.a[16] = 0;
    }
    e.a[17] = cn;
    e.a[18] = aM;
    if (!au)
    {
      byte[] arrayOfByte = l(cj);
      e.a[19] = arrayOfByte[0];
      e.a[20] = arrayOfByte[1];
    }
    for (int i1 = 1; i1 < 5; i1++) {
      e.a[(20 + i1)] = dv[i1];
    }
    e.a[25] = this.bL;
    if (!at) {
      e.a[26] = cD;
    }
    e.j = true;
    e.b();
  }
  
  static void c(int paramInt)
  {
    int i1 = 27 + (paramInt - 1) * 8;
    for (int i2 = 0; i2 < 5; i2++)
    {
      e.a[i1] = dv[i2];
      i1++;
    }
    byte[] arrayOfByte = l(cj);
    e.a[i1] = arrayOfByte[0];
    e.a[(i1 + 1)] = arrayOfByte[1];
    i1 += 2;
    e.a[i1] = aM;
  }
  
  private final int a(int[] paramArrayOfInt1, int paramInt1, int[] paramArrayOfInt2, int paramInt2)
  {
    b localb = j[paramInt1];
    if (j[paramInt1].e) {
      return -1;
    }
    i[] arrayOfi1 = br;
    i[] arrayOfi2 = bl;
    int i1 = 0;
    int[] arrayOfInt = dg;
    arrayOfi1[0] = localb.b[3];
    arrayOfi1[1] = localb.b[1];
    arrayOfi1[2] = localb.b[0];
    arrayOfi1[3] = localb.b[2];
    int i3;
    switch (i3 = localb.a)
    {
    case 1: 
      if ((Math.max(arrayOfi1[0].k, Math.max(arrayOfi1[1].k, arrayOfi1[2].k)) > arrayOfInt[1]) && (Math.max(arrayOfi1[0].l, Math.max(arrayOfi1[1].l, arrayOfi1[2].l)) > arrayOfInt[2])) {
        i3 = Math.abs(arrayOfInt[(i3 - 1)] - arrayOfi1[0].j);
      } else {
        i3 = 9830401;
      }
      break;
    case 2: 
      if ((Math.max(arrayOfi1[0].j, Math.max(arrayOfi1[1].j, arrayOfi1[2].j)) > arrayOfInt[0]) && (Math.max(arrayOfi1[0].l, Math.max(arrayOfi1[1].l, arrayOfi1[2].l)) > arrayOfInt[2])) {
        i3 = Math.abs(arrayOfInt[(i3 - 1)] - arrayOfi1[0].k);
      } else {
        i3 = 9830401;
      }
      break;
    case 3: 
      if ((Math.max(arrayOfi1[0].k, Math.max(arrayOfi1[1].k, arrayOfi1[2].k)) > arrayOfInt[1]) && (Math.max(arrayOfi1[0].j, Math.max(arrayOfi1[1].j, arrayOfi1[2].j)) > arrayOfInt[0])) {
        i3 = Math.abs(arrayOfInt[(i3 - 1)] - arrayOfi1[0].l);
      } else {
        i3 = 9830401;
      }
      break;
    }
    if (i3 <= 9830400)
    {
      localb.e = true;
      paramArrayOfInt2[aP] = paramArrayOfInt1[0];
      paramArrayOfInt2[(aP + 1)] = paramArrayOfInt1[1];
      paramArrayOfInt2[(aP + 2)] = paramArrayOfInt1[2];
      paramArrayOfInt2[(aP + 3)] = paramArrayOfInt1[3];
      if (localb.c == paramInt2)
      {
        paramArrayOfInt2[(aP + 4)] = localb.d;
        aP += 5;
        return localb.d;
      }
      paramArrayOfInt2[(aP + 4)] = localb.c;
      aP += 5;
      return localb.c;
    }
    for (int i2 = 3; i2 >= 0; i2--) {
      b(arrayOfi1[i2]);
    }
    if ((i1 = c(arrayOfi2, arrayOfi1, paramArrayOfInt1[2], 4)) == 0) {
      return -1;
    }
    if ((i1 = a(arrayOfi1, arrayOfi2, paramArrayOfInt1[3], i1)) == 0) {
      return -1;
    }
    if ((i1 = d(arrayOfi2, arrayOfi1, paramArrayOfInt1[1], i1)) == 0) {
      return -1;
    }
    if ((i1 = b(arrayOfi1, arrayOfi2, paramArrayOfInt1[0], i1)) == 0) {
      return -1;
    }
    for (i2 = i1 - 1; i2 >= 0; i2--) {
      a(arrayOfi1[i2]);
    }
    int i6 = arrayOfi1[0].e;
    int i7 = arrayOfi1[0].e;
    int i4 = arrayOfi1[0].d;
    int i5 = arrayOfi1[0].d;
    for (i2 = i1 - 1; i2 > 0; i2--)
    {
      if (i4 < arrayOfi1[i2].d) {
        i4 = arrayOfi1[i2].d;
      }
      if (i5 > arrayOfi1[i2].d) {
        i5 = arrayOfi1[i2].d;
      }
      if (i6 < arrayOfi1[i2].e) {
        i6 = arrayOfi1[i2].e;
      }
      if (i7 > arrayOfi1[i2].e) {
        i7 = arrayOfi1[i2].e;
      }
    }
    paramArrayOfInt2[aP] = (130 - i7);
    paramArrayOfInt2[(aP + 1)] = (i6 - 130 + 1);
    paramArrayOfInt2[(aP + 2)] = (120 - i5 + 1);
    paramArrayOfInt2[(aP + 3)] = (i4 - 120 + 1);
    if (localb.c == paramInt2)
    {
      paramArrayOfInt2[(aP + 4)] = localb.d;
      aP += 5;
      localb.e = true;
      return localb.d;
    }
    paramArrayOfInt2[(aP + 4)] = localb.c;
    aP += 5;
    localb.e = true;
    return localb.c;
  }
  
  private static final void h(j paramj)
  {
    if (paramj.s != 0)
    {
      paramj.o = true;
      return;
    }
    paramj.B = 5;
    paramj.s = cW[aM];
    d locald1 = dH;
    d locald2 = bb;
    locald1.a = paramj.p;
    locald1.b = paramj.q;
    locald1.c = paramj.r;
    locald1.a += paramj.D[0] * 3000;
    locald1.b += paramj.D[1] * 3000;
    locald1.c += paramj.D[2] * 3000;
    int i1 = paramj.t;
    int i2 = -1;
    for (;;)
    {
      if (i1 == 999) {
        return;
      }
      if (a(i1, locald1, locald2, paramj) != -1) {
        return;
      }
      if ((i2 = a(i1, locald1, locald2, i2)) == -1) {
        break;
      }
      if (j[i2].c == i1) {
        i1 = j[i2].d;
      } else {
        i1 = j[i2].c;
      }
    }
    if (a(i1, locald1, locald2) != -1)
    {
      a(locald2.a, locald2.b, locald2.c, (byte)1, (short)i1);
      return;
    }
  }
  
  private static final void i(j paramj)
  {
    if ((paramj.s != 0) || (ap != 0)) {
      return;
    }
    if (eg > 8) {
      ap = 4;
    }
    byte[] arrayOfByte = ai;
    paramj.s = cX[eg];
    if (arrayOfByte[dw] == 0)
    {
      if (aj[dw] != 0)
      {
        if (bX[dw] > aj[dw])
        {
          arrayOfByte[dw] = aj[dw];
          aj[dw] = 0;
        }
        else
        {
          arrayOfByte[dw] = bX[dw];
          byte tmp117_114 = dw;
          byte[] tmp117_111 = aj;
          tmp117_111[tmp117_114] = ((byte)(tmp117_111[tmp117_114] - bX[dw]));
        }
        paramj.s = 10;
        return;
      }
      x();
      return;
    }
    if (arrayOfByte[dw] > 0)
    {
      byte tmp152_149 = dw;
      byte[] tmp152_148 = arrayOfByte;
      tmp152_148[tmp152_149] = ((byte)(tmp152_148[tmp152_149] - 1));
    }
    if (eg == 0) {
      cV = 9;
    }
    int i1;
    if (dw != 3)
    {
      be = true;
      bd = (byte)(bd + 1);
      if (bd > 2) {
        bd = 1;
      }
      cR = g(17);
      aG += cQ[(eg + 1)];
      if (aG > 20) {
        aG = 20;
      }
      cS = -aG >> 1;
      i1 = 0;
      d locald1 = dH;
      d locald2 = bb;
      locald1.a = dg[0];
      locald1.b = dg[1];
      locald1.c = dg[2];
      locald1.a += n[0].D[0] * ee[eg];
      locald1.b += n[0].D[1] * ee[eg];
      locald1.c += n[0].D[2] * ee[eg];
      int i3 = n[0].t;
      int i4 = -1;
      for (;;)
      {
        if ((i3 == 999) || (a(i3, locald1, locald2, paramj) != -1)) {
          return;
        }
        if ((i4 = a(i3, locald1, locald2, i4)) == -1) {
          break;
        }
        if (j[i4].c == i3) {
          i3 = j[i4].d;
        } else {
          i3 = j[i4].c;
        }
      }
      if (a(i3, locald1, locald2) != -1) {
        a(locald2.a, locald2.b, locald2.c, (byte)1, (short)i3);
      }
    }
    else
    {
      if ((dw == 3) && (arrayOfByte[dw] == 0))
      {
        eg = 0;
        dw = 0;
      }
      if (dm >= 19) {
        return;
      }
      dm += 1;
      for (i1 = 19; i1 >= 0; i1--) {
        if (dk[i1][6] == 0)
        {
          int i2;
          if ((i2 = dd - 15) < 0) {
            i2 = 0;
          }
          dk[i1][3] = ((int)(-dn[df] * -dn[i2] >> 16));
          dk[i1][4] = ((int)(-aA[df] * -dn[i2] >> 16));
          dk[i1][5] = (-aA[i2]);
          dk[i1][8] = ' ';
          dk[i1][0] = (paramj.p + dk[i1][3] * 160);
          dk[i1][1] = (paramj.q + dk[i1][4] * 160);
          dk[i1][2] = (paramj.r + dk[i1][5] * 160);
          dk[i1][6] = 50;
          dk[i1][7] = paramj.t;
          dk[i1][9] = dd;
          dk[i1][10] = df;
          dk[i1][11] = dt[3];
          return;
        }
      }
    }
  }
  
  public final void showNotify()
  {
    super.showNotify();
  }
  
  private static final void a(int[] paramArrayOfInt1, int[] paramArrayOfInt2)
  {
    int[] arrayOfInt1 = bz;
    int[] arrayOfInt2 = bp;
    int i1 = paramArrayOfInt1.length >> 4;
    for (int i3 = 0; i3 < i1; i3++)
    {
      int i2 = i3 << 4;
      arrayOfInt2[i3] = (paramArrayOfInt2[(paramArrayOfInt1[i2] + 5)] + paramArrayOfInt2[(paramArrayOfInt1[(i2 + 1)] + 5)] + paramArrayOfInt2[(paramArrayOfInt1[(i2 + 2)] + 5)]);
      arrayOfInt1[i3] = i3;
    }
    b(arrayOfInt2, arrayOfInt1, 0, i1 - 1);
  }
  
  private static final int n(int paramInt)
  {
    int[] arrayOfInt1 = by;
    int[] arrayOfInt2 = bo;
    int i1 = dg[0];
    int i2 = dg[1];
    int i3 = dg[2];
    int i4 = cz;
    int i5 = 0;
    int[][] arrayOfInt3 = dA;
    int[][] arrayOfInt4 = dk;
    int i6 = 0;
    int i7 = 0;
    for (int i8 = dR - 1; i8 > 0; i8--)
    {
      j localj;
      if (((localj = n[i8]).E) && (paramInt == localj.t))
      {
        arrayOfInt1[i5] = i8;
        arrayOfInt2[i5] = (Math.abs(localj.p - i1) + Math.abs(localj.q - i2) + Math.abs(localj.r - i3));
        i5++;
      }
    }
    for (int i9 = 0; i9 < cA; i9++)
    {
      g localg;
      if (((localg = h[i9]).t) && (localg.r == paramInt))
      {
        arrayOfInt1[i5] = (i9 + i4);
        arrayOfInt2[i5] = (Math.abs(localg.m - i1) + Math.abs(localg.n - i2) + Math.abs(localg.o - i3));
        i5++;
      }
    }
    i4 += cA;
    while (i6 < dB) {
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
    i4 += 20;
    i6 = 0;
    i7 = 0;
    while (i6 < dm) {
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
    if ((!paramBoolean) && (paramInt >= bJ)) {
      return;
    }
    if (dx)
    {
      if (m.j == null)
      {
        NET_Lizard.b.ag();
        m.a(NET_Lizard.b);
      }
      if (paramBoolean) {
        paramInt = bJ;
      }
      m.a(paramInt);
    }
  }
  
  public static final void d(int paramInt)
  {
    a(paramInt, false);
  }
  
  private static void ad() {}
  
  public static void k() {}
  
  private static boolean b(String paramString1, String paramString2)
  {
    if (((paramString1 == null) || (paramString2 == null)) && ((paramString1 != null) || (paramString2 != null))) {
      return false;
    }
    if ((paramString1 == null) && (paramString2 == null)) {
      return true;
    }
    if ((paramString1 != null) && (paramString2 != null))
    {
      if (paramString1.length() != paramString2.length()) {
        return false;
      }
      for (int i1 = 0; i1 < paramString1.length(); i1++) {
        if (paramString1.charAt(i1) != paramString2.charAt(i1)) {
          return false;
        }
      }
      return true;
    }
    return false;
  }
  
  private static final boolean ae()
  {
    int i1 = n[0].p;
    int i2 = n[0].q;
    int i3 = n[0].r;
    for (int i7 = dR - 1; i7 > 0; i7--)
    {
      j localj;
      if ((!(localj = n[i7]).k) && (localj.C > 3))
      {
        int i4 = localj.p - i1 >> 16;
        int i5 = localj.q - i2 >> 16;
        int i6 = localj.r - i3 >> 16;
        if (i4 * i4 + i5 * i5 + i6 * i6 < 40000)
        {
          localj.B = 0;
          localj.i = 0;
          localj.x = (!localj.x);
          d(5);
          bn = 0;
          return true;
        }
      }
    }
    return false;
  }
  
  private static void c(j paramj, int paramInt1, int paramInt2, int paramInt3, int paramInt4)
  {
    int[] arrayOfInt1 = aA;
    int[] arrayOfInt2 = dn;
    int i1 = paramInt1 - paramj.p >> 16;
    int i2 = paramInt2 - paramj.q >> 16;
    int i3 = paramInt3 - paramj.r >> 16;
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
    paramj.D[0] = (i1 * 65536 / i5);
    paramj.D[1] = (i2 * 65536 / i5);
    paramj.D[2] = (i3 * 65536 / i5);
    if (paramInt4 -= g(paramInt4 << 1) < 0) {
      paramInt4 += 360;
    }
    paramj.D[0] = ((int)(paramj.D[0] * arrayOfInt1[paramInt4] - paramj.D[1] * arrayOfInt2[paramInt4] >> 16));
    paramj.D[1] = ((int)(paramj.D[0] * arrayOfInt2[paramInt4] + paramj.D[1] * arrayOfInt1[paramInt4] >> 16));
  }
  
  private static final int a(d paramd1, d paramd2, d paramd3, int paramInt1, int paramInt2, int paramInt3, int paramInt4, int paramInt5, int paramInt6)
  {
    int[] arrayOfInt = aO;
    int i6 = -1;
    long l3 = Math.abs(paramd1.a - paramd2.a) + Math.abs(paramd1.b - paramd2.b) + Math.abs(paramd1.c - paramd2.c);
    int i1 = paramInt1 - paramd2.a >> 16;
    int i2;
    long l1;
    long l2;
    int i3;
    int i4;
    int i5;
    if ((((i2 = paramInt1 - paramd3.a >> 16) >= 0) && (i1 <= 0)) || ((i1 >= 0) && (i2 <= 0)))
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
      i3 = (int)(paramd2.a * l1 + paramd3.a * l2 >> 18);
      i4 = (int)(paramd2.b * l1 + paramd3.b * l2 >> 18);
      i5 = (int)(paramd2.c * l1 + paramd3.c * l2 >> 18);
      if ((paramInt5 <= i4) && (paramInt6 <= i5) && (paramInt2 >= i4) && (paramInt3 >= i5))
      {
        paramd3.a = (i3 + 65536);
        paramd3.b = i4;
        paramd3.c = i5;
        i6 = 1;
      }
    }
    i1 = paramInt2 - paramd2.b >> 16;
    if ((((i2 = paramInt2 - paramd3.b >> 16) >= 0) && (i1 <= 0)) || ((i1 >= 0) && (i2 <= 0)))
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
      i3 = (int)(paramd2.a * l1 + paramd3.a * l2 >> 18);
      i4 = (int)(paramd2.b * l1 + paramd3.b * l2 >> 18);
      i5 = (int)(paramd2.c * l1 + paramd3.c * l2 >> 18);
      if ((paramInt4 <= i3) && (paramInt6 <= i5) && (paramInt1 >= i3) && (paramInt3 >= i5))
      {
        paramd3.a = i3;
        paramd3.b = (i4 + 65536);
        paramd3.c = i5;
        i6 = 2;
      }
    }
    i1 = paramInt3 - paramd2.c >> 16;
    if ((((i2 = paramInt3 - paramd3.c >> 16) >= 0) && (i1 <= 0)) || ((i1 >= 0) && (i2 <= 0)))
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
      i3 = (int)(paramd2.a * l1 + paramd3.a * l2 >> 18);
      i4 = (int)(paramd2.b * l1 + paramd3.b * l2 >> 18);
      i5 = (int)(paramd2.c * l1 + paramd3.c * l2 >> 18);
      if ((paramInt4 <= i3) && (paramInt5 <= i4) && (paramInt1 >= i3) && (paramInt2 >= i4))
      {
        paramd3.a = i3;
        paramd3.b = i4;
        paramd3.c = (i5 + 65536);
        i6 = 3;
      }
    }
    i1 = paramd2.a - paramInt4 >> 16;
    if ((((i2 = paramd3.a - paramInt4 >> 16) >= 0) && (i1 <= 0)) || ((i1 >= 0) && (i2 <= 0)))
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
      i3 = (int)(paramd2.a * l1 + paramd3.a * l2 >> 18);
      i4 = (int)(paramd2.b * l1 + paramd3.b * l2 >> 18);
      i5 = (int)(paramd2.c * l1 + paramd3.c * l2 >> 18);
      if ((paramInt5 <= i4) && (paramInt6 <= i5) && (paramInt2 >= i4) && (paramInt3 >= i5))
      {
        paramd3.a = i3;
        paramd3.b = i4;
        paramd3.c = i5;
        i6 = 1;
      }
    }
    i1 = paramd2.b - paramInt5 >> 16;
    if ((((i2 = paramd3.b - paramInt5 >> 16) >= 0) && (i1 <= 0)) || ((i1 >= 0) && (i2 <= 0)))
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
      i3 = (int)(paramd2.a * l1 + paramd3.a * l2 >> 18);
      i4 = (int)(paramd2.b * l1 + paramd3.b * l2 >> 18);
      i5 = (int)(paramd2.c * l1 + paramd3.c * l2 >> 18);
      if ((paramInt4 <= i3) && (paramInt6 <= i5) && (paramInt1 >= i3) && (paramInt3 >= i5))
      {
        paramd3.a = i3;
        paramd3.b = i4;
        paramd3.c = i5;
        i6 = 2;
      }
    }
    i1 = paramd2.c - paramInt6 >> 16;
    if ((((i2 = paramd3.c - paramInt6 >> 16) >= 0) && (i1 <= 0)) || ((i1 >= 0) && (i2 <= 0)))
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
      i3 = (int)(paramd2.a * l1 + paramd3.a * l2 >> 18);
      i4 = (int)(paramd2.b * l1 + paramd3.b * l2 >> 18);
      i5 = (int)(paramd2.c * l1 + paramd3.c * l2 >> 18);
      if ((paramInt4 <= i3) && (paramInt5 <= i4) && (paramInt1 >= i3) && (paramInt2 >= i4))
      {
        paramd3.a = i3;
        paramd3.b = i4;
        paramd3.c = i5;
        i6 = 3;
      }
    }
    if (Math.abs(paramd3.a - paramd2.a) + Math.abs(paramd3.b - paramd2.b) + Math.abs(paramd3.c - paramd2.c) < l3)
    {
      paramd1.a = paramd3.a;
      paramd1.b = paramd3.b;
      paramd1.c = paramd3.c;
      Math.abs(paramd1.a - paramd2.a);
      Math.abs(paramd1.b - paramd2.b);
      Math.abs(paramd1.c - paramd2.c);
    }
    return i6;
  }
  
  private static boolean j(j paramj)
  {
    j localj = n[0];
    int i1 = paramj.p - localj.p >> 16;
    int i2 = paramj.q - localj.q >> 16;
    int i3 = paramj.r - localj.r >> 16;
    return 19600L > i1 * i1 + i2 * i2 + i3 * i3;
  }
  
  private final String[] c(String paramString)
  {
    String[][] arrayOfString;
    int i1;
    String[] arrayOfString1 = new String[i1 = (arrayOfString = e.l.b(paramString))[this.cg].length];
    for (int i2 = 0; i2 < i1; i2++) {
      arrayOfString1[i2] = arrayOfString[this.cg][i2];
    }
    return arrayOfString1;
  }
  
  private final String[] d(String paramString)
  {
    return e.a(e.l.c(paramString) + (this.cg == 18 ? this.m : ""), this.bi, 205, true);
  }
  
  private static final int a(int paramInt1, int paramInt2)
  {
    if (paramInt1 < 0) {
      paramInt1 += 256;
    }
    if (paramInt2 < 0) {
      paramInt2 += 256;
    }
    return paramInt1 + paramInt2 * 256;
  }
  
  private static int af()
  {
    try
    {
      Class.forName(e.a(X));
      return 1;
    }
    catch (Exception localException) {}
    return 0;
  }
  
  private static final void c(byte paramByte)
  {
    dQ = true;
    if (b == 0)
    {
      db -= 2;
      if (db < -5 << paramByte) {
        db = -5 << paramByte;
      }
    }
    else
    {
      db -= 2;
      if (db < -4) {
        db = -4;
      }
    }
    cR += 2;
  }
  
  private static final void d(byte paramByte)
  {
    dQ = true;
    if (b == 0)
    {
      db += 2;
      if (db > 5 << paramByte) {
        db = 5 << paramByte;
      }
      return;
    }
    db += 2;
    if (db > 4) {
      db = 4;
    }
  }
  
  private static final void b(int[] paramArrayOfInt)
  {
    int[] arrayOfInt1 = dn;
    int[] arrayOfInt2 = aA;
    paramArrayOfInt[0] = ((int)(-arrayOfInt1[df] * -arrayOfInt1[dd] >> 16));
    paramArrayOfInt[1] = ((int)(-arrayOfInt2[df] * -arrayOfInt1[dd] >> 16));
    paramArrayOfInt[2] = (-aA[dd]);
    int i1;
    if ((i1 = aG >> 1) != 0)
    {
      if (i1 -= g(i1 << 1) < 0) {
        i1 += 360;
      }
      paramArrayOfInt[0] = ((int)(paramArrayOfInt[0] * arrayOfInt2[i1] - paramArrayOfInt[1] * arrayOfInt1[i1] >> 16));
      paramArrayOfInt[1] = ((int)(paramArrayOfInt[0] * arrayOfInt1[i1] + paramArrayOfInt[1] * arrayOfInt2[i1] >> 16));
    }
  }
  
  private static final void a(i parami1, i parami2, i parami3, int paramInt1, int paramInt2, int paramInt3)
  {
    byte[] arrayOfByte = dL[bx];
    int[] arrayOfInt1 = cG[bx];
    int[] arrayOfInt2 = aO;
    int[] arrayOfInt3 = az;
    int[] arrayOfInt4 = aN;
    for (int i2 = parami1.e; i2 < parami2.e; i2++)
    {
      int i5 = (i2 - parami1.e) * arrayOfInt3[(parami3.e - parami1.e)];
      int i6 = parami1.d + (int)((parami3.d - parami1.d) * i5 >> 16);
      int i7 = parami1.g + (int)((parami3.g - parami1.g) * i5 >> 16);
      int i8 = parami1.i + (int)((parami3.i - parami1.i) * i5 >> 16);
      int i9 = parami1.m + (int)((parami3.m - parami1.m) * i5 >> 16);
      i5 = (i2 - parami1.e) * arrayOfInt3[(parami2.e - parami1.e)];
      int i10 = parami1.m + (int)((parami2.m - parami1.m) * i5 >> 16);
      int i1 = i2 * 240 + i6;
      int i3 = parami1.d + (int)((parami2.d - parami1.d) * i5 >> 16) - i6;
      int i11 = i7 * arrayOfInt2[i9];
      int i14;
      int i15;
      int i16;
      for (int i12 = i8 * arrayOfInt2[i9]; i3 >= 16; i12 = i14)
      {
        i7 += paramInt1;
        i8 += paramInt2;
        i9 += paramInt3;
        int i13 = i7 * arrayOfInt2[i9];
        i14 = i8 * arrayOfInt2[i9];
        i15 = i13 - i11 >> 4;
        i16 = i14 - i12 >> 4;
        int i4 = 16;
        while (i4-- > 0)
        {
          arrayOfInt4[(i1++)] = arrayOfInt1[arrayOfByte[((i12 >> 18 << 6) + (i11 >> 18) & 0xFFF)]];
          i11 += i15;
          i12 += i16;
        }
        i3 -= 16;
        i11 = i13;
      }
      if (i3 > 0)
      {
        i15 = (int)(((parami1.g + (int)((parami2.g - parami1.g) * i5 >> 16)) * arrayOfInt2[i10] - i11) * arrayOfInt3[i3] >> 16);
        i16 = (int)(((parami1.i + (int)((parami2.i - parami1.i) * i5 >> 16)) * arrayOfInt2[i10] - i12) * arrayOfInt3[i3] >> 16);
        while (i3-- > 0)
        {
          arrayOfInt4[(i1++)] = arrayOfInt1[arrayOfByte[((i12 >> 18 << 6) + (i11 >> 18) & 0xFFF)]];
          i11 += i15;
          i12 += i16;
        }
      }
    }
  }
  
  private static final void b(i parami1, i parami2, i parami3, int paramInt1, int paramInt2, int paramInt3)
  {
    byte[] arrayOfByte = dL[bx];
    int[] arrayOfInt1 = cG[bx];
    int[] arrayOfInt2 = aO;
    int[] arrayOfInt3 = az;
    int[] arrayOfInt4 = aN;
    int i20 = paramInt3 >> 4;
    for (int i2 = parami1.e; i2 < parami2.e; i2++)
    {
      int i5 = (i2 - parami1.e) * arrayOfInt3[(parami3.e - parami1.e)];
      int i6 = parami1.d + (int)((parami3.d - parami1.d) * i5 >> 16);
      int i7 = parami1.g + (int)((parami3.g - parami1.g) * i5 >> 16);
      int i8 = parami1.i + (int)((parami3.i - parami1.i) * i5 >> 16);
      int i9 = parami1.m + (int)((parami3.m - parami1.m) * i5 >> 16);
      i5 = (i2 - parami1.e) * arrayOfInt3[(parami2.e - parami1.e)];
      int i10 = parami1.m + (int)((parami2.m - parami1.m) * i5 >> 16);
      int i1 = i2 * 240 + i6;
      int i3 = parami1.d + (int)((parami2.d - parami1.d) * i5 >> 16) - i6;
      int i11 = i7 * arrayOfInt2[i9];
      int i14;
      int i15;
      int i16;
      int i19;
      int i18;
      for (int i12 = i8 * arrayOfInt2[i9]; i3 >= 16; i12 = i14)
      {
        i7 += paramInt1;
        i8 += paramInt2;
        i9 += paramInt3;
        int i13 = i7 * arrayOfInt2[i9];
        i14 = i8 * arrayOfInt2[i9];
        i15 = i13 - i11 >> 4;
        i16 = i14 - i12 >> 4;
        int i4 = 16;
        i17 = i9;
        while (i4-- > 0)
        {
          i19 = arrayOfInt1[arrayOfByte[((i12 >> 18 << 6) + (i11 >> 18) & 0xFFF)]];
          if ((i18 = i17 << 7 >> 8) < 128)
          {
            if (i18 < 30) {
              i18 = 30;
            }
            i19 = (i19 = (i19 = i19 & 0xFFFF | (i19 & 0xFF0000) * i18 >> 7 & 0xFF0000) & 0xFF00FF | (i19 & 0xFF00) * i18 >> 7 & 0xFF00) & 0xFFFF00 | (i19 & 0xFF) * i18 >> 7 & 0xFF;
          }
          arrayOfInt4[i1] = i19;
          i1++;
          i17 += i20;
          i11 += i15;
          i12 += i16;
        }
        i3 -= 16;
        i11 = i13;
      }
      int i17 = i10;
      if (i3 > 0)
      {
        i15 = (int)(((parami1.g + (int)((parami2.g - parami1.g) * i5 >> 16)) * arrayOfInt2[i10] - i11) * arrayOfInt3[i3] >> 16);
        i16 = (int)(((parami1.i + (int)((parami2.i - parami1.i) * i5 >> 16)) * arrayOfInt2[i10] - i12) * arrayOfInt3[i3] >> 16);
        while (i3-- > 0)
        {
          i19 = arrayOfInt1[arrayOfByte[((i12 >> 18 << 6) + (i11 >> 18) & 0xFFF)]];
          if ((i18 = i17 << 7 >> 8) < 128)
          {
            if (i18 < 30) {
              i18 = 30;
            }
            i19 = (i19 = (i19 = i19 & 0xFFFF | (i19 & 0xFF0000) * i18 >> 7 & 0xFF0000) & 0xFF00FF | (i19 & 0xFF00) * i18 >> 7 & 0xFF00) & 0xFFFF00 | (i19 & 0xFF) * i18 >> 7 & 0xFF;
          }
          arrayOfInt4[i1] = i19;
          i1++;
          i17 += i20;
          i11 += i15;
          i12 += i16;
        }
      }
    }
  }
  
  private static final void c(i parami1, i parami2, i parami3, int paramInt1, int paramInt2, int paramInt3)
  {
    byte[] arrayOfByte = dL[bx];
    int[] arrayOfInt1 = cG[bx];
    int[] arrayOfInt2 = aO;
    int[] arrayOfInt3 = az;
    int[] arrayOfInt4 = aN;
    for (int i2 = parami1.e; i2 < parami2.e; i2++)
    {
      int i5 = (i2 - parami1.e) * arrayOfInt3[(parami2.e - parami1.e)];
      int i6 = parami1.d + (int)((parami2.d - parami1.d) * i5 >> 16);
      int i7 = parami1.g + (int)((parami2.g - parami1.g) * i5 >> 16);
      int i8 = parami1.i + (int)((parami2.i - parami1.i) * i5 >> 16);
      int i10 = parami1.m + (int)((parami2.m - parami1.m) * i5 >> 16);
      i5 = (i2 - parami1.e) * arrayOfInt3[(parami3.e - parami1.e)];
      int i9 = parami1.m + (int)((parami3.m - parami1.m) * i5 >> 16);
      int i1 = i2 * 240 + i6;
      int i3 = parami1.d + (int)((parami3.d - parami1.d) * i5 >> 16) - i6;
      int i11 = i7 * arrayOfInt2[i10];
      int i14;
      int i15;
      int i16;
      for (int i12 = i8 * arrayOfInt2[i10]; i3 >= 16; i12 = i14)
      {
        i7 += paramInt1;
        i8 += paramInt2;
        i10 += paramInt3;
        int i13 = i7 * arrayOfInt2[i10];
        i14 = i8 * arrayOfInt2[i10];
        i15 = i13 - i11 >> 4;
        i16 = i14 - i12 >> 4;
        int i4 = 16;
        while (i4-- > 0)
        {
          arrayOfInt4[(i1++)] = arrayOfInt1[arrayOfByte[((i12 >> 18 << 6) + (i11 >> 18) & 0xFFF)]];
          i11 += i15;
          i12 += i16;
        }
        i3 -= 16;
        i11 = i13;
      }
      if (i3 > 0)
      {
        i15 = (int)(((parami1.g + (int)((parami3.g - parami1.g) * i5 >> 16)) * arrayOfInt2[i9] - i11) * arrayOfInt3[i3] >> 16);
        i16 = (int)(((parami1.i + (int)((parami3.i - parami1.i) * i5 >> 16)) * arrayOfInt2[i9] - i12) * arrayOfInt3[i3] >> 16);
        while (i3-- > 0)
        {
          arrayOfInt4[(i1++)] = arrayOfInt1[arrayOfByte[((i12 >> 18 << 6) + (i11 >> 18) & 0xFFF)]];
          i11 += i15;
          i12 += i16;
        }
      }
    }
  }
  
  private static final void d(i parami1, i parami2, i parami3, int paramInt1, int paramInt2, int paramInt3)
  {
    byte[] arrayOfByte = dL[bx];
    int[] arrayOfInt1 = cG[bx];
    int[] arrayOfInt2 = aO;
    int[] arrayOfInt3 = az;
    int[] arrayOfInt4 = aN;
    int i20 = paramInt3 >> 4;
    for (int i2 = parami1.e; i2 < parami2.e; i2++)
    {
      int i5 = (i2 - parami1.e) * arrayOfInt3[(parami2.e - parami1.e)];
      int i6 = parami1.d + (int)((parami2.d - parami1.d) * i5 >> 16);
      int i7 = parami1.g + (int)((parami2.g - parami1.g) * i5 >> 16);
      int i8 = parami1.i + (int)((parami2.i - parami1.i) * i5 >> 16);
      int i10 = parami1.m + (int)((parami2.m - parami1.m) * i5 >> 16);
      i5 = (i2 - parami1.e) * arrayOfInt3[(parami3.e - parami1.e)];
      int i9 = parami1.m + (int)((parami3.m - parami1.m) * i5 >> 16);
      int i1 = i2 * 240 + i6;
      int i3 = parami1.d + (int)((parami3.d - parami1.d) * i5 >> 16) - i6;
      int i11 = i7 * arrayOfInt2[i10];
      int i14;
      int i15;
      int i16;
      int i19;
      int i18;
      for (int i12 = i8 * arrayOfInt2[i10]; i3 >= 16; i12 = i14)
      {
        i7 += paramInt1;
        i8 += paramInt2;
        i10 += paramInt3;
        int i13 = i7 * arrayOfInt2[i10];
        i14 = i8 * arrayOfInt2[i10];
        i15 = i13 - i11 >> 4;
        i16 = i14 - i12 >> 4;
        int i4 = 16;
        i17 = i10;
        while (i4-- > 0)
        {
          i19 = arrayOfInt1[arrayOfByte[((i12 >> 18 << 6) + (i11 >> 18) & 0xFFF)]];
          if ((i18 = i17 << 7 >> 8) < 128)
          {
            if (i18 < 30) {
              i18 = 30;
            }
            i19 = (i19 = (i19 = i19 & 0xFFFF | (i19 & 0xFF0000) * i18 >> 7 & 0xFF0000) & 0xFF00FF | (i19 & 0xFF00) * i18 >> 7 & 0xFF00) & 0xFFFF00 | (i19 & 0xFF) * i18 >> 7 & 0xFF;
          }
          arrayOfInt4[i1] = i19;
          i1++;
          i17 += i20;
          i11 += i15;
          i12 += i16;
        }
        i3 -= 16;
        i11 = i13;
      }
      int i17 = i9;
      if (i3 > 0)
      {
        i15 = (int)(((parami1.g + (int)((parami3.g - parami1.g) * i5 >> 16)) * arrayOfInt2[i9] - i11) * arrayOfInt3[i3] >> 16);
        i16 = (int)(((parami1.i + (int)((parami3.i - parami1.i) * i5 >> 16)) * arrayOfInt2[i9] - i12) * arrayOfInt3[i3] >> 16);
        while (i3-- > 0)
        {
          i19 = arrayOfInt1[arrayOfByte[((i12 >> 18 << 6) + (i11 >> 18) & 0xFFF)]];
          if ((i18 = i17 << 7 >> 8) < 128)
          {
            if (i18 < 30) {
              i18 = 30;
            }
            i19 = (i19 = (i19 = i19 & 0xFFFF | (i19 & 0xFF0000) * i18 >> 7 & 0xFF0000) & 0xFF00FF | (i19 & 0xFF00) * i18 >> 7 & 0xFF00) & 0xFFFF00 | (i19 & 0xFF) * i18 >> 7 & 0xFF;
          }
          arrayOfInt4[i1] = i19;
          i1++;
          i17 += i20;
          i11 += i15;
          i12 += i16;
        }
      }
    }
  }
  
  private static final void e(i parami1, i parami2, i parami3, int paramInt1, int paramInt2, int paramInt3)
  {
    byte[] arrayOfByte = dL[bx];
    int[] arrayOfInt1 = cG[bx];
    int[] arrayOfInt2 = aO;
    int[] arrayOfInt3 = az;
    int[] arrayOfInt4 = aN;
    for (int i2 = parami2.e; i2 < parami3.e; i2++)
    {
      int i5 = (i2 - parami1.e) * arrayOfInt3[(parami3.e - parami1.e)];
      int i6 = parami1.d + (int)((parami3.d - parami1.d) * i5 >> 16);
      int i7 = parami1.g + (int)((parami3.g - parami1.g) * i5 >> 16);
      int i8 = parami1.i + (int)((parami3.i - parami1.i) * i5 >> 16);
      int i9 = parami1.m + (int)((parami3.m - parami1.m) * i5 >> 16);
      i5 = (i2 - parami2.e) * arrayOfInt3[(parami3.e - parami2.e)];
      int i10 = parami2.m + (int)((parami3.m - parami2.m) * i5 >> 16);
      int i1 = i2 * 240 + i6;
      int i3 = parami2.d + (int)((parami3.d - parami2.d) * i5 >> 16) - i6;
      int i11 = i7 * arrayOfInt2[i9];
      int i14;
      int i15;
      int i16;
      for (int i12 = i8 * arrayOfInt2[i9]; i3 >= 16; i12 = i14)
      {
        i7 += paramInt1;
        i8 += paramInt2;
        i9 += paramInt3;
        int i13 = i7 * arrayOfInt2[i9];
        i14 = i8 * arrayOfInt2[i9];
        i15 = i13 - i11 >> 4;
        i16 = i14 - i12 >> 4;
        int i4 = 16;
        while (i4-- > 0)
        {
          arrayOfInt4[(i1++)] = arrayOfInt1[arrayOfByte[((i12 >> 18 << 6) + (i11 >> 18) & 0xFFF)]];
          i11 += i15;
          i12 += i16;
        }
        i3 -= 16;
        i11 = i13;
      }
      if (i3 > 0)
      {
        i15 = (int)(((parami2.g + (int)((parami3.g - parami2.g) * i5 >> 16)) * arrayOfInt2[i10] - i11) * arrayOfInt3[i3] >> 16);
        i16 = (int)(((parami2.i + (int)((parami3.i - parami2.i) * i5 >> 16)) * arrayOfInt2[i10] - i12) * arrayOfInt3[i3] >> 16);
        while (i3-- > 0)
        {
          arrayOfInt4[(i1++)] = arrayOfInt1[arrayOfByte[((i12 >> 18 << 6) + (i11 >> 18) & 0xFFF)]];
          i11 += i15;
          i12 += i16;
        }
      }
    }
  }
  
  private static final void f(i parami1, i parami2, i parami3, int paramInt1, int paramInt2, int paramInt3)
  {
    byte[] arrayOfByte = dL[bx];
    int[] arrayOfInt1 = cG[bx];
    int[] arrayOfInt2 = aO;
    int[] arrayOfInt3 = az;
    int[] arrayOfInt4 = aN;
    int i20 = paramInt3 >> 4;
    for (int i2 = parami2.e; i2 < parami3.e; i2++)
    {
      int i5 = (i2 - parami1.e) * arrayOfInt3[(parami3.e - parami1.e)];
      int i6 = parami1.d + (int)((parami3.d - parami1.d) * i5 >> 16);
      int i7 = parami1.g + (int)((parami3.g - parami1.g) * i5 >> 16);
      int i8 = parami1.i + (int)((parami3.i - parami1.i) * i5 >> 16);
      int i9 = parami1.m + (int)((parami3.m - parami1.m) * i5 >> 16);
      i5 = (i2 - parami2.e) * arrayOfInt3[(parami3.e - parami2.e)];
      int i10 = parami2.m + (int)((parami3.m - parami2.m) * i5 >> 16);
      int i1 = i2 * 240 + i6;
      int i3 = parami2.d + (int)((parami3.d - parami2.d) * i5 >> 16) - i6;
      int i11 = i7 * arrayOfInt2[i9];
      int i14;
      int i15;
      int i16;
      int i19;
      int i18;
      for (int i12 = i8 * arrayOfInt2[i9]; i3 >= 16; i12 = i14)
      {
        i7 += paramInt1;
        i8 += paramInt2;
        i9 += paramInt3;
        int i13 = i7 * arrayOfInt2[i9];
        i14 = i8 * arrayOfInt2[i9];
        i15 = i13 - i11 >> 4;
        i16 = i14 - i12 >> 4;
        int i4 = 16;
        i17 = i9;
        while (i4-- > 0)
        {
          i19 = arrayOfInt1[arrayOfByte[((i12 >> 18 << 6) + (i11 >> 18) & 0xFFF)]];
          if ((i18 = i17 << 7 >> 8) < 128)
          {
            if (i18 < 30) {
              i18 = 30;
            }
            i19 = (i19 = (i19 = i19 & 0xFFFF | (i19 & 0xFF0000) * i18 >> 7 & 0xFF0000) & 0xFF00FF | (i19 & 0xFF00) * i18 >> 7 & 0xFF00) & 0xFFFF00 | (i19 & 0xFF) * i18 >> 7 & 0xFF;
          }
          arrayOfInt4[i1] = i19;
          i1++;
          i17 += i20;
          i11 += i15;
          i12 += i16;
        }
        i3 -= 16;
        i11 = i13;
      }
      int i17 = i10;
      if (i3 > 0)
      {
        i15 = (int)(((parami2.g + (int)((parami3.g - parami2.g) * i5 >> 16)) * arrayOfInt2[i10] - i11) * arrayOfInt3[i3] >> 16);
        i16 = (int)(((parami2.i + (int)((parami3.i - parami2.i) * i5 >> 16)) * arrayOfInt2[i10] - i12) * arrayOfInt3[i3] >> 16);
        while (i3-- > 0)
        {
          i19 = arrayOfInt1[arrayOfByte[((i12 >> 18 << 6) + (i11 >> 18) & 0xFFF)]];
          if ((i18 = i17 << 7 >> 8) < 128)
          {
            if (i18 < 30) {
              i18 = 30;
            }
            i19 = (i19 = (i19 = i19 & 0xFFFF | (i19 & 0xFF0000) * i18 >> 7 & 0xFF0000) & 0xFF00FF | (i19 & 0xFF00) * i18 >> 7 & 0xFF00) & 0xFFFF00 | (i19 & 0xFF) * i18 >> 7 & 0xFF;
          }
          arrayOfInt4[i1] = i19;
          i1++;
          i17 += i20;
          i11 += i15;
          i12 += i16;
        }
      }
    }
  }
  
  private static final void g(i parami1, i parami2, i parami3, int paramInt1, int paramInt2, int paramInt3)
  {
    byte[] arrayOfByte = dL[bx];
    int[] arrayOfInt1 = cG[bx];
    int[] arrayOfInt2 = aO;
    int[] arrayOfInt3 = az;
    int[] arrayOfInt4 = aN;
    for (int i2 = parami2.e; i2 < parami3.e; i2++)
    {
      int i5 = (i2 - parami2.e) * arrayOfInt3[(parami3.e - parami2.e)];
      int i6 = parami2.d + (int)((parami3.d - parami2.d) * i5 >> 16);
      int i7 = parami2.g + (int)((parami3.g - parami2.g) * i5 >> 16);
      int i8 = parami2.i + (int)((parami3.i - parami2.i) * i5 >> 16);
      int i10 = parami2.m + (int)((parami3.m - parami2.m) * i5 >> 16);
      i5 = (i2 - parami1.e) * arrayOfInt3[(parami3.e - parami1.e)];
      int i9 = parami1.m + (int)((parami3.m - parami1.m) * i5 >> 16);
      int i1 = i2 * 240 + i6;
      int i3 = parami1.d + (int)((parami3.d - parami1.d) * i5 >> 16) - i6;
      int i11 = i7 * arrayOfInt2[i10];
      int i14;
      int i15;
      int i16;
      for (int i12 = i8 * arrayOfInt2[i10]; i3 >= 16; i12 = i14)
      {
        i7 += paramInt1;
        i8 += paramInt2;
        i10 += paramInt3;
        int i13 = i7 * arrayOfInt2[i10];
        i14 = i8 * arrayOfInt2[i10];
        i15 = i13 - i11 >> 4;
        i16 = i14 - i12 >> 4;
        int i4 = 16;
        while (i4-- > 0)
        {
          arrayOfInt4[(i1++)] = arrayOfInt1[arrayOfByte[((i12 >> 18 << 6) + (i11 >> 18) & 0xFFF)]];
          i11 += i15;
          i12 += i16;
        }
        i3 -= 16;
        i11 = i13;
      }
      if (i3 > 0)
      {
        i15 = (int)(((parami1.g + (int)((parami3.g - parami1.g) * i5 >> 16)) * arrayOfInt2[i9] - i11) * arrayOfInt3[i3] >> 16);
        i16 = (int)(((parami1.i + (int)((parami3.i - parami1.i) * i5 >> 16)) * arrayOfInt2[i9] - i12) * arrayOfInt3[i3] >> 16);
        while (i3-- > 0)
        {
          arrayOfInt4[(i1++)] = arrayOfInt1[arrayOfByte[((i12 >> 18 << 6) + (i11 >> 18) & 0xFFF)]];
          i11 += i15;
          i12 += i16;
        }
      }
    }
  }
  
  private static final void h(i parami1, i parami2, i parami3, int paramInt1, int paramInt2, int paramInt3)
  {
    byte[] arrayOfByte = dL[bx];
    int[] arrayOfInt1 = cG[bx];
    int[] arrayOfInt2 = aO;
    int[] arrayOfInt3 = az;
    int[] arrayOfInt4 = aN;
    int i20 = paramInt3 >> 4;
    for (int i2 = parami2.e; i2 < parami3.e; i2++)
    {
      int i5 = (i2 - parami2.e) * arrayOfInt3[(parami3.e - parami2.e)];
      int i6 = parami2.d + (int)((parami3.d - parami2.d) * i5 >> 16);
      int i7 = parami2.g + (int)((parami3.g - parami2.g) * i5 >> 16);
      int i8 = parami2.i + (int)((parami3.i - parami2.i) * i5 >> 16);
      int i10 = parami2.m + (int)((parami3.m - parami2.m) * i5 >> 16);
      i5 = (i2 - parami1.e) * arrayOfInt3[(parami3.e - parami1.e)];
      int i9 = parami1.m + (int)((parami3.m - parami1.m) * i5 >> 16);
      int i1 = i2 * 240 + i6;
      int i3 = parami1.d + (int)((parami3.d - parami1.d) * i5 >> 16) - i6;
      int i11 = i7 * arrayOfInt2[i10];
      int i14;
      int i15;
      int i16;
      int i19;
      int i18;
      for (int i12 = i8 * arrayOfInt2[i10]; i3 >= 16; i12 = i14)
      {
        i7 += paramInt1;
        i8 += paramInt2;
        i10 += paramInt3;
        int i13 = i7 * arrayOfInt2[i10];
        i14 = i8 * arrayOfInt2[i10];
        i15 = i13 - i11 >> 4;
        i16 = i14 - i12 >> 4;
        int i4 = 16;
        i17 = i10;
        while (i4-- > 0)
        {
          i19 = arrayOfInt1[arrayOfByte[((i12 >> 18 << 6) + (i11 >> 18) & 0xFFF)]];
          if ((i18 = i17 << 7 >> 8) < 128)
          {
            if (i18 < 30) {
              i18 = 30;
            }
            i19 = (i19 = (i19 = i19 & 0xFFFF | (i19 & 0xFF0000) * i18 >> 7 & 0xFF0000) & 0xFF00FF | (i19 & 0xFF00) * i18 >> 7 & 0xFF00) & 0xFFFF00 | (i19 & 0xFF) * i18 >> 7 & 0xFF;
          }
          arrayOfInt4[i1] = i19;
          i1++;
          i17 += i20;
          i11 += i15;
          i12 += i16;
        }
        i3 -= 16;
        i11 = i13;
      }
      int i17 = i9;
      if (i3 > 0)
      {
        i15 = (int)(((parami1.g + (int)((parami3.g - parami1.g) * i5 >> 16)) * arrayOfInt2[i9] - i11) * arrayOfInt3[i3] >> 16);
        i16 = (int)(((parami1.i + (int)((parami3.i - parami1.i) * i5 >> 16)) * arrayOfInt2[i9] - i12) * arrayOfInt3[i3] >> 16);
        while (i3-- > 0)
        {
          i19 = arrayOfInt1[arrayOfByte[((i12 >> 18 << 6) + (i11 >> 18) & 0xFFF)]];
          if ((i18 = i17 << 7 >> 8) < 128)
          {
            if (i18 < 30) {
              i18 = 30;
            }
            i19 = (i19 = (i19 = i19 & 0xFFFF | (i19 & 0xFF0000) * i18 >> 7 & 0xFF0000) & 0xFF00FF | (i19 & 0xFF00) * i18 >> 7 & 0xFF00) & 0xFFFF00 | (i19 & 0xFF) * i18 >> 7 & 0xFF;
          }
          arrayOfInt4[i1] = i19;
          i1++;
          i17 += i20;
          i11 += i15;
          i12 += i16;
        }
      }
    }
  }
  
  static final void l()
  {
    if (dT) {
      try
      {
        m.c();
        return;
      }
      catch (Exception localException) {}
    }
  }
  
  private final void h(Graphics paramGraphics)
  {
    try
    {
      int i1 = this.bi.b() + this.aS;
      int i2 = 0;
      int i3 = this.aW + 1;
      int i4 = 0;
      int i5 = this.aL / (this.bi.b() + this.aS);
      int i6;
      if ((i6 = this.bT.length - this.aR) > i5) {
        i6 = i5;
      }
      int i7;
      if ((i7 = i1 * i6) < this.bu) {
        i7 = this.bu;
      }
      this.bu = i7;
      int i8 = i7 + 7;
      i2 = 320 - i1 - 1 - i7 >> 1;
      if (i3 - 4 < 0) {
        i3 = 4;
      }
      if (i3 + this.aV > 240) {
        i3 = 240 - this.aV;
      }
      if (i2 - 4 < 0) {
        i2 = 4;
      }
      if (i2 + i7 > 320) {
        i2 = 320 - i7;
      }
      int i9 = i2 - 4;
      paramGraphics.setColor(38, 43, 23);
      paramGraphics.fillRect(0, i9, 240, i8);
      paramGraphics.setColor(0);
      paramGraphics.drawRect(0, i9, 239, i8 - 1);
      if (!this.aF)
      {
        i10 = this.bi.b();
        paramGraphics.setColor(115, 0, 0);
        paramGraphics.fillRect(0, i9 - i10, 240, i10);
        paramGraphics.fillRect(0, i9 + i8, 240, i10);
        paramGraphics.setColor(255, 255, 255);
        i11 = i10 / 3;
        i12 = i10 - 2 * i11;
        int i13 = -1;
        int i14 = 2;
        int i15 = 240 - i12 - 2 * i11;
        int i16 = 1;
        int i17 = i9 - i10 + i11;
        for (int i18 = 0; i18 < 2; i18++)
        {
          for (int i19 = 0; i19 < i12; i19++)
          {
            paramGraphics.drawLine(i15, i17, i15 + i16, i17);
            i17++;
            i15 += i13;
            i16 += i14;
          }
          i17 = i9 + i8 + i11;
          i13 = -i13;
          i14 = -i14;
          i16 += i14;
        }
        paramGraphics.setColor(0);
        paramGraphics.drawRect(0, i9 - i10 - 1, 239, i9 + i8 + i10 - (i9 - i10 - 1));
      }
      i2 += this.aS / 2;
      int i10 = 0;
      for (int i11 = this.aR; ((i11 < this.bT.length ? 1 : 0) & (i4 < i5 ? 1 : 0)) != 0; i11++)
      {
        if ((this.bT[i11] != null) && (this.bT[i11].length() > 0) && (this.bT[i11].charAt(0) == '*'))
        {
          if (i10 == this.co)
          {
            i12 = this.bi.b() - this.bi.d;
            paramGraphics.setColor(255, 255, 255);
            paramGraphics.fillRect(0, i2 - 2 + 1, 240, i12 + 4);
            paramGraphics.setColor(76, 89, 39);
            paramGraphics.fillRect(0, i2 - 1 + 1, 240, i12 + 2);
          }
          this.bi.a(paramGraphics, this.bT[i11], 1, this.bT[i11].length() - 1, i3, i2, 20);
          i10++;
        }
        else
        {
          this.bi.a(paramGraphics, this.bT[i11], i3, i2, 20);
        }
        i2 += i1;
        i4++;
      }
      i2 = 320 - i1 - 1;
      int i12 = 0;
      if (this.dj) {
        i12 = 2;
      }
      paramGraphics.setColor(38, 43, 23);
      paramGraphics.fillRect(0, i2, 240, 320 - i2);
      i2++;
      i2 += (320 - i2 - this.bi.b()) / 2;
      if (System.currentTimeMillis() > this.aE)
      {
        if (this.aZ) {
          this.bi.a(paramGraphics, this.jdField_do[i12], i3, i2, 20);
        }
        this.bi.a(paramGraphics, this.jdField_do[1], 240 - this.bi.a(this.jdField_do[1]) - (i3 - 0), i2, 20);
      }
      return;
    }
    catch (Exception localException) {}
  }
  
  private final void ag()
  {
    this.dV = true;
    this.bN = b(false);
    repaint();
    serviceRepaints();
    this.bN = null;
    this.dV = false;
  }
  
  private static final void b(i parami)
  {
    int[] arrayOfInt1 = dn;
    int[] arrayOfInt2 = aA;
    int[] arrayOfInt3 = dg;
    parami.a = ((int)((arrayOfInt3[0] - parami.j) * arrayOfInt2[df] - (arrayOfInt3[1] - parami.k) * arrayOfInt1[df] >> 16));
    parami.b = ((int)((arrayOfInt3[0] - parami.j) * arrayOfInt1[df] + (arrayOfInt3[1] - parami.k) * arrayOfInt2[df] >> 16));
    parami.c = ((int)((arrayOfInt3[2] - parami.l) * arrayOfInt2[dd] - parami.b * arrayOfInt1[dd] >> 16));
    parami.b = ((int)((arrayOfInt3[2] - parami.l) * arrayOfInt1[dd] + parami.b * arrayOfInt2[dd] >> 16));
  }
  
  private static final void c(int[] paramArrayOfInt, int paramInt)
  {
    int[] arrayOfInt1 = dn;
    int[] arrayOfInt2 = aA;
    int[] arrayOfInt3 = dg;
    do
    {
      int i1 = paramInt * 6;
      paramArrayOfInt[(i1 + 3)] = ((int)((arrayOfInt3[0] - paramArrayOfInt[i1]) * arrayOfInt2[df] - (arrayOfInt3[1] - paramArrayOfInt[(i1 + 1)]) * arrayOfInt1[df] >> 16));
      paramArrayOfInt[(i1 + 4)] = ((int)((arrayOfInt3[0] - paramArrayOfInt[i1]) * arrayOfInt1[df] + (arrayOfInt3[1] - paramArrayOfInt[(i1 + 1)]) * arrayOfInt2[df] >> 16));
      paramArrayOfInt[(i1 + 5)] = ((int)((arrayOfInt3[2] - paramArrayOfInt[(i1 + 2)]) * arrayOfInt2[dd] - paramArrayOfInt[(i1 + 4)] * arrayOfInt1[dd] >> 16));
      paramArrayOfInt[(i1 + 4)] = ((int)((arrayOfInt3[2] - paramArrayOfInt[(i1 + 2)]) * arrayOfInt1[dd] + paramArrayOfInt[(i1 + 4)] * arrayOfInt2[dd] >> 16));
      paramInt--;
    } while (paramInt >= 0);
  }
}


/* Location:              C:\Documents and Settings\Administrator\桌面\3D Contr Terrorism se k790 240-320.jar!\h.class
 * Java compiler version: 4 (48.0)
 * JD-Core Version:       0.7.1
 */