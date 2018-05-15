#pragma once
#include "Vector.h"
#include "Scope.h"

namespace FieaGameEngine {
	//!GarbageCollectorclass 
	class GarbageCollector
	{
	public:
		//!Default constructor
		GarbageCollector() = default;
		//!Copy and move constructors
		GarbageCollector(GarbageCollector& rhs) = delete;
		GarbageCollector(GarbageCollector&& rhs) = delete;
		GarbageCollector& operator=(GarbageCollector& rhs) = delete;
		GarbageCollector& operator=(GarbageCollector&& rhs) = delete;
		//!Destructor
		~GarbageCollector() = default;
		//!CleanUp function
		/*!
			static cleanup function that is called at the end of each update to delete all the actions
		*/
		static void CleanUp();
	    static Vector<Scope*> garbageList; /*<!Vector that stores pointers to all the actions that needs to be deleted after the current update call */
	};
}

