#ifndef TREE_SOLUTION
#define TREE_SOLUTION

#include <iostream>
#include <map>
#include <stdio.h>
#include <string.h>
using namespace std;

static const int MIN_INIT = -99999999;
static const int MAX_INIT = 10000;
static const int MAX_BIT = 100;
static const int MAX_NODE = 2000;

namespace MP {

struct TreeNode {
    int val, id;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x, int i) : val(x), id(i), left(NULL), right(NULL) {}
};

class MaxPath {
  private:
    int max;
  public:
    MaxPath() : max(MAX_INIT) {}
    int findMaxPath(TreeNode *root) {
        if (root == NULL) return 0;
        int left_val = findMaxPath(root->left);
        int right_val = findMaxPath(root->right);
        if (root->val + left_val > max) max = root->val + left_val;
        if (root->val + right_val > max) max = root->val + right_val;
        if (root->val > max) max = root->val;
        int temp =
        (root->val + left_val > root->val) ? root->val + left_val : root->val;
        temp = (temp > root->val + right_val) ? temp : root->val + right_val;
        return temp;
    }
};

}  // namespace MP

namespace HFM {

struct HuffNode {
    int weight, flag;
    int parent, leftChild, rightChild;
    HuffNode() {
        parent = weight = flag = 0;
        leftChild = rightChild = -1;
    }
};

struct Code {
    int bit[MAX_BIT];
    int position;
    int weight;
    Code() {
        position = weight = 0;
        memset(bit, 0, MAX_BIT);
    }
};

class HuffmanCode {
    HuffNode node[MAX_NODE];
    Code code[MAX_NODE];
    char nodeChar[MAX_NODE];
    string copy;
    bool hasStr;
    int LeafNode;
  public:
    explicit HuffmanCode(const string &str) {
        int type[26] = { 0 };
        LeafNode = 0;
        copy = "";
        for (int i = 0; i < str.length(); i++) {
            if (str[i] < 'a' || str[i] > 'z')
                continue;
            type[str[i] - 'a']++;
            copy += str[i];
        }
        for (int i = 0; i < 26; i++)
            if (type[i] > 0) {
                node[LeafNode++].weight = type[i];
                nodeChar[LeafNode-1] = 'a' + i;
            }
        hasStr = true;
    }
    HuffmanCode(int w[], int n) {
        for (int i = 0; i < 2 * n - 1; i++) {
            if (i < n) node[i].weight = w[i];
            else node[i].weight = 0;
        }
        LeafNode = n;
        hasStr = false;
        copy = "";
    }
    void BuildTree() {
        for (int i = 0; i < LeafNode - 1; i++) {
            int min1, min2, pos1, pos2;
            min1 = min2 = MAX_INIT;
            pos1 = pos2 = 0;
            for (int j = 0; j < LeafNode + i; j++) {
                if (node[j].weight < min2 && node[j].flag == 0) {
                    min1 = min2;
                    pos1 = pos2;
                    min2 = node[j].weight;
                    pos2 = j;
                } else if (node[j].weight < min1 && node[j].flag == 0) {
                    min1 = node[j].weight;
                    pos1 = j;
                }
            }
            node[pos1].parent = node[pos2].parent = LeafNode + i;
            node[pos1].flag = node[pos2].flag = 1;
            node[LeafNode + i].weight = node[pos1].weight + node[pos2].weight;
            node[LeafNode + i].leftChild = pos1;
            node[LeafNode + i].rightChild = pos2;
        }
    }
    void GenerateCode() {
        Code *codeP = new Code;
        int childPos, parentPos;
        for (int i = 0; i < LeafNode; i++) {
            codeP->position = 0;
            codeP->weight = node[i].weight;
            childPos = i;
            parentPos = node[i].parent;
            while (parentPos != 0) {
                if (node[parentPos].leftChild == childPos)
                    codeP->bit[codeP->position] = 0;
                else
                    codeP->bit[codeP->position] = 1;
                codeP->position++;
                childPos = parentPos;
                parentPos = node[childPos].parent;
            }
            for (int j = codeP->position - 1; j >= 0; j--)
                code[i].bit[codeP->position - j - 1] = codeP->bit[j];
            code[i].position = codeP->position;
            code[i].weight = codeP->weight;
        }
        delete codeP;
    }
    void DisplayCode() {
        BuildTree();
        GenerateCode();
        int codeLength = 0;
        bool isVisit[MAX_NODE];
        memset(isVisit, true, MAX_NODE);
        for (int i = 0; i < LeafNode; i++) {
            int min = MAX_INIT, position_max = -1;
            for (int j = 0; j < LeafNode; j++)
                if (isVisit[j] && node[j].weight < min) {
                    min = node[j].weight;
                    position_max = j;
                }
            isVisit[position_max] = false;
            if (hasStr)
                cout << "(" << nodeChar[position_max] << ") ";
            cout << "Weight = " << node[position_max].weight << "; Code = ";
            for (int j = 0; j < code[position_max].position; j++)
                cout << code[position_max].bit[j];
            codeLength +=
                code[position_max].weight * code[position_max].position;
            cout << endl;
        }
        cout << "Huffman's codeLength = " << codeLength << endl;
        if (!hasStr) return;
        cout << "Origin Text: " << copy << endl;
        cout << "Huffman's Code: ";
        for (int i = 0; i < copy.length(); i++)
            for (int j = 0; j < LeafNode; j++)
                if (nodeChar[j] == copy[i])
                    for (int p = 0; p < code[j].position; p++)
                        cout << code[j].bit[p];
        cout << endl;
    }
};

}  // namespace HFM

#endif
