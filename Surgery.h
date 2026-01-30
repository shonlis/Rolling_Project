#ifndef Surgey__H_
#define Surgey__H_

#include "VisitCard.h"

class Surgery : public VisitCard
{
	
	int surgeryRoomNumber;
	bool isFast;

	public:

        Surgery(const std::string& purposeOfVisit, const std::string& visitingDate, Department& departmentsToVisit, const std::string& hostWorker, int surgeryRoomNumber, bool isFast);
		

		//setters
		void setSurgeryRoomNumber(int surgeryRoomNumber);
		void setIsFast(bool isFast);
		
		// getters
		int getSurgeryRoomNumber() const { return surgeryRoomNumber; }
		bool getIsFast() const { return isFast; }

		// other methods
		void toOs(ostream& os) const override;

};

#endif // Surgey__H_