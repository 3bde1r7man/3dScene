#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <math.h>


#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float PI = 3.14159265358979323846;

GLfloat doorAngle = 0.0f; // Angle of the door
GLfloat windowAngle = 0.0f; // Angle of the windows
GLfloat wheelAngle = 0.0f; // Angle of the wheels
GLfloat angle = 0.0f; // Angle of bicycle around the y-axis
GLfloat bicycleRedus = 8.0f; // Radius of the bicycle around the origin
bool isDoorOpening = false, isDoorOpen = false;
bool isWindowOpening = false, isWindowOpen = false;
bool wheelMid = true, rotatingMid = false, isWheelRotating = false, isWheelRotatingRight = false;
bool rotateBicycle = false;

// Function prototypes
void draw3dObject(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat R, GLfloat G, GLfloat B);
void drawWindows(GLfloat x, GLfloat y, GLfloat z);
void drawDoor();
void drawWall(GLfloat x, GLfloat y, GLfloat z);
void drawRoof();
void drawWalls();
void drawBuilding();
void drawWheel(float centerX, float centerY, float centerZ);
void drawFrame();
void drawSeat();
void drawHandlebars();
void drawBicycle();
void drawPlane();
void idle();
void DrawScene();
void updateCamera(GLfloat cameraX, GLfloat cameraY, GLfloat cameraZ, GLfloat pitch, GLfloat yaw);


// draw 3d object that take the bottom near left and top far right points and draw a cube
void draw3dObject(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat R, GLfloat G, GLfloat B) {

	GLfloat vertices[8][3] = {
		{x1, y1, z1}, {x2, y1, z1}, {x2, y2, z1}, {x1, y2, z1},
		{x1, y1, z2}, {x2, y1, z2}, {x2, y2, z2}, {x1, y2, z2}
	};

	glBegin(GL_QUADS);
	// Front face
	glVertex3fv(vertices[0]); glVertex3fv(vertices[1]); glVertex3fv(vertices[2]); glVertex3fv(vertices[3]);
	glColor3f(R, G, B); 
	// Back face
	glVertex3fv(vertices[4]); glVertex3fv(vertices[5]); glVertex3fv(vertices[6]); glVertex3fv(vertices[7]);
	// Left face
	glVertex3fv(vertices[0]); glVertex3fv(vertices[4]); glVertex3fv(vertices[7]); glVertex3fv(vertices[3]);
	// Right face
	glVertex3fv(vertices[1]); glVertex3fv(vertices[5]); glVertex3fv(vertices[6]); glVertex3fv(vertices[2]);
	// Top face
	glVertex3fv(vertices[3]); glVertex3fv(vertices[2]); glVertex3fv(vertices[6]); glVertex3fv(vertices[7]);
	// Bottom face
	glVertex3fv(vertices[0]); glVertex3fv(vertices[1]); glVertex3fv(vertices[5]); glVertex3fv(vertices[4]);
	glEnd();
	
}


// draw a window with a size of 0.5 * 1 * 0.1
void drawWindows(GLfloat x, GLfloat y, GLfloat z) {
	glColor3f(0.0f, 0.5f, 0.5f); // Dark cyan color
	draw3dObject(x, y, z, x + 0.5, y + 1, z - 0.1, 0.6, 0.6, 0.6);  // Draw the window
}


// draw a door with a size of 0.5 * 1.8 * 0.1
void drawDoor() {
	glPushMatrix();
	glTranslatef(-0.5, 0.0, 3.01);
	glRotatef(doorAngle, 0, 1, 0); 
	glTranslated(0.5, 0.0, -3.01);
	glColor3f(0.3, 0.2, 0.1); // Dark brown for the door
	draw3dObject(-0.5, 0.0, 3.01, 0.5, 1.8, 2.9, 0.6, 0.6, 0.6); // Draw the door with grey depth color
	glBegin(GL_QUADS);
	// make a handle for the door like a knob
	glColor3f(1.0f, 1.0f, 0.0f); // Yellow color
	glVertex3f(0.4, 0.6, 3.02); glVertex3f(0.5, 0.6, 3.02); glVertex3f(0.5, 0.7, 3.02); glVertex3f(0.4, 0.7, 3.02);
	glEnd();
	
	glPopMatrix(); // Restore the previous matrix state
}
// this draw a 3 * 3 * 0.1 right and left wall
void drawWall(GLfloat x, GLfloat y, GLfloat z) {
	glColor3f(0.3f, 0.3f, 0.3f); // Dark grey color for the wall
	draw3dObject(x, y, z, x, y + 3, -z, 0.3, 0.3, 0.3);
}


void drawRoof() {
	// Roof is a Tetrahedron pyramid
	glBegin(GL_TRIANGLES);
	glColor3f(0.5f, 0.0f, 0.0f); // dark red color

	// front
	glVertex3f(-3.0, 6.1, 3.0); glVertex3f(3.0, 6.1, 3.0); glVertex3f(0.0, 8.0, 0.0);

	// back
	glVertex3f(-3.0, 6.1, -3.0); glVertex3f(3.0, 6.1, -3.0); glVertex3f(0.0, 8.0, 0.0);

	// right
	glVertex3f(3.0, 6.1, 3.0); glVertex3f(3.0, 6.1, -3.0); glVertex3f(0.0, 8.0, 0.0);

	// left
	glVertex3f(-3.0, 6.1, 3.0); glVertex3f(-3.0, 6.1, -3.0); glVertex3f(0.0, 8.0, 0.0);

	glEnd();
}

void drawWalls() {
	glBegin(GL_QUADS);
	// first floor
	// front
	// plane for the first floor with color off white
	glColor3f(0.7f, 0.7f, 0.7f);
	glVertex3f(-3.0, 0.1, 3.0); glVertex3f(3.0, 0.1, 3.0); glVertex3f(3.0, 0.1, -3.0); glVertex3f(-3.0, 0.1, -3.0);

	// dark grey color for the wall
	glColor3f(0.3f, 0.3f, 0.3f);
	// this exclueds the windows for the first floor
	glVertex3f(-3.0, 0.0, 3.0);  glVertex3f(-2, 0.0, 3.0); glVertex3f(-2, 3.0, 3.0); glVertex3f(-3.0, 3.0, 3.0);

	glVertex3f(2, 0.0, 3.0); glVertex3f(3.0, 0.0, 3.0); glVertex3f(3.0, 3.0, 3.0); glVertex3f(2, 3.0, 3.0);

	glVertex3f(-1, 0.0, 3.0); glVertex3f(-0.5, 0.0, 3.0); glVertex3f(-0.5, 3.0, 3.0); glVertex3f(-1, 3.0, 3.0);

	glVertex3f(0.5, 0.0, 3.0); glVertex3f(1, 0.0, 3.0); glVertex3f(1, 3.0, 3.0); glVertex3f(0.5, 3.0, 3.0);

	// filling top of the door 
	glVertex3f(-0.5, 1.8, 3.0); glVertex3f(0.5, 1.8, 3.0); glVertex3f(0.5, 3.0, 3.0); glVertex3f(-0.5, 3.0, 3.0);

	// filling top of the windows
	glVertex3f(-2, 2.2 , 3.0); glVertex3f(2, 2.2, 3.0); glVertex3f(2, 3.0, 3.0); glVertex3f(-2, 3.0, 3.0);
	


	// filling under the windows
	glVertex3f(-2, 0.0, 3.0); glVertex3f(-1, 0.0, 3.0); glVertex3f(-1, 1.2, 3.0); glVertex3f(-2, 1.2, 3.0);

	glVertex3f(1, 0.0, 3.0); glVertex3f(2, 0.0, 3.0); glVertex3f(2, 1.2, 3.0); glVertex3f(1, 1.2, 3.0);
	glEnd();


	// right
	drawWall(3.0, 0.0, -3.0);
	// left
	drawWall(-3.0, 0.0, -3.0);
	// back
	glPushMatrix();
	glTranslatef(-3.0, 0.0, -3.0);
	glRotatef(90, 0, 1, 0);
	glTranslatef(3.0, 0.0, 3.0);
	drawWall(-3.0, 0.0, -3.0); // first floor
	drawWall(-3.0, 3.1, -3.0); // second floor
	glPopMatrix();


	// Second floor
	// front
	// draw the second floor with color off white
	glBegin(GL_QUADS);
	glColor3f(0.7f, 0.7f, 0.7f); 
	glVertex3f(-3.0, 3.1, 3.0); glVertex3f(3.0, 3.1, 3.0); glVertex3f(3.0, 3.1, -3.0); glVertex3f(-3.0, 3.1, -3.0);

	// exclude the windows for the second floor
	glColor3f(0.3f, 0.3f, 0.3f);
	glVertex3f(-3.0, 3.1, 3.0); glVertex3f(-2, 3.1, 3.0); glVertex3f(-2, 6.1, 3.0); glVertex3f(-3.0, 6.1, 3.0);

	glVertex3f(2, 3.1, 3.0); glVertex3f(3.0, 3.1, 3.0); glVertex3f(3.0, 6.1, 3.0); glVertex3f(2, 6.1, 3.0);

	// filling between the windows
	glVertex3f(-1, 3.1, 3.0); glVertex3f(1, 3.1, 3.0); glVertex3f(1, 6.1, 3.0); glVertex3f(-1, 6.1, 3.0);

	// filling the top of the windows
	glVertex3f(-2, 5.2, 3.0); glVertex3f(2, 5.2, 3.0); glVertex3f(2, 6.1, 3.0); glVertex3f(-2, 6.1, 3.0);


	// filling the bottom of the windows
	glVertex3f(-2, 3.1, 3.0); glVertex3f(2, 3.1, 3.0); glVertex3f(2, 4.2, 3.0); glVertex3f(-2, 4.2, 3.0);

	glEnd();
	// right
	drawWall(3.0, 3.1, -3.0);
	// left
	drawWall(-3.0, 3.1, -3.0);

	// add split between the first and second floor
	glBegin(GL_QUADS);
	glColor3f(0, 0, 0); // black color
	glVertex3f(-3.0, 3.0, 3.0); glVertex3f(3.0, 3.0, 3.0); glVertex3f(3.0, 3.1, 3.0); glVertex3f(-3.0, 3.1, 3.0);

	glVertex3f(3.0, 3.0, 3.0); glVertex3f(3.0, 3.0, -3.0); glVertex3f(3.0, 3.1, -3.0); glVertex3f(3.0, 3.1, 3.0);

	glVertex3f(-3.0, 3.0, -3.0); glVertex3f(-3.0, 3.0, 3.0); glVertex3f(-3.0, 3.1, 3.0); glVertex3f(-3.0, 3.1, -3.0);

	glVertex3f(-3.0, 3.0, -3.0); glVertex3f(3.0, 3.0, -3.0); glVertex3f(3.0, 3.1, -3.0); glVertex3f(-3.0, 3.1, -3.0);
	glEnd();
}

// draw a building
void drawBuilding() {
	// draw the walls
	drawWalls();
	// draw the roof
	drawRoof();

	//left windows
	glPushMatrix();
	glTranslatef(-2.0, 1.2, 3.01); 
	glRotatef(windowAngle, 0, 1, 0); 
	glTranslatef(2.0, -1.2, -3.01); 
	drawWindows(-2, 1.2, 3.01); // first floor left window
	drawWindows(-2, 4.2, 3.01); // second floor left window
	glPopMatrix();

	glPushMatrix();
	glTranslated(1.0, 1.2, 3.01);
	glRotatef(windowAngle, 0, 1, 0);
	glTranslated(-1.0, -1.2, -3.01);
	drawWindows(1, 1.2, 3.01); //  first floor right window
	drawWindows(1, 4.2, 3.01); // second floor right window
	glPopMatrix();

	//right windows
	glPushMatrix();
	glTranslated(-1, 1.2, 3.01);
	glRotatef(-windowAngle, 0, 1, 0);
	glTranslated(1, -1.2, -3.01);
	drawWindows(-1.5, 1.2, 3.01); // first floor left window
	drawWindows(-1.5, 4.2, 3.01); // second floor left window
	glPopMatrix();

	glPushMatrix();
	glTranslated(2.0, 1.2, 3.01);
	glRotatef(-windowAngle, 0, 1, 0);
	glTranslated(-2, -1.2, -3.01);
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
	glColor3f(0.5f, 0.35f, 0.05f); // Brown color for the wheel
	for (int i = 0; i <= 360; i++) {
		float angle = i * PI / 180.0;
		glVertex3f(outerRadius * cos(angle), outerRadius * sin(angle), 0.03);
		glVertex3f(innerRadius * cos(angle), innerRadius * sin(angle), 0.03);
	}
	for (int i = 0; i <= 360; i++) {
		float angle = i * PI / 180.0;
		glVertex3f(outerRadius * cos(angle), outerRadius * sin(angle), 0.0);
		glVertex3f(innerRadius * cos(angle), innerRadius * sin(angle), 0.0);
	}
	glEnd();
	// Spokes
	for (int i = 0; i < numSpokes; i++) {
		glPushMatrix();
		glRotatef(i * angleBetweenSpokes, 0.0, 0.0, 1.0);
		glBegin(GL_LINES);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(0.0, radius, 0.0);
		glEnd();
		glPopMatrix();
	}
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


void drawFrame() {
	glColor3f(0.0, 0.0, 0.0); // Black color for frame

	// Main frame
	draw3dObject(-0.5, -0.3, 0.1, 0.5, -0.27, 0.09, 0.0, 0.0, 0.0);
	draw3dObject(-0.2, 0.0, 0.1, 0.2, 0.03, 0.09, 0.0, 0.0, 0.0);

	glPushMatrix();
	glTranslatef(-0.3, -0.25, 0.1);
	glRotatef(-20, 0, 0, 1);
	glTranslatef(0.3, 0.25, -0.1);
	draw3dObject(-0.3, -0.3, 0.1, -0.28, 0.05, 0.09, 0.0, 0.0, 0.0);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.3, -0.25, 0.1);
	glRotatef(20, 0, 0, 1);
	glTranslatef(-0.3, 0.25, -0.1);
	draw3dObject(0.3, -0.3, 0.1, 0.28, 0.05, 0.09, 0.0, 0.0, 0.0);
	glPopMatrix();
	// drawCube that connects the frame to the handlebars 
	draw3dObject(0.5, -0.3, 0.1, 0.48, 0.2, 0.09, 0.0, 0.0, 0.0);

	// Seat support
	draw3dObject(0.0, 0.0, 0.1, 0.02, 0.2, 0.09, 0.0, 0.0, 0.0);

}


void drawSeat() {
	glColor3f(0.5, 0.35, 0.05); // Brown color
	// seat
	draw3dObject(-0.1, 0.2, 0.15, 0.1, 0.25, 0.0, 0.5, 0.35, 0.05);

}

void drawHandlebars() {
	glColor3f(0.5f, 0.35f, 0.05f); // Brown color
	glPushMatrix();
	glTranslatef(0.5, 0.2, 0.25);
	glRotatef(180, 0, 1, 0);
	GLUquadric* quad;
	quad = gluNewQuadric();
	gluCylinder(quad, 0.04, 0.04, 0.3, 12, 3);
	glPopMatrix();
}



void drawBicycle() {
	glPushMatrix();
	glRotatef(angle, 0, 1, 0);
	glTranslatef(0.5, 0.7, bicycleRedus);
	glPushMatrix();
	glTranslated(0.5, -0.3, 0.1);
	glRotatef(wheelAngle, 0, 1, 0);
	glTranslatef(-0.5, 0.3, -0.1);
	drawWheel(0.5, -0.3, 0.1);  // Right wheel
	drawHandlebars();
	glPopMatrix();
	drawWheel(-0.5, -0.3, 0.1); // Left wheel
	drawFrame();
	drawSeat();
	glPopMatrix();
	
}


void idle() {
	angle += 0.9f; // Increment the angle to rotate
	if (angle > 360.0f) angle -= 360.0f; // Keep the angle within 0-360 range

}

// draw plane with a size of 100x100 under the building
void drawPlane() {
	glBegin(GL_QUADS);
	glColor3f(0.5f, 0.5f, 0.5f); // Grey color
	glVertex3f(-50.0, 0.0, 50.0);
	glVertex3f(50.0, 0.0, 50.0);
	glVertex3f(50.0, 0.0, -50.0);
	glVertex3f(-50.0, 0.0, -50.0);
	glEnd();
}

void DrawScene() {
	drawPlane();
	drawBuilding();
	drawBicycle();
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
	
	static PIXELFORMATDESCRIPTOR pfd = { sizeof(PIXELFORMATDESCRIPTOR), 1,
										  PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
										  PFD_TYPE_RGBA, 24, 0, 0, 0, 0, 0, 0, 0, 32, 0, 0, 0, 0, 0, 0, PFD_MAIN_PLANE, 0, 0, 0, 0 };

	
	static HDC hdc;
	static HGLRC hgl;
	static int w, h;
	static GLfloat cameraX = 5.0f, cameraY = 8.0f, cameraZ = 30.0f;
	static GLfloat pitch = 0.0f, yaw = 0.0f; // Pitch and yaw angles
	static GLfloat cameraSpeed = 1.0f;
	static GLfloat rotationSpeed = 1.0f;

	int  iPixelFormat;
	
	switch (m)
	{
	case WM_CREATE:
		hdc = GetDC(hwnd);
		iPixelFormat = ChoosePixelFormat(hdc, &pfd);
		SetPixelFormat(hdc, iPixelFormat, &pfd);
		hgl = wglCreateContext(hdc);
		wglMakeCurrent(hdc, hgl);
		glClearColor(0.0f, 0.5f, 0, 1.0f);  // green Background color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		// Set perspective projection
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(45.0f, (GLfloat)WINDOW_WIDTH / (GLfloat)WINDOW_HEIGHT, 0.1f, 100.0f);

		
		// Set camera position and orientation
		updateCamera(cameraX, cameraY, cameraZ, pitch, yaw);
		SetTimer(hwnd, 2, 1000 / 120, NULL); // set the timer to 120 fps

		glViewport(0, 0, w, h);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_DEPTH_TEST);
		// draw the scene
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
		// draw the scene
		DrawScene();
		glFlush();
		SwapBuffers(hdc);
		break;
	case WM_KEYDOWN:
		switch (wp)
		{
			case 'O':
			{
				// get the state of the shift and caps lock keys
				bool shiftPressed = GetKeyState(VK_SHIFT) & 0x8000;
				bool capsLockOn = GetKeyState(VK_CAPITAL) & 0x0001;

				// Perform XOR operation to determine which condition to open
				bool openCondition = shiftPressed ^ capsLockOn;

				if (openCondition)
				{
					if (!isWindowOpen)
					{
						isWindowOpening = true;
					}
				}
				else
				{
					if (!isDoorOpen)
					{
						isDoorOpening = true;
					}
				}
				SetTimer(hwnd, 1, 1000 / 60, NULL);
				break;
			}
			case 'C':
			{
				// get the state of the shift and caps lock keys
				bool shiftPressed = GetKeyState(VK_SHIFT) & 0x8000;
				bool capsLockOn = GetKeyState(VK_CAPITAL) & 0x0001;

				// Perform XOR operation to determine which condition to close
				bool closeCondition = shiftPressed ^ capsLockOn;

				if (closeCondition)
				{
					if (isWindowOpen)
					{
						isWindowOpening = false;
					}
				}
				else
				{
					if (isDoorOpen)
					{
						isDoorOpening = false;
					}
				}
				SetTimer(hwnd, 1, 1000 / 60, NULL);
				break;
			}
			case 'R':
			{
				isWheelRotating = true;
				isWheelRotatingRight = true;
				wheelMid = false;
				SetTimer(hwnd, 1, 1000 / 60, NULL);
				break;
			}
			case 'L':
			{
				isWheelRotating = true;
				isWheelRotatingRight = false;
				wheelMid = false;
				SetTimer(hwnd, 1, 1000 / 60, NULL);
				break;
			}
			case 'T':
			{
				rotatingMid = true;
				SetTimer(hwnd, 1, 1000 / 60, NULL);
				break;
			}
			case 'F':
			{
				if (bicycleRedus < 15.0f) {
					bicycleRedus += 0.5;
				}
				break;
			}
			case 'B':
			{
				if (bicycleRedus > 5.0f) {
					bicycleRedus -= 0.5;
				}
				break;
			}
			case 'W': // Move forward
				cameraX -= cameraSpeed * sin(yaw * PI / 180.0);
				cameraZ -= cameraSpeed * cos(yaw * PI / 180.0);
				break;
			case 'S': // Move backward
				cameraX += cameraSpeed * sin(yaw * PI / 180.0);
				cameraZ += cameraSpeed * cos(yaw * PI / 180.0);
				break;
			case 'A': // Rotate left
				yaw += rotationSpeed;
				break;
			case 'D': // Rotate right
				yaw -= rotationSpeed;
				break;
			case 'E': // Look up
				pitch += rotationSpeed;
				break;
			case 'Q': // Look down
				pitch -= rotationSpeed;
				break;
			case VK_SPACE: // Move up
				cameraY += cameraSpeed;
				break;
			case VK_CONTROL: // Move down
				cameraY -= cameraSpeed;
				break;
			
			default: break;
		}
		updateCamera(cameraX, cameraY, cameraZ, pitch, yaw);
		break;
	case WM_LBUTTONDOWN:
		if (!rotateBicycle)
		{
			rotateBicycle = true;
			SetTimer(hwnd, 3, 1000 / 120, NULL);
		}
		break;
	case WM_RBUTTONDOWN:
		if (rotateBicycle)
		{
			rotateBicycle = false;
			KillTimer(hwnd, 3);
		}
		break;
	case WM_TIMER:
	{
		bool isAnimating = false;
		switch (wp)
		{
			case 1:
			{
				if (!isDoorOpen && doorAngle > -90.0f && isDoorOpening) {
					doorAngle -= 5.0f;
					isAnimating = true;
				}
				else if (isDoorOpen && doorAngle < 0.0f && !isDoorOpening) {
					doorAngle += 5.0f;
					isAnimating = true;
				}

				if (!isWindowOpen && windowAngle > -90.0f && isWindowOpening) {
					windowAngle -= 5.0f;
					isAnimating = true;
				}
				else if (isWindowOpen && windowAngle < 0.0f && !isWindowOpening) {
					windowAngle += 5.0f;
					isAnimating = true;
				}
				if (rotatingMid && !wheelMid) {
					if (wheelAngle > 0.0f) {
						wheelAngle -= 5.0f;
						isAnimating = true;
					}
					else if (wheelAngle < 0.0f) {
						wheelAngle += 5.0f;
						isAnimating = true;
					}
				}
				else if (isWheelRotating && isWheelRotatingRight && wheelAngle > -45.0f)
				{
					wheelAngle -= 5.0f;
					isAnimating = true;
				}
				else if (isWheelRotating && !isWheelRotatingRight && wheelAngle < 45.0f)
				{
					wheelAngle += 5.0f;
					isAnimating = true;
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
					isWheelRotating = false;
					if (rotatingMid)
					{
						wheelMid = !wheelMid;
					}
					rotatingMid = false;
				}
				break;
			}
			case 2:
			{
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glEnable(GL_DEPTH_TEST);
				DrawScene();
				glFlush();
				SwapBuffers(hdc);
				break;
			}
			case 3:
			{
				idle();
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glEnable(GL_DEPTH_TEST);
				DrawScene();
				glFlush();
				SwapBuffers(hdc);
			}
			default:
				break;
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
	HWND hwnd = CreateWindow(L"MyClass", L"3d building & bicycle", WS_OVERLAPPEDWINDOW, 300, 150, 800, 600, NULL, NULL, hi, 0);
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