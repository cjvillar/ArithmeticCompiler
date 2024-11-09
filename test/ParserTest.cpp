//c++ -std=c++17 ParserTest.cpp ../src/Parser.cpp ../src/Lexer.cpp -o ParserTest

#include "../src/includes/config.h"

int main() {
  try {
    // Test case 1: Should be correct
    std::cout << "Parsing: ((41 + 378) * (19 / (54 - 6)))\n";
    Parser parser1("((41 + 378) * (19 / (54 - 6)))");
    parser1.parse();
    parser1.getResult()->print("");  // Print the resulting AST
  } catch (const std::exception &e) {
    std::cerr << "Error in parsing expression 1: " << e.what() << "\n";
  }

  try {
    // Test case 2: Should be correct
    std::cout << "\nParsing: (   (  (6/5    )+    12345)-(34      *16)  )\n";
    Parser parser2("   (   (  (6/5    )+    12345)-(34      *16)  ) ");
    parser2.parse();
    parser2.getResult()->print("");  // Print the resulting AST
  } catch (const std::exception &e) {
    std::cerr << "Error in parsing expression 2: " << e.what() << "\n";
  }

  try {
    // Test case 3: Should fail (incomplete expression)
    std::cout << "\nParsing: (((3+)4)\n";
    Parser parser3("(((3+)4)");
    parser3.parse();
    parser3.getResult()->print("");  // This will not be reached if parsing fails
  } catch (const std::exception &e) {
    std::cerr << "Error in parsing expression 3: " << e.what() << "\n";
  }

   return 0;
}
