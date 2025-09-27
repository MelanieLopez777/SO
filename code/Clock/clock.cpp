#include "clock.h"

Clock::Clock()
{
    arriveTime = -1;        
    endTime = -1;
    waitingTime = 0;
    responseTime = -1;      
    returnTime = -1;
    serviceTime = 0;
    estimatedTimeAmount = 0;
    elapsedTime = 0;
    blockedTime = 0;
}

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

void Clock::setBlockedTime(int blockedTime)
{
    this->blockedTime = blockedTime;
}


int Clock::getArriveTime() const
{
    return arriveTime;
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
int Clock::getBlockedTime() const
{
    return blockedTime;
}



// Time calculations

void Clock::calcReturnTime()
{
    setReturnTime(endTime - arriveTime);
}

void Clock::calcResponseTime(int generalCounter)
{
    if (arriveTime >= 0) {
        setResponseTime(generalCounter - arriveTime);
    } else {
        setResponseTime(0);
    }
}

void Clock::calcServiceTime()
{
    setServiceTime(returnTime - waitingTime);
}

void Clock::calcWaitingTime()
{
    setWaitingTime(returnTime - serviceTime);
}
int Clock::decreaseBlockedTime()
{
    return --blockedTime;
}

