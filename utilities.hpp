#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <muParser.h>
#include <cmath>
#include <memory>
#include <string>
#include <functional>
#include <iostream>

// Function to create a muParser function from a string expression
inline std::function<double(double, double)> tofunct(const std::string& expression) {
    return [expression](double x, double y) {
        try {
            mu::Parser f;
            f.DefineConst("pi", M_PI);
            f.DefineVar("x", &x);
            f.DefineVar("y", &y);
            f.SetExpr(expression);
            return f.Eval();
        } catch (mu::Parser::exception_type &e) {
            std::cerr << "Error: " << e.GetMsg() << std::endl;
            return 0.0;
        }
    };
}



#endif // UTILITIES_HPP