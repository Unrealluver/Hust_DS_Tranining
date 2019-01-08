#include <stdio.h>
#include <iostream>
#include "extendTest.h"

using namespace std;

Point::Point() {
    x = 0;
    y = 0;
}
Point::Point(int x, int y) {
    this->x = x;
    this->y = y;
}

Point::Point(int x, int y, int varA) {
    Point(x, y);
    this->varA = varA;
}

void Point::virMethod() {
    cout << "this is the virtual method of Point"
         << endl;

}

void DoublePoint::virMethod() {
    cout << "this is the virtual method of DPoint"
         << endl;
}

void TriplePoint::virMethod() {
    cout << "this is the virtual method of TPoint"
         << endl;
}

void SonPoint::virMethod() {
    cout << "this is the virtual method of SPoint"
         << endl;
}

void Point::printWhich() {
    virMethod();
}

void Point::retake() {
    cout << "this is the no Param method"
         << endl;
}

void Point::retake(bool flag) {
    if (flag)
        cout << "this is the method with params"
             << endl;
}

void DoublePoint::retake() {
    cout << "this is the method of DoublePoint"
         << endl;
}

void DoublePoint::virRetake() {
    Point::virRetake();
}

void DoublePoint::sameMethod() {
    cout << "this is the same method that provided by D"
         << endl;
}

void TriplePoint::sameMethod() {
    cout << "this is the same method that provided by T"
         << endl;
}

void Point::virRetake() {
    cout << "this is the virtual method with no params"
         << endl;
}

void Point::virRetake(bool flag) {
    if (flag)
        cout << "this is the virtual method with params"
             << endl;
}
void Point::draw() {
    cout << "this is the output of Point: x:"
         << x << "\t y:" << y << endl;
}

Line::Line(int x, int y, int length, int varB) : Point(x, y) {
    this->length = length;
    this->varB = varB;
}

void Line::draw() {
    cout << "this is the output of Line: x:"
         << x << "\t y:" << y << "\t length:" << length << endl;
}

Circle::Circle(int x, int y, int radius, int varC) : Point(x, y) {
    this->radius = radius;
    this->varC = varC;
}

void Circle::draw() {
    cout << "this is the output of Circle: x:"
         << x << "\t y:" << y << "\t radius:" << radius << endl;
}

Multi::Multi(int x, int y, int radius, int length, int center, int varD) : Circle(x + 1, y + 1, radius + 1, 0),
                                                                           Point(x, y),
                                                                           Line(x + 2, y + 2, length + 2, 0) {
    this->center = center;
    this->varD = varD;
}

void Multi::draw() {
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

/** Question 3:
 *
 *      采用虚函数的菱形继承中,两个直接
 *  父类分别对于目标虚函数进行 Override
 *  子类不处理该函数, 会发生什么, 子类
 *  同样 Override 会发生什么.
 */

/** Question 4:
 *      两个父类中含有同名方法, 子类同时
 *  继承这两个类, 调用该方法会发生什么,
 *  若该同名方法中有一个被声明为 virtual
 *  会发生什么, 是不是子类必须也 Override
 *  这个方法呢?
 */

/** Question 5:
 *      在父类中声明一个a方法,再同时声明
 *  一个重载的a方法,子类中声明一个同名的
 *  a方法,此时调用适用于父类中参数类型的
 *  a方法,会如何,如果为父类的两个a方法添
 *  加virtual属性, 那么它们还能算作是重载
 *  吗?
 */

/** Question 6:
 *
 *      虚基类继承下被声明为虚基类的父类对象
 *  与子类对象本身在地址上是否具有不连续性,
 *  以及4个字节大小的虚基类指针如何体现.
 */

/** Question 7:
 *
 *      虚基类的构造函数和一般类的构造函数同时
 *  出现在初始化列表当中时,他们的初始化顺序如何
 *  ?
 */

/**
 * Plus 1:
 * CPP 的虚继承机制:
 *
 *      父类中A函数调用B函数, 在子类中覆写
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

    // local test
    DoublePoint doublePoint;
    doublePoint.virMethod();
    TriplePoint triplePoint;
    triplePoint.virMethod();
    // pointer test
    Point * pointP;
    pointP = &doublePoint;
    printWhich(pointP);
    // 注: 此处如果是私有继承, 子类对象无法赋给父类指针;

    // reference test
    Point &pointR = triplePoint;
    printWhich(&pointR);

    // final son test
    SonPoint sonPoint;
    sonPoint.virMethod();
    // (子类无处理)error: request for member ‘virMethod’ is ambiguous
    // (子类仅声明)error: undefined reference to `vtable for SonPoint'
    // (子类声明且定义) this is the virtual method of SPoint
    /** Conclusion 3:
     *
     *      子类此处如果不对从父类继承下来的virtual方法进行处理,
     *  在调用的时候会报歧义错误.此处逻辑很好理解, 因为子类当中找
     *  不到相关实现, 所以会在父类中寻找, 而此时恰好两个父类都对其
     *  有所定义, 所以会报二义性错误.
     *
     *      子类仅仅只是声明而不定义的话则会有所不同, 因为子类当中
     *  有对此虚函数的声明, 所以编译器会去虚函数表中寻找该虚函数,
     *  但由于我们没有对其进行定义, 于是会报虚函数表错误, 告诉我们
     *  此虚函数在表中缺少相应的定义.
     *
     *      子类声明且提供相关的定义, 此时可以正常运行.
     */

    // 成员方法测试
    doublePoint.printWhich();
    triplePoint.printWhich();
    sonPoint.DoublePoint::printWhich();
    sonPoint.TriplePoint::printWhich();
    // 注: 此处如果不注明作用域会因不知调用哪一个直接父类的方法而报错
//    sonPoint.Point::printWhich();
    // 注: 此处不可以直接调用源头基类的方法.会报二义性错误
    // error: ‘Point’ is an ambiguous base of ‘SonPoint’

    // 测试来自不同父类的同样方法
//    sonPoint.sameMethod();
    //  error: request for member ‘sameMethod’ is ambiguous
    // 不出我们所料报了二义性的错误.

    // 当其中一个父类的方法被声明为virtual时
//    sonPoint.sameMethod();
    //  error: request for member ‘sameMethod’ is ambiguous
    //  任然是报了二义性的错误.virtual并未使该方法再优先级上有改变

    /** Conclusion 4:
     *
     *      子类继承的父类中有同名方法时, 必须表明该方法来自于哪一个父类,
     *  不然就会报二义性错误.
     *
     *      就算是表明为virtual也不能改变这一点.
     *      virtual只是表明该方法的存储位置有改变, 单独提供虚函数vptr指向他,
     *  但并不代表该方法再优先级上有何变化, 再相同的作用域当中一样可以发生重载,
     *  一样会有二义性的情况产生.
     *
     */

    // 测试重载覆盖
    doublePoint.retake();
    doublePoint.Point::retake(true);
//    doublePoint.retake(true);
    // error: no matching function for call to ‘DoublePoint::retake(bool)’
    // 会提示找不到匹配的函数

    doublePoint.virRetake();
//    doublePoint.virRetake(true);
    // error: no matching function for call to ‘DoublePoint::virRetake(bool)’
    // 会提示找不到匹配的项

    // 测试两个父类中
    /** Conclusion 5:
     *
     *      如果我们再父类当中声明了重载的两个方法, 然后再由子类覆盖
     *  其中的某一个方法, 那么当我们在调用另一个方法的时候, 编译器会
     *  报错告诉我们再子类的类体内无法找到匹配的方法.我们只能再前面
     *  声明一下该方法的作用域
     *
     *      就算我们声明为virtual, 也不会改变函数重载的关系,同时,
     *  也不会影响子类当中因此而生的无匹配函数的问题,该问题同样会在
     *  这里出现.
     */


    cout << "hello\n";
}
