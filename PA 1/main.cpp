/* Double Linked List Template
 * Author:
 * Prof. Fnu Manju Muralidharan Priya & Dat  Truong
 * CS 210
 *
 * */


#include <iostream>

using namespace std;

// Data Class : Holds all the data that goes inside the Node
class Data {
public:
    int value;
    string name;
    Data(int value, string name) {
        this->value = value;
        this->name = name;
    }

    //encapsulation to get the value and name of the node
    string getName()
    {
        return name;
    }
    int getValue()
    {
        return value;
    }
    void print() {
        cout << "["<< value << ", " << name << "] ";
    }

};

// Node Class : Node for the LinkedList
template <typename T> class Node {
public:
    T *value;
    Node<T> *next;
    Node<T> *prev;
    Node(T *value) {
        this->value = value;
        next = nullptr;
        prev = nullptr;
    }
    void print() { value->print(); }
};

// LinkedList Class : Container for Nodes
template <typename T> class DoubleLinkedList {
private:
    Node<T> *head;
    Node<T> *tail;
    int length;

public:
    // Constructor
    DoubleLinkedList(T *value) {
        Node<T> *newNode = new Node<T>(value);
        head = newNode;
        tail = newNode;
        length = 1;
    }

    // Destructor
    ~DoubleLinkedList() {
        Node<T> *temp = head;
        while (head) {
            head = head->next;
            delete temp;
            temp = head;
        }
    }

    void printList() {
        Node<T> *temp = head;
        while (temp != nullptr) {
            temp->print();
            temp = temp->next;
        }

    }

    // get and set
    Node<T> *getHead() {
        if (head == nullptr) {
            cout << "Head: nullptr" << endl;
        } else {
            cout << "Head: " << head->value << endl;
        }
        return head;
    }

    Node<T> *getTail() {
        if (tail == nullptr) {
            cout << "Tail: nullptr" << endl;
        } else {
            cout << "Tail: " << tail->value << endl;
        }
        return tail;
    }

    int getLength() {

        return length;
    }

    Node<T> *get(int index) {
        if (index < 0 || index >= length)
            return nullptr;
        Node<T> *temp = head;
        for (int i = 0; i < index; ++i) {
            temp = temp->next;
        }
        return temp;
    }

    bool set(int index, T *value) {
        Node<T> *temp = get(index);
        if (temp) {
            temp->value = value;
            return true;
        }
        return false;
    }

    // All insert methods
    // Insert at end
    void append(T *value) {

        Node<T> *newNode = new Node<T>(value);
        if (length == 0) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        length++;
    }

    // Insert at beginning

    void prepend(T *value) {
        Node<T> *newNode = new Node<T>(value);
        if (length == 0) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        length++;
    }

    // Insert at Index

    bool insert(int index, T *value) {
        if (index < 0 || index > length)
            return false;
        if (index == 0) {
            prepend(value);
            return true;
        }
        if (index == length) {
            append(value);
            return true;
        }
        Node<T> *newNode = new Node<T>(value);
        Node<T> *prev1 = get(index - 1);
        Node<T> *next1 = prev1->next;
        newNode->prev = prev1;
        newNode->next = next1;
        prev1->next = newNode;
        next1->prev = newNode;
        length++;
        return true;
    }

    // All delete Methods
    // Write DeleteHead, DeleteTail & DeleteAtIndex here
    void deleteAtHead()
    {
        if(length == 0)
        {
            return;
        }

        Node<T> *temp = head;
        if(length ==1)
        {
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            head=head->next;
            head->prev = nullptr;
        }
        delete temp;
        length --;

    }

    //Delete Tail
    void deleteAtTail()
    {
        if(length ==0)
            return;
        Node<T> *temp = head;
        if(length == 1)
        {
            head= nullptr;
            tail = nullptr;
        }
        else
        {
            Node<T> *pre = head;
            while(temp->next)
            {
                pre = temp;
                temp = temp->next;
            }
            tail->prev = pre;
            tail = pre;
            tail->next = nullptr;
        }
        delete temp;
        length--;
    }
    //delete at index
    void deleteAtIndex(int index)
    {
        if (index < 0 || index >= length)
            return;
        if (index == 0)
            return deleteAtHead();
        if (index == length - 1)
            return deleteAtTail();

        Node<T> *prev = get(index - 1);
        Node<T> *temp = prev->next;

        prev->next = temp->next;
        delete temp;
        length--;
    }



    //Using Bubble sort
    void sortList()
    {
        //Dealing with 3 nodes currentPrev -> current -> currentAfter
        Node<T> *currentPrev;
        Node<T> *currentAfter;
        Node<T> *currentNode;
        int intValA, intValB;

        //check if list is sorted
        bool isSorted = false;

        while (!isSorted)
        {
            isSorted = true;
            //Keep the list back to the head to sort
            currentNode = head;
            while (currentNode->next != nullptr)
            {
                //get the value to compare
                 intValA= currentNode->value->getValue();
                 intValB = currentNode->next->value->getValue();

                //Test case if the int value in currentNode is bigger
                if (intValA > intValB)
                {
                    //this point the prev node
                    currentPrev = currentNode->prev;
                    // this point to next node
                    currentAfter = currentNode->next;
                    //this is check if currentNode is head or not
                    if (currentPrev != nullptr)
                    {
                        // currentNode is not at beginning of list
                        currentPrev->next = currentAfter;
                    }
                    else
                    {
                        //if currentNode is the head then swap it with the nextNode after it
                        head = currentAfter;
                    }
                    //point currentNode->next to the one after next: c->n->n
                    currentNode->next = currentAfter->next;
                    //at the end of list
                    if (currentAfter->next != nullptr)
                    {
                        currentAfter->next->prev = currentNode;
                    }
                    else
                    {
                        tail = currentNode;
                    }
                    //update the link after dealing with the head and tail;
                    currentNode->prev = currentAfter;
                    currentAfter->next = currentNode;
                    currentAfter->prev = currentPrev;
                    //if the comparison is passed then list is still not sorted
                    isSorted = false;
                }
                else
                {
                    currentNode = currentNode->next;  //moves through the list
                }

            }
        }

    }

    //Only remove the duplicates while keep original order
    void removeMultiplies() {
        int intValA, intValB;
        string strValA, strValB;
        Node<T> *currentNode = nullptr;
        Node<T> *checkNode = nullptr;
        Node<T> *found = nullptr;
        //iterate the whole list
        for (currentNode = head; currentNode != nullptr; currentNode = currentNode->next) {
            // Go to the next Node after current Node
            checkNode = currentNode->next;
            while (checkNode != nullptr) {
                //get value at the current Node and check Node to check
                intValA = currentNode->value->getValue();
                strValA = currentNode->value->getName();
                intValB = checkNode->value->getValue();
                strValB = checkNode->value->getName();
                // Check node is duplicate or not
                if (intValA == intValB && strValA == strValB) {
                    found = checkNode;
                }
                // Go to the next Node
                checkNode = checkNode->next;

                if (found != nullptr) {
                    // When found the delete node we need to check these condition
                    if (found->prev != nullptr) {
                        found->prev->next = checkNode;
                    }
                    //this check if it is at the end of list
                    if (checkNode != nullptr) {
                        checkNode->prev = found->prev;
                    }
                    //this check if found is the tail
                    if (found == tail) {
                        // When remove last node
                        tail = found->prev;
                    }
                    //delete the dup by setting it to nullptr;
                    found->prev = nullptr;
                    found->next = nullptr;
                    found = nullptr;
                }
            }
        }
    }

    //Count the multiples
    int countMultiples(T *value) {
        //Setting variables
        int count = 0;
        int intValA, intValB;
        string strValA, strValB;
        Node<T> *checkNode = new Node<T> (value);// node hold value to check

        //set the current Node at the head
        Node<T> *currentNode = head;
                //iterate through
                do
                {
                    //get values in check Node
                    intValA = checkNode->value->getValue();
                    strValA = checkNode ->value ->getName();
                    //get value in temp Node to compare
                    intValB = currentNode->value->getValue();
                    strValB = currentNode -> value -> getName();
                    if((intValA == intValB) && (strValA == strValB))
                    {
                        count ++;
                    }
                    currentNode = currentNode->next; // go to next value
                }while (currentNode != nullptr);
                //free the new creating node
                free(checkNode);
        return count;
    }

    //Create 2 list that will hold the value for even and odd node
    void evenOddSplit()
    {

        Node <T> *evenHead = head; // start at index 0
        Node<T> *oddHead = head-> next; // start at index 1
        //create 2 linked list to store the nodes
        DoubleLinkedList<Data> *evenList = new DoubleLinkedList<Data> (evenHead->value);
        DoubleLinkedList<Data> *oddList = new DoubleLinkedList<Data> (oddHead->value);
        //loop through the list
        while(evenHead->next != nullptr || oddHead ->next != nullptr)
        {
            // evenHead start at node 0  and this will go to node 2 by skipping 1
            evenHead->next = evenHead->next->next;
            //update the node
            evenHead = evenHead->next;
            //when the list hit the node near end
            if(evenHead->next == nullptr)
            {
                //add the last node then break
                evenList->append(evenHead->value);
                break;
            }
            else
            {
                evenList->append(evenHead->value);
            }

            //this start from node [1] and go to node [3]
            oddHead->next = oddHead->next->next;
            oddHead = oddHead ->next;
            //when the list hit the node near end
            if(oddHead -> next == nullptr)
            {
                oddList->append(oddHead->value);
                break;
            }
            else
            {
                oddList->append(oddHead->value);
            }
        }
        cout << "Odd List: \n";
        oddList->printList();
        cout << endl;
        cout << "Even List:\n";
        evenList->printList();
        destroyList();
    }

    void destroyList()
    {
        head = nullptr;
        tail = nullptr;
    }


    void reverseList()
    {
        Node<T> *temp = nullptr;
        Node<T> *current = head;
        while(current != nullptr)
        {
            temp = current->next;
            current->next = current->prev;
            current->prev = temp;
            current= current->prev;
        }
        //swapping the position of head and tail
        temp = head;
        head = tail;
        tail = temp;

    }
}; // end of linkedlist

//helper function to disply menu
void menuDisplay()
{
    //Display Menu
    cout <<"=========================================";
    cout << "\nWelcome to Dat's Doubly linked list menu!" << endl;
    cout << "Please read the option: " << endl;
    cout << "a. Create a list" << endl;
    cout << "b. Delete a list" << endl;
    cout << "c. Insert at Head" << endl;
    cout << "d. Insert at Tail" << endl;
    cout << "e. Insert at Index" << endl;
    cout << "f. Delete at Head" << endl;
    cout << "g. Delete at Tail" << endl;
    cout << "h. Delete at Index" << endl;
    cout << "j. Reverse List" << endl;
    cout << "k. Sort List" << endl;
    cout << "l. Count Multiples" << endl;
    cout << "m. Delete Multiples" << endl;
    cout << "n. Split List Even Odd" << endl;
    cout << "q. Exit" << endl;
    cout << "Please choose the option above:\n";
};



// Main Program

int main() {
 //initialize variables
    char choice;
    int value;
    string name;
    int index;
    int count =0;
    bool isQuit = false;

   // Create a constructor for used in the menu;
    DoubleLinkedList<Data> *ll;
    Data *temp;
    int length;

    do {
        menuDisplay();
        cin >> choice;
        while((choice > 'z' && choice >'z') || (choice < 'a' &&choice <'A'))
        {
            cout <<"That is invalid input.\nPlease enter your character choice:\nPress any character other than those in the menu to quit";
            cin >> choice;
        }
        cout <<"=========================================\n";
        switch (toupper(choice)) {
            case 'A':
                cout << "Please enter the string value of the node: \n";
                cin >> name;
                cout << "Please enter the integer value of the node: \n";
                cin >> value;
                temp = new Data(value, name);
                // Creating Linked List
                ll = new DoubleLinkedList(temp);
                cout <<"Your new linked list is: \n";
                ll->printList();
                cout << endl;
                isQuit = false;
                break;

            case 'B':
                ll->destroyList();
                //test case to see if list is still appear:
                ll->printList();
                cout << "\nThe list is destroyed!\n";
                isQuit = true;
                break;

            case 'C':
                cout << "Please enter the string value of the node: \n";
                cin >> name;
                cout << "Please enter the integer value of the node: \n";
                cin >> value;
                temp = new Data(value, name);
                cout <<"This is the list before add:\n";
                ll->printList();
                ll->prepend(temp);
                cout <<"\nYour new linked list after adding new node is: \n";
                ll->printList();
                cout << endl;
                isQuit = false;
                break;

            case 'D':
                cout << "Please enter the string value of the node: \n";
                cin >> name;
                cout << "Please enter the integer value of the node: \n";
                cin >> value;
                temp = new Data(value, name);
                cout <<"This is the list before add:\n";
                ll->printList();
                ll->append(temp);
                cout <<"\nYour new linked list after adding new node is: \n";
                ll->printList();
                cout << endl;
                isQuit = false;
                break;

            case 'E':
                cout << "Please enter the string value of the node: \n";
                cin >> name;
                cout << "Please enter the integer value of the node: \n";
                cin >> value;
                length = ll->getLength();
                cout << "Length of the list is: "<< length << endl;
                cout << "Please enter the index you want to insert at: \n";
                cin >> index;

                while(index > length|| index < 0)
                {
                    cout << "Please enter correct index you want to insert at: \n";
                    cin >> index;
                }
                temp = new Data(value, name);
                cout <<"This is the list before add:\n";
                ll->printList();
                ll->insert(index,temp);
                cout <<"\nYour new linked list after adding new node is: \n";
                ll->printList();
                cout << endl;
                isQuit = false;
                break;

            case 'F':
                cout <<"This is the list before you delete:\n";
                ll->printList();
                ll->deleteAtHead();
                if(ll->getLength() > 0)
                {
                    cout <<"\nYour new linked list after delete is: \n";
                    ll->printList();
                }
                else
                {
                    cout << "\nThere is no more nodes to delete.";
                    ll->destroyList();
                    isQuit = true;
                    break;
                }
                cout << endl;
                isQuit = false;
                break;

            case 'G':
                cout <<"This is the list before you delete:\n";
                ll->printList();
                ll->deleteAtTail();
                if(ll->getLength() > 0)
                {
                    cout <<"\nYour new linked list after delete is: \n";
                    ll->printList();
                }
                else
                {
                    cout << "\nThere is no more nodes to delete.";
                    ll->destroyList();
                    isQuit = true;
                    break;
                }
                cout << endl;
                isQuit = false;
                break;

            case 'H':


                cout <<"Please enter the the index you want to delete at:\n";
                cin >> index;
                while(index >= ll->getLength()||index < 0)
                {
                    cout << "Please enter correct index you want to delete at: \n";
                    cin >> index;
                }
                cout <<"This is the list before you delete:\n";
                ll->printList();
                ll->deleteAtIndex(index);
                if(ll->getLength() > 0)
                {
                    cout <<"\nYour new linked list after delete is: \n";
                    ll->printList();
                }
                else
                {
                    cout << "\nThere is no more nodes to delete.";
                    ll->destroyList();
                    isQuit = true;
                    break;
                }
                cout << endl;
                isQuit = false;
                break;

            case 'J':
                cout<< "This is your list before reverse:\n";
                ll->printList();
                cout<<endl;
                ll->reverseList();
                cout <<"Your new linked list after reverse is: \n";
                ll->printList();
                cout << endl;
                isQuit = false;
                break;

            case 'K':
                cout <<"Your list before sorting is:\n";
                ll->printList();
                cout <<endl;
                ll->sortList();
                cout <<"Your new linked list after sort is: \n";
                ll->printList();
                cout << endl;
                isQuit = false;
                break;

            case 'L':
                cout <<"Enter the string value:\n";
                cin >> name;
                cout <<"Enter the integer value: \n";
                cin >> value;
                temp = new Data(value,name);
                count = ll->countMultiples(temp);
                ll->printList();
                cout << "\nThe value of [" << value << ", " << name << "] appeared " << count  << " times.\n";
                cout << endl;
                isQuit = false;
                break;

            case 'M':
                cout <<"This is the list before remove Duplicates:\n";
                ll->printList();
                ll->removeMultiplies();
                cout << endl;
                cout <<"This is the list after remove Duplicates:\n";
                ll->printList();
                cout << endl;
                isQuit = false;
                break;

            case 'N':
                cout <<"This is the list before the split:\n";
                ll->printList();
                cout << endl;
                ll->evenOddSplit();
                //test case to see if the list is destroy
                ll->printList();
                cout << "\nlist is destroyed after new two list are created" << endl;
                isQuit = true;
                break;

            default:
                isQuit = true;
                break;
        }
    }while(!isQuit);


    return 0;
}
