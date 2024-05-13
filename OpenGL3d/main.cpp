#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>
#include <cmath>


#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float PI = 3.14159265358979323846;

GLfloat doorAngle = 0.0f; // Angle of the door
GLfloat windowAngle = 0.0f; // Angle of the windows
bool isDoorOpening = false, isDoorClosing = false, isDoorOpen = false;
bool isWindowOpening = false, isWindowClosing = false, isWindowOpen = false;
bool move = false;



// takes 3 points the left bottom (x,y,z) 
void drawWindows(GLfloat x, GLfloat y, GLfloat z) {
	glBegin(GL_QUADS);
	glColor3f(0.0f, 0.5f, 0.5f); // Dark cyan color
	glVertex3f(x, y, z);
	glVertex3f(x + 0.5, y, z);
	glVertex3f(x + 0.5, y + 1, z);
	glVertex3f(x, y + 1, z);

	// add depth to the windows to inside the building
	// color gray
	glColor3f(0.6, 0.6, 0.6);
	glVertex3f(x, y, z - 0.1);
	glVertex3f(x + 0.5, y, z - 0.1);
	glVertex3f(x + 0.5, y + 1, z - 0.1);
	glVertex3f(x, y + 1, z - 0.1);

	// fill the space between the 2 quads to make the window look solid
	glVertex3f(x + 0.5, y, z);
	glVertex3f(x + 0.5, y, z - 0.1);
	glVertex3f(x + 0.5, y + 1, z - 0.1);
	glVertex3f(x + 0.5, y + 1, z);

	glVertex3f(x, y + 1, z);
	glVertex3f(x + 0.5, y + 1, z);
	glVertex3f(x + 0.5, y + 1, z - 0.1);
	glVertex3f(x, y + 1, z - 0.1);

	glVertex3f(x, y, z);
	glVertex3f(x, y, z - 0.1);
	glVertex3f(x, y + 1, z - 0.1);
	glVertex3f(x, y + 1, z);

	glVertex3f(x, y, z);
	glVertex3f(x + 0.5, y, z);
	glVertex3f(x + 0.5, y, z - 0.1);
	glVertex3f(x, y, z - 0.1);



	glEnd();
}


void drawDoor() {
	glPushMatrix(); // Save the current matrix state
	glTranslatef(-0.5, 0.0, 3.01); // Translate the door to its original position
	glRotatef(doorAngle, 0, 1, 0); // Rotate the door around the y-axis
	glTranslated(0.5, 0.0, -3.01); // Translate the door back to its position
	glBegin(GL_QUADS);
	glColor3f(0.3, 0.2, 0.1); // Dark brown for the door
	glVertex3f(-0.5, 0.0, 3.01);
	glVertex3f(0.5, 0.0, 3.01);
	glVertex3f(0.5, 1.8, 3.01);
	glVertex3f(-0.5, 1.8, 3.01);
	// add depth to the door to inside the building
	// color gray
	glColor3f(0.6, 0.6, 0.6);
	glVertex3f(-0.5, 0.0, 2.9);
	glVertex3f(0.5, 0.0, 2.9);
	glVertex3f(0.5, 1.8, 2.9);
	glVertex3f(-0.5, 1.8, 2.9);

	// fill the space between the 2 quads to make the door look solid
	glVertex3f(-0.5, 0.0, 3.01);
	glVertex3f(-0.5, 0.0, 2.9);
	glVertex3f(-0.5, 1.8, 2.9);
	glVertex3f(-0.5, 1.8, 3.01);

	glVertex3f(0.5, 0.0, 3.01);
	glVertex3f(0.5, 0.0, 2.9);
	glVertex3f(0.5, 1.8, 2.9);
	glVertex3f(0.5, 1.8, 3.01);
	// the upper part of the door
	glVertex3f(-0.5, 1.8, 3.01);
	glVertex3f(0.5, 1.8, 3.01);
	glVertex3f(0.5, 1.8, 2.9);
	glVertex3f(-0.5, 1.8, 2.9);

	// make a handle for the door like a knob
	glColor3f(1.0f, 1.0f, 0.0f); // Yellow color
	glVertex3f(0.4, 0.6, 3.02);
	glVertex3f(0.5, 0.6, 3.02);
	glVertex3f(0.5, 0.7, 3.02);
	glVertex3f(0.4, 0.7, 3.02);
	glEnd();
	glPopMatrix(); // Restore the previous matrix state
}


void drawWalls() {
	glBegin(GL_QUADS);
	// front
	// plane for the first floor with color off white
	
	glColor3f(0.7f, 0.7f, 0.7f);
	glVertex3f(-3.0, 0.1, 3.0);
	glVertex3f(3.0, 0.1, 3.0);
	glVertex3f(3.0, 0.1, -3.0);
	glVertex3f(-3.0, 0.1, -3.0);

	// dark grey color for the wall
	glColor3f(0.3f, 0.3f, 0.3f);
	// this exclueds the windows for the first floor
	glVertex3f(-3.0, 0.0, 3.0); 
	glVertex3f(-2, 0.0, 3.0);
	glVertex3f(-2, 3.0, 3.0);
	glVertex3f(-3.0, 3.0, 3.0);

	glVertex3f(2, 0.0, 3.0);
	glVertex3f(3.0, 0.0, 3.0);
	glVertex3f(3.0, 3.0, 3.0);
	glVertex3f(2, 3.0, 3.0);

	glVertex3f(-1, 0.0, 3.0);
	glVertex3f(-0.5, 0.0, 3.0);
	glVertex3f(-0.5, 3.0, 3.0);
	glVertex3f(-1, 3.0, 3.0);

	glVertex3f(0.5, 0.0, 3.0);
	glVertex3f(1, 0.0, 3.0);
	glVertex3f(1, 3.0, 3.0);
	glVertex3f(0.5, 3.0, 3.0);

	// filling top of the door 
	glVertex3f(-0.5, 1.8, 3.0);
	glVertex3f(0.5, 1.8, 3.0);
	glVertex3f(0.5, 3.0, 3.0);
	glVertex3f(-0.5, 3.0, 3.0);

	// filling top of the windows
	glVertex3f(-2, 2.2 , 3.0);
	glVertex3f(-1, 2.2, 3.0);
	glVertex3f(-1, 3.0, 3.0);
	glVertex3f(-2, 3.0, 3.0);
	

	glVertex3f(1, 2.2, 3.0);
	glVertex3f(2, 2.2, 3.0);
	glVertex3f(2, 3.0, 3.0);
	glVertex3f(1, 3.0, 3.0);

	// filling under the windows
	glVertex3f(-2, 0.0, 3.0);
	glVertex3f(-1, 0.0, 3.0);
	glVertex3f(-1, 1.2, 3.0);
	glVertex3f(-2, 1.2, 3.0);

	glVertex3f(1, 0.0, 3.0);
	glVertex3f(2, 0.0, 3.0);
	glVertex3f(2, 1.2, 3.0);
	glVertex3f(1, 1.2, 3.0);



	// right
	glVertex3f(3.0, 0.0, -3.0);
	glVertex3f(3.0, 0.0, 3.0);
	glVertex3f(3.0, 3.0, 3.0);
	glVertex3f(3.0, 3.0, -3.0);
	// left
	glVertex3f(-3.0, 0.0, -3.0);
	glVertex3f(-3.0, 0.0, 3.0);
	glVertex3f(-3.0, 3.0, 3.0);
	glVertex3f(-3.0, 3.0, -3.0);
	// back
	glVertex3f(-3.0, 0.0, -3.0);
	glVertex3f(3.0, 0.0, -3.0);
	glVertex3f(3.0, 3.0, -3.0);
	glVertex3f(-3.0, 3.0, -3.0);

	// Second floor
	// front
	// draw the second floor with color off white
	glColor3f(0.7f, 0.7f, 0.7f);
	glVertex3f(-3.0, 3.1, 3.0);
	glVertex3f(3.0, 3.1, 3.0);
	glVertex3f(3.0, 3.1, -3.0);
	glVertex3f(-3.0, 3.1, -3.0);

	// exclude the windows for the second floor
	glColor3f(0.3f, 0.3f, 0.3f);
	glVertex3f(-3.0, 3.1, 3.0);
	glVertex3f(-2, 3.1, 3.0);
	glVertex3f(-2, 6.1, 3.0);
	glVertex3f(-3.0, 6.1, 3.0);

	glVertex3f(2, 3.1, 3.0);
	glVertex3f(3.0, 3.1, 3.0);
	glVertex3f(3.0, 6.1, 3.0);
	glVertex3f(2, 6.1, 3.0);

	// filling between the windows
	glVertex3f(-1, 3.1, 3.0);
	glVertex3f(1, 3.1, 3.0);
	glVertex3f(1, 6.1, 3.0);
	glVertex3f(-1, 6.1, 3.0);

	// filling the top of the windows
	glVertex3f(-2, 5.2, 3.0);
	glVertex3f(-1, 5.2, 3.0);
	glVertex3f(-1, 6.1, 3.0);
	glVertex3f(-2, 6.1, 3.0);

	glVertex3f(1, 5.2, 3.0);
	glVertex3f(2, 5.2, 3.0);
	glVertex3f(2, 6.1, 3.0);
	glVertex3f(1, 6.1, 3.0);

	// filling the bottom of the windows
	glVertex3f(-2, 3.1, 3.0);
	glVertex3f(-1, 3.1, 3.0);
	glVertex3f(-1, 4.2, 3.0);
	glVertex3f(-2, 4.2, 3.0);

	glVertex3f(1, 3.1, 3.0);
	glVertex3f(2, 3.1, 3.0);
	glVertex3f(2, 4.2, 3.0);
	glVertex3f(1, 4.2, 3.0);

	// right
	glVertex3f(3.0, 3.1, -3.0);
	glVertex3f(3.0, 3.1, 3.0);
	glVertex3f(3.0, 6.1, 3.0);
	glVertex3f(3.0, 6.1, -3.0);
	// left
	glVertex3f(-3.0, 3.1, -3.0);
	glVertex3f(-3.0, 3.1, 3.0);
	glVertex3f(-3.0, 6.1, 3.0);
	glVertex3f(-3.0, 6.1, -3.0);
	// back
	glVertex3f(-3.0, 3.1, -3.0);
	glVertex3f(3.0, 3.1, -3.0);
	glVertex3f(3.0, 6.1, -3.0);
	glVertex3f(-3.0, 6.1, -3.0);
	glEnd();
	// Roof is a Tetrahedron pyramid
	glBegin(GL_TRIANGLES);
	glColor3f(0.5f, 0.0f, 0.0f); // dark red color

	// front
	glVertex3f(-3.0, 6.1, 3.0);
	glVertex3f(3.0, 6.1, 3.0);
	glVertex3f(0.0, 8.0, 0.0);

	// back
	glVertex3f(-3.0, 6.1, -3.0);
	glVertex3f(3.0, 6.1, -3.0);
	glVertex3f(0.0, 8.0, 0.0);

	// right
	glVertex3f(3.0, 6.1, 3.0);
	glVertex3f(3.0, 6.1, -3.0);
	glVertex3f(0.0, 8.0, 0.0);

	// left
	glVertex3f(-3.0, 6.1, 3.0);
	glVertex3f(-3.0, 6.1, -3.0);
	glVertex3f(0.0, 8.0, 0.0);
	glEnd();

	// fill the space between the first and second floor
	glBegin(GL_QUADS);
	glColor3f(0, 0, 0); // black color
	glVertex3f(-3.0, 3.0, 3.0);
	glVertex3f(3.0, 3.0, 3.0);
	glVertex3f(3.0, 3.1, 3.0);
	glVertex3f(-3.0, 3.1, 3.0);

	glVertex3f(3.0, 3.0, 3.0);
	glVertex3f(3.0, 3.0, -3.0);
	glVertex3f(3.0, 3.1, -3.0);
	glVertex3f(3.0, 3.1, 3.0);

	glVertex3f(-3.0, 3.0, -3.0);
	glVertex3f(-3.0, 3.0, 3.0);
	glVertex3f(-3.0, 3.1, 3.0);
	glVertex3f(-3.0, 3.1, -3.0);

	glVertex3f(-3.0, 3.0, -3.0);
	glVertex3f(3.0, 3.0, -3.0);
	glVertex3f(3.0, 3.1, -3.0);
	glVertex3f(-3.0, 3.1, -3.0);
	glEnd();
}

// draw a building
void drawBuilding() {
	// draw the walls
	drawWalls();

	//left windows
	glPushMatrix();
	glTranslatef(-2.0, 1.2, 3.01); // Translate to the first floor left window position
	glRotatef(windowAngle, 0, 1, 0); // Rotate the window around the y-axis
	glTranslatef(2.0, -1.2, -3.01); // Translate back to the original position
	drawWindows(-2, 1.2, 3.01); // first floor left window
	drawWindows(-2, 4.2, 3.01); // second floor left window
	glPopMatrix();

	glPushMatrix();
	glTranslated(1.0, 1.2, 3.01); // Translate to the first floor right window position
	glRotatef(windowAngle, 0, 1, 0); // Rotate the window around the y-axis
	glTranslated(-1.0, -1.2, -3.01); // Translate back to the original position
	drawWindows(1, 1.2, 3.01); //  first floor right window
	drawWindows(1, 4.2, 3.01); // second floor right window
	glPopMatrix();

	//right windows
	glPushMatrix();
	glTranslated(-1, 1.2, 3.01); // Translate to the first floor left window position
	glRotatef(-windowAngle, 0, 1, 0); // Rotate the window around the y-axis
	glTranslated(1, -1.2, -3.01); // Translate back to the original position
	drawWindows(-1.5, 1.2, 3.01); // first floor left window
	drawWindows(-1.5, 4.2, 3.01); // second floor left window
	glPopMatrix();

	glPushMatrix();
	glTranslated(2.0, 1.2, 3.01); // Translate to the first floor right window position
	glRotatef(-windowAngle, 0, 1, 0); // Rotate the window around the y-axis
	glTranslated(-2, -1.2, -3.01); // Translate back to the original position
	drawWindows(1.5, 1.2, 3.01); // first floor right window
	drawWindows(1.5, 4.2, 3.01); // second floor right window
	glPopMatrix();
	
	// Draw the door
	drawDoor(); 
	
}

void drawWheel(float centerX, float centerY, float centerZ) {
	int numSpokes = 12;
	float angleBetweenSpokes = 360.0 / numSpokes;
	float radius = 0.3;
	float depth = 0.1; // Depth of the wheel
	float innerRadius = radius - depth / 2.0;
	float outerRadius = radius + depth / 2.0;

	// Outer Wheel Rim
	glPushMatrix();
	glTranslatef(centerX, centerY, centerZ);
	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i <= 360; i++) {
		float angle = i * PI / 180.0;
		glVertex3f(outerRadius * cos(angle), outerRadius * sin(angle), 0.03);
		glVertex3f(innerRadius * cos(angle), innerRadius * sin(angle), 0.03);
	}
	for (int i = 0; i <= 360; i++) {
		float angle = i * PI / 180.0;
		glVertex3f(outerRadius * cos(angle), outerRadius * sin(angle), -0.018);
		glVertex3f(innerRadius * cos(angle), innerRadius * sin(angle), -0.018);
	}
	glEnd();
	glPopMatrix();
	// Cylinder filling
	glPushMatrix();
	glTranslatef(centerX, centerY, centerZ);
	GLUquadricObj* quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL);
	gluCylinder(quadric, outerRadius, outerRadius, depth, 30, 30);
	gluDeleteQuadric(quadric);
	glPopMatrix();
}

// Function to draw a cube between two points
void drawCube(float x1, float y1, float z1, float x2, float y2, float z2, float width) {
	// Vector from (x1, y1, z1) to (x2, y2, z2)
	float dx = x2 - x1;
	float dy = y2 - y1;
	float dz = z2 - z1;

	// Normalize the direction vector
	float length = sqrt(dx * dx + dy * dy + dz * dz);
	dx /= length;
	dy /= length;
	dz /= length;

	// Perpendicular vectors to (dx, dy, dz)
	float px, py, pz, qx, qy, qz;
	if (fabs(dy) > fabs(dx)) {
		px = 0;
		py = -dz;
		pz = dy;
	}
	else {
		px = dz;
		py = 0;
		pz = -dx;
	}

	// Normalize p
	float plength = sqrt(px * px + py * py + pz * pz);
	px /= plength;
	py /= plength;
	pz /= plength;

	// Compute q as the cross product of d and p
	qx = dy * pz - dz * py;
	qy = dz * px - dx * pz;
	qz = dx * py - dy * px;

	// Coordinates of the corners of the cube
	float corners[8][3] = {
		{x1 + width * (px + qx), y1 + width * (py + qy), z1 + width * (pz + qz)},
		{x1 + width * (-px + qx), y1 + width * (-py + qy), z1 + width * (-pz + qz)},
		{x1 + width * (-px - qx), y1 + width * (-py - qy), z1 + width * (-pz - qz)},
		{x1 + width * (px - qx), y1 + width * (py - qy), z1 + width * (pz - qz)},
		{x2 + width * (px + qx), y2 + width * (py + qy), z2 + width * (pz + qz)},
		{x2 + width * (-px + qx), y2 + width * (-py + qy), z2 + width * (-pz + qz)},
		{x2 + width * (-px - qx), y2 + width * (-py - qy), z2 + width * (-pz - qz)},
		{x2 + width * (px - qx), y2 + width * (py - qy), z2 + width * (pz - qz)}
	};

	// Draw the cube using quads
	glBegin(GL_QUADS);
	// Front face
	glVertex3fv(corners[0]); glVertex3fv(corners[1]); glVertex3fv(corners[2]); glVertex3fv(corners[3]);
	// Back face
	glVertex3fv(corners[4]); glVertex3fv(corners[5]); glVertex3fv(corners[6]); glVertex3fv(corners[7]);
	// Left face
	glVertex3fv(corners[0]); glVertex3fv(corners[3]); glVertex3fv(corners[7]); glVertex3fv(corners[4]);
	// Right face
	glVertex3fv(corners[1]); glVertex3fv(corners[2]); glVertex3fv(corners[6]); glVertex3fv(corners[5]);
	// Top face
	glVertex3fv(corners[3]); glVertex3fv(corners[2]); glVertex3fv(corners[6]); glVertex3fv(corners[7]);
	// Bottom face
	glVertex3fv(corners[0]); glVertex3fv(corners[1]); glVertex3fv(corners[5]); glVertex3fv(corners[4]);
	glEnd();
}

void drawFrame() {
	glColor3f(0.0, 0.0, 0.0); // Black color for frame

	// Main frame
	drawCube(-0.5, -0.3, 0.1, 0.5, -0.3, 0.1, 0.01);
	drawCube(-0.3, -0.3, 0.1, -0.2, 0.0, 0.1, 0.01);
	drawCube(0.3, -0.3, 0.1, 0.2, 0.0, 0.1, 0.01);
	drawCube(-0.2, 0.0, 0.1, 0.2, 0.0, 0.1, 0.01);
	// drawCube that connects the frame to the handlebars 
	drawCube(0.5, -0.3, 0.1, 0.5, 0.1, 0.1, 0.01);

	// Seat support
	drawCube(0.0, 0.0, 0.1, 0.0, 0.2, 0.1, 0.01);

}


void drawSeat() {
	glColor3f(0.5f, 0.35f, 0.05f); // Brown color for seat
	glBegin(GL_QUADS);
	// seat
	drawCube(-0.1, 0.2, 0.12, 0.1, 0.25, 0.12, 0.03);
	glEnd();
}

void drawHandlebars() {
	glColor3f(0.5f, 0.35f, 0.05f); // Brown color for handlebars
	glPushMatrix();
	glTranslatef(5, 0.9, 3.9);
	glRotatef(180, 0, 1, 0);
	GLUquadric* quad;
	quad = gluNewQuadric();
	gluCylinder(quad, 0.04, 0.04, 0.4, 12, 3);
	glPopMatrix();
}

void drawBicycle() {
	drawWheel(4, 0.5, 4); // Left wheel
	drawWheel(5, 0.5, 4);  // Right wheel
	drawFrame();
	drawSeat();
	drawHandlebars();
}




// draw a plane with a size of 100x100 under the building
void drawPlane() {
	glBegin(GL_QUADS);
	glColor3f(0.5f, 0.5f, 0.5f); // Grey color for the plane
	glVertex3f(-50.0, 0.0, 50.0);
	glVertex3f(50.0, 0.0, 50.0);
	glVertex3f(50.0, 0.0, -50.0);
	glVertex3f(-50.0, 0.0, -50.0);
	glEnd();
}

void DrawScene() {
	drawPlane();
	drawBuilding();
	//drawBicycle();
}

void updateCamera(GLfloat cameraX, GLfloat cameraY, GLfloat cameraZ, GLfloat pitch, GLfloat yaw) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Apply rotation
	glRotatef(pitch, 1.0f, 0.0f, 0.0f);
	glRotatef(-yaw, 0.0f, 1.0f, 0.0f);

	// Apply translation
	glTranslatef(-cameraX, -cameraY, -cameraZ);
}

LRESULT WINAPI WndProc(HWND hwnd, UINT m, WPARAM wp, LPARAM lp)
{
	
	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),   // size of this pfd  
		1,                     // version number  
		PFD_DRAW_TO_WINDOW |   // support window  
		PFD_SUPPORT_OPENGL |   // support OpenGL  
		PFD_DOUBLEBUFFER,      // double buffered  
		PFD_TYPE_RGBA,         // RGBA type  
		24,                    // 24-bit color depth  
		0, 0, 0, 0, 0, 0,      // color bits ignored  
		0,                     // no alpha buffer  
		0,                     // shift bit ignored  
		0,                     // no accumulation buffer  
		0, 0, 0, 0,            // accum bits ignored  
		32,                    // 32-bit z-buffer  
		0,                     // no stencil buffer  
		0,                     // no auxiliary buffer  
		PFD_MAIN_PLANE,        // main layer  
		0,                     // reserved  
		0, 0, 0                // layer masks ignored  
	};
	// set timer with 60 fps
	
	static HDC hdc;
	static HGLRC hgl;
	static int w, h;
	static GLfloat cameraX = 5.0f, cameraY = 10.0f, cameraZ = 40.0f;
	static GLfloat pitch = 0.0f, yaw = 0.0f; // Pitch and yaw angles
	static GLfloat cameraSpeed = 1.0f;
	static GLfloat rotationSpeed = 1.0f; // Adjust rotation speed as needed

	int  iPixelFormat;
	
	switch (m)
	{
	case WM_CREATE:
		hdc = GetDC(hwnd);
		iPixelFormat = ChoosePixelFormat(hdc, &pfd);
		SetPixelFormat(hdc, iPixelFormat, &pfd);
		hgl = wglCreateContext(hdc);
		wglMakeCurrent(hdc, hgl);
		glClearColor(0, 0.5f, 0, 1.0f);  // Background color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		// Set perspective projection
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);

		
		// Set camera position and orientation
		updateCamera(cameraX, cameraY, cameraZ, pitch, yaw);

		glViewport(0, 0, w, h);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		// Call the function to draw the scene
		DrawScene();
		glFlush();
		SwapBuffers(hdc);
		break;
	case WM_SIZE:
		w = LOWORD(lp);
		h = HIWORD(lp);
		glViewport(0, 0, w, h);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		// Call the function to draw the scene
		DrawScene();
		glFlush();
		SwapBuffers(hdc);
		break;
	case WM_KEYDOWN:
		switch (wp)
		{
			case 'O':
			{
				if (GetKeyState(VK_SHIFT) & 0x8000)
				{
					if (!isWindowOpen)
					{
						isWindowOpening = true;
						isWindowClosing = false;
					}
				}
				else
				{
					if (!isDoorOpen)
					{
						isDoorOpening = true;
						isDoorClosing = false;
					}
				}
				break;
			}
			case 'C':
			{
				if (GetKeyState(VK_SHIFT) & 0x8000)
				{
					if (isWindowOpen)
					{
						isWindowClosing = true;
						isWindowOpening = false;
					}
				}
				else
				{
					if (isDoorOpen)
					{
						isDoorClosing = true;
						isDoorOpening = false;
					}
				}
				break;
			}
			case 'W': // Move forward
				cameraX -= cameraSpeed * sin(yaw * PI / 180.0);
				cameraZ -= cameraSpeed * cos(yaw * PI / 180.0);
				move = 1;
				break;
			case 'S': // Move backward
				cameraX += cameraSpeed * sin(yaw * PI / 180.0);
				cameraZ += cameraSpeed * cos(yaw * PI / 180.0);
				move = 1;
				break;
			case 'A': // Rotate left
				yaw += rotationSpeed;
				move = 1;
				break;
			case 'D': // Rotate right
				yaw -= rotationSpeed;
				move = 1;
				break;
			case 'E': // Look up
				pitch += rotationSpeed;
				move = 1;
				break;
			case 'Q': // Look down
				pitch -= rotationSpeed;
				move = 1;
				break;
			case VK_SPACE: // Move up
				cameraY += cameraSpeed;
				move = 1;
				break;
			case VK_CONTROL: // Move down
				cameraY -= cameraSpeed;
				move = 1;
				break;
			
			default: break;
		}
		SetTimer(hwnd, 1, 1000 / 60, NULL);
		updateCamera(cameraX, cameraY, cameraZ, pitch, yaw);
		break;
		
	case WM_LBUTTONDOWN:
		if (isDoorOpen) {
			isDoorClosing = true;
			isDoorOpening = false;
		}
		else {
			isDoorOpening = true;
			isDoorClosing = false;
		}
		if (isWindowOpen) {
			isWindowClosing = true;
			isWindowOpening = false;
		}
		else {
			isWindowOpening = true;
			isWindowClosing = false;
		}
		SetTimer(hwnd, 1, 1000 / 60, NULL);
		break;
	case WM_TIMER:
	{
		bool isAnimating = false;

		if (!isDoorOpen && doorAngle > -90.0f && isDoorOpening) {
			doorAngle -= 5.0f;
			isAnimating = true;
		}
		else if (isDoorOpen && doorAngle < 0.0f && isDoorClosing) {
			doorAngle += 5.0f;
			isAnimating = true;
		}

		if (!isWindowOpen && windowAngle > -90.0f && isWindowOpening) {
			windowAngle -= 5.0f;
			isAnimating = true;
		}
		else if (isWindowOpen && windowAngle < 0.0f && isWindowClosing) {
			windowAngle += 5.0f;
			isAnimating = true;
		}
		if (move) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glEnable(GL_DEPTH_TEST);
			DrawScene();
			glFlush();
			SwapBuffers(hdc);
			move = 0;
		}
		if (isAnimating) {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glEnable(GL_DEPTH_TEST);
			DrawScene();
			glFlush();
			SwapBuffers(hdc);
		}
		else {
			KillTimer(hwnd, 1);
			isDoorOpen = !isDoorOpen;
			isWindowOpen = !isWindowOpen;
		}
		
		break;
	}

	case WM_DESTROY:
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(hgl);
		ReleaseDC(hwnd, hdc);
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hwnd, m, wp, lp);
	}
	return 0;
}




int APIENTRY WinMain(HINSTANCE hi, HINSTANCE pi, LPSTR c, int ns)
{
	WNDCLASS wc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hInstance = hi;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = L"MyClass";
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wc);
	HWND hwnd = CreateWindow(L"MyClass", L"Hello World", WS_OVERLAPPEDWINDOW, 300, 150, 800, 600, NULL, NULL, hi, 0);
	ShowWindow(hwnd, ns);
	UpdateWindow(hwnd);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}