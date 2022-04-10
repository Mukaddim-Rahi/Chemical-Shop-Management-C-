#include <iostream>
#include<string>
using namespace std;
struct Element
{
    int atomicNumber;
    string symbol;
    string name;
    Element *left;
    Element *right;
};
class ElementDatabase
{
private:
    Element* root;

    void addElement(Element *&e, int atomicNumber, string symbol, string name)
    {

        if(e == NULL)
        {
            e = new Element();
            e->atomicNumber = atomicNumber;
            e->symbol = symbol;
            e->name = name;
            e->left = NULL;
            e->right = NULL;
            return;
        }
        if(atomicNumber < e->atomicNumber)
        {
            addElement(e->left,atomicNumber,symbol,name);
        }
        else
        {
            addElement(e->right,atomicNumber,symbol,name);
        }

    }
    void printElements(Element *e)
    {
        if(e==NULL) return;
        printElements(e->left);
        cout<<e->atomicNumber<<", "<<e->symbol<<", "<<e->name<<endl;
        printElements(e->right);
    }
// Returns the address of the element if a match is found
// Return NULL if no match is found
    Element* findElementBySymbol(Element *e, string symbol)
    {
        if(e != NULL)
        {
            if((e->symbol.c_str(),symbol.c_str())==0)
            {
                return e;
            }
            else
            {
                Element *foundNode = findElementBySymbol(e->left,symbol);
                if(foundNode == NULL)
                {
                    foundNode = findElementBySymbol(e->right,symbol);
                }
                return foundNode;
            }
        }
        else
        {
            return NULL;
        }
    }
// Returns the address of the element if a match is found
// Return NULL if no match is found
    Element* findElementByName(Element *e, string name)
    {
        if(e != NULL)
        {
            if((e->name.c_str(),name.c_str())==0)
            {
                return e;
            }
            else
            {
                Element *foundNode = findElementByName(e->left,name);
                if(foundNode == NULL)
                {
                    foundNode = findElementByName(e->right,name);
                }
                return foundNode;
            }
        }
        else
        {
            return NULL;
        }
    }
    void deleteElement(Element *&e, int atomicNumber)
    {
        Element *temp = e;
        Element *prev = NULL;
        while(temp!=NULL && temp->atomicNumber != atomicNumber)
        {
            prev = temp;
            if(atomicNumber > temp->atomicNumber)
            {
                temp = temp->right;
            }
            else
            {
                temp = temp->left;
            }
        }

        if(temp!=NULL)
        {
            cout<<"\nDo you want to delete:"<<endl;
            cout<<temp->atomicNumber<<", "<<temp->symbol<<", "<<temp->name<<endl;
            char ch;
            cout<<"\nEnter y or n: ";
            cin >> ch;
            if(ch=='y'||ch=='Y')
            {
                // Check if the node to be
                // deleted has atmost one child.
                if (temp->left == NULL || temp->right == NULL)
                {

                    // newCurr will replace
                    // the node to be deleted.
                    Element* newCurr;

                    // if the left child does not exist.
                    if (temp->left == NULL)
                        newCurr = temp->right;
                    else
                        newCurr = temp->left;
                    // check if the node to
                    // be deleted is the root.
                    if (prev == NULL)
                    {
                        e = newCurr;
                        return;
                    }


                    // check if the node to be deleted
                    // is prev's left or right child
                    // and then replace this with newCurr
                    if (temp == prev->left)
                        prev->left = newCurr;
                    else
                        prev->right = newCurr;

                    // free memory of the
                    // node to be deleted.
                    delete temp;
                }
                // node to be deleted has
                // two children.
                else
                {
                    Element* p = NULL;
                    Element* temp2;

                    // Compute the inorder successor
                    temp2 = temp->right;
                    while (temp2->left != NULL)
                    {
                        p = temp2;
                        temp2 = temp2->left;
                    }
                    if (p != NULL)
                        p->left = temp2->right;
                    else
                        temp->right = temp2->right;

                    temp->atomicNumber = temp2->atomicNumber;
                    temp->symbol = temp2->symbol;
                    temp->name = temp2->name;
                    delete temp2;
                }
                cout<<"\nElement deleted successfully."<<endl;
            }
            else return;
        }
        else
        {
            cout<<"\nNo element was found."<<endl;
        }
    }
public:
    ElementDatabase()
    {
        root = NULL;
    }
    void addElement(int atomicNumber, string symbol, string name)
    {
        addElement(root, atomicNumber, symbol, name);
    }
    void printElements()
    {
        printElements(root);
    }
// Returns the address of the element if a match is found
// Return NULL if no match is found
    Element* findElementBySymbol(string symbol)
    {
        return findElementBySymbol(root, symbol);
    }
// Returns the address of the element if a match is found
// Return NULL if no match is found
    Element* findElementByName(string name)
    {
        return findElementByName(root,name);
    }
    void deleteElement(int atomicNumber)
    {
        deleteElement(root,atomicNumber);
    }
};
int main()
{
// Complete the functions above
// Add more functions if necessary
// Create the menu as shown in the example of program execution
// The program should only exit when the user chooses "Exit program"
    int choice,atomicNum;
    string symbol,name;
    ElementDatabase *obj = new ElementDatabase();
    Element *elm ;
    do
    {
        cout<<endl;
        cout<<"-----------------------------"<<endl;
        cout<<"1. Add an element"<<endl;
        cout<<"2. View elements"<<endl;
        cout<<"3. Search elements by chemical symbol"<<endl;
        cout<<"4. Search elements by element name"<<endl;
        cout<<"5. Delete an element"<<endl;
        cout<<"6. Exit program"<<endl;
        cout<<endl;
        cout<<"Enter your choice: ";
        cin >> choice;
        cout<<endl;
        switch(choice)
        {
        case 1:
            cout<<"* Add an element *"<<endl;
            cout<<"Enter atomic number: ";
            cin >> atomicNum;
            cout<<"Enter chemical symbol: ";
            cin >> symbol;
            cout<<"Enter element name: ";
            cin >> name;
            obj->addElement(atomicNum,symbol,name);
            cout<<"\nElement added successfully."<<endl;
            break;
        case 2:
            cout<<"* View Elements *"<<endl;
            obj->printElements();
            break;
        case 3:
            cout<<"* Search Elements by Chemical Symbol *\n"<<endl;
            cout<<"Enter chemical symbol: ";
            cin >> symbol;
            cout<<endl;
            cout<<"Search result:"<<endl;
            elm = obj->findElementBySymbol(symbol);
            if(elm!=NULL)
                cout<<elm->atomicNumber<<", "<<elm->symbol<<", "<<elm->name<<endl;
            else cout<<"No element was found."<<endl;
            break;
        case 4:
            cout<<"* Search Elements by Chemical Name *\n"<<endl;
            cout<<"Enter Element Name: ";
            cin >> name;
            cout<<endl;
            cout<<"Search result:"<<endl;
            elm = obj->findElementByName(name);
            if(elm!=NULL)
                cout<<elm->atomicNumber<<", "<<elm->symbol<<", "<<elm->name<<endl;
            else cout<<"No element was found."<<endl;
            break;
        case 5:
            cout<<"* Delete an element *\n"<<endl;
            cout<<"Enter atmoic number: ";
            cin >> atomicNum;
            obj->deleteElement(atomicNum);
            break;
        case 6:
            exit(0);
        }
    }
    while(choice!=6);
}

