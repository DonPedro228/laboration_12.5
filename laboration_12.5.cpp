#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Elem
{
    Elem* link;
    int info;
};

ifstream openInputFile(const string& filename);
ofstream openOutputFile(const string& filename);
int precedence(char op);
string infixToPostfix(const string& infix);
void writeToFile(const string& filename, const string& content);
void closeOutputFile(ofstream& file);
void closeInputFile(ifstream& file);

int main() {
    ifstream inputFile = openInputFile("120.txt");
    if (!inputFile) {
        return 1; 
    }

    string infix;
    getline(inputFile, infix);
    closeInputFile(inputFile); 

    string postfix = infixToPostfix(infix);

    writeToFile("121.txt", postfix);

    cout << "Postfix expression has been written to output.txt." << endl;

    return 0;
}

ifstream openInputFile(const string& filename) {
    ifstream inputFile(filename);
    if (!inputFile) {
        cerr << "Error: Unable to open input file." << endl;
    }
    return inputFile;
}

void closeInputFile(ifstream& file) {
    file.close();
}

ofstream openOutputFile(const string& filename) {
    ofstream outputFile(filename);
    if (!outputFile) {
        cerr << "Error: Unable to open output file." << endl;
    }
    return outputFile;
}

void closeOutputFile(ofstream& file) {
    file.close();
}

void writeToFile(const string& filename, const string& content) {
    ofstream outputFile(filename);
    if (!outputFile) {
        cerr << "Error: Unable to open output file." << endl;
        return;
    }
    outputFile << "Postfix expression: " << content << endl;
    outputFile.close();
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

string infixToPostfix(const string& infix) {
    string postfix = "";
    string stack;

    for (char c : infix) {
        if (c == ' ') {
            continue; 
        }
        if (isalnum(c)) {
            postfix += c;
        }
        else if (c == '(') {
            stack.push_back(c);
        }
        else if (c == ')') {
            while (!stack.empty() && stack.back() != '(') {
                postfix += stack.back();
                stack.pop_back();
            }
            stack.pop_back(); 
        }
        else {
            while (!stack.empty() && precedence(stack.back()) >= precedence(c)) {
                postfix += stack.back();
                stack.pop_back();
            }
            stack.push_back(c);
        }
    }

    while (!stack.empty()) {
        postfix += stack.back();
        stack.pop_back();
    }

    return postfix;
}