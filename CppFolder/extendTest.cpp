#include <stdio.h>
#include <iostream>
#include "./extendTest.h"
using namespace std;

Point :: Point(int x, int y) {
    this -> x = x;
    this -> y = y;
}

Point :: Point(int x, int y, int varA) {
    Point(x, y);
    this -> varA = varA;
}

void Point :: draw() {
    cout << "this is the output of Point: x:"
        << x << "\t y:" << y << endl;
}

Line :: Line(int x, int y, int length, int varB) : Point(x, y){
    this -> length = length;
    this -> varB = varB;
}

void Line :: draw() {
    cout << "this is the output of Line: x:"
        << x << "\t y:" << y << "\t length:" << length << endl;
}

Circle :: Circle(int x, int y, int radius, int varC) : Point(x, y) {
    this -> radius = radius;
    this -> varC = varC;
}

void Circle :: draw() {
    cout << "this is the output of Circle: x:"
        << x << "\t y:" << y << "\t radius:" << radius << endl;
}

Multi :: Multi(int x, int y, int radius, int length, int center, int varD) : Circle(x + 1, y + 1, radius + 1, 0), Line(x + 2, y + 2, length + 2, 0), Point(x, y) {
    this -> center = center;
    this -> varD = varD;
}

void Multi :: draw() {
    cout << "this is the output of Multi: x:"
        << x << "\t y:" << y << "\t radius:" <<
        radius << "\t length:" << length << "\t center:" << center << endl;
}
/** Question 1:
 *
 *      菱形继承中源头基类的方法分别被
 *  两个类 Override , 再由一个子类同时
 *  继承这两个类, 调用此方法, 此时该方
 *  法同时具有三个实现: 源头基类, 两个
 *  直接父类, 会采用哪一个实现呢?
 */

/** Question 2:
 *
 *      采用虚继承的方法来使菱形继承中
 *  的两个中间类继承源头类, 然后最底部
 *  的子类再继承这两个中间类, 在变量初
 *  始化的时候三个非基类分别对源头类进
 *  行带参初始化, 在调用各个类中的函数
 *  进行展示, 源自源头基类的数据部分会
 *  有怎样的显示呢?
 */

/**
 * Plus 1:
 * CPP 的虚继承机制:
 *
 *      父类中A函数调用B函数, 在子 类中覆写
 * B函数, 此时若不再B函数前声明virtual
 * , 则会调用父类中的B函数而非子类覆写
 * 过的.
 */

/**
 * Plus 2:
 * 友元函数的继承性问题
 */

int main() {
    Multi multi(1, 1, 1, 1, 1, 1);
    // error!: request for member draw is ambiguous. 
    multi.draw();
    /** Conclusion 1:
     *
     *      菱形继承的情况下,继承链底端若不重
     * 写多个父类中均出现的函数而直接调用, 将
     * 会报歧义的error.
     */

    /** Conclusion 2:
     *      
     *      采用虚继承机制下的菱形继承, 产生的
     * 最终结果为再底部子类最后用基类初始化的
     * 结果,很显然, 因为根据虚基类的实现原理,
     * 我们知道当一个类被声明为虚继承时,编译器
     * 将会自动在其内部增加一个四个字节大小的
     * 虚指针,用作当多个类同时继承一个父类的时
     * 候, 处理这之间多个重复对象变量之间的冲
     * 突, 处理的具体方法为指向一个虚继承表,
     * 该表中记载了被虚继承的父类相对于子类的
     * 偏移地址.再根据此偏移地址即可找到共有的
     * 父类.至此,虚继承完美解决了多重继承情况
     * 下的下级子类持有多个父类变量实体的情况.
     */

    cout << "hello\n";
}
