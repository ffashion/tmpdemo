#include <iostream>
#include <stdint.h>
using namespace std;
struct Base{
	//有个问题 是这个不会传递this 指针导致参数有问题 输出结果是不对的
    virtual int one(int x,int y){
        printf("one: %d\n",x + y);
        return 0;
    }
    virtual int two(int x,int y, int z){
        printf("two :%d\n",x+y+z);
        return  0;
    }
};
typedef int(*fun_t1)(int x,int y);
typedef int (*fun_t2)(int x,int y,int z);
struct vftable_t{
    fun_t1  fun1;
    fun_t2  fun2;
};

struct vfptr_t{
    struct vftable_t *vftable;
};
int main(){
    Base *p;
    p = new Base();
    struct vfptr_t *vfptr = (struct vfptr_t *) p;
    vfptr->vftable->fun1(1, 1);
    vfptr->vftable->fun2(2,2,1);

    return 0;
}