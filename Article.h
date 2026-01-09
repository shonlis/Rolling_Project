#ifndef ARTICLE_H
#define ARTICLE_H


#include <string>
#include <vector>

class Article {
protected:
	char* title;
	char* publicationDate;
	char* magazinName;


public:
	Article(const Article& article); 
	Article(Article&& article); 

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
	bool operator==(const Article& other) const;
    
};

#endif // ARTICLE_H
