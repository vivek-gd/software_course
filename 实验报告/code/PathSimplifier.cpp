#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

string simplifyPath(const string& path) {
    vector<string> stack;
    istringstream iss(path);
    string token;

    while (getline(iss, token, '/')) {
        if (token.empty() || token == ".") {
            continue;
        } else if (token == "..") {
            if (!stack.empty()) {
                stack.pop_back();
            }
        } else {
            stack.push_back(token);
        }
    }

    if (stack.empty()) {
        return "/";
    }

    string result = "";
    for (const auto& dir : stack) {
        result += "/" + dir;
    }
    return result;
}

int main() {
    string path;
    getline(cin, path);
    string simplified = simplifyPath(path);
    cout << simplified << endl;
    return 0;
}
