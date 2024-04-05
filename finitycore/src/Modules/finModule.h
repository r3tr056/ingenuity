#pragma once

#ifndef __FIN_MODULE_H__
#define __FIN_MODULE_H__

#include <string>

class Application;

struct Collider;

class finModule {
public:
	std::string name;
	bool active;

public:
	finModule() : active(false) {}
	virtual ~finModule() {}

	void Init() { active = true; }
	virtual bool Awake() { return true; }
	virtual bool Start() { return true; }
	virtual bool PreUpdate() { return true; }
	virtual bool Update() { return true; }
	virtual bool PostUpdate() { return true; }
	virtual bool CleanUp() { return true; }
	virtual bool Load() { return true; }
	virtual bool Save() const { return true; }
	virtual void OnCollision(Collider*, Collider*) {}

};

#endif // !__FIN_MODULE_H__
