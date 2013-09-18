
#ifndef TTIME_PAN_H
#define TTIME_PAN_H

/** TTime application panic codes */
enum TTTimePanics
	{
	ETTimeUi = 1
	// add further panics here
	};

inline void Panic(TTTimePanics aReason)
	{
	_LIT(applicationName,"TTime");
	User::Panic(applicationName, aReason);
	}

#endif // TTIME_PAN_H
