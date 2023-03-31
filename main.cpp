#include <iostream>
#include <string>
#include <cctype>
#include <sstream>
#include <fstream>
#include <vector>

using namespace std;

enum Token
{
    Operator,
    Seperator,
    Int,
    Keyword,
    ID,
    Real,
};

void lexer()
{
    ifstream inputfile("input_scode.txt", ios::in);
    ofstream fileWriter;
    fileWriter.open("output.txt");
    fileWriter << "Token:		Lexeme:\n";

    if (!inputfile.is_open())
    {
        cout << "Cannot open file";
    }
    while (getline(inputfile, input))
    {
        // input = lexer(s);

        string store;
        bool flag = false;
        bool opflag = true;
        string current_token = "";
        string current_type = "";
        // cout << "Token    "
        //      << "Lexeme" << endl;
        for (size_t i = 0; i < input.length(); i++)
        {
            char current_char = input[i];

            if (isspace(current_char))
            {
                continue;
            }
            else if (isalpha(current_char))
            {
                current_token += current_char;
                while (isalnum(input[i + 1]))
                {
                    current_token += input[++i];
                }
                if (current_token == "int" || current_token == "function" || current_token == "int" || current_token == "bool" || current_token == "real" || current_token == "if" ||
                    current_token == "else" || current_token == "fi" || current_token == "return" || current_token == "put" || current_token == "get" || current_token == "while" || current_token == "endwhile" || current_token == "true" || current_token == "false")
                {
                    current_type = current_token;

                    cout << "Keyword: " << current_token << endl;
                }
                else
                {
                    fileWriter << "Identifier: " << current_token << endl;
                }
                current_token = "";
            }
            else if (isdigit(current_char) || current_char == '.')
            {
                current_token += current_char;
                while (isdigit(input[i + 1]) || input[i + 1] == '.')
                {
                    if (input[i + 1] == '.')
                    {
                        flag = true;
                    }
                    current_token += input[++i];
                }
                if ((current_token == "0" || "1" || "2" || "3" || "4" || "5" || "6" || "7" || "8" || "9") && (flag == false))
                {
                    fileWriter << "Integer: " << current_token << endl;
                }
                else if (flag = true)
                {
                    fileWriter << "Real: " << current_token << endl;
                }
                current_token = "";
            }
            else if (current_char == '=' || current_char == '!' || current_char == '>' || current_char == '<' || current_char == '*' ||
                     current_char == '/' || current_char == '-' || current_char == '+')
            {
                opflag = true;

                if ((current_char == '<' || current_char == '>') && (input[i + 1] == '='))
                {

                    cout << "Operator: " << current_char << input[i + 1] << endl;
                    i++;
                    opflag = false;
                }
                else if ((current_char == '=') && (input[i + 1] == '>' || input[i + 1] == '<'))
                {
                    cout << "Operator: " << current_char << input[i + 1] << endl;
                    i++;
                    opflag = false;
                }
                if (opflag == true)
                    cout << "Operator: " << current_char << endl;
            }
            else if (current_char == '(' || current_char == ')' || current_char == '{' || current_char == '}' || current_char == ';')
            {
                fileWriter << "Separator: " << current_char << endl;
            }
            else if (current_char == '[')
            {
                while (input[i + 1] != ']' && i < input.length() - 1)
                {
                    i++;
                }
            }
            else
            {
                fileWriter << "Unknown: " << current_char << endl;
                continue;
            }
        }
    }
    inputfile.close();
}

int main(int argc, char *argv[])
{

    lexer();
}