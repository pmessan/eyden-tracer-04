#pragma once

#include "SampleGenerator.h"
#include <math.h>

class CSampleGeneratorRegular : public CSampleGenerator
{
public:
	virtual void getSamples(int n, float* u, float* v, float* weight) const override
	{
		// --- PUT YOUR CODE HERE ---
		int m = sqrt(n);

		for(int i = 0; i < m; i ++)
			for(int j = 0; j < m; j ++){
				int pos = i * m + j;
				u[pos] 	= (i + 0.5f)/m;
				v[pos] 	= (j + 0.5f)/n;
				weight[pos] = 1.0f / n;
			}
	}
};
