#ifndef ARTICLE_H
#define ARTICLE_H

#include <string>
#include <iostream>

class Article {
protected:
    std::string title;
    std::string publicationDate;
    std::string magazinName;

public:
    Article(const Article& article);
    Article(Article&& article) noexcept;

    // constructors and destructor
    Article(const char* title, const char* publicationDate, const char* magazinName);
    ~Article() = default;

    // getters (keep C-style API by returning c_str())
    const char* getTitle() const { return title.c_str(); };
    const char* getPublicationDate() const { return publicationDate.c_str(); };
    const char* getMagazinName() const { return magazinName.c_str(); };

    //setters
    bool setTitle(const char* title);
    bool setPublicationDate(const char* publicationDate);
    bool setMagazinName(const char* magazinName);

    // operators overloading
    friend std::ostream& operator<<(std::ostream& os, const Article& a);

    // Add operator== to compare Article objects by value
    bool operator==(const Article& other) const;
};

#endif // ARTICLE_H
