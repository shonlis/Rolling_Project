#ifndef Researcher__H_
#define Researcher__H_
#include "Worker.h"

class Article;

class Researcher : virtual public Worker
{
private:
	int maxNumberOfArticles;
	int currentNumberOfArticles;
	Article ** publishedArticles;

public:
	Researcher(const char* name, int id, int birthYear, Gender gender, Article** articles = nullptr);

	Researcher(const Worker& worker);
	Researcher(const Researcher& researcher);
	Researcher(Researcher&& researcher);

	~Researcher() {delete[]publishedArticles;};
	bool addArticle(Article& article);

	// getters
	int getCurrentNumberOfArticles() const { return currentNumberOfArticles; };

	//setters

	// other methods
	virtual void showthis() const override;

	const Researcher& operator=(const Researcher& researcher);
	bool articleExist(const Article& article);
	bool operator<(const Researcher& researcher) const;
	bool operator>(const Researcher& researcher) const;
	virtual void toOs(ostream& os) const override;
};
#endif // !Researcher__H_