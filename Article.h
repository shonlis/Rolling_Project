#ifndef ARTICLE_H
#define ARTICLE_H

#include <string>
#include <ostream>
#include <iostream>
using namespace std;

class Article {
protected:
    
    string title;
    string publicationDate;
    string magazinName;

public:
	
	// constructors and destructor
	Article(const string& title, const string& publicationDate, const string& magazinName);

	// getters
	const string getTitle() const { return title; };
	const string getPublicationDate() const { return publicationDate; };
	const string getMagazinName() const { return magazinName; };

	//setters
	bool setTitle(const string& title);
	bool setPublicationDate(const string&  publicationDate);
	bool setMagazinName(const string& magazinName);

    // operators overloading
    friend std::ostream& operator<<(std::ostream& os, const Article& a);

    // Add operator== to compare Article objects by value
    bool operator==(const Article& other) const;
};

#endif // ARTICLE_H
