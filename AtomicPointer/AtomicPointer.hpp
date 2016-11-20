#ifndef ATOMIC_POINTER_H
#define ATOMIC_POINTER_H

namespace zy {

//__volatile__��ʾ��ֹ�������Ը�ֵ�����Ż���
// ǿ�Ʊ���ʹ�þ�ȷ�ڴ��ַ���� cache��register����memory��ʾ���ڴ����޸Ĳ�������Ҫ���¶���

inline void MemoryBarrier() {
  __asm__ __volatile__("":: : "memory");
}

class AtomicPointer{
 private:
  void * rep_;
 public:
  AtomicPointer(){}
  explicit AtomicPointer(void * p):rep_(p){}

  inline void *NoBarried_Load() const{
    return rep_;
  }

  inline void NoBarrier_Store(void * v){
    rep_= v;
  }

  inline void * Acquare_Load() const{
    void * result = rep_;
    MemoryBarrier();
    return result;
  }

  inline void  Release_Store(void * v){
    MemoryBarrier();
    rep_ = v;
  }

};

}

#endif