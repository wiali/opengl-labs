#include "loader.h"
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <vector>

Loader::Loader()
{

}

void Loader::loadModel(QString fileName, std::vector<float> *vertices, std::vector<float> *textures, std::vector<float> *normals){
    QFile f( fileName );
    QString str;
    if (!f.open(QIODevice::ReadOnly)){
        return;
    }

    QTextStream stream(&f);

    std::vector<cordinate> verticesArray;
    std::vector<int>  verticesSequence;
    std::vector<cordinate> textureArray;
    std::vector<int> textureSequence;
    std::vector<cordinate> normalArray;
    std::vector<int> normalSequence;

    while( !stream.atEnd() ){
        str = stream.readLine();
        if ( str[0] == 'v' && str[1] == ' ' ){
            QList<QString> cords = str.split(" ");
            cordinate vertex;
            vertex.x = cords[1].toFloat();
            vertex.y = cords[2].toFloat();
            vertex.z = cords[3].toFloat();
            verticesArray.push_back(vertex);
        }
        if ( str[0] == 'v' && str[1] == 't' ){
            QList<QString> cords = str.split(" ");
            cordinate vertex;
            vertex.x = cords[1].toFloat();
            vertex.y = cords[2].toFloat();
            textureArray.push_back( vertex );
        }
        if ( str[0] == 'v' && str[1] == 'n' ){
            QList<QString> cords = str.split(" ");
            cordinate vertex;
            vertex.x = cords[1].toFloat();
            vertex.y = cords[2].toFloat();
            vertex.z = cords[3].toFloat();
            normalArray.push_back(vertex);
        }
        if (str[0] == 'f'){
            QList<QString> numbers = str.split( QRegExp( "(\\ |\\/)" ) );
            int i = 1;
            verticesSequence.push_back( numbers[i++].toShort() );
            textureSequence.push_back( numbers[i++].toShort() );
            if (normalArray.size()){
                normalSequence.push_back( numbers[i++].toShort() );
            }
            verticesSequence.push_back( numbers[i++].toShort() );
            textureSequence.push_back( numbers[i++].toShort() );
            if (normalArray.size()){
                normalSequence.push_back( numbers[i++].toShort() );
            }
            verticesSequence.push_back( numbers[i++].toShort() );
            textureSequence.push_back( numbers[i++].toShort() );
            if (normalArray.size()){
                normalSequence.push_back( numbers[i++].toShort() );
            }
        }
    }
    int size = verticesSequence.size();
    for (int i = 0; i < size; i++){
        int j = verticesSequence[i];
        vertices->push_back(verticesArray[j-1].x);
        vertices->push_back(verticesArray[j-1].y);
        vertices->push_back(verticesArray[j-1].z);
    }
    size = textureSequence.size();
    for (int i = 0; i < size; i++){
        int j = textureSequence[i];
        textures->push_back(textureArray[j-1].x);
        textures->push_back(textureArray[j-1].y);
    }
    size = normalSequence.size();
    for (int i = 0; i < size; i++){
        int j = normalSequence[i];
        normals->push_back(normalArray[j-1].x);
        normals->push_back(normalArray[j-1].y);
        normals->push_back(normalArray[j-1].z);
    }
}
