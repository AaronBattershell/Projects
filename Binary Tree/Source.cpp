int main() {

    Node *n = new Node;

    int height = 0;
    int ch, numb, tmp;

    while (true) {

        cout << endl << endl;
        cout << " Binary Search Tree Operations " << endl;
        cout << " ----------------------------- " << endl;
        cout << " 1. Insertion " << endl;
        cout << " 2. Deletion " << endl;
        cout << " 3. Find the Depth " << endl;
        cout << " 4. Find the Cost " << endl;
        cout << " 5. Find the Balance " << endl;
        cout << " 6. Exit " << endl;
        cout << " Enter your choice : ";

        cin >> ch;

        switch (ch) {
            case 1: cout << " Enter number to be inserted : ";
                cin >> numb;
                search(numb);
                break;
            case 2: cout << endl;
                cout << " Insertion " << endl;
                cout << " --------- " << endl;
                insert();
                break;
            case 3: cout << endl;
                cout << " The Depth " << endl;
                cout << " --------- " << endl;
                get_Depth();
                break;
            case 4: cout << endl;
                cout << " The Cost " << endl;
                cout << " -------- " << endl;
                BST_cost();
                break;
            case 5: cout << endl;
                cout << " The Balance " << endl;
                cout << " ----------- " << endl;
                is_Balanced();
                break;
            case 6: cout << endl;
                cout << " Enter data to be deleted " << endl;
                cout << " -------- " << endl;
                cin >> tmp;
                remove(tmp);
                break;
            case 7:
                return 0;

        }
    }
}