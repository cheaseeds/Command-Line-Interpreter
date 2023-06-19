#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP
//
#include <string>
#include <vector>


//
class Executor
{
	//
	public:
		
		//
		Executor();
		
		//
		bool executeCommand(char * command);
		static void* threadRunner(void* param);
		
	//
	private:
		
		//
		
};

#endif