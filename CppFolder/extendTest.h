// 该类为我们实验探究时所需的源头基类
class Point {
private:
    int varA;
public:
    // 基类内重要的基础变量
    int x, y;

    // 提供一个无参构造方法
    Point();

    // 为我们的基类提供两种构造方法
    Point(int x, int y);

    Point(int x, int y, int varA);

    // 用来测试的virtual方法
    virtual void virMethod();

    // 用来测试重载的方法
    void retake();

    void retake(bool flag);

    // 用来测试virtual重载的方法
    virtual void virRetake();

    virtual void virRetake(bool flag);

    virtual // 用来供后续类 Override 的draw方法
    void draw();

    void printWhich();
};

// 菱形继承中的一个中间类
class Line : virtual public Point {
private:
    int varB;
public:
    // 中间类的特征变量
    int length;

    // 中间类的构造函数
    Line(int x, int y, int length, int varB);

    // 中间类对于draw方法的重载
    void draw();
};

// 菱形继承当中的另外一个中间类
class Circle : virtual public Point {
private:
    int varC;
public:
    // 中间类的特征变量
    int radius;

    // 中间类的构造函数
    Circle(int x, int y, int radius, int varC);

    // 中间类对于draw方法的重载
    void draw();
};

// 菱形继承中的最下游子类, 同时继承自Circle, Line两个父类
class Multi : Circle, Line {
private:
    int varD;
public:
    // 下游子类的特征变量
    int center;

    // 下游子类的内部方法
    Multi(int x, int y, int radius, int length, int center, int varD);

    // 下游子类对于 draw 方法的 Override
    void draw();
};

// 用于测试虚函数的类
class DoublePoint : public Point {
private:
    int varE;
public:
    virtual void virMethod();

    // 重载re-take方法
    void retake();

    // 重载virtual的retake 方法
    void virRetake() override;

    // 和另一个类提供相同的方法
    virtual void sameMethod();

};

// 用于测试虚函数的类2
class TriplePoint : public Point {
private:
    int varF;
public:
    virtual void virMethod();

    // 和另一个类提供同名的方法
    void sameMethod();
};

// 用于测试虚函数的最子类
class SonPoint : public DoublePoint, public TriplePoint {
private:
    int varG;
public:
    virtual void virMethod();
};

void printWhich(Point * point) {
    point->virMethod();
}