#include <iostream>
#include <vector>

using namespace std;

//All enum valeus are actually integers represented by constants with identifiers
enum type{Circles,Squares,Shapes,Triangles};

//Giving semi-useless definitions in abstract class to appease the compiler
class Shape{
    protected:
        type t;
    public:
        Shape(type nt) : t(nt) {}
        virtual void draw() {cout << "I'm drawing a circle, lol" << endl;}; //There is no real implementation yet - this makes this an abstract class in theory
        virtual type whatAmI() {return t;}
        //Don't want to print show
        virtual string name() {return "Shape";};
        virtual ~Shape() = default();
};

class Circle : public Shape{
    public:
        Circle() : Shape(Circles) {}
        ~Circle() {cout << "I'm destroying a circle, lol" << endl;}
        //We can make sure that our base class is fully virtual by using the override keyword
        void draw() override {cout << "I'm drawing a circle" << endl;}
        //Used for enum
        type whatAmI() override {return Circles;}
        string name() const {return "Circle";}
        void specificCircleMethod() {cout << "Only circles can do this" << endl;}
};
class Triangle: public Shape{
    public:
        Triangle() : Shape(Triangles) {}
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

Shape* getCircle(bool circleornot){
    if(circleornot) return new Circle(Circles);
    else return new Shape(Shapes);
}

//Static cast (casts at complile-time)
    //Cannot handle anything done dynamically
//Dynamic cast (casts at run-time)
    //Allows us to look at the propeorties/context fof dynamic binding and take this into account when casting

int main(){
    Shape* genericShape = new Circle(Circles);
    //Static cast is a container, therefore defined a data type
    Circle* staticCircle = static_cast<Circle*>(genericShape);
    cout << "I'm using a static_cast: " << staticCircle->draw() << endl;
    staticCircle->specificCircleMethod();

    Shape* genShape2 = new Shape(Shapes);
    //Prints shape::draw as the static cast only recognises the Shape class here rn due to static binding
    Circle* unsafeCircle = static_cast<Circle*>(genShape2);
    cout << "I'm using an unsafe static_cast: " << unsafeCircle->draw() << endl;
    unsafeCircle->specificCircleMethod();

    //Dynamic casting section
    Shape* s3 = getCircle(true); //this'll be a circle
    Shape* s4 = getCircle(false); //this is just a shape

    if(Circle* validCircle = dynamic_cast<Circle*>(s3)){
        //If this dynamic cast was successful
        cout << "This is a dynamically casted circle" << endl;
        validCircle->draw();
        validCircle->specificCircleMethod();
    }
    else{
        cout << "This isn't a circle." << endl;
    }

    if(Circle* invalidCircle = dynamic_cast<Circle*>(s4)){
        //If this dynamic cast was successful somehow - shouldn't work
        cout << "This is a dynamically casted circle from invalid circle somehow" << endl;
        validCircle->draw();
    }
    else{
        cout << "As expected, the cast failed and this is still not a circle" << endl;
    }

}