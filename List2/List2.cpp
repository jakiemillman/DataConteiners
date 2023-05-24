// List2
#include <iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
#define tab "\t"
#define delimetr "-----------------------------------------------------------------------------------------------------"

//#define BASE_CHECK

class List 
{
    class Element
    {
        int Data;
        Element* pNext;
        Element* pPrev;
    public:
        Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) :Data(Data), pNext(pNext), pPrev(pPrev)
        {
            cout << "EConstructor:\t" << this << endl;
        }
        ~Element()
        {
            cout << "EDestructor:\t" << this << endl;
        }
        friend class List;
    }*Head, *Tail;
    size_t size;
    class Iterator
    {
        Element* Temp;
    public:
        Iterator(Element* Temp):Temp(Temp)
        {
            cout << "ItConstructor\t" << this << endl;
        }
        ~Iterator()
        {
            cout << "ItDestructor\t" << this << endl;
        }
        Iterator& operator++()
        {
           Temp = Temp->pNext;
           return *this;
        }
        Iterator& operator--()
        {
            Temp = Temp->pPrev;
        }
        bool operator==(const Iterator& other)const
        {
            return this->Temp == other.Temp;
        }
        bool operator!=(const Iterator& other)const
        {
            return this->Temp != other.Temp;
        }
        int& operator*()
        {
            return Temp->Data;
        }
        friend class List;
    };
public:
    Iterator begin()
    {
        return Head;
    }
    Iterator end()
    {
        return nullptr;
    }

    List()
    {
        Head = Tail = nullptr;
        size = 0;
        cout << "LConstructor:\t" << this << endl;
    }
    List(const initializer_list<int>& il) :List()
    {
        for (int const* it = il.begin(); it != il.end(); it++)
        {
            push_back(*it);
        }
    }
    ~List()
    {
        cout << "LDestructor:\t" << this << endl;
    }

    // Adding Elements:
    void push_front(int Data)
    {
        if (Head == nullptr && Tail == nullptr)
        {
            Head = Tail = new Element(Data);
            size++;
            return;
        }
        Head=Head->pPrev = new Element(Data, Head);
        size++;
        /*Element* New = new Element(Data);
        New->pNext = Head;
        Head->pPrev = New;*/
    }
    void push_back(int Data)
    {
        if (Head == nullptr && Tail == nullptr)
        {
            push_front(Data);
            return;
        }
        Tail = Tail->pNext = new Element(Data, nullptr, Tail);
        size++;
    }
    void pop_front()
    {
        if (Head == Tail)
        {
            delete Head;
            Head = Tail = nullptr;
            size=0;
            return;
        }
        Head = Head->pPrev;
        delete Head->pPrev;
        Head->pPrev = nullptr;
        size--;
    }
    void pop_back()
    {
        if (Head == Tail)return pop_front();
        Tail = Tail->pPrev;
        delete Tail -> pNext;
        Tail -> pNext = nullptr;
        size--;
       
    }
    void insert(int Data, int Index)
    {
        if (Index == 0)pop_front();
        if (Index == size)return push_back(Data);
        if (Index > size)return;
        Element* Temp;
        if (Index < size / 2)   
        {   
            Temp = Head;
            for (int i = 0; i < Index; i++)
            {
                Temp = Temp->pNext;
            }
        }
        else
        {
            Temp = Tail;
            for (int i = 0; i < size-Index-1; i++)
            {
                Temp = Temp->pPrev;
            }
        }
       Temp->pPrev =  Temp->pPrev->pNext=new Element(Data, Temp, Temp->pPrev);
       /* New->pNext = Temp;
        New->pPrev = Temp->pPrev;
        Temp->pPrev->pNext = New;
        Temp->pPrev = New;*/
        size++;
    }
    void erase(int Index)
    {
        Element* Temp;
        if (Index == 0)return pop_front();
        if (Index >= size)return;
        if (Index == size-1)return pop_back();
        if (Index < size / 2)
        {
            Temp = Head;
            for (int i = 0; i < Index; i++)Temp = Temp->pNext;
        }
        else
        {
            Temp = Tail;
            for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
        }
        Temp->pPrev->pNext = Temp->pNext;
        Temp->pNext->pPrev = Temp->pPrev;
        delete Temp;
        size--;

    }

    void Print()const
    {
        for (Element* Temp = Head; Temp; Temp = Temp->pNext)
        {
            cout << Temp->pPrev << tab << Temp->Data << tab << Temp->pNext << endl;
            
        }
        cout << "Кол-во элементов: " << size << endl;
    }
    void Reverse_Print()const
    {
        for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
        {
            cout << Temp->pPrev << tab << Temp->Data << tab << Temp->pNext << endl;
        }
        cout << "Кол-во элементов: " << size << endl;
    }

};

int main()
{
     setlocale(LC_ALL, "rus");
#ifdef BASE_CHECK
     int n = 0;
     cout << "Введите размер списка: "; cin >> n;
     List list1;
     for (int i = 0; i < n; i++)
     {
         list1.push_front(rand() % 100);
     }
     list1.Print();
     //list1.Reverse_Print();
     cout << delimetr;
     cout << endl;
     list1.push_back(12);
     list1.Print();
     cout << delimetr;
     cout << endl;
     list1.pop_back();
     list1.Print();
     cout << delimetr;
     cout << delimetr;
     cout << endl;
     int m = 0;
     int value;
     cout << "Введите индекс: "; cin >> m;
     cout << "Введите значение: "; cin >> value;
     list1.insert(value, m);
     list1.Print();
     list1.Reverse_Print();
     list1.erase(5);
     list1.Print();
#endif // 
     List list = { 3,5,8,13,21 };
     for (int i : list)
     {
         cout << i << tab;
     }
     cout << endl;
     for(List::Iterator it=list.end()
}

