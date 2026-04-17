#include <cstdint>
#include <cstdio>
#include <stack>
#include <ctype.h>

/**
 * Return the precedence level for a binary operator.
 *
 * @param op The operator character to evaluate ('+', '-', '*', '/').
 * @return 2 for '*' or '/', 1 for '+' or '-', otherwise -1 for unknown operators.
 */
int precedence(char op)
{
    if ('+' == op || '-' == op)
    {
        return 1;
    }
    else if ('*' == op || '/' == op)
    {
        return 2;
    }
    else
    {
        return -1;
    }
}

/**
 * Convert an infix expression to postfix (Reverse Polish Notation).
 *
 * @param infix The input infix expression as a null-terminated string.
 * @param postFix Output buffer that receives the postfix expression.
 * @return 0 on success, -1 on invalid parentheses or malformed input.
 */
int infixToPostfix(const char* const infix, char* const postFix)
{
    std::stack<char> stack;

    uint32_t idx = 0U;
    uint32_t jdx = 0U;

    while (0 != infix[idx])
    {
        char c = infix[idx++];

        if (isalnum(c))
        {
            /*
             * Operands are copied directly to the output.
             */
            postFix[jdx++] = c;
        }
        else if ('(' == c)
        {
            /*
             * Left parenthesis is pushed onto the stack and delays operator
             * output until the matching ')' is found.
             */
            stack.push(c);
        }
        else if (')' == c)
        {
            /*
             * Pop operators until the matching '(' is found.
             */
            while (!stack.empty() && '(' != stack.top())
            {
                postFix[jdx++] = stack.top();
                stack.pop();
            }
            if (!stack.empty() && '(' != stack.top())
            {
                return -1;
            }
            else
            {
                /* pop '(' character */
                stack.pop();
            }
        }
        else
        {
            /*
             * For an operator, pop operators with higher or equal precedence
             * from the stack before pushing the new operator.
             */
            while (!stack.empty() && precedence(c) <= precedence(stack.top()))
            {
                postFix[jdx++] = stack.top();
                stack.pop();
            }
            stack.push(c);
        }
    }

    /*
     * Pop any remaining operators from the stack to the output.
     */
    while (!stack.empty())
    {
        postFix[jdx++] = stack.top();
        stack.pop();
    }

    /*
     * Terminate the postfix string with a null byte.
     */
    postFix[jdx] = '\0';

    return 0;
}

/**
 * Evaluate a postfix expression using a stack.
 *
 * @param postFix The postfix expression to evaluate.
 * @return The integer result of the evaluated expression.
 */
int eval(const char* postFix)
{
    int             result = 0;
    uint32_t        idx    = 0U;
    std::stack<int> stack;

    while (postFix[idx])
    {
        char c = postFix[idx++];
        if (isalnum(c))
        {
            /*
             * Convert digit character to integer value.
             */
            stack.push(c - '0');
        }
        else
        {
            /*
             * Pop the two top values for the operator.
             * arg1 is the first operand and arg2 is the second operand.
             */
            int arg2 = stack.top();
            stack.pop();
            int arg1 = stack.top();
            stack.pop();
            switch (c)
            {
                case '+':
                {
                    stack.push(arg1 + arg2);
                    break;
                }
                case '-':
                {
                    stack.push(arg1 - arg2);
                    break;
                }
                case '*':
                {
                    stack.push(arg1 * arg2);
                    break;
                }
                case '/':
                {
                    stack.push(arg1 / arg2);
                    break;
                }
            }
        }
    }
    result = stack.top();
    stack.pop();
    return result;
}

/**
 * Example driver for infix-to-postfix conversion and postfix evaluation.
 *
 * Demonstrates conversion of a hard-coded infix string and prints the result.
 */
int main()
{
    char infix[]     = "(3+4)*2";
    char postFix[10] = {};

    /* As infix is difficult to solve by algorithm and operator precedences
     * It is first converted to prefix or postfix and then solved
     */
    infixToPostfix(infix, postFix);

    printf("Infix: %s\n", infix);
    printf("Postfix: %s\n", postFix);
    printf("Solution: %d\n", eval(postFix));
    return 0;
}
