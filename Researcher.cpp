#pragma warning(disable: 4996)
#include <iostream>
using namespace std;

#include "Researcher.h"
#include "Article.h"
#include "Worker.h"

Researcher::Researcher(const string name, int id, int birthYear, Gender gender, Article** articles)
    : Worker(name, id, birthYear, gender)
{
    if (articles) {
        // assume null-terminated or at least two entries isn't guaranteed -> copy until nullptr
        for (int i = 0; articles[i]; ++i) publishedArticles.push_back(articles[i]);
    }
}

Researcher::Researcher(const Worker& worker) : Worker(worker) {}

Researcher::Researcher(const Researcher& researcher) : Worker(researcher)
{
    publishedArticles = researcher.publishedArticles;
}

Researcher::Researcher(Researcher&& researcher) noexcept : Worker(std::move(researcher)), publishedArticles(std::move(researcher.publishedArticles)) {}


bool Researcher::addArticle(Article& article)
{
    if (articleExist(article)) return false;
    publishedArticles.push_back(&article);
    return true;
}

void Researcher::showthis() const
{
    Worker::showthis();
    cout << "Number of Published Articles: " << getCurrentNumberOfArticles() << endl;
    for (size_t i = 0; i < publishedArticles.size(); ++i) {
        cout << "Article " << i + 1 << ": " << (publishedArticles[i] ? publishedArticles[i]->getTitle() : "not defined") << endl;
    }
}

bool Researcher::articleExist(const Article& article) const
{
    for (auto a : publishedArticles) {
        if (a && *a == article) return true;
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

// assignment operator intentionally deleted in header

void Researcher::toOs(std::ostream& os) const
{
    Worker::toOs(os);
    os << "Number of Published Articles: " << getCurrentNumberOfArticles() << std::endl;
    for (size_t i = 0; i < publishedArticles.size(); ++i) {
        os << "Article " << i + 1 << ": " << (publishedArticles[i] ? publishedArticles[i]->getTitle() : "not defined") << std::endl;
    }
}
