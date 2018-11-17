#pragma once
// the master header file of djaha's library.
#ifndef _DJALIB_H_
#define _DJALIB_H_

// math:
#include "djalib_math.h"

#include "components\mutual\djalib_roman.h"
#include "components\mutual\djalib_point.h"
#include "components\mutual\djalib_complex.h"

#include "components\matrix\djalib_matrix.h"
#include "components\counter\djalib_counter.h"
#include "components\fraction\djalib_fraction.h"

// algorithms & data strctures:
#include "components\linkedlist\djalib_linkedlist.h"
#include "componentsII\design\djalib_algorithm.h"
#include "componentsII\design\djalib_pair.h"

// other components:
#include "components\mutual\djalib_text.h"
#include "components\mutual\djalib_tinystr.h"
#include "components\mutual\djalib_fullstr.h"

#include "componentsII\design\djalib_wiseptr.h"

// functors:
#include "djalib_functor.h"

// design model:
#include "components\mutual\djalib_objectpool.h"
#include "componentsII\design\djalib_reflection.h"

// overall test class:
#include "djalib_test.h"

namespace djalib
{
	// macro definitions:
#define BLANK \
	std::cout << "\n"
#define PAUSE \
	std::system("pause")

}

#endif
