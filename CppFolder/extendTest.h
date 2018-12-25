class Point {
    private:
        int varA;
    public:
        int x, y;
        
        Point(int x, int y); 
        Point(int x, int y, int varA);
        void draw();
};

class Line : virtual public Point {
    private:
        int varB;
    public:
        int length;
        
        Line(int x, int y, int length, int varB);
        void draw();
};

class Circle : virtual public Point {
    private:
        int varC;
    public:
        int radius;

        Circle(int x, int y, int radius, int varC);
        void draw();
};

class Multi : Circle, Line {
    private:
        int varD;
    public:
        int center;

        Multi(int x, int y, int radius, int length, int center, int varD);
        void draw();
};
