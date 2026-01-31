#pragma warning(disable: 4996)

#include "Researcher.h"
#include "Article.h"

Researcher::Researcher(const string& name, int id, int birthYear, Gender gender)
	: Worker(name, id, birthYear, gender), maxNumberOfArticles(2), currentNumberOfArticles(0)
{
	this->publishedArticles.reserve(maxNumberOfArticles);
}

Researcher::Researcher(const Researcher& researcher) :
	Researcher(researcher.getName(), researcher.getId(), researcher.getBirthYear() ,researcher.getGender())
{
	this->publishedArticles = researcher.publishedArticles;
	this->maxNumberOfArticles = researcher.maxNumberOfArticles;
	this->currentNumberOfArticles = researcher.currentNumberOfArticles;
}

bool Researcher::addArticle(Article& article)
{

	if (articleExist(article))
		return false;


	if (currentNumberOfArticles == maxNumberOfArticles)
	{
		maxNumberOfArticles *= 2;
		this->publishedArticles.reserve(maxNumberOfArticles);
	}
	Article* articleCopy = new Article(article.getTitle(), article.getPublicationDate(), article.getMagazinName());
	this->publishedArticles.push_back(articleCopy);
	currentNumberOfArticles++;
	return true;
}

void Researcher::showthis() const
{
	vector<Article*>::const_iterator itr = publishedArticles.begin();
	vector<Article*>::const_iterator itrEnd = publishedArticles.end();

	Worker::showthis();
	cout << "Number of Published Articles: " << currentNumberOfArticles << endl;
	for (int i = 0; itr < itrEnd; ++itr, i++)
	{
		cout << "Article " << i + 1 << ": ";
		if ((*itr)->getTitle().empty())
		{
			cout << "not defined" << endl;
		}
		else
		{
			cout << (*itr)->getTitle() << endl;
		}
	}
};

bool Researcher::articleExist(const Article& article) const
{
	vector<Article*>::const_iterator itr = publishedArticles.begin();
	vector<Article*>::const_iterator itrEnd = publishedArticles.end();

	for (; itr < itrEnd; ++itr)
	{
		if (((*itr)->getTitle() == article.getTitle()) && ((*itr)->getMagazinName() == article.getMagazinName()) && ((*itr)->getPublicationDate() == article.getPublicationDate())) // we need to create operator== in Article class
			return true;
	}
	return false;
}

bool Researcher::operator<(const Researcher& researcher) const
{
    return getCurrentNumberOfArticles() < researcher.getCurrentNumberOfArticles();
}

bool Researcher::operator>(const Researcher& researcher) const
{
    return getCurrentNumberOfArticles() > researcher.getCurrentNumberOfArticles();
}


void Researcher::toOs(ostream& os) const
{
	vector<Article*>::const_iterator itr = publishedArticles.begin();
	vector<Article*>::const_iterator itrEnd = publishedArticles.end();

	Worker::toOs(os);
	os << "Number of Published Articles: " << currentNumberOfArticles << endl;
	for (int i = 0; itr < itrEnd; ++itr)
	{
		os << "Article " << i + 1 << ": ";
		if ((*itr)->getTitle().empty())
		{
			os << "not defined" << endl;
		}
		else
		{
			os << (*itr)->getTitle() << endl;
		}
		i++;
	}
}