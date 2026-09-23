/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    int result=~(~x|~y);
    return result;
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(x & y) & ~(~x & ~y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if(!x)
        return (!y);
    else if(!y)
        return 0;
    else
        return !(((x>>31)&1)^((y>>31)&1));
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int shift;
    int result=0;

    shift=(v>0xFFFF)<<4;
    v=v>>shift;
    result=result|shift;

    shift=(v>0xFF)<<3;
    v=v>>shift;
    result=result|shift;

    shift=(v>0xF)<<2;
    v=v>>shift;
    result=result|shift;

    shift=(v>0x3)<<1;
    v=v>>shift;
    result=shift|result;

    shift=(v>0x1)<<0;
    result=result|shift;

    return result;

}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int shiftn = n << 3;
    int shiftm = m << 3;
    int byten = (x >> shiftn) & 0xFF;
    int bytem = (x >> shiftm) & 0xFF;
    int diff = byten ^ bytem;

    return x ^ (diff << shiftn) ^ (diff << shiftm);
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned result = 0;
    unsigned i = 32;

    while (i) {
        result = (result << 1) | (v & 1);
        v = v >> 1;
        i = i - 1;
    }
    return result;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int result=0;
    result=x>>n;
    int mid=(0xFFFFFFFF>>n);
    result=(mid&result);
    return result;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int y = ~x;
    int count = 0;
    int shift;

    shift = !(y >> 16) << 4;
    count = count + shift;
    y = y << shift;

    shift = !(y >> 24) << 3;
    count = count + shift;
    y = y << shift;

    shift = !(y >> 28) << 2;
    count = count + shift;
    y = y << shift;

    shift = !(y >> 30) << 1;
    count = count + shift;
    y = y << shift;

    shift = !(y >> 31);
    count = count + shift;

    return count + !y;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned sign;
    unsigned value;
    unsigned exponent;
    unsigned fraction;
    unsigned remainder;
    int shifts = 0;

    if (!x)
        return 0;

    sign = x & 0x80000000;
    value = x;

    if (sign)
        value = ~value + 1;

    while (!(value & 0x80000000)) {
        value = value << 1;
        shifts = shifts + 1;
    }

    exponent = 158 - shifts;
    fraction = (value & 0x7FFFFFFF) >> 8;
    remainder = value & 0xFF;

    if (remainder > 0x80)
        fraction = fraction + 1;
    else if (remainder == 0x80) {
        if (fraction & 1)
            fraction = fraction + 1;
    }

    return sign | ((exponent << 23) + fraction);
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign = uf & 0x80000000;
    unsigned exponent = (uf >> 23) & 0xFF;

    if (exponent == 0xFF)
        return uf;

    if (exponent == 0)
        return sign | ((uf & 0x7FFFFFFF) << 1);

    if (exponent == 0xFE)
        return sign | 0x7F800000;

    return uf + (1 << 23);
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    int sign = uf2 >> 31;
    int exponent = (uf2 >> 20) & 0x7FF;
    int realExponent = exponent - 1023;
    unsigned high;
    int result;

    if (exponent > 0x7FE)
        return 0x80000000;

    if (realExponent < 0)
        return 0;

    if (realExponent > 30)
        return 0x80000000;

    high = (uf2 & 0xFFFFF) | 0x100000;

    if (realExponent <= 20) {
        result = high >> (20 - realExponent);
    } else {
        result = (high << (realExponent - 20)) |(uf1 >> (52 - realExponent));
    }

    if (sign)
        return -result;
    else
        return result;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    unsigned exponent;

    if (x < -149)
        return 0;

    if (x < -126)
        return 1 << (x + 149);

    if (x <= 127) {
        exponent = x + 127;
        return exponent << 23;
    }

    return 0x7F800000;
}
