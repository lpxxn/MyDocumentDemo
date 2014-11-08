#ifndef DOCXSTYLE_H
#define DOCXSTYLE_H
#include "docx_global.h"
#include "itagelement.h"
#include "abstractooxmlfile.h"

#include <QVector>

namespace TDocx
{

enum class Headerings
{
    header1,
    header2,
    header3,
    header4,
    header5,
    header6,
    header7,
    header8,
    header9
};

class StyleTagElement;
class StyleTagIterator : public ITagIterator<ITagElement>
{
public:
    StyleTagIterator(const StyleTagElement *element);
    bool hasNext() const;
    ITagElement *next() const;
private:
    const StyleTagElement *m_tagElement;
    mutable int m_currentIndex;
};

enum class StyleType {
    paragraph,
    table,
    character,
    numbering
};

class StyleTagElement : public ITagElement
{
public:


    StyleTagElement(StyleType type, const QString &styleId);
    void addProperty(QString name, QString value);
    void addChild(ITagElement *child);
    void remoevChild(ITagElement *child);
    void saveToXmlElement(QXmlStreamWriter *writer) const;
    StyleTagIterator createIterator() const;

    virtual ~StyleTagElement();

private:
    QString convertType(StyleType type) const;

private:
    StyleType m_type;
    QString m_styleId;
    typedef QPair<QString, QString> pairValue;
    QVector<pairValue> m_properties;
    QList<ITagElement*> m_childs;
    friend class StyleTagIterator;
};

class DOCX_EXPORT DocxStyle  : public AbstractOOXmlFile
{
public:
    DocxStyle(CreateFlag flag);

    virtual void saveToXmlFile(QIODevice *device) const;
    bool loadFromXmlFile(QIODevice *device);


    QVector<StyleTagElement *> headingTags() const;
    void addHeadingStyle();

protected:
    void initTag();
    TagElement *m_docDefaultsTag;
    StyleTagElement* m_defParagraph;
    StyleTagElement* m_defCharacter;
    StyleTagElement* m_defTable;
    StyleTagElement* m_defnumbering;

    QVector<StyleTagElement*> m_headingTags;

};
}

#endif // DOCXSTYLE_H
