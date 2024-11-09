#include "includes/config.h"

// c++ -std=c++17 main.cpp Parser.cpp Lexer.cpp CodeGen.cpp -o math

using namespace ::std;

// Method to create execuable: gcc -o output output.asm -e _start
void compileAssembly(const std::string& assemblyFile,
                     const std::string& executableFile) {
  std::string compileCmd =
      "gcc -o " + executableFile + " " + assemblyFile + " -e _start";
  if (system(compileCmd.c_str()) != 0) {
    cerr << "Error: Compilation failed." << endl;
    exit(1);
  }
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    system("clear");  // for cleaner output
    cerr << "Usage: " << argv[0] << " <input file>" << "\n";
    cout << endl;
    return 1;
  }

  // open file
  ifstream inputFile(argv[1]);
  if (!inputFile.is_open()) {
    cerr << "Error: Could not open the file " << argv[1] << endl;
    return 1;
  }

  // read file into a string
  string text((std::istreambuf_iterator<char>(inputFile)),
              istreambuf_iterator<char>());
  inputFile.close();

  // show input Arithmetic string
  system("clear");
  cout << "\033[\033[1;32mInput Arithmetic Expression:\033[0m" << "\n";
  cout << "\033[1;33m" << text << "\033[0m" << endl;
  sleep(2);

  // lexing step
  system("clear");  // clear screen mac/linux for clean output
  cout << "\033[\033[1;32mLexical Analysis Output:\033[0m"
       << "\n";  // color via ANSI
                 // Escape Codes
                 // (green)
  sleep(1);
  Lexer lexer(text);
  Token token;
  while ((token = lexer.getNextToken()).getKind() != TokenKind::END) {
    cout << lexer.getTokenKindString(token.getKind()) << " ";
    if (token.getKind() == TokenKind::NUMBER) cout << token.getValue() << " ";
    cout << endl;
  }

  // Parse and generate the AST
  try {
    cout << "\n";
    cout << "\033[\033[1;32mAbstract Syntax Tree:\033[0m" << "\n" << endl;
    sleep(1);

    Parser parser(text);
    parser.parse();
    parser.getResult()->print("");  // output AST
    cout << "\n" << endl;

    // get x86 assembly code from the AST
    ofstream outFile("ArithmeticOut.asm");
    CodeGenerator codeGen(outFile);
    unique_ptr<ExprAST>& ast =
        parser.getResult();  // create ast for codeGen (not very DRY)
    codeGen.generateAssembly(*ast);
    outFile.close();

    // Call compileAssembly and create executable in current dir
    compileAssembly("ArithmeticOut.asm", "ArithmeticOut");
    cout << "\033[\033[1;32mExecutable generated: ./ArithmeticOut\033[0m" << "\n"
         << endl;

    cout << "\033[\033[1;32mAssembly code generated in ./ArithmeticOut\033[0m" << "\n"
         << endl;
  } catch (const exception& e) {
    cerr << "Error in parsing for assembly: " << e.what() << "\n";
    return 1;
  }

  return 0;
}