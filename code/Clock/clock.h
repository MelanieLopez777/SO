#pragma once

class Clock
{
private:
    int arriveTime;
    int endTime;
    int waitingTime;
    int responseTime;
    int returnTime;
    int serviceTime;
    int estimatedTimeAmount;
    int elapsedTime;
    
public:
    void setArriveTime(int arriveTime);
    void setEndTime(int endTime);
    void setWaitingTime(int waitingTime);
    void setResponseTime(int responseTime);
    void setReturnTime(int returnTime);
    void setServiceTime(int serviceTime);
    void setEstimatedTimeAmount(int estimatedTimeAmount);
    void setElapsedTime(int elapsedTime);

    int getArriveTime() const;
    int getEndTime() const;
    int getWaitingTime() const;
    int getResponseTime() const;
    int getReturnTime() const;
    int getServiceTime() const;
    int getEstimatedTimeAmount() const;
    int getElapsedTime() const;

    void calcReturnTime();
    void calcResponseTime(int generalCounter);
    void calcServiceTime();
    void calcWaitingTime();
    void calcElapsedTime();
};