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
