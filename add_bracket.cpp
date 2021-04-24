#include <iostream>
#include <cstring>

using namespace std;

struct Tree{
    Tree* right;
    Tree* left;
    char* s;
};

int N, max_num = -(2<<30);
char expression[19];

// void print_tree(Tree* cur) {
//     cout << cur->s << endl;
// }

void makeTree(Tree* cur, int i) {
   // cout << "****i : " << i << "****" << endl;
    if(i > N - 2) {
        cur->left = (Tree*)malloc(sizeof(Tree));
        cur->right = (Tree*)malloc(sizeof(Tree));
        cur->left->s = (char*)malloc(sizeof(char));
        cur->right->s = (char*)malloc(sizeof(char));
        cur->left->s = "d";
        cur->right->s = "d";
        //cout << "left end position" << endl;
        return;
    }

    cur->left = (Tree*)malloc(sizeof(Tree));
    cur->left->s = (char*)malloc(3 * sizeof(char));
    cur->left->s[0] = expression[i];
    cur->left->s[1] = expression[i+1];
    cur->left->s[2] = '\0';
    //cout << "left : ";
   // print_tree(cur->left);

    if(i > N - 4) {
        cur->right = (Tree*)malloc(sizeof(Tree));
        cur->right->s = (char*)malloc(sizeof(char));
        cur->right->s = "e"; // 왼쪽으로 가지를 칠 수 있고, 오른쪽으로는 더 이상 가지를 칠 수 없는 경우. 계산중에 마지막 연산자가 빠지는 경우가 있으므로 e(error)로 표시하여 예외 처리.
        //cout << "right end position" << endl;
        //cout << "LEFT MAKE TREE" << endl;
        makeTree(cur->left, i+2);
        return;
    }

    cur->right = (Tree*)malloc(sizeof(Tree));
    cur->right->s = (char*)malloc(5 * sizeof(char));
    cur->right->s[0] = expression[i];
    cur->right->s[1] = expression[i+1];
    cur->right->s[2] = expression[i+2];
    cur->right->s[3] = expression[i+3];
    cur->right->s[4] = '\0';
    //cout << "right : ";
    //print_tree(cur->right);

    //cout << "LEFT MAKE TREE" << endl;
    makeTree(cur->left, i+2);
    //cout << "RIGHT MAKE TREE" << endl;
    makeTree(cur->right, i+4);
}

int calc_bracket(char* exp) {
    int n1 = exp[1] - '0';
    int n2 = exp[3] - '0';
    switch(exp[2]) {
        case '+' :
            return n1+n2;

        case '-' :
            return n1-n2;

        default : // *
            return n1*n2;
    }
}

void calculate(Tree* cur, int cur_res) {
    switch(cur->s[0]) {
        case '+' :
            if(strlen(cur->s) == 2) {
                cur_res += cur->s[1] - '0';
                calculate(cur->left, cur_res);
                calculate(cur->right, cur_res);
            }
            else {
                cur_res += calc_bracket(cur->s);
                calculate(cur->left, cur_res);
                calculate(cur->right, cur_res);
            }
            break;

        case '-' :
            if(strlen(cur->s) == 2) {
                cur_res -= cur->s[1] - '0';
                calculate(cur->left, cur_res);
                calculate(cur->right, cur_res);
            }
            else {
                cur_res -= calc_bracket(cur->s);
                calculate(cur->left, cur_res);
                calculate(cur->right, cur_res);
            }
            break;

        case '*' :
            if(strlen(cur->s) == 2) {
                cur_res *= cur->s[1] - '0';
                calculate(cur->left, cur_res);
                calculate(cur->right, cur_res);
            }
            else {
                cur_res *= calc_bracket(cur->s);
                calculate(cur->left, cur_res);
                calculate(cur->right, cur_res);
            }
            break;

        case 'e' : // 오른쪽으로 가지를 치는 경우, 연산자 하나와 피연산자 하나가 아직 남아있는데도 끝나는 경우가 있으므로, 제외.
            return;

        default : // 끝에 도달했을 때
            max_num = max(max_num, cur_res);
            return;
    }
}

int main() {
    cin >> N;
    cin >> expression;
    Tree* root1 = (Tree*)malloc(sizeof(Tree));
    root1->s = (char*)malloc(3 * sizeof(char*));
    root1->s[0] = '+';
    root1->s[1] = expression[0];
    root1->s[2] = '\0';
    //cout << "ROOT1 : ";
    //print_tree(root1);
    makeTree(root1, 1);
    calculate(root1, 0);

    cout << endl << endl;

    if(N >= 3) {
        Tree* root2 = (Tree*)malloc(sizeof(Tree));
        root2->s = (char*)malloc(5 * sizeof(char));
        root2->s[0] = '+';
        root2->s[1] = expression[0];
        root2->s[2] = expression[1];
        root2->s[3] = expression[2];
        root2->s[4] = '\0';
        //cout << "ROOT2 : ";
        //print_tree(root2);
        makeTree(root2, 3);
        calculate(root2, 0);
    }

    cout << max_num;
}