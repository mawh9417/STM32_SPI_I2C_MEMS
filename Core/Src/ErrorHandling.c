#include "ErrorHandling.h"

void APPLICATION_ASSERT(bool var)
{
	if (var == false)
	{
		while(1);
	}
}
