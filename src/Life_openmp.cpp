#include "Life_openmp.h"
#include <omp.h>

#define num_threads 8

void Life_openmp::update()
{
	omp_set_num_threads(num_threads);
	#pragma omp parallel
	{
		#pragma omp for collapse(2) nowait
		for (unsigned int i = 1; i <= height; i++)
		{
			for (unsigned int j = 1; j <= width; j++)
			{
				int m = getNeighbors(j, i);
				if (m == 3)
				{
					setNewLife(j, i, 1);
				}
				if (m == 2)
				{
					setNewLife(j, i, getLifeform(j, i));
				}
				if (m != 3 && m != 2)
				{
					setNewLife(j, i, 0);
				}
			}
		}
	}
	swapGrids();
}
