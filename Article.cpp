
// Article implementation
#pragma warning(disable: 4996)
#include <iostream>

#include "Article.h"

Article::Article(const Article& article)
    : title(article.title), publicationDate(article.publicationDate), magazinName(article.magazinName) {}

Article::Article(Article&& article) noexcept
    : title(std::move(article.title)), publicationDate(std::move(article.publicationDate)), magazinName(std::move(article.magazinName)) {}

Article::Article(const char* title, const char* publicationDate, const char* magazinName)
    : title(title ? title : std::string()), publicationDate(publicationDate ? publicationDate : std::string()), magazinName(magazinName ? magazinName : std::string()) {}

bool Article::setTitle(const char* title)
{
    this->title = title ? title : std::string();
    return true;
}

bool Article::setPublicationDate(const char* publicationDate)
{
    this->publicationDate = publicationDate ? publicationDate : std::string();
    return true;
}

bool Article::setMagazinName(const char* magazinName)
{
    this->magazinName = magazinName ? magazinName : std::string();
    return true;
}

bool Article::operator==(const Article& other) const
{
    return title == other.title && publicationDate == other.publicationDate && magazinName == other.magazinName;
}

std::ostream& operator<<(std::ostream& os, const Article& a)
{
    os << "Article Details: " << a.getTitle() << ": Publication Date = " << a.getPublicationDate() << ", Magazin Name = " << a.getMagazinName() << std::endl;
    return os;
}
