#ifndef MISC_H_
#define MISC_H_

namespace tcpsim
{

class Misc
{
public:
	Misc();
	virtual ~Misc();

	///
	static bool Happen(double probability);
};

} /* namespace tcpsim */

#endif 
