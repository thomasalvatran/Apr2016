//mycodeschool Binary search tree
//AllSort + ADT
#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <array>
#include <stdlib.h>
#include <limits.h>
#include <functional>
#include <stack>

using namespace std;

int rand_int(int a, int b)
{
    return (a + rand()) % b;
}

void print(int a[], int n)
{
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    cout << "\n";
}

void swap(int a[], int i, int j)
{
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

void insertSort(int a[], int n)
{
    int i, j, value;
    for (i =0; i < n; i++)
    {
        value = a[i];
        for (j = i; j > 0 && value < a[j -1]; j--)
            a[j] = a[j -1];
        a[j] = value;
    }
}
/* void bubbleSort(int *a, int n)
   void bubbleSort(int (&a)[4])
*/
void bubbleSort(int a[], int n)
{
   int i, j;
   for (i = 1; i < n; i++)
       for (j = n-1; j >= i; j--)
           if (a[j] < a[j -1])
               swap(a, j, j-1);
}

void selectSort(int a[], int n)
{
    int i, j, min;
    for (i = 0; i < n; i++)
    {
        min = i;
        for (j = i; j < n; j++)
            if (a[j] < a[min])
                min = j;
            swap(a, i, min);
    }
}
//http://geeksquiz.com/quick-sort/
int partition(int a[], int l, int r)
{
    int p = a[l];
//    while (l < r)
//    {
//        while (a[l] < p)
//            l++;
//        while (a[r] > p)
//            r--;
//        if (l < r)
//            swap (a, l, r);
//    }
    while (l < r && a[l] < p)
        l++;
    while (l < r && a[r] > p)
        r--;
    if (l < r)
        swap (a, l, r);
    return r;
}

void quickSort(int a[],  int l, int r)
{
    int m;
    if (l < r)
    {
        m = partition(a, l, r);
        quickSort(a, l, m -1);
        quickSort(a, m + 1, r);
    }

}

void shellSort(int a[], int n)
{
    int gap, i, j, temp;
    for (gap = n/2; gap > 0; gap /= 2)
        for (i = gap; i < n; i++)
            for (j = i - gap; j >= 0 && a[j] > a[j + gap]; j -= gap)
            // {
                swap(a, j, j + gap);
            // }
}
//http://geeksquiz.com/merge-sort/
void merge(int a[], int l, int m, int r) {
  int n = r - l + 1;
  int t[n];
  int i1 = l;
  int i2 = m + 1;
  int j = 0;
  while (i1 <= m && i2 <= r) {
    if (a[i1] < a[i2]) {
      t[j] = a[i1];
      i1++;
    } else {
      t[j] = a[i2];
      i2++;
    }
    j++;
  }
  while (i1 <= m) {
    t[j] = a[i1];
    i1++;
    j++;
  }
  while (i2 <= r) {
    t[j] = a[i2];
    i2++;
    j++;
  }
  for (j = 0; j < n; j++)
    a[l + j] = t[j];
}

void mergeSort(int a[], int l, int r)
{
   if (l >= r)
       return;
   int m = (l + r) / 2;
   mergeSort(a, l, m);
   mergeSort(a, m + 1, r);
   merge(a, l, m, r);
}

void isPrime(int n)
{
    int flag = 0, i;
    for (i = 2; i <= n/2; i++)
    {
        flag = 0;
        if (n % 2 == 0)
        {
            flag = 1;
            break;
        }
    }
    cout << (flag == 0 ? "Prime" : "Not Prime") << endl;
}

int factorial(int n)
{
    if (n > 1)
     return n * factorial(n - 1);
    else
     return n;
}

int factor (int n)
{
    int temp = 1;
    for (int i = 1; i <= n; i++)
        temp *= i;
    return temp;
}

int fibonacci (int n)
{
    if (n > 2)
        return fibonacci( n -1 ) + fibonacci(n - 2);
    else
        return n;
}

//1 1 2 3 5 8 13
int fibo (int n)
{
    int prev1, prev2, temp;
    if (n > 1)
    {
        prev1 = prev2 = 1;
        for (int i = 2; i <= n; i++)
        {
            temp = prev1 + prev2;
            prev2 = prev1;
            prev1 = temp;
        }
    }
    return temp;
}

// int f[] = new int[max];
int *f = new int[10];
int fibocache(int i) 
{
    if (i == 0) return 0;
    if (i == 1) return 1;
    if (i > 2)
    {
    if (f[i] != 0) return f[i]; // Return cached result.
        f[i] = fibocache(i - 1) + fibocache(i - 2); // Cache result
        return f[i];
    }
}

function<int(int)> fib = [](int x) { return x < 2 ? 1 : fib(x -1 ) + fib(x - 2);};

/**********************Queue ADT Array *****************************/
#ifdef INCLUDE //dummy
    #include <iostream>
    #include <stdio.h>
    #include <vector>
    #include <algorithm>
#endif
using namespace std;

const int SIZE = 5;
int Array[SIZE];

int rear = 0, front = 0;

bool isFull()
{
    return (rear + 1) % SIZE == front;
}
bool isEmpty()
{
    return (rear == 0 && front == 0);
}
void enqueueArray(int data)
{
    if(isFull())
    {
        cout << "Queue is full for data " << data << endl;
        return;
    }
    rear = (rear + 1) % SIZE;
    Array[rear] = data;
}
void dequeueArray()
{
    if (isEmpty())
    {
        cout << "Queue is empty " << endl;
        return;
    }
    front = (front + 1) % SIZE;
}
void printArray()
{
    int count = (SIZE + rear - front) % SIZE + 1;
    for (int i = 1; i < count; i++)
    {
        int index = (front + i) % SIZE;
        cout << Array[index] << "[" << index << "] ";
    }
    cout << "\n";
}
/***********************Queue LinkedList ***************************/
struct Node
{
    int data;
    struct Node *next;
};
struct Node *rearLL = NULL, *frontLL = NULL;
void enqueueLinkedList(int data)
{
    struct Node *temp = new Node;
    temp->data = data;
    temp->next = NULL;
    if (rearLL == NULL && frontLL == NULL)
    {
        rearLL = frontLL = temp;
        return;
    }
    rearLL->next = temp;
    rearLL = temp;
}
void dequeueLinkedList()
{
    if (frontLL == NULL)
    {
        cout << "Queue is empty" << endl;
        return;
    }
    else if (frontLL == rearLL)
        frontLL = rearLL = NULL;
    else
        frontLL = frontLL->next;
}
void printLinkedList()
{
    Node *temp = frontLL;
    while (temp != NULL)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << "\n";
}

void swapNode (Node *first, Node *second)
{
    int tmpValue = first->data;
    first->data = second->data;
    second->data = tmpValue;
}

/***********************Queue ADT Tree *****************************/
struct BstNode
{
    int data;
    struct BstNode *left = 0, *right = 0;
};
BstNode *root = NULL; //root is global

BstNode* createNode(int data)
{
    BstNode *temp = new BstNode;
    temp->data = data;
    temp->left = temp->right = 0;
    return temp;
}
BstNode* insertNode(BstNode *root, int data);
BstNode* enqueueTree(BstNode *root, int data)
{
    root = insertNode(root, data);
    return root;
}
BstNode* dequeueMinTree(BstNode* root) //smallest in balance tree Aug 8, 2018
{
     BstNode *temp = root, *prev;
   if (root == NULL || root ->left == 0)
      return root;
   
    while (temp->left != 0) //check last node
    {
        prev = temp;
        temp = temp->left;
    }
    if (temp->left == 0 && temp->right == 0) // no left no right
    {    
        delete temp;                  //delete node
        prev->left = 0;               //cut the link
    }
    else if (temp->left != 0)         //has left
    {
        delete temp->left;          
        prev->left->left = 0;
    }
    else if (temp->right != 0)         //has right
    {
        delete temp->right;
        prev->left->right = 0;
    }
    return root;
}

BstNode* dequeueMaxTree(BstNode *root)
{
    BstNode *temp = root, *prev = 0;
    if (root == NULL)
        return root;
    while (temp->right != NULL)
    {
        prev = temp;
        temp = temp->right;
    }
    delete temp;
    prev->right = NULL; //set to none cut link
    return root;
}

//Method 1: use global root
void insertNodeGlobal(int data)
{
    BstNode *temp = root, *prev = 0;
    if (root == NULL)
    {
        root = createNode(data);
        printf("Create root\n");
        return;
    }
    while (temp)
    {
        prev = temp;
        if (data < temp->data)
            temp = temp->left;
        else
            temp = temp->right;
    }
    if (data < prev->data)
        prev->left = createNode(data);
    else
        prev->right = createNode(data);

}
//Method 2 use reference
void insertNodeRef(BstNode **root, int data)
{
    BstNode *temp = *root, *prev = 0;
    if (*root == NULL)
    {
        *root = createNode(data);
        printf("Create root\n");
        return;
    }
    while (temp)
    {
        prev = temp;
        if (data < temp->data)
            temp = temp->left;
        else
            temp = temp->right;
    }
    if (data < prev->data)
        prev->left = createNode(data);
    else
        prev->right = createNode(data);

}
//Method 3: Normal pass by pointer in C
BstNode* insertNode(BstNode *root, int data)
{
    BstNode *temp = root, *prev = 0;
    if (root == NULL)
    {
        root = createNode(data);
        printf("Create root 1\n");
        return root;
    }

    while (temp)                  // find empty tree
    {
        prev = temp;              //store prev tree
        if (data < temp->data)
          temp = temp->left;
        else
          temp = temp->right;
    }  
    if (data < prev->data)
        prev->left = createNode(data);
    else
        prev->right = createNode(data);

    return root;
}
//Method 4: recursive
BstNode* insertNodeRecursive(BstNode *root, int data)
{
    if (root == NULL)
    {
        root = createNode(data);
        printf("Create root 1\n");
        return root;
    }
    if (data <= root->data)
        root->left = insertNodeRecursive(root->left, data);
    else 
        root->right = insertNodeRecursive(root->right, data);
    return root;
}


void printTree(BstNode *root)
{
    if (root)
    {
        printTree(root->left);
        printf("%d ", root->data);
        printTree(root->right);
    }
}
//printTree using stack
void in_order_traversal_iterative(BstNode *root) {
  stack<BstNode*> s;
  BstNode *current = root;
  while (!s.empty() || current) 
  {
    if (current) {
      s.push(current);
      current = current->left;
    } else {
      current = s.top();
      s.pop();
      cout << current->data << " ";
      current = current->right;
    }
  }
}

BstNode* deleteTree(BstNode* root)
{
    if (root)
    {
        deleteTree(root->left);
        deleteTree(root->right);
        free(root);
        root = NULL;
    }
    return root;
}
int findMax(BstNode* root)
{
    BstNode *temp = root;
    if (root == NULL)
    {
        printf("Tree is empty\n");
        return -1;
    }
    while (temp->right != NULL)
        temp = temp->right;
    return temp->data;
}

int findMin(BstNode *root)
{
    if (root == NULL)
    {
        cout << "Empty tree" << endl;
        return -1;
    }
    BstNode *temp = root;
    while (temp->left != NULL)
        temp = temp->left;
    return temp->data;
}

BstNode* findMinNode(BstNode *root)
{
    BstNode *temp = root;
    if (root == NULL)
    {
        printf("Tree is empty\n");
        return 0;
    }
    while (temp->left != NULL)
        temp = temp->left;
    return temp;
}

BstNode* removeNode(BstNode* root, int data)
{
    if (root == NULL)
        return root;
    if (data < root->data)
        root->left = removeNode(root->left, data);
    else if (data > root->data) 
        root->right = removeNode (root->right, data);
    else
    {
        if (root->left == NULL && root->right == NULL)
        {
            delete root;
            return NULL;
        }
        else if (root->left == NULL)
        {
            BstNode* temp = root;
            root = root->right;
            delete temp;
        }
        else if (root->right == NULL)
        {
            BstNode* temp = root;
            root = root->left;
            delete temp;
        }
        else
        {
            BstNode *temp = findMinNode(root->right); //find min in right subtree
            // temp->data = findMax(root->left);   // find max in left subtree
            root->data = temp->data;
            root->right = removeNode(root->right, temp->data);
        }

    }
    return root;
}

vector<int> vec; //global
void treetoBST(BstNode *root)
{
    if (root)
    {
        treetoBST(root->left);
        vec.push_back(root->data); //push end vector
        treetoBST(root->right);
    }
}
int binsearch(int x, vector<int> v, int n)
{
    int low = 0, mid = 0;
    int high = n - 1;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if ( x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else
            return mid;
    }
    return -1; //not found
}
bool binsearchRecursive(BstNode *root, int data)
{
    if (root == NULL)
        return false;
    else if (root->data == data)
        return true;
    else if (data <= root->data)
        return binsearchRecursive(root->left, data);
    else
        return binsearchRecursive(root->right, data);
}

bool isSubtreeLesser(BstNode* root, int data)
{
    if (root == NULL)
        return true;
    else if (root->data <= data
        && isSubtreeLesser(root->left, data)
        && isSubtreeLesser(root->right, data))
        return true;
    else
        return false;
}
bool isSubtreeGreater(BstNode* root, int data)
{
    if (root == NULL)
        return true;
    else if (root->data > data
        && isSubtreeGreater(root->left, data)
        && isSubtreeGreater(root->right, data))
        return true;
    else
        return false;
}

bool isBinarySearchTree(BstNode *root)
{
    if (root == NULL)
        return true;
    if (isSubtreeLesser(root->left, root->data)
       && isSubtreeGreater(root->right, root->data)
       && isBinarySearchTree(root->left)
       && isBinarySearchTree(root->right))
       return true;
    else
        return false;
}

bool isBinarySearchTreeUpperLower(BstNode *root, int lower, int upper)
{
    if (root == NULL)
        return true;
    if (root->data > lower
       && root->data < upper
       && isBinarySearchTreeUpperLower(root->left, lower, root->data)
       && isBinarySearchTreeUpperLower(root->right, root->data, upper))
       return true;
    else
        return false;
}

bool isBSTUpperLower(BstNode *root)
{

    return isBinarySearchTreeUpperLower(root, INT_MIN, INT_MAX);

}

bool isBST(BstNode* root)
{
    if (root == NULL)
        return true;
    if (isSubtreeLesser(root->left, root->data)
        && isSubtreeGreater(root->right, root->data)
        && isBinarySearchTree(root->left)
        && isBinarySearchTree(root->right))
            return true;
    else
        return false;

}
bool searchNode(BstNode *root, int data)
{
    return binsearchRecursive(root, data);
}
struct // lesser
{
    bool operator()(int a, int b)
    {
      return a < b;
    }
} customless;
/*bool comp(int a, int b)*/
int comp(int a, int b)
{
    return a < b;
}

//http://en.cppreference.com/w/cpp/algorithm/sort
void sortArray(int a[])
{
   //Sorting an array
   sort(a, a+SIZE); //sort array
   std::array<int, SIZE -1> arr ; //convert array to template array
   //Method 1: Sorting template array using greater
   for (int i = 1; i < SIZE; i++)
       arr[i-1] = a[i];
    sort(arr.begin(), arr.end(), greater<int>()); //sort template
    for (int a : arr)
    {
        cout << a << " ";
    }
    cout << '\n';
    //Method 2: Sorting template array using custom
    sort(arr.begin(), arr.end(), customless); //struct
    sort(arr.begin(), arr.end(), comp);       //function thinking in C++ media
    for (int a : arr)
    {
        cout << a << " ";
    }
    //Method 3: Sorting template array using lambda
    cout << '\n';
    // sort using a lambda expression
    std::sort(arr.begin(), arr.end(), [](int a, int b) {
        cout << "lambda compare " << a << " " << b << " " << endl;
       return b < a;
     });
    for (int a : arr) {
       std::cout << a << " ";
    }
    std::cout << '\n';
}

int main()
{
    isPrime(4);
    cout << "Factorial(4) " << factorial(4) << endl;
    cout << "Fibonacci(5) " << fibonacci(5) << endl;
    cout <<  "*********** Sorting ***********" << endl;
    int a[4];
    srand(time(0));
    for (int i = 0; i < 3; i++)
        a[i] = rand_int(1, 100);
    // insertSort(a, 4);
    // print(a, 4);
    mergeSort(a, 0, 3);
    print(a, 4);
    cout <<  "***********Queue Array ***********" << endl;
    enqueueArray(12);
    enqueueArray(4);
    enqueueArray(5);
    enqueueArray(15);
    printArray();
    cout <<  "***********Queue Linked List ***********" << endl;
    enqueueLinkedList(22);
    enqueueLinkedList(23);
    enqueueLinkedList(29);
    enqueueLinkedList(124);
    enqueueLinkedList(24);
    printLinkedList();
    dequeueLinkedList();
    printLinkedList();
    bool isSwapped;
    Node *temp = NULL;
    do 
    {
        temp = frontLL;
        isSwapped = false;
        while (temp->next != NULL)
        {
            if (temp->data > temp->next->data)
            {
                swapNode(temp, temp->next);
                isSwapped = true;
            }
            temp = temp->next;
        }
    }while (isSwapped);
    printLinkedList();
    cout <<  "***********Queue Tree ***********" << endl;
    insertNodeGlobal(100); //Method 0: global no return
    insertNodeGlobal(90);
    insertNodeGlobal(110);
    insertNodeRef(&root, 77); //Method 1: ref no return
    insertNodeRef(&root, 177);
    root = insertNode(root, 88); //Method 2: normal
    root = insertNode(root, 880);
    root = insertNode(root, 353);
    root = insertNodeRecursive(root, 99); //Method 3: recursive
    root = insertNodeRecursive(root, 999);
    root = enqueueTree(root, 55);
    root = enqueueTree(root, 555);
    printTree(root);
    printf("\n");
    dequeueMinTree(root);
    dequeueMinTree(root);
    printTree(root);
    printf("\n");
    dequeueMaxTree(root);
    printTree(root);
    printf("\n");
    printf("Max is %d\n", findMax(root));
    printf("Min is %d\n", findMin(root));
//    root = deleteTree(root);
//    printTree(root);
//    printf("\n");
    root = removeNode(root, 555);
    printTree(root);
    printf("\n");
    printf("Vector..\n");
    treetoBST(root);
    for_each(vec.begin(), vec.end(), [](int i){
        printf("%d ", i);
    });
    printf("\n");
    int data = 100;
    cout << (binsearch(data, vec, vec.size()) ? "Found" : "Not found") << endl;
    cout << (binsearchRecursive(root, data)) << endl;
    cout << (isBSTUpperLower(root) ? "BST" : "Not BST") << endl;

    printArray();
    //mergeSort(Array, 0, 4);
    //shellSort(Array, 4);
    //quickSort(Array, 0, 4);
    //bubbleSort(Array, 4);
    //insertSort(Array, 4);
    //selectSort(Array, 4);
    printArray();
    sortArray(Array);

}

