/*
 * GameMgr.cpp
 *
 *  Created on: Mar 7, 2019
 *      Author: wtong
 */

#include <OgreOverlay.h>
#include <OgreSceneNode.h>
#include <OgreMeshManager.h>

#include <Engine.h>
#include <EntityMgr.h>
#include <GameMgr.h>
#include <GfxMgr.h>

using namespace Ogre;

GameMgr::GameMgr(Engine *engine) : Mgr(engine) {
	surfaceHeight = 0;
	cameraNode = NULL;
}

GameMgr::~GameMgr() {
}

void GameMgr::Init(){
}

void GameMgr::LoadLevel(){

	// Configure the lighting
	engine->gfxMgr->mSceneMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
	Light* light = engine->gfxMgr->mSceneMgr->createLight("MainLight");
	light->setPosition(0, 200, 500);

	//Camera node to allow custom camera keys
	cameraNode = engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	cameraNode->setPosition(0, 200, 500);
	cameraNode->attachObject(engine->gfxMgr->mCamera);

	generateTerrain();

	// entityMgr = new EntityMgr(engine);
	generateEntities();
	engine->entityMgr->selectNextEntity();
	// To avoid accidentally crashing program when attempting
	// to move an entity before selecting one first (at program start)
}

void GameMgr::generateTerrain(){
	// Make the skybox
	engine->gfxMgr->mSceneMgr->setSkyBox(true, "Examples/StormySkyBox");

	// Create ground
	// groundSurface(Vector3::UNIT_Y, 0);
	groundSurface.normal = Vector3::UNIT_Y;
	groundSurface.d = 0;
	MeshManager::getSingleton().createPlane(
		"ground", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		groundSurface, 10000, 10000, 20, 20,
		true, 1, 5, 5, 	Vector3::UNIT_Z);
	Entity* groundEntity = engine->gfxMgr->mSceneMgr->createEntity("ground");
	engine->gfxMgr->mSceneMgr->getRootSceneNode()->createChildSceneNode(Vector3(0, surfaceHeight, 0))->attachObject(groundEntity);
	groundEntity->setCastShadows(false);
	groundEntity->setMaterialName("Examples/Water2");
}

void GameMgr::generateEntities(){
	Vector3 pos = Vector3(-1000, 0, 0);
	engine->entityMgr->CreateEntityOfTypeAtPosition("Destroyer", pos);
	pos.x += 500;
	engine->entityMgr->CreateEntityOfTypeAtPosition("Carrier", pos);
	pos.x += 500;
	engine->entityMgr->CreateEntityOfTypeAtPosition("Speedboat", pos);
	pos.x += 500;
	engine->entityMgr->CreateEntityOfTypeAtPosition("Frigate", pos);
	pos.x += 500;
	engine->entityMgr->CreateEntityOfTypeAtPosition("Alien", pos);
	pos.x += 500;
	engine->entityMgr->CreateEntityOfTypeAtPosition("Banshee", pos);
}
