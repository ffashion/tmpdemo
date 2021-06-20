#include <iostream>
#include <stdint.h>
using namespace std;
struct Base{
    typedef int(Base::*fun_t1)(int x,int y);
    typedef int(Base::*fun_t2)(int x,int y,int z);

    virtual int one(int x,int y){
        printf("one: %d\n",x + y);
        return 0;
    }
    virtual int two(int x,int y, int z){
        printf("two:%d\n",x+y+z);
        return  0;
    }
};
struct vftable_t1{
    //Base::fun_t2是16位的 但是内存里面是8个字节的偏移
    Base::fun_t1  fun1;//16个字节宽度
    // Base::fun_t2  fun2; //但是我想让这个从8字节开始
};
struct vftable_t2{
    char *placeholder;
    Base::fun_t2  fun2; 
};
struct vfptr_t{
    union vftable_t{
        struct vftable_t1 *vftable1;
        struct vftable_t2 *vftable2;
    } vftable;
};
int main(){
    Base *p;
    p = new Base();
    struct vfptr_t *vfptr = (struct vfptr_t *) p;
    Base *obj = nullptr;
    (obj->*((Base::fun_t1) vfptr->vftable.vftable1->fun1))(1,100);
    (obj->*((Base::fun_t2)vfptr->vftable.vftable2->fun2))(1,100,1);
    return 0;
}