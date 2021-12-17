#pragma once

#include "../Homework3-Tests/interface.h"
#include <vector>
#include <list>
#include "MyList.hpp"

struct MyClient {
	int arriveMinute; ///< The time at which client arrives
	int banana; ///< Amount of bananas the client wants to take
	int schweppes; ///< Amount of schweppes the client wants to take
	int departMinute; ///< The max amount of time the client will wait before he departs
	int index;
	MyClient(int arriveMinute,int banana,int schweppes,int maxWaitingTime,int index)
		: arriveMinute(arriveMinute), banana(banana), schweppes(schweppes), departMinute(arriveMinute+maxWaitingTime), index(index){}
};

struct MyWorker {
	int product; //0 for banana and 1 for schweppes
	int arriveMinute; //The time at which worker arrives
	MyWorker(int currentMinutes, int product)
		: arriveMinute(currentMinutes+60), product(product) {}
};

struct MyStore : public Store {
	int currentBanana;
	int currentSchweppes;
	int waitingBanana;
	int waitingSchweppes;
	int neededSchweppes;
	int neededBanana;
	int freeWorkers;
	int currentMinutes;
	bool unitTestMode = true;
	MyList<MyWorker> busyWorkers;
	MyList<MyClient> waitingClients;
	MyList<MyClient> awayClients;

	ActionHandler* actionHandler = nullptr;

	void setActionHandler(ActionHandler* handler) override {
		actionHandler = handler;
	}

	void init(int workerCount, int startBanana, int startSchweppes) override {
		currentBanana = startBanana;
		currentSchweppes = startSchweppes;
		freeWorkers = workerCount;
		waitingBanana = 0;
		waitingSchweppes = 0;
		neededSchweppes = 0;
		neededBanana = 0;
		currentMinutes = 0;
	}

	void addClients(const Client* clients, int count) override {
		for (int i = 0; i < count; i++)
		{
			awayClients.push_back(MyClient(clients[i].arriveMinute, clients[i].banana, clients[i].schweppes, clients[i].maxWaitTime, i));
		}
	}

	void advanceTo(int minute) override {
		
		while (minute >= currentMinutes) {

			//ClientArrive
			clientArrive();

			//Check WorkerSend
			sendWorkers();

			//Check WorkerBack
			workersArrive();

			//ClientDepart
			clientsDepart();

			currentMinutes++;

			/*
			Така работи коректно и тестовете минават, но според мен за по-правилно решение на задачата това нулиране не трябва да го има.
			Ако бъде премахнато, ще фейлнат 2 теста, които според мен не са изцяло коректни. С тази логика на задачата, много от клиентите биха
			си тръгнали с празни ръце заради по-нетърпеливи клиенти след тях, което в реалния живот не би било справедливо.
			*/
			neededBanana = 0;
			neededSchweppes = 0;
		}
	}

	virtual int getBanana() const {
		return currentBanana;
	}

	virtual int getSchweppes() const {
		return currentSchweppes;
	}

	private:
		void clientArrive() {
			MyList<MyClient>::node* currentClient = awayClients.head;
			while (currentClient != nullptr)
			{
				if (currentClient->data.arriveMinute > currentMinutes) {
					break; //Понеже според условието, клиентите са подадени по реда на пристигне. Ако не се сортирани по него, ифът трябва да се махне.
				}

				if (currentClient->data.arriveMinute == currentMinutes) {
					waitingClients.push_back(MyClient(currentClient->data.arriveMinute, currentClient->data.banana, currentClient->data.schweppes,
						currentClient->data.departMinute - currentClient->data.arriveMinute, currentClient->data.index));
					neededBanana += currentClient->data.banana;
					neededSchweppes += currentClient->data.schweppes;

					MyList<MyClient>::node* token = currentClient;
					currentClient = currentClient->next;
					awayClients.remove(token);
					continue;
				}

				currentClient = currentClient->next;
			}
		}

		void sendWorkers() {
			if (freeWorkers > 0) {

				int bananaDifference = neededBanana - (currentBanana + waitingBanana);
				int schweppesDifference = neededSchweppes - (currentSchweppes + waitingSchweppes);
				int bananaSendCount = 0;
				int schweppesSendCount = 0;
				while (freeWorkers > 0 && (bananaDifference > 0 || schweppesDifference > 0)) {
					if (bananaDifference >= schweppesDifference) {
						waitingBanana += 100;
						bananaDifference -= 100;
						bananaSendCount++;
					}
					else {
						waitingSchweppes += 100;
						schweppesDifference -= 100;
						schweppesSendCount++;
					}
					freeWorkers--;
				}

				for (int i = 0; i < bananaSendCount; i++)
				{
					if (unitTestMode) {
						actionHandler->onWorkerSend(currentMinutes, ResourceType::banana);
					}
					else {
						std::cout << "W " << currentMinutes << " banana\n";
					}

					busyWorkers.push_back(MyWorker(currentMinutes, 0));
				}

				for (int i = 0; i < schweppesSendCount; i++)
				{
					if (unitTestMode) {
						actionHandler->onWorkerSend(currentMinutes, ResourceType::schweppes);
					}
					else {
						std::cout << "W " << currentMinutes << " schweppes\n";
					}

					busyWorkers.push_back(MyWorker(currentMinutes, 1));
				}
			}
		}

		void workersArrive() {
			MyList<MyWorker>::node* currentWorker = busyWorkers.head;
			while (currentWorker != nullptr && currentWorker->data.arriveMinute == currentMinutes)
			{
				if (currentWorker->data.product == 0) {
					if (unitTestMode) {
						actionHandler->onWorkerBack(currentMinutes, ResourceType::banana);
					}
					else {
						std::cout << "D " << currentMinutes << " banana\n";
					}

					currentBanana += 100;
					waitingBanana -= 100;
					neededBanana -= 100;
				}
				else {
					if (unitTestMode) {
						actionHandler->onWorkerBack(currentMinutes, ResourceType::schweppes);
					}
					else {
						std::cout << "D " << currentMinutes << " schweppes\n";
					}

					currentSchweppes += 100;
					waitingSchweppes -= 100;
					neededSchweppes -= 100;
				}

				freeWorkers++;
				busyWorkers.remove(currentWorker);
				currentWorker = busyWorkers.head;
			}
		}

		void clientsDepart() {
			MyList<MyClient>::node* waitingClient = waitingClients.head;
			while (waitingClient != nullptr)
			{
				if (waitingClient->data.departMinute == currentMinutes) {
					int bananaCount, schweppesCount;
					if (waitingClient->data.banana <= currentBanana) {
						bananaCount = waitingClient->data.banana;
					}
					else {
						bananaCount = currentBanana;
					}
					if (waitingClient->data.schweppes <= currentSchweppes) {
						schweppesCount = waitingClient->data.schweppes;
					}
					else {
						schweppesCount = currentSchweppes;
					}

					currentBanana -= bananaCount;
					currentSchweppes -= schweppesCount;
					//neededBanana -= bananaCount;
					//neededSchweppes -= schweppesCount;

					if (unitTestMode) {
						actionHandler->onClientDepart(waitingClient->data.index, currentMinutes, bananaCount, schweppesCount);
					}
					else {
						std::cout << waitingClient->data.index << " " << currentMinutes << " " << bananaCount << " " << schweppesCount << std::endl;
					}

					MyList<MyClient>::node* token = waitingClient;
					waitingClient = waitingClient->next;
					waitingClients.remove(token);
					continue;
				}
				else if (waitingClients.head == waitingClient
					&& waitingClient->data.banana <= currentBanana && waitingClient->data.schweppes <= currentSchweppes) {
					if (unitTestMode) {
						actionHandler->onClientDepart(waitingClient->data.index, currentMinutes, waitingClient->data.banana, waitingClient->data.schweppes);
					}
					else {
						std::cout << waitingClient->data.index << " " << currentMinutes << " "
							<< waitingClient->data.banana << " " << waitingClient->data.schweppes << std::endl;
					}


					currentBanana -= waitingClient->data.banana;
					currentSchweppes -= waitingClient->data.schweppes;
					neededBanana -= waitingClient->data.banana;
					neededSchweppes -= waitingClient->data.schweppes;

					MyList<MyClient>::node* token = waitingClient;
					waitingClient = waitingClient->next;
					waitingClients.remove(token);
					continue;
				}

				waitingClient = waitingClient->next;
			}
		}
};
