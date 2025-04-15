#include "templateStack.h"

int main() {
    int choice, stackSize;

    cout << "Choose data type for stack:\n";
    cout << "1. Integer\n2. Float\n3. Struct (Name, Age)\n4. String\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1: {
            mystack<int> stack;
            int value;
            cout << "Enter initial stack size (max " << getMaxSize() << "): ";
            cin >> stackSize;

            if (!initialize(stack, stackSize)) {
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
                        cout << "Enter value to push: ";
                        cin >> value;
                        push(stack, value);
                        break;

                    case 2: {
                        if (pop(stack, value)) {
                            cout << "Popped: " << value << endl;
                        } else {
                            cout << "Stack is empty!\n";
                        }
                        break;
                    }

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

        case 2: {
            mystack<float> stack;
            float value;
            cout << "Enter initial stack size (max " << getMaxSize() << "): ";
            cin >> stackSize;

            if (!initialize(stack, stackSize)) {
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
                        cout << "Enter value to push: ";
                        cin >> value;
                        push(stack, value);
                        break;

                    case 2: {
                        if (pop(stack, value)) {
                            cout << "Popped: " << value << endl;
                        } else {
                            cout << "Stack is empty!\n";
                        }
                        break;
                    }

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

        case 3: {
            mystack<MyStruct> stack;
            MyStruct value;
            cout << "Enter initial stack size (max " << getMaxSize() << "): ";
            cin >> stackSize;

            if (!initialize(stack, stackSize)) {
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
                        cout << "Enter name: ";
                        cin >> value.name;
                        cout << "Enter age: ";
                        cin >> value.age;
                        push(stack, value);
                        break;

                    case 2: {
                        if (pop(stack, value)) {
                            cout << "Popped: Name: " << value.name << ", Age: " << value.age << endl;
                        } else {
                            cout << "Stack is empty!\n";
                        }
                        break;
                    }

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

        case 4: {
            mystack<char*> stack;
            char* value = new char[50];
            cout << "Enter initial stack size (max " << getMaxSize() << "): ";
            cin >> stackSize;

            if (!initialize(stack, stackSize)) {
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
                        cout << "Enter string to push: ";
                        cin >> value;
                        push(stack, value);
                        break;

                    case 2: {
                        if (pop(stack, value)) {
                            cout << "Popped: " << value << endl;
                        } else {
                            cout << "Stack is empty!\n";
                        }
                        break;
                    }

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

        default:
            cout << "Invalid choice!\n";
            return 1;
    }
}
