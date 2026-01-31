#ifndef Researcher__H_
#define Researcher__H_

#include "Worker.h"
#include <vector>

class Article;

class Researcher : virtual public Worker
{
	int maxNumberOfArticles;
	int currentNumberOfArticles;
	vector <Article*> publishedArticles;

public:
	Researcher(const string& name, int id, int birthYear, Gender gender);
	Researcher(const Researcher& researcher);

	bool addArticle(Article& article);
	int getCurrentNumberOfArticles() const { return currentNumberOfArticles; };

	virtual void showthis() const override;

	bool articleExist(const Article& article) const ;

	bool operator<(const Researcher& researcher) const;
	bool operator>(const Researcher& researcher) const;
	virtual void toOs(ostream& os) const override;

};

#endif // !Researcher__H_
