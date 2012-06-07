#ifndef _UTIMER_H_
#define _UTIMER_H_

#include "..\GameBootstrap\concurrent\Runnable.h"

namespace util
{
template<class T>
class UTimer : public concurrent::Runnable
{
public:
    
	typedef void (T::*FN)();

	UTimer(int interval)
	{
		m_pClass = 0;
		_active = true;
		this->interval = interval;
	}

	~UTimer(){}


	void setCallback(T* obj, FN pCallback)
	{
		m_pClass  = obj;
		m_pMethod = pCallback;
	}


	int  getInterval() { return interval;}

	void stop() { _active = false;}

protected:
    
	DWORD run(void)
	{
		clock_t delayTime = 0;
		while (_active)
		{			
			if (delayTime > clock())
			{
				// espera el tiempo definido segun interval
				while ((delayTime - clock()) > 0) { Sleep(delayTime); }
	
				if (m_pClass && _active)
				{
					(m_pClass->*m_pMethod)();
				}
			}

			delayTime = clock() + interval;
		}

		return 0;
	}

private:
    T*    m_pClass;
    FN    m_pMethod;
	int   interval;
	bool _active;
};
};

#endif

