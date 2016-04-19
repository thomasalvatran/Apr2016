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
