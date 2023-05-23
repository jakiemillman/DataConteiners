// List2
#include <iostream>
using namespace std;
#define tab "\t"
#define delimetr "-----------------------------------------------------------------------------------------------------"

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
public:
    List()
    {
        Head = Tail = nullptr;
        size = 0;
        cout << "LConstructor:\t" << this << endl;
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
        if (Head == nullptr && Tail == nullptr)return;
        Element* Temp = Head->pNext;
        Temp->pPrev = nullptr;
        delete Head;
        Head = Temp;
        Temp = nullptr;
        size--;
    }
    void pop_back()
    {
        if (Head == nullptr && Tail == nullptr)return;
        Element* Temp = Tail->pPrev;
        Temp->pNext = nullptr;
        delete Tail;
        Tail = Temp;
        Temp = nullptr;
        size--;
    }
    void insert(int Data, int Index)
    {
        if (Index < size / 2)
        {   
            Element* Temp = Head;
            for (int i = 0; i < Index-1; i++)
            {
                Temp = Temp->pNext;
            }
            Temp->pNext = new Element(Data, Temp->pNext->pNext, Temp);
            Temp = nullptr;
            size++;
        }
        else
        {
            Element* Temp = Tail;
            for (int i = 0; i < size / 2 - (Index - size / 2); i++)
            {
                Temp = Temp->pPrev;
            }
            Temp->pPrev = new Element(Data, Temp, Temp->pPrev->pPrev);
            Temp = nullptr;
            size++;
        }
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
     int n = 0;
     cout << "Введите размер списка: "; cin >> n;
     List list1;
     for (int i = 0; i < n; i++)
     {
         list1.push_front(rand()%100);
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
     list1.insert(12, 8);
     list1.Print();
}

