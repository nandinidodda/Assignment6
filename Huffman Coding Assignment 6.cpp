// Use only essential includes
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <map>
using namespace std;

// Node structure for Huffman Tree
struct Node {
    char data;
    int freq;
    Node* left;
    Node* right;
    
    Node(char data, int freq) {
        this->data = data;
        this->freq = freq;
        left = right = nullptr;
    }
};

// Comparison class for priority queue
struct CompareNodes {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

void printCodes(Node* root, string str, vector<string>& codes, const string& chars) {
    if (!root) return;
    
    if (!root->left && !root->right) {
        size_t pos = chars.find(root->data);
        if (pos != string::npos) {
            codes[pos] = str;
        }
    }
    
    printCodes(root->left, str + "0", codes, chars);
    printCodes(root->right, str + "1", codes, chars);
}

vector<string> generateHuffmanCodes(string str, vector<int>& freq) {
    priority_queue<Node*, vector<Node*>, CompareNodes> minHeap;
    
    // Create initial nodes
    for (size_t i = 0; i < str.length(); i++) {
        minHeap.push(new Node(str[i], freq[i]));
    }
    
    // Build Huffman Tree
    while (minHeap.size() > 1) {
        Node* left = minHeap.top();
        minHeap.pop();
        Node* right = minHeap.top();
        minHeap.pop();
        
        Node* parent = new Node('$', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        minHeap.push(parent);
    }
    
    vector<string> codes(str.length());
    printCodes(minHeap.top(), "", codes, str);
    return codes;
}

int main() {
    string str;
    cout << "Enter string of distinct characters: ";
    cin >> str;
    
    vector<int> freq(str.length());
    cout << "Enter " << str.length() << " frequencies:\n";
    for (size_t i = 0; i < str.length(); i++) {
        cout << "Frequency for " << str[i] << ": ";
        cin >> freq[i];
    }
    
    vector<string> huffmanCodes = generateHuffmanCodes(str, freq);
    
    cout << "\nHuffman Codes:\n";
    for (size_t i = 0; i < str.length(); i++) {
        cout << str[i] << ": " << huffmanCodes[i] << "\n";
    }
    
    cout << "\nCodes in order: ";
    for (const string& code : huffmanCodes) {
        cout << code << " ";
    }
    cout << endl;
    
    return 0;
}