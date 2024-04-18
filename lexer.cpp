#include <cctype>
#include <cstdio>
#include <string>
#include <cstdlib>

class Lexer
{
public:
    enum Token
    {
        tok_eof = -1,
        tok_def = -2,
        tok_extern = -3,
        tok_identifier = -4,
        tok_number = -5,
    };

    static std::string IdentifierStr;
    static double NumVal;
    static int gettok()
    {
        static int LastChar = ' ';

        // Skip any whitespace.
        while (isspace(LastChar))
        {
            LastChar = getchar();
        }

        if (isalpha(LastChar)) // Identifier: [a-zA-Z][a-zA-Z0-9]*
        {
            IdentifierStr = LastChar;
            while (isalnum((LastChar = getchar())))
            {
                IdentifierStr += LastChar;
            }

            if (IdentifierStr == "def")
                return tok_def;
            if (IdentifierStr == "extern")
                return tok_extern;
            return tok_identifier;
        }

        if (isdigit(LastChar) || LastChar == '.') // Number: [0-9.]+
        {
            std::string NumStr;
            do
            {
                NumStr += LastChar;
                LastChar = getchar();
            } while (isdigit(LastChar) || LastChar == '.');
            NumVal = strtod(NumStr.c_str(), nullptr);
            return tok_number;
        }

        if (LastChar == '#') // Comment until end of line.
        {
            do
            {
                LastChar = getchar();
            } while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

            if (LastChar != EOF)
                return gettok();
        }

        if (LastChar == EOF)
            return tok_eof;

        // Return the character as its ascii value.
        int ThisChar = LastChar;
        LastChar = getchar();
        return ThisChar;
    }
};

std::string Lexer::IdentifierStr = "";
double Lexer::NumVal = 0.0;

#include <iostream>

int main()
{
    int tok;
    while ((tok = Lexer::gettok()) != Lexer::tok_eof)
    {
        switch (tok)
        {
        case Lexer::tok_def:
            std::cout << "Token: 'def' (keyword)" << std::endl;
            break;
        case Lexer::tok_extern:
            std::cout << "Token: 'extern' (keyword)" << std::endl;
            break;
        case Lexer::tok_identifier:
            std::cout << "Token: Identifier with name '" << Lexer::IdentifierStr << "'" << std::endl;
            break;
        case Lexer::tok_number:
            std::cout << "Token: Number with value " << Lexer::NumVal << std::endl;
            break;
        default:
            std::cout << "Token: '" << (char)tok << "' (character)" << std::endl;
            break;
        }
    }
    return 0;
}
