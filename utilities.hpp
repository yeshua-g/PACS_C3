#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <muParser.h>
#include <cmath>
#include <memory>
#include <string>
#include <functional>
#include <iostream>
#include <vector>
#include <fstream>

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

void generateVTKFile(const std::string & filename, 
                     const std::vector<std::vector<double>> & scalarField, 
                     int nx, int ny, double hx, double hy){

    // Open file
    std::ofstream vtkFile(filename);

    // Check if file is open
    if (!vtkFile.is_open()) {
        std::cerr << "Error: could not open file " << filename << std::endl;
        return;
    }

    // Write header
    vtkFile <<  "# vtk DataFile Version 3.0\n";
    vtkFile << "Scalar Field Data\n";
    vtkFile << "ASCII\n";                               

    // Write grid data

    // type of dataset
    vtkFile << "DATASET STRUCTURED_POINTS\n";      
    // number of points in each direction                       
    vtkFile << "DIMENSIONS " << nx+1 << " " << ny+1 << " " << 1 << "\n"; 
    // origin of the grid 
    vtkFile << "ORIGIN 0 0 0\n";                                     
    // spacing between points     
    vtkFile << "SPACING" << " " << hx << " " << hy << " " << 1 << "\n"; 
    // number of points  
    vtkFile << "POINT_DATA " << (nx+1) * (ny+1) << "\n";                  
                                                                
    
    // Write scalar field data

    // name of the scalar field
    vtkFile << "SCALARS scalars double\n";   
    // color table            
    vtkFile << "LOOKUP_TABLE default\n";                

    //write scalar field data
    for (int j = 0; j < ny+1; j++) {
        for (int i = 0; i < nx+1; i++) {
            vtkFile <<  scalarField[i][j] << "\n";
        }
    }

};



#endif // UTILITIES_HPP