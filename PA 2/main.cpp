#include <iostream>

using namespace std;


// Data Class : Holds all the data that goes inside the Node
class TicketItem {
public:
    string reserveCode;
    string personName;

    TicketItem(string code, string name) {
        this->reserveCode = code;
        this->personName = name;
    }
    ~TicketItem()
    {
        cout <<"It is deleted.\n";
    }

    void print()
    {
        cout << "Customer: " <<  personName << " has the ticket number " << reserveCode;
    }

};

// Node Class : Node for the LinkedList
template <typename T> class Node {
public:
    T *value;
    Node<T> *nextNode;
    Node(T *value)
    {
        this->value = value;
        nextNode = nullptr;
    }
    ~Node()
    {
        this->value = nullptr;
        cout << "Item is deleted\n";
    }

    void print()
    {
        value->print();
    }
};

//LinkedList Class : Container for Nodes
template <typename T> class LLStack {
public:
    Node<T> *top;
    int stackSize = 0;
    const int SMAXITEMS = 5;
// Constructor
    LLStack()
    {
        this->top = nullptr;
        stackSize = 0;
        SMAXITEMS;
    }


//Destructor
    ~LLStack() {
        Node<T> *temp = top;
        while (top) {
            top = top->nextNode;
            delete temp;
            temp = top;
        }
    }

    bool isEmpty()
    {
        return top == nullptr;
    }

    bool isFull()
    {
         if(stackSize < SMAXITEMS)
         {
             return false;
         }
         else
             return true;
    }
    int getSize()
    {
        return stackSize;
    }

    T* peek()
    {
        return top->value;
    }

    void push(T* item)
    {
        Node<T>* newNode = new Node<T>(item);
        newNode->nextNode = top;
        top = newNode;
        stackSize++;
    }

    void pop()
    {
        Node<T>* temp = top;
        top = top->nextNode;
        free (temp);
        stackSize--;
    }

    void print() {
        Node<T> *temp = top;
        while (temp != nullptr) {
            temp->print();
            cout << endl;
            temp = temp->nextNode;
        }
    }

};

//Queue
template <typename T> class StackQ
{
public:
    LLStack<T> *enQStack;
    LLStack<T> *deQStack;
    int queueSize = 0;
    const int QMAXITEMS = 5;

    StackQ()
    {
        enQStack = new LLStack<T>();
        deQStack = new LLStack<T>();
        queueSize = 0;
        QMAXITEMS;
    }
    //Deconstructor
    ~StackQ()
    {
        delete enQStack;
        delete deQStack;
        cout << "Queue is destroyed";
    }

    void enqueue(T* item)
    {
        //this will move the item back to the stack before enqueue more items
        if(enQStack->isEmpty()&&!deQStack->isEmpty())
        {
            while (!deQStack->isEmpty())
            {
                T *fromDQstack = deQStack->peek();
                deQStack->pop();
                enQStack->push(fromDQstack);
            }
            enQStack->push(item);
        }
        else
        {
          enQStack->push(item);
        }
        queueSize++;
    }

    void dequeue() {

        if (deQStack->isEmpty())
        {
            while (!enQStack->isEmpty()) {
                T* item = enQStack->peek();
                enQStack->pop();
                deQStack->push(item);
            }
        }
        deQStack->pop();
        queueSize--;
    }

    T* peek() {
        if (deQStack->isEmpty())
        {
            while (!enQStack->isEmpty()) {
                T* item = enQStack->peek();
                enQStack->pop();
                deQStack->push(item);
            }
        }
        return deQStack->peek();
    }


    bool isEmpty()
    {
        if (enQStack->isEmpty() && deQStack->isEmpty())
            return true;
        else
            return false;
    }

    bool isFull()
    {
        if(queueSize >= QMAXITEMS)
            return true;
        else
            return false;
    }

    int ticketQueueSize()
    {
        int size = enQStack->getSize() + deQStack->getSize();
        return size;
    }

    void print() {
        LLStack<T> *tempStack = new LLStack<T> ();

        //move item from enqstack to temp stack to print
        while (!enQStack->isEmpty()) {
            T* item = enQStack->peek();
            deQStack->push(item);
            enQStack->pop();
        }
        Node<T>* current = deQStack->top;
        while (current != nullptr) {
            current->print();
            cout << endl;
            current = current->nextNode;
        }
        //move item back to EnqStack after print
        while (!deQStack->isEmpty()) {
            T* item = deQStack->peek();
            enQStack->push(item);
            deQStack->pop();
        }
    }

    void printBoth() {
        Node<T>* current = deQStack->top;
        cout << "Dequeue Stack: " << endl;
        if(deQStack->isEmpty())
        {
            cout << "Dequeue is empty.\n";
        }
        while (current != nullptr) {
            current->print();
            cout << endl;
            current = current->nextNode;
        }
        current = enQStack->top;
        cout << "\nEnqueue Stack: " << endl;
        if(enQStack->isEmpty())
        {
            cout << "Enqueue is empty.\n";
        }
        while (current != nullptr) {
            current->print();
            cout << endl;
            current = current->nextNode;
        }
        cout << endl;
    }

};

void menuDisplay()
{
    cout << "Please choose the option below:\n";
    cout << "1. Add Item to ticket queue\n";
    cout << "2. Delete from ticket queue\n";
    cout << "3. Peek from the ticket queue\n";
    cout << "4. Display the ticket queue\n";
    cout << "5. Display ticket queue size\n";
    cout << "6. Display enQStack and deQStack\n";
    cout << "7. Exit\n";
    cout << "Enter your choice:\n";
}
//Main Program

int main() {
    int choice;
    string name;
    string ticketNumber;
    TicketItem *t1;
    StackQ<TicketItem> *queue = new StackQ<TicketItem> ();

   do{
       menuDisplay();
       cin >> choice;
       while (choice < 1 || choice > 8)
       {
           cout << "Invalid choice! Please enter a valid option:\n";
           cin.clear();
           cin.ignore(10000,'\n');
           cin >> choice;
       }
        switch (choice) {
            case 1:
                if(queue->isFull())
                {
                    cout << "Queue is Full. Please delete before you add more\n\n";
                    break;
                }
                else
                {
                    cout <<"Please enter the name of the person:\n";
                    cin >> name;
                    cout << "Please enter the ticket number:\n";
                    cin >> ticketNumber;
                    t1 = new TicketItem (ticketNumber,name);
                    queue->enqueue(t1);
                }
                break;
            case 2:
                if(queue->isEmpty())
                {
                    cout << "Queue is empty.\n\n";
                    break;
                }
                queue->dequeue();
                break;
            case 3:
                if(queue->isEmpty())
                {
                    cout << "Queue is empty.\n\n";
                    break;
                }
                cout << "Front of the line is:\n";
                queue->peek()->print();
                cout << endl;
                cout << endl;
                break;
            case 4:
                if(queue->isEmpty())
                {
                    cout << "Queue is empty.\n\n";
                    break;
                }
                else
                {
                    queue->print();
                }
                cout << endl;

                break;
            case 5:
                cout << "Queue Size is: "<< queue->ticketQueueSize() << endl << endl;
                break;
            case 6:
                if(queue->isEmpty())
                {
                    cout << "Queue is empty.\n\n";
                    break;
                }
                queue->printBoth();
                break;
           case 7:
               queue->~StackQ();
               exit(0);
               break;
        }
    }while(choice != 8);


    return 0;
}