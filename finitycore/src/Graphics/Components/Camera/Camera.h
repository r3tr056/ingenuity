#pragma once
#ifndef FINITY_GUI_CAMERA_H
#define FINITY_GUI_CAMERA_H

#include "../GLShader.h"
#include <memory>
#include <GL/gl.h>
#include <glm/gtx/quaternion.hpp>
#include "UIGFX/Gfx.h"

namespace finitycore::Core::Graphics::Components {
    class Camera {
    private:
        glm::mat4 mViewMatrix;
        glm::mat4 mProjection = glm::mat4{ 1.0f };
        glm::vec3 mPos = { .0f, .0f, .0f };
        GLfloat mDistance = 5.0f;
        GLfloat mFOV;
        GLfloat mNear;
        GLfloat mFar;
        GLfloat mSpeed;
        GLfloat mAspect;
        GLfloat mSensitivity;
        glm::vec2 mPrev;
        GLfloat mPitch = .0f;
        GLfloat mYaw = .0f;
        const GLfloat mRotSpeed = 2.0f;
        glm::vec2 mCurrentPos2d = { .0f, .0f };
        const glm::vec3 cRight = { 1.0f, .0f, .0f };
        const glm::vec3 cUp = { .0f, 1.0f, .0f };
        const glm::vec3 cForward = { 0.0f, .0f, 1.0f };
        glm::vec3 mFocus = { .0f, .0f, .0f };
        GLboolean mManual = false;

        enum class Direction {
            FORWARD,
            BACKWARD,
            LEFT,
            RIGHT,
            DOWN
        };

        // Private methods
        void updateView(GLboolean constrainPath = true);
        void processInput(const Direction direction, const GLfloat dT);
        void updateVectors();

    public:
        Camera(const glm::vec3& pos, GLfloat fov, GLfloat aspect, GLfloat near, GLfloat far) {
            mPos = pos;
            mAspect = aspect;
            mNear = near;
            mFar = far;
            mFOV = fov;
            setAspect(mAspect);
            updateViewMatrix();
        }

        void update(Shader* shader) {
            glm::mat4 model{ 1.0f };
            shader->setuniform("model", model);
            shader->setuniform("view", mViewMatrix);
            shader->setuniform("projection", getProjection());
            shader->setuniform("camPos", mPos);
        }

        void setAspect(GLfloat aspect) {
            mProjection = glm::perspective(mFOV, aspect, mNear, mFar);
        }

        void setDistance(GLfloat offset) {
            mDistance += offset;
            updateViewMatrix();
        }

        const glm::mat4& getProjection() {
            return mProjection;
        }

        glm::mat4 getViewProjection() const {
            return mProjection * getViewMatrix();
        }

        glm::quat getDirection() const {
            return glm::quat(glm::vec3(-mPitch, -mYaw, .0f));
        }

        glm::vec3 getUp() const {
            return glm::rotate(getDirection(), cUp);
        }

        glm::vec3 getRight() const {
            return glm::rotate(getDirection(), cRight);
        }

        glm::vec3 getForward() const {
            return glm::rotate(getDirection(), cForward);
        }

        glm::mat4 getViewMatrix() const {
            return mViewMatrix;
        }

        void onMouseWheel(GLfloat dT) {
            setDistance(dT * .5f);
            updateViewMatrix();
        }

        void reset() {
            mFocus = { .0f, .0f, .0f };
            updateViewMatrix();
        }

        void updateViewMatrix() {
            mPos = mFocus - getForward() * mDistance;
            glm::quat orientation = getDirection();
            mViewMatrix = glm::translate(glm::mat4(1.0f), mPos) * glm::toMat4(orientation);
            mViewMatrix = glm::inverse(mViewMatrix);
        }

        void onMouseMove(double x, double y, EInputButton button) {
            glm::vec2 pos2d{ x , y };
            if (button == EInputButton::RIGHT) {
                glm::vec2 delta = (pos2d - mCurrentPos2d) * 0.004f;
                float sign = getUp().y < 0 ? -1.0f : 1.0f;
                mYaw += sign * delta.x * mRotSpeed;
                mPitch += delta.y * mRotSpeed;

                updateViewMatrix();
            }
            else if (button == EInputButton::MIDDLE) {
                glm::vec2 delta = (pos2d - mCurrentPos2d) * 0.003f;
                mFocus += -getRight() * delta.x * mDistance;
                mFocus += getUp() * delta.y * mDistance;

                updateViewMatrix();
            }

            mCurrentPos2d = pos2d;

        }
    };

#endif //FINITY_GUI_CAMERA_H

#ifndef FINITY_GUI_PRESPECTIVE_CAMERA_H
#define FINITY_GUI_PRESPECTIVE_CAMERA_H

    class PrespectiveCamera : public Camera {
    public:
        bool init(GLint screenWidth, GLint screenHeight, GLfloat fovRadians, GLfloat depth);
        void update(GLint projectionViewBinding, glm::vec3 camPos, glm::vec3 camLookAt);
        glm::mat4 getPojectionView() { return mProjection * mView; }

        ~PrespectiveCamera() = default;

    private:
        glm::mat4 mProjection;
        glm::mat4 mView;
    };

#endif

#ifndef FINITY_GUI_ORTHO_CAMERA_H
#define FINITY_GUI_ORTHO_CAMERA_H

    class OrthoCamera : public Camera {
    public:
        bool init(GLfloat width, GLfloat height, GLfloat minDepth, GLfloat maxDepth);

        void update(GLint projectionViewBinding, glm::vec3 camPos, glm::vec3 camLookAt);
        glm::mat4 getProjectionView() { return mProjection * mView; }

    private:
        glm::mat4 mProjection;
        glm::mat4 mView;
    };

}
#endif
