// Article implementation
#pragma warning(disable: 4996)
using namespace std;
#include <iostream>

#include "Article.h"


Article::Article(const Article& article) : Article(article.title, article.publicationDate, article.magazinName){}

Article::Article(Article&& article)
{
	this->title = article.title;
	article.title = nullptr;
	this->publicationDate = article.publicationDate;
	article.publicationDate = nullptr;
	this->magazinName = article.magazinName;
	article.magazinName = nullptr;
}

Article::Article(const char* title, const char* publicationDate, const char* magazinName)
{
	this->title = new char[strlen(title) + 1];
	strcpy(this->title, title);
	this->publicationDate = new char[strlen(publicationDate) + 1];
	strcpy(this->publicationDate, publicationDate);
	this->magazinName = new char[strlen(magazinName) + 1];
	strcpy(this->magazinName, magazinName);
}

Article::~Article()
{
	delete[] title;
	delete[] publicationDate;
	delete[] magazinName;
}

bool Article::setTitle(const char* title)
{
	if (this->title) {
		delete[] this->title;
	}
	this->title = new char[strlen(title) + 1];
	strcpy(this->title, title);
	return true;
}

bool Article::setPublicationDate(const char* publicationDate)
{
	if (this->publicationDate) {
		delete[] this->publicationDate;
	}
	this->publicationDate = new char[strlen(publicationDate) + 1];
	strcpy(this->publicationDate, publicationDate);
	return true;
}

bool Article::setMagazinName(const char* magazinName)
{
	if (this->magazinName) {
		delete[] this->magazinName;
	}
	this->magazinName = new char[strlen(magazinName) + 1];
	strcpy(this->magazinName, magazinName);
	return true;
}

bool Article::operator==(const Article& other) const
{
	// Add operator== to compare Article objects
	// Compare by pointer equality for now, as the rest of the code uses pointers
		return this == &other;
	
}

ostream& operator<<(ostream& os, const Article& a)
{
	os << "Article Details: " << a.getTitle() << ": Publication Date = " << a.getPublicationDate() << ", Magazin Name = " << a.getMagazinName() << endl;
	return os;
}
