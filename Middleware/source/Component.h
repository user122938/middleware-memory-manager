#pragma once
class Event {
private:
	int id;
	int idTarget;
	int eType;
	int iParam;
	void* pParam;
public:
	Event() {}
	Event(int id,
		int idTarget,
		int eType,
		int iParam,
		void* pParam) {}
	int getTarget() { return this->idTarget; }
};
class Component
{
private:

public:
	void sendEvent(Event* pEvent) {
	}
	virtual void processAEvent(Event* pEvent) {
	}
};

#include <map>
using namespace std;
class EventQueue {
public:
	void enQueue(Event* pEvent) {
	}
	Event* deQueue() {
	}
};

class Scheduler : public Component {
private:
	map<int, Component*> mapComponents;
	EventQueue* pEventQueue;
public:
	void run() {
		Event* pEvent = pEventQueue->deQueue();
		while (pEvent!=nullptr) {
			this->mapComponents[pEvent->getTarget()]->processAEvent(pEvent);
			pEvent = pEventQueue->deQueue();
		}
	}
};