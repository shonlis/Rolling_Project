#ifndef Researcher__H_
#define Researcher__H_

#include "Worker.h"
#include "Article.h"


class Researcher : public Worker
{
private:
	
	Article* publishedArticles;
public:
	Researcher();
	~Researcher();

};

#endif // !Researcher__H_