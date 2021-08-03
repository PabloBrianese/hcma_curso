/* A C-program for MT19937: Real number version                 */
/* genrand() generates one pseudorandom real number (double)    */
/* wich is uniformly distributed on [0, 1]-interval, for each   */
/* call. sgenrand(seed) set initial values to the working area  */
/* of 624 words. Before genrand(), sgenrand(seed) must be       */
/* called once. (seed is any 32-bit integer except for 0).      */
/* Integer generator is obtained by modifiying two lines.       */
/*   Coded by Takuji Nishimura, considering the suggestions by  */
/* Topher Cooper and Marc Rieffel in July-Aug. 1997. Comments   */
/* should be addressed to: matsumoto@math.keio.ac.jp            */

#include <stdio.h>

/* Period parameters */

#define N 624
#define M 397
#define MATRIX_A 0x9908b0df   /* constant vector a */
#define UPPER_MASK 0x80000000 /* most significant w-r bits */
#define LOWER_MASK 0x7fffffff /* least significant r bits */

/* Tempering parameters */
#define TEMPERING_MASK_B 0x9d2c5680
#define TEMPERING_MASK_C 0xefc60000
#define TEMPERING_SHIFT_U(y)  (y >> 11)
#define TEMPERING_SHIFT_S(y)  (y << 7)
#define TEMPERING_SHIFT_T(y)  (y << 15)
#define TEMPERING_SHIFT_L(y)  (y >> 18)

static unsigned long mt[N];  /* the array for the state vector */
static int mti=N+1;  /* mti==N+1 means mt[N] is not initialized */

/* initializing the array with NONZERO seed */
void
sgenrand(seed)
     unsigned long seed;
{
  /* setting initial seeds to mt[N] using         */
  /* the generator Line 25 of Table 1 in          */
  /* [KNUTH 1981, The Art of Computer Programming */
  /* Vol. 2 (2nd Ed.), pp102]                     */
  mt[0] = seed & 0xffffffff;
  for (mti = 1; mti < N; mti++)
    mt[mti] = (69069 * mt[mti-1]) & 0xffffffff;
}

/* double */ /* for generating reals */
unsigned long /* for integer generation */
genrand()
{
  unsigned long y;
  static unsigned long mag01[2]={0x0, MATRIX_A};
  /* mag01[x] = x * MATRIX_A for x=0,1 */

  if (mti >= N) { /* generate N words at one time */
    int kk;

    if (mti == N+1)   /* if sgenrand() has not been called,  */
      sgenrand(4357); /* a default initial seed is used      */

    for (kk = 0; kk < N-M; kk++) {
      y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
      mt[kk] = mt[kk+M] ^ (y >> 1) ^ mag01[y & 0x1];
    }
    for(; kk < N-1; kk++) {
      y = (mt[kk]&UPPER_MASK)|(mt[kk+1]&LOWER_MASK);
      mt[kk] = mt[kk + (M-N)] ^ (y >> 1) ^mag01[y & 0x1];
    }
  y = (mt[N-1]&UPPER_MASK) | (mt[0]&LOWER_MASK);
  mt[N-1] = mt[M-1] ^ (y >> 1) ^ mag01[y & 0x1];
  
  mti = 0;
  }

  y = mt[mti++];
  y ^= TEMPERING_SHIFT_U(y);
  y ^= TEMPERING_SHIFT_S(y) & TEMPERING_MASK_B;
  y ^= TEMPERING_SHIFT_T(y) & TEMPERING_MASK_C;
  y ^= TEMPERING_SHIFT_L(y);

  /* return ( (double)y / (unsigned long)0xffffffff ); */ /* for generating reals */
  return y; /* for integer generation */
}

/* this main() outputs first 1000 generated numbers */
int main()
{
  sgenrand(4357); /* any nonzero integer can be used as a seed */
  for (int j = 0; j < 1000; j++) {
    printf("%lu ", genrand());
    if (j % 8 == 7) printf("\n");
  }
  printf("\n");
}
