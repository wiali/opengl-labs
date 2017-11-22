#include "openglviewer.h"

#include <QtWidgets/qdialog.h>

#include "common.h"
#include "glutils.h"

static const int SHADOWMAP_SIZE = 512;
static const int nSamples = 64;
static const float sampleRadius = 0.5f;
static const QVector3D lightPos = QVector3D(0.0f, 9.0f, 0.0f);

QVector3D axes[6] = {
    QVector3D(-1.0f,  0.0f,  0.0f),
    QVector3D( 1.0f,  0.0f,  0.0f),
    QVector3D( 0.0f, -1.0f,  0.0f),
    QVector3D( 0.0f,  1.0f,  0.0f),
    QVector3D( 0.0f,  0.0f, -1.0f),
    QVector3D( 0.0f,  0.0f,  1.0f)
};

OpenGLViewer::OpenGLViewer(QWidget *parent)
    : QOpenGLWidget(parent)
    , QOpenGLFunctions() {
    vao = new VertexArray();
    camera = new ArcballCamera(this);
}

OpenGLViewer::~OpenGLViewer() {
    delete vao;
    delete camera;
}

void OpenGLViewer::initializeGL() {
    initializeOpenGLFunctions();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    vao->load(std::string(DATA_DIRECTORY) + "cbox.ply");
    
    shader = compileShader(std::string(SOURCE_DIRECTORY) + "shaders/render");
    rsmShader = compileShader(std::string(SOURCE_DIRECTORY) + "shaders/rsm", true);
    
    camera->setLookAt(QVector3D(0.0f, 5.0f, 15.0f), QVector3D(0.0f, 5.0f, 0.0f), QVector3D(0.0f, 1.0f, 0.0f));

    randTexture = std::make_unique<QOpenGLTexture>(QOpenGLTexture::Target1D);
    randTexture->create();
    randTexture->setSize(nSamples * 2);
    randTexture->setFormat(QOpenGLTexture::TextureFormat::R32F);
    randTexture->allocateStorage();
    
    std::vector<float> randValues(nSamples * 2);
    srand((unsigned long)time(0));
    for (int i = 0; i < nSamples * 2; i++) {
        randValues[i] = rand() / (float)RAND_MAX;
    }

    randTexture->setData(0, 0, QOpenGLTexture::Red, QOpenGLTexture::Float32, &randValues[0], 0);
    
    cubeViewMat.resize(6);
    for (int i = 0; i < 6; i++) {
        QVector3D center = lightPos + axes[i];
        QVector3D up(0.0f, 1.0f, 0.0f);
        if (QVector3D::crossProduct(axes[i], up).length() < 0.01f) {
            up = QVector3D(1.0f, 0.0f, 0.0f);
        }
        cubeViewMat[i].lookAt(lightPos, center, up);
    }
}

void OpenGLViewer::paintGL() {
    // Shadow mapping
    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);

    glViewport(0, 0, SHADOWMAP_SIZE * 4, SHADOWMAP_SIZE * 3);

    rsmShader->bind();
    rsmFbo->bind();
    
    QMatrix4x4 pMat, mvMat;
    pMat.ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.01f, 10.0f);
    QMatrix4x4 mvpMat = pMat * mvMat;
    
    auto f = QOpenGLContext::currentContext()->extraFunctions();
    GLenum bufs[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1,
                      GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
    f->glDrawBuffers(4, bufs);

    rsmShader->setUniformValue("u_projMat", pMat);
    rsmShader->setUniformValueArray("u_mvMat", &cubeViewMat[0], 6);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    float white[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    f->glClearBufferfv(GL_COLOR, 0, white);
    
    vao->draw(*rsmShader);
    
    rsmShader->release();
    rsmFbo->release();
    
    rsmFbo->toImage(true, 0).save(QString(OUTPUT_DIRECTORY) + "depth.png");
    rsmFbo->toImage(true, 1).save(QString(OUTPUT_DIRECTORY) + "position.png");
    rsmFbo->toImage(true, 2).save(QString(OUTPUT_DIRECTORY) + "normal.png");
    rsmFbo->toImage(true, 3).save(QString(OUTPUT_DIRECTORY) + "diffuse.png");
    
    // Rendering
    glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader->bind();
    
    QVector<GLuint> textures = rsmFbo->textures();
    for (int i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        glBindTexture(GL_TEXTURE_2D, textures[i]);
    }
    
    shader->setUniformValue("u_mvMat", camera->mvMat());
    shader->setUniformValue("u_mvpMat", camera->mvpMat());
    shader->setUniformValue("u_lightPos", lightPos);
    
    shader->setUniformValue("u_depthMap", 0);
    shader->setUniformValue("u_positionMap", 1);
    shader->setUniformValue("u_normalMap", 2);
    shader->setUniformValue("u_diffuseMap", 3);
    
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_1D, randTexture->textureId());
    shader->setUniformValue("u_randMap", 4);
    
    shader->setUniformValue("u_lightMvpMat", mvpMat);
    shader->setUniformValue("u_nSamples", nSamples);
    shader->setUniformValue("u_sampleRadius", sampleRadius);

    vao->draw(*shader);
    
    shader->release();
}

void OpenGLViewer::resizeGL(int w, int h) {
    glViewport(0, 0, width(), height());

    camera->setPerspective(45.0f, (float)width() / (float)height(), 0.1f, 100.0f);
    
    rsmFbo = std::make_unique<QOpenGLFramebufferObject>(
        SHADOWMAP_SIZE * 4, SHADOWMAP_SIZE * 3,
        QOpenGLFramebufferObject::Attachment::Depth,
        GL_TEXTURE_2D, GL_RGBA32F
    );
    rsmFbo->addColorAttachment(SHADOWMAP_SIZE * 4, SHADOWMAP_SIZE * 3);
    rsmFbo->addColorAttachment(SHADOWMAP_SIZE * 4, SHADOWMAP_SIZE * 3);
    rsmFbo->addColorAttachment(SHADOWMAP_SIZE * 4, SHADOWMAP_SIZE * 3);
}

void OpenGLViewer::mousePressEvent(QMouseEvent *ev) {
    camera->mousePressEvent(ev);
}

void OpenGLViewer::mouseMoveEvent(QMouseEvent *ev) {
    camera->mouseMoveEvent(ev);
}

void OpenGLViewer::mouseReleaseEvent(QMouseEvent *ev) {
    camera->mouseReleaseEvent(ev);
}

void OpenGLViewer::wheelEvent(QWheelEvent *ev) {
    camera->wheelEvent(ev);
}
