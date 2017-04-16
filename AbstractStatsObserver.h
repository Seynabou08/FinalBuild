#pragma once

#ifndef ABSTRACTSTATSOBSERVER_H
#define ABSTRACTSTATSOBSERVER_H

class AbstractStatsObserver
{
public:
	
	AbstractStatsObserver() {};
	~AbstractStatsObserver() {};

	virtual void update() = 0;
};

#endif
