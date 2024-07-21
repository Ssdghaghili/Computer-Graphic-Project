// #include <GL/glut.h>
// #include <cmath>

// // Function to draw a wheel
// void drawWheel(float radius, float width) {
//     const int numSegments = 36;
//     glBegin(GL_QUAD_STRIP);
//     for (int i = 0; i <= numSegments; ++i) {
//         float angle = 2.0f * M_PI * i / numSegments;
//         float x = radius * cos(angle);
//         float y = radius * sin(angle);
//         glVertex3f(x, y, width / 2);
//         glVertex3f(x, y, -width / 2);
//     }
//     glEnd();
// }

// // Function to draw the bicycle frame
// void drawFrame() {
//     glBegin(GL_LINES);

//     // Main triangle
//     glVertex3f(0.0f, 0.0f, 0.0f); // Bottom bracket
//     glVertex3f(1.0f, 1.0f, 0.0f); // Top of seat tube

//     glVertex3f(1.0f, 1.0f, 0.0f); // Top of seat tube
//     glVertex3f(3.0f, 1.0f, 0.0f); // Top of head tube

//     glVertex3f(3.0f, 1.0f, 0.0f); // Top of head tube
//     glVertex3f(0.0f, 0.0f, 0.0f); // Bottom bracket

//     // Seat stay
//     glVertex3f(1.0f, 1.0f, 0.0f); // Top of seat tube
//     glVertex3f(0.0f, 0.0f, 0.0f); // Bottom bracket

//     // Chain stay
//     glVertex3f(0.0f, 0.0f, 0.0f); // Bottom bracket
//     glVertex3f(-1.0f, 0.0f, 0.0f); // Rear dropout

//     // Front fork
//     glVertex3f(3.0f, 1.0f, 0.0f); // Top of head tube
//     glVertex3f(4.0f, 0.0f, 0.0f); // Front dropout

//     glEnd();
// }

// // Display callback function
// void display() {
//     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//     glLoadIdentity();

//     // Camera setup
//     gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

//     glColor3f(1.0f, 0.0f, 0.0f);

//     // Draw the wheels
//     glPushMatrix();
//     glTranslatef(-1.0f, 0.0f, 0.0f);
//     drawWheel(1.0f, 0.2f);
//     glPopMatrix();

//     glPushMatrix();
//     glTranslatef(4.0f, 0.0f, 0.0f);
//     drawWheel(1.0f, 0.2f);
//     glPopMatrix();

//     // Draw the frame
//     drawFrame();

//     glutSwapBuffers();
// }

// // Reshape callback function
// void reshape(int w, int h) {
//     glViewport(0, 0, w, h);
//     glMatrixMode(GL_PROJECTION);
//     glLoadIdentity();
//     gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
//     glMatrixMode(GL_MODELVIEW);
// }

// // Main function
// int main(int argc, char** argv) {
//     glutInit(&argc, argv);
//     glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
//     glutInitWindowSize(800, 600);
//     glutCreateWindow("3D Bicycle");

//     glEnable(GL_DEPTH_TEST);

//     glutDisplayFunc(display);
//     glutReshapeFunc(reshape);

//     glutMainLoop();
//     return 0;
// }