#ifndef Surgen__H_
#define Surgen__H_


#include "Doctor.h"

class Surgen : public Doctor
{
	int numberOfOperations;

	public:

		
		Surgen(const Doctor& doctor);
		Surgen(const Surgen& surgen);

		// setters
		void setNumberOfOperations(int numberOfOperations);

		// getters
		int getNumberOfOperations() const { return numberOfOperations; }

		// other methods

        void toOs(ostream& os) const override;

};

#endif // !Surgen__H_