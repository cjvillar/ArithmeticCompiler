enum TokenKind {
    NUMBER,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    LPAREN,
    RPAREN,
    INVALID,
    END
};

struct Token {
    TokenKind kind;
    int value; 

    Token() : kind(INVALID), value(0) {}
    Token(TokenKind kind) : kind(kind), value(0) {}
    Token(TokenKind kind, int value) : kind(kind), value(value) {}
    TokenKind getKind() const { return kind; }
    int getValue() const { return value; }
};