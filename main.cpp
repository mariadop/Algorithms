#include <iostream>
using namespace std;

//All functions concerning list implementation are based on algorithms provided during AISD lectures
//(taken from presentation)

struct ListNode {
    char data;
    ListNode *next;
    ListNode(char d, ListNode* n = nullptr) : data(d), next(n) {}
};

struct Stack {
    ListNode *top;
    Stack *next;
};

//adds a new element to the next-pointer in the current last element of Stack
void AddLastToStack(Stack*& head, Stack* newElement) {
    if (head == nullptr) {
        head = newElement;
        return;
    }
    Stack *temp = head;
    if (temp->next != nullptr) {
        AddLastToStack(temp->next, newElement);
    }
    else {
        temp->next = newElement;
    }

}

//adds a new element to the next-pointer in the current last element of a List
void AddLastToList(ListNode *&top, ListNode *newElement) {
    if (top == nullptr) {
        top = newElement;
        return;
    }
    ListNode *temp = top;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    temp->next = newElement;
}

//returns the list added to the last Stack element
ListNode* GetLast(Stack *head) {
    if (head == nullptr) {
        return nullptr;
    }
    Stack *temp = head;
    if (temp->next != nullptr) {
        return GetLast(temp->next);
    }
    return temp->top;
}

//returns a pointer to the last element of the Stack - allows to factually modify the Stack
Stack* GetLastStack(Stack *head) {
    if (head == nullptr || head->next == nullptr) {
        return head;
    }
    return GetLastStack(head->next);
}

ListNode* GetLastListNode(ListNode *top) {
    if (top == nullptr || top->next == nullptr) {
        return top;
    }
    return GetLastListNode(top->next);
}

//returns the last (the first that was added) element of the specific ListNode
char GetLastFromList(ListNode *top) {
    if (top == nullptr) {
        return '\0';
    }
    ListNode *temp = top;
    if (temp->next != nullptr) {
        return GetLastFromList(temp->next);
    }
    return temp->data;
}

//removes last Stack element
void RemoveLast(Stack*& head) {
    if (head == nullptr) {
        return;
    }
    else if (head->next == nullptr) {
        delete head;
        head = nullptr;
    }
    else {
        RemoveLast(head->next);
    }
}

//removes last element from ListNode
void RemoveLastFromList(ListNode *&top) {
    if (top == nullptr) {
        return;
    }
    if (top->next == nullptr) {
        delete top;
        top = nullptr;
    }
    else {
        RemoveLastFromList(top->next);
    }
}

//removes the first added element of ListNode
void RemoveFirstFromList(ListNode*& top) {
    if (top == nullptr) return;

    ListNode* temp = top;
    top = top->next;
    delete temp;
}

//removes last element of Stack and returns the pointer to a still existing ListNode
//added so it wouldn't be always necessary to use CopyList
ListNode* RemoveLastWithPointer(Stack*& head) {
    if (head == nullptr) return nullptr;
    if (head->next == nullptr) {
        ListNode* savedTop = head->top;
        delete head;
        head = nullptr;
        return savedTop;
    }
    return RemoveLastWithPointer(head->next);
}

//prints the list in the reversed order of elements
void PrintListReversed(ListNode* top) {
    if (top == nullptr) return;
    PrintListReversed(top->next);
    cout << top->data;
}

//prints the stack
void PrintStack(Stack* head, int index) {
    if (head == nullptr) return;
    cout << index << ": ";
    index--;
    PrintListReversed(head->top);
    cout << endl;
    PrintStack(head->next, index);
}

//handling adding normal elements to ListNode
void handleNumbers(Stack* head, char c) {
    if (head->next == nullptr) {
        AddLastToList(head->top, new ListNode(c, nullptr));
    }
    else {
        handleNumbers(head->next, c);
    }

}

//finds the length of the Stack
int findLength(Stack* head, int length=1) {
    if (head == nullptr) return 0;
    if (head->next == nullptr) return length;
    return findLength(head->next, length+1);
}

//finds length of a list
int findListLength(ListNode* top, int length=1) {
    if (top == nullptr) return 0;
    if (top->next == nullptr) return length;
    return findListLength(top->next, length+1);
}

//returns a pointer to a list at a given index
ListNode* GetListAtIndex(Stack* head, unsigned long long index) {
    if (head == nullptr) return nullptr;
    if (index == (findLength(head, 1) - 1)) {
        return GetLast(head);
    }
    Stack *temp = head;
    if (temp->next == nullptr || index == 0) {
        return temp->top;
    }

    return GetListAtIndex(head->next, index - 1);
}

//converts a char-coded index to an integer
unsigned long long getIndexHelper(ListNode* top, unsigned long long result) {
    if (top == nullptr) return result;
    result = result * 10 + (top->data - '0');
    return getIndexHelper(top->next, result);
}

unsigned long long getIndex(ListNode* top) {
    if (top == nullptr) return 0;
    if (top->data == '-') {
        RemoveFirstFromList(top);
        return -getIndexHelper(top, 0);
    }
    return getIndexHelper(top, 0);
}

long long getSmallIndexHelper(ListNode* top, unsigned long long result) {
    if (top == nullptr) return result;
    result = result * 10 + (top->data - '0');
    return getSmallIndexHelper(top->next, result);
}

long long getSmallIndex(ListNode* top) {
    if (top == nullptr) return 0;

    if (top->data == '-') {
        ListNode* temp = top->next;
        return -getSmallIndexHelper(temp, 0);
    }
    return getSmallIndexHelper(top, 0);
}

//inserts a ListNode element at the beginning of already existing ListNode
void InsertAtTheBeginning(ListNode*& top, ListNode* newElement) {
    if (newElement == nullptr) return;
    if (newElement->next == nullptr) newElement->next = top;
    else {
        ListNode* temp = GetLastListNode(newElement);
        temp->next = top;
    }
    top = newElement;
}

//TODO: understand it better
ListNode* CopyList(ListNode* list, ListNode* tail = nullptr) {
    if (!list) return tail;
    ListNode* copy = new ListNode(list->data, nullptr);
    copy->next = CopyList(list->next, tail);
    return copy;
}

ListNode* fromIntToCharSequence(unsigned long long n, ListNode*& top) {
    unsigned long long help = n;
    if (n/10 != 0) {
        top = fromIntToCharSequence(help/10, top);
    }

    char el = (char) ((n % 10) + '0');
    AddLastToList(top, new ListNode(el, nullptr));
    return top;
}

ListNode* removeLeadingZeroes(ListNode*& l1) {
    char first = l1->data;
    int negative = 0;
    if (first == '-') {
        RemoveFirstFromList(l1);
        negative = 1;
    }
    if (l1 == nullptr) return l1;
    if (l1->data != '0') return l1;
    if (l1->next->data != '0') {
        ListNode* temp = l1;
        l1 = l1->next;
        delete temp;
        return l1;
    }
    if (l1->data == '0') {
        ListNode* temp = l1;
        l1 = l1->next;
        delete temp;
        return removeLeadingZeroes(l1);
    }
    if (negative == 1) {
        InsertAtTheBeginning(l1, new ListNode('-'));
    }
    return l1;
}

bool listsAreEqual(ListNode* l1, ListNode* l2) {
    removeLeadingZeroes(l1);
    removeLeadingZeroes(l2);
    if (l1 == nullptr && l2 == nullptr) return true;
    if (l1->data != l2->data) return false;
    if (l1->next != nullptr && l2->next != nullptr) return listsAreEqual(l1->next, l2->next);
    return true;
}



void addZeroes(ListNode*& l1, int toAdd) {
    if (toAdd == 0) {
        return;
    }
    ListNode* l2 = new ListNode('0');
    l2->next = l1;
    l1 = l2;
    addZeroes(l1, toAdd - 1);
}

int compareTwoLists(ListNode* l1, ListNode* l2) {
    if (l1 == nullptr && l2 == nullptr) return 0;
    if (l1->next == nullptr && l2->next == nullptr) return 0;
    int length1 = findListLength(l1);
    int length2 = findListLength(l2);

    if (length1 < length2) {
        addZeroes(l1, length2 - length1);
    }
    else if (length2 < length1) {
        addZeroes(l2, length1 - length2);
    }
    if (l1->data < l2->data) return 2;
    else if (l1->data > l2->data) return 1;
    return compareTwoLists(l1->next, l2->next);
}

int AddTwoListsHelper(ListNode* l1, ListNode* l2, ListNode*& result) {
    if (l1 == nullptr && l2 == nullptr) return 0;

    int rest = AddTwoListsHelper(l1->next, l2->next, result);

    int sum = (l1->data - '0') + (l2->data - '0') + rest;
    ListNode* l3 = new ListNode((sum % 10) + '0');

    l3->next = result;
    result = l3;

    return sum / 10;
}

ListNode* AddTwoLists(ListNode* l1, ListNode* l2, ListNode*& result) {
    int length1 = findListLength(l1);
    int length2 = findListLength(l2);

    if (length1 < length2) {
        addZeroes(l1, length2 - length1);
    }
    else if (length2 < length1) {
        addZeroes(l2, length1 - length2);
    }

    result = nullptr;
    int rest = AddTwoListsHelper(l1, l2, result);

    if (rest) {
        ListNode* l3 = new ListNode(rest + '0');
        l3->next = result;
        result = l3;
    }
    ListNode* r0 = nullptr;
    return result;
}

int SubtractTwoListsHelper(ListNode* l1, ListNode* l2, ListNode*& result, long long& maxLength) {
    if ((l1 == nullptr && l2 == nullptr)) {
        return 0;
    }

    int rest = SubtractTwoListsHelper(l1->next, l2->next, result, maxLength);
    maxLength--;

    if (maxLength < 0) return rest;
    int difference = ((l1->data - '0') - rest) - (l2->data - '0');

    rest = 0;
    if (difference < 0) {
        difference += 10;
        rest = 1;
    }
    ListNode* l3 = new ListNode(difference + '0');
    l3->next = result;
    result = l3;

    return rest;
}

ListNode* SubtractTwoLists(ListNode* l1, ListNode* l2, ListNode*& result) {
    //added so the functions wouldn't operate on modified part of Stack that was already deleted (in removeLeadingZeroes)
    ListNode* l10 = CopyList(l1);
    ListNode* l20 = CopyList(l2);
    l10 = removeLeadingZeroes(l10);
    l20 = removeLeadingZeroes(l20);
    long long maxLength = 0;
    int newLength1 = findListLength(l10);
    int newLength2 = findListLength(l20);
    if (newLength1 < newLength2) maxLength = newLength2;
    else maxLength = newLength1;

    if (newLength1 < newLength2) {
        addZeroes(l10, newLength2 - newLength1);
    }
    else if (newLength2 < newLength1) {
        addZeroes(l20, newLength1 - newLength2);
    }
    int compare = compareTwoLists(l10, l20);
    result = nullptr;
    if (compare == 1) {
        SubtractTwoListsHelper(l10, l20, result, maxLength);
    }
    else if (compare == 2) {
        SubtractTwoListsHelper(l20, l10, result, maxLength);
    }
    else {
        result = new ListNode('0');
    }
    ListNode* result0 = nullptr;
    result0 = removeLeadingZeroes(result);
    return result0;
}

//handling behaviours of all signs added in the input command line
void handleSigns(Stack*& head, char elements[], int& mode, unsigned long long& instruction) {
    char c = elements[instruction];
    if (((int) c <= 57 && (int) c >= 48) && mode == 1) {
        handleNumbers(head, c);
    }
    else if ((int) c == '\'') {
        //if it's not the first usage of ' then we add another stack element
        if (mode != 2) {
            Stack* n1 = new Stack();
            n1->top = nullptr;
            n1->next = nullptr;
            AddLastToStack(head, n1);
        }
        mode = 1;
    }
    else if (c == ',') {
        RemoveLast(head);
    }
    else if (c == ':') {
        ListNode* l1 = nullptr;
        l1 = GetLast(head);
        Stack* n2 = new Stack();
        n2->top = CopyList(l1);
        n2->next = nullptr;
        AddLastToStack(head, n2);
    }
    else if (c == ';') {
        ListNode* l1 = RemoveLastWithPointer(head);
        ListNode* l2 = RemoveLastWithPointer(head);
        Stack* n3 = new Stack();
        n3->top = l1;
        n3->next = nullptr;

        Stack* n4 = new Stack();
        n4->top = l2;
        n4->next = nullptr;


        AddLastToStack(head, n3);
        AddLastToStack(head, n4);
    }
    else if (c == '&') {
        PrintStack(head, findLength(head, 1) - 1);
    }
    else if (c == '@') {
        ListNode* l1 = GetLast(head);
        int length = findLength(head, 1) - 2;

        //length - 3, index - 2 --> 0 (3 - 1 - 2)
        //length - 2, index - 0 --> 1 (2 - 1 - 0)

        unsigned long long index = length - getIndex(l1);
        RemoveLast(head);

        ListNode* l2 = GetListAtIndex(head, index);

        Stack* n5 = new Stack();
        n5->top = CopyList(l2);
        n5->next = nullptr;
        AddLastToStack(head, n5);
    }
    else if (c == '.') {
        char el;
        cin >> el;
        handleNumbers(head, el);
    }

    else if (c == '>') {
        ListNode* lastList = GetLast(head);
        if (lastList != nullptr) {
            char last = GetLastFromList(lastList);
            cout << last;
            RemoveLast(head);
        }
    }

    else if (c == '-') {
        if (GetLast(head) == nullptr) {
            handleNumbers(head, c);
            return;
        }

        Stack* lastStack = GetLastStack(head);
        if (lastStack != nullptr && lastStack->top != nullptr) {
            if (lastStack->top->data == '-') {
                RemoveFirstFromList(lastStack->top);
            }
            else {
                InsertAtTheBeginning(lastStack->top, new ListNode(c));
            }
        }
    }

    else if (c == '^') {
        Stack* lastStack = GetLastStack(head);
        if (lastStack != nullptr && lastStack->top != nullptr && lastStack->top->data == '-') {
            RemoveFirstFromList(lastStack->top);
        }
    }

    else if (c == ']') {
        ListNode* l1 = GetLast(head);
        unsigned long long number = getIndex(l1);
        RemoveLast(head);
        Stack* n1 = new Stack();
        n1->top = nullptr;
        n1->next = nullptr;
        AddLastToStack(head, n1);
        handleNumbers(head, (char) number);
    }

    else if (c == '[') {
        ListNode* l2 = GetLast(head);
        char last = GetLastFromList(l2);
        unsigned long long number = (int) last;
        ListNode* l3 = nullptr;
        l3 = fromIntToCharSequence(number, l3);
        RemoveLast(head);
        Stack* n1 = new Stack();
        n1->top = l3;
        n1->next = nullptr;
        AddLastToStack(head, n1);
    }

    else if (c == '$') {
        Stack* lastStack = GetLastStack(head);
        char firstElementFromLast = '0';
        if (lastStack != nullptr && lastStack->top != nullptr) {
            firstElementFromLast = GetLastFromList(lastStack->top);
            RemoveLastFromList(lastStack->top);
        }
        Stack* n1 = new Stack();
        n1->top = nullptr;
        n1->next = nullptr;
        AddLastToStack(head, n1);
        handleNumbers(head, firstElementFromLast);
    }

    else if (c == '#') {
        ListNode* l1 = RemoveLastWithPointer(head);
        Stack* lastStack = GetLastStack(head);
        if (lastStack != nullptr && lastStack->top != nullptr) {
            InsertAtTheBeginning(lastStack->top, l1);
        }
        else {
            Stack* n1 = new Stack();
            n1->top = l1;
            n1->next = nullptr;
            AddLastToStack(head, n1);
        }
    }

    else if (c == '<') {
        Stack* n1 = new Stack();
        n1->top = nullptr;
        n1->next = nullptr;
        ListNode* l1 = GetLast(head);
        RemoveLast(head);
        ListNode* l2 = GetLast(head);
        RemoveLast(head);
        AddLastToStack(head, n1);
        long long num1 = getSmallIndex(l1);
        long long num2 = getSmallIndex(l2);
        if (num2 < num1) {
            handleNumbers(head, '1');
        }
        else {
            handleNumbers(head, '0');
        }
    }

    else if (c == '=') {
        Stack* n1 = new Stack();
        n1->top = nullptr;
        n1->next = nullptr;

        ListNode* l1 = GetLast(head);
        int length1 = findListLength(GetLast(head));
        RemoveLast(head);

        ListNode* l2 = GetLast(head);
        int length2 = findListLength(GetLast(head));
        RemoveLast(head);
        AddLastToStack(head, n1);

        unsigned long long num1 = getIndex(l1);
        unsigned long long num2 = getIndex(l2);
        if (length1 < 17 || length2 < 17 || (num1 == 0 && num2 == 0)) {
            if (num1 == num2) {
            handleNumbers(head, '1');
            }
            else {
                handleNumbers(head, '0');
            }
        }
        else if (listsAreEqual(l1, l2)) {
            handleNumbers(head, '1');
        }
        else {
            handleNumbers(head, '0');
        }
    }

    else if (c == '!') {
        ListNode* l1 = GetLast(head);
        if (l1 == nullptr || (l1->data == '0' && (findListLength(l1, 1) == 1))) {
            RemoveLast(head);
            Stack* n1 = new Stack();
            n1->top = nullptr;
            n1->next = nullptr;
            AddLastToStack(head, n1);
            handleNumbers(head, '1');
        }
        else {
            RemoveLast(head);
            Stack* n1 = new Stack();
            n1->top = nullptr;
            n1->next = nullptr;
            AddLastToStack(head, n1);
            handleNumbers(head, '0');
        }
    }

    else if (c == '?') {
        ListNode* l1 = RemoveLastWithPointer(head);
        if (l1 == nullptr) {
            return;
        }
        unsigned long long num1 = getIndex(l1);
        ListNode* l2 = RemoveLastWithPointer(head);
        if (l2 == nullptr || (l2->data == '0' && (findListLength(l2, 1) == 1))) {}
        else {
            instruction = num1 - 1;
        }

    }

    else if (c == '~') {
        ListNode* l1 = nullptr;
        l1 = fromIntToCharSequence(instruction, l1);
        if (mode != 2) {
            Stack* n1 = new Stack();
            n1->top = l1;
            n1->next = nullptr;
            AddLastToStack(head, n1);
        }
        else {
            AddLastToList(head->top, l1);
            mode = 0;
        }
    }

    else if (c == '+') {
        ListNode* l1 = CopyList(GetLast(head));
        int length1 = findListLength(l1);
        RemoveLast(head);
        long long num1 = 0;
        ListNode* l2 = CopyList(GetLast(head));
        int length2 = findListLength(l2);
        RemoveLast(head);
        long long num2 = 0;

        if (length1 > 17) {
            if (l1->data != '-' && l2->data != '-') {
                ListNode* l4 = nullptr;
                l4 = AddTwoLists(l1, l2, l4);
                Stack* n1 = new Stack();
                n1->top = l4;
                n1->next = nullptr;
                AddLastToStack(head, n1);
                return;
            }
            else if (l1->data == '-' && l2->data == '-') {
                RemoveFirstFromList(l1);
                RemoveFirstFromList(l2);
                ListNode* l4 = nullptr;
                l4 = AddTwoLists(l1, l2, l4);
                InsertAtTheBeginning(l4, new ListNode('-'));
                Stack* n1 = new Stack();
                n1->top = l4;
                n1->next = nullptr;
                AddLastToStack(head, n1);
                return;
            }
            else if (l1->data != '-' && l2->data == '-') {
                RemoveFirstFromList(l2);
                ListNode* l4 = nullptr;
                l4 = SubtractTwoLists(l1, l2, l4);
                int compare = compareTwoLists(l1, l2);
                if (compare == 2) InsertAtTheBeginning(l4, new ListNode('-'));
                Stack* n1 = new Stack();
                n1->top = l4;
                n1->next = nullptr;
                AddLastToStack(head, n1);

                return;
            }
            else if (l1->data == '-' && l2->data != '-') {
                RemoveFirstFromList(l1);
                ListNode* l4 = nullptr;
                l4 = SubtractTwoLists(l1, l2, l4);
                int compare = compareTwoLists(l1, l2);
                if (compare == 1) InsertAtTheBeginning(l4, new ListNode('-'));
                Stack* n1 = new Stack();
                n1->top = l4;
                n1->next = nullptr;
                AddLastToStack(head, n1);
                return;
            }
        }
        else {
            num1 = getSmallIndex(l1);
        }

        if (length2 > 17) {
            if (l1->data != '-' && l2->data != '-') {
                ListNode* l4 = nullptr;
                l4 = AddTwoLists(l1, l2, l4);
                Stack* n1 = new Stack();
                n1->top = l4;
                n1->next = nullptr;
                AddLastToStack(head, n1);
                return;
            }
            else if (l1->data == '-' && l2->data == '-') {
                RemoveFirstFromList(l1);
                RemoveFirstFromList(l2);
                ListNode* l4 = nullptr;
                l4 = AddTwoLists(l1, l2, l4);
                InsertAtTheBeginning(l4, new ListNode('-'));
                Stack* n1 = new Stack();
                n1->top = l4;
                n1->next = nullptr;
                AddLastToStack(head, n1);
                return;
            }
            else if (l1->data != '-' && l2->data == '-') {
                RemoveFirstFromList(l2);
                ListNode* l4 = nullptr;
                l4 = SubtractTwoLists(l1, l2, l4);
                int compare = compareTwoLists(l1, l2);
                if (compare == 2) InsertAtTheBeginning(l4, new ListNode('-'));
                Stack* n1 = new Stack();
                n1->top = l4;
                n1->next = nullptr;
                AddLastToStack(head, n1);

                return;
            }
            else if (l1->data == '-' && l2->data != '-') {
                RemoveFirstFromList(l1);
                ListNode* l4 = nullptr;
                l4 = SubtractTwoLists(l1, l2, l4);
                int compare = compareTwoLists(l1, l2);
                if (compare == 1) InsertAtTheBeginning(l4, new ListNode('-'));
                Stack* n1 = new Stack();
                n1->top = l4;
                n1->next = nullptr;
                AddLastToStack(head, n1);
                return;
            }
        }
        else {
            num2 = getSmallIndex(l2);
        }

        long long sum = num1 + num2;
        int absolute = abs(sum);
        ListNode* l3 = nullptr;
        l3 = fromIntToCharSequence(absolute, l3);
        if (sum < 0) {
            InsertAtTheBeginning(l3, new ListNode('-'));
        }
        Stack* n1 = new Stack();
        n1->top = l3;
        n1->next = nullptr;
        AddLastToStack(head, n1);
    }

    else {
        if (mode == 1) {
            handleNumbers(head, c);
        }
    }
}

int main() {

    int mode = 2;

    char elements[20000];
    cin >> elements;
    Stack *head = new Stack;
    head->top = nullptr;
    head->next = nullptr;
    for (int i = 0; elements[i] != '\0'; ++i) {
         unsigned long long instruction = i;
         handleSigns(head, elements, mode, instruction);
         i = (int) instruction;
    }

    return 0;
}