/* 
 * CS:APP Data Lab 
 * 
 * <Leo Liu 005589443>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }


NOTES:
  1. Our checker requires that you do NOT define a variable after 
     a statement that does not define a variable.

     For example, this is NOT allowed:

     int illegal_function_for_this_lab(int x, int y) {
      // this statement doesn't define a variable
      x = x + y + 1;
      
      // The checker for this lab does NOT allow the following statement,
      // because this variable definition comes after a statement 
      // that doesn't define a variable
      int z;

      return 0;
     }
     
  2. VERY IMPORTANT: Use the dlc (data lab checker) compiler (described in the handout)
     to check the legality of your solutions.
  3. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  4. Use the btest test harness to check your functions for correctness.
  5. Use the BDD checker to formally verify your functions
  6. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2012 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* We do support the IEC 559 math functionality, real and complex.  */
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */
//1
/*
 * isTmin - returns 1 if x is the minimum, two's complement number,
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmin(int x) {
  //bias for corner case 0 
  //only tmin+tmin = 0
  //negate for result
  int bias;
  bias = !x;
  x = x + bias;
  return !(x+x);
}
//2
/* 
 * isEqual - return 1 if x == y, and 0 otherwise 
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) {
//x^y = 0 only when x=y
//negate for result
  return !(x^y);
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  //bias to differentiate x >= 0 and x < 0 cases
  //shift x right n-1 times to evaluate if fits bits
  //for x > 0 if after shift there exists a 1, then cannot fit 
  //for x < 0 if after shift there exists a 0, then cannot fit (sign extension) 
  int bias,fits;
  bias = ~(x >> 31);
  n = n + ~0;
  x = (x >> n);
  fits = (x^bias);
  return !~fits;
}
/* 
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
  //extract the nth and mth byte so they are represented from 0-15
  //remove them from the original byte pattern by subtraction
  //append mth byte to nth location and vise versa
  int shiftn, shiftm, bias, bias2, nbyte, mbyte, xsubtracted, xnew;
  shiftn = (n << 3);
  shiftm = (m << 3);
  bias = (0xff << (shiftn));
  bias2 = (0xff << (shiftm));
  nbyte = x & bias;
  nbyte = (nbyte >> (shiftn)) & 0xff;
  mbyte = x & bias2;
  mbyte = (mbyte >> (shiftm)) & 0xff;
  xsubtracted = x + (~(nbyte << shiftn) + 1) + (~(mbyte << shiftm)+ 1);
  xnew = xsubtracted + (mbyte << shiftn) + (nbyte << shiftm);
  return xnew;
}
//3
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  //make all integers x (except 0) negative using bias
  //now  two possible cases: negative integer for y or zero for z 
  //second bias to determine ON or OFF of conditional statement
  //either y or z will be returned exclusively due to second bias 
  int bias, oppx, bias2;
  bias = (x >> 31);
  bias = (x & bias);
  oppx = ~x + 1;
  x = oppx + bias + bias;
  bias2 = (x >> 31);
  return((y & bias2) + (z & ~bias2));
}
/* 
 * subtractionOK - Determine if can compute x-y without overflow
 *   Example: subtractionOK(0x80000000,0x80000000) = 1,
 *            subtractionOK(0x80000000,0x70000000) = 0, 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int subtractionOK(int x, int y) {
  //4 cases: pos-pos, neg-neg, pos-neg, neg-pos
  //pos-pos and neg-neg cannot overflow so use bias to skip algorithm
  //use sign bias to return correct result
  //pos-neg and neg-pos will overflow if different signs for x and result after subtraction
  //subtract using complement 
  int xsign, ysign, signcheck, result, xsign2, overflow, bias;
  xsign = (x >> 31);
  ysign = (y >> 31);
  signcheck = !(xsign ^ ysign);
  result = x + ~y + 1;
  xsign2 = (result >> 31);
  overflow = !(xsign^ xsign2);
  bias = !signcheck;
  return (signcheck + ((bias) & overflow));
}
/* 
 * isGreater - if x > y  then return 1, else return 0 
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y){
  //5 cases: pos > pos, neg > neg, pos > neg, neg > pos, x=y
  //sign swap from x-y means false for pos > pos
  //use bias to reverse algorithm for neg > neg
  //all pos > neg are true so ignore
  //all neg > pos are false so use bias
  //all x=y are false so use bias
  //use bias to ignore sign swap algorithm for latter 3 cases
  int xsign, ysign, signcheck, negposcheck, equalcheck, negnegrev, xnew, xsignnew, alg;
  xsign = (x >> 31);
  ysign = (y >> 31);
  signcheck = (xsign ^ ysign);
  negposcheck = xsign & signcheck;
  equalcheck = !(x ^ y);
  negnegrev = ~(xsign & ysign) + 1;
  xnew = (x + ~y + 1); 
  xsignnew = (xnew >> 31);
  alg = (xsign ^ xsignnew) + negnegrev;
  alg = alg & !signcheck;
  alg = alg + negposcheck + equalcheck;
  return (!alg);
}
//4
/* 
 * logicalNeg - implement the ! operator, using all of 
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4 
 */
int logicalNeg(int x) {
  //use bias to change all integers x (other than 0) to negative
  //now 2 possible cases: 0 or negative 
  //add 1 to the MSB >> 31 for negation
  //logic: 0 has MSB 0 and negative number MSB is 1
  int bias, oppx;
  bias = (x >> 31);
  bias = (x & bias);
  oppx = ~x + 1;
  x = oppx + bias + bias;
  x = (x >> 31);
  return (x+1);
}
/* 
 * twosComp2SignMag - Convert from two's complement to sign-magnitude 
 *   where the MSB is the sign bit
 *   You can assume that x > TMin
 *   Example: twosComp2SignMag(-5) = 0x80000005.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 4
 */
int twosComp2SignMag(int x) {
  //negate using ~x+1
  //use bias to get positive sign for x>0 
  //bias gives all 0's or 1's depending on x
  //shifted bias also gives sign
  //update bias through masking
  //twice the bias with new x to get absolute value of original x 
  //add sign for result
  int oldx, bias, sign;
  oldx = x;
  x = ~x + 1;
  bias = (oldx >> 31);
  sign = (bias << 31);
  bias = ~bias;
  bias = (oldx & bias);
  return (sign+x+bias+bias);
}
