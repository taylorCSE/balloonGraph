/**
 * \file Plot.h
 * \brief This file contains the definition for the plot class
 *
 * Objects derived from this class hold the the actual data for a plot.
 * Plots are generally returned by the database and then graphed.
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
