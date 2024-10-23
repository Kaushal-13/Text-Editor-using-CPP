#include "gap_buffer.cpp"
using namespace std;

struct Node
{
    GapBuffer *g;
    Node *prev;
    Node *next;
    Node(string s)
    {
        g = new GapBuffer();
        g->initialize(s);
        prev = nullptr;
        next = nullptr;
    }
    ~Node()
    {
        delete g;
    }
};

Node *join(Node *a, Node *b)
{
    if (!a || !b)
    {
        return nullptr;
    }
    if (a->next != b)
    {
        return nullptr;
        // only join two consecutive nodes;
    }
    string s;
    for (char c : (a->g->v))
    {
        if (c != '\0')
            s += c;
    }
    for (char c : (b->g->v))
    {
        if (c != '\0')
            s += c;
    }
    cout << s << endl;
    Node *newNode = new Node(s);
    newNode->prev = a->prev;
    newNode->next = b->next;
    if (a->prev)
    {
        (a->prev)->next = newNode;
    }
    if (b->next)
    {
        (b->next)->prev = newNode;
    }
    delete a;
    delete b;
    return newNode;
}

int insert(Node *n, string s)
{
    if (!n)
    {
        return -1;
    }
    Node *a = new Node(s);
    a->next = n->next;
    a->prev = (n);
    if (n->next)
    {
        (n->next)->prev = a;
    }
    n->next = a;
    return 0;
}

void display(Node *head)
{
    Node *current = head; // Start from the head
    while (current)
    {
        current->g->display();
        cout << endl;
        current = current->next; // Move to the next node
    }
}
void clear(Node *head)
{
    Node *current = head; // Start from the head
    while (current)
    {
        Node *nextNode = current->next; // Store the next node
        delete current;                 // Delete the current node
        current = nextNode;             // Move to the next node
    }
    cout << "All nodes deleted." << endl;
}

Node *initialize_list(string s)
{
    Node *superhead = new Node("");
    string temp = "";
    Node *current = superhead;
    for (char c : s)
    {
        temp += c;
        if (c == '\n')
        {
            insert(current, temp);
            current = current->next;
            temp = "";
            cout << "Hello" << endl;
        }
    }
    insert(current, temp);
    return superhead;
}

void breakNode(Node *n)
{
    string temp = n->g->breakBuffer();
    insert(n, temp);
}

// int main()
// {
//     int x = 0;
//     string s = "";
//     while (x != 1)
//     {
//         char c;
//         cin >> c;
//         s += c;
//         if (c == 'p')
//             x = 1;
//     }
//     cout << s << endl;
//     Node *superhead = initialize_list(s);
//     display(superhead);
// }