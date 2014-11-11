#include "docxnumbering.h"
#include <QString>
#include <QIODevice>

namespace TDocx
{
const QString str = R"~(<?xml version="1.0" encoding="UTF-8" standalone="yes"?>
        <w:numbering xmlns:wpc="http://schemas.microsoft.com/office/word/2010/wordprocessingCanvas" xmlns:mc="http://schemas.openxmlformats.org/markup-compatibility/2006" xmlns:o="urn:schemas-microsoft-com:office:office" xmlns:r="http://schemas.openxmlformats.org/officeDocument/2006/relationships" xmlns:m="http://schemas.openxmlformats.org/officeDocument/2006/math" xmlns:v="urn:schemas-microsoft-com:vml" xmlns:wp14="http://schemas.microsoft.com/office/word/2010/wordprocessingDrawing" xmlns:wp="http://schemas.openxmlformats.org/drawingml/2006/wordprocessingDrawing" xmlns:w10="urn:schemas-microsoft-com:office:word" xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main" xmlns:w14="http://schemas.microsoft.com/office/word/2010/wordml" xmlns:wpg="http://schemas.microsoft.com/office/word/2010/wordprocessingGroup" xmlns:wpi="http://schemas.microsoft.com/office/word/2010/wordprocessingInk" xmlns:wne="http://schemas.microsoft.com/office/word/2006/wordml" xmlns:wps="http://schemas.microsoft.com/office/word/2010/wordprocessingShape" mc:Ignorable="w14 wp14">
            <w:abstractNum w:abstractNumId="0">
                <w:nsid w:val="00000001"/>
                <w:multiLevelType w:val="hybridMultilevel"/>
                <w:tmpl w:val="00000001"/>
                <w:lvl w:ilvl="0" w:tplc="2AE2898A">
                    <w:start w:val="1"/>
                    <w:numFmt w:val="decimal"/>
                    <w:lvlText w:val="%1."/>
                    <w:lvlJc w:val="left"/>
                    <w:pPr>
                        <w:tabs>
                            <w:tab w:val="num" w:pos="720"/>
                        </w:tabs>
                        <w:ind w:left="720" w:hanging="360"/>
                    </w:pPr>
                </w:lvl>
                <w:lvl w:ilvl="1" w:tplc="EADCA2D0">
                    <w:start w:val="1"/>
                    <w:numFmt w:val="lowerLetter"/>
                    <w:lvlText w:val="%2."/>
                    <w:lvlJc w:val="left"/>
                    <w:pPr>
                        <w:tabs>
                            <w:tab w:val="num" w:pos="1440"/>
                        </w:tabs>
                        <w:ind w:left="1440" w:hanging="360"/>
                    </w:pPr>
                </w:lvl>
                <w:lvl w:ilvl="2" w:tplc="6F0EF170">
                    <w:start w:val="1"/>
                    <w:numFmt w:val="lowerRoman"/>
                    <w:lvlText w:val="%3."/>
                    <w:lvlJc w:val="right"/>
                    <w:pPr>
                        <w:tabs>
                            <w:tab w:val="num" w:pos="2160"/>
                        </w:tabs>
                        <w:ind w:left="2160" w:hanging="180"/>
                    </w:pPr>
                </w:lvl>
                <w:lvl w:ilvl="3" w:tplc="10BAF8E8">
                    <w:start w:val="1"/>
                    <w:numFmt w:val="decimal"/>
                    <w:lvlText w:val="%4."/>
                    <w:lvlJc w:val="left"/>
                    <w:pPr>
                        <w:tabs>
                            <w:tab w:val="num" w:pos="2880"/>
                        </w:tabs>
                        <w:ind w:left="2880" w:hanging="360"/>
                    </w:pPr>
                </w:lvl>
                <w:lvl w:ilvl="4" w:tplc="A3B00240">
                    <w:start w:val="1"/>
                    <w:numFmt w:val="lowerLetter"/>
                    <w:lvlText w:val="%5."/>
                    <w:lvlJc w:val="left"/>
                    <w:pPr>
                        <w:tabs>
                            <w:tab w:val="num" w:pos="3600"/>
                        </w:tabs>
                        <w:ind w:left="3600" w:hanging="360"/>
                    </w:pPr>
                </w:lvl>
                <w:lvl w:ilvl="5" w:tplc="D45C804A">
                    <w:start w:val="1"/>
                    <w:numFmt w:val="lowerRoman"/>
                    <w:lvlText w:val="%6."/>
                    <w:lvlJc w:val="right"/>
                    <w:pPr>
                        <w:tabs>
                            <w:tab w:val="num" w:pos="4320"/>
                        </w:tabs>
                        <w:ind w:left="4320" w:hanging="180"/>
                    </w:pPr>
                </w:lvl>
                <w:lvl w:ilvl="6" w:tplc="0A00F600">
                    <w:start w:val="1"/>
                    <w:numFmt w:val="decimal"/>
                    <w:lvlText w:val="%7."/>
                    <w:lvlJc w:val="left"/>
                    <w:pPr>
                        <w:tabs>
                            <w:tab w:val="num" w:pos="5040"/>
                        </w:tabs>
                        <w:ind w:left="5040" w:hanging="360"/>
                    </w:pPr>
                </w:lvl>
                <w:lvl w:ilvl="7" w:tplc="13F87EFC">
                    <w:start w:val="1"/>
                    <w:numFmt w:val="lowerLetter"/>
                    <w:lvlText w:val="%8."/>
                    <w:lvlJc w:val="left"/>
                    <w:pPr>
                        <w:tabs>
                            <w:tab w:val="num" w:pos="5760"/>
                        </w:tabs>
                        <w:ind w:left="5760" w:hanging="360"/>
                    </w:pPr>
                </w:lvl>
                <w:lvl w:ilvl="8" w:tplc="322AE160">
                    <w:start w:val="1"/>
                    <w:numFmt w:val="lowerRoman"/>
                    <w:lvlText w:val="%9."/>
                    <w:lvlJc w:val="right"/>
                    <w:pPr>
                        <w:tabs>
                            <w:tab w:val="num" w:pos="6480"/>
                        </w:tabs>
                        <w:ind w:left="6480" w:hanging="180"/>
                    </w:pPr>
                </w:lvl>
            </w:abstractNum>
            <w:abstractNum w:abstractNumId="1">
                <w:nsid w:val="00000002"/>
                <w:multiLevelType w:val="hybridMultilevel"/>
                <w:tmpl w:val="6AFEEA0E"/>
                <w:lvl w:ilvl="0" w:tplc="04090001">
                    <w:start w:val="1"/>
                    <w:numFmt w:val="bullet"/>
                    <w:lvlJc w:val="left"/>
                    <w:pPr>
                        <w:tabs>
                            <w:tab w:val="num" w:pos="720"/>
                        </w:tabs>
                        <w:ind w:left="720" w:hanging="360"/>
                    </w:pPr>
                    <w:rPr>
                        <w:rFonts w:ascii="Wingdings" w:hAnsi="Wingdings" w:hint="default"/>
                    </w:rPr>
                </w:lvl>
                <w:lvl w:ilvl="1" w:tplc="F3F82C8C">
                    <w:start w:val="1"/>
                    <w:numFmt w:val="bullet"/>
                    <w:lvlText w:val="o"/>
                    <w:lvlJc w:val="left"/>
                    <w:pPr>
                        <w:tabs>
                            <w:tab w:val="num" w:pos="1440"/>
                        </w:tabs>
                        <w:ind w:left="1440" w:hanging="360"/>
                    </w:pPr>
                    <w:rPr>
                        <w:rFonts w:ascii="Courier New" w:hAnsi="Courier New"/>
                    </w:rPr>
                </w:lvl>
                <w:lvl w:ilvl="2" w:tplc="79120E82">
                    <w:start w:val="1"/>
                    <w:numFmt w:val="bullet"/>
                    <w:lvlText w:val=" "/>
                    <w:lvlJc w:val="left"/>
                    <w:pPr>
                        <w:tabs>
                            <w:tab w:val="num" w:pos="2160"/>
                        </w:tabs>
                        <w:ind w:left="2160" w:hanging="360"/>
                    </w:pPr>
                    <w:rPr>
                        <w:rFonts w:ascii="Wingdings" w:hAnsi="Wingdings"/>
                    </w:rPr>
                </w:lvl>
                <w:lvl w:ilvl="3" w:tplc="D0501E12">
                    <w:start w:val="1"/>
                    <w:numFmt w:val="bullet"/>
                    <w:lvlText w:val=" "/>
                    <w:lvlJc w:val="left"/>
                    <w:pPr>
                        <w:tabs>
                            <w:tab w:val="num" w:pos="2880"/>
                        </w:tabs>
                        <w:ind w:left="2880" w:hanging="360"/>
                    </w:pPr>
                    <w:rPr>
                        <w:rFonts w:ascii="Symbol" w:hAnsi="Symbol"/>
                    </w:rPr>
                </w:lvl>
                <w:lvl w:ilvl="4" w:tplc="024A253E">
                    <w:start w:val="1"/>
                    <w:numFmt w:val="bullet"/>
                    <w:lvlText w:val="o"/>
                    <w:lvlJc w:val="left"/>
                    <w:pPr>
                        <w:tabs>
                            <w:tab w:val="num" w:pos="3600"/>
                        </w:tabs>
                        <w:ind w:left="3600" w:hanging="360"/>
                    </w:pPr>
                    <w:rPr>
                        <w:rFonts w:ascii="Courier New" w:hAnsi="Courier New"/>
                    </w:rPr>
                </w:lvl>
                <w:lvl w:ilvl="5" w:tplc="48160AFC">
                    <w:start w:val="1"/>
                    <w:numFmt w:val="bullet"/>
                    <w:lvlText w:val=" "/>
                    <w:lvlJc w:val="left"/>
                    <w:pPr>
                        <w:tabs>
                            <w:tab w:val="num" w:pos="4320"/>
                        </w:tabs>
                        <w:ind w:left="4320" w:hanging="360"/>
                    </w:pPr>
                    <w:rPr>
                        <w:rFonts w:ascii="Wingdings" w:hAnsi="Wingdings"/>
                    </w:rPr>
                </w:lvl>
                <w:lvl w:ilvl="6" w:tplc="B9687AA0">
                    <w:start w:val="1"/>
                    <w:numFmt w:val="bullet"/>
                    <w:lvlText w:val=" "/>
                    <w:lvlJc w:val="left"/>
                    <w:pPr>
                        <w:tabs>
                            <w:tab w:val="num" w:pos="5040"/>
                        </w:tabs>
                        <w:ind w:left="5040" w:hanging="360"/>
                    </w:pPr>
                    <w:rPr>
                        <w:rFonts w:ascii="Symbol" w:hAnsi="Symbol"/>
                    </w:rPr>
                </w:lvl>
                <w:lvl w:ilvl="7" w:tplc="C50042D8">
                    <w:start w:val="1"/>
                    <w:numFmt w:val="bullet"/>
                    <w:lvlText w:val="o"/>
                    <w:lvlJc w:val="left"/>
                    <w:pPr>
                        <w:tabs>
                            <w:tab w:val="num" w:pos="5760"/>
                        </w:tabs>
                        <w:ind w:left="5760" w:hanging="360"/>
                    </w:pPr>
                    <w:rPr>
                        <w:rFonts w:ascii="Courier New" w:hAnsi="Courier New"/>
                    </w:rPr>
                </w:lvl>
                <w:lvl w:ilvl="8" w:tplc="D17AD084">
                    <w:start w:val="1"/>
                    <w:numFmt w:val="bullet"/>
                    <w:lvlText w:val=" "/>
                    <w:lvlJc w:val="left"/>
                    <w:pPr>
                        <w:tabs>
                            <w:tab w:val="num" w:pos="6480"/>
                        </w:tabs>
                        <w:ind w:left="6480" w:hanging="360"/>
                    </w:pPr>
                    <w:rPr>
                        <w:rFonts w:ascii="Wingdings" w:hAnsi="Wingdings"/>
                    </w:rPr>
                </w:lvl>
            </w:abstractNum>
            <w:num w:numId="1">
                <w:abstractNumId w:val="0"/>
            </w:num>
            <w:num w:numId="2">
                <w:abstractNumId w:val="1"/>
            </w:num>
        </w:numbering>
)~";

DocxNumbering::DocxNumbering(CreateFlag flag)
    : AbstractOOXmlFile(flag)
{
}

void DocxNumbering::saveToXmlFile(QIODevice *device) const
{
    if (m_data.isEmpty())
        device->write(str.toUtf8());
    else
        device->write(m_data);
}

bool DocxNumbering::loadFromXmlFile(QIODevice *device)
{
    m_data = device->readAll();
    return true;
}

}



