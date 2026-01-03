#ifndef ARTICLE_H
#define ARTICLE_H

using namespace std;
#include <ostream>
#pragma warning(disable: 4996)

#include <string>
#include <vector>

class Article {
protected:
	char* title;
	char* publicationDate;
	char* magazinName;

	Article(const Article& article); // copy c'tor for iherritants only
	Article(Article&& article); // move c'tor for iherritants only

public:

	// constructors and destructor
	Article(const char* title, const char* publicationDate, const char* magazinName);
	~Article();

	// getters
	const char* getTitle() const { return title; };
	const char* getPublicationDate() const { return publicationDate; };
	const char* getMagazinName() const { return magazinName; };

	//setters
	bool setTitle(const char* title);
	bool setPublicationDate(const char* publicationDate);
	bool setMagazinName(const char* magazinName);

	// operators overloading
	friend ostream& operator<<(ostream& os, const Article& a);



    // Add operator== to compare Article objects
    bool operator==(const Article& other) const {
        // Compare by pointer equality for now, as the rest of the code uses pointers
        return this == &other;
    }
};

#endif // ARTICLE_H
