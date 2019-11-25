// C++ program for Huffman Coding 
#include <iostream> 
#include <cstdlib> 
#include <string>
using namespace std; 

// This constant can be avoided by explicitly 
// calculating height of Huffman Tree 
#define MAX_TREE_HT 100 

// A Huffman tree node 
struct MinHeapNode { 

	// One of the input characters 
	char data; 

	// Frequency of the character 
	unsigned freq; 

	// Left and right child of this node 
	struct MinHeapNode *left, *right; 
}; 

// A Min Heap: Collection of 
// min-heap (or Huffman tree) nodes 
struct MinHeap { 

	// Current size of min heap 
	unsigned size; 

	// capacity of min heap 
	unsigned capacity; 

	// Attay of minheap node pointers 
	struct MinHeapNode** array; 
}; 

class Huffman
{
private:
    char letter;
    string code;
public:
    Huffman(/* args */);
    ~Huffman();
    char getLetter();
    string getCode();
    void setLetter(char );
    void setCode(string );
	int codSize();
};

Huffman::Huffman(/* args */){

}

Huffman::~Huffman() {

}

int Huffman::codSize(){
	return code.size();
}

char Huffman::getLetter(){
    return letter;
}

string Huffman::getCode(){
    return code;
}

void Huffman::setLetter(char pLetter){
	letter = pLetter;
}

void Huffman::setCode(string pCode){
	code = pCode;
}

// A utility function allocate a new 
// min heap node with given character 
// and frequency of the character 
struct MinHeapNode* newNode(char data, unsigned freq) 
{ 
	struct MinHeapNode* temp 
		= (struct MinHeapNode*)malloc
(sizeof(struct MinHeapNode)); 

	temp->left = temp->right = NULL; 
	temp->data = data; 
	temp->freq = freq; 

	return temp; 
} 

// A utility function to create 
// a min heap of given capacity 
struct MinHeap* createMinHeap(unsigned capacity) 

{ 

	struct MinHeap* minHeap 
		= (struct MinHeap*)malloc(sizeof(struct MinHeap)); 

	// current size is 0 
	minHeap->size = 0; 

	minHeap->capacity = capacity; 

	minHeap->array 
		= (struct MinHeapNode**)malloc(minHeap-> 
capacity * sizeof(struct MinHeapNode*)); 
	return minHeap; 
} 

// A utility function to 
// swap two min heap nodes 
void swapMinHeapNode(struct MinHeapNode** a, 
					struct MinHeapNode** b) 

{ 

	struct MinHeapNode* t = *a; 
	*a = *b; 
	*b = t; 
} 

// The standard minHeapify function. 
void minHeapify(struct MinHeap* minHeap, int idx) 

{ 

	int smallest = idx; 
	int left = 2 * idx + 1; 
	int right = 2 * idx + 2; 

	if (left < minHeap->size && minHeap->array[left]-> 
freq < minHeap->array[smallest]->freq) 
		smallest = left; 

	if (right < minHeap->size && minHeap->array[right]-> 
freq < minHeap->array[smallest]->freq) 
		smallest = right; 

	if (smallest != idx) { 
		swapMinHeapNode(&minHeap->array[smallest], 
						&minHeap->array[idx]); 
		minHeapify(minHeap, smallest); 
	} 
} 

// A utility function to check 
// if size of heap is 1 or not 
int isSizeOne(struct MinHeap* minHeap) 
{ 

	return (minHeap->size == 1); 
} 

// A standard function to extract 
// minimum value node from heap 
struct MinHeapNode* extractMin(struct MinHeap* minHeap) 

{ 

	struct MinHeapNode* temp = minHeap->array[0]; 
	minHeap->array[0] 
		= minHeap->array[minHeap->size - 1]; 

	--minHeap->size; 
	minHeapify(minHeap, 0); 

	return temp; 
} 

// A utility function to insert 
// a new node to Min Heap 
void insertMinHeap(struct MinHeap* minHeap, 
				struct MinHeapNode* minHeapNode) 

{ 

	++minHeap->size; 
	int i = minHeap->size - 1; 

	while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) { 

		minHeap->array[i] = minHeap->array[(i - 1) / 2]; 
		i = (i - 1) / 2; 
	} 

	minHeap->array[i] = minHeapNode; 
} 

// A standard function to build min heap 
void buildMinHeap(struct MinHeap* minHeap) 

{ 

	int n = minHeap->size - 1; 
	int i; 

	for (i = (n - 1) / 2; i >= 0; --i) 
		minHeapify(minHeap, i); 
} 

// A function to give the huffman code of a char
string insertCode(int arr[], int n) 
{ 
	int i;
	string code; 
	for (i = 0; i < n; ++i){
		string a = to_string(arr[i]);
		code.append(a);
	}

	return code;
}

// Utility function to check if this node is leaf 
int isLeaf(struct MinHeapNode* root) 

{ 

	return !(root->left) && !(root->right); 
} 

// Creates a min heap of capacity 
// equal to size and inserts all character of 
// data[] in min heap. Initially size of 
// min heap is equal to capacity 
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) 

{ 

	struct MinHeap* minHeap = createMinHeap(size); 

	for (int i = 0; i < size; ++i) 
		minHeap->array[i] = newNode(data[i], freq[i]); 

	minHeap->size = size; 
	buildMinHeap(minHeap); 

	return minHeap; 
} 

// The main function that builds Huffman tree 
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) 

{ 
	struct MinHeapNode *left, *right, *top; 

	// Step 1: Create a min heap of capacity 
	// equal to size. Initially, there are 
	// modes equal to size. 
	struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size); 

	// Iterate while size of heap doesn't become 1 
	while (!isSizeOne(minHeap)) { 

		// Step 2: Extract the two minimum 
		// freq items from min heap 
		left = extractMin(minHeap); 
		right = extractMin(minHeap); 

		// Step 3: Create a new internal 
		// node with frequency equal to the 
		// sum of the two nodes frequencies. 
		// Make the two extracted node as 
		// left and right children of this new node. 
		// Add this node to the min heap 
		// '$' is a special value for internal nodes, not used 
		top = newNode('$', left->freq + right->freq); 

		top->left = left; 
		top->right = right; 

		insertMinHeap(minHeap, top); 
	} 

	// Step 4: The remaining node is the 
	// root node and the tree is complete. 
	return extractMin(minHeap); 
} 


// A function that creat the huffman code
void huffCodes(struct MinHeapNode* root, int arr[], int top, Huffman *codes, int *idx) 

{ 

	// Assign 0 to left edge and recur 
	if (root->left) { 

		arr[top] = 0; 
		huffCodes(root->left, arr, top + 1, codes, idx); 
	} 

	// Assign 1 to right edge and recur 
	if (root->right) { 

		arr[top] = 1; 
		huffCodes(root->right, arr, top + 1, codes, idx); 
	} 

	// If this is a leaf node, then 
	// it contains one of the input 
	// characters, so insert character
	// and the code in array codes
	if (isLeaf(root)) { 
		codes[*idx].setLetter(root->data);
		codes[*idx].setCode(insertCode(arr, top));
		*idx = *idx + 1;
	} 
}

// The main function that builds a 
// Huffman Tree and print codes by traversing 
// the built Huffman Tree 
void HuffmanCodes(char data[], int freq[], int size, Huffman *codes, int *i) 

{ 
	// Construct Huffman Tree 
	struct MinHeapNode* root 
		= buildHuffmanTree(data, freq, size); 

	// Print Huffman codes using 
	// the Huffman tree built above 
	int arr[MAX_TREE_HT], top = 0; 

	// printCodes(root, arr, top);
	huffCodes(root, arr, top, codes, i);
} 

// A function that codify the string to Huffman's code
string codify(string a, Huffman *codes, int size){
	string codeHuffman;
	for (int i = 0; i < a.size(); i++){
		for (int k = 0; k < size; k++){
			if (codes[k].getLetter() == a[i])
				codeHuffman.append(codes[k].getCode());
		}
	}
	
	return codeHuffman;
}

// string decodify(string a, Huffman *codes, int size){
// 	string decodeHuffman;
// 	int i = 0, k = 0, j = 0, count, temp;
// 	while (i < a.size()){
// 		if (a[i] == codes[i].getCode())
// 			decodeHuffman.append(codes[i].getLetter());
// 		else{
// 			temp = i;
// 			bool check = false;
// 			while (k < size || check){
// 				count = 0;
// 				for (j = 0; j < codes[k].codSize(); j++){
// 					if(codes[j].getCode() == a[temp]){
// 						count++;
// 						temp++;
// 					}
// 					else
// 						break;
// 				}
// 				if(count == codes[k].codSize()){
// 					decodeHuffman.append(codes[k].getCode);
// 					check = true;
// 				}
// 				k++;
// 			}
// 			i = temp;
// 		}
// 	}
// 	return decodeHuffman;
// }

bool operator == (const Huffman &p1, const Huffman &p2){
   if (p1 == p2)
     return true;
   else
     return false;
}

// Driver program to test above functions 
int main() 
{ 

	char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' }; 
	int freq[] = { 5, 9, 12, 13, 16, 45 }; 

	int size = sizeof(arr) / sizeof(arr[0]); 

	Huffman* codes = new Huffman[size];

	int idx = 0;

	HuffmanCodes(arr, freq, size, codes, &idx);

	string a = codify(arr, codes, size);

//	string b = decodify(a, codes, size);

	cout << a << endl;

//	cout << b << endl;

	//cout << codes[0].getLetter() <<": " << codes[0].getCode() << endl;

	delete[] codes;

	return 0;
} 
