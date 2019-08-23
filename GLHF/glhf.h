#pragma once

//#include <QtWidgets/QWidget>
#include "qgl.h"
#include "ui_glhf.h"
//#include <QTimer>
#include "QOpenGLBuffer"
#include <QOpenGLShader>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLFunctions>
#include "Field.h"

class GLHF : public QGLWidget
{
	Q_OBJECT

public:
	GLHF(QWidget *parent = Q_NULLPTR);

	unsigned short width;
	unsigned short height;
	unsigned short depth;
	Field * field;

private:
	Ui::GLHFClass ui;

	//QTimer *timer;	
	QOpenGLBuffer *VBO;
	QOpenGLBuffer *IBO;
	QOpenGLShader * vShad;
	QOpenGLShader * fShad;
	QOpenGLShaderProgram * shaderProgram;
	QOpenGLVertexArrayObject * VAO_draw;
	QOpenGLFunctions * f;

	void initializeGL()				override;
	void resizeGL(int aW, int aH)	override;
	void paintGL()					override;

	void draw() const;
	void draw_cell(const Cell & cell) const;
	void processing();

	GLfloat * convert_from_my_coord(int const * vertices) const;//coord.png
	void mousePressEvent(QMouseEvent *event) override;
	void keyPressEvent(QKeyEvent * event) override;
	void start();
};
