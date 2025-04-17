#include "EventHandler.h"
#include <stdio.h>
#include <string.h>

bool EventHandler::events[];

EventHandler::EventHandler()
{
}

EventHandler::~EventHandler()
{
}

bool EventHandler::Update()
{
	bool success = true;


	return success;
}

void EventHandler::SetButton(GameEvents eventNum, bool pressed)
{
	events[eventNum] = pressed;
}
