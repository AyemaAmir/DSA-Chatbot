#include <iostream>
#include <queue>
#include <string>
#include <map>
#include <functional>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <filesystem> // For directory traversal

namespace fs = std::filesystem;

using namespace std;



// Utility functions
class Utils {
public:
    static string preprocessInput(string input) {
        transform(input.begin(), input.end(), input.begin(), ::tolower);
        input.erase(0, input.find_first_not_of(' '));
        input.erase(input.find_last_not_of(' ') + 1);
        return input;
    }

    static vector<string> extractKeywords(const string& input) {
        stringstream ss(input);
        string word;
        vector<string> keywords;
        while (ss >> word) {
            keywords.push_back(word);
        }
        return keywords;
    }
};

// Conversation Manager
class ConversationManager {
private:
    queue<string> conversationQueue;

public:
    void enqueueResponse(const string& response) {
        conversationQueue.push(response);
    }

    void processConversation() {
        if (conversationQueue.empty()) {
            cout << "Chatbot: No responses to display.\n";
            return;
        }

        while (!conversationQueue.empty()) {
            cout << "Chatbot: " << conversationQueue.front() << endl;
            conversationQueue.pop();
        }
    }
};
struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};

string toString(int value) {
    stringstream ss;
    ss << value;
    return ss.str();
}
// Function to get the height of the tree
int height(Node* N) {
    return (N == nullptr) ? 0 : N->height;
}

// Function to get the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to create a new node
Node* newNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1; // New node is initially added at leaf
    return node;
}

// Right rotate subtree rooted with y
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

// Left rotate subtree rooted with x
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

// Get balance factor of node N
int getBalance(Node* N) {
    if (N == nullptr)
        return 0;
    return height(N->left) - height(N->right);
}

// Recursive function to insert a key in the subtree rooted with node and returns the new root of the subtree.
Node* insert(Node* node, int key) {
    // Perform the normal BST insertion
    if (node == nullptr)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);

    // Update height of this ancestor node
    node->height = 1 + max(height(node->left), height(node->right));

    // Get the balance factor of this ancestor node to check whether this node became unbalanced
    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return the (unchanged) node pointer
    return node;
}

// Helper function to print tree nodes visually
void printLevel(vector<Node*> level, vector<string>& lines, int levelWidth) {
    vector<Node*> nextLevel;
    bool hasMore = false;
    string currentLine;
    string branchesLine;

    for (Node* node : level) {
        if (node) {
            currentLine += string(levelWidth / 2, ' ') + to_string(node->key) + string(levelWidth / 2, ' ');
            nextLevel.push_back(node->left);
            nextLevel.push_back(node->right);

            branchesLine += string(levelWidth / 4, ' ');
            branchesLine += node->left ? "/" : " ";
            branchesLine += string(levelWidth / 2 - 1, ' ');
            branchesLine += node->right ? "\\" : " ";
            branchesLine += string(levelWidth / 4, ' ');

            if (node->left || node->right) hasMore = true;
        }
        else {
            currentLine += string(levelWidth, ' ');
            branchesLine += string(levelWidth, ' ');
            nextLevel.push_back(nullptr);
            nextLevel.push_back(nullptr);
        }
    }

    lines.push_back(currentLine);
    lines.push_back(branchesLine);

    if (hasMore) printLevel(nextLevel, lines, levelWidth / 2);
}

// Function to print the tree using / \ style
void printTree(Node* root) {
    if (!root) return;

    vector<Node*> level;
    vector<string> lines;
    level.push_back(root);

    printLevel(level, lines, 27); // Adjust initial spacing width for proper formatting

    for (const string& line : lines) {
        cout << line << endl;
    }
}
void createAVLTREE() {
    Node* root = nullptr;

    int number;

    cout << "Enter numbers to insert into AVL Tree (enter -1 to stop):" << endl;

    while (true) {
        cin >> number;
        if (number == -1) break; // Stop input on -1

        root = insert(root, number);
    }

    cout << "\nFinal AVL Tree structure:\n";
    printTree(root);

    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear input buffer

}
// Chatbot Class
class Chatbot {
private:
    map<string, string> topicFiles; // Map of topics and file paths

    void loadTopics(const string& directoryPath) {
        for (const auto& entry : fs::directory_iterator(directoryPath)) {
            if (entry.path().extension() == ".txt") {
                string fileName = entry.path().stem().string();
                fileName = Utils::preprocessInput(fileName); // Preprocess the key
                topicFiles[fileName] = entry.path().string();
            }
        }
        string avlTopic = Utils::preprocessInput("create an avl tree"); // Preprocess the topic
        topicFiles[avlTopic] = "avl_tree creation"; // Add AVL tree as a topic
    }


    map<string, string> loadSubtopics(const string& filePath) {
        map<string, string> subtopics;
        ifstream file(filePath);
        if (!file.is_open()) {
            cerr << "Error opening file: " << filePath << endl;
            return subtopics;
        }

        string line, key, value;
        while (getline(file, line)) {
            size_t delimiterPos = line.find("#");
            if (delimiterPos != string::npos) {
                key = line.substr(0, delimiterPos);
                value = line.substr(delimiterPos + 2);

                while (getline(file, line) && !line.empty()) {
                    value += "\n" + line;
                }

                key = Utils::preprocessInput(key);
                value.erase(0, value.find_first_not_of(" \t"));

                subtopics[key] = value;
            }
        }
        return subtopics;
    }

    int calculateKeywordScore(const vector<string>& inputKWs, const vector<string>& subtopicKWs, const map<string, vector<string>>& keywordContextMap) {
        int score = 0;
        for (const auto& ikw : inputKWs) {
            for (const auto& skw : subtopicKWs) {
                if (ikw == skw) {
                    score += 20; // Base score for match
                    auto contextIt = keywordContextMap.find(skw);
                    if (contextIt != keywordContextMap.end()) {
                        const vector<string>& contextKWs = contextIt->second;
                        for (const auto& contextKW : contextKWs) {
                            if (find(inputKWs.begin(), inputKWs.end(), contextKW) != inputKWs.end()) {
                                score += 5; // Additional score for context match
                            }
                        }
                    }
                }
            }
        }
        return score;
    }

    string matchSubtopic(const string& userInput, const map<string, string>& subtopics, const map<string, vector<string>>& keywordContextMap) {
        auto inputKeywords = Utils::extractKeywords(userInput);
        map<string, int> subtopicScores;
        const int relevanceThreshold = 20; // Define what you consider a minimum relevant score

        for (const auto& subtopic : subtopics) {
            auto subtopicKeywords = Utils::extractKeywords(subtopic.first);
            int score = calculateKeywordScore(inputKeywords, subtopicKeywords, keywordContextMap);
            subtopicScores[subtopic.first] = score;
        }

        string bestMatch;
        int highestScore = -1;
        for (const auto& score : subtopicScores) {
            if (score.second > highestScore) {
                highestScore = score.second;
                bestMatch = score.first;
            }
        }

        if (highestScore < relevanceThreshold) {
            return "";  // Or return some message indicating no relevant subtopic was found
        }

        return bestMatch;
    }


public:
    Chatbot(const string& directoryPath) {
        loadTopics(directoryPath);
    }
    bool skipTopicList = false; // New flag to control topic list display

    void run() {
        cout << "\nWelcome to the Learning Chatbot!" << endl;
        cout << "\nHere, you can learn about various topics. Type your questions, and I will assist you.\n";

        map<string, vector<string>> keywordContextMap = {
            {"insert", {"start", "end", "specific", "location"}},
            {"delete", {"node", "specific", "position"}},
            {"search", {"element", "key"}},
            {"sort", {"ascending", "descending", "order"}}
        };

        while (true) {
            if (!skipTopicList) { // Display only if skipTopicList is false
                cout << "\nTopics you can learn about:" << endl;
                for (const auto& topic : topicFiles) {
                    cout << "- " << topic.first << endl;
                }
                cout << "\nPrompt: What would you like to learn? (Type 'exit' to quit)\n";
            }
            skipTopicList = false; // Reset flag after skipping once

            string userInput;
            getline(cin, userInput);
            userInput = Utils::preprocessInput(userInput);

            if (userInput == "exit") {
                cout << "\nGoodbye! Happy learning!" << endl;
                break;
            }
            vector<string> inputKeywords = Utils::extractKeywords(userInput);
            vector<string> avlKeywords = { "avl", "tree", "create", "make" };

            bool isAVLMatch = false;
            for (const string& word : inputKeywords) {
                if (find(avlKeywords.begin(), avlKeywords.end(), word) != avlKeywords.end()) {
                    isAVLMatch = true;
                    break;
                }
            }

            if (isAVLMatch) {
                cout << "\nYou selected 'create an AVL tree'. Let's begin!\n";

                while (true) { // Loop to stay in AVL creation mode
                    createAVLTREE(); // Perform AVL tree creation

                    // Prompt user for next action
                    cout << "\nAVL Tree creation complete. Would you like to create another AVL tree?"
                        << "\nOr type 'back' to return to the topic list: ";

                    string avlInput;
                    getline(cin, avlInput);

                    if (avlInput.empty()) {
                        cout << "\nInvalid input. Please type 'back' or indicate if you'd like to create another tree.\n";
                        continue;
                    }

                    avlInput = Utils::preprocessInput(avlInput);

                    // Check if the user wants to create another tree
                    if (avlInput == "yes" || avlInput.find("create") != string::npos || avlInput.find("another") != string::npos) {
                        continue; // Stay in the AVL creation loop
                    }

                    // Check if the user wants to go back
                    if (avlInput == "back" || avlInput.find("return") != string::npos || avlInput.find("go") != string::npos) {
                        cout << "\nReturning to the topic list.\n";
                        skipTopicList = false; // Reset flag to ensure topic list is displayed
                        break; // Exit AVL creation mode
                    }

                    // Handle invalid input
                    cout << "\nInvalid input. Please type 'back' or indicate if you'd like to create another tree.\n";
                }

                continue; // Go back to the main loop
            }





            string matchedTopic;
            for (const auto& topic : topicFiles) {
                if (userInput.find(topic.first) != string::npos) {
                    matchedTopic = topic.first;
                    break;
                }
            }

            if (!matchedTopic.empty()) {
                cout << "\nSure! How can I assist you with " << matchedTopic << "?" << endl;

                string filePath = topicFiles[matchedTopic];
                map<string, string> subtopics = loadSubtopics(filePath);

                if (subtopics.empty()) {
                    cout << "\nSorry, no information is available for this topic." << endl;
                    continue;
                }

                while (true) {
                    cout << "\nPrompt: Please ask your question or type 'back' to return to the topic list." << endl;

                    getline(cin, userInput);
                    userInput = Utils::preprocessInput(userInput);

                    if (userInput == "back") {
                        break;
                    }

                    string matchedSubtopic = matchSubtopic(userInput, subtopics, keywordContextMap);

                    if (!matchedSubtopic.empty()) {
                        cout << "\n" << subtopics[matchedSubtopic] << "\n";
                    }
                    else {
                        cout << "\nI couldn't find an answer to that. Please try a different question or check the input." << endl;
                    }

                }
            }
            else {
                cout << "\nI couldn't find that topic. Please try again." << endl;
            }
        }
    }
};

int main() {
    string topicDirectory = "topics/"; // Ensure this directory exists and contains .txt files
    Chatbot chatbot(topicDirectory);
    chatbot.run();

    return 0;
}
