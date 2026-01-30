// Article implementation
#pragma warning(disable: 4996)

#include "Article.h"

Article::Article(const Article& article)
    : title(article.title), publicationDate(article.publicationDate), magazinName(article.magazinName) {}

Article::Article(Article&& article) noexcept
    : title(std::move(article.title)), publicationDate(std::move(article.publicationDate)), magazinName(std::move(article.magazinName)) {}

Article::Article(const string title, const string publicationDate, const string magazinName)
    : title(title), publicationDate(publicationDate), magazinName(magazinName) {}

bool Article::setTitle(const string title)
{
    this->title = title;
    return true;
}

bool Article::setPublicationDate(const string publicationDate)
{
    this->publicationDate = publicationDate;
    return true;
}

bool Article::setMagazinName(const string magazinName)
{
    this->magazinName = magazinName;
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
