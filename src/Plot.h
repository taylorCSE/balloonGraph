/**
 * \file Plot.h
 * \brief This file contains the definition for the plot class
 *
 * This class could just be a struct, so it has not .cpp file associated
 * with it.
 */

#ifndef _PLOT_H_
#define _PLOT_H_

#include <vector>

using namespace std;

class Plot {
    public:
        vector<double> time;
        vector<double> altitude; 
        vector<double> data;
};

#endif
