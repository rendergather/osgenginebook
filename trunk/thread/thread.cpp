/* -*-c++-*- Copyright (C) 2009 Wang Rui <wangray84 at gmail dot com>
 * OpenSceneGraph Engine Book - Design and Implementation
 * An example of designing a counting thread
*/

#include <OpenThreads/Thread>
#include <OpenThreads/Block>
#include <iostream>

class TestThread : public OpenThreads::Thread
{
public:
	TestThread() : _done(false), _count(0) {}
	~TestThread() { cancel(); }
	
	void block() { _operator.block(); }
	
	virtual int cancel()
	{
		_operator.release();
		_done = true;
		while( isRunning() )
			OpenThreads::Thread::YieldCurrentThread();
		return 0;
	}
	
	virtual void run()
	{
		do
		{
			std::cout << "(" << _count << ")";
			++_count;

			if ( _count==10 )
			{
				_operator.release();
				_operator.reset();
				_operator.block();
			}
			microSleep( 150000L );
		} while( !_done );
	}
protected:
	bool _done;
	unsigned long _count;
	OpenThreads::Block _operator;
};

int main(int argc, char** argv)
{
	TestThread t;
	t.start();
	t.block();
	std::cout << "(Main)" << std::endl;
	t.cancel();
	return 0;
}
