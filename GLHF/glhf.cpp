#include "stdafx.h"
#include "glhf.h"

#define CELL_WIDTH 10
#define CELL_HEIGHT 10
#define NUM_OF_ELEMENTS_IN_VERTICES 12

GLHF::GLHF(QWidget *parent)
	: QGLWidget(parent)
{
	ui.setupUi(this);

	width = 1000;
	height = 600;
	depth = 1;

	this->setFixedSize(QSize(width, height));
	this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

	this->move(0, 0);

	field = new Field(width / CELL_WIDTH, height / CELL_HEIGHT);

	//timer = new QTimer(this);
	//timer->setInterval(100);
	//connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
}

void GLHF::initializeGL()
{
	qglClearColor(Qt::white);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_INDEX_ARRAY);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);

	VAO_draw = new QOpenGLVertexArrayObject(this);
	VAO_draw->create();

	f = new QOpenGLFunctions;
	f->initializeOpenGLFunctions();

	VBO = new QOpenGLBuffer(QOpenGLBuffer::Type::VertexBuffer);
	qDebug() << VBO->create() << " create VBO";
	VBO->setUsagePattern(QOpenGLBuffer::UsagePattern::StreamDraw);

	IBO = new QOpenGLBuffer(QOpenGLBuffer::Type::IndexBuffer);
	qDebug() << IBO->create() << " create IBO";
	IBO->setUsagePattern(QOpenGLBuffer::UsagePattern::StreamDraw);


	vShad = new QOpenGLShader(QOpenGLShader::Vertex);
	qDebug() << vShad->compileSourceFile(":/GLHF/vert") << " vShad";

	fShad = new QOpenGLShader(QOpenGLShader::Fragment);
	qDebug() << fShad->compileSourceFile(":/GLHF/frag") << " fShad";

	shaderProgram = new QOpenGLShaderProgram(this);
	shaderProgram->create();
	qDebug() << shaderProgram->addShader(vShad) << " add vShad";
	qDebug() << shaderProgram->addShader(fShad) << " add fShad";
	qDebug() << shaderProgram->link() << " link";
	shaderProgram->setUniformValue("outColor", Qt::black);

	int * my_vertices = new int[NUM_OF_ELEMENTS_IN_VERTICES]
	{
		0,			0,			 0,
		0,			CELL_HEIGHT, 0,
		CELL_WIDTH, CELL_HEIGHT, 0,
		CELL_WIDTH, 0,			 0
	};
	GLuint * indexes = new GLuint[6]
	{
		0,1,2,
		0,2,3
	};

	GLfloat * vertices = convert_from_my_coord(my_vertices);
	for(int i = 0; i < NUM_OF_ELEMENTS_IN_VERTICES; i++)
	{
		qDebug() << vertices[i];
	}

	//используем шейдерную программу
	qDebug() << shaderProgram->bind() << " shPr bind";
	//привязываем Объект Вершинного Массива
	VAO_draw->bind();
	//привязка буфера к OpenGL
	qDebug() << VBO->bind() << " VBO bind";
	IBO->bind();
	//запись данных в буфер
	VBO->allocate(vertices, sizeof(GLfloat) * NUM_OF_ELEMENTS_IN_VERTICES);
	IBO->allocate(indexes, sizeof(GLuint) * 6);
	//установка указателя в вершинном буфере на location; tupleSize = количество компонентов в векторе
	shaderProgram->setAttributeBuffer(0, GL_FLOAT, 0, 3, sizeof(GLfloat) * 0);
	//хз
	shaderProgram->enableAttributeArray(0);
	//shaderProgram->setAttributeBuffer(1, GL_FLOAT, sizeof(GLfloat) * 3, 3, sizeof(GLfloat) * STRIDE);
	//shaderProgram->enableAttributeArray(1);
	//отвязываем VAO_draw
	VAO_draw->release();
}

void GLHF::resizeGL(int aW, int aH)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, depth, 0);
	glViewport(0, 0, (GLint)aW, (GLint)aH);
}

void GLHF::paintGL()
{
	qglClearColor(Qt::black);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	processing();

	draw();
}

void GLHF::draw() const
{
	//Cell cell(2, 1, false);
	//field->place_cell(cell);
	for (auto i = 0; i < field->height(); i++)
	{
		for (auto j = 0; j < field->width(); j++)
		{
			draw_cell((*field)[i][j]);
		}
	}
}

void GLHF::draw_cell(const Cell & cell) const
{
	if(cell.is_alive())
	{
		const auto x = cell.x() * CELL_WIDTH;
		const auto y = cell.y() * CELL_HEIGHT;

		int * my_vertices = new int[NUM_OF_ELEMENTS_IN_VERTICES]
		{
			x, y, 0,
			x, y + CELL_HEIGHT, 0,
			x + CELL_WIDTH, y + CELL_HEIGHT, 0,
			x + CELL_WIDTH, y, 0
		};

		GLfloat * vertices = convert_from_my_coord(my_vertices);

		shaderProgram->bind();
		VAO_draw->bind();
		VBO->write(0, vertices, sizeof(GLfloat) * NUM_OF_ELEMENTS_IN_VERTICES);
		//VBO->allocate(vertices, sizeof(GLfloat) * NUM_OF_ELEMENTS_IN_VERTICES);
		f->glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		VAO_draw->release();
		delete[] my_vertices;
		delete[] vertices;
	}
}

void GLHF::processing()
{

}

GLfloat* GLHF::convert_from_my_coord(int const* vertices) const
{
	GLfloat * result = new GLfloat[NUM_OF_ELEMENTS_IN_VERTICES];
	for (auto i = 0; i <= NUM_OF_ELEMENTS_IN_VERTICES - 3; i+=3)
	{
		const auto x = vertices[i];
		const auto y = vertices[i + 1];
		const auto z = vertices[i + 2];
		result[i] = 2.0f / static_cast<GLfloat>(width) * x - 1.0;
		result[i + 1] = (-2.0f / static_cast<GLfloat>(height) * y + 1.0);
		result[i + 2] = z;
	}
	return result;
}

void GLHF::mousePressEvent(QMouseEvent* event)
{
	const auto x = round(event->x() / CELL_WIDTH);
	const auto y = round(event->y() / CELL_HEIGHT);
	
	if (field->is_alive(x, y))
	{
		field->kill(x, y);
		field->release_cell(x, y);
	}
	else if (field->is_dead(x, y))
	{
		field->revive(x, y);
		field->release_cell(x, y);
	}
	updateGL();
}

void GLHF::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Enter || (event->key() == Qt::Key_Return))
		start();
}

void GLHF::start()
{
	for(auto x = 0; x < field->width(); x++)
	{
		for(auto y = 0; y < field->height(); y++)
		{
			field->transform_cell(x, y);
		}
	}
	field->release_cells();
	updateGL();
}
