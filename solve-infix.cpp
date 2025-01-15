#include <cstdint>
#include <cstdio>
#include <stack>

int precedence(char op)
{
    if ('+' == op || '-' == op)
    {
        return (1);
    }
    else if ('*' == op || '/' == op)
    {
        return (2);
    }
    else
    {
        return (-1);
    }
}

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
            postFix[jdx++] = c;
        }
        else if ('(' == c)
        {
            stack.push(c);
        }
        else if (')' == c)
        {
            while (!stack.empty() && '(' != stack.top())
            {
                postFix[jdx++] = stack.top();
                stack.pop();
            }
            if (!stack.empty() && '(' != stack.top())
            {
                return (-1);
            }
            else
            {
                /* pop '(' character */
                stack.pop();
            }
        }
        else
        {
            while (!stack.empty() && precedence(c) <= precedence(stack.top()))
            {
                postFix[jdx++] = stack.top();
                stack.pop();
            }
            stack.push(c);
        }
    }

    while (!stack.empty())
    {
        postFix[jdx++] = stack.top();
        stack.pop();
    }
    postFix[++jdx] = '\0';

    return (0);
}

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
            stack.push(c - '0');
        }
        else
        {
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
    return (0);
}
