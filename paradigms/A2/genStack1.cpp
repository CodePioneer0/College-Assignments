#include "GenericStack.h"
int main() {
    mystack stack;
    Data d;
    int choice, stackSize;
    DataType type;

    cout << "Choose data type for stack:\n";
    cout << "1. Integer\n2. Float\n3. Struct (Name, Age)\n4. String\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1: type = INT; break;
        case 2: type = FLOAT; break;
        case 3: type = STRUCT; break;
        case 4: type = STRING; break;
        default: cout << "Invalid choice!\n"; return 1;
    }

    cout << "Enter initial stack size (max " << getMaxSize() << "): ";
    cin >> stackSize;

    if (!initialize(stack, stackSize, type)) {
        cout << "Stack initialization failed!\n";
        return 1;
    }


    while (true) {
        cout << "\nChoose an option:\n";
        cout << "1. Push\n2. Pop\n3. Print Stack\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                if (isFull(stack)) {
                    cout << "Stack is full, inflating...\n";
                    if (!inflate(stack)) {
                        cout << "Failed to inflate stack.\n";
                        break;
                    }
                }

                cout << "Enter value to push: ";
                switch (stack.type) {
                    case INT:
                        cin >> d.i;
                        break;
                    case FLOAT:
                        cin >> d.f;
                        break;
                    case STRUCT:
                        cout << "Enter name: ";
                        cin >> d.s.name;
                        cout << "Enter age: ";
                        cin >> d.s.age;
                        break;
                    case STRING:
                        char temp[100];
                        cin.ignore();
                        cin.getline(temp, 100);
                        d.str = strdup(temp);
                        break;
                }
                push(stack, d);
                break;

            case 2:  
                if (pop(stack, d)) {
                    cout << "Popped: ";
                    switch (stack.type) {
                        case INT:
                            cout << d.i << endl;
                            break;
                        case FLOAT:
                            cout << d.f << endl;
                            break;
                        case STRUCT:
                            cout << d.s.name << " (" << d.s.age << ")" << endl;
                            break;
                        case STRING:
                            cout << d.str << endl;
                            free(d.str);
                            break;
                    }
                } else {
                    cout << "Stack is empty!\n";
                }
                break;

            case 3:  
                printStack(stack);
                break;

            case 4:  
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice!\n";
        }
    }
}
