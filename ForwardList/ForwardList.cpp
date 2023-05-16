// ForwardList
#include <iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;
#define tab "\t"
class Element
{
   int Data;
   Element* pNext;
public:
   Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
   {
      cout << "Constructor:\t" << this << endl;
   }
   ~Element()
   {
      cout << "Desstructor:\t" << this << endl;
   }
   friend class ForwardList;
   //push_front
   
};
class ForwardList
{
   Element* Head;
public:
   ForwardList()
   {
      Head = nullptr;
      cout << "LConstructor:\t" << this << endl;
   }
   ForwardList(const ForwardList& other)
   {
       clear();
       this->Head = 0;
       Element* Temp = this->Head;
       Element* Temp1 = other.Head;
       while (Temp1)
       {
           Element* New = new Element(Temp1->Data);
           Temp= New;
           Temp1 = Temp1->pNext;
       }
       delete Temp;
       delete Temp1;
       cout << "LCopyConstructor:\t" << this << endl;
   }
   ~ForwardList()
   {
       clear();
       cout << "LDestructor:\t" << this << endl;
   }
   //add elements
   void clear()
   {
       Element* Temp = Head;
       Element* Erase = Head;
       while (Temp)
       {
           Erase = Temp->pNext;
           delete Temp;
           Temp = Erase;
       }
       delete Erase;
       Erase = nullptr;
   }
   void push_front(int Data)
   {
      Element* New = new Element(Data);
      New->pNext = Head;
      Head = New;

   }
   void push_back(int data)
   {
       if (Head == nullptr)return push_front(rand() % 100);
      Element* New=new Element(data);
      Element* Temp = Head;
      while (Temp->pNext)
      {
          Temp = Temp->pNext;

      }
      Temp->pNext = New;
   }
   //delete elements
   void pop_front()
   {
       Element* Erased = Head;
       Head = Head->pNext;
       delete Erased;
   }
   void pop_back()
   {
       Element* Temp = Head;
       while (Temp->pNext->pNext)
       {
           Temp = Temp->pNext;

       }
       delete Temp->pNext;
       Temp->pNext = nullptr;
   }
   void insert(int Data, int Index)
   {
       Element* New = new Element(Data);
       Element* Temp = Head;
       for (int i = 0; i < Index; i++)Temp = Temp->pNext;
       New->pNext = Temp->pNext;
       Temp->pNext = New;

   }
   void erase(int index)const
   {
       Element* Temp = Head;
       Element* Erase = Head;
       for (int i = 0; i < index-1; i++)
       {
           Temp = Temp->pNext;
       }
       Erase = Temp->pNext;
       Temp->pNext = Temp->pNext->pNext;
       delete Erase;
   }
   void print()const
   {
      Element* Temp = Head;
      while (Temp)
      {
         cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
         Temp = Temp->pNext;
      }
   }
};

int main()
{
   setlocale(LC_ALL, "rus");
   int n=0;
   int m = 0;
   cout << "¬ведите размер списка1: "; cin >> n;
   cout << "¬ведите размер списка1: "; cin >> m;
   ForwardList list;
   ForwardList list1;
   for (int i = 0; i < n; i++)
   {
      //list.push_front(rand() % 100);
      list.push_back(rand()%100);
   }
   for (int i = 0; i < m; i++)
   {
       //list.push_front(rand() % 100);
       list1.push_back(rand() % 100+1);
   }
   list.print(); cout << endl;
   list1.print(); cout << endl;
   //list.pop_front();
   //list.print();
   //list.pop_back();
   //list.print();
   //list.insert(5, 3);
   /*list.erase(2);
   list.print();*/
   list=list1;
   list.print(); cout << endl;
   list1.print(); cout << endl;
}

