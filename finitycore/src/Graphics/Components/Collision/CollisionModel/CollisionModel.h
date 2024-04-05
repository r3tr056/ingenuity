#pragma once
#ifndef FINITY_GUI_COLLISIONMODEL_H
#define FINITY_GUI_COLLISIONMODEL_H

#include "CollisionModel.h"

#include <glm/glm.hpp>
#include <GL/gl.h>

class finMaterial;

enum class ContactType {
    CONTACT_NONE,
    CONTACT_EDGE,
    CONTACT_MODELVERTEX,
    CONTACT_TERMVERTEX
};

typedef struct {
    ContactType contactType;
    glm::vec3 point;
    glm::vec3 normal;
    GLfloat dist;
    GLint contents;
    const finMaterial* material;
    GLint modelFeature;
    GLint trmFeature;
    GLint entityNum;
    GLint id_;
} contactInfo_t;

typedef struct {
    GLfloat fraction;
    glm::vec3 endPos;
    glm::mat3 endAxis;
    contactInfo_t contactInfo;
} trace_t;

typedef GLint cmHandle_t;

#define CM_CLIP_EPSILON .25f
#define CM_BOX_EPSILON 1.0f
#define CM_MAX_TRACT_DIST 4096.0f

class finCollisionModelManager {
public:
    virtual void loadMap(const finMapFile *mapFile) = 0;
    virtual void freeMap() = 0;
    virtual cmHandle_t loadModel(const char *modelName, const bool precache) = 0;
    virtual cmHandle_t setupTrmModel(const finTraceModel &trm, const finMaterial *mat) = 0;
    virtual bool trmFromModel(const char* modelName, finTraceModel &trm) = 0;
    virtual const char* getModelName(cmHandle_t model) const = 0;
    virtual bool getModelBounds(cmHandle_t model, finBounds &bounds) const = 0;
    virtual bool getModelContents(cmHandle_t model, int &contents) const = 0;
    virtual bool getModelEdge(cmHandle_t model, int edgeNum);
    virtual bool getModelPolygon(cmHandle_t model, int polyNum, finFixedWinding& winding)const = 0;
    virtual void translation(trace_t *results, const glm::vec3 &start, const glm::vec3 &end)const = 0;
    virtual void rotation() = 0;
    virtual void contents() = 0;
    virtual void contacts(contactInfo_t *contacts, const int maxContacts, const glm::vec3 &start, const string &dir, const float depth, const finTraceModel *trm, const glm::mat3 &trmAxis, int contentMask, cmHandle_t model, const glm::vec3 &modelOrigin, const glm::mat3 &modelAxis) = 0;
    virtual void debugOut(const glm::vec3 &origin) = 0;
    virtual void drawModel(cmHandle_t model, const glm::vec3 &modelOrigin, const glm::mat3 &modelAxis, const glm::vec3 &viewOrigin, const float radius) = 0;
    virtual void modelInfo(cmHandle_t model) = 0;
    virtual void listModels(void) = 0;

};


#endif //FINITY_GUI_COLLISIONMODEL_H
