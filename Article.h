#ifndef ARTICLE_H
#define ARTICLE_H

#include <string>
#include <ostream>
using namespace std;

class Article {
protected:
    std::string title;
    std::string publicationDate;
    std::string magazinName;

public:
    Article(const Article& article);
    Article(Article&& article) noexcept;

    // constructors and destructor
    Article(const string title, const string publicationDate, const string magazinName);
    ~Article() = default;

    // getters (keep C-style API by returning c_str())
    const string getTitle() const { return title.c_str(); };
    const string getPublicationDate() const { return publicationDate.c_str(); };
    const string getMagazinName() const { return magazinName.c_str(); };

    //setters
    bool setTitle(const string title);
    bool setPublicationDate(const string publicationDate);
    bool setMagazinName(const string magazinName);

    // operators overloading
    friend std::ostream& operator<<(std::ostream& os, const Article& a);

    // Add operator== to compare Article objects by value
    bool operator==(const Article& other) const;
};

#endif // ARTICLE_H
