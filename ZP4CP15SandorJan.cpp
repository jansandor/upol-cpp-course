#include <iostream>
#include <stack>
#include <map>
#include <stdexcept>
#include <cstdarg>
#include <cmath>

using namespace std;

typedef void (*pFunc)(stack<double> &, va_list &); // pojmenovani ukazatele na fci pFunc

inline void check_stack_size(stack<double> &stack, size_t size)
{
    if (stack.size() < size)
        throw runtime_error("Too few values in the stack to execute operation.");
}

void read_push_double(stack<double> &stack, va_list &args)
{
    double value = va_arg(args, double);
    stack.push(value);
}

void read_push_int(stack<double> &stack, va_list &args)
{
    int value = va_arg(args, int);
    stack.push(value); // implicitni pretypovani int na double
}

void add(stack<double> &stack, va_list &args)
{
    check_stack_size(stack, 2);
    double b = stack.top();
    stack.pop();
    stack.top() = stack.top() + b; // a + b
}

void substract(stack<double> &stack, va_list &args)
{
    check_stack_size(stack, 2);
    double b = stack.top();
    stack.pop();
    stack.top() = stack.top() - b; // a - b
}

void multiply(stack<double> &stack, va_list &args)
{
    check_stack_size(stack, 2);
    double b = stack.top();
    stack.pop();
    stack.top() = stack.top() * b; // a * b
}

void divide(stack<double> &stack, va_list &args)
{
    check_stack_size(stack, 2);
    double b = stack.top();
    if (b == 0)
    {
        throw invalid_argument("Cannot divide by zero.");
    }
    stack.pop();
    stack.top() = stack.top() / b; // a / b
}

void square(stack<double> &stack, va_list &args)
{
    check_stack_size(stack, 1);
    stack.top() = pow(stack.top(), 2); // a^2
}

double Kalkulator(map<char, pFunc> &char_func_map, const char *postfix_expr, ...)
{
    stack<double> s;
    va_list args;
    va_start(args, postfix_expr); // init va_list
    int i = 0;
    char c = postfix_expr[i];
    while (c != '\0')
    {
        try
        {
            auto it = char_func_map.find(c);
            if (it == char_func_map.end())
            {
                string msg("Invalid postfix expression \"");
                msg += postfix_expr;
                msg += "\" value '";
                msg += c;
                msg += "'.";
                throw invalid_argument(msg);
            }
            it->second(s, args);
            //pFunc f = it->second;
            //f(s, args);
        }
        catch (...) // zachyceni jakekoliv vyjimky
        {
            va_end(args);
            throw; // propagace vyjimky dal -> throw bez argumentu
        }
        i++;
        c = postfix_expr[i];
    }
    va_end(args);
    return s.top();
}

int main(int argc, char const *argv[])
{
    map<char, pFunc> char_func_map = {
        {'d', read_push_double},
        {'i', read_push_int},
        {'+', add},
        {'-', substract},
        {'*', multiply},
        {'/', divide},
        {'s', square}};

    const char *E = "ii+dsis-*i/";
    try
    {
        double result = Kalkulator(char_func_map, E, 7, 2, 2.5, 4, 5);
        cout << result << endl;
    }
    catch (const exception &e) // const, pokud s vyjimkou nechci dale pracovat/menit ji
    {
        cerr << e.what() << endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
