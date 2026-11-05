#include <iostream>
#include <limits>
#include <clocale>

using namespace std;


struct Node {
    int val;
    Node* left;
    Node* right;

    Node(int x) {
        val = x;
        left = NULL;
        right = NULL;
    }
};


class Tree {
private:
    Node* root;

    
    void freeMem(Node* curr) {
        if (curr != NULL) {
            freeMem(curr->left);
            freeMem(curr->right);
            delete curr;
        }
    }

    
    Node* push(Node* curr, int x) {
        if (curr == NULL) {
            return new Node(x);
        }
        if (x < curr->val) {
            curr->left = push(curr->left, x);
        }
        else if (x > curr->val) {
            curr->right = push(curr->right, x);
        }
        return curr; 
    }

   
    void showInorder(Node* curr) {
        if (curr != NULL) {
            showInorder(curr->left);
            cout << curr->val << " ";
            showInorder(curr->right);
        }
    }

    
    void showLikeTree(Node* curr, int level) {
        if (curr == NULL) return;

       
        showLikeTree(curr->right, level + 1);

        
        for (int i = 0; i < level; i++) {
            cout << "\t";
        }
        cout << curr->val << endl;

        
        showLikeTree(curr->left, level + 1);
    }

    
    int getDepth(Node* curr) {
        if (curr == NULL) return 0;
        int l = getDepth(curr->left);
        int r = getDepth(curr->right);
        return 1 + (l > r ? l : r);
    }

    
    int getCount(Node* curr) {
        if (curr == NULL) return 0;
        return 1 + getCount(curr->left) + getCount(curr->right);
    }

    
    int getSumma(Node* curr) {
        if (curr == NULL) return 0;
        return curr->val + getSumma(curr->left) + getSumma(curr->right);
    }

    
    bool findNode(Node* curr, int x) {
        if (curr == NULL) return false;
        if (curr->val == x) return true;
        if (x < curr->val) return findNode(curr->left, x);
        return findNode(curr->right, x);
    }

public:
    
    Tree() {
        root = NULL;
    }

    
    ~Tree() {
        freeMem(root);
    }

    
    void add(int x) {
        root = push(root, x);
    }

    void printInorder() {
        showInorder(root);
        cout << endl;
    }

    void printTree() {
        if (root == NULL) {
            cout << "Дерево пока пустое!" << endl;
            return;
        }
        showLikeTree(root, 0);
    }

    int height() { return getDepth(root); }  //маленькие функции))
    int count() { return getCount(root); }
    int sum() { return getSumma(root); }

    bool search(int x) {
        return findNode(root, x);
    }
};

// от дурака 
int inputInt() {
    int num;
    while (true) {
        if (cin >> num) {
            return num;
        }
        else {
            cout << "Неверный ввод! Нужно целое число: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

int main() {
    setlocale(LC_ALL, "Russian");

    Tree myTree;

    cout << "Лабораторная работа: Дерево поиска " << endl;
    cout << "Сколько чисел хотите ввести? ";
    int n = inputInt();
    while (n <= 0) {
        cout << "Число должно быть больше нуля! Повторите: ";
        n = inputInt();
    }

    cout << "Введите " << n << " чисел через пробел или Enter:" << endl;
    for (int i = 0; i < n; i++) {
        int temp = inputInt();
        myTree.add(temp);
    }

    cout << "\n Структура дерева (повернуто влево) " << endl;
    myTree.printTree();
    

    cout << "\nИнфиксный обход (сортировка): ";
    myTree.printInorder();

    cout << "Высота дерева: " << myTree.height() << endl;
    cout << "Всего узлов: " << myTree.count() << endl;
    cout << "Сумма элементов: " << myTree.sum() << endl;

    cout << "\n Проверка поиска " << endl;
    cout << "Какое число найти в дереве? ";
    int target = inputInt();

    if (myTree.search(target)) {
        cout << "Ура! Число " << target << " есть в дереве." << endl;
    }
    else {
        cout << "Да нет тут " << target << " такого числа." << endl;
    }

    return 0;
}
