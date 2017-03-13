//
// Created by AJ Pryor on 3/13/17.
//

#ifndef PRISM_GETWORKID_H
#define PRISM_GETWORKID_H
#include "params.h"
#include "configure.h"
//#include <mutex>
//template <class T>
//class PRISM::Parameters;
// helper function for dispatching work
bool getWorkID_probePos(const PRISM::Parameters<PRISM_FLOAT_PRECISION>& pars, size_t& Nstart, size_t& Nstop);
#endif //PRISM_GETWORKID_H