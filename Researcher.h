#ifndef Researcher__H_
#define Researcher__H_
#include "Worker.h"
#include "Article.h"
#include <vector>
#include <ostream>

class Researcher : virtual public Worker
{
private:
    std::vector<Article> publishedArticles; // store Article copies (owning)

public:
    Researcher(const string name, int id, int birthYear, Gender gender, Article** articles = nullptr);

    Researcher(const Worker& worker);
    Researcher(const Researcher& researcher);
    Researcher(Researcher&& researcher) noexcept;

    ~Researcher() = default;
    bool addArticle(Article& article);

    // getters
    int getCurrentNumberOfArticles() const { return static_cast<int>(publishedArticles.size()); };

    // other methods
    virtual void showthis() const override;

    
    bool articleExist(const Article& article) const;
    bool operator<(const Researcher& researcher) const;
    bool operator>(const Researcher& researcher) const;
    Researcher& operator=(const Researcher& researcher) = delete;
    virtual void toOs(std::ostream& os) const override;
};

#endif // !Researcher__H_
