#include <iostream>
#include "Scene.h"


Scene::Scene()
{
	for (int i = 0; i < 4; i++)
		circulos[i] = NULL;
}

Scene::~Scene()
{
	for (int i = 0; i < 4; i++)
		if (circulos[i] != NULL)
			delete circulos[i];
}


void Scene::init()
{
	initShaders();
	for(int i = 0; i < 4; i++)
		circulos[i] = Circulo::createCirculo(-0.5f + (i % 2), -0.5f + (i / 2), 0.25f, program);
}

void Scene::update(int deltaTime)
{
}

void Scene::render()
{
	program.use();
	for (int i = 0; i < 4; i++)
		circulos[i]->render();
}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/simple.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/simple.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	program.init();
	program.addShader(vShader);
	program.addShader(fShader);
	program.link();
	if(!program.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << program.log() << endl << endl;
	}
	program.bindFragmentOutput("outColor");
}

