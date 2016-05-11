#include <iostream>
#include <cstring>
#include <string>
#include "tree_solution.h"
using namespace std;
using namespace MP;
using namespace HFM;

void test_MP() {
    cout << "---------- test_MP ----------\n";
    TreeNode *n[9];
    n[0] = new TreeNode(1, 0);
    n[1] = new TreeNode(1, 1);
    n[2] = new TreeNode(3, 2);
    n[0]->left = n[1];
    n[0]->right = n[2];
    n[3] = new TreeNode(0, 3);
    n[4] = new TreeNode(1, 4);
    n[1]->left = n[3];
    n[1]->right = n[4];
    n[5] = new TreeNode(1, 5);
    n[6] = new TreeNode(1, 6);
    n[2]->left = n[5];
    n[2]->right = n[6];
    n[7] = new TreeNode(1, 7);
    n[8] = new TreeNode(0, 8);
    n[4]->left = n[7];
    n[4]->right = n[8];
    MaxPath tree;
    cout << "MaxPathValue: ";
    cout << tree.findMaxPath(n[0]) << "\n\n";
    for (int i = 0; i < 9; i++) delete n[i];
}

void test_HFM() {
    cout << "---------- test_HFM ----------\n# TEST_1\n";
    int weight[] = { 7, 4, 5, 2 };
    int count = 4;
    HuffmanCode HFC(weight, count);
    HFC.DisplayCode();
    cout << "\nTEST_2\n";
    string input = "you are the apple in my eyes";
    HuffmanCode HFC_2(input);
    HFC_2.DisplayCode();
}

void hard_test() {
    cout << "---------- test_MP ----------\n";
    TreeNode *n[9];
    int weight;
    for (int i = 0; i < 9; i++) {
        cin >> weight;
        n[i] = new TreeNode(weight, i);
    }
    n[0]->left = n[1];
    n[0]->right = n[2];
    n[1]->left = n[3];
    n[1]->right = n[4];
    n[2]->left = n[5];
    n[2]->right = n[6];
    n[4]->left = n[7];
    n[4]->right = n[8];
    MaxPath tree;
    cout << "MaxPathValue: ";
    cout << tree.findMaxPath(n[0]) << "\n\n";
    for (int i = 0; i < 9; i++) delete n[i];
    cout << "---------- test_HFM ----------\n# TEST_1\n";
    int count, weight_arr[20] = {0};
    cin >> count;
    for (int i = 0; i < count; i++) cin >> weight_arr[i];
    HuffmanCode HFC(weight_arr, count);
    HFC.DisplayCode();
    cout << "\nTEST_2\n";
    string input = "";
    cin >> input;
    HuffmanCode HFC_2(input);
    HFC_2.DisplayCode();
}

int main() {
    int t;
    cin >> t;
    if (t == 0) {
        test_MP();
        test_HFM();
    } else {
        hard_test();
    }
    return 0;
}


/**
 * Hope you can enjoy this problem.
 * - by Carson 2016.4.24

namespace MP {

struct TreeNode;

class MaxPath {
private:
    int max;
public:
    MaxPath() : max(MAX_INIT) {}
    int findMaxPath(TreeNode *root)
};

}  // namespace MP

namespace HFM {

class HuffmanCode {
public:
    explicit
    HuffmanCode(const string &str)
    HuffmanCode(int w[], int n)
    void DisplayCode()
};

}  // namespace HFM
*/
