// Article implementation

#include "Article.h"


Article::Article(const Article& article) : Article(article.title, article.publicationDate, article.magazinName){}

Article::Article(Article&& article) : title(article.title), publicationDate(article.publicationDate), magazinName(article.magazinName)
{
	article.title = nullptr;
	article.publicationDate = nullptr;
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

ostream& operator<<(ostream& os, const Article& a)
{
	os << "Article Details: " << a.getTitle() << ": Publication Date = " << a.getPublicationDate() << ", Magazin Name = " << a.getMagazinName() << endl;
	return os;
}
