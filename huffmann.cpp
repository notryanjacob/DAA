//huffman code using priority queue
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

struct minHeapNode {
    char data;
    int freq;
    minHeapNode *left, *right;
    minHeapNode(char data, int freq) {
        this->data = data; 
        this->freq = freq;
        left=right=NULL;
    }
};

struct compare {
    bool operator()(minHeapNode* l, minHeapNode* r) {
        return l->freq > r->freq; 
    }
};

void printCodes(struct minHeapNode* root, string str) {
    if (!root) return;
    if (root->data != '$') cout << root->data << " : " << str << endl;
    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

void HuffmanCodes(char data[], int freq[], int size) {
    struct minHeapNode *left, *right, *top;

    priority_queue<minHeapNode*, vector<minHeapNode*>, compare> minHeap;

    for (int i = 0; i < size; ++i) {
        minHeap.push(new minHeapNode(data[i], freq[i]));
    }

    while (minHeap.size() > 1) { 
        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();

        top = new minHeapNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        minHeap.push(top); 
    }

    printCodes(minHeap.top(), "");
    
}

int main() {
    char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freq[] = {5, 9, 12, 13, 16, 45};

    cout<<"Frequencies of characters : "<<endl;
    for(int i = 0;i < 6;i++){
        cout<<arr[i]<<" : "<<freq[i]<<endl;
    }
    cout<<"Codes : "<<endl;
    int size = sizeof(arr) / sizeof(arr[0]);
    HuffmanCodes(arr, freq, size);

    return 0;
}
