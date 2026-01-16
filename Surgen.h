#ifndef Surgen__H_
#define Surgen__H_


#include "Doctor.h"

class Surgen : public Doctor
{
	int numberOfOperations;

	public:

		friend ostream& operator<<(ostream& os, const Surgen& s);

		Surgen(const Worker& worker);

		Surgen(const Surgen& surgen);
		Surgen(Surgen&& surgen);

		// setters
		void setNumberOfOperations(int numberOfOperations);

		// getters
		int getNumberOfOperations() const { return numberOfOperations; }

};

#endif // !Surgen__H_