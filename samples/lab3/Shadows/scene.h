#ifndef SCENE_H
#define SCENE_H

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QMatrix4x4>
#include <vector>
#include <QTimer>
#include <camera.h>

class Scene : public QOpenGLWidget
{
    Q_OBJECT
private:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);
    QOpenGLShaderProgram program;
    int mvpUniform;
    int mUniform;
    int vertexAttr;
    int textureAttr;
    int normalAttr;
    int textureUniform;
    int cameraPosUniform;
    int pointUniform;
    int pointColorUniform;
    int pointAmbientUniform;
    int pointDiffuseUniform;
    int pointSpecularUniform;
    int materialSpecularFactorUniform;
    int materialEmissionUniform;
    QMatrix4x4 mMatrix;
    QMatrix4x4 pMatrix;
    std::vector<float> vertices;
    std::vector<float> textureCord;
    std::vector<float> normals;
    QOpenGLTexture* texture;
    QTimer timer;
    float hRot;
    QVector3D pointLightPos;
public:
    explicit Scene(QWidget *parent=0);
    ~Scene();
    Camera camera;
public slots:

};

#endif // SCENE_H
