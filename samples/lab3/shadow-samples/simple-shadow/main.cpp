#ifdef __APPLE__
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
    #include <GLUT/glut.h>
#else
    #include <GL/gl.h>
    #include <GL/glu.h>
    #include <GL/glut.h>
#endif


constexpr float light_position_X = 0;
constexpr float light_position_Y = 1.5;
constexpr float light_position_Z = 0;


void display();
void idle();


int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
    glutInitWindowSize(600, 600);
    glutCreateWindow("simple-shadow");

    // init
    glClearColor(0.0, 0.0, 0.0, 1.0);

    glShadeModel(GL_SMOOTH);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1, 0.001, 100.0);
    gluLookAt(
        0,  2,  -5,
        0,  0,   0,
        0,  1,   0
    );

    constexpr float ligth_position[] =  {light_position_X, light_position_Y, light_position_Z, 1};
    constexpr float light_ambient[] =   { .35, .35, .35, 1 };
    constexpr float light_diffuse[] =   { .65, .65, .80, 1 };
    constexpr float light_specular[] =  { .50, .50, .50, 1 };
    glLightfv(GL_LIGHT1, GL_POSITION, ligth_position);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);

    // refresh
    glutDisplayFunc(display);
    glutIdleFunc(idle);

    // looping
    glutMainLoop();
    return 0;
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT1);
    glDepthMask(GL_TRUE);
    glCullFace(GL_FRONT);

    // draw plane
    glBegin(GL_QUADS);
        glVertex3f(-2, -.5,  2);
        glVertex3f(-2, -.5, -2);
        glVertex3f( 2, -.5, -2);
        glVertex3f( 2, -.5,  2);
    glEnd();

    // draw triangle
    float vert[][3] = {
        {-0.5,  .5,  -1},
        { 0.5,  .5,  -1},
        {   0,  .5,   0.732}
    };

    glBegin(GL_TRIANGLES);
    for(auto v : vert) {
        glVertex3fv(v);
    }
    glEnd();

    // shadow volum
    float to[3][3];
    for (int i=0; i<3; i++) {
        to[i][0] = (vert[i][0] - light_position_X) *10;
        to[i][1] = (vert[i][1] - light_position_Y) *10;
        to[i][2] = (vert[i][2] - light_position_Z) *10;
    }

    auto drawFace = [&](int i) -> void {
        glBegin(GL_QUADS);
            glVertex3fv(vert[i]);
            glVertex3fv(to[i]);
            glVertex3fv(to[(i+1)%3]);
            glVertex3fv(vert[(i+1)%3]);
        glEnd();
    };

    // start draw shadow
    glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
    glDepthMask(GL_FALSE);

    glEnable(GL_STENCIL_TEST);

    // front
    glCullFace(GL_FRONT);
    glStencilFunc(GL_ALWAYS, 0x0, 0xff);
    glStencilOp(GL_KEEP, GL_KEEP, GL_INCR);
    drawFace(0);
    drawFace(1);
    drawFace(2);

    // back
    glCullFace(GL_BACK);
    glStencilFunc(GL_ALWAYS, 0x0, 0xff);
    glStencilOp(GL_KEEP, GL_KEEP, GL_DECR_WRAP);
    drawFace(0);
    drawFace(1);
    drawFace(2);

    // recover settings
    glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
    glDepthMask(GL_TRUE);

    // draw shadow
    glStencilFunc(GL_EQUAL, 0x1, 0xff);
    glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);

    glPushAttrib(GL_CURRENT_BIT);
    glPushMatrix();
        // glLoadIdentity();
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
            // glEnable(GL_LIGHTING);
            glCullFace(GL_FRONT);
            glLoadIdentity();
            glOrtho(0, 1, 1, 0, 0, 1);

            glDisable(GL_DEPTH_TEST);
            glDisable(GL_LIGHTING);
            glColor4f(.1, .1, .15, .1);
            glBegin(GL_QUADS);
                glVertex2i(0, 0);
                glVertex2i(1, 0);
                glVertex2i(1, 1);
                glVertex2i(0, 1);
            glEnd();

            glEnable(GL_DEPTH_TEST);
        glPopMatrix();

        glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glPopAttrib();

    glDisable(GL_STENCIL_TEST);

    // draw light source
    glDepthMask(GL_FALSE);
    glDisable(GL_LIGHTING);

    glPushAttrib(GL_CURRENT_BIT);
    glPushMatrix();
        glColor3f(1.0, 1.0, 0);
        glTranslated(light_position_X, light_position_Y, light_position_Z);
        glutSolidSphere(.01, 4, 4);
    glPopMatrix();
    glPopAttrib();

    glutSwapBuffers();
}


void idle() {
	glutPostRedisplay();
}
