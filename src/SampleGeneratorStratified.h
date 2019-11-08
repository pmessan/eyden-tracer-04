#pragma once

#include "SampleGenerator.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>

class CSampleGeneratorStratified : public CSampleGenerator
{
public:
	virtual void getSamples(int n, float* u, float* v, float* weight) const override
	{
		// --- PUT YOUR CODE HERE ---
		int m = sqrt(n);
        	for (int i = 0; i < m; i++) {
            		for (int j = 0; j < m; j++) {
						int pos = i * m + j;
                		u[pos] = (i + (float)rand() / (float)RAND_MAX) / m;
               			v[pos] = (j + (float)rand() / (float)RAND_MAX) / n;
                		weight[pos] = 1.0f/n;
            		}
        	}
	}
};
