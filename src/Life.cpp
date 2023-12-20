#include "Life.h"
#include "pthread.h"
#include "iostream"

const unsigned int numThreads = 4;

struct ThreadData {
	int idx;
	unsigned int start;
	unsigned int end;
	Life* life;
};

void* updateThread(void* arg) {
	ThreadData* data = (ThreadData*)arg;
	for (unsigned int i = data->start; i <= data->end; i++) {
		for (unsigned int j = 1; j <= data->life->getWidth(); j++) {
			int m = data->life->getNeighbors(j, i, 1);
			if (m == 3) {
				data->life->setNewLife(j, i, 1);
			}
			if (m == 2) {
				data->life->setNewLife(j, i, data->life->getLifeform(j, i));
			}
			if (m != 3 && m != 2)
			{
				data->life->setNewLife(j, i, 0);
			}
		}
	}

	return NULL;
}

void Life::update() {
	pthread_t threads[numThreads];
	ThreadData threadData[numThreads];

	unsigned int rowsPerThread = height / numThreads;

	for (unsigned int i = 0; i < numThreads; i++) {
		threadData[i].start = i * rowsPerThread + 1;
		threadData[i].end = (i+1) * rowsPerThread;
		threadData[i].life = this;
		threadData[i].idx = i;

		pthread_create(&threads[i], NULL, updateThread, &threadData[i]);
	}

	for (unsigned int i = 0; i < numThreads; i++) {
		pthread_join(threads[i], NULL);
	}
	swapGrids();
}
/*
void Life::update()
{
	for (unsigned int i = 1; i <= height; i++)
	{
		for (unsigned int j = 1; j <= width; j++)
		{
			int m = getNeighbors(j, i, 1);
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
	swapGrids();
}
*/