#include"Octahedron .h"

//初始化
Octahedron::Octahedron(float l, float w, float h)
{
	length = l;
	width = w;
	height = h;
	x = 0;
	y = 0;
	z = 0;
	Texture = NULL;
}

void Octahedron::setPos(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}


int Octahedron::setTexture(GLuint texture)
{
	if (this->Texture != NULL)
	{
		textureChain* temp = new(textureChain);
		temp->No = this->Texture->No + 1;
		temp->next = this->Texture;
		temp->texture = texture;
		this->Texture = temp;
		return 0;
	}
	else
	{
		textureChain* temp = new(textureChain);
		temp->No = 0;
		temp->next = this->Texture;
		temp->texture = texture;
		this->Texture = temp;
		return 0;
	}


}

void Octahedron::showFaceWithSingleTex()
{
	this->getver();
	glColor3f(1, 1, 1);//glut中的颜色设置类似于AE中的时间轴，如果不指定会沿用上一个（如果有）或者定为下一个（此前未定义）
	GLint* currentTexture = new(GLint);
	glGetIntegerv(GL_TEXTURE_BINDING_2D, currentTexture);
	if (this->Texture != NULL)
	{
	glBindTexture(GL_TEXTURE_2D, this->Texture->texture);
	}

	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(1.0, 0.0); glVertex3f(this->x, this->t, this->z);
	glTexCoord2f(0.0, 0.0); glVertex3f(this->r, this->y, this->z);
	glTexCoord2f(1.0, 1.0); glVertex3f(this->x, this->y, this->n);
	glTexCoord2f(0.0, 0.0); glVertex3f(this->l, this->y, this->z);
	glTexCoord2f(1.0, 1.0); glVertex3f(this->x, this->y, this->f);
	glTexCoord2f(0.0, 0.0); glVertex3f(this->r, this->y, this->z);
	glEnd();
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(1.0, 0.0); glVertex3f(this->x, this->b, this->z);
	glTexCoord2f(0.0, 0.0); glVertex3f(this->r, this->y, this->z);
	glTexCoord2f(1.0, 1.0); glVertex3f(this->x, this->y, this->n);
	glTexCoord2f(0.0, 0.0); glVertex3f(this->l, this->y, this->z);
	glTexCoord2f(1.0, 1.0); glVertex3f(this->x, this->y, this->f);
	glTexCoord2f(0.0, 0.0); glVertex3f(this->r, this->y, this->z);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, *currentTexture);
	delete(currentTexture);
}

void Octahedron::showFaceWithDuoTex()
{
	this->getver();
	glColor3f(1, 1, 1);
	GLint* currentTexture=new(GLint);
	glGetIntegerv(GL_TEXTURE_BINDING_2D, currentTexture);
	if (this->Texture != NULL)
	{
		glBindTexture(GL_TEXTURE_2D, this->Texture->texture);
	}
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(1.0, 0.0); glVertex3f(this->x, this->t, this->z);
	glTexCoord2f(0.0, 0.0); glVertex3f(this->r, this->y, this->z);
	glTexCoord2f(1.0, 1.0); glVertex3f(this->x, this->y, this->n);
	glTexCoord2f(0.0, 0.0); glVertex3f(this->l, this->y, this->z);
	glTexCoord2f(1.0, 1.0); glVertex3f(this->x, this->y, this->f);
	glTexCoord2f(0.0, 0.0); glVertex3f(this->r, this->y, this->z);
	glEnd();
	if (this->Texture != NULL && this->Texture->next != NULL)
	{
		glBindTexture(GL_TEXTURE_2D, this->Texture->next->texture);
	}
	glBegin(GL_TRIANGLE_FAN);
	glTexCoord2f(1.0, 0.0); glVertex3f(this->x, this->b, this->z);
	glTexCoord2f(0.0, 0.0); glVertex3f(this->r, this->y, this->z);
	glTexCoord2f(1.0, 1.0); glVertex3f(this->x, this->y, this->n);
	glTexCoord2f(0.0, 0.0); glVertex3f(this->l, this->y, this->z);
	glTexCoord2f(1.0, 1.0); glVertex3f(this->x, this->y, this->f);
	glTexCoord2f(0.0, 0.0); glVertex3f(this->r, this->y, this->z);
	glEnd();
	glBindTexture(GL_TEXTURE_2D, *currentTexture);
	delete(currentTexture);
}

void Octahedron::showEdge(float R, float G, float B, float LineWidth)
{
	this->getver();
	glColor3f(R, G, B);
	glLineWidth(LineWidth);
	glBegin(GL_LINE_STRIP);
	glVertex3f(this->r, this->y, this->z);
	glVertex3f(this->x, this->t, this->z);
	glVertex3f(this->x, this->y, this->n);
	glVertex3f(this->r, this->y, this->z);
	glVertex3f(this->x, this->b, this->z);
	glVertex3f(this->x, this->y, this->f);
	glVertex3f(this->l, this->y, this->z);
	glVertex3f(this->x, this->b, this->z);
	glVertex3f(this->x, this->y, this->n);
	glVertex3f(this->l, this->y, this->z);
	glVertex3f(this->x, this->t, this->z);
	glVertex3f(this->x, this->y, this->f);
	glVertex3f(this->r, this->y, this->z);
	glEnd();
}

void Octahedron::getver()
{
	this->n = this->z + this->length / 2;
	this->f = this->z - this->length / 2;
	this->r = this->x + this->width / 2;
	this->l = this->x - this->width / 2;
	this->t = this->y + this->height / 2;
	this->b = this->y - this->height / 2;
}

