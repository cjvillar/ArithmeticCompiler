//c++ -std=c++17 LexerTest.cpp Lexer.cpp -o LexerTest

#include "../src/includes/config.h"

int main() {
    std::string text = "(10 + 38) * 9";
    Lexer lexer(text);

    Token token;
    while ((token = lexer.getNextToken()).getKind() != TokenKind::END) {
        std::cout << lexer.getTokenKindString(token.getKind()) << " ";
        if (token.getKind() == TokenKind::NUMBER)
            std::cout << token.getValue() << " ";
        std::cout << std::endl;
    }

    return 0;
}