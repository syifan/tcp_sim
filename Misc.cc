#include <cstdlib>

#include "Misc.h"

namespace tcpsim
{

Misc::Misc()
{
	// TODO Auto-generated constructor stub

}

Misc::~Misc()
{
	// TODO Auto-generated destructor stub
}


bool Misc::Happen(double probability)
{
	double random_number = ((double) rand() / (RAND_MAX));
	if (random_number < probability)
		return true;

	return false;
}

} /* namespace tcpsim */
