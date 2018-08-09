//home/tovantran/Ctest/AllTest.cpp ----------> 2014-06-15 by ./.tv  owner: tovantran
// ---------------------WAYS to CREATE OBJECT in C++
//E:\Ctest\CtorDtor.cpp
#include <iostream>
#include <stdlib.h>
using namespace std;

class Base {
	public:
		Base() { cout << "Base constuctor - created " << endl;}
		virtual ~Base() {cout << "Base destructor - destroyed " << endl;}
		void print() {cout << "Print" << endl;}
};
class Derived : public Base {
	public:
		Derived() {cout << "Derived constuctor created\n";}
		~Derived () {cout << "Derived destructor - destroyed\n";}
};		
int main(int argc, char *argv[])
{
	Derived d1;					//create in stack
	Derived(d2);
	d2.print();
	Derived p(d1); 				// implicit, explicit assignment D p = d1;
	Derived p1 = d1;  			// same as D p1(d);
	Base *p2 = &d1;
	Derived *ptr = new Derived(); //new create in heap
	Base *ptr1 = new Derived;     //Delete instant of derived class through a pointer
	delete ptr;				      // to a base class need a virtual Dtor virtual ~Base()
	delete ptr1;
	return 0;
}									
//Ways to create object in C++
//Derived obj; Derived obj1 = obj; Derived obj2(obj); 
//Derived *ptr = new Derived();  (create in heap with new)
//Base *ptr1 = new Derived;
//D d; Base *p = &d; (create in stack)
//    Derived cDerived(5); // explicit copy constructor see Borland c++ p.837
//    Derived cDerived = 5; // implicit assignment in an expression
//-----------------------------Virtual Function
// E:\Ctest\Virtual_Function.cpp
#include <iostream>
using namespace std;

class Sample {
	public:
		void f(int id){ cout << "Base Class f()" << endl; }
		virtual void vf(){ cout << "Base Class vf()" << endl; } //virtual function
		~Sample() { cout << "Base Dctor" << endl; }
		Sample() { cout << "Base Ctor" << endl; }
};

class Derived : public Sample {
	public:
		void f(int i){ cout << "Derived Class f()" << endl; }
		void vf(){ cout << "Derived Class vf()" << endl; }
		Derived() { cout << "Derived Ctor" << endl; }
		~Derived() { cout << "Derived Dctor" << endl; }
};

// void function()
int main()
{
	Derived d;			//create in stack
	Sample* p = &d;		// object point to &d 
	p->f(1);			// this calls base class since no vitual function 
	p->vf();		    // this calls derived class since virtual function
	// delete p;        // FAIL CREATE IN STACK no NEW therefore no DELETE
	return 0;
}
//Caveforprogramming in Polymorphism Sample *p dictate what function to be called in Sample
//but when call the object is pointing to &d
//p -> f(1) look into Sampple does have f(1)
//if both have f(int i) in Sample and Derived it will execute Derived if virtual function
//this function overriden happens parent and child same signature
//it is not function overloading.
//---------------------------------Pure Virtual Function
#include <iostream>
using namespace std;
class CPolygon {
	protected:
		int width, height;
	public:
		void set_values (int a, int b)
		{ width=a; height=b; }
		virtual int area (void) =0;
		void printarea(){ cout << this->area() << endl; }
};

class CRectangle: public CPolygon {
	public:
		int area (void)
		{ return (width * height); }
};

class CTriangle: public CPolygon {
	public:
		int area (void)
		{ return (width * height / 2); }
};

int main () {
	CRectangle rect;
	CTriangle trgl;
	CPolygon * ppoly1 = &rect;
	CPolygon * ppoly2 = &trgl;
	ppoly1->set_values (4,5);
	ppoly2->set_values (4,5);
	//  cout << ppoly1->area() << endl;
	//  cout << ppoly2->area() << endl;
	ppoly1->printarea();
	ppoly2->printarea();
	return 0;
}
//---------------------------------Virtual Desctructor
// Virtual destructors are useful when you can delete an instance of a 
// derived class through a pointer to base class:
#include <iostream>
using namespace std;
class Base 
{
	public:
		Base() { cout << "Base Ctor" << endl; }
		virtual ~Base() { cout << "Base Dctor" << endl; } //virtual Ctors
};

class Derived : public Base
{
	public:
		Derived() { cout << "Derived Ctor" << endl; }
		~Derived() { cout << "Derived Dctor" << endl; }
};
int main()
{
	Base *b = new Derived();		//create in the heap new need delete (Base from derived is upcasting) 
	// use b
	delete b; // Here's the problem !
	return 0;
}
// without virtual on ~Base()
// Base Ctor
// Derived Ctor
// Base Dctor

// with virtual on virtual ~Base()
// Base Ctor								
// Derived Ctor
// Derived Dctor
// Base Dctor
//Forgetting to make a destructor virtual is an
//insidious bug because it often doesn’t directly affect the behavior of
//your program, but it can quietly introduce a memory leak. Also, the
//fact that some destruction is occurring can further mask the
//problem. (Thinking of C++)
// -------------------------Virtual Base Class
//home/tovantran/Ctest/virtual_class1.cpp --> 2014-09-08 by ./.tv  owner: tovantran
//C h a p t e r 2 6 : M i s c e l l a n e o u s C + + T o p i c s 779 C++
#include <iostream>
using namespace std;
class base {
	public:
		int i;
};
// d1 inherits base as virtual.
class d1 : virtual public base {
	public:
		int j;
};
// d2 inherits base as virtual.
class d2 : virtual public base {
	public:
		int k;
};

/* d3 inherits both d1 and d2. However, now there is
   only one copy of base in d3. */
class d3 : public d1, public d2 {
	public:
		int m;
};
int main()
{
	d3 d;
	d.i = 10; // no longer ambiguous
	d.j = 20;
	d.k = 30;
	d.m = 40;
	cout << d.i << " "; // no longer ambiguous
	cout << d.j << " " << d.k << " ";
	cout << d.m;
	return 0;
}
//--------------------------Operator Overload by Value
// vectors: overloading operators example cplucplus.doc
//#include <iostream.h>
#include <iostream>
using namespace std;

class CVector {
	public:
		int x,y;
		CVector () {};          // empty constructor will not create because we have set constructor CVector::CVector review
		CVector (int,int);		//overload constructor with arguments
		CVector operator + (CVector);  //????
		CVector operator - (CVector);
};

CVector::CVector (int a, int b) {
	x = a;
	y = b;
}

CVector CVector::operator + (CVector param) {
	//  CVector param;
	CVector temp;
	temp.x = x + param.x;
	temp.y = y + param.y;
	return (temp);
}
CVector CVector::operator - (CVector param) {
	CVector temp;
	temp.x = x - param.x;
	temp.y = y - param.y;
	return (temp);
}
//CVector CVector::operator+

int main () {
	CVector a (3,1);
	CVector b (1,2);
	CVector c;          // no default constructor will fail here - define c April 11
	c = a.operator+ (b); // c = a + b is the same thing
	cout << c.x << "," << c.y <<endl;
	c = a - b;
	cout << c.x << "," << c.y <<endl;
	return 0;
}
//------------------Overload Operator by Reference
#include <iostream>
#include <stdlib.h>
using namespace std;

class CVector {
  public:
    int x,y;
    CVector () {};          // empty constructor will not create because we have set constructor CVector::CVector review
    CVector (int,int);    //overload constructor with arguments
    const CVector operator + (const CVector &);  //????
    CVector& operator - (const CVector &);
};

CVector::CVector (int a, int b) {
  x = a;
  y = b;
}

const CVector CVector::operator + (const CVector &param) {
  //  CVector param;       //USING CONST
  CVector temp;
  temp.x = x + param.x;
  temp.y = y + param.y;
  return temp;
}
CVector& CVector::operator - (const CVector &param) {
  static CVector temp;      //USING STATIC
  temp.x = x - param.x;
  temp.y = y - param.y;
  return temp;
}
//CVector CVector::operator+

int main () {
  CVector a (3,1);
  CVector b (1,2);
  CVector c;          // no default constructor will fail here - define c April 11
  c = a.operator+ (b); // c = a + b is the same thing
  cout << c.x << "," << c.y <<endl;
  c = a - b;
  cout << c.x << "," << c.y <<endl;
  return 0;
}
//----------------- VECTOR

// Access the elements of a vector through an iterator.
//B o r l a n d C + + B u i l d e r : T h e C o m p l e t e R e f e r e n c e
#include <iostream>
#include <vector>
#include <cctype>
using namespace std;
int main()
{
	vector<char> v(10); // create a vector of length 10
	vector<char>::iterator p; // create an iterator
	int i;
	// assign elements in vector a value
	p = v.begin();
	i = 0;
	while(p != v.end()) {
		*p = i + 'a';
		p++;
		i++;
	}
	// display contents of vector
	cout << "Original contents:\n";
	p = v.begin();
	while(p != v.end()) {
		cout << *p << " ";
		p++;
	}
	cout << "\n\n";
	// change contents of vector
	p = v.begin();
	while(p != v.end()) {
		*p = toupper(*p);
		p++;
	}
	// display contents of vector
	cout << "Modified Contents:\n";
	p = v.begin();
	while(p != v.end()) {
		cout << *p << " ";
		p++;
	}
	cout << endl;
	return 0;
}	
//---------------FUNCTION POINTER(CALL BACK)
#include <stdio.h>
using namespace std;
int test(int (*p)(int, int), int a, int b) {
  int result = (*p)(a, b);
  return result;
}
int sum(int a, int b) { return a + b; }
int mul(int a, int b) { return a*b; }
int div(int a, int b) { return a/b; }
int mod(int a, int b) { return a%b; }
int add(int a, int b) { return a+b; }
int main(int argc, char *argv[]) {
  int (*fp)(int, int);
  fp = &add;
  printf("Sum %d\n", (*fp)(2, 4));
  printf("Sum %d\n", fp(2, 4));
  printf("Sum1 %d\n", test(fp, 10, 5));
  return 0;
}

//-----------SMART POINTER
//home/tovantran/Ctest/SmartPointer2.cpp --> 2014-06-28 by ./.tv  owner: tovantran
//http://www.codeproject.com/Articles/541067/Cplusplus-Smart-Pointers
#include <iostream>
#include <memory>  // need this class for smart pointer
using namespace std;
class Test
{	
	public:
		Test(int a = 0 ) : m_a(a)
	{
	}
		~Test( )
		{			
			cout<<"Calling destructor"<<endl;
		}
	public:
		int m_a;
};

int main( )
{
	auto_ptr<Test>  p( new Test(5) ); 
	cout<<p->m_a<<endl;
	return 0;
}
//--------------SMART POINTER
//home/tovantran/Ctest/smartpointerQC.cpp --> 2014-06-22 by ./.tv  owner: tovantran
//http://www.codeproject.com/Articles/15351/Implementing-a-simple-smart-pointer-in-c
#include <cstdlib>
#include <iostream>
#include <stdio.h>
class Person
{
	int age;
	const char* pName;

	public:
	Person(): pName(0),age(0)
	{
	}
	Person(const char* pName, int age): pName(pName), age(age)
	{
	}
	~Person()
	{
	}

	void Display()
	{
		printf("Name = %s Age = %d \n", pName, age);
	}
	void Shout()
	{
		printf("Ooooooooooooooooo");
	} 
};
template <class T>
class SP
{
	private:
		T*    pData; // pointer to person class
	public:
		SP(T* pValue) : pData(pValue)
	{
	}
		~SP()
		{
			// pointer no longer requried
			delete pData;
		}
		T& operator* ()
		{
			return *pData;
		}

		T* operator-> ()
		{    
			return pData;
		}
};
int  main(int argc, char (argv[]))
{
	SP<Person> p(new Person("Scott", 25));
	p->Display();
	// Dont need to delete Person pointer..
	return 0;
}

//-------------TEMPLATE STACK
#include <iostream>
using namespace std;
template<class T>
class Stack {
	T *data;			//private no need to define private
	int length;
	int ptr;
public:
	Stack(int);
	void push(T);
	T pop();
	T top() const;
	int size() const;
	~Stack();
};

template<class T>
Stack<T>::Stack(int stk_size) {
	data = new T[length = stk_size];
	ptr = 0;
	cout << "constructor" << endl;
}

template<class T>
void Stack<T>::push(T x) {
	if (ptr < length)
		data[ptr++] = x;
	else
		throw "overflow";
}

template<class T>
T Stack<T>::pop() {
	if (ptr > 0)
		return data[--ptr];
	else
		throw "underflow";
}

template<class T>
T Stack<T>::top() const {
	if (ptr > 0)
		return data[ptr-1];
	else
		throw "underflow";
}

template<class T>
int Stack<T>::size() const {
	return ptr;
}

template<class T>
Stack<T>::~Stack() {
	delete [] data;
	cout << "destructor" << endl;
}
//tinstack.cpp: Test StackOfInt
#include "intstack.h"
#include <iostream>
#include <stdio.h>
using namespace std;
int main() {
	const int N = 5;
	Stack<float> stk(N);
	cout << " Class Template" << endl;
	cout << "push" <<' ';
	for (int i = 0; i < N; ++i) {
		stk.push(i);
		cout << i << ' ';
	}	
	putchar('\n');
	cout << " pop" <<' ';
	while (stk.size() > 0)
		cout << stk.pop() << ' ';
	cout << endl;
}
//----------------------/home/tovantran/Ctest/May11Stack.cpp (Needham)
//Youtube video Needham class template
#include <iostream>
using namespace std;

template <typename T, int MAX>
class Stack
{
	int m_top;
	T m_data[MAX];
public:
	Stack() : m_top(-1) {} /*m_top(0)*/
	~Stack(){}
	void push(T value)
	{
		if (m_top >= MAX -1)
			throw "overflow";
		m_data[++m_top] = value;   /*++m_top increase first */
	}
	void pop() 
	{
		if (empty())
			throw "empty";
		--m_top;
	}
	T top()
	{
		return m_data[m_top];
	}
	bool empty()
	{
		return m_top < 0; /*m_top == 0*/
	}
};

int main()
{
	Stack<int, 5> s;
	s.push(1);
	s.push(2);
	s.push(3);
	s.push(4);
	s.push(5);
	while (!s.empty())
	{
		cout << s.top() << endl;
		s.pop();
	}
}

//---------------COPY CTOR DEFINED TO RELEASE MEMORY
//Borlandc p.633
//http://www.tutorialspoint.com/cplusplus/cpp_copy_constructor.htm
//E:\Ctest\CopyCtor1.cpp
#include <iostream>
using namespace std;
class Line
{
	public:
		int getLength( void );
		Line( int len );             // simple constructor
		Line( const Line &obj);      // copy constructor
		~Line();                     // destructor
	private:
		int *ptr;
};
// Member functions definitions including constructor
Line::Line(int len)
{
	cout << "Normal constructor allocating ptr" << endl;
	// allocate memory for the pointer;
	ptr = new int;
	*ptr = len;
}
Line::Line(const Line &obj)
{
	cout << "Copy constructor allocating ptr." << endl;
	ptr = new int;
	*ptr = *obj.ptr; // copy the value
}
Line::~Line(void)
{
	cout << "Freeing memory!" << endl;
	delete ptr;
}
int Line::getLength( void )
{
	return *ptr;
}
void display(Line obj)				//copy Ctor
{
	cout << "Length of line : " << obj.getLength() <<endl;
}
// Main function for the program
int main( )
{
	// Line obj(1);  // create object
	Line line(10);   
	display(line);	//copy ctors
	//    Line line2 = line; //also copy ctors
	return 0;
}
//--------------------------Reference int &b = a
// /E:\Ctest\CopyCtor3_0.cpp 8:11 AM 6/22/2014
// http://en.wikipedia.org/wiki/Copy_constructor
#include <iostream>
using namespace std;

class Person {
	public:
		int age;

		explicit Person(int a) 
			: age(a)
		{
		}
		Person ( Person &p) : age(p.age)
	{
		// this->age = p.age;
		cout << "Copy ctors" << endl;
	}
};

int main() 
{
	Person timmy(10);
	Person sally(15);

	Person &timmy_clone = timmy;	// reference clone to timmy so timmy changes clone changes as well
	// Person timmy_clone = timmy;    // 2 different object timmy changes clone won't changes
	std::cout << timmy.age << " " << sally.age << " " << timmy_clone.age << std::endl;
	timmy.age = 23;
	std::cout << timmy.age << " " << sally.age << " " << timmy_clone.age << std::endl;

	int a = 2;
	int *b = &a;			//b pointer to address of a 
	cout << *b << endl;
	a = 3;
	// b =a ;
	cout << *b << endl;

	int c = 4;
	int &d = c;				//d reference to C d is alias of C defined int &d
	cout << d << endl;		// it is not address as in C *p = &d (Cplusplus)
	c = 5;
	cout << d << endl;
	cout << &d << endl;		//address of d
	cout << *&d << endl;	//pointer address of d which is content qualcomm3.c

	int e = 6;
	int f = e;
	cout << f << endl;     
	e = 7;    				// e change
	cout << f << endl;      // f won't change they assign operator different object

	//int &d = e;          //You can not change the address of an object once it has been assign by the compiler.
}
// http://www.daniweb.com/software-development/cpp/threads/281730/2-variable-with-the-same-address
// As expected, timmy has been copied to the new object, timmy_clone. While timmy's age was changed, 
// timmy_clone's age remained the same. This is because they are totally different objects.
// The compiler has generated a copy constructor for us, and it could be written like this:
// Person(const Person& other) 
// : age(other.age) // calls the copy constructor of the age
// {
// ------------------------------PASS BY POINTER in C/C++ & BY REFERENCE IN C++ is ALIAS
// E:\Ctest\Pass_By_Address.cpp
// 3:10 PM 6/18/2014
#include <iostream>
using namespace std;
void foo(int *pValue)
{
	*pValue = 6;
}

int main()
{
	int nValue = 5;

	cout << "nValue = " << nValue << endl;
	foo(&nValue);
	cout << "nValue = " << nValue << endl;
	return 0;
}
//----by reference almost the same
// #include <iostream>
// using namespace std;
// void foo(int &pValue)
// {
// pValue = 6;
// }

// int main()
// {
// int nValue = 5;

// cout << "nValue = " << nValue << endl;
// foo(nValue);
// cout << "nValue = " << nValue << endl;
// return 0;
// }
// http://www.tutorialspoint.com/cplusplus/cpp_references.htm
// C++ References vs Pointers:
// References are often confused with pointers but three major differences between references and pointers are:
// -You cannot have NULL references. You must always be able to assume that a reference is 
// connected to a legitimate piece of storage.
// -Once a reference is initialized to an object, it cannot be changed to refer to another object. 
// -Pointers can be pointed to another object at any time.
// A reference must be initialized when it is created. Pointers can be initialized at any time.
//-------------------------------PURE VIRTUAL DESTRUCTOR
// Pure virtual destructors
// While pure virtual destructors are legal in Standard C++, there is
// an added constraint when using them: you must provide a function
// body for the pure virtual destructor. This seems counterintuitive;
// how can a virtual function be “pure” if it needs a function body?
// But if you keep in mind that constructors and destructors are
// special operations it makes more sense, especially if you remember
// that all destructors in a class hierarchy are always called. If you
// could leave off the definition for a pure virtual destructor, what
// function body would be called during destruction? Thus, it’s
// absolutely necessary that the compiler and linker enforce the
// existence of a function body for a pure virtual destructor.
// If it’s pure, but it has to have a function body, what’s the value of
// it? The only difference you’ll see between the pure and non-pure
// virtual destructor is that the pure virtual destructor does cause the
// base class to be abstract, so you cannot create an object of the base
// 702 Thinking in C++ www.BruceEckel.com
// class (although this would also be true if any other member
// function of the base class were pure virtual).
// Things are a bit confusing, however, when you inherit a class from
// one that contains a pure virtual destructor. Unlike every other pure
// virtual function, you are not required to provide a definition of a
// pure virtual destructor in the derived class. The fact that the
// following compiles and links is the proof:
//: C15:UnAbstract.cpp
// Pure virtual destructors
// seem to behave strangely
/*
   class AbstractBase {
   public:
   virtual ~AbstractBase() = 0;
   };
   AbstractBase::~AbstractBase() {}
   class Derived : public AbstractBase {};
// No overriding of destructor necessary?
int main() { Derived d; } ///:~
 */
// Normally, a pure virtual function in a base class would cause the
// derived class to be abstract unless it (and all other pure virtual
// functions) is given a definition. But here, this seems not to be the
// case. However, remember that the compiler automatically creates a
// destructor definition for every class if you don’t create one. That’s
// what’s happening here – the base class destructor is being quietly
// overridden, and thus the definition is being provided by the
// compiler and Derived is not actually abstract.
// This brings up an interesting question: What is the point of a pure
// virtual destructor? Unlike an ordinary pure virtual function, you
// must give it a function body. In a derived class, you aren’t forced to
// provide a definition since the compiler synthesizes the destructor
// for you. So what’s the difference between a regular virtual
// destructor and a pure virtual destructor?
// The only distinction occurs when you have a class that only has a
// single pure virtual function: the destructor. In this case, the only
// effect of the purity of the destructor is to prevent the instantiation
// of the base class. If there were any other pure virtual functions,
// they would prevent the instantiation of the base class, but if there
// are no others, then the pure virtual destructor will do it. So, while
// the addition of a virtual destructor is essential, whether it’s pure or
// not isn’t so important.
// When you run the following example, you can see that the pure
// virtual function body is called after the derived class version, just
// as with any other destructor:
//: C15:PureVirtualDestructors.cpp
// Pure virtual destructors
// require a function body
#include <iostream>
using namespace std;
class Pet {
	public:
		virtual ~Pet() = 0;
};
Pet::~Pet() {
	cout << "~Pet()" << endl;
}
class Dog : public Pet {
	public:
		~Dog() {
			cout << "~Dog()" << endl;
		}
};
int main() {
	Pet* p = new Dog; // Upcast
	delete p; // Virtual destructor call
} 
// -------------------------CASTING
//home/tovantran/Ctest/dynamic_cast1.cpp ----------> 2014-06-15 by ./.tv  owner: tovantran
//: C15:DynamicCast.cpp Thinking of C
#include <iostream>
using namespace std;
class Pet { public: virtual ~Pet(){}};
class Dog : public Pet {};
class Cat : public Pet {};
int main() {
	Pet *b = new Cat; // Upcast to pointer of base class Cat
	Pet *bb = new Dog;
	// Try to cast it to Dog*:
	Dog  *d1 = dynamic_cast<Dog*>(bb);  //Downcast but b is Cat 
	Dog *d11 = (Dog *)bb;               //Cast 
	// Try to cast it to Cat*:
	Cat *d2 = dynamic_cast<Cat*>(b);
	Cat *d22 = (Cat *)b;
	cout << "d1 = " << (long)d1 << endl;  //Zero 
	cout << "d2 = " << (long)d2 << endl;

} ///:~
//When you use dynamic_cast, you must be working with a true
//polymorphic hierarchy – one with virtual functions
//home/tovantran/Ctest/Casting2.cpp ----------> 2014-06-15 by ./.tv  owner: tovantran
#include <string>
#include <iostream>
using namespace std;

class Parent {
	public:
		void sleep() {
		}
		virtual ~Parent(){}
};

class Child: public Parent {
	private:
		std::string classes[10];
	public:
		void gotoSchool(){}
};

int main( ) 
{ 
	Parent *pParent = new Child;
	//	Parent *pParent = new Parent;
	Parent *pChild = new Child;

	Child *p1 = (Child *)pParent;	// #1   Downcasting is not safe explicit type cast require
	Child *p11 = dynamic_cast<Child *>(pParent);    //need virtual void sleep() or virtual ~Parent
	Parent *p2 = (Parent *) pChild; // #2    Upcasting no need to cast because it is safe
	Parent *p22 = dynamic_cast<Parent *>(pChild);
	cout << "p11 = " << (long)p11 << endl;  //Zero 
	cout << "p22 = " << (long)p22 << endl;
	return 0; 
}
//Casting2.cpp:23:44: error: cannot dynamic_cast ‘pParent’ (of type ‘class Parent*’) to type ‘class Child*’ (source type is not polymorphic) need virtual void sleep()) or virtual ~Parent(){})
//--------------------------- const_cast
//-------------------- PRINT CAST TYPE
//home/tovantran/Ctest/Cast4.cpp --> 2014-06-25 by ./.tv  owner: tovantran
#include <iostream>
#include <typeinfo>  // need typeinfo
using namespace std;

int main(void)
{
	int a1 = 40;
	const volatile int* b1 = &a1;
	cout << "typeid of b1 " << typeid(b1).name() << '\n';
	int* c1 = const_cast <int *> (b1);
	cout << "typeid of c1 " << typeid(c1).name() << '\n';
	const double *c3 = 0;
	cout << "typeid of c1 " << typeid(c3).name() << '\n';

	return 0;
}
// ------------------------ C cast
// /E:\Ctest\Cast5.cpp 10:13 AM 6/25/2014
#include <iostream>
using namespace std;

int main(void)
{
	int a1 = 66;          // interger
	const int* b1 = &a1;
	cout << *b1 << endl;
	char* c1 = (char *)b1;  //become character
	cout << *c1 << endl;
	*c1 = 'A';
	cout << *c1 << endl;
	int c2 = 67;			// integer
	cout << *&c2 << endl;
	// char c3 = const_cast<char *>(c2);
	char c3 = (char )(c2);   // become character
	cout << c3 << endl;
	return 0;
}
// 66
// B
// A
// 67
//--------------------------   Default constructor when defined ctors or copy ctors
// E:\Ctest\TestCode2.cpp
// 9:59 PM 6/17/2014
#include <iostream>
using namespace std;
class base 
{ 
	public: int i;
		base(){}
		//base(int num = 7){i=num;}; 
		base(int num){i=num;}; 
		// base(){}; //why???? default ctors here....
}; 
class derived: public base 
{ 
	public: 
		derived(int num):base(num) {} ; 
}; 
int main() 
{ 
	base b; //this need default A(){};
	derived d(11); 
	cout << "i " << d.i << endl;
}

// TestCode2.cpp:14: error: no matching function for call to 'base::base()'
//if remove default ctors in base
//----------------------------- FUNCTION OVERRIDE
// E:\Ctest\Function_Override1.cpp
// 6:16 AM 6/18/2014
#include <iostream>
using namespace std;

class foo
{
	public:
		int x;
		foo(){}
		foo(int i){ x = i;}
		~foo(){}
		void a(int i) { cout << "foo:a(int) "<< x << endl; }
		// virtual void a(double);
};

class bar : public foo 
{
	public:
		bar(){};
		~bar(){};
		void a(int i);
		// using foo::a;
};
int main() 
{
	// double i = 0;
	foo c(100);
	// bar b;
	c.a(1);
	return 0;
}
//Look error: undefined reference to `foo::a(int)' because no function foo:a(int)
// Not to confuse
//void a(int i); //prototype
//void a(int i){} //function defined
//------------------------FUNCTION OVERRIDE need virtual function to work properly
//home/tovantran/Ctest/Function_Override.cpp --> 2014-06-18 by ./.tv  owner: tovantran

#include <iostream>
using std::cout;
using std::endl;

class A { 
	int a; 
	public: 
	A() { a = 10; } 
	virtual int show() { cout << "A::a " << a << endl; return 0;} 
}; 
class B: public A { 
	int b; 
	public: B() { b = 20; } 
		int show() 
		{ cout <<"B::b "<< b << endl; return 1;} 
}; 

int main() { 
	A ob1; 
	B ob2; 
	ob2.show(); // calls derived class show() function. o/p is 20 
	ob1.show();
	A *pA = &ob2;
	cout << pA->show() << endl;
	return 0; 
} 
//Function override 
//A *pA = &ob2;  //Caveprogramming variable *pA dictate by A by action call object is &ob2
//since no virtual function int show() it will display the base A::a instead of B::b
// with virtual int show() it will work properly
//pA->show() display on &ob2 object
// int show();    // no virtual output
//A *pA = &ob2;  //display A
//B::b 20
//A::a 10
//A::a 10
//0
//B *pA = &ob2; //display B
//B::b 20
//A::a 10
//B::b 20
//1
// int virtual show(); //with virtual output
//A *pA = &ob2; //display B on &ob2 regardless what A *pa or B*pa
//B::b 20
//A::a 10
//B::b 20
//1
//B *pA = &ob2;
//B::b 20
//A::a 10
//B::b 20
//1
// ------------------------LINKK LIST RECURSIVE
//linknode_5_0.cpp
#include <stdio.h>
#include <iostream>

using namespace std;

struct node                                                
{                                                               
	int data;               // will store information
	node *next;             // the reference to the next node
}; 
node *head, *ptr, *temp; 

void Reverse(struct node *p)
{
	//	cout << "head = "<< h << endl;
	if (p->next == NULL){
		head = p;	// head now at the end
		//cout << "node = " << p << " data = " << p->data << " p->next = " << p->next << endl;
		return;
	}
	Reverse(p->next);  // push to stack many times pop to stack from stack to get p stack has return function pointer + p
	temp = p->next;    // p is 603070 before reversing has p->next point to last 603090 which is head now assign temp = p->next
	temp->next = p;    // now temp is head (last before) now temp->next = p which is 603070 so head -> next now is 603070
	p->next = NULL;		// head has to keep the same do not modify head. Assign p->next = NULL last node also for above p->next == NULL to return
}
int main()
{
	head = new node;
	head ->data = 1;
	head ->next = 0; //first of linked list it is initialized to0 but explicit to clearify

	ptr = head;   //temporarily  now ptr is the same as head 

	ptr->next = new node;
	ptr  = ptr->next;     // this first before write data otherwise it will write over head  move head to a new create node
	ptr->data = 2;

	ptr->next = new node;
	ptr  = ptr->next;	// assign ptr to new node just create
	ptr->data = 3;

	ptr->next = new node;
	ptr  = ptr->next;
	ptr->data = 4;;

	ptr->next = 0; //end of linked list it is initialized to 0 but explicit to clearify

	ptr = head; // insert the lst node	
	while(ptr->next !=NULL) // go to the last node
		ptr = ptr->next;//tranfer the address of 'temp1->next' to 'temp1'
	temp = new node;
	temp -> data = 1234;
	temp-> next = 0;
	ptr->next = temp;                  // 'temp' node will be the last node

	//	temp = new node; //delete front of head
	//	temp = head;
	//	head = temp->next; //head->next; 
	//	delete temp; //free(temp) 


	node *tmp = head->next; //delete first
	//	head = head ->next;
	delete head;  // delete head then head = head->next is gone 
	head = tmp;

	node *tmp1 = head;      //delete first 
	delete head;
	head = tmp1->next;

	temp = new node; //insert front of head
	temp -> next = head;
	temp -> data = 12;
	head = temp;


	ptr = head;
	while (ptr ->next != 0){
		cout << ptr->data << endl;
		ptr = ptr ->next;		
	}	
	cout << ptr->data << endl; //print the last node if ptr ->next = 0

	Reverse(head);
	cout << "last" << endl;
	ptr = head;
	while (ptr ->next != 0){
		cout << ptr->data << endl;
		ptr = ptr ->next;		
	}	
	cout << ptr->data << endl; //print the last node if ptr ->next = 0
	return 0;
}
//-------------------------LINKED LIST REVERSED USING RECURSIVE 
#include <stdio.h>
#include <malloc.h>

//youtube mycodeschool
struct Node{
	int data;
	struct Node *next;
};
/*struct Node *ptr; */
void ReversePrint(struct Node *p)
{
	if (p == NULL)
		return;
	ReversePrint(p->next);
	printf("%d ", p->data);
}
void Print(struct Node *p)
{
	while (p->next != NULL) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("%d ", p->data);
}
struct Node *Insert(struct Node *head, int data)
{
	struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
	temp ->data = data;
	temp -> next = NULL;
	if (head == NULL)
		head = temp;
	else
	{
		struct Node *temp1 = head;   
		while (temp1->next != NULL){
			temp1 = temp1->next;
		}
		temp1 -> next = temp;
	}
	return head;
}
int main()
{
	struct Node *head = NULL;  //head move
	head = Insert(head, 2);
	head = Insert(head, 4);
	head = Insert(head, 6);
	head = Insert(head, 5);
	Print(head);
	printf("\n");
	ReversePrint(head);
	printf("\n");
}
//---------------------------------reverselinklist
//home/tovantran/Ctest/linklistrecursive.c --> 2014-06-15  by ./.tv

#include <stdio.h>
#include <malloc.h>

//youtube mycodeschool
struct Node{
	int data;
	struct Node *next;
};
/*struct Node *ptr; */
void ReversePrint(struct Node *p)
{
	if (p == NULL)
		return;
	ReversePrint(p->next);
	printf("%d ", p->data);
}
void Print(struct Node *p)
{
	while (p->next != NULL) {
		printf("%d ", p->data);
		p = p->next;
	}
	printf("%d ", p->data);
}
struct Node *Insert(struct Node *head, int data)
{
	struct Node *temp = (struct Node *)malloc(sizeof(struct Node));
	temp ->data = data;
	temp -> next = NULL;
	if (head == NULL)
		head = temp;
	else
	{
		struct Node *temp1 = head;   
		while (temp1->next != NULL){
			temp1 = temp1->next;
		}
		temp1 -> next = temp;
	}
	return head;
}
int main()
{
	struct Node *head = NULL;  //head move
	head = Insert(head, 2);
	head = Insert(head, 4);
	head = Insert(head, 6);
	head = Insert(head, 5);
	Print(head);
	printf("\n");
	ReversePrint(head);
	printf("\n");
}
//----------------------------------SORT
/*
 *  Sort.c
 */

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

void swap(int* A, int i, int j){
	int temp;
	temp = A[i];
	A[i] = A[j];
	A[j] = temp;
}

void BubbleSort(int* A, int n){
	int i, j;
	for(j=n-1; j>0; j--){
		for(i=1; i<=j; i++){
			if( A[i]<A[i-1] ) swap(A, i, i-1);
		}
	}
}

void SelectionSort(int* A, int n){
	int i, j, imax;
	for(j=n-1; j>0; j--){
		imax = 0;
		for(i=1; i<=j; i++) if( A[imax]<A[i] ) imax = i;
		swap(A, imax, j);
	}
}

void InsertionSort(int* A, int n){
	int i, j, temp;
	for(j=1; j<n; j++){
		temp = A[j];
		i = j-1;
		while( i>=0 && temp<A[i] ){
			A[i+1] = A[i];
			i--;
		}
		A[i+1] = temp;
	}
}

void Merge(int* A, int p, int q, int r){
	int i, j, k, n1=q-p+1, n2=r-q;
	int* L = calloc(n1, sizeof(int));
	int* R = calloc(n2, sizeof(int));
	assert(L!=NULL && R!=NULL);

	for(i=0; i<n1; i++) L[i] = A[p+i];
	for(j=0; j<n2; j++) R[j] = A[q+j+1];
	i = 0; j = 0;
	for(k=p; k<=r; k++){
		if( i<n1 && j<n2 ){
			if( L[i]<R[j] ){ A[k] = L[i]; i++;}
			else{ A[k] = R[j]; j++;}
		}
		else if( i<n1 ){ A[k] = L[i]; i++;}
		else{ /* j<n2 */ A[k] = R[j]; j++;}
	}
	free(L);
	free(R);
}

void MergeSort(int* A, int p, int r){
	int q;
	if( p<r ){
		q = (p+r)/2;
		MergeSort(A, p, q);
		MergeSort(A, q+1, r);
		Merge(A, p, q, r);
	}
}

int Partition(int* A, int p, int r){
	int i, j, x;
	x = A[r];
	i = p-1;
	for(j=p; j<r; j++){
		if( A[j]<=x ){
			i++;
			swap(A, i, j);
		}
	}
	swap(A, i+1, r);
	return(i+1);
}

void QuickSort(int* A, int p, int r){
	int q;
	if( p<r ){
		q = Partition(A, p, r);
		QuickSort(A, p, q-1);
		QuickSort(A, q+1, r);
	}
}

void CountingSort(int* A, int* B, int n, int k){
	int i, j;
	int* C = calloc(k+1, sizeof(int));
	assert(C!=NULL);
	for(i=0; i<=k; i++) C[i] = 0;
	for(j=0; j<n; j++) C[A[j]] = C[A[j]]+1;
	for(i=1; i<=k; i++) C[i] = C[i] + C[i-1];
	for(j=n-1; j>=0; j--){
		B[C[A[j]]-1] = A[j];
		C[A[j]]--;
	}
	free(C);
}

int main(int argc, char** argv){
	int i, n=9;
	int A[] = {9,5,3,6,7,4,8,1,2};
	int B[9];

	for(i=0; i<n; i++) printf("%d ", A[i]);
	printf("\n");

	QuickSort(A, 0, 8);

	for(i=0; i<n; i++) printf("%d ", A[i]);
	printf("\n");


	return(EXIT_SUCCESS);
}
//---------------------------------bash gedit script to call python
#!/bin/sh
echo "Append this file to " $GEDIT_CURRENT_DOCUMENT_PATH
file_name=$GEDIT_CURRENT_DOCUMENT_NAME
echo $file_name
python addtext.py $file_name
//----------------------------------addtext.py
#! /usr/bin/python -tt
#//home/tovantran/Ctest/addtext.py --> 2014-07-01 by ./.tv  owner: tovantran

import sys

def Cat(filename): 
	fa = open('AllTest.cpp', 'a')  
	f = open(filename,'r')
#  adddivider = '//---------------------------------filename\n'
#  fa.write(adddivider)
	text = f.read() 
	fa.write('----------------------------------' + filename + '\n'+ text) 
fa.close()

	def main():
#	print "Hello World"
#  print sys.argv
		Cat(sys.argv[1])

#This is the standard boilerplace that calls the main() function.
	if __name__ == '__main__':
main()
	//----------------------------------makedocs.sh
#!/bin/bash
#//home/tovantran/Ctest/makedocs.sh --> 2014-07-01 by ./.tv  owner: tovantran

	echo "the $1 eats a $2 every time there is a $3"
	echo "bye:-)"
	echo $1
	name=$(echo $1 | sed 's/\.[^.]*$//')
	echo $name
	enscript -2rc --borders --pretty -p$name.ps $1
	ps2pdf $name.ps $name.pdf
	//----------------------------------wordcount.py
#! /usr/bin/python -tt
#//home/tovantran/Ctest/wordcount.py --> 2014-07-01 by ./.tv  owner: tovantran

	import sys

	def Cat(filename): 
	f = open(filename, 'rU')  
	text = f.read()
	print text
	f.close()
	text1 = text.split()
	print text1
	wordcount = 0;
	charcount = 0; 
	linecount = 0; 
	for count in text1 : print count, '-', len(count)
	for count in text1 : 
charcount = charcount + len(count)
	wordcount += 1
	print "Total characters in", filename," : ", charcount
	print "Total words in", filename," : ", wordcount
	def main():
#	print "Hello World"
#	print sys.argv
		Cat(sys.argv[1])

#This is the standard boilerplace that calls the main() function.
	if __name__ == '__main__':
main()
	//----------------------------------hello1.py
#! /usr/bin/python -tt
#//home/tovantran/Ctest/hello1.py --> 2014-07-01 by ./.tv  owner: tovantran

	import sys

	def Hello(name):
		if name == 'Alice' or name == 'Nick':
		name = name + '???'
		else:
		print 'Else'
#		DoesNotExist(name)
		name = name + '!!!!'
		print 'Hello', name

		def main():
			print "Hello World"
	print sys.argv
	  Hello(sys.argv[1])

#This is the standard boilerplace that calls the main() function.
	  if __name__ == '__main__':
main()

	//----------------------------------vector2.cpp
	//home/tovantran/Ctest/vector2.cpp --> 2014-06-28 by ./.tv  owner: tovantran
	// Access the elements of a vector through an iterator.
	//B o r l a n d C + + B u i l d e r : T h e C o m p l e t e R e f e r e n c e
#include <iostream>
#include <vector>
#include <cctype>
	using namespace std;
int main()
{
	vector<char> v(10); // create a vector of length 10
	vector<char>::iterator p; // create an iterator
	int i;
	// assign elements in vector a value
	p = v.begin();
	i = 0;
	while(p != v.end()) {
		*p = i + 'a';
		p++;
		i++;
	}
	// display contents of vector
	cout << "Original contents:\n";
	p = v.begin();
	while(p != v.end()) {
		cout << *p << " ";
		p++;
	}
	cout << "\n\n";
	// change contents of vector
	p = v.begin();
	while(p != v.end()) {
		*p = toupper(*p);
		p++;
	}
	// display contents of vector
	cout << "Modified Contents:\n";
	p = v.begin();
	while(p != v.end()) {
		cout << *p << " ";
		p++;
	}
	cout << endl;
	return 0;
}

//----------------------------------CRectangle2.cpp
//home/tovantran/Ctest/CRectangle2.cpp --> 2014-07-06 by ./.tv  owner: tovantran
// pointer to classes example
#include <iostream>
using namespace std;

class CRectangle {
	int width, height;
	public:
	//    CRectangle(){};  //default ctors
	CRectangle(int a =11, int b=22): width(a), height(b){};
	void set_values (int, int);
	int area (void) {return (width * height);}
};

void CRectangle::set_values (int a, int b) {
	width = a;
	height = b;
}

int main () {
	CRectangle a(1,2), *b, *c;
	CRectangle * d2 = new CRectangle[2]; //Ctors has no parameter = default ctors or need initialize default int a = 11
	d2[10].set_values(200,2);
	d2->set_values(1,1);
	CRectangle *d3 = new CRectangle(1,1);
	//  CRectangle * d = new CRectangle(1,2); //Ctors with 2 parameters
	//  CRectangle a(new B(1,2), new C(1,2));
	//  CRectangle d(new CRectangle, new CRectangle);
	//  CRectangle * d = new CRectangle(1,2);
	//   CRectangle *d(new CRectangle(1,2), new CRectangle(2,3));
	//  CRectangle *d[(new CRectangle(1,4),new CRectangle(1,4)]);
	CRectangle d[] = {CRectangle(1,2), CRectangle(2, 3), CRectangle(44, 1)}; //stack
	CRectangle *d1 = ({new CRectangle(1,2), new CRectangle(2, 3), new CRectangle(488, 1);});
	CRectangle *d11[] = {new CRectangle(1,2), new CRectangle(2, 3), new CRectangle(488, 1)};
	//    CRectangle *d1 = new CRectangle[2];  
	//  CRectangle *d3[1] = new CRectangle(2,3);
	b= new CRectangle(1,2);
	c= &a;
	a.set_values (1,2);
	b->set_values (3,4);

	//  d->set_values (5,6);  //Ctor does initialize
	//  d[1].set_values (7,8);
	//  d[2].set_values (8,8);
	cout << "a area: " << a.area() << endl;
	cout << "*b area: " << b->area() << endl;
	cout << "*c area: " << c->area() << endl;
	cout << "d[0] area: " << d[0].area() << endl;
	cout << "d[1] area: " << d[1].area() << endl;
	cout << "d[2] area: " << d[2].area() << endl;
	cout << "d[2] area: " << d2[0].area() << endl;
	cout << "d[2] area: " << d3->area() << endl;
	cout << "d[2] area: " << d1[0].area() << endl;
	cout << "d[2] area: " << d11[1]->area() << endl;
	return 0;
}
//---------------------------------SmartPointer.cpp
//home/tovantran/Ctest/SmartPointer.cpp --> 2014-12-12 by ./.tv  owner: tovantran
#include <stdio.h>
#include <iostream>
using namespace std;
#define char const char
class FriendClass; //prototype declaration
class Test{
	int a;
	public: 
	void showtest(int c) { a = c; cout << "from other object class Test" <<   c  << endl; }
	void showtest1(){ cout << a << endl; }

};
//class Test;  //prototype declaration
class Person
{
	int age;
	char * pName;
	protected:
	int pro;
	void setPro(int x) { pro =x; } //functionx.com/java/Lesson09.htm
	friend class FriendClass;
	friend void FriendFunction(Person t) { cout << t.age << endl;} 
	public:
	//       friend void FriendFunction(Person t) { cout << t.age << endl;} could be in private or publoic
	Test a;
	Person(): pName(0),age(0){cout <<"Person constructor" << endl;}        
	Person(char * pName, int age): pName(pName), age(age){cout <<"Argument constructor" << endl;}
	~Person(){}     
	void Person1(char *pName, int age){ this->pName = pName; this->age = age;}   //& T want to change *q  if Person T a new object T.age = 12 won't effect q
	//void Person1(Person &T){ T.age = 11; pName="Dumb";}
	void Display()
	{
		printf("Name = %s Age = %d \n", pName, age);
	}
	void Shout()
	{
		printf("Ooooooooooooooooo");
	} 
};
class FriendClass
{
	int friendvalue;
	public:
	int subtractionfrom(Person test, int x)
	{
		//	Person test;
		test.age -= x;
		return test.age;
	}
	int subtractionforgood(Person &test, int x)
	{
		test.age -= x;
		return test.age;
	}
};
class Derived : public Person {
	int myage;
	public:
	int myage1;
	void setmyage(int a) { myage =a; } 
	void showmyage() { cout << "myage: " << myage << endl; }
	void showmyparent() { setPro(120); cout << "parent age " << pro << endl;}
	Derived(int i){}
	Derived(){}
};
int main()
{
	//Person d("test",1);
	Derived d (1);
	d.setmyage(5);
	d.showmyage();
	d.Person1("derived", 20);
	d.myage1 =2; //private pass
	//d.myage = 2; //fail private but you can setmyage in side the class
	d.setmyage(2);
	//   d.pro;//protected
	d.showmyage(); // to change pro it is ok
	d.showmyparent();  // private cannot access from derived class
	d.Display();
	//   Person *pPerson  = const_cast<Person*>(new Person("Scott", 25)); // char f(a); same as cha f = a;
	Person *pPerson(new Person("Scott", 25));
	Person *q = new Person;
	Person testObject;

	testObject.a.showtest(111111);
	testObject.a.showtest1();
	q->Person1("stupid", 11);  // need pointer
	//q->Person1(*q); //using function pass object pointer (the same)
	//  q->a.showtest(222);
	//    Person *t = p  
	//    q->Display();
	pPerson->Display(); 
	q->Display();
	Person w("Me", 22);  //using constructor

	//    w.Person1(w); //using function pass object (the same)
	w.Display();

	FriendClass var;

	cout << "Added to friend class: " << var.subtractionfrom(w, 4) << endl; 
	FriendFunction(w);
	var.subtractionforgood(w,4); 
	FriendFunction(w); 
	FriendClass varr;
	//    varr.friendvalue;   //private
	delete pPerson;
	return 0;
}
//----------------------------------PureVirtualFunction5.cpp
#include <iostream>
#include <string>
using namespace std;

class Cat {
	public:
		Cat(string name = "tom", string color = "black_and_white") : _name(name), _color(color) {}
		~Cat() {}
		void setName(string name) {_name = name;}
		string getName() {return _name;}
		void setColor(string color) {_color = color;}
		string getColor() {return _color;}
		void speak() {cout << "meow" << endl;}
	private:
		string _name;
		string _color;
};

int main()
{
	Cat cat1("morris","orange");    //Objects of automatic extent exist on stack.
	Cat *cat2pt = new Cat("felix","black");    /* Dynamically allocated objects exist on the heap. */
	Cat *cat3pt = new Cat;    //Calls default constructor

	cout << cat1.getName() << " is " << cat1.getColor() << endl;
	cout << cat2pt->getName() << " is " << cat2pt->getColor() << endl;
	cout << cat3pt->getName() << " is " << cat3pt->getColor() << endl;

	cat1.speak();
	cat2pt->speak();

	delete cat2pt;    //Always "delete" dynamically allocated objects!
	delete cat3pt;

	return 0;
} 
//----------------------------------PureVirtualFunction4.cpp
#include <iostream> 
#include <new> 
using namespace std; 

class Rectangle { 
	int width; 
	int height; 
	public: 
	Rectangle() {      //default ctors
		width = height = 0; 
		cout << "Constructing " << width << " by " << height << " rectangle.\n"; 
	} 

	Rectangle(int w, int h) { 
		width = w; 
		height = h; 
		cout << "Constructing " << width << " by " << height << " rectangle.\n"; 
	} 

	~Rectangle() {  
		cout << "Destructing " << width << " by " << height << " rectangle.\n"; 
	}  

	void set(int w, int h) { 
		width = w; 
		height = h; 
	} 

	int area() { 
		return width * height; 
	} 
}; 

int main() 
{ 
	Rectangle *p; 

	try { 
		p = new Rectangle [3]; 
	} catch (bad_alloc xa) { 
		cout << "Allocation Failure\n"; 
		return 1; 
	} 

	//----------------------------------bubblesort.cpp
	//home/tovantran/Ctest/bubblesort.cpp --> 2014-07-07 by ./.tv  owner: tovantran
	// Using the bubble sort to order an array from the C++ ground up book
#include <iostream>
#include <cstdlib>
	using namespace std;
	int main()
	{
		int nums[4]= {10, 12, 1, 0};
		int a, b, t;
		int size;
		size = 4; // number of elements to sort
		// Give the array some random initial values.
		//	for(t=0; t<size; t++) nums[t] = rand();
		//for(t=size; t>=0  ; t--) nums[t] = 10-t;

		// Display original array.
		cout << "Original array is: ";
		for(int t=0; t<size; t++) cout << nums[t] << ' '; cout << '\n';
		// This is the bubble sort.
		for(a=0; a<size; a++)
			for(b=size-1; b>=a; b--) {
				if(nums[b-1] > nums[b]) { // if out of order
					// exchange elements
					t = nums[b-1];
					nums[b-1] = nums[b];
					nums[b] = t;
				}
			}
		// This is the end of the bubble sort.
		// Display sorted array.
		cout << "Sorted array is: ";
		for(t=0; t<size; t++) cout << nums[t] << ' ';

		cout << endl;
		return 0;
	}

	//----------------------------------bubblesort.cpp
	//home/tovantran/Ctest/bubblesort.cpp --> 2014-07-07 by ./.tv  owner: tovantran
	// Using the bubble sort to order an array from the C++ ground up book
#include <iostream>
#include <cstdlib>
	using namespace std;
	int main()
	{
		int nums[4]= {10, 12, 1, 0};
		int a, b, t;
		int size;
		size = 4; // number of elements to sort
		// Give the array some random initial values.
		//	for(t=0; t<size; t++) nums[t] = rand();
		//for(t=size; t>=0  ; t--) nums[t] = 10-t;

		// Display original array.
		cout << "Original array is: ";
		for(int t=0; t<size; t++) cout << nums[t] << ' '; cout << '\n';
		// This is the bubble sort.
		for(a=0; a<size; a++)
			for(b=size-1; b>=a; b--) {
				if(nums[b-1] > nums[b]) { // if out of order
					// exchange elements
					t = nums[b-1];
					nums[b-1] = nums[b];
					nums[b] = t;
				}
			}
		// This is the end of the bubble sort.
		// Display sorted array.
		cout << "Sorted array is: ";
		for(t=0; t<size; t++) cout << nums[t] << ' ';

		cout << endl;
		return 0;
	}

	//----------------------------------selectionsort1.cpp
	//home/tovantran/Ctest/selectionsort1.cpp --> 2014-07-07 by ./.tv  owner: tovantran
#include <iostream>
	using namespace std;

	void SelectionSort(int A[], int n)
	{
		for(int i = 0; i < n -1; i++)
		{
			int iMin = i; //1st position
			for(int j = i + 1; j < n; j++)
			{
				if (A[j] < A[iMin])
					iMin = j; 		//update index not value to minimum elements
			}
			int temp = A[i];
			A[i] = A[iMin];
			A[iMin] = temp;
		}
	}
	int main()
	{
		int A[] = {2, 7, 4, 1, 5, 3};
		SelectionSort(A, 6);
		for (int i = 0; i < 6; i++)
			cout << A[i] << " ";
		cout << endl;
		return 0;
	}
	//----------------------------------insertion_sort.cpp
	//home/tovantran/Ctest/insertion_sort.c --> 2014-07-08 by ./.tv  owner: tovantran
#include <stddef.h>
#include <stdio.h>

	static void insertion_sort(int *a, const size_t n) {
		size_t i, j;
		int value;
		for (i = 1; i < n; i++) {
			value = a[i];
			for (j = i; j > 0 && value < a[j - 1]; j--) {
				a[j] = a[j - 1];
			}
			a[j] = value;
		}
	}

	int main(void) {
		int a[] = {4, 65, 2, -31, 0, 99, 2, 83, 782, 1};
		insertion_sort(a, sizeof a / sizeof a[0]);
		for (int i = 0; i < sizeof a/ sizeof a[0]; i++)
			printf("%d", a[i]);
		printf("\n");
		return 0;
	}

	//----------------------------------shellsort1.cpp
	//home/tovantran/Ctest/shellsort1.c --> 2014-07-08 by ./.tv  owner: tovantran
	//K&R
#include <stdio.h>
#include <iostream>
	using namespace std;

	int v[] = {5, 2, 4, 9};

	void shellsort(int v[], int n)
	{
		int i,j, temp, gap;
		for (gap = n/2; gap > 0; gap /=2)
			for (i = gap; i < n ; i++)
				for (j = i - gap; j >= 0 && v[j] > v[j + gap]; j = j - gap)
				{
					temp = v[j];
					v[j] = v[j + gap];
					v[j+gap] = temp;
				}
	}
	void prt()
	{ 
		int i, z;
		z = sizeof v / sizeof v[0];
		for (i = 0; i < z; i++)
			printf("%d",v[i]);
		printf("\n");
	} 
	int main()
	{
		prt();
		shellsort(v,4);
		prt();
		return 0;

	}

	//----------------------------------quicksort.c
	//home/tovantran/Ctest/quicksort.c --> 2014-07-08 by ./.tv  owner: tovantran
#include <stdio.h>
	void quickSort( int[], int, int);
	void main()
	{
		int a[] = { 7, 12, 1, -2, 0, 15, 4, 11, 9};
		int i;
		printf("\n\nUnsorted array is: ");
		for(i = 0; i < 9; ++i)
			printf(" %d ", a[i]);
		quickSort( a, 0, 8);
		printf("\n\nSorted array is: ");
		for(i = 0; i < 9; ++i)
			printf(" %d ", a[i]);
		printf("\n");
	}
	void quickSort( int a[], int l, int r)
	{
		int pivot, i, j, t;
		if( l < r )
		{
			pivot = a[l];
			i = l; 
			j = r+1;
			while( 1)
			{
				do ++i; 
				while( a[i] <= pivot && i <= r );
				do --j; 
				while( a[j] > pivot );
				if( i >= j )   //move i to low and j to high elements of array
					break;
				t = a[i]; 
				a[i] = a[j]; 
				a[j] = t;
			}
			t = a[l]; a[l] = a[j]; a[j] = t;
			quickSort( a, l, j-1);
			quickSort( a, j+1, r);
		}
	}

	//----------------------------------quicksort.c
	//home/tovantran/Ctest/quicksort.c --> 2014-07-08 by ./.tv  owner: tovantran
#include <stdio.h>
	void quickSort( int[], int, int);
	void main()
	{
		int a[] = { 7, 12, 1, -2, 0, 15, 4, 11, 9};
		int i;
		printf("\n\nUnsorted array is: ");
		for(i = 0; i < 9; ++i)
			printf(" %d ", a[i]);
		quickSort( a, 0, 8);
		printf("\n\nSorted array is: ");
		for(i = 0; i < 9; ++i)
			printf(" %d ", a[i]);
		printf("\n");
	}
	void quickSort( int a[], int l, int r)
	{
		int pivot, i, j, t;
		if( l < r )
		{
			pivot = a[l];
			i = l; 
			j = r+1;
			while( 1)
			{
				do ++i; 
				while( a[i] <= pivot && i <= r );
				do --j; 
				while( a[j] > pivot );
				if( i >= j )   //move i to low and j to high elements of array
					break;
				t = a[i]; 
				a[i] = a[j]; 
				a[j] = t;
			}
			t = a[l]; a[l] = a[j]; a[j] = t;
			quickSort( a, l, j-1);
			quickSort( a, j+1, r);
		}
	}

	//----------------------------------randomdigit.cpp
	//home/tovantran/Ctest/randomdigit.cpp --> 2014-07-07 by ./.tv  owner: tovantran
	//mergeSort
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
	using namespace std;

	struct node* SortedMerge(node* a, node* b);
	void FrontBackSplit(node* source, node** frontRef, node** backRef);


	static const char alphanum[] =
		"0123456789"
		"!@#$%^&*"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	struct node{
		int data;
		node *next;
	};
	void MergeSort(struct node** headRef)

	{
		node* head = *headRef;
		node* a;
		node* b;
		if ((head == NULL) || (head->next == NULL))
		{
			return;
		}
		FrontBackSplit(head, &a, &b);
		MergeSort(&a);
		MergeSort(&b);
		*headRef = SortedMerge(a, b);
	}
	node* SortedMerge(node* a, node* b)
	{
		node* result = NULL;

		/* Base cases */
		if (a == NULL)
			return(b);
		else if (b==NULL)
			return(a);

		/* Pick either a or b, and recur */
		if (a->data <= b->data)
		{
			result = a;
			result->next = SortedMerge(a->next, b);
		}
		else
		{
			result = b;
			result->next = SortedMerge(a, b->next);
		}
		return(result);
	}
	void FrontBackSplit(node* source, node** frontRef, node** backRef)

	{
		node *fast, *slow;

		if (source==NULL || source->next==NULL)
		{
			*frontRef = source;
			*backRef = NULL;
		}
		else
		{
			slow = source;
			fast = source->next;
			/* Advance 'fast' two nodes, and advance 'slow' one node */
			while (fast != NULL)
			{
				fast = fast->next;       //fast is double of slow
				if (fast != NULL)
				{
					slow = slow->next;
					fast = fast->next;
				}
			}
			/* 'slow' is before the midpoint in the list, so split it in two
			   at that point. */
			*frontRef = source;
			*backRef = slow->next;
			slow->next = NULL;
		}
	}

	//void swap (node *i, node *j)
	//{	int temp;
	//	temp = i ->data;
	//	j->data = i->data;
	//	j->data = temp;
	//}
	int stringLength = sizeof(alphanum) - 1;

	char genRandom()
	{

		return alphanum[rand() % stringLength];
	}
	string getrandomstr()
	{
		string Str;

		unsigned j = rand() % 20 + 1;
		cout << j << endl;
		for(unsigned int i = 0; i < j; ++i)
		{
			Str += genRandom();

		}
		return Str;
	}
	int main()
	{
		srand(time(0));
		node *ptr, *head;

		head = new node;
		head-> next = 0;
		head->data = 12;
		ptr = head;

		ptr -> next = new node;
		ptr = ptr -> next;
		ptr ->data = 9;

		ptr -> next = new node;
		ptr = ptr -> next;
		ptr ->data = 2;

		ptr -> next = new node;
		ptr = ptr -> next;
		ptr ->data = 11;

		ptr -> next = new node;
		ptr = ptr -> next;
		ptr ->data = 100;

		ptr -> next = new node;
		ptr = ptr -> next;
		ptr ->data = 90;

		ptr->next = 0; // end
		ptr = head;
		while (ptr -> next != 0){
			cout << ptr->data << endl;
			ptr = ptr -> next;	
		}
		cout << ptr->data << endl;
		node *l, *r;
		FrontBackSplit(head, &l, &r); // slip linked link head into left and right

		MergeSort(&l);					//sort left and sort right
		MergeSort(&r);

		cout << "---------" << endl;
		ptr = l;
		while (ptr->next != 0){
			cout << ptr ->data << endl;
			ptr = ptr -> next;
		}
		cout << ptr->data << endl;
		ptr = r;

		while (ptr->next != 0){
			cout << ptr ->data << endl;
			ptr = ptr -> next;
		}
		cout << ptr->data << endl;

		cout << "+++" << endl;
		node *temp = SortedMerge(l, r);   //merger left and right
		ptr = temp;

		while (ptr->next != 0){
			cout << ptr ->data << endl;
			ptr = ptr -> next;
		}
		cout << ptr->data << endl;

		return 0;
	}

	//----------------------------------Animals.java
	//home/tovantran/Ctest/Animal.java --> 2014-06-15  by ./.tv
	//This class has everything: interface, abstract, normal class
	interface Animal {
		String getName();
		String talk();
	}

	abstract class AnimalBase implements Animal
	{
		private String name;

		protected AnimalBase(String name)
		{
			this.name = name;
		}
		public void setName(String name)
		{
			this.name = name;
		}
		public String getName()
		{
			return name;
		}
	}

	class Cat extends AnimalBase
	{
		public Cat(String name)
		{
			super(name);
			//        System.out.println(name);
		}

		public String talk()
		{
			return "Meowww!";
		}
	}

	class Dog extends AnimalBase
	{
		public Dog(String name)
		{
			super(name);
		}

		public String talk()
		{
			return "Arf! Arf! Arf!";
		}
	}

	class Animals
	{
		// prints the following:
		//
		// Missy: Meowww!
		// Mr. Mistoffelees: Meowww!
		// Lassie: Arf! Arf!
		//
		public static void main(String[] args)
		{
			Animal[] animals = 
			{
				new Cat("Missy"),
				new Cat("Mr. Mistoffelees"),
				new Dog("Lassie")
			};

			for (Animal a : animals)
			{
				System.out.println(a.getName() + ": " + a.talk());
			}
		}
	}


	//----------------------------------SuperTest.java
	//javavids Java OOPS inheritance for superclass
	//home/tovantran/Ctest/TestCode.java --> 2014-07-09 by ./.tv  owner: tovantran

	class A { 
		int i;
		A(int i){ 
			this.i = i;
			System.out.println(i);
		}
		int getI() { return i;}
	}
	class B extends A {

		B(int i) {    // add constructor for B with super(i) in the 1st line
			super(i);
		}
		int showI(){
			return i;
		}
	}
	class TestCode {   
		public static void main(String a[]){
			B b_obj = new B(2); //constructor has a value
			System.out.println(b_obj.showI());
			A obj = new A(3);
			System.out.println(b_obj.showI());
		}
	}

	//----------------------------------Main.java
	//home/tovantran/Ctest/Main.java --> 2014-07-09 by ./.tv  owner: tovantran
	abstract class A{
		static String str;
	}

	class B extends A{
		public B(){
			str = "123";
		}
	}

	class C extends A{
		public C(){
			str = "abc";
		}
	}

	public class Main{

		public static void main(String[] args){
			A b = new B();
			A c = new C();
			System.out.println("b.str = " + b.str);
			System.out.println("c.str = " + c.str);
		}
	}
	//----------------------------------cisco_linklist.cpp
	//home/tovantran/Ctest/cisco_linklist.cpp --> 2014-06-15  by ./.tv  owner: tovantran
#include <iostream>
#include <stdio.h>
	using namespace std;
	struct node {
		int data;
		node *next;

	};
	void printList(struct node *start)
	{
		struct node *temp;

		if(start != NULL)
		{
			temp = start;
			printf("\n");
			do {
				printf("%d ", temp->data);
				temp = temp->next;
			} while(temp != start);
			printf("\n");
		}
	}



	node *ptr, *head, *temp;
	void Reverse( node *p)
	{
		if (p->next == NULL)
		{
			head = p;
			return;
		}
		Reverse(p->next);
		temp = p->next;
		temp->next = p;
		p->next = NULL;
	}
	void Print(node *p)
	{
		while (p->next != NULL)
		{
			cout << p->data << endl;
			p = p->next;
		}
		cout << p->data << endl;
	}
	node *Insert(node *head, int data)
	{
		node *temp = new node;
		temp->data = data;
		temp->next = NULL;
		if (head == NULL)
			head = temp;
		else
		{
			node *temp1 = head;
			while (temp1->next != NULL)
				temp1 = temp1->next;

			temp1->next = temp;		// insert new node after head
		}
		return head; 				// after head has been modified
	}
	int isListCircular(node *head)
	{
		node *fast, *slow;
		slow = head;
		fast = head->next; //start faster one node ahead
		if (head == NULL)
			return 0;
		while (true){
			if (fast == slow || fast->next == slow)
				return true;
			else if( !fast || !fast->next)
				return false;
			else{
				fast = fast->next->next;
				slow = slow ->next;
			}
		}		
		//return 0;
	}
	bool findCircular(node *head)
	{
		node *slower, * faster;
		slower = head;
		faster = head->next; //start faster one node ahead
		while(true) {

			// if the faster pointer encounters a NULL element
			if( !faster || !faster->next)
				return false;
			//if faster pointer ever equals slower or faster's next
			//pointer is ever equal to slow then it's a circular list
			else if (faster == slower || faster->next == slower)
				return true;
			else{
				// advance the pointers
				slower = slower->next;
				faster = faster->next->next;
			}
		}
	}
	int main(){

		head = new node;
		head -> next = NULL;
		head ->data = 12;
		ptr = head;
		ptr->next = new node;
		ptr = ptr->next;
		ptr->data = 13;
		ptr->next = 0;
		ptr->next = new node;
		ptr = ptr->next;
		ptr->data = 14;
		ptr->next = 0;

		head = Insert(head, 111);
		head = Insert(head, 112);
		head = Insert(head, 113);

		ptr = head ->next;  //delete 12
		delete head;
		head = ptr;

		Print(head);
		Reverse(head); // head is now at the end of linked list
		printf("---\n");
		Print(head);

		ptr = head;		// make it circular linked list
		while (ptr -> next != NULL)
		{
			ptr = ptr->next;
		}
		ptr -> next = head;   // 13-> 14 ->111 ->112->113 -> 13  tail to head

		printf("Cir = %d\n",findCircular(head));
		cout << "Circular = " << findCircular(head) << endl;
		printf("%s\n",findCircular(head) != 0 ? "Circular linked list" : "Not Circular linked list");
		printf("%s\n",isListCircular(head) != 0 ? "Circular linked list" : "Not Circular linked list");
		printList(head);  //print circular linked list
		return 0;
	}

	//----------------------------------structbook.c
	/* manybook.c -- multiple book inventory */
#include <stdio.h>
#define MAXTITL   40
#define MAXAUTL   40
#define MAXBKS   100              /* maximum number of books  */
	struct book {                     /* set up book template     */
		char title[MAXTITL];
		char author[MAXAUTL];
		float value;
	};
	int main(void)
	{
		struct book library[MAXBKS]; /* array of book structures */
		int count = 0;
		int index;
		printf("Please enter the book title.\n");
		printf("Press [enter] at the start of a line to stop.\n");
		while (count < MAXBKS && gets(library[count].title) != NULL
				&& library[count].title[0] != '\0')
		{
			printf("Now enter the author.\n");
			gets(library[count].author);
			printf("Now enter the value.\n");
			scanf("%f", &library[count++].value);
			while (getchar() != '\n')
				continue;          /* clear input line         */
			if (count < MAXBKS)
				printf("Enter the next title.\n");
		}
		if (count > 0)
		{
			printf("Here is the list of your books:\n");
			for (index = 0; index < count; index++)
				printf("%s by %s: $%.2f\n", library[index].title,
						library[index].author, library[index].value);
		}
		else
			printf("No books? Too bad.\n");
		return 0;
	}
	//home/tovantran/Ctest/Test2.cpp --> 2014-08-25 by ./.tv  owner: tovantran

	//#include <iostream>
	// using namespace std;
	// class Animal
	// {
	// 	public:
	// 	virtual string talk()=0;
	// 	string chat() { cout << "chat" << endl; return 0;};
	// 	int i;
	// 	virtual ~Animal(){};
	// };
	// class Dog: public Animal
	// {
	// 	public:
	//    virtual string talk() {  return 0; }
	//    virtual ~Dog(){};
	// };
	//int i = 9;
	//int main()
	//{
	//Animal *p ;
	//Dog *pt ;
	////Animal Dog;

	//// p->chat();
	//// pt->talk();

	// 
	// return 0;
	//}

#include <iostream>
	using namespace std;
	class Animal
	{
		string name;
		int age;
		public:
		//  void getFoo(string& retname, int& retage){ retname = name; retage = age;};
		virtual string talk() { return "talk"; };
		string chat() {  return "Animal";};
		int i;
		void getFoo(string &n, int &i);  // declare 
		virtual ~Animal(){};
		Animal(string n, int i){ name=n; age = i;}
		string Print(){ return name;};
	};
	class Dog: public Animal
	{
		public:
			Dog( string name, int i) : Animal(name, i) { cout <<"Dog: "<< name  << endl;}
			virtual string talk() {  return "Arf"; }
			virtual ~Dog(){};
	};
	int i = 9;

	void Animal::getFoo(string& retname, int& retage){  //define
		retname = name;
		retage = age;
	}
	int main()
	{
		Animal *p = new Animal ("Bobby", 2);
		Dog *pt = new Dog ("Tippy", 12);
		//Animal Dog;

		// p->chat();

		// p->getFoo( string name, int age);
		//string &retname=retname; int &retage=retage;
		string retname; int retage ;  // you want return to local variable so you can use it
		p->getFoo(retname, retage);
		cout << p->Print() << " is "<< retname << " " << retage << " yrs old will "<< p->talk() << endl;
		pt->getFoo(retname, retage);
		cout << retname << " is " << retage  <<  " yrs old will " << pt->talk() << endl;


		return 0;
	}
	//home/tovantran/Ctest/Test4.cpp --> 2014-08-27 by ./.tv  owner: tovantran
	//http://www.geekinterview.com/question_details/87256  Ways to create objects in C++
	//http://stackoverflow.com/questions/677632/different-methods-for-instantiating-an-object-in-c
#include <iostream>
#include <cstdlib>

	using namespace std;

	class Shape{
		public:
			Shape(){cout<<"Shape..."<<endl;}
			Shape(const Shape& obj)
			{
				cout<<"Copy called"<<endl;
			}
			void* operator new(size_t size)
			{
				cout<<"new...."<<endl;
				void* storage=malloc(size);
				if(NULL == storage) {
					throw "allocation fail : no free memory";
				}
				return storage;
			}

			void operator delete (void*){

			}
	};

	int main()
	{
		Shape obj;
		Shape obj2=obj;  //Assigm oprator
		Shape obj3(obj); //Copy
		Shape* ptrShape=new Shape(); //new
		Shape* ptrShapeOver= new Shape();
		return 0;
	}
	//home/tovantran/Ctest/CPolygon1.cpp --> 2014-11-02 by ./.tv  owner: tovantran
	// virtual members
#include <iostream>
	using namespace std;
	static int obj = 0;

	class CPolygon {
		protected:
			int width, height;
		public:
			void set_values (int a, int b)
			{ width=a; height=b; cout << a << " "<< b << endl;}
			virtual int area (void){ return (width * height);};
			void printarea (void)
				//      { cout << this->area() << endl; }
			{ cout << area() << endl; };
			CPolygon() {cout << "Ctor" << ++obj << endl; }
			~CPolygon() {cout << "Dtor" << obj-- << endl; };
	};

	class CRectangle: public CPolygon {
		public:
			int area (void)
			{ return (width * height) * 2; }
	};
	class CTriangle: public CPolygon {
		public:
			int area (void)
			{ return (width * height / 2); }
	};

	int main () {

		CTriangle trgl;						 // Create object2 of derived class in stack

		CPolygon ppoly1;						// Create object3 in stack
		CRectangle ppoly2;          // Create object4 in stack
		CPolygon * ppoly3 = &trgl;  // pointer to address of object trgl in stack

		CPolygon * ppoly4;				  // pointer only and it points to NOWHERE
		CPolygon *ppoly5 = new CRectangle; //create derived object5 in the heap

		ppoly1.set_values (1,2);    //Base class 
		ppoly2.set_values (3,4); 		//Derived class CRectangle
		ppoly3->set_values(5,6);    //Derived class CTriangle  

		//  ppoly4->set_values(7,8);		//Segmentation fault      ./$file_name
		ppoly5->set_values(10,100);  

		ppoly1.printarea();					
		ppoly2.printarea();       
		ppoly3->printarea();  
		//  ppoly4->printarea();       //Undefined Segmentation fault      ./$file_name  
		ppoly5->printarea();
		delete ppoly5;             //Need delete for the last object Dtor1
		return 0;
	}
	//Pointer vs. Reference
	//home/tovantran/Ctest/reference.c --> 2014-11-03 by ./.tv  owner: tovantran
	//http://cboard.cprogramming.com/c-programming/5783-c-function-returning-multiple-values.html
#include <stdio.h>

	//in C++ with reference 
	void doubleit(int &x, int &y){
		x *= 2;
		y *= 2;
	}

	int main(void){
		int x = 10;
		int y = 5;

		doubleit(x,y);

		printf("%i %i",x,y);

		return 0;
	}
	//in C
#include <stdio.h>

	void doubleit( int *x, int *y){
		*x *= 2;
		*y *= 2;
	}

	int main(void){
		int x = 10;
		int y = 5;
		doubleit( &x, &y);
		printf("%i %i",x,y);
		return 0;
	}
	//: C11:Reference.cpp
	// Simple C++ references
#include <iostream>
	using namespace std;

	int* f(int* x) {
		(*x)++;   //(*x)++ increate point to, *x++ increase the address
		return x; // Safe, x is outside this scope
	}
	int& g(int& x) {
		x++; // Same effect as in f()
		return x; // Safe, outside this scope
	}
	int& h() {
		int q;
		//! return q; // Error
		static int x;
		return x; // Safe, x lives outside this scope
	}
	int main() {
		int a = 0;
		cout << f(&a) << endl; // Ugly (but explicit)
		cout << "a "<< a << endl;
		cout << g(a) << endl; // Clean (but hidden)
		cout << "a "<< a << endl;
	} ///:~
	//The call to f( ) doesn’t have the convenience and cleanliness of
	//using references, but it’s clear that an address is being passed. In
	//the call to g( ), an address is being passed (via a reference), but you
	//don’t see it.

	//: C11:ReferenceToPointer.c Thinking in C++
	//in C
#include <stdio.h>

	void f(int**i){ printf("%p\n", i); (**i)++; printf("%p\n", i);};
	int main() {
		int i = 47;
		int* ip = &i;

		printf("ip = %p, i = %d \n", ip, i);
		f(&ip);
		printf("ip = %p, i = %d \n", ip, i);


	} ///:~
	/*Pointer references*/
	// You don't have reference & in C
	/*In C, if you want to modify the contents of the pointer rather than*/
	/*what it points to, your function declaration looks like:*/
	/*void f(int**);*/
	/*and you’d have to take the address of the pointer when passing it*/
	/*in:*/
	/*int i = 47;*/
	/*int* ip = &i;*/
	/*f(&ip);*/

	//: C11:ReferenceToPointer.cpp Thinking in C++
	// in C++
#include <iostream>
#include <stdio.h>
	using namespace std;
	void increment(int **i) { cout << i << endl; (*i)++; cout << i << endl; }   
	int main() {
		//int* i = 0;  //cannot int *i = 1 but ok with int *i = 0 NULL POINTER
		int *i = 0;
		cout << "i = " << i << endl;
		increment(&i);
		cout << "i = " << i << endl;
	} ///:~

#include <iostream>
	using namespace std;
	void increment(int*&i) { cout << i << endl; i++; cout << i << endl; }
	int main() {
		int* i = 0;
		cout << "i = " << i << endl;
		increment(i);
		cout << "i = " << i << endl;
	} ///:~
	//: C11:ReferenceToPointer.cpp
	//Pointer references
	// You don't have reference & in C

	//With references in C++, the syntax is cleaner. The function
	//argument becomes a reference to a pointer, and you no longer have
	//to take the address of that pointer. Thus,

#include<stdio.h> 

	int main(void)
	{
		/*    char **ptr = NULL; */

		/*    char *p = NULL; */

		char c = 'd'; 

		char *p = &c;
		char **ptr = &p;   //&* -> **

		printf("\n c = [%c]\n",c);
		printf("\n *p = [%c]\n",*p);
		printf("\n **ptr = [%c]\n",**ptr); 

		return 0;
	}
	//------------------StackReverse.cpp
	//home/tovantran/Ctest/StackReverse.cpp --> 2014-12-13 by ./.tv  owner: tovantran
	// like Think of C when create Stack Template StackTemplate.cpp
#include <iostream>
	using namespace std;

	const int SIZE = 100;
	//#define SIZE 100
	template <class T>
		class Stack{
			T stack[SIZE];
			int tos; 				//Top of Stack
			public:
			Stack();
			~Stack();       //if declared here then need to define it later
			void Push(T i);
			T Pop();	
		};
	template <class T>
		Stack<T>::Stack()
		{
			tos = 0;
			cout << "stack initialized\n";
		}
	template <class T>        //when create the ctors you must also create dtors as well compiler create when there is none ctors or dtors was created      
		Stack<T>::~Stack()        //error:  undefined reference to `Stack<char>::~Stack()' this IS NOT THE CASE because you declared in class Stack therefore you need
		{													//define here. If you want compile create a default ctor for you then you must remove declaration in the class ~Stack()
			cout << "stack destroyed\n";
		}
	template <class T>
		void Stack<T>::Push(T i)
		{
			if (tos == SIZE)
			{
				cout << "stack is full\n";
				return;
			}
			stack[tos] = i;
			tos ++;
		}
	template <class T>
		T Stack<T>::Pop()
		{
			if (tos == 0)
			{
				cout << "stack underflow \n";
				return 0;
			}
			tos --;
			return stack[tos];
		}
	int main()
	{
		Stack<int> a;
		Stack<double> b;
		Stack<char> c;
		int i;
		a.Push(1);
		b.Push(99.3);
		a.Push(2);
		b.Push(-12.23);
		cout << a.Pop() << " " << a.Pop() << " " << b.Pop() << " "<< b.Pop() << endl;
		//cout << a.Pop() << " " << b.Pop() << " " << a.Pop() << " "<< b.Pop() << endl;

	}
	//--------------------ReverseString1.cpp
	//home/tovantran/Ctest/ReverseString1.cpp --> 2014-12-16 by ./.tv  owner: tovantran
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <cstring>    // not string but cstring
	using namespace std;

	/* reverse:  reverse string s in place */
	void reverse(char *s)
	{
		int c, i, j;

		for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
			c = s[i];
			s[i] = s[j];
			s[j] = c;
		}
	}
	//overwrite
	void reverse(char *s, int n, int m) //pass pointer but s change outside the caller
	{
		char p = s[m];
		if (n != 0)
			reverse(s, n-1, m+1);
		//	printf("%c\n", p);
		s[n] = p; 	//pull from stack tovan-> novot n is in stack 6,5...1
	}
	//C++11
	string reverse(string &s)
	{
		string b(s);	//copy s to b
		reverse_copy(s.begin(),s.end(),b.begin());
		return b;
	}
	//reverse string can swap here
	void reverse(char *s)
	{
		int n = s.length();
		for (int i = n, j = 0; i >= 0; i--, j++)  //reverse string
			cout << s[j] << endl;
	}
	int main()
	{
		char s[] = "tovan";
		cout << "String before:" << s << endl;
		reverse(s);
		cout << "String after reverse: " << s << endl;  //tovan navot
		reverse(s, strlen(s) -1, 0); //remove null at the end strlen(s) -1
		cout << "String after reverse again: " << s << endl; 
		return 0;
	}

	//----------------------------------smartpointer3.cpp
	//home/tovantran/Ctest/smartpointer3.cpp --> 2014-06-23 by ./.tv  owner: tovantran
	//http://www.cplusplus.com/reference/memory/auto_ptr/auto_ptr/
	// auto_ptr example
#include <iostream>
#include <memory>

	int main () {
		std::auto_ptr<int> p1 (new int);
		*p1.get()=10;

		//  std::auto_ptr<int> p2 (p1);

		//  std::cout << "p2 points to " << *p2 << '\n';
		std::cout << "p1 points to " << *p1 << '\n';  //renew
		// (p1 is now null-pointer auto_ptr)

		return 0;
	}

	//----------------------------------SmartPointer3.cpp
	//home/tovantran/Ctest/SmartPointer3.cpp --> 2014-12-17 by ./.tv  owner: tovantran
	//http://www.bogotobogo.com/cplusplus/autoptr.php
#include <iostream>
#include <memory>

	using namespace std;

	class Double
	{
		public:
			Double(double d = 0) : dValue(d) { cout << "constructor: " << dValue << endl; } 
			~Double() { cout << "destructor: " << dValue << endl; }
			void setDouble(double d) { dValue = d; }
		private:
			double dValue;
	}; 

	int main()
	{
		auto_ptr<Double> ptr(new Double(3.14));
		(*ptr).setDouble(6.28);   //review *ptr.setDouble(6.28) is not the same.
		//	ptr->setDouble(4.44);
		return 0;
	}
	//----------------------------------SmartPointer6.cpp
	//C++ How to program 5/e
	// Fig. 16.8: Integer.h
	// Integer class definition.
#include <iostream>
#include <memory>
	using std::auto_ptr; // auto_ptr class definition
	using std::cout;
	using std::endl;

	class Integer
	{
		public:
			Integer( int i = 0 ); // Integer default constructor
			~Integer(); // Integer destructor
			void setInteger( int i ); // functions to set Integer
			int getInteger() const; // function to return Integer
		private:
			int value;
	}; // end class Integer
	// Fig. 16.9: Integer.cpp
	// Integer member function definition.


	// Integer default constructor
	Integer::Integer( int i ) : value( i )
	{
		cout << "Constructor for Integer " << value << endl;
	} // end Integer constructor

	// Integer destructor
	Integer::~Integer()
	{
		cout << " **Destructor for Integer " << value << endl;
	} // end Integer destructor

	// set Integer value
	void Integer::setInteger( int i )
	{
		value = i;
	} // end function setInteger

	// return Integer value
	int Integer::getInteger() const
	{
		return value;
	} // end function getInteger
	// Fig. 16.10: Fig16_10.cpp
	// Demonstrating auto_ptr.

	// use auto_ptr to manipulate Integer object
	int main()
	{
		cout << "Creating an auto_ptr object that points to an Integer\n";

		// "aim" auto_ptr at Integer object
		auto_ptr< Integer > ptrToInteger( new Integer( 7 ) );

		cout << "\nUsing the auto_ptr to manipulate the Integer\n";
		ptrToInteger->setInteger( 99 ); // use auto_ptr to set Integer value

		// use auto_ptr to get Integer value
		cout << "Integer after setInteger: " << ( *ptrToInteger ).getInteger() << endl;
		return 0;
	} // end mainal
	//----------------------------------endianness1.c
#include <stdio.h>

	typedef enum _endian {little_endian, big_endian} EndianType;

	EndianType CheckCPUEndian()
	{
		unsigned short x;
		unsigned char c;
		EndianType CPUEndian;

		x = 0x0401;
		c = *(unsigned char *)(&x);
		if( c == 0x01 )
			CPUEndian = little_endian;
		else
			CPUEndian = big_endian;

		return CPUEndian;
	}
	int main()
	{
		printf("CheckCPUEndian() = %d\n", CheckCPUEndian());
		printf("Endian type: %s\n", CheckCPUEndian() == 0 ? "Little_endian" : "Big_endian");
	}
	//----------------------------------endianness.cpp
	//home/tovantran/Ctest/endianness.cpp --> 2014-12-20 by ./.tv  owner: tovantran
	//Annonation C++
#include <iostream>
#include <stdio.h>

	using namespace std;
	int main()
	{
		int value = 0x12345678; // assume a 32-bits int
		printf("%x\n", *(unsigned char *)&value);

		cout  << hex << *(unsigned char *)&value << endl;

		cout  << hex << (int)*(unsigned char *)&value << endl;

		cout << hex << 0x78 << endl;
		cout << "Value’s first byte has value: " << hex << static_cast<int>(*reinterpret_cast<unsigned char *>(&value)) << endl;
	}
Output:
78
x  (ascii of 78)
78
78
Value’s first byte has value: 78
//----------------------------------VoidPointer.cpp
// home/tovantran/Ctest/VoidPointer.cpp --> 2014-12-22 by ./.tv  owner:
// tovantran
// class templates class template
// update Aug31, 2015
#include <iostream>
#include <stdio.h>
#include <iomanip>

using namespace std;

template <class T> class Increase {
  T value;

public:
  Increase(T val) { value = ++val; }
  T getValue() const;
  void setValue(const T &value); // C++ referemce
};

template <class T> T Increase<T>::getValue() const { return value; }

template <class T> void Increase<T>::setValue(const T &value) { this->value = value; }

void increase(void *data, int type) {
  switch (type) {
  case sizeof(char):
    (*((char *)data))++;
    break;
  case sizeof(short):
    (*((short *)data))++;
    break;
  case sizeof(long):
    (*((long *)data))++;
    break;
  case sizeof(float):
    (*((float *)data))++;
    break;
  }
}

int main() {
  Increase<int> myobject(1);
  cout << myobject.getValue() << endl;

  Increase<char> myobject1('a');
  cout << (char)myobject1.getValue() << endl;
  cout << static_cast<char>(myobject1.getValue()) << endl;

  Increase<float> myobject2(100.22);
  cout << setprecision(5) << myobject2.getValue() << endl;
  
  myobject2.setValue(200);
  cout << setprecision(5) << myobject2.getValue() << endl;

  char a = 5;
  short b = 6;
  long c = 12;
  float d = 12.12;
  increase(&a, sizeof(a));
  increase(&b, sizeof(b));
  increase(&c, sizeof(c));
  increase(&d, sizeof(d));
  cout << (int)a << ", " << b << ", " << c << ", " << d << endl;
  return 0;
}
	//----------------------------------Reinterpret_Cast3.cpp
#include <iostream>
	using namespace std;
	int main()
	{
		int i;
		const char *p = "This is a string";
		//	i = *reinterpret_cast<int *> (p); // cast pointer to integer
		//	cout << i << endl;
		//	char * const s = "test";

		//	s = "tran";  //error: assignment of read-only variable ‘s’
		//	*s = (*(const_cast<char *>("ttt")));
		//	*s = (*const_cast<char *>("ttt"));
		//	*s = *(char *)("tran");
		//	char *j = const_cast<char *> (s);  //cast const
		//  j = "tt";	
		//	cout << j << endl;
		const char *s1 = "abc";
		cout << s1 << endl;
		s1 =  const_cast<char *>("def");
		cout << s1 << endl;
		return 0;
	}



	//----------------------------------Reinterpret_Cast.cpp
	//home/tovantran/Ctest/Reinterpret_Cast.cpp --> 2014-12-20 by ./.tv  owner: tovantran
	// An example that uses reinterpret_cast.
#include <iostream>
	using namespace std;
	int main()
	{
		int i;
		//	char *p = "This is a string";
		//  i = static_cast<int>(*reinterpret_cast<char *>(p)); // cast pointer to integer
		//Reinterpret_Cast.cpp:11:50: error: reinterpret_cast from type ‘const char*’ to type ‘char*’ casts away qualifiers USE const_cast
		const char *p = "This is a string";
		i = static_cast<int>(*const_cast<char *>(p)); // cast pointer to integer
		cout << hex <<  i << endl;
		//  cout << "Value’s first byte has value: " << hex << static_cast<int>(*reinterpret_cast<unsigned char *>(&value)) << endl;
		i = *(unsigned char *)p;
		cout << i << endl;
		return 0;
	}



//----------------------------------UDPServer.java
//home/tovantran/Ctest/UDPServer.java --> 2015-03-14 by ./.tv  owner: tovantran

//https://systembash.com/a-simple-java-udp-server-and-udp-client/
//ip=localhost port=9876
//package socket.udpserver;

//import java.io.*;
import java.net.*;

class UDPServer
{
   public static void main(String args[]) throws Exception
      {
         DatagramSocket serverSocket = new DatagramSocket(9876);
            byte[] receiveData = new byte[1024];
            byte[] sendData = new byte[1024];
            while(true)
               {
                  DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
                  serverSocket.receive(receivePacket);
                  String sentence = new String( receivePacket.getData());
                  // convert byte to String
                  System.out.println("RECEIVED: " + sentence);
                  InetAddress IPAddress = receivePacket.getAddress();
                  int port = receivePacket.getPort();
                  String capitalizedSentence = sentence.toUpperCase();
                  sendData = capitalizedSentence.getBytes();
                  DatagramPacket sendPacket =
                  new DatagramPacket(sendData, sendData.length, IPAddress, port);
                  serverSocket.send(sendPacket);
               }
      }
}
//----------------------------------UDPClient.java
//home/tovantran/Ctest/UDPClient.java --> 2015-03-14 by ./.tv  owner: tovantran

//https://systembash.com/a-simple-java-udp-server-and-udp-client/
//ip=localhost port=9876

//package socket.udpclient;

import java.io.*;
import java.net.*;

class UDPClient
{
   public static void main(String args[]) throws Exception
   {
      BufferedReader inFromUser =
         new BufferedReader(new InputStreamReader(System.in));
      DatagramSocket clientSocket = new DatagramSocket();
      InetAddress IPAddress = InetAddress.getByName("localhost");
      byte[] sendData = new byte[1024];
      byte[] receiveData = new byte[1024];
      for (int i = 0; i < sendData.length; i++){
    	  sendData[i] = 0x41;
      }
      String sentence = inFromUser.readLine();
      sendData = sentence.getBytes();
      DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, 9876);
      clientSocket.send(sendPacket);
      DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
      clientSocket.receive(receivePacket);
      String modifiedSentence = new String(receivePacket.getData());
      System.out.println("FROM UDP SERVER:" + modifiedSentence);
      clientSocket.close();
   }
}

//----------------------------------TCPServer.java
//home/tovantran/Ctest/TCPServer.java --> 2015-03-14 by ./.tv  owner: tovantran

//https://systembash.com/a-simple-java-tcp-server-and-tcp-client/
//package mythread.tcpserver;

import java.io.*;
import java.net.*;

class TCPServer
{
   public static void main(String argv[]) throws Exception
      {
         String clientSentence;
         String capitalizedSentence;
         ServerSocket welcomeSocket = new ServerSocket(6789);
                                      // ServerSocket only port
         while(true)
         {
            Socket connectionSocket = welcomeSocket.accept();
            BufferedReader inFromClient =
               new BufferedReader(new InputStreamReader(connectionSocket.getInputStream()));
            DataOutputStream outToClient = new DataOutputStream(connectionSocket.getOutputStream());
            clientSentence = inFromClient.readLine();
            System.out.println("Received: " + clientSentence);
            capitalizedSentence = clientSentence.toUpperCase() + '\n';
            outToClient.writeBytes(capitalizedSentence);
         }
      }
}
//----------------------------------TCPClient.java
//home/tovantran/Ctest/TCPClient.java --> 2015-03-14 by ./.tv  owner: tovantran

//https://systembash.com/a-simple-java-tcp-server-and-tcp-client/
//package mythread.tcpclient;

import java.io.*;
import java.net.*;

class TCPClient
{
 public static void main(String argv[]) throws Exception
 {
  String sentence;
  String modifiedSentence;
  BufferedReader inFromUser = new BufferedReader( new InputStreamReader(System.in));
  Socket clientSocket = new Socket("localhost", 6789); //Socket(client) host and port
  DataOutputStream outToServer = new DataOutputStream(clientSocket.getOutputStream());
  BufferedReader inFromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
  sentence = inFromUser.readLine();
  outToServer.writeBytes(sentence + '\n');
  modifiedSentence = inFromServer.readLine();
  System.out.println("FROM TCP SERVER: " + modifiedSentence);
  clientSocket.close();
 }
}
//----------------------------------WorkerRunnable.java
//home/tovantran/Ctest/WorkerRunnable.java --> 2015-03-17 by ./.tv  owner: tovantran
//package mythread.threadpooled.runnable;
//http://tutorials.jenkov.com/java-multithreaded-servers/multithreaded-server.html

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.Socket;

public class WorkerRunnable implements Runnable {

	protected Socket clientSocket = null;
	protected String serverText = null;
	String clientSentence;

	public WorkerRunnable(Socket clientSocket, String serverText) {
		this.clientSocket = clientSocket;
		this.serverText = serverText;
	}

	public void run() {
		try {
			InputStream input = clientSocket.getInputStream();
			OutputStream output = clientSocket.getOutputStream();
			BufferedReader inFromClient =
	                new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
			long time = System.currentTimeMillis();
			
			clientSentence = inFromClient.readLine();
	        System.out.println("FROM CLIENT: " + clientSentence);
	        
			output.write(("HTTP/1.1 200 OK\n\nWorkerRunnable: "
					+ this.serverText + " - " + time + "").getBytes());
			output.close();
			input.close();
			System.out.println("Request processed time: " + time);
		} catch (IOException e) {
			// report exception somewhere.
			e.printStackTrace();
		}
	}
}

//----------------------------------WorkerRunnable.java
//home/tovantran/Ctest/WorkerRunnable.java --> 2015-03-17 by ./.tv  owner: tovantran
//package mythread.threadpooled.runnable;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.Socket;

public class WorkerRunnable implements Runnable {

	protected Socket clientSocket = null;
	protected String serverText = null;
	String clientSentence;

	public WorkerRunnable(Socket clientSocket, String serverText) {
		this.clientSocket = clientSocket;
		this.serverText = serverText;
	}

	public void run() {
		try {
			InputStream input = clientSocket.getInputStream();
			OutputStream output = clientSocket.getOutputStream();
			BufferedReader inFromClient =
	                new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
			long time = System.currentTimeMillis();
			
			clientSentence = inFromClient.readLine();
	        System.out.println("FROM CLIENT: " + clientSentence);
	        
			output.write(("HTTP/1.1 200 OK\n\nWorkerRunnable: "
					+ this.serverText + " - " + time + "").getBytes());
			output.close();
			input.close();
			System.out.println("Request processed time: " + time);
		} catch (IOException e) {
			// report exception somewhere.
			e.printStackTrace();
		}
	}
}

//----------------------------------WorkerRunnable.java
//home/tovantran/Ctest/WorkerRunnable.java --> 2015-03-17 by ./.tv  owner: tovantran
//package mythread.threadpooled.runnable;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.Socket;

public class WorkerRunnable implements Runnable {

	protected Socket clientSocket = null;
	protected String serverText = null;
	String clientSentence;

	public WorkerRunnable(Socket clientSocket, String serverText) {
		this.clientSocket = clientSocket;
		this.serverText = serverText;
	}

	public void run() {
		try {
			InputStream input = clientSocket.getInputStream();
			OutputStream output = clientSocket.getOutputStream();
			BufferedReader inFromClient =
	                new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
			long time = System.currentTimeMillis();
			
			clientSentence = inFromClient.readLine();
	        System.out.println("FROM CLIENT: " + clientSentence);
	        
			output.write(("HTTP/1.1 200 OK\n\nWorkerRunnable: "
					+ this.serverText + " - " + time + "").getBytes());
			output.close();
			input.close();
			System.out.println("Request processed time: " + time);
		} catch (IOException e) {
			// report exception somewhere.
			e.printStackTrace();
		}
	}
}

//----------------------------------referencepointer4-const.cpp
#include <iostream>
using namespace std;

void f(int&) {}
void g(const int&) {}
//C
void increment(int **i) { (**i)++ ; } 
//C++
//void increment1(int &*i) { i++;} //error: cannot declare pointer to 'int&'
void increment1(int *&i) { (*i)++;} //content what it points is incremented
void increment2(int *&i) { i++; } //pointer is incremented
int main() {
 int a = 1;
// f(1); // Error
 f(a);
 g(1);
 cout << "out" << endl;
 
 int i = 5;
 int *ip = &i; //pointer
 int **ipp = &ip;
 //how to print i = 5;
 cout << "**ipp =" << **ipp << endl;
 cout << "*ip =" << *ip << endl;
 cout << "i =" << i << endl;
 cout << "*&i =" << *&i << endl;
 cout << "Address of pointer ipp = " << ipp << endl;
 cout << "Address of pointer &ip = " << &ip << endl;
 increment(&ip);  //address of pointer 
 cout << "i =" << i << endl;
 increment(ipp);
 cout << "i =" << i << endl;
 increment1(ip);
 cout << "i =" << i << endl;
 
 int* j = 0;
 cout << "j = " << j << endl;
 increment2(j);
 cout << "j = " << j << endl;
} ///:~

//----------------------------------Reference5.cpp
//home/tovantran/Ctest/Reference5.cpp --> 2015-04-01 by ./.tv  owner: tovantran

//-------C--------Pass by reference is simulated by passing the address of variable(pointer)
//and dereferencing that address within the function to read or write the actual variable.
#include <stdio.h>
void duplicate (int* a, int* b, int* c)
{
	*a *= 2; //change A like value
	*b *= 2; // not pointer
	*c *= 2;
	*c = 100;
}
void change(char *s)
{
	s[0] = 'A'; //already pointer
}
int main ()
{
	char *s = "Hello";
	int x=1, y=3, z=7;
	duplicate (&x, &y, &z);
	/*  cout << "x=" << x << ", y=" << y << ", z=" << z << endl;*/
	printf("x = %d, y = %d, x = %d\n", x, y, z);
	change(s); //no need take address is a already pointer
	return 0;
}
//-------C++ ----------
// passing parameters by reference
#include <iostream>
using namespace std;

void duplicate (int& a, int& b, int& c)
{
	a *= 2; //change A like value
	b *= 2; // not pointer
	c *= 2;
	c = 100;
}

int main ()
{
	int x=1, y=3, z=7;
	duplicate (x, y, z);
	cout << "x=" << x << ", y=" << y << ", z=" << z << endl;
	return 0;
}
//Here’s an example:
//: C11:Reference.cpp
// Simple C++ references
int* f(int* x) {
	(*x)++;
	return x; // Safe, x is outside this scope
}
int& g(int& x) {
	x++; // Same effect as in f()
	return x; // Safe, outside this scope
	int& h() {
		int q;
		//! return q; // Error
		static int x;
		return x; // Safe, x lives outside this scope
	}
	int main() {
		int a = 0;
		f(&a); // Ugly (but explicit)
		g(a); // Clean (but hidden)
	} ///:~

//----------------------------------userapp.c
////home/tovantran/Ctest/k_r/kernel_hi8usbdriver/kernel_modules/test_char_device/userapp.c --> 2015-04-03 by ./.tv  owner: tovantran
//youtube.com SolidusCode
//http://stackoverflow.com/questions/1247989/how-do-you-allow-spaces-to-be-entered-using-scanf
/* user application which reads and writes to a device */
/* 
   Usage:
   % make
   % ./userapp
 */
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>

#define DEVICE "/dev/testCharDevice"

int main(int argc, char *argv[])
{
  int i, fd;
  char ch, write_buf[100], read_buf[100];

  fd = open(DEVICE, O_RDWR);	/* open for read/write */

  if(fd == -1){
    printf("file %s either doesnot exit, or locked by another process\n", DEVICE);
    exit(-1);
  }
  printf("r - read from device,\nw- write from device\nEnter command: ");
  scanf("%c", &ch);
/*  ch = getchar();*/
  switch (ch){    
  case 'w':
 		printf ("enter data: ");
		fgets(write_buf,100, stdin);        // read AT echo
/*    scanf("%s", write_buf);*/
		scanf("%[^\n]s", write_buf);
    write(fd, write_buf, sizeof(write_buf)); //user to kernel writebuf ->fd
    break;

  case 'r':
    read(fd, read_buf, sizeof(read_buf));
    printf ("device: %s\n", read_buf);
    break;

  default:
    printf ("command not recognized\n");
    break;
  }

  close(fd);
  return 0;
}

//----------------------------------csbu.c
//home/tovantran/Ctest/csbu.c --> 2015-04-06 by ./.tv  owner: tovantran

//Book. Computer Science bottom up
#include <stdio.h>
/* The API to implement */
struct greet_api
{
	int (*say_hello)(char *name);
	int (*say_goodbye)(void);
};
/* Our implementation of the hello function */
/* Our implementation of the goodbye function */
int say_goodbye_fn(void)
{
	printf("Goodbye\n");
	return 0;
}
int say_hello_fn(char *name)
{
	printf("Hello %s\n", name);

}
/* A struct implementing the API */
struct greet_api greet_api =
{
	.say_hello = say_hello_fn,
	say_goodbye : say_goodbye_fn //: initialize
};
/* main() doesn't need to know anything about how the
 * say_hello/goodbye works, it just knows that it does */
int main(int argc, char *argv[])
{
	greet_api.say_hello(argv[1]);
	greet_api.say_goodbye();
	printf("%p, %p, %p\n", greet_api.say_hello, say_hello_fn, &say_hello_fn);
/*	exit(0);*/
	return 0;
}
//from rtmp_main.c
/*struct usb_driver rtusb_driver = {*/
/*		name:"rt73",*/
/*		probe:usb_rtusb_probe,*/
/*		disconnect:usb_rtusb_disconnect,*/
/*		id_table:rtusb_usb_id,*/
/*	};*/
/*	.name="rt73",*/
/*	.probe=usb_rtusb_probe,*/
/*	.disconnect=usb_rtusb_disconnect,*/
/*	.id_table=rtusb_usb_id,*/
//----------------------------------TestApril.cpp
//home/tovantran/Ctest/TestApril.cpp --> 2015-04-06 by ./.tv  owner: tovantran

// google C++ style guide and C++ programming guide
//http://geosoft.no/development/cppst/c.html#Naming Convention
#include <iostream>
using namespace std;

class Test{
	public:
	bool m_isVal;  // member variable in C++ beginning with m_isVal
	
	bool isVal() {
			return m_isVal;
	}
};
int main(){
	Test *t = new Test;
	cout << "isVal = " << t->isVal() << endl;
	return 0;
}
//----------------------------------TestApril.java
//home/tovantran/Ctest/TestApril.java --> 2015-04-06 by ./.tv  owner: tovantran
// in Java member variable and function have the same name in C++ cannot because 
//class.isVal() and class.isval C++ no member variable namespace
class TestApril{
	
	public boolean isVal;
	public boolean isVal() { return isVal; }
	public static void main(String args[]){
		System.out.println("Test");
	}
};
//----------------------------------dynamic_cast4.cpp
//Derived class member initialization by base class constructor
//http://stackoverflow.com/questions/20561441/derived-class-member-initialization-by-base-class-constructor

#include <iostream>
#include <stdio.h>
using namespace std;

class Base
{
	public:
		char *p;
		Base(){};
		Base(char *a) :p(a)   // pointer of arr[10]
		{
			sprintf(a, "HELLO");
			cout << "Base a = " << a << endl;
		};
};
class Derived : public Base
{
	public:
		int a;
		char arr[10];   //Base(arr)
		Derived(int a) : Base(&arr[0]){ cout << "Derived a = " << a << endl; }
		//        Derived(int a) : Base(arr){ cout << "Derived a = " << a << endl; }
};
int main() {


Derived *d = new Derived(111);
//        cout << d->Base << endl;
//        cout << d->Derived << endl;

cout << "Base p = " << d->p << endl;
cout << "Derived arr = " << d->arr << endl;
//	char p[2];
//	sprintf(p,"Atest");
//	printf("%d\n", *p);
cout << "test" << endl;
return 0;
}


//----------------------------------struct_hardware9.c
//home/tovantran/Ctest/struct_hardware9.c --> 2015-04-13 by ./.tv  owner: tovantran

// CANNOT USE Qt Creator because it is C++ unless open terminal gcc -o and
// remove namespace std
// in C
#include <stdio.h>

struct greet_api {
  const char *name;
  void (*say_hello)(char *name);   //function pointer need bracket (*say_hello)
  void (*say_goodbye)(void);
};
void say_hello_fn(char *name) { printf("Hello %s\n", name); }
void say_goodbye_fn(void) { printf("Goodbye\n "); }
struct greet_api greet_api = {
  name : "ToVan",
  say_hello : say_hello_fn,
  say_goodbye : say_goodbye_fn,
};

int main() {
  greet_api.say_hello("ToVan");
  greet_api.say_goodbye();
  printf("name = %s\n", greet_api.name);
}

// in C++
//#include <stdio.h>
//#include <iostream>
// using namespace std;

// class greet_api {
//    string name;
// public:
//    greet_api(string name): name(name){ cout << name << endl;}
//    void say_hello() { cout << "Hello "<< name << endl; }
//    void say_goodbye() { cout << "Goodbye "<< name << endl;}
//};

// int main()
//{
//    greet_api obj("ToVan");
//    obj.say_hello();
//    obj.say_goodbye();
//}

//----------------------------------struct_hardware9.c
//home/tovantran/Ctest/struct_hardware9.c --> 2015-04-13 by ./.tv  owner: tovantran

// CANNOT USE Qt Creator because it is C++ unless open terminal gcc -o and
// remove namespace std
// in C
#include <stdio.h>

struct greet_api {
  const char *name;
  void (*say_hello)(char *name);   //function pointer need bracket (*say_hello)
  void (*say_goodbye)(void);
};
void say_hello_fn(char *name) { printf("Hello %s\n", name); }
void say_goodbye_fn(void) { printf("Goodbye\n "); }
struct greet_api greet_api = {
  name : "ToVan",
  say_hello : say_hello_fn,
  say_goodbye : say_goodbye_fn,
};

int main() {
  greet_api.say_hello("ToVan");
  greet_api.say_goodbye();
  printf("name = %s\n", greet_api.name);
}

// in C++
//#include <stdio.h>
//#include <iostream>
// using namespace std;

// class greet_api {
//    string name;
// public:
//    greet_api(string name): name(name){ cout << name << endl;}
//    void say_hello() { cout << "Hello "<< name << endl; }
//    void say_goodbye() { cout << "Goodbye "<< name << endl;}
//};

// int main()
//{
//    greet_api obj("ToVan");
//    obj.say_hello();
//    obj.say_goodbye();
//}

//----------------------------------FunctionTemplate.cpp
//home/tovantran/Ctest/FunctionTemplate.cpp --> 2015-04-16 by ./.tv  owner: tovantran
//http://www.tutorialspoint.com/cplusplus/cpp_templates.htm
#include <iostream>
#include <string>

using namespace std;

template <typename T>
T Max (T a, T b)
{
    return a < b ? b:a;
}
int main ()
{

    int i = 39;
    int j = 20;
    cout << "Max(i, j): " << Max(i, j) << endl;

    double f1 = 13.5;
    double f2 = 20.7;
    cout << "Max(f1, f2): " << Max(f1, f2) << endl;

    string s1 = "Hello";
    string s2 = "World";
    cout << "Max(s1, s2): " << Max(s1, s2) << endl;

   return 0;
}

//----------------------------------StructHardware.cpp
// home/tovantran/Ctest/struct_hardware9.c --> 2015-04-13 by ./.tv  owner:
// tovantran

// CANNOT USE Qt Creator because it is C++ unless open terminal gcc -o and
// remove namespace std
// in C
#include <stdio.h>
#include <malloc.h>
typedef struct foo{int i;} foo;
#define greet_api1 struct greet_api
#define MY_TYPE 10

foo f = { 2 };
struct foo ff;

struct foo *p;
foo *pp;

foo test;  //it is not a pointer no need to initialize
//Thinking in C++ media
struct Foo { int x:22; int y:23; };
struct Foo fx = { 220, 221};
//struct FooTest{ int x;};
typedef struct Footest{int x; int y;} Fooo;
Fooo ftest = { 111112, 13 };  //Fooo ftest = { 12, 13}; same thing with = or without
//Array {}


typedef struct greet_api {
  const char *name;
  void (*say_hello)(const char *name); // function pointer need bracket (*say_hello)
  void (*say_goodbye)(void);
} _greet_api;
void say_hello_fn(const char *name) { printf("Hello %s\n", name); } //const
void say_goodbye_fn(void) { printf("Goodbye\n "); }
struct greet_api greet_api = {
  name : "ToVan",

  say_hello : say_hello_fn,
  say_goodbye : say_goodbye_fn,
};
//const char *s = "constant string"; //need const: deprecated from string constanst to char*
void footesting(const char *s) { printf("%s\n",s);};

//STRUCT DO AFTER MAIN
int main() {
  footesting("constant string");
  printf("%d\n", ftest.x);

  p = &f;  // point to something
//  p->i = 10;
  printf("%d\n", p->i);
  pp = &ff; //point to something
  pp->i = 100;
  printf("%d\n", pp->i);

  test.i = 111;
  p = &test;
  printf("%d\n", p->i);

  Foo foo = {1, 2} ;  //point to something
  printf("foo = %d  %d\n",foo.x, foo.y);
  Foo *foo1 = &fx;
  printf("foo = %d  %d\n",foo1->x, foo1->y);

  printf("foo = %d  %d\n",fx.x, fx.y);
  Foo *t = &fx;
  printf("foo = %d  %d\n",t->x, t->y);
  greet_api.say_hello("ToVan");  //stack
  greet_api.say_goodbye();
  printf("name = %s\n", greet_api.name);
  struct greet_api *api = (struct greet_api *)malloc(sizeof(greet_api));//heap
  api->name = "Tom";
  api->say_hello = &say_hello_fn;
  api->say_goodbye = &say_goodbye_fn;
  printf("name = %s\n", api->name);
  api->say_hello("Andy");
  api->say_goodbye();
}

// in C++
//#include <stdio.h>
//#include <iostream>
// using namespace std;

// class greet_api {
//    string name;
// public:
//    greet_api(string name): name(name){ cout << name << endl;}
//    void say_hello() { cout << "Hello "<< name << endl; }
//    void say_goodbye() { cout << "Goodbye "<< name << endl;}
//};

// int main()
//{
//    greet_api obj("ToVan");
//    obj.say_hello();
//    obj.say_goodbye();
//}

//----------------------------------Interface.java
//home/tovantran/Ctest/Interface.java --> 2015-04-24 by ./.tv  owner: tovantran

interface Callback {
void callback(int param);
}
class Client implements Callback {
// Implement Callback's interface
	public void callback(int p) {
	System.out.println("callback called with " + p);
	}

	void nonIfaceMeth() {
	System.out.println("Classes that implement interfaces " +
	"may also define other members, too.");
	}
}
// Another implementation of Callback.
class AnotherClient implements Callback {
// Implement Callback's interface
	public void callback(int p) {
	System.out.println("Another version of callback");
	System.out.println("p squared is " + (p*p));
	}
}

class Interface {
	public static void main(String args[]) {
	Callback c = new Client();
	AnotherClient ob = new AnotherClient();
	c.callback(42);
	c = ob; // c now refers to AnotherClient object
	c.callback(42);
	
	Callback callback = new Callback(){ 
	  public void callback(int p){ 
	  System.out.println("Anonymous class " + p);	
    }	
	};
	callback.callback(22);
	}
}

//----------------------------------Anonymous.java
//home/tovantran/Ctest/Anonymous.java --> 2015-04-30 by ./.tv  owner: tovantran
//http://www.programmerinterview.com/index.php/java-questions/java-anonymous-class-example/

package anonymousclass;

class Animal{
	void run(){
		System.out.println("Run");
	}
	void eat(){}
}
class Dog extends Animal{
	void park(){
	  System.out.println("Park");
	}
}
public class Anonymous {
  public static void main(String[] args)
  {
  	Animal d = new Dog();
  	d.run();
//  	d.park();
  	
  	Animal dd = new Dog(){
  		public void eat() {}
  		public void run() {}
  	};
  	dd.eat();   //using anonymous class to overload function eat in superclass
//  	dd.run();
  }
}
//----------------------------------MayInsertionSort.cpp
//home/tovantran/Ctest/MayInsertionSort.cpp --> 2015-05-14 by ./.tv  owner: tovantran

#include <iostream>
using namespace std;

void insertion(int *a, int n)
{
	int i, j, value, temp;
	for (i = 1; i < n; i++)
	{
		value = a[i];
	for (j = i; j > 0; j--){
		if (value < a[j -1])
		{
			temp = a[j];
			a[j] = a[j - 1];
			a[j -1] = temp;
			}
		}
	}
}
void insertionSort(int a[], int n)
{
	int i, j, value;
	for (i = 1; i < n; i++)
	{
		value = a[i];
		for (j = i; j > 0 && value < a[j-1]; j--)
			a[j] = a[j-1];
		a[j] = value;
	}
}
int main(){
	int arr[] = {3, 7, 1, 0, 22, 1, 5};
	insertionSort(arr, 7);
	for (int i = 0; i < 7; i++)
		cout << arr[i] << " ";
	cout << endl;
}

//----------------------------------May16Sort.cpp
//home/tovantran/Ctest/May16Sort.cpp --> 2015-05-19 by ./.tv  owner: tovantran
//selection, insertion, bubble, merge, quick
#include <iostream>
#include <stdlib.h>
#include <ctime>
using namespace std;

int rand_int(int a, int b) { return (a + rand()) % b; }

void print(int a[], int n) {
  for (int i = 0; i < n; i++)
    cout << a[i] << " ";
  cout << endl;
}
void swap(int a[], int i, int j) {
  int temp = a[i];
  a[i] = a[j];
  a[j] = temp;
}
void merge(int a[], int l, int m, int r) {
  int n = r - l + 1;
  int t[n];
  int i1 = l;
  int i2 = m + 1;
  int j = 0;
  while (i1 <= m && i2 <= r) {
    if (a[i1] < a[i2]) {
      t[j] = a[i1];
      i1++;
    } else {
      t[j] = a[i2];
      i2++;
    }
    j++;
  }
  while (i1 <= m) {
    t[j] = a[i1];
    i1++;
    j++;
  }
  while (i2 <= r) {
    t[j] = a[i2];
    i2++;
    j++;
  }
  for (j = 0; j < n; j++)
    a[l + j] = t[j];
}
void mergeSort(int a[], int l, int r) {
  if (l >= r)
    return;
  int m = (r + l) / 2;
  mergeSort(a, l, m);
  mergeSort(a, m + 1, r);
  merge(a, l, m, r);
}
void insertSort(int a[], int n) {
  int i, j, value;
  for (i = 0; i < n; i++) {
    value = a[i];
    for (j = i; j > 0 && value <= a[j - 1]; j--)
      a[j] = a[j - 1];
    a[j] = value;
  }
}
void bubbleSort(int a[], int n) {
  int i, j;
  for (i = 1; i < n; i++)
    for (j = n - 1; j >= i; j--)
      if (a[j] < a[j - 1])
        swap(a, j, j - 1);
}
void selectSort(int a[], int n) {
  int i, j, min;
  for (i = 0; i < n; i++) {
    min = i;
    for (j = i; j < n; j++)
      if (a[j] < a[min])
        min = j;
    swap(a, i, min);
  }
}
int partition1(int a[], int p, int r) {
  int i, j;
  i = p - 1; // pivot p at position l
  for (j = p; j < r; j++) {
    if (a[j] <= a[r]) {
      i++;
      swap(a, i, j);
    }
  }
  swap(a, i + 1, r);
  return (i + 1); // middle
}
int partition(int a[], int l, int r) {
  int p = a[l];
  while (l < r) {
    while (a[l] < p)
      l++;
    while (a[r] > p)
      r--;
    if (l < r)
      swap(a, l, r);
  }
  return r;
}
void quickSort(int a[], int l, int r) {
  int m;
  if (l < r) {
    cout << "partition" << endl;
    //    m = partition1(a, l, r);
    m = partition(a, l, r);
    quickSort(a, l, m - 1);
    quickSort(a, m + 1, r);
  }
}
int main() {
  //  int a[] = {49, 92, 43, 80};
  int a[10];
  srand(time(0));
  for (int i = 0; i < 10; i++)
    a[i] = rand_int(1, 100);
  print(a, 10);
  //  selectSort(a, 4);
  //  insertSort(a, 4);
  //  bubbleSort(a, 4);
  //  mergeSort(a, 0, 3);
  quickSort(a, 0, 9);
  print(a, 10);
}


//----------------------------------MayReference.cpp
//Thinking in C++ p.499
#include <iostream>
using namespace std;
int *f(int *x) { // increase via pointer
  (*x)++;
  return x;
}
int &g(int &x) { // reference via reference
  x++;
  return x;
}
void f(int &) {} // non const
void g(const int &) {} // const

void f(int **x) { (**x)++; } // increase pointer to pointer
void increment(int *&x) { x++; } // reference

int main() {
  int a = 0;
  f(&a); // increment content via pointer C using direct
  cout << "f&a " << a << endl;

  int *pa = &a; // increment content via pointer C using indirect
  f(pa);
  cout << "f(pa) " << a << endl;

  g(a); // increment content via reference &
  cout <<"g(a) "<< a << endl;

  //    f(1);  //pass to non const fail
  g(1);        //pass to const ok

  int i = 47; // content increment via address of pointer
  int *ip = &i;
  f(&ip);
  cout << i << endl;

  int *j = 0; // pointer increment via reference
  increment(j);
  cout << j << endl;
}
// Output:
//f&a 1
//f(pa) 2
//g(a) 3
//48
//0x4

//----------------------------------strcpy_memcpy.cpp
//GeeksQuiz write your own strlen
//http://stackoverflow.com/questions/2898364/strcpy-vs-memcpy
//Different between strcpy (stop at NULL) and memcpy does not
#include <iostream>
#include <string.h>
#include <stdio.h>


using namespace std;

void strlen1(char a[]){
    for (int i = 0; i < 5; i++)
        cout << a[i];
    cout << endl;
}

int main(){
    char s[5] = {'s', 'a', '\0', 'c', 'h'};
    char *str = "Hello Tom";
    string test = "this is a test";

    char str1[5];
    char str2[5];
    memset(str1, 0, 5);
    memset(str2, 0, 5);

    strcpy(str1, s);
    memcpy(str2, s, 5);

    cout << strlen(str1) << endl;
    cout << strlen(str2) << endl;
    strlen1(str1);
    strlen1(str2);

}

//----------------------------------sortfunctioncallback.cpp
//qsort.c Thinking in C++ media
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comp(const void*, const void*);

int main(){
	char const *strings[] = {"how", "now", "brown", "cow"};
	const unsigned int nstr = sizeof strings / sizeof strings[0];
	unsigned int i;
	qsort(strings, nstr, sizeof strings[0], comp);  //function callback
	for (i = 0; i < nstr ; i++)
		puts(strings[i]);
	return 0;
	//pass to qsort array of pointer, qsort pass to comp pointer to pointer to character 
}            //pointer array of elements = qsort passes pointer to pointer to character 
int comp(const void *p1, const void *p2){  //function callback
	char *a = *(char **)p1;  //actual element =  one level of indirect - content of p1 pointer to 
	char *b = *(char **)p2;
	return strcmp(a, b);
}

//----------------------------------Functor2.cpp
//home/tovantran/Ctest/Functor2.cpp --> 2015-09-27 by ./.tv  owner: tovantran
//Overload (). from bogotobogo
#include <iostream>
using namespace std;

class Functor{
	int x;
	public: 
	int operator() (int x) { return ++x; };

};

int function(int x) { return ++x;};

int main(){
  	  Functor obj;
  	  cout << obj(2) << endl;  //object
  	  //obj.operator()(2) == obj(2)
  	  cout << obj.operator()(2) << endl;
  	  cout << function(5) << endl; //function
}

//----------------------------------June1OverloadArrayOperator.cpp
//home/tovantran/Ctest/June1OverloadArrayOperator.cpp --> 2015-10-06 by ./.tv  owner: tovantran
// Overload []. from ground and up
#include <iostream>
using namespace std;
const int SIZE = 3;
class atype {
	int a[SIZE];
	public:
	atype() {
		register int i;
		for(i=0; i<SIZE; i++) a[i] = i;
	}
	int &operator[](int i) { //return value as reference
	  return a[i];
	}
};
int main()
{
	atype ob;
	cout << ob[2] << endl;  // displays 2
  ob[2] = 25; //assing 2 = 25 WRONG need &operator, [] on left of =
  int x = ob[2]; //ob[2] is 2, [] on right of =
  //error: lvalue required as left operand of assignment
  //ob[2] is an int try to assign int to int
	cout << ob[2] << endl;
	cout << ob.operator[](2) << endl;
	return 0;
}

//----------------------------------FunctionPointer1.cpp
//home/tovantran/Ctest/FunctionPointer1.cpp --> 2015-10-06 by ./.tv  owner: tovantran
//: C03:PointerToFunction.cpp 
// Defining and using a pointer to a function 
#include <iostream> 
using namespace std; 
double cm_to_inches(double cm) {
	return cm / 2.54;
}
void func() { 
	cout << "func() called..." << endl; 
} 
void show(void(*funcp)(), int a, int b){
	funcp();
}
int sum(int i, int j) { return i+j;}
int add(int(*funcp)(int, int), int i, int j ){
   return funcp(i, j);
}

int main() { 
	void (*fp)();  // Define a function pointer 
	fp = func;  // Initialize it 
//	fp = &func; // reference
	(*fp)();    // Dereferencing calls the function 
	void (*fp2)() = func;  // Define and initialize 
//	void (*fp2)() = &func;  // Define and initialize 
	(*fp2)(); 
	
	double (*fp3)(double) = cm_to_inches;
	cout << (fp3)(12.12) << endl;
	
	fp = func;
	show(fp, 1, 2);
	
	int(*fp1)(int a, int b);
 	fp1 = sum;
 	cout << add(fp1, 1,2) << endl;
// 	sum(int i, int j);
//	add(fp);
} ///:~ 

//----------------------------------struct6.c
//home/tovantran/Ctest/struct6.c --> 2015-10-06 by ./.tv  owner: tovantran
//Function pointer csbu book
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

/*struct dog {*/
/*    const char *name;*/
/*    const char *breed;*/
/*    int height;*/
/*    int weight;*/
/*};*/
/*void getDogInfo(struct dog theDog){*/
/*    printf("\n");*/
/*    printf(" Name: %s\n", theDog.name);*/
/*    printf(" Breed: %s\n", theDog.breed);*/
/*    printf(" Height: %s\n", theDog.height);*/
/*    printf(" Weight: %s\n", theDog.weight);*/
/*}*/
/*    */
struct greet_api
{
    void (*say_hello)(const char *name);
    void (*say_goodbye)(void);
};
void say_hello_fn( const char *name){
    printf("Hello %s\n", name);
}

void say_goodbye_fn(void){
  printf("Goodbye\n");
}

//struct greet_api api =  // in C
//{
//	.say_hello =say_hello_fn,
//	say_goodbye : say_goodbye_fn //: initialize
//};

struct greet_api api =  // in C++
{
    say_hello_fn,
    say_goodbye_fn //: initialize
};
//struct greet_api api =
//{
//    say_hello : say_hello_fn,
//    say_goodbye : say_goodbye_fn
//};

int f(int a)
{
  printf("test = %d\n", a);
  return 0;
}
void printhello(void(*f)(string name), string name){
    f(name);
}
void pt(string name){ //(char *name)
//    printf("%s\n", name); ????
    cout << name << endl;
}

int main(){
    const char *s = "test";
    const char s1[] = "test1"; //C
    const char *s2 = "131.90";
/*    struct dog cujo = {"Cujo","Saint Bernard", 90, 264};*/
/*    getDogInfo(cujo);*/
  int n = atoi(s2);
    printf("n :%d\n", n);
    printf("s :%s\n", s); //c -> *s
    printf("s :%s\n", s1);

    (*f)(2);
    f(3);

    api.say_hello("Tom");
    api.say_goodbye();

    struct greet_api ap = (struct greet_api)api;  //cast 
    ap.say_hello("Tim");
    ap.say_goodbye();

    struct greet_api *app = &api;
    app->say_hello("Rick");
    app->say_goodbye();

    int i = 1;
    int (*fp)(const char *, ...) = printf;
      fp ("i = %d\n", i); //same
    (*fp)("ip = %d\n", i);

    void(*fp1)(string a);  //declare
    fp1 = pt;              //initialize/reference
    printhello(fp1, "hello world");   //Dereference

    void(*fp2)(string a) = pt;
    printhello(fp2, "hello world 1");

    void(*fp3)(const string a) = pt;
    fp3("hello world 2");

    printhello(&pt, "hello world 3");
    (*f)(1); //call a function (*f)(1) == f(1)
    return 0;
}


//----------------------------------declytype.cpp
//home/tovantran/Ctest/declytype.cpp --> 2015-10-07 by ./.tv  owner: tovantran 
//C++ Without Fear
#include <stdio.h>
#include <iostream>
using namespace std;

int main(){
	int i = 4;
	float f;
	decltype(i) j = i * 2.2;
	decltype(f) g = i * 2.2;
	cout << j << endl;
	cout << g << endl;
}
//Compiling  /home/tovantran/Ctest/declytype.cpp
//declytype.cpp
//declytype
//8
//8.8

//Done.
//----------------------------------Dec4OverloadOperator.cpp
// http://www.tutorialspoint.com/cplusplus/cpp_overloading.htm
//home/tovantran/Ctest/Dec4OverloadOperator.cpp --> 2015-12-04 by ./.tv  owner: tovantran

#include <iostream>
#include <vector>
#include <limits>

using namespace std;

template <typename T>
class Box
{
  T m_width;
  T m_height;
  std::vector<T> vec;
  public:
  Box operator+(Box b) 
  {
      Box box;
      box.m_width = this->m_width + b.m_width;
      box.m_height = this->m_height + b.m_height;
      return box;
  }
  Box(){};
  Box(T width, T height) : m_width(width), m_height(height) {}
  
  T getwidth() { return m_width; }
  T getheight() { return m_height; }
};

int main()
{
  Box<float> box1(2.3, 3.5);
  Box<float>  box2(5.5, 6.8);
  Box<float> box = box1 + box2;
  cout << fixed  << box.getwidth() << endl;
  cout << box.getheight() << endl;  
}
//----------------------------------Dec4OverloadOperator1.cpp
// http://www.tutorialspoint.com/cplusplus/cpp_overloading.htm
//home/tovantran/Ctest/Dec4OverloadOperator1.cpp --> 2015-12-04 by ./.tv  owner: tovantran

#include <iostream>
#include <vector>
#include <limits>

using namespace std;
const int SIZE = 3; /* height, width, lenght */

template <typename T>
class Box
{
  
  std::vector<T> m_vec;  //no size vec(2) initiate in ctor
  public:
  
  Box operator+(Box& b) 
  {
      Box box;
      box.m_vec[0] = this->m_vec[0] + b.m_vec[0];
      box.m_vec[1] = this->m_vec[1] + b.m_vec[1];
      box.m_vec[2] = this->m_vec[2] + b.m_vec[2];
      return box;
  }
  Box(T height, T width, T lenght) : m_vec(SIZE) //vector size in ctor
  { 
    m_vec[0] = height;
    m_vec[1] = width;
    m_vec[2] = lenght;
  } 
  Box() : m_vec(SIZE) { cout <<"Ctor" << endl;};
  void showBox(Box box)
  {
    cout << "height = "<< box.m_vec[0] << endl;
    cout << "wodth = "<< box.m_vec[1] << endl;
    cout << "lenght = "<< box.m_vec[2] << endl;
  }
};

int main()
{
  // vector<int> v(2);
  Box<int> box1(1, 2, 3);
  Box<int> box2(3, 4, 5);
  Box<int> box = box1 + box2;
  box.showBox(box);
  
  // cout << box.m_vec[0] << endl;  //m_vec is private
  // cout << box.m_vec[1] << endl; 
  // cout << box.m_vec[2] << endl;
}
// http://stackoverflow.com/questions/1657883/variable-number-of-arguments-in-c
//home/tovantran/Ctest/Dec4DynamicArguments.cpp --> 2015-12-08 by ./.tv  owner: tovantran

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

template <class T>
class Box 
{
  vector<T> m_vec;
  int size;
  public:
  Box operator+(Box& b)
  {
      Box box(this->size);  //ctor: set vector size to write in otherwise use push_back
      for (int i = 0; i < this->size; i++)
      {
        box.m_vec[i] = this->m_vec[i] + b.m_vec[i];
      }
    
      box.size = this->size; //set lenght for this vector
      return box;
  }
  Box(vector<T> vec)
  {
      cout << "Ctor" << endl;
     int i = 0;
     for(typename vector<T>::iterator iter = vec.begin(); iter != vec.end(); ++iter, i++)
     {
         m_vec.push_back(*iter);
     }
     size = i;
  }
  Box(int size) : m_vec(size) { cout <<"Default Ctor "<< size << endl; }
  void showBox()
  {
    for_each(begin(m_vec), end(m_vec),[](T x) { //lambda
        cout << setprecision(4) << x << " ";
    });
    cout << endl;
  }
  ~Box() { cout << "Dtor" << endl; }
  int getsize() { return size; }
};

template <typename D>
void test()
{
    vector<D> v = {10.55, 20, 30, 40, 45, 101, 12, 111, 1, 2, 3, 4};
    vector<D> v1 = {11, 22, 33, 44, 55, 99, 14, 1};
   
    Box<D> box1(v);
    Box<D> box2(v1);
    Box<D> box(v.size()); //why cab't Box<int> box = box1 + box2
    box = box1 + box2;
    cout << box.getsize() << endl;
    box.showBox();
}

int main()
{
   test<float>();  //change type just one.
   return 0;
}

//----------------------------------Dec13FunctorVirtualFunction.cpp
// http://www.cprogramming.com/tutorial/functors-function-objects-in-c++.html
//http://stackoverflow.com/questions/1955074/virtual-methods-or-function-pointers
//Keywords: Functor, virtual function , function pointer, overload, overidde
//home/tovantran/Ctest/Dec13FunctorVirtualFunction.cpp --> 2015-12-13 by ./.tv  owner: tovantran

#include <iostream>
using namespace std;


class MathComputer    //virtual function + Functor operator()
{
    public:
    virtual int computerResult(int x, int y) = 0;  //Virtual function (Overload at run time)
    int operator()(int x, int y)
    { 
		  cout << "Function obj or Functor " << endl;
		  return x * y; 
    }  //Functor
    int add() { }        // Override at compile time
};

class MathComputerDerived : public MathComputer
{
public:
  int computerResult(int x, int y)
  {
      cout << "Override Virtual Function at run time" << endl;
      return (x + y);
  }  
  int add(int x, int y) 
  {
  cout << "Overload function in base class at compile time" << endl;
  return x + y;
  }
};

                     //function pointer
int sum(int i, int j) { return i + j; }

template <typename Functype>  //template function
int doMath (int x, int y, Functype func )
{
    cout << "Function pointer template " << endl;
    return func(x, y);
}

int add(int(*funcptr)(int, int), int i, int j)
{
    cout << "Function pointer " << endl;
    return funcptr(i, j);    
}
int main()
{
    int (*fp1)(int a, int b);
    fp1 = sum;       
    cout << doMath(1, 2, fp1) << endl;  //function pointer
    cout << add(fp1, 1, 2) << endl;
    
    MathComputerDerived mc;  //virtual function in derived class (Overload at run time)
    cout << "Override virtual function from derived class = " << mc.computerResult(1, 2) << endl;
    cout << "Overload function " << mc.add(3, 4) << endl; //overload function at compile time
    MathComputer *m = &mc;  //virtual function in based class
    cout << "Override virtual function from based class = " << m->computerResult(2, 3) << endl;
    
    cout << "Function object or Functor = " << mc(9, 2) << endl;  //functor
    
}
//----------------------------------Dec9ModernC.cpp
//Modern C++ youtube.com A tour of Modern C++
//home/tovantran/Ctest/Dec9ModernC.cpp --> 2015-12-14 by ./.tv  owner: tovantran

#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
#include <functional> //function
using namespace std;

struct Address
{

};

struct Person{  //own type not build in type
    string name;
    int age;
    Address address;
public:
    explicit Person(const Address& address) : address(address){}
    explicit Person(const string name, const int age):
    name(name), age(age){}
};

struct Exchange
{
    int count;
    float rates[2];
    Exchange(initializer_list<float> r)
    {
        if (r.size() < 2) return;
        auto i = r.begin();
        rates[0] = *i;
        i++;
        rates[1] = *i;
    }
};

template<typename T, typename U>
auto add(T t, U u) //->decltype(t+u)
{
    return t + u;
}

auto meaning_of_life() //->int
{
    return 42;
}

class Animal
{
protected:
    int legs = 4; //old C++ const int legs
public:
    explicit Animal(int legs) : legs(legs) {}
    virtual int walk(int steps)
    {
        return steps * 20;
    }
};

class Human : public Animal
{
 public:
    Human() : Animal(2) {}   //derived from Animal calls base ctor ****
//    Human(const Human&) = delete; //avoid generate automatic
//    int walk(int steps) override;
    int walk(int steps)
    {
        return steps * 10;
    }
};

int main()
{
    {
        vector<int> scores {8, 2, 4, 3};
        for_each(begin(scores), end(scores), []( int n) -> float
        {
            cout << n << endl;
            return n;
        });
        int zero = 0;
        auto is_positive = [zero](int n){ return n > zero; };
        cout << boolalpha << is_positive(2) << endl;
    }
//    auto fib = [&fib](int x) { return x < 2 ? 1 : fib(x -1) + fix(x - 2); };
    function<int(int)> fib = [&fib](int x) { return x < 2 ? 1 : fib(x -1) + fib(x - 2); };
    Human h;
    Human h2{ h };
    cout << "walk = " << h2.walk(1) << endl;

    Exchange e{10, 2, 3};  //legal value 1 assign to count and 2, 3 to rates
    Exchange e1{100.10, 200.20};    //count  == 1 and 1st element of array == 2
    cout << e1.count << " " << e1.rates[0] << " " << e1.rates[1] << endl;

    cout << add(2, 2.5) << endl;
    cout << add(string("Hello, "), "world") << endl; //string + char

    vector<double> value;
    typedef decltype(value.begin()) dvi;
    typedef decltype(42) myint;
//    myint = 1; //FAIL expected unqualified id before = token but it is ok myint(1)
    cout << "myint =" << myint(1) << endl;
    typedef decltype(add(2, 2.5)) qtype;
    cout << qtype(2222) << endl;

    int a = 1;
    int n{4}; //more powerful easy to initialize type
    string s{ "foo" };

    vector<int> values = {1, 2, 3};

    vector<int> values0;
    values0.push_back(1);

    vector<int> values1{1, 2, 3};  //new modern

    // map<string, string> capitals = {  OK without operator =
    map<string, string> capitals {
      {"UK", "London"}
    };
    Person p{"tom", 12};

    Person person(Address());  //like function
    Person person1{Address()}; // uniform initialization  this is constructor
    {
        auto a = 12.11;
        auto c =  "hello";
        auto d = { 1, 2, 3 };
        cout << a << endl;
        decltype(a) x = 2;


        map<string, vector<double>> ticks;
        auto itt = ticks.begin();

        map<string, vector<double>>::iterator it = ticks.begin();

        cout << meaning_of_life() << endl;
    }

}
 // Youtube lambda expression in  C++ Bradley Needham
 //home/tovantran/Ctest/Dec8LamdaReview.cpp --> 2015-12-14 by ./.tv  owner: tovantran

 #include <iostream>
 #include <vector>
 #include <algorithm>  //count_if
 #include <iomanip>
 using namespace std;
 
 struct isOdd
 {
     bool operator()(int x)  //no ctor use default ctor 
     {
         return x % 2;
     }
 };
 bool isEven( int x)
 {
 		return !(x % 2);
 }
class isMultipleOf
{
	int m_multi;
public:
	isMultipleOf(int multi) : m_multi(multi) {}
	bool operator()(int x)
	{
		return !(x % m_multi);
	}
};
class SumUp
{
	int &m_sum;
public:
  SumUp(int &sum) : m_sum(sum) {}
  void operator()(int x) { m_sum += x; }
	
};
int main()
{
 
 vector<int> col = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 15, 25};
 {
 isOdd isodd;
 cout << (isodd.operator()(3) ? "Odd" : "Even") << endl;   //Don't forget parathenses bracket
 cout << (isodd(3) ? "Odd" : "Even") << endl;   //Don't forget parathenses bracket
 size_t c = count_if(col.begin(), col.end(), isOdd());  //default ctor + ()
 size_t c1 = count_if(col.begin(), col.end(), isEven);  //using function
 cout << "Integers that are odd: " << c << " and Even: "<< c1 << endl;
 }
 int multi = 2;
 {
 size_t c = count_if(col.begin(), col.end(), [](int x){ return !(x % 2); }); 
 cout << "Integers that are even: " << c << endl; 
 }
 {
 size_t c = count_if(col.begin(), col.end(), isMultipleOf(multi) ); 
 cout << "Integers that are multiple of: " << c << endl; 
 }
 {
 size_t c = count_if(col.begin(), col.end(), [multi](int x){ return !(x % multi); } ); //capture multi
 cout << "Integers that are multiple of: " << c << endl; 
 }
 {
 size_t c = count_if(col.begin(), col.end(), [=](int x){ return !(x % multi); } ); //capture multi
 cout << "Integers that are multiple of: " << c << endl; 
 }
 {
 int sum = 0;
 for_each(col.begin(), col.end(), SumUp(sum) ); //capture multi
 cout << "Sum1 is: " << sum << endl; 
 } //end of scope so variable can be resused
 {
 int sum = 0;
 int *sum1 = &sum;
 for_each(col.begin(), col.end(), [&sum](int x) { sum += x; } ); //capture sum by value is copy from sum 
 cout << "Sum2 is: " << sum << endl; 														//problem
 }
 {
 int sum = 0;
 for_each(col.begin(), col.end(), [=](int x) mutable { sum += x; } ); //capture sum by value is copy from sum 
 cout << "Sum3 is: " << sum << endl; 
 }
 {
 size_t c;
 c = count_if(col.begin(), col.end(), [](int x) ->bool   //landa more then 1 line specify return type ->
	 { 
	 	bool odd = x % 2;
	 	cout << x << " is " << (odd ? "odd" : "even") << endl;
	 	return odd; 
	 } 
 ); //capture sum by value is copy from sum 
 cout << "Number of odd integers " << c << endl;  //from ->bool
 }
 { //call lambda to print
 double x = 12.12;
 cout << [&x]() -> double { return x * 2; }() << endl;  //return type if many line in lambda
 cout << setprecision(4) << x * 2 << endl;
 }
 return 0;
} 
//Bartosz Milewski youtube C++ Concurrency Part 1
//home/tovantran/Ctest/k_r/thread/thread.cpp --> 2015-11-10 by ./.tv  owner: tovantran

#include <iostream>
#include <thread>

void threadFunction()
{
	std::cout << "Hello From Worker Thread ! \n"; //Worker thread 
}

int main()
{
	std::thread th(&threadFunction);
	std::cout << "Hello World From Main \n";
  th.join();
  return 0;
}	
//Bartosz Milewski youtube C++ Concurrency Part 1
//home/tovantran/Ctest/k_r/thread/thread.cpp --> 2015-11-10 by ./.tv  owner: tovantran

//Bartosz Milewski youtube C++ Concurrency Part 2
#include <iostream>
#include <thread>
#include <vector>
#include <algorithm> //for_each
#include <unistd.h> //sleep(1)
//#include <Windows.h>

//void threadFunction(std::thread &th)
//{
//		th.join();
//}

int main()
{
	std::vector<std::thread> workers;
	for (int i = 0; i < 10; i++)
	{
		workers.push_back(std::thread([i]()  //construct a thread called ctor
		{
			std::cout << "Hello From Thread ! Index " << i <<  "\n"; //Worker thread define inline  / parallelism then join (task/thread base program)
																//non determinism in concurrency program very clear from video 
			std::cout << std::this_thread::get_id() << "\n";
		}));
		
	}
	sleep(2);
	std::cout << "Hello World From Main \n";
	//Sleep(2000);
	std::for_each(workers.begin(), workers.end(), [](std::thread &th)  //lambda replace threadFunction
	{
		th.join();
	});
	return 0;
}	

//Bartosz Milewski youtube C++ Concurrency Part 1
//home/tovantran/Ctest/k_r/thread/thread3.cpp --> 2015-12-14 by ./.tv  owner: tovantran

//#include "stdafx.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <list>
#include <algorithm>
using namespace std;

//worker thread
void toSin(list<double>&& list)  //rvalue reference move segmentics
{
    //this_thread::sleep_for(chrono::seconds(1));
    for_each(list.begin(), list.end(), [](double & x)
    {
        x = sin(x);
    });

    for_each(list.begin(), list.end(), [](double & x)
    {
        int count = static_cast<int>(10*x+10.5);
        for (int i=0; i<count; ++i)
        {
            cout.put('*');
        }
        cout << endl;
    });
}    

//int _tmain(int argc, _TCHAR* argv[])
int main()
{
    list<double> list;

    const double pi = 3.1415926;
    const double epsilon = 0.00000001;
    for (double x = 0.0; x<2*pi+epsilon; x+=pi/16)
    {
        list.push_back(x);
    }

    thread th(&toSin, /*std::ref(list)*/std::move(list)); //list has been moved from main to worker 
    th.join();    

    return 0;
}
// http://www.bogotobogo.com/cplusplus/C11/1_C11_creating_thread.php 
// Not Working need change move segmentic &&
//home/tovantran/Ctest/k_r/thread/thread2_1.cpp --> 2015-12-14 by ./.tv  owner: tovantran
#include <iostream>
#include <thread>
#include <string>
#include <unistd.h> //sleep(1)

using namespace std;
//void thread_function(string s)    //pass by value
// void thread_function(string& s)  //pass by ref
void thread_function(string&& s)    //move segmentic take rvalue reference &&
{
    cout << "Thread function:  " << s << endl;
    s = "Hello from Main...";
}

int main()
{
    string s = "Hello from Thread";
    // thread t(&thread_function, "Hello from thread ");  //passing string to thread function
    // thread t(&thread_function, ref(s));
    thread t(&thread_function, move(s));
    sleep(2);  //wait for s string change from thread function
    cout << "Main thread: " << s << " ID " << this_thread::get_id() << " " << t.get_id()<< endl;
    cout << thread::hardware_concurrency() << endl;
    t.join();
    
    return 0;
}

//http://stackoverflow.com/questions/31417389/use-member-function-for-stdthread-with-stdrefthis-fails-to-compile
//home/tovantran/Ctest/k_r/thread/Dec11ClassThread.cpp --> 2015-12-14 by ./.tv  owner: tovantran

#include <thread>
#include <iostream>
using namespace std;
class Worker
{
public:
  // Worker() : m_worker(&Worker::doWork, std::ref(*this), 1) {}
  // std::string s = "Hello from Thread";
  Worker(string a) : m_worker(&Worker::doWork, this, a) {}
  std::thread m_worker;

  void doWork(string a) { std::cout << a << std::endl; }
};

int main(int argc, char* argv[]) {
  Worker k("Hello World");
  k.m_worker.join();  //terminate called without an active exception forget to join main thread. exception forget to join
}

// http://stackoverflow.com/questions/19278424/what-is-a-callable-object-in-c
//Funcallable is functor
//home/tovantran/Ctest/k_r/thread/Dec11ClassThreadCallable.cpp --> 2015-12-14 by ./.tv  owner: tovantran

#include <thread>
#include <iostream>
#include <boost/thread.hpp>
using namespace std;

class CallableClass
{
private:
    // Number of iterations
    int m_iterations;

public:

    // Default constructor
    CallableClass()
    {
        m_iterations=10;
    }

    // Constructor with number of iterations
    CallableClass(int iterations)
    {
        m_iterations=iterations;
    }

    // Copy constructor
    CallableClass(const CallableClass& source)
    {
        m_iterations=source.m_iterations;
    }

    // Destructor
    ~CallableClass()
    {
    }

    // Assignment operator
    CallableClass& operator = (const CallableClass& source)
    {
        m_iterations=source.m_iterations;
        return *this;
    }

    // Static function called by thread
    static void StaticFunction()
    {
        for (int i=0; i < 10; i++)  // Hard-coded upper limit
        {
            cout<<i<<"Do something in parallel (Static function)."<<endl;
            boost::this_thread::yield(); // 'yield' discussed in section 18.6
        }
    }

    // Operator() called by the thread
    void operator () (int x)
    {
        for (int i=0; i<m_iterations; i++)
        {
            cout<<i<<" - Do something in parallel (operator() ). " << x <<endl;
             boost::this_thread::yield(); // 'yield' discussed in section 18.6
        }
    }

};

int main()
{
  CallableClass obj;
  obj(111);  
}
//----------------------------------Dec10Tuples.cpp
// http://en.cppreference.com/w/cpp/utility/tuple
//home/tovantran/Ctest/Dec10Tuples.cpp --> 2015-12-14 by ./.tv  owner: tovantran
//A tuple is an object capable to hold a collection of elements. 
// Each element can be of a different type.

#include <tuple>
#include <iostream>
#include <string>
#include <stdexcept>
 
std::tuple<double, char, std::string> get_student(int id)
{
    if (id == 0) return std::make_tuple(3.8, 'A', "Lisa Simpson");
    if (id == 1) return std::make_tuple(2.9, 'C', "Milhouse Van Houten");
    if (id == 2) return std::make_tuple(1.7, 'D', "Ralph Wiggum");
    if (id == 3) return std::make_tuple(1.2, 'F', "Tom Tran");
    throw std::invalid_argument("id");
}
 
int main()
{
    auto student0 = get_student(0);
    std::cout << "ID: 0, "
              << "GPA: " << std::get<0>(student0) << ", "
              << "grade: " << std::get<1>(student0) << ", "
              << "name: " << std::get<2>(student0) << '\n';
              
    auto student3 = get_student(3);
     std::cout << "ID: 3, "
              << "GPA: " << std::get<0>(student3) << ", "
              << "grade: " << std::get<1>(student3) << ", "
              << "name: " << std::get<2>(student3) << '\n';
 
    double gpa1;
    char grade1;
    std::string name1;
    std::tie(gpa1, grade1, name1) = get_student(1);
    std::cout << "ID: 1, "
              << "GPA: " << gpa1 << ", "
              << "grade: " << grade1 << ", "
              << "name: " << name1 << '\n';
    
    double gpa3;
    char grade3;
    std::string name3;
    std::tie(gpa3, grade3, name3) = get_student(3);
    
    std::cout << "ID: 3, "
              << "GPA: " << gpa3 << ", "
              << "grade: " << grade3 << ", "
              << "name: " << name3 << '\n';
}
//----------------------------------Dec7DynamicArguments.cpp
//home/tovantran/Ctest/Dec7DynamicArguments.cpp --> 2015-12-14 by ./.tv  owner: tovantran

#include <iostream>
#include <string>
#include <initializer_list>

template <typename T>
void func(T t) 
{
    std::cout << t << std::endl ;
    std::cout << t << std::endl ;
}

template<typename T, typename... Args>
void func(T t, Args... args) // recursive variadic function
{
    std::cout << t <<std::endl ;

    func(args...) ;
}

template <class T>
void func2( std::initializer_list<T> list )
{
    for( auto elem : list )
    {
        std::cout << elem << std::endl ;
    }
}

int main()
{
    std::string
        str1( "Hello" ),
        str2( "world" );

    func(1,2.5,'a',str1,'b');

    func2( {10, 20, 30, 40 , 100, 299}) ;
    func2( {str1, str2 } ) ;
} 
//----------------------------------Dec4DynamicArguments.cpp
// http://stackoverflow.com/questions/1657883/variable-number-of-arguments-in-c
//home/tovantran/Ctest/Dec4DynamicArguments.cpp --> 2015-12-08 by ./.tv  owner: tovantran

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

template <class T>
class Box 
{
  vector<T> m_vec;
  int size;
  public:
  Box operator+(Box& b)
  {
      Box box(this->size);  //ctor: set vector size to write in otherwise use push_back
      for (int i = 0; i < this->size; i++)
      {
        box.m_vec[i] = this->m_vec[i] + b.m_vec[i];
      }
    
      box.size = this->size; //set lenght for this vector
      return box;
  }
  Box(vector<T> vec)
  {
      cout << "Ctor" << endl;
     int i = 0;
     for(typename vector<T>::iterator iter = vec.begin(); iter != vec.end(); ++iter, i++)
     {
         m_vec.push_back(*iter);
     }
     size = i;
  }
  Box(int size) : m_vec(size) { cout <<"Default Ctor "<< size << endl; }
  void showBox()
  {
    for_each(begin(m_vec), end(m_vec),[](T x) { //lambda
        cout << setprecision(4) << x << " ";
    });
    cout << endl;
  }
  ~Box() { cout << "Dtor" << endl; }
  int getsize() { return size; }
};

template <typename D>
void test()
{
    vector<D> v = {10.55, 20, 30, 40, 45, 101, 12, 111, 1, 2, 3, 4};
    vector<D> v1 = {11, 22, 33, 44, 55, 99, 14, 1};
   
    Box<D> box1(v);
    Box<D> box2(v1);
    Box<D> box(v.size()); //why cab't Box<int> box = box1 + box2
    box = box1 + box2;
    cout << box.getsize() << endl;
    box.showBox();
}

int main()
{
   test<float>();  //change type just one.
   return 0;
}
//----------------------------------Nov29SmartPointerReview.cpp
// home/tovantran/Ctest/smartpointerQC.cpp --> 2014-06-22 by ./.tv  owner:
// Youtube video Dive into C++11
// http://www.codeproject.com/Articles/15351/Implementing-a-simple-smart-pointer-in-c
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <string>
#include <memory> //unique_ptr
using namespace std;
 //ownership smart pointer
    struct Resource {};
    void passByValue(unique_ptr<Resource> mResPtr){}
    void passByConstRef(const unique_ptr<Resource>& mResPtr){}
    void passByRawPtr(Resource* mResPtr){}
void whatShouldIPassByToMaintainOriginalOwership()
{
    unique_ptr<Resource> resPtr{new Resource}; //ownership is resPtr
//    passByValue(resPtr); //unique pointer cannot copy
    passByConstRef(resPtr); //OK
    passByRawPtr(resPtr.get()); //OK
}
void iHaveToTransferOwnershipWhatNow() //move semantics transfer ownership
{                                      //move ownership
    unique_ptr<Resource> resPtr(new Resource);
    {
        string source{"Hello"};
        string target{move(source)};  //source->target move semantics
    }
    std::unique_ptr<Resource> newOwner{std::move(resPtr)};
    passByValue(std::move(newOwner));
}

struct Resource1{};         //share resources expensive to copy so share

struct NaiveGameEffect
{
    Resource animation;     //expensive move or copy a lot to copy
    Resource backgroundTexture;
    Resource particleTexture;
    Resource sound;
};

struct GameEffect //share the resources gameEffect owner but sharing
{
    std::shared_ptr<Resource> animation; //object alive share pointer alive
    shared_ptr<Resource> backgroundTexture;
    shared_ptr<Resource> particleTexture;
    shared_ptr<Resource> sound;
};

class FreeStorePoint {
public:
  FreeStorePoint(int *mInt) : pointer{mInt}
  {
    cout << "Ctor FreeStorePointer" << endl;
  }
  ~FreeStorePoint() {
    cout << "Dtor FreeStorePointer" << endl;
    delete pointer;
  }
  int *get() { return pointer; }

  int *getPointer() const;
  void setPointer(int *value);

private:
  int *pointer;  //pointer to object (points to our free-store-allocated 'int'
};
int *FreeStorePoint::getPointer() const { return pointer; }

void FreeStorePoint::setPointer(int *value) { pointer = value; }

class Person
{
	const char *m_name;
	int m_age;
public:
	Person() : m_name(0), m_age(0){ cout << "Empty Person CTOR" << endl; } 
	Person(const char *name, int age) : m_name(name), m_age(age){ cout << "PERSON CTOR" << endl;}
	~Person(){ cout << "Person DTOR" << endl; }
	void display() { printf("%s %d\n", m_name, m_age );}
};

template <typename T>
class SP : public Person
{
	T *pData;
public:
	SP(T *pValue) : pData(pValue){ cout << "SP CTOR" << endl; }
	~SP(){ delete pData; cout << "SP DTOR" << endl; }
	T& operator *() { return *pData;}
	T* operator->() { return pData; }
};

int main()
{
	SP<Person> p = SP<Person>(new Person("Scott", 25));
	SP<Person> p1(new Person("Thomas", 35));
	p->display();
	// p1->display();
}

int main(int argc, char *argv[]) {
  char msg[] = "Scott";
  char *msg1 =
      (char *)"Scott"; // warning: deprecated conversion from string constant
  string msg2 = "Scott";
  SP<Person> p(new Person{
      "Scott", 25}); // warning: deprecated conversion from string constant
                     //    SP<Person> p(new Person(msg1, 25)); //OK
  p->Display(); //OR below //need *operator->
  p.operator *().Display(); //need &operator*
  p.operator ->().Diplay(); //Do nothing
  	SP<Person> p = SP<Person>(new Person("Scott", 25));
	SP<Person> p1(new Person("Thomas", 35));
	p->display();
  // Dont need to delete Person pointer..
  // Dont need to delete Person pointer..
  {
      FreeStorePoint test = new int(10);
      FreeStorePoint test1(new int(11)); //same as above
      cout << *(test.getPointer()) << endl; //not test.getPointer()
//      FreeStorePoint *p = new int(10); //pass pointer to ctor
                                     //cannot convert int* to FreeStorePoint*
      std::unique_ptr<int> test2(new int(10)); //generic
  } //Out of scope
  {
      unique_ptr<double> smartPointers{new double{20.3}};
      unique_ptr<string> are {new string{"extremely"}};
      unique_ptr<char> versatile{new char{'!'}};
  }
  {
      size_t runtimeSize(10);
      unique_ptr<int[]> array{new int[runtimeSize]};
      auto pointertoArray(array.get()); //raw pointer
  }
  {
      string testString{"This string is not on the free store"}; //stack
      string* pointerToString(&testString); //raw pointer
  } //out of scope stack delete
  struct TextureResource
  {
      TextureResource() { cout << "Ctor TextureResource" << endl; }
      ~TextureResource() {cout << "Dtor TextureResource" << endl; }
      //Non-copyable(using C++11's new = 'delete' feature)
      TextureResource(const TextureResource&) = delete;
      TextureResource& operator=(const TextureResource&) = delete;
  };//no allocation and dellocation slows down the game
  shared_ptr<TextureResource> source(new TextureResource); //share pointer increment 1
  struct TextureObject
  {
      shared_ptr<TextureResource> texture;
  };
  {
      TextureObject to1;
      to1.texture = source;  //share pointer increment 2
  }//out of scope share pointer increment back to 1
  {
      TextureObject to2; to2.texture = source; //TextureObject
      TextureObject to3; to3.texture = source; // is shared by
      TextureObject to4; to4.texture = source; // all objects
      TextureObject to5; to5.texture = source; // to2 - to6
      TextureObject to6; to6.texture = source;
  }
  std::shared_ptr<TextureResource> newOwner{source}; //share ownership count = 2
  source.reset(); //share pointer increase (not abuse) run time operator
  return 0;
}

//----------------------------------Jan14OstreamSum.cpp
//home/tovantran/Ctest/Jan14OstreamSum.cpp --> 2016-03-03 by ./.tv  owner: tovantran
//friend ostream
#include <iostream>
using namespace std;

class Three
{
    string *m_ob;
    int m_x, m_y, m_z;
public:
    Three(){}
    Three(string ob, int x, int y, int z): m_ob(new string(ob)), m_x(x), m_y(y), m_z(z) {}
    Three &operator+(Three &t)
    {
        static Three th;
        th.m_ob = new string("Sum object");
        
        th.m_x = this->m_x + t.m_x;
        th.m_y = this->m_y + t.m_y;
        th.m_z = this->m_z + t.m_z;
        return th; //create in stack gone when return
    }

    friend ostream &operator<< (ostream &stream, Three t)
    {
        stream << *t.m_ob <<": ",
        stream << t.m_x << ",";
        stream << t.m_y << ",";
        stream << t.m_z << "\n";
        return stream;
    }
};	

int main()
{
    Three ob1("ob1", 1, 2, 3), ob2("ob2", 4, 5, 6), ob3("ob3", 7, 8, 9);
    cout << ob1 << ob2 << ob3 << endl;
    Three ob = ob1 + ob2 + ob3;
    cout << ob << endl;
}

//----------------------------------Mar7OutInner.java
class Mar7OutInner {
	public static void main(String[] args) {	
		System.out.println("Outer");
		InnerClass t = new InnerClass();
		t.inner_print();
	}
	static class InnerClass {	
		public void inner_print() {
			System.out.println("Inner");
		}
	};
};

 class Mar7OutInner {
 	public static void main(String[] args) {	
 		System.out.println("Outer");
 //	  Mar7OutInner o = new Mar7OutInner();
 //		InnerClass inner = o.new InnerClass();
 		Mar7OutInner.InnerClass ob = new Mar7OutInner.InnerClass();
 		ob.inner_print();
 	}
 	static class InnerClass {	
 		public void inner_print() {
 			System.out.println("Inner");
 		}
 	};
 };
//----------------------------------/home/tovantran/Ctest/CtorDtor.cpp
//----------------------/home/tovantran/Ctest/CtorDtor.cpp

#include <iostream>
#include <stdlib.h>
using namespace std;

// class Base {
// 	public:
// 		Base() { cout << "Base constuctor - created " << endl;}
// 		virtual ~Base() {cout << "Base destructor - destroyed " << endl;}
// 		void print() {cout << "Print" << endl;}
// };
// class Derived : public Base {
// 	public:
// 		Derived() {cout << "Derived constuctor created\n";}
// 		~Derived () {cout << "Derived destructor - destroyed\n";}
// };		
// int main(int argc, char *argv[])
// {
// 	Derived d1;					//create in stack
// 	Derived(d2);
	
// }
	
class A
{
public:
	A(){ cout << "Base ctor" << endl; fn();  }
	virtual void fn() {  cout << "base fn()" << endl; _n = 1;}
	int getn() { return _n; }
	friend class B;  //class B is my friend now can see my private part 
private:
	int _n;
};

class B : public A
{
public:
	B() : A() { cout << "Derived ctor" << endl; fn(); }
	virtual void fn() { cout << "derived fn()" << endl;  _n = 2;}
	int getn() { return _n; } //function overridden 
// private:
	// int _n;   //use base class _n
};

int main()
{
	B b;
	int n = b.getn();  //access _n of base class need to be frienf class
	cout << n << endl;
}

//----------------------------------CtorDtor.cpp
//----------------------/home/tovantran/Ctest/CtorDtor.cpp

#include <iostream>
#include <stdlib.h>
using namespace std;

// class Base {
// 	public:
// 		Base() { cout << "Base constuctor - created " << endl;}
// 		virtual ~Base() {cout << "Base destructor - destroyed " << endl;}
// 		void print() {cout << "Print" << endl;}
// };
// class Derived : public Base {
// 	public:
// 		Derived() {cout << "Derived constuctor created\n";}
// 		~Derived () {cout << "Derived destructor - destroyed\n";}
// };		
// int main(int argc, char *argv[])
// {
// 	Derived d1;					//create in stack
// 	Derived(d2);
	
// }
	
class A
{
public:
	A(){ cout << "Base ctor" << endl; fn();  }
	virtual void fn() {  cout << "base fn()" << endl; _n = 1;}
	int getn() { return _n; }
	friend class B;  //class B is my friend now can see my private part 
private:
	int _n;
};

class B : public A
{
public:
	B() : A() { cout << "Derived ctor" << endl; fn(); }
	virtual void fn() { cout << "derived fn()" << endl;  _n = 2;}
	int getn() { return _n; } //function overridden 
// private:
	// int _n;   //use base class _n
};

int main()
{
	B b;
	int n = b.getn();  //access _n of base class need to be frienf class
	cout << n << endl;
}

//love_C
//----------------------/home/tovantran/Ctest/checkprime.c
#include <stdio.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;

template <typename T>
struct isPrime
{
	bool operator()(T n) 
	{ 
		bool flag = 0;
		cout << n << " ";
		for (int i = 2; i <= n/2; i++ )
		{
			if (n % i == 0)
			{
				flag = 1;
				break;
			}
		}
		printf("%s\n", flag == 0 ? "prime" : "not prime");
		return !flag;
	}
	
};
bool checkprime(int n)
{
  int flag = 0;
  for (int i = 2; i <= n/2 ; i++)
  {
    printf("%d\n", i);
    if (n % i == 0)
    {
      flag = 1;
      break;
  	}
  }
  printf("%s\n", flag == 0 ? "prime" : "not prime");
  return flag;
}

int main()
{
	vector<int> vec = { 1, 2, 13, 4, 5, 6, 7, 8, 9, 17};
	size_t c = count_if(vec.begin(), vec.end(), isPrime<int>());
	cout << "number of prime in vector : " << c << endl;
	// checkprime(7);
	// isPrime<int> isprime;
	// isprime.operator()(15);
	// isprime(4);

	// cout << boolalpha << checkprime(13) << endl;

}


}//----------------------------------April6Test.cpp
#include <iostream>
using namespace std;

class Base
{
   Base(){}
   ~Base(){}	
};

class Derived
{
   Derived(){}
   ~Derived(){}	
};

class All : public Base, public Derived
{
   All(){}
   ~All(){}	
};

int main()
{
	
}//----------------------------------April6Test.cpp
#include <iostream>
using namespace std;

class Base
{
public:
   Base(){ cout << "Base" << endl;}
   ~Base(){}	
};

class Derived : virtual public Base
{
public:
   Derived(){ cout << "Derived" << endl; }
   ~Derived(){}	
};

class Derived1 : virtual public Base
{
public:
	Derived1(){ cout << "Derived1" << endl;}
	~Derived1(){}	
};


class All : public Derived, public Derived1
{
public:
   All(){}
   ~All(){}	
};


int main()
{
	All a;
}//----------------------------------PureVirtualDesctructor.cpp
//----------------------/home/tovantran/Ctest/PureVirtualDesctructor.cpp
//http://www.geeksforgeeks.org/pure-virtual-destructor-c/
#include <iostream>
using namespace std;
//Class has pure virtual destructor is also called Abstract class
class Base
{
public:
	Base() { cout << "Base ctor" << endl; }
    virtual ~Base()=0; // Pure virtual destructor
	// virtual ~Base() { cout << "Pure virtual destructor is called" << endl;}
};
Base::~Base()
{
    cout << "Pure virtual destructor is called" << endl;
}
class Derived : public Base
{
public:
	Derived() { cout << "Derived ctor" << endl; }
    ~Derived()
    {
        std::cout << "~Derived() is executed" << endl;
    }
};
 
int main()
{
    Base *b=new Derived();
    delete b;
    return 0;
}
//----------------------/home/tovantran/Ctest/MutableConst.cpp
//Const Bradley video
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

class Student 
{
	string m_name;
	vector<double> m_score;
	mutable bool m_cacheStale; //will change in const gpa
	mutable double m_gpa;   //mutual Student::m_gpa in read-onyl object
public:
	Student(string name) : 
	m_name(name), m_score(true), m_gpa(0.0) {}
	~Student(){}
	string getName() const { return m_name;}
	double gpa() const
	{ 
		if (m_cacheStale){
			double sum = accumulate(m_score.begin(), m_score.end(), 0.0);
			m_gpa = sum/ m_score.size();
			m_cacheStale = false;
		}
		return m_gpa;
	}
	void addScore(double score)
	{
		m_score.push_back(score);
		m_cacheStale = true;
	}
};

void print(const Student& s) // make promise will not be changed even ref
{
	cout << "Student " << s.getName() << endl;
	cout << "gpa " << s.gpa() << endl;
}

int main()
{
	Student s1("Bradley");
	s1.addScore(3.2);
	s1.addScore(3.7);
	s1.addScore(3.1);

	print(s1);
	s1.addScore(4.0);
	print(s1);
}//----------------------------------smartpointer18.cpp
//----------------------/home/tovantran/Ctest/smartpointer18.cpp
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

class Person
{
    string m_name;
    int m_age;
public:
    Person(){}   //need default for derived
    Person(string name, int age) : m_name(name), m_age(age){ cout << "Person CTOR " << m_name <<" " << m_age << endl; }
    ~Person(){ cout << "Person DTOR " << endl; }
    void Display() { cout << "Name "<< m_name << " Age " << m_age << endl; }
    template<typename T> friend class SP;
};
template <typename T>
class SP  : public Person
{
    T* m_array;
public:
    SP(const Person &p) : Person(p.m_name, p.m_age) {}
    SP(T* pValue) : m_array(pValue){ cout << "SP CTOR " << pValue << endl;}
    SP(const SP<T>& s){ cout << "SP COPY CTOR " << endl; }
    SP(T& i) : m_array(new T(i))
        {
            cout << "CTOR " << *m_array << endl;
        }
    SP& operator=(const SP& sp)
        {
            if (this == &sp)  //check self assignment
                return *this;
            cout << "OPERATOR" << endl;
            this->m_array = sp.m_array;
            return *this;
        }
    ~SP() { cout << "SP DTOR" << endl; delete m_array; }
    T* operator-> () { return m_array;}
    T& operator*() { return *m_array; }
    T* get() { return m_array;}
    friend ostream& operator<<(ostream& os, const SP<Person>& obj);
};

ostream& operator<<(ostream& os, const SP<Person>& obj)  //like toString() print out object
{
    os << "ostream object: " << obj.m_array << " "  << endl;
    return os;
}

int main()
{
    Person p1(Person("Scott", 25));  //create base object without smart pointer
    p1.Display();
    //SP is smart pointer in stack
    SP<Person> p2(new Person("Tom", 26));  //create base and derived object pointer
    p2.get()->Display();

    SP<Person> p3 = new Person("Tommy", 50);
    p3.get()->Display();

    SP<Person> *p4 = new SP<Person>(new Person("Scotty", 42));
    p4->get()->Display();

    // array template Person to store smart pointer via SP class
    typedef SP<Person>* SPptr;
    SP<Person>* *array = new SP<Person>*[3];
    for (int i = 0; i < 3; i++)
    {
       array[i] = new SP<Person>(new Person("Array", 11));
       cout << *array[i] << endl;  //i object Person
    }
     //vector template Person to store smart pointer via SP class
    vector<SP<Person>*> arrayVec;
    for (int i = 0; i < 3; i++)
     {
         arrayVec.push_back(new SP<Person>(new Person("Vector", 55)));
         cout << *arrayVec[i] << endl;
     }
     for(const auto& a: arrayVec)
        // cout << *a << endl;
        a->get()->Display();
     // for(arrayVec.begin(), arrayVec.end(), [](int &x){ cout << x << endl;})

     //smart pointer template no need to pass through SP class. Generic for any class
     unique_ptr<Person*> arraySP(new Person*(new Person("Smart Pointer", 65)));
     //push into array
     vector<unique_ptr<Person>> sp; //Lambda (Modern C++)
     sp.push_back(unique_ptr<Person>(new Person("Unique_ptr", 70)));
     sp.push_back(unique_ptr<Person>(new Person("Unique_ptr1", 71)));
     sp.push_back(unique_ptr<Person>(new Person("Unique_ptr2", 72)));
     for_each(sp.begin(), sp.end(), [](const unique_ptr<Person>& p) //iterator
     {
         p->Display();
     });

    return 0;
}
//----------------------------------smartpointer19.cpp
//----------------------/home/tovantran/Ctest/smartpointer19.cpp
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;


class Person
{
    string m_name;
    int m_age;
public:
    Person(){}   //need default for derived
    Person(string name, int age) : m_name(name), m_age(age){ cout << "Person CTOR " << m_name <<" " << m_age << endl; }
    ~Person(){ cout << "Person DTOR " << endl; }
    void Display() { cout << "Name "<< m_name << " Age " << m_age << endl; }
    template<typename T> friend class SP;
};

template <typename T>   // T is Person
class SP
{
    unique_ptr<T> m_array;
public:
    SP(string name, int age) : m_array (unique_ptr<T>(new T(name, age))){}
    T *getPtr() { return m_array.get();}
    void makeClass(T& t)
    {
       return {t};
    }
 };

int main()
{
   SP<Person> andy("Andy Williams", 76); //create person as smart pointer
   SP<Person> johnny("Johnny Walker", 89); //create person as smart pointer
   SP<Person> tom("Thomas Edison", 96); //create person as smart pointer
//   cout << andy.m_array.get() << endl; //require m_array is public
   cout << andy.getPtr() << endl;

   auto pointerToandy(andy.getPtr()); //raw pointer to store smart pointer
   cout << pointerToandy << endl;     // no ownership just refer

   andy.getPtr()->Display();
   johnny.getPtr()->Display();
   tom.getPtr()->Display();
    return 0;
}
//----------------------------------smartpointer23.cpp
//http://stackoverflow.com/questions/823426/passing-references-to-pointers-in-c
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

using namespace std;

class Person
{
    string m_name;
    int m_age;
public:
    Person(){}   //need default for derived
    Person(string name, int age) : m_name(name), m_age(age) { cout << "Person CTOR " << m_name <<" " << m_age << endl; }
    ~Person() { cout << "Person DTOR " << endl; }
    void Display() const { cout << "Name "<< m_name << " Age " << m_age << endl; }
    template<typename T> friend class SP;
};
template <typename T>
class SP  : public Person
{
    T* m_array;
public:
    SP(const Person &p) : Person(p.m_name, p.m_age) {}
    SP(T* pValue) : m_array(pValue){ cout << "SP CTOR " << pValue << endl;}
    SP(const SP<T>& s){ cout << "SP COPY CTOR " << endl; }
    SP(T& i) : m_array(new T(i))
        {
            cout << "CTOR " << *m_array << endl;
        }
    SP& operator=(const SP& sp)
        {
            if (this == &sp)  //check self assignment
                return *this;
            cout << "OPERATOR=******" << endl;
            this->m_array = sp.m_array;
            return *this;
        }
    SP& operator()(const SP& sp)
    {
        cout << "FUNCTOR OPERATOR()********" << endl;
        this->m_array = sp.m_array;
        return *this;
    }
    ~SP() { cout << "SP DTOR" << endl; delete m_array; }
    T* operator-> () const { cout << "Overload->" << endl; return m_array;}
    T& operator*() const { cout << "Overload*" << endl; return *m_array; }
    T* get() const { return m_array;}
    T* getArray() { return m_array;}
    friend ostream& operator<<(ostream& os, const SP<Person>& obj);
};

ostream& operator<<(ostream& os, const SP<Person>& obj)  //like toString() print out object
{
    os << "ostream object: " << obj.m_array << " "  << endl;
    return os;
}

int main()
{
    
 
     vector<SP<Person>*> aV; //iterator
     aV.push_back(new SP<Person>(new Person("test", 11)));  //derived class because SP
     aV.push_back(new SP<Person>(new Person("test1", 22)));
     aV.push_back(new SP<Person>(new Person("test3", 33)));

     for_each(aV.begin(), aV.end(), [](const SP<Person>& p)
     {
        p->Display();  //NOT OK does not use SP
     });
     // for_each(aV.begin(), aV.end(), [](const SP<Person>const * p)
     for_each(begin(aV), end(aV), [](const SP<Person>* const &p)
     {
        p->get()->Display(); //OK via SP
     });

     // for (const SP<Person>* a: aV)
     for (const SP<Person>* const &a: aV)
        a->get()->Display();

     for (const auto& a: aV)
        a->get()->Display();

     // smart pointer template no need to pass through SP class. Generic for any class
     unique_ptr<Person*> arraySP(new Person*(new Person("Smart Pointer", 65)));  //base class
     //push into array
     vector<unique_ptr<Person>> sp; //Lambda (Modern C++)
     sp.push_back(unique_ptr<Person>(new Person("Unique_ptr", 70)));
     sp.push_back(unique_ptr<Person>(new Person("Unique_ptr1", 71)));
     sp.push_back(unique_ptr<Person>(new Person("Unique_ptr2", 72)));
     for_each(sp.begin(), sp.end(), [](const unique_ptr<Person>& p) //iterator
     {
         p->Display();
     });
     for (const auto& a: sp)
        a->Display();
     for (const unique_ptr<Person>& a: sp)
        a->Display();
    return 0;
}
//----------------------------------vector2.cpp
//home/tovantran/Ctest/vector2.cpp --> 2014-06-28 by ./.tv  owner: tovantran
// Access the elements of a vector through an iterator.
//B o r l a n d C + + B u i l d e r : T h e C o m p l e t e R e f e r e n c e
#include <iostream>
#include <vector>
#include <cctype>
using namespace std;
int main()
{
	vector<char> v(10); // create a vector of length 10
	vector<char>::iterator p; // create an iterator
	int i;
	// assign elements in vector a value
	p = v.begin();
	i = 0;
	while(p != v.end()) {
		*p = i + 'a';
		p++;
		i++;
	}
	// display contents of vector
	cout << "Original contents:\n";
	p = v.begin();
	while(p != v.end()) {
		cout << *p << " ";
		p++;
	}
	cout << "\n\n";
	// change contents of vector
	p = v.begin();
	while(p != v.end()) {
		*p = toupper(*p);
		p++;
	}
	// display contents of vector
	cout << "Modified Contents:\n";
	p = v.begin();
	while(p != v.end()) {
		cout << *p << " ";
		p++;
	}
	cout << endl;
	return 0;
}

//----------------------/home/tovantran/Ctest/April17Test.cpp
//http://stackoverflow.com/questions/823426/passing-references-to-pointers-in-c
#include <iostream>
using namespace std;

void myfunc(string *& val)
{
	cout << *val << endl;
	*val = "te";
}

void myfunc2(string* const& val)
{
	cout << *val << endl;
	// val = "te"; assign read only cannot change rvalue
}
void myfunc3(string *val)
{
	cout << *val << endl;
}
//rvalue reference &&
void myfunc4(string* &&val)  //close to myfunc2
{
	cout << *val << endl;
	*val = "test";  //reference && rvalue you can now change val
}
int squareInt(int x) { return x*x; }
int square(int &x) { return x*x; }
int squareC(const int& x) { return x*x; }
int squareRef(int &&x) {  return x*x; }
string test() { return "ModernC++";}

int main(int argc, char const *argv[])
{
	string s = "test";
	string *ps = &s;  //&s temporarily rvalue

	cout << "s = " << s << endl;
	myfunc(ps);						// OK because ps is not a temporary
	cout << "s = " << s << endl;
	myfunc2(&s);					// OK because the parameter is a const&
	cout << "s = " << s << endl;
	myfunc3(&s);
	( *myfunc3 )(&s);

	myfunc4(&s);					// OK because the parameter is a &&val
	cout << s << endl;

	string &r = s;
	cout << "&r = " << r << endl;
	//string &r1 = "test";       //non-const reference from an rvalue
	const string &r2 = "test";	 // unless const 
	// &r = "test";  //fail  reference assign only one different pointer
//Ref
	int i = 2;
	square(i); //OK is memory location
	// square(2); //FAIL rvalue &2 is temporarily
	squareC(2);  //square C has const &x
	squareRef(2); //squareRef &&x rvalue reference
	cout << i << endl;
//Value
	squareInt(2); //OK pass by value a copy is make
	
	string name = test();  //pass by value
	// string& name1 = test();  //FAIL by reference
	const string &name2 = test(); //OK with const
	string &&name3 = test();
	return 0;
}
//int i = 10;
// int *ip = &i;
// int *ipp = &ip 

//int &r = i;
//----------------------------------Struct2_1.cpp
//----------------------/home/tovantran/Ctest/Struct2_1.cpp
#include <functional>
#include <iostream>

using namespace std;
typedef int(*func) (int, int);

int rectangle(int a, int b) { return a *b; }

func afunc = &rectangle;  //func has been defined before

typedef void(*fp)(void);  //fp is a pointer to a function pointer take no argument return void
// typedef function<void(void)> fp;

void foo(void)
{
	cout << "foo" << endl;
}

void f(fp)  //fp pointer by typedef
{
	// fp();
	cout << "f" << endl;
}

//typedef void(*fun)(void);
//    void (*fun)(); // = foo;                //pointer

int main()
{
  fp fun;
  // function<void(void)> fun = foo;  //pointer 

  f(fun); // error
  f(foo); // ok

  void (*fp1)(); 
  fp1 = foo; //fp1 = &foo;
  (*fp1)();

  void (*fp2)() = foo;
  (*fp2)(); 

  function<void(void)> fp3 = foo;
  (fp3)();

  int rec = (*afunc)(3, 4);
  cout << rec << endl;

  int (*func1)(int, int) = rectangle;
  cout << (*func1)(2, 3) << endl;

  cout << rectangle(4, 3) << endl;

  // function<int(int, int)> rectangle1 = [](int a, int b){ return a * b;  };
  auto rectangle1 = [](int a, int b){ return a * b;  };
  cout << rectangle1(7, 8) << endl;

  function<int(int, int)> rectangle2 = static_cast<function<int(int, int)>>(rectangle);

  cout << rectangle2(1, 2) << endl;

  int (*func2)(int, int);

  func2 = rectangle;

  cout << (*func2)(100, 200) << endl;


  function<int(int, int)> rectangle4 = rectangle;
  cout << rectangle4(1, 2) << endl;

  auto lambda = [](int a, float b) {
  // function<void(int, float)> lambda = [](int a, float b) {
  	std::cout << "a: " << a << std::endl;
  	std::cout << "b: " << b << std::endl;
  };

  auto function_1  = static_cast<void (*)(int, float)>(lambda);
  function_1(23, 5.4);

auto function_2 = static_cast<std::function<void(int, float)>>(lambda); //cannot convert function to raw pointer
function_2(23, 5.4);

void(*func3)(int, float);
//func3 = function_2; //error
func3 = function_1;
(*func3)(55, 55.5);
}

//----------------------/home/tovantran/Ctest/April28FunctionPointer.cpp
#include <iostream>
using namespace std;

int doubler (int a, int b) { return a*b; }

typedef int (*fp) (int, int);               //Method 1
fp funcP = &doubler;

int main()
{
  int (*func)(int, int) = doubler;  //Method 1
  cout <<	(*func)(2, 3) << endl;

  cout << (*funcP)(4, 5) << endl;   //Method 2
}//----------------------------------May9FunctionLambda.cpp
//----------------------/home/tovantran/Ctest/Apr28FunctionLambda.cpp
#include <functional>
#include <iostream>
// #include <typeinfo>
using namespace std;

template<typename T>
size_t getAddress(std::function<void (T &)> f) {
    typedef void (fnType)(T &);
    fnType ** fnPointer = f.template target<fnType*>();
    return (size_t) *fnPointer;
}
template<typename T, typename... U>
size_t getAddressVariadic(std::function<T(U...)> f) {
    typedef T(fnType)(U...);
    fnType ** fnPointer = f.template target<fnType*>();
    if (fnPointer)
    {
      cout << "fnPointer = " << (size_t) *fnPointer << endl;
      return (size_t) *fnPointer;
  } else {
   cout << "fnPointer = " << (size_t) fnPointer << endl;
   cout << "Undefined pointer std::function" << endl;	
   return 0;
}
}

void foo(int& a) {
    a = 0;
}

void print() { cout << 2 << endl; }

void print1 (int i) {
    cout << i << endl;
}

std::function<int(int, int)> m_minus = std::minus<int>();

int main() {

    std::function<void(int&)> f = &foo;
    std::cout << (size_t)&foo << std::endl << getAddress(f) << std::endl;

    std::function<void(int)> fp = print1;
    function<void()> fp1 = []() { cout << "test " << endl;  };
    void (*func2)(void) = [](){} ;
	auto lambda = [](int x ) { cout << " Lambda " << x <<  endl; }; //OK
    void (*func)(int);

    func = (void(*)(int))lambda;
    func = (void(*)(int))print1;
    func = (void(*)(int))getAddressVariadic(fp);
    cout << "func = " << (void *)func << endl;

    if (func)
        (*func)(1122);

    fp1();
     fp(1123);  //call norm function
     (*fp.target<void(*)(int)>())(11111);  //invoking target
      fp1.target<void()>();  //???? no pointer no target

      bind(fp1)();

      cout << m_minus(5, 3) << endl;
  return 0;
  }

 //----------------------/home/tovantran/Ctest/May11Test2.cpp
//youtube video Needham functors + Pete Becker standard C++ 
//The C++ Standard Library Extensions A Tutorial and
// Reference By Pete Becker
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

// bool isOdd(int n) { return n % 2; }  //unary operator
bool isEqual(int a, int b) { return a == b;} //binary operator

struct isOdd
{
	bool operator()(int n) { return n % 2; } 
};

bool isEven (int a)
{
	return !( a % 2);
}
struct print  //with state
{
	void operator()(int x) { cout << x << endl; };
};
struct printCtor  //with state
{
	string m_delm;
	printCtor(string delm) : m_delm(delm){};
	void operator()(int x) { cout << x <<  m_delm;  };
};
int main()
{
	struct isOdd fn;
	cout << boolalpha << fn(4) << endl;

	std::vector<int> v { 1, 2, 3, 4, 5, 6, 7, 8 };
	std::vector<int> v2{ 1, 2, 3, 4, 5 };
	cout << count_if (v.begin(), v.end(), isOdd()) << endl;
	cout << count_if (v.begin(), v.end(), isEven) << endl;
	cout << count_if (v.begin(), v.end(), [](int x){ return !(x %2);}) << endl;

	for (auto it = v.begin(); it != v.end(); ++it )
		cout << *it << " ";
	cout << endl;

	for_each(v.begin() + 2, v.end() -1, [](int x){cout << x << " "; });
	cout << endl;
	for_each(v.begin(), v.end(), print());
	for_each(v.begin() + 2, v.end(), printCtor(":"));
	cout << endl;

	auto it = find (v.begin(), v.end(), 5);
	it = find (it + 1, v.end(), 5);
	if (it != v.end())
		for_each(it, v.end(), printCtor(" "));
	else
		cout << "not found " << endl;
	cout << endl;

	it = find_if(v.begin(), v.end(), isEven);
	if (it != v.end())
		for_each(it, v.end(), printCtor(" "));
	else
		cout << "not found " << endl;
	cout << endl;

	
	cout << *it << endl;
	//it = 1; //cannot reassign to integer
	int c = count(v.begin(), v.end(), 5);
	cout << "number of 5: " << c << endl;

	cout << boolalpha << equal(v.begin(), v.end(), v2.begin()) << endl;

	it = search(v.begin(), v.end(), v2.begin(), v2.end());
	for_each(it, v.end(), printCtor(" "));

	cout << endl;

	vector<int> v3{9, 5, 6, 3, 5 , 1};
	
	sort(v3.begin(), v3.end());
	for_each(v3.begin(), v3.end(), [](int x) { cout << x << " "; });
	cout << endl;

	copy(v3.begin(), v3.end(),
	ostream_iterator<int>(cout, " "));
	cout << '\n';
}//----------------------------------May14Test1.cpp
//----------------------/home/tovantran/Ctest/May14Test1.cpp
#include <iostream>
#include <cstdint>

using namespace std;

int main()
{

const char *p = "This is a string"; //*p is illegal, ++p OK
// or static_cast
int i = static_cast<int> (*p); // cast pointer to integer
char &g = const_cast<char&>(*p); //which is not a pointer, reference
char *j = const_cast<char*>(p); //OK

cout << hex << "i -->" << i << " " << j << " " << g << endl; //get 1st character in string *p
printf("%x\n", g);

char *x = &g;
printf("*x = %s\n", x);

const char *s = "This is a test";
char *a = reinterpret_cast<char*>(*s);
int &b = reinterpret_cast<int&>(s);  /*  pointer to reference */

printf("%p\n", a);
// printf("%s\n", b);/*warning: format ‘%s’ expects argument of type ‘char*’, but argument 2 has type ‘int’*/
// printf("%s\n", (char*)b); /*warning: cast to pointer from integer of different size*/
printf("%s\n", reinterpret_cast<char*>(b)); /*string int*/
                /* static_cast */           /*int/double int/char*/
                /* const_cast */            /* remove const */
}//----------------------------------May15Test.cpp
//BorlandC p. 590
// An example that uses reinterpret_cast.
#include <iostream>
#include <cstdint>
using namespace std;
int main()
{
	intptr_t i; /*big enought to hold pointer*/
	const char *p = "This is a string";
	i = reinterpret_cast<intptr_t> (p); // cast pointer to integer
	cout << i << endl;
	printf("%s\n", reinterpret_cast<char*>(i));  /*expected *char but argument 2 has type intptr_t i is a pointer*/
	return 0;
}
//----------------------------------May15Test.cpp
#include <iostream>
#include <cstdint>
using namespace std;
int main()
{
	int i;
	const char *p = "This is a string";
	// i = reinterpret_cast<int> (p); // cast pointer to integer
	// cout << i;

	//i = const_cast<int>(*p);
	//error: invalid use of const_cast with type ‘int’, which is not a pointer, reference, nor a pointer-to-data-member type

	//cast a *p a pointer
	i = static_cast<int>(*p);  //*p is 1st character "This" using int to hold *p is T
	printf("static_cast: %x\n", i);

	//cast address p need intptr_t to hold the big address
	intptr_t ii = reinterpret_cast<intptr_t>(p);          /*OK*/
	//warning: format ‘%s’ expects argument of type ‘char*’, but argument 2 has type ‘intptr_t
	printf("reinterpret_cast: %s\n", reinterpret_cast<char *>(ii));  //cast intptr_t to string or char *

	//if it is char * then only cast away const using const_cast p is already *p is const char "T"
	char *iii = const_cast<char*>(p);
	printf("const_cast: %s\n", iii);
	
	return 0;
}//----------------------------------May21Test.cpp
//Lvalue Rvalue you tube Bo Qian also May20Test.cpp SmartPointer
#include <iostream>
#include <typeinfo>
using namespace std;

class Base
{
	int i;
public:
	Base(int i): i(i) { cout << "CTOR" << endl;}
	Base(const Base &b) { cout << "copy CTOR" << endl; } //if copy not create compile create one
	~Base(){ cout << "DTOR " << endl;}
	int getInt() { return i; }
};

                
void obValue (Base o) /*Base o copy by value COPY is made and call DTOR */
{
	cout << "ob Value " << endl;
}
void ob (Base &o)
{
	cout << "ob lvalue ref "  << /*typeid(o).name()*/ o.getInt() << endl;
}
void ob (Base *o)
{
	cout << "ob pointer * "  << /*typeid(o).name()*/ o->getInt() << endl;
}
void ob (Base &&o) 
{ 
	cout << "on rvalue ref && " << o.getInt() << endl;
}
void ob (Base const &o) //rvalue ref const. Base o create a new obj copy CTOR if pass by value. 
						
{
	cout << "ob rvalue ref const " << endl;
}
//overload function based on parameter types lvalue or rvalue but not by value 
void printValue(int i) { cout << "printValue: "<< i << endl; }
void print(int &i) { cout <<"print & lvalue ref:" << i << endl; } //error: invalid initialization of non-const reference of type ‘int&’
void print(int *i) { cout << "print pointer *i: " << *i << endl; }
// 2 statements are the same && or const &
void print(int &&i) { cout <<"print && rvalue ref: " << i << endl; }  //rvalue ref &&
void print(int const &i) { cout <<"print & const rvalue ref: " << i << endl; } //rvalue ref const
//void printValue(int &i){} //call of overloaded ‘printValue(int&)’ is ambiguous printValue(int i)
int main()
{
	int a = 1; //lvalue
	int &b = a; //lvalue reference before reference
	int &&c = 1; //rvalue reference

	printValue(a); //value
	printValue(1); //value
	print(a); //lvalue ref &
	print(&a); //pointer *
	print(1); //rvalue ref &&
	// print(&a); //rvalue ref &&
	{
		 Base *b = new Base(11);
		 Base b1(12);
		      obValue(*b);  //COPY CTOR by value b is address *b is pointer is integer
		 		 	ob(*b);  //ob2(*b)  ob2(b1) / lvalue ref
		 				 ob(b);  //b is address, *b is value  ob1(b) ob1(&b1) / pointer *
		           			ob(12); //Ref
		       obValue(b1);
		       ob(b1);  //lvalue ref
		       ob(&b1); //pointer
		       ob(11); //rvalue ref && /rvalue ref const
		cout << "from main" << endl;
		  delete b;
	} //end of scope DTOR is called if COPY CTOR is called when pass by value
	int i = 1;
	// int &r = i; //OK lvalue assignment 
	//&r = 5; //lvalue required as left operand of assignment
	// int &r = 5; //non-const reference of type int& from an rvalue
	const int &r = 5; //OK const here can initialize using rvalue
	
	int d = 5;  //lvalue is created with 5
	int &temp = d;
	d = temp; //ref e is initilize with temporarily lvalue

	cout << r  << " " << d << endl;

	
}
