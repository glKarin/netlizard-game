final class g
{
  int[] a;
  int[] b;
  int[][] c;
  short d;
  int e;
  int f;
  int g;
  int h;
  int i;
  int j;
  int k;
  byte l = -1;
  int m = 40960000;
  int n = 40960000;
  int o = 8192000;
  int p = 0;
  int q = 0;
  short r;
  byte s;
  boolean t = true;
  
  g(o paramo)
  {
    this();
  }
  
  private g() {}
  
  private final void a()
  {
    int[] arrayOfInt1 = h.aA;
    int[] arrayOfInt2 = h.dn;
    int i1 = h.dg[0];
    int i2 = h.dg[1];
    int i3 = h.dg[2];
    int i4 = h.df;
    int i5 = h.dd;
    int i6 = 0;
    int i7 = 0;
    int i9 = arrayOfInt1[this.q];
    int i10 = arrayOfInt2[this.q];
    int i8 = h.g[this.s].k;
    int i11;
    do
    {
      i11 = i8 * 6;
      this.a[(i11 + 3)] = ((int)(this.a[i11] * i9 - this.a[(i11 + 1)] * i10 >> 16));
      this.a[(i11 + 4)] = ((int)(this.a[i11] * i10 + this.a[(i11 + 1)] * i9 >> 16));
      this.a[(i11 + 5)] = ((int)(this.a[(i11 + 2)] * arrayOfInt1[this.p] - this.a[(i11 + 4)] * arrayOfInt2[this.p] >> 16));
      this.a[(i11 + 4)] = ((int)(this.a[(i11 + 2)] * arrayOfInt2[this.p] + this.a[(i11 + 4)] * arrayOfInt1[this.p] >> 16));
      i6 = this.a[(i11 + 5)];
      i7 = this.a[(i11 + 3)];
      this.a[(i11 + 3)] = ((int)((i1 - (i7 + this.m)) * arrayOfInt1[i4] - (i2 - (this.a[(i11 + 4)] + this.n)) * arrayOfInt2[i4] >> 16));
      this.a[(i11 + 4)] = ((int)((i1 - (i7 + this.m)) * arrayOfInt2[i4] + (i2 - (this.a[(i11 + 4)] + this.n)) * arrayOfInt1[i4] >> 16));
      this.a[(i11 + 5)] = ((int)((i3 - (i6 + this.o)) * arrayOfInt1[i5] - this.a[(i11 + 4)] * arrayOfInt2[i5] >> 16));
      this.a[(i11 + 4)] = ((int)((i3 - (i6 + this.o)) * arrayOfInt2[i5] + this.a[(i11 + 4)] * arrayOfInt1[i5] >> 16));
      i8--;
    } while (i8 >= 0);
    i8 = this.b.length >> 4;
    do
    {
      i11 = i8 << 4;
      this.b[(i11 + 13)] = ((int)(this.b[(i11 + 10)] * arrayOfInt1[this.q] - this.b[(i11 + 11)] * arrayOfInt2[this.q] >> 16));
      this.b[(i11 + 14)] = ((int)(this.b[(i11 + 10)] * arrayOfInt2[this.q] + this.b[(i11 + 11)] * arrayOfInt1[this.q] >> 16));
      this.b[(i11 + 15)] = ((int)(this.b[(i11 + 12)] * arrayOfInt1[this.p] - this.b[(i11 + 14)] * arrayOfInt2[this.p] >> 16));
      this.b[(i11 + 14)] = ((int)(this.b[(i11 + 12)] * arrayOfInt2[this.p] + this.b[(i11 + 14)] * arrayOfInt1[this.p] >> 16));
      i8--;
    } while (i8 >= 0);
  }
  
  static void a(g paramg)
  {
    paramg.a();
  }
}


/* Location:              C:\Documents and Settings\Administrator\桌面\3D Contr Terrorism se k790 240-320.jar!\g.class
 * Java compiler version: 4 (48.0)
 * JD-Core Version:       0.7.1
 */