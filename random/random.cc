#include "random.h"

using namespace zy;

///�㷨���ģ� seed = (seed * A + C) % M ,��ʹ������ͬ�෨��������һ�������
///�� C Ϊ����ʱ�򣬳�Ϊ"��ͬ�෨", ����������������ʹ�õľ��ǳ�ͬ�෨

//0x7fffffff == 2147483647L == 2^31-1 == 0111 1111 1111 1111 1111 1111 1111 1111
//s&0x7fffffff make sure seed is between from 0 to 2147483647L
Random::Random(uint32_t s) : seed_(s & 0x7fffffff) {
  //Avoid bad seeds
  if (seed_==0 || seed_==2147483647L) {
    seed_ = 1;
  }
}

//return next random number
uint32_t Random::Next() {
  static const uint32_t M = 2147483647L;  // 2^31 -1
  static const uint64_t A = 16807;        // 0100 0001 1010 0111
  /*
   * We are computing
   *  seed_ = (seed_ * A) % M , where M = 2^31 -1
   *  seed_ must not be zero or M, or else all subsequent computed values
   *  will be zero or M respectively. For all other values, seed_ will end
   *  up cycling through every number in [1,M-1]
   */
  uint64_t product = seed_*A;
  //compute (product % M) using the fact that ((x<<31) %M) == x
  seed_ = static_cast<uint32_t>((product >> 31) + (product & M));
  //the first reduction may overflow by 1 bit, so we may need to
  //repeat. mod == M is not possible; using > allows the faster
  //sign-bit-based test
  if (seed_ > M) {
    seed_ -= M;
  }
  return seed_;
}

//return a uniformly distributed value in the range [0..n-1]
//Requires: n > 0
uint32_t Random::Uniform(int n) {
  return Next()%n;
}

//Randomly returns true ~"1/n" of the time, and false otherwise
//Requires: n > 0
bool Random::OneIn(int n) {
  return (Next()%n)==0;
}

//pick "base" uniformly from range[0,max_log] and then
//return "base" random bits. The effect is to pick a number in the
//range [0,2^max_log-1] with exponential bias towards smaller numbers
uint32_t Random::Skewed(int max_log) {
  return Uniform(1 << Uniform(max_log + 1));
}

/*
  ֤��: ��ʽ(product%M) == (product>>31)+(product&M)������ע��M����2^31-1��
  ֤����
    ��Ϊproduct������uint64_t�����Խ�product�Ķ����ƴ����ҷֽ�ɸ�33λ�͵�31λ�������33λ��ֵΪH����31λ��ֵΪL��
    ��product�൱�ڸ�33λ�����ƶ���31λ���ϵ�31λ����H<<31+L��
    ��product����H*2^31+L����Դ��֪��product=seed_*A����seed_��A��С��M���� ** H�϶�С��M ** ��
    �Ӷ����ǿ��Եõ���
    ���ʽ���product%M = (H*2^31+L)%M = (H*M+H+L)%M = H+L��
    ���ʽ�ұ�(product>>31) + (product&M) = (H*2^31 +L)>>31+L = (H*2^31+L)/2^31+L = H+L��
    ע����31λ��ֵL���ܵ���M����ô���ʽ��߾͵���H�ˣ���ʱ���ʽ�ұߵ���H+M,���Ծ���Next()����������ж�H�Ƿ����M,��
    ����M�ͼ�ȥM��
 */