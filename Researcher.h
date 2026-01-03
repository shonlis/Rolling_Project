#ifndef Researcher__H_
#define Researcher__H_

#include "Worker.h"
#include "Article.h"


class Researcher : public Worker
{
private:
	int maxNumberOfArticles;
	int currentNumberOfArticles;
	Article** publishedArticles;

public:
	Researcher(const Worker& worker);
	~Researcher() {delete[]publishedArticles;};
	bool addArticle(Article& article);

	// getters
	int getCurrentNumberOfArticles() const { return currentNumberOfArticles; };

	//setters

	// other methods
	const Researcher& operator=(const Researcher& researcher);
	bool articleExist(const Article& article);
	bool operator<(const Researcher& researcher) const;
	bool operator>(const Researcher& researcher) const;

	friend std::ostream& operator<<(std::ostream& os, const Researcher& r);
};

#endif // !Researcher__H_