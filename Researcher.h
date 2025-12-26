#pragma once

#include "Worker.h"
class Article;

class Researcher : public Worker
{
private:
	
	Article* publishedArticles;
public:
	Researcher();
	~Researcher();

};

