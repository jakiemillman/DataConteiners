// ForwardList
#include <iostream>
#include <time.h>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
#define tab "\t"
#define delimiter "\n--------------------------------------------------------\n"
class Element
{
   int Data;
   Element* pNext;
   static int count;
public:
   Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
   {
       count++;
#ifdef DEBUG
       cout << "Constructor:\t" << this << endl;
#endif // DEBUG

   }
   ~Element()
   {
       count--;
#ifdef DEBUG
       cout << "Desstructor:\t" << this << endl;
#endif
   }
   friend class ForwardList;
   friend class Iterator;
   //push_front
   
};

int Element::count = 0;

class Iterator
{
    Element* Temp;
public:
    Iterator(Element* Temp) :Temp(Temp)
    {
        cout << "ItConstructor:\t" << this << endl;
    }
    ~Iterator()
    {
        cout << "ItDestructor:\t" << this << endl;
    }
    Iterator& operator++()
    {
        Temp = Temp->pNext;
        return *this;
    }
    Iterator& operator++(int)
    {
        Iterator Old = *this;
        Temp = Temp->pNext;
        return Old;
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
};

class ForwardList
{
   Element* Head;
   unsigned int size;
public:
    Iterator begin() const
    {
        return Head;
    }
    Iterator end() const
    {
        return nullptr;
    }
   ForwardList()
   {
      Head = nullptr;
      size = 0;
      cout << "LConstructor:\t" << this << endl;
   }
   ForwardList(const initializer_list<int>& il) :ForwardList()
   {
       //begin() - возвращает итератор на начало контейнера
       //end()   - возвращает итератор на конец контейнера
       cout << typeid(il.begin()).name() << endl;
       for (int const* it = il.begin(); it != il.end(); it++)
       {
           push_back(*it);
       }
   }
   ForwardList(const ForwardList& other):ForwardList()
   {
       *this = other;
      /* Element* Temp = other.Head;
       while (Temp)
       {
           push_back(Temp->Data);
           Temp = Temp -> pNext;
       }*/
       //delete Temp;
       //delete Temp1;
       cout << "LCopyConstructor:\t" << this << endl;
   }
   ForwardList(ForwardList&& other) :ForwardList()
   {
       *this = std::move(other);
       cout << "MoveConstructor:\t" << this << endl;
   }
   ~ForwardList()
   {
       while(Head)pop_front();
       cout << "LDestructor:\t" << this << endl;
   }
   ForwardList& operator=(const ForwardList& other)
   {
       if (this == &other)return *this;
       while (Head)pop_front();
       for(Element* Temp = other.Head;Temp; Temp = Temp->pNext)push_back(Temp->Data);
      /* Element* Temp = other.Head;
       while (Temp)
       {
           push_back(Temp->Data);
           Temp = Temp->pNext;
       }*/
       cout << "CopyAssingment:\t" << this << endl;
       return *this;
   }
   ForwardList& operator=(ForwardList&& other)
   {
       if (this == &other)return *this;
       while(Head)pop_front();
       this->Head = other.Head;
       this->size = other.size;
       other.Head = nullptr;
       other.size = 0;
       return *this;

   }
   //add elements
   void clear()
   {
       while (Head)pop_front();
       
   }
   void push_front(int Data)
   {
      Head = new Element(Data, Head);
      size++;

   }
   void push_back(int data)
   {
       if (Head == nullptr)return push_front(data);
      Element* Temp = Head;
      while (Temp->pNext)
      {
          Temp = Temp->pNext;
      }
      Temp->pNext = new Element(data);
      
      size++;
   }
   //delete elements
   void pop_front()
   {
       Element* Erased = Head;
       Head = Head->pNext;
       delete Erased;
       size--;
   }
   void pop_back()
   {
       if (Head->pNext == nullptr)return pop_front();
       Element* Temp = Head;
       while (Temp->pNext->pNext)
       {
           Temp = Temp->pNext;

       }
       delete Temp->pNext;
       Temp->pNext = nullptr;
       size--;
   }
   void insert(int Data, int Index)
   {
       if (Index == 0)return push_front(Data);
       if (Index > size)return;
       Element* Temp = Head;
       for (int i = 0; i < Index; i++)Temp = Temp->pNext;
       Temp->pNext = new Element(Data,Temp->pNext);
       size++;

   }
   void erase(int index)
   {
       if (index == 0)return pop_front();
       if (index > size)return;
       Element* Temp = Head;
       Element* Erase = Head;
       for (int i = 0; i < index-1; i++)
       {
           Temp = Temp->pNext;
       }
       Erase = Temp->pNext;
       Temp->pNext = Temp->pNext->pNext;
       delete Erase;
       size--;
   }
   void print()const
   {
       cout << "Head:\t\t" << Head << endl;
      Element* Temp = Head;
      while (Temp)
      {
         cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
         Temp = Temp->pNext;
      }
      // for(Element* Temp = Head;Temp;Temp=Temp->pNext)cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
      cout << "Кол-во элементов списка: " <<size<< endl;
      cout << "Общее кол-во элементов списка: " << Head->count << endl;
   }
};
//#define BASE_CHECK
//#define COPY_CHECK
//#define PREFORMANCE_TEST
ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
    ForwardList Cat = left;
    for (Iterator it = right.begin(); it != right.end(); it++)Cat.push_back(*it);
    return Cat;
}
int main()
{
   setlocale(LC_ALL, "rus");
#ifdef BASE_CHECK
   int n = 0;
   int m = 0;
   cout << "Введите размер списка1: "; cin >> n;
   /* cout << "Введите размер списка1: "; cin >> m;*/
   ForwardList list;
   /*ForwardList list1;*/
   for (int i = 0; i < n; i++)
   {
       //list.push_front(rand() % 100);
       list.push_back(rand() % 100);
   }
   /*for (int i = 0; i < m; i++)
   {
       list.push_front(rand() % 100);
       list1.push_back(rand() % 100+1);
   }*/
   /* list.print(); cout << endl;*/
   /* list1.print(); cout << endl;*/
    //list.pop_front();
    //list.print();
    //list.pop_back();
    //list.print();
    //list.insert(5, 3);
    /*list.erase(2);
    list.print();*/
   cout << delimiter << endl;
   ForwardList list1 = list;
   /* list1 = list1;*/
   list.print(); cout << endl;
   list1.print(); cout << endl;
   cout << delimiter << endl;
   list.push_front(5);
   list.print(); cout << endl;
   cout << delimiter << endl;
   list.push_back(5);
   list.print(); cout << endl;
#endif 
#ifdef PREFORMANCE_TEST
   int n = 0;
   cout << "Введите размер списка: "; cin >> n;
   ForwardList list;
   cout << "Список создан, идет загрузка даенных" << endl;
   clock_t t_start = clock();
   for (int i = 00; i < n; i++)
   {
       list.push_front(rand() % 100);
   }
   clock_t t_end = clock();
   cout << "Данные загруженны за " << double(t_end - t_start) / CLOCKS_PER_SEC << endl;
   cout << delimiter << endl;
   cout << "Копируем список " << endl;
   t_start = clock();
   ForwardList list2 = list;
   t_end = clock();
   cout << "Список скопирован за: " << double(t_end - t_start) / CLOCKS_PER_SEC << endl;

   ForwardList list = { 3,5,8,13,21 };
   //list.print();
   for (int i : list)
   {
       cout << i << tab;
   }
   cout << endl;
#endif // PREFORMANCE_TEST
   ForwardList list1 = { 3,5,8,13,21 };
   for (int i : list1)
   {
       cout << i << tab;
   }
   cout << endl;
   ForwardList list2 = { 33,44,55,66,77 };
   for (int i : list2)
   {
       cout << i << tab;
   }
   cout << endl;
   ForwardList list3 = list1 + list2;
   for (int i : list3)
   {
       cout << i << tab;
   }
   cout << endl;
}

