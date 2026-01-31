#ifndef Surgey__H_
#define Surgey__H_

#include "VisitCard.h"

class Surgery : public VisitCard
{
	
	int surgeryRoomNumber;
	bool isFast;

	public:

		Surgery(const string& purposeOfVisit, const string& visitingDate, Department& departmentsToVisit, const string& hostWorker, int surgeryRoomNumber, bool isFast);
		

		//setters
		void setSurgeryRoomNumber(int surgeryRoomNumber);
		void setIsFast(bool isFast);
		
		// getters
		int getSurgeryRoomNumber() const { return surgeryRoomNumber; }
		bool getIsFast() const { return isFast; }

		void toOs(ostream& os) const override;

};

#endif // Surgey__H_