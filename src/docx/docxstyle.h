#ifndef DOCXSTYLE_H
#define DOCXSTYLE_H
#include "docx_global.h"
#include "itagelement.h"
#include "abstractooxmlfile.h"
#include "docxstyleheading.h"

#include <QVector>

namespace TDocx
{

class StyleTagElement;
class StyleTagIterator : public ITagIterator<ISaveToXml>
{
public:
    StyleTagIterator(const StyleTagElement *element);
    bool hasNext() const;
    ISaveToXml *next() const;
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
    void addChild(ISaveToXml *child);
    void remoevChild(ISaveToXml *child);
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
    QList<ISaveToXml*> m_childs;
    friend class StyleTagIterator;
};

class DOCX_EXPORT DocxStyle  : public AbstractOOXmlFile
{
public:
    DocxStyle(CreateFlag flag);

    virtual ~DocxStyle();

    virtual void saveToXmlFile(QIODevice *device) const;
    bool loadFromXmlFile(QIODevice *device);
    QVector<AbsHeading *> headingTags() const;
    void addHeadingStyle(AbsHeading *heading);
    AbsHeading *headbyLevel(HeadingLevel headLevel) const;

protected:
    void initTag();
    TagElement *m_docDefaultsTag;
    StyleTagElement* m_defParagraph;
    StyleTagElement* m_defCharacter;
    StyleTagElement* m_defTable;
    StyleTagElement* m_defnumbering;

    QVector<AbsHeading *> m_headingTags;

};
}

#endif // DOCXSTYLE_H
