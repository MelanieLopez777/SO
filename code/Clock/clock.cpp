#include "clock.h"

void Clock::setArriveTime(int arriveTime)
{
    this->arriveTime = arriveTime;
}
void Clock::setEndTime(int endTime)
{
    this->endTime = endTime;
}
void Clock::setWaitingTime(int waitingTime)
{
    this->waitingTime = waitingTime;
}
void Clock::setResponseTime(int responseTime)
{
    this->responseTime = responseTime;
}
void Clock::setReturnTime(int returnTime)
{
    this->returnTime = returnTime;
}
void Clock::setServiceTime(int serviceTime)
{
    this->serviceTime = serviceTime;
}
void Clock::setEstimatedTimeAmount(int estimatedTimeAmount)
{
    this->estimatedTimeAmount = estimatedTimeAmount;
}

void Clock::setElapsedTime(int elapsedTime)
{
    this->elapsedTime = elapsedTime;
}

int Clock::getEndTime() const
{
    return endTime;
}
int Clock::getWaitingTime() const
{
    return waitingTime;
}
int Clock::getResponseTime() const
{
    return responseTime;
}
int Clock::getReturnTime() const
{
    return returnTime;
}
int Clock::getServiceTime() const
{
    return serviceTime;
}
int Clock::getElapsedTime() const
{
    return elapsedTime;
}
int Clock::getEstimatedTimeAmount() const
{
    return estimatedTimeAmount;
}


// Time calculations

void Clock::calcReturnTime()
{
    setReturnTime(endTime - arriveTime);
}

void Clock::calcResponseTime(int generalCounter)
{
    setResponseTime(generalCounter - arriveTime);
}

void Clock::calcServiceTime()
{
    setServiceTime(returnTime - waitingTime);
}

void Clock::calcWaitingTime()
{
    setWaitingTime(returnTime - serviceTime);
}