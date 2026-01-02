#include <iostream>
using namespace std;
#include "Researcher.h"

Researcher::Researcher(const Worker& worker) : Worker(worker)
{
	maxNumberOfArticles = 2;
	this->publishedArticles = new Article*[maxNumberOfArticles];
	currentNumberOfArticles = 0;
}


bool Researcher::addArticle(Article& article)
{

	if (articleExist(article))
		return false;


	if (currentNumberOfArticles == maxNumberOfArticles)
	{
		maxNumberOfArticles *= 2;
		Article** temp = new Article * [maxNumberOfArticles];
		for (int i = 0; i < currentNumberOfArticles; i++)
			temp[i] = this->publishedArticles[i];

		delete[]this->publishedArticles;
		this->publishedArticles = temp;
	}

	this->publishedArticles[currentNumberOfArticles] = &article;
	currentNumberOfArticles++;
	return true;

}

bool Researcher::articleExist(const Article& article)
{
	for (int i = 0; i < currentNumberOfArticles; i++)
	{
		if (publishedArticles[i] == article) // we need to create operator== in Article class/
			return true;
	}
	return false;
}

bool Researcher::operator<(const Researcher& researcher) const
{
	if (this->currentNumberOfArticles < researcher.currentNumberOfArticles)
		return true;
	else
		return false;
}

bool Researcher::operator>(const Researcher& researcher) const
{
	if (this->currentNumberOfArticles > researcher.currentNumberOfArticles)
		return true;
	else
		return false;
}

const Researcher& Researcher::operator=(const Researcher& researcher)
{
	if (this->workerNumber == researcher.workerNumber)
		return *this;

	this->publishedArticles = researcher.publishedArticles;
	this->maxNumberOfArticles = researcher.maxNumberOfArticles;
	this->currentNumberOfArticles = researcher.currentNumberOfArticles;

	return *this;
}
