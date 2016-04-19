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
