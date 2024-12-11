#include <iostream>
#include <vector>

using namespace std;

//All enum valeus are actually integers represented by constants with identifiers
enum type{Circles,Squares,Shapes,Triangles};

//Super class
    //We could either make everything virtual manually or just make this class an abstract class

//making everything manually abstract but that means that we can't use this in dynamica binding at all without compiler complaining and giving up
/*
    class Shape{
    public:
        virtual void draw() = 0; //There is no real implementation yet - this makes this an abstract class in theory
        virtual type whatAmI() = 0;
        //Don't want to print show
        virtual string name() = 0;
    };
*/

//Giving semi-useless definitions in abstract class to appease the compiler
class Shape{
    public:
        virtual void draw() {cout << "I'm drawing a circle, lol" << endl;}; //There is no real implementation yet - this makes this an abstract class in theory
        virtual type whatAmI() {return Shapes;}
        //Don't want to print show
        virtual string name() {return "Shape";};
};

class Circle : public Shape{
    public:
        ~Circle() {cout << "I'm destroying a circle, lol" << endl;}
        //We can make sure that our base class is fully virtual by using the override keyword
        void draw() override {cout << "I'm drawing a circle" << endl;}
        //Used for enum
        type whatAmI() override {return Circles;}
        string name() const {return "Circle";}
};
class Triangle: public Shape{
    public:
        ~Triangle() {cout << "I'm destroying a triangle, lol" << endl;}
        void draw() {cout << "I'm drawing a triangle" << endl;}
        //Used for enum
        type whatAmI() {return Triangles;}
        string name() const {return "Triangle";}
};
class Square: public Shape{
    public:
        ~Square() {cout << "I'm destroying a square, lol" << endl;}
        void draw() {cout << "I'm drawing a square" << endl;}
        //Used for enum
        type whatAmI() {return Squares;}
        string name() const {return "Square";}
};

int main(){

    typedef vector<Shape*> Container;
    typedef Container::iterator iter;
    Container shapes;
    shapes.push_back(new Circle);
    shapes.push_back(new Square);
    shapes.push_back(new Triangle);

    for(iter i=shapes.begin(); i != shapes.end(); i++){
        (*i)->draw();
        if((*i)->whatAmI() == Squares){
            cout << "I am a square!" << endl;
        }
    }
}