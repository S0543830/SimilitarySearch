/*
 * Copyright (c) 1997-1999 Massachusetts Institute of Technology
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

/* This file was automatically generated --- DO NOT EDIT */
/* Generated on Sun Nov  7 20:43:58 EST 1999 */

#include "fftw-int.h"
#include "fftw.h"

/* Generated by: ./genfft -magic-alignment-check -magic-twiddle-load-all -magic-variables 4 -magic-loopi -real2hc 15 */

/*
 * This function contains 64 FP additions, 25 FP multiplications,
 * (or, 50 additions, 11 multiplications, 14 fused multiply/add),
 * 40 stack variables, and 30 memory accesses
 */
static const fftw_real K509036960 = FFTW_KONST(+0.509036960455127183450980863393907648510733164);
static const fftw_real K823639103 = FFTW_KONST(+0.823639103546331925877420039278190003029660514);
static const fftw_real K250000000 = FFTW_KONST(+0.250000000000000000000000000000000000000000000);
static const fftw_real K559016994 = FFTW_KONST(+0.559016994374947424102293417182819058860154590);
static const fftw_real K587785252 = FFTW_KONST(+0.587785252292473129168705954639072768597652438);
static const fftw_real K951056516 = FFTW_KONST(+0.951056516295153572116439333379382143405698634);
static const fftw_real K484122918 = FFTW_KONST(+0.484122918275927110647408174972799951354115213);
static const fftw_real K216506350 = FFTW_KONST(+0.216506350946109661690930792688234045867850657);
static const fftw_real K866025403 = FFTW_KONST(+0.866025403784438646763723170752936183471402627);
static const fftw_real K500000000 = FFTW_KONST(+0.500000000000000000000000000000000000000000000);

/*
 * Generator Id's : 
 * $Id: exprdag.ml,v 1.41 1999/05/26 15:44:14 fftw Exp $
 * $Id: fft.ml,v 1.43 1999/05/17 19:44:18 fftw Exp $
 * $Id: to_c.ml,v 1.25 1999/10/26 21:41:32 stevenj Exp $
 */

void fftw_real2hc_15(const fftw_real *input, fftw_real *real_output, fftw_real *imag_output, int istride, int real_ostride, int imag_ostride)
{
     fftw_real tmp3;
     fftw_real tmp53;
     fftw_real tmp47;
     fftw_real tmp39;
     fftw_real tmp40;
     fftw_real tmp10;
     fftw_real tmp17;
     fftw_real tmp18;
     fftw_real tmp57;
     fftw_real tmp58;
     fftw_real tmp59;
     fftw_real tmp31;
     fftw_real tmp34;
     fftw_real tmp43;
     fftw_real tmp54;
     fftw_real tmp55;
     fftw_real tmp56;
     fftw_real tmp24;
     fftw_real tmp27;
     fftw_real tmp42;
     ASSERT_ALIGNED_DOUBLE;
     {
	  fftw_real tmp45;
	  fftw_real tmp1;
	  fftw_real tmp2;
	  fftw_real tmp46;
	  ASSERT_ALIGNED_DOUBLE;
	  tmp45 = input[0];
	  tmp1 = input[10 * istride];
	  tmp2 = input[5 * istride];
	  tmp46 = tmp2 + tmp1;
	  tmp3 = tmp1 - tmp2;
	  tmp53 = tmp45 + tmp46;
	  tmp47 = tmp45 - (K500000000 * tmp46);
     }
     {
	  fftw_real tmp22;
	  fftw_real tmp29;
	  fftw_real tmp32;
	  fftw_real tmp6;
	  fftw_real tmp23;
	  fftw_real tmp25;
	  fftw_real tmp16;
	  fftw_real tmp33;
	  fftw_real tmp9;
	  fftw_real tmp26;
	  fftw_real tmp13;
	  fftw_real tmp30;
	  ASSERT_ALIGNED_DOUBLE;
	  {
	       fftw_real tmp4;
	       fftw_real tmp5;
	       fftw_real tmp14;
	       fftw_real tmp15;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp22 = input[3 * istride];
	       tmp29 = input[6 * istride];
	       tmp32 = input[9 * istride];
	       tmp4 = input[13 * istride];
	       tmp5 = input[8 * istride];
	       tmp6 = tmp4 - tmp5;
	       tmp23 = tmp5 + tmp4;
	       tmp25 = input[12 * istride];
	       tmp14 = input[4 * istride];
	       tmp15 = input[14 * istride];
	       tmp16 = tmp14 - tmp15;
	       tmp33 = tmp15 + tmp14;
	       {
		    fftw_real tmp7;
		    fftw_real tmp8;
		    fftw_real tmp11;
		    fftw_real tmp12;
		    ASSERT_ALIGNED_DOUBLE;
		    tmp7 = input[7 * istride];
		    tmp8 = input[2 * istride];
		    tmp9 = tmp7 - tmp8;
		    tmp26 = tmp8 + tmp7;
		    tmp11 = input[istride];
		    tmp12 = input[11 * istride];
		    tmp13 = tmp11 - tmp12;
		    tmp30 = tmp12 + tmp11;
	       }
	  }
	  tmp39 = tmp6 - tmp9;
	  tmp40 = tmp13 - tmp16;
	  tmp10 = tmp6 + tmp9;
	  tmp17 = tmp13 + tmp16;
	  tmp18 = tmp10 + tmp17;
	  tmp57 = tmp29 + tmp30;
	  tmp58 = tmp32 + tmp33;
	  tmp59 = tmp57 + tmp58;
	  tmp31 = tmp29 - (K500000000 * tmp30);
	  tmp34 = tmp32 - (K500000000 * tmp33);
	  tmp43 = tmp31 + tmp34;
	  tmp54 = tmp22 + tmp23;
	  tmp55 = tmp25 + tmp26;
	  tmp56 = tmp54 + tmp55;
	  tmp24 = tmp22 - (K500000000 * tmp23);
	  tmp27 = tmp25 - (K500000000 * tmp26);
	  tmp42 = tmp24 + tmp27;
     }
     imag_output[5 * imag_ostride] = -(K866025403 * (tmp3 + tmp18));
     {
	  fftw_real tmp21;
	  fftw_real tmp37;
	  fftw_real tmp36;
	  fftw_real tmp38;
	  ASSERT_ALIGNED_DOUBLE;
	  {
	       fftw_real tmp19;
	       fftw_real tmp20;
	       fftw_real tmp28;
	       fftw_real tmp35;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp19 = (K866025403 * tmp3) - (K216506350 * tmp18);
	       tmp20 = K484122918 * (tmp10 - tmp17);
	       tmp21 = tmp19 + tmp20;
	       tmp37 = tmp20 - tmp19;
	       tmp28 = tmp24 - tmp27;
	       tmp35 = tmp31 - tmp34;
	       tmp36 = (K951056516 * tmp28) + (K587785252 * tmp35);
	       tmp38 = (K951056516 * tmp35) - (K587785252 * tmp28);
	  }
	  imag_output[imag_ostride] = tmp21 - tmp36;
	  imag_output[4 * imag_ostride] = tmp21 + tmp36;
	  imag_output[2 * imag_ostride] = tmp37 + tmp38;
	  imag_output[7 * imag_ostride] = tmp38 - tmp37;
     }
     {
	  fftw_real tmp63;
	  fftw_real tmp64;
	  fftw_real tmp62;
	  fftw_real tmp60;
	  fftw_real tmp61;
	  ASSERT_ALIGNED_DOUBLE;
	  tmp63 = tmp54 - tmp55;
	  tmp64 = tmp57 - tmp58;
	  imag_output[3 * imag_ostride] = (K587785252 * tmp63) - (K951056516 * tmp64);
	  imag_output[6 * imag_ostride] = -((K951056516 * tmp63) + (K587785252 * tmp64));
	  tmp62 = K559016994 * (tmp56 - tmp59);
	  tmp60 = tmp56 + tmp59;
	  tmp61 = tmp53 - (K250000000 * tmp60);
	  real_output[3 * real_ostride] = tmp61 - tmp62;
	  real_output[6 * real_ostride] = tmp62 + tmp61;
	  real_output[0] = tmp53 + tmp60;
	  {
	       fftw_real tmp41;
	       fftw_real tmp52;
	       fftw_real tmp44;
	       fftw_real tmp48;
	       fftw_real tmp49;
	       fftw_real tmp51;
	       fftw_real tmp50;
	       ASSERT_ALIGNED_DOUBLE;
	       tmp41 = (K823639103 * tmp39) + (K509036960 * tmp40);
	       tmp52 = (K509036960 * tmp39) - (K823639103 * tmp40);
	       tmp44 = K559016994 * (tmp42 - tmp43);
	       tmp48 = tmp42 + tmp43;
	       tmp49 = tmp47 - (K250000000 * tmp48);
	       real_output[5 * real_ostride] = tmp47 + tmp48;
	       tmp51 = tmp49 - tmp44;
	       real_output[2 * real_ostride] = tmp51 - tmp52;
	       real_output[7 * real_ostride] = tmp52 + tmp51;
	       tmp50 = tmp44 + tmp49;
	       real_output[real_ostride] = tmp41 + tmp50;
	       real_output[4 * real_ostride] = tmp50 - tmp41;
	  }
     }
}

fftw_codelet_desc fftw_real2hc_15_desc =
{
     "fftw_real2hc_15",
     (void (*)()) fftw_real2hc_15,
     15,
     FFTW_FORWARD,
     FFTW_REAL2HC,
     332,
     0,
     (const int *) 0,
};
