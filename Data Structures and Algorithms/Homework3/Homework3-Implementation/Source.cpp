#include <iostream>
#include "./MyStore.h"
#include "./MyList.hpp"

void input(MyStore& st) {
	int workersCount, customersCount, arriveMinute, banana, schweppes, maxWaitTime;

	std::cin >> workersCount >> customersCount;

	st.init(workersCount, 0, 0);
	for (int i = 0; i < customersCount; i++)
	{
		std::cin >> arriveMinute >> banana >> schweppes >> maxWaitTime;
		MyClient client = MyClient(arriveMinute, banana, schweppes, maxWaitTime, i);
		st.awayClients.push_back(client);
	}
}

int main() {
	MyStore st;
	
	input(st);
	int minute = 0;
	st.unitTestMode = false;

	while (!st.awayClients.empty() || !st.waitingClients.empty() || !st.busyWorkers.empty()) {
		st.advanceTo(minute);
		minute++;
	}

	return 0;
}

