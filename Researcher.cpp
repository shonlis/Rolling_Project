#pragma warning(disable: 4996)
#include <iostream>
using namespace std;

#include "Researcher.h"
#include "Article.h"
#include "Worker.h"

Researcher::Researcher(const char* name, int id, int birthYear, Gender gender, Article** articles)
	: Worker(name, id, birthYear, gender), maxNumberOfArticles(2), currentNumberOfArticles(0)
{
	this->publishedArticles = new Article*[maxNumberOfArticles];
	if(articles != nullptr)
	{
		for (int i = 0; i < maxNumberOfArticles; i++)
		{
			this->publishedArticles[i] = articles[i];
		}
	}
	else {
		for (int i = 0; i < maxNumberOfArticles; ++i) publishedArticles[i] = nullptr;
	}
}

Researcher::Researcher(const Worker& worker) : Worker(worker)
{
	maxNumberOfArticles = 2;
	this->publishedArticles = new Article*[maxNumberOfArticles];
	currentNumberOfArticles = 0;
}

Researcher::Researcher(const Researcher& researcher) : Worker(researcher)
{
	maxNumberOfArticles = researcher.maxNumberOfArticles;
	currentNumberOfArticles = researcher.currentNumberOfArticles;
	publishedArticles = new Article * [maxNumberOfArticles];
	for (int i = 0; i < maxNumberOfArticles; i++)
	{
		publishedArticles[i] = researcher.publishedArticles[i];
	}
}

Researcher::Researcher(Researcher&& researcher) : Worker(move(researcher))
{
	maxNumberOfArticles = researcher.maxNumberOfArticles;
	currentNumberOfArticles = researcher.currentNumberOfArticles;
	publishedArticles = researcher.publishedArticles;
	researcher.publishedArticles = nullptr;
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

void Researcher::showthis() const
{
	Worker::showthis();
	cout << "Number of Published Articles: " << currentNumberOfArticles << endl;
	for (int i = 0; i < currentNumberOfArticles; i++) {
		cout << "Article " << i + 1 << ": " << (publishedArticles[i] ? publishedArticles[i]->getTitle() : "not defined") << endl;
	}
};

bool Researcher::articleExist(const Article& article)
{
	for (int i = 0; i < currentNumberOfArticles; i++)
	{
		if (*(publishedArticles[i]) == article) // we need to create operator== in Article class
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

void Researcher::toOs(ostream& os) const
{
	Worker::toOs(os);
	os << "Number of Published Articles: " << currentNumberOfArticles << endl;
	for (int i = 0; i < currentNumberOfArticles; i++) {
		os << "Article " << i + 1 << ": " << (publishedArticles[i] ? publishedArticles[i]->getTitle() : "not defined") << endl;
	}
}
