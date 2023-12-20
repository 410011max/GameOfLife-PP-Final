#include "Life3d.h"
#include "pthread.h"
#include "iostream"

const unsigned int numThreads = 1;

namespace life3
{
	struct ThreadData
	{
		int idx;
		Life3d *instance;
		unsigned int startHeight;
		unsigned int endHeight;
	};

	void *updateThread(void *arg)
	{
		ThreadData *data = (ThreadData *)arg;
		//cout << data->idx << endl;
		for (unsigned int i = data->startHeight; i <= data->endHeight; i++)
		{
			for (unsigned int j = 1; j <= data->instance->getWidth(); j++)
			{
				for (unsigned int k = 1; k <= data->instance->getDepth(); k++)
				{
					int m = data->instance->getNeighbors(i, j, k, 1);
					if (m == 5)
					{
						data->instance->setNewLife(i, j, k, 1);
					}
					else if (m < 3)
					{
						data->instance->setNewLife(i, j, k, 0);
					}
					else
					if (m > 5)
					{
						data->instance->setNewLife(i, j, k, 0);
					}
					else if ((m == 4) | (m == 5))
					{
						data->instance->setNewLife(i, j, k, data->instance->getLifeform(i, j, k));
					}
				}
			}
		}
		return NULL;
	}
	void Life3d::update()
	{
		const unsigned int numThreads = 4;
		pthread_t threads[numThreads];
		ThreadData threadData[numThreads];

		unsigned int heightPerThread = height / numThreads;

		for (unsigned int t = 0; t < numThreads; t++)
		{
			threadData[t].instance = this;
			threadData[t].startHeight = t * heightPerThread + 1;
			threadData[t].endHeight = (t == numThreads - 1) ? height : (t + 1) * heightPerThread;
			pthread_create(&threads[t], NULL, updateThread, &threadData[t]);
		}

		for (unsigned int t = 0; t < numThreads; t++)
		{
			pthread_join(threads[t], NULL);
		}
		swapGrids();
	}
	/*
	void Life3d::update()
	{

		for (unsigned int i = 1; i <= height; i++)
		{
			for (unsigned int j = 1; j <= width; j++)
			{
				for (unsigned int k = 1; k <= depth; k++)
				{
					int m = getNeighbors(i, j, k, 1);
					if (m == 5)
					{
						setNewLife(i, j, k, 1);
					}
					else
					if (m < 3)
					{
						setNewLife(i, j, k, 0);
					}
					else
					if (m > 5)
					{
						setNewLife(i, j, k, 0);
					}
					else if ((m == 4) | (m == 5))
					{
						setNewLife(i, j, k, getLifeform(i, j, k));
					}
				}
			}
		}
		swapGrids();
	}
	*/
}
