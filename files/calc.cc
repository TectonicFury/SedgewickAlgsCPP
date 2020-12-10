#include <iostream>
#include <string>
#include <vector>
int calc(std::vector<int> v, std::vector<char> op) {
  int sum = v[0];
  
}

int main(int argc, char const *argv[]) {
  std::cout << "Please enter expression (we can handle +, -, / and *):" << '\n';
  std::string xpr; //the expression
  std::getline(std::cin, xpr);
  std::vector<int> v;
  std::string str;
  std::vector<char> op;
  bool prevOp = false;
  int rval, lval;

  for (size_t i = 0; i < xpr.size(); i++) {
    if (std::isdigit(xpr[i])) {
      str.append(1, xpr[i]);
    } else {
      v.push_back(std::stod(str));
      str = "";
      op.push_back(xpr[i]);
    }
  }
  v.push_back(std::stod(str));

  int lval = 0;
  int rval;
  char op;
  int res;
  std::cin >> lval>>op>>rval;
  if (op == '+') {
    res = lval + rval;
  } else if (op == '-') {
    res = lval - rval;
  }
  std::cout << "Result: " << res << '\n';
  return 0;
}
