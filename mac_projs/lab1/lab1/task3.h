//
//  task3.h
//  lab1
//
//  Created by Roman on 04.12.2017.
//  Copyright © 2017 Roman. All rights reserved.
//

#ifndef task3_h
#define task3_h


void drawTorus3(double r, double c, int rSeg, int cSeg)
{
    const double TAU = 2 * M_PI;
    for (int i = 0; i < rSeg; i++) {
        //        glBegin(GL_QUAD_STRIP);
        glBegin(GL_LINE_LOOP);
        for (int j = 0; j <= cSeg; j++) {
            for (int k = 0; k <= 1; k++) {
                double s = (i + k) % rSeg + 0.5;
                double t = j % (cSeg + 1);
                double x = (c + r * cos(s * TAU / rSeg)) * cos(t * TAU / cSeg);
                double y = (c + r * cos(s * TAU / rSeg)) * sin(t * TAU / cSeg);
                double z = r * sin(s * TAU / rSeg);
                double u = (i + k) / (float) rSeg;
                double v = t / (float) cSeg;
                //                glTexCoord2d(u, v);
                glNormal3f(2 * x, 2 * y, 2 * z);
                glVertex3d(2 * x, 2 * y, 2 * z);
            }
        }
        glEnd();
    }
}


void doTask3()
{
    
}

#endif /* task3_h */
