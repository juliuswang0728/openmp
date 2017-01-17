//
// Created by juliuswang on 1/17/17.
//

#ifndef OPENMP_PROCESS_H
#define OPENMP_PROCESS_H

#include "preprocessors.h"
#include "filters.h"
#include "predictors.h"

/*
 * Where the full working pipeline to do defect detection / classification
 * is controlled through three main classes, preprocessor, filter, and classifier,
 * which are basically the key components for defect detection.
 *
 */

class process {
public:
    // input sources or configuration files
    string ifile;

    preprocessors preprocessor;
    filters filter;
    predictors classifier;

    process(string filename);
    ~process();

    void run();
};


#endif //OPENMP_PROCESS_H
