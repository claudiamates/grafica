//
//  Camera.cpp
//  Lab5
//
//  Created by CGIS on 28/10/2016.
//  Copyright © 2016 CGIS. All rights reserved.
//

#include "Camera.hpp"

namespace gps {
    
    Camera::Camera(glm::vec3 cameraPosition, glm::vec3 cameraTarget)
    {
        this->cameraPosition = cameraPosition;
        this->cameraTarget = cameraTarget;
        this->cameraDirection = glm::normalize(cameraTarget - cameraPosition);
        this->cameraRightDirection = glm::normalize(glm::cross(this->cameraDirection, glm::vec3(0.0f, 1.0f, 0.0f)));
		this->cameraUpDirection = glm::cross(cameraDirection, cameraRightDirection);
    }
    
    glm::mat4 Camera::getViewMatrix()
    {
        return glm::lookAt(cameraPosition, cameraPosition + cameraDirection , glm::vec3(0.0f, 1.0f, 0.0f));
    }

	glm::vec3 Camera::getCameraTarget()
	{
		return cameraTarget;
	}
    
    void Camera::move(MOVE_DIRECTION direction, float speed)
    {
        switch (direction) {
            case MOVE_FORWARD:
                cameraPosition += cameraDirection * speed;
                break;
                
            case MOVE_BACKWARD:
                cameraPosition -= cameraDirection * speed;
                break;
                
            case MOVE_RIGHT:
                cameraPosition += cameraRightDirection * speed;
                break;
                
            case MOVE_LEFT:
                cameraPosition -= cameraRightDirection * speed;
                break;
        }
    }
    
    void Camera::rotate(float pitch, float yaw)
    {
		if (pitch == 0)
		{
			float R = glm::length(cameraTarget - cameraPosition);
			cameraTarget.x = cameraPosition.x - R * sin(yaw);
			this->cameraTarget.y = this->cameraTarget.y;
			cameraTarget.z = cameraPosition.z - R * cos(yaw);

			cameraDirection = glm::normalize(cameraTarget - cameraPosition);
			this->cameraRightDirection = glm::normalize(glm::cross(this->cameraDirection, this->cameraUpDirection));
		}
		if (yaw == 0)
		{
			float R = glm::length(cameraTarget - cameraPosition);
			cameraTarget.x = cameraTarget.x;
			cameraTarget.y = cameraPosition.y + R * sin(pitch);
			cameraTarget.z = cameraPosition.z - R * cos(pitch);

			cameraDirection = glm::normalize(cameraTarget - cameraPosition);
			this->cameraUpDirection = glm::normalize(glm::cross(this->cameraRightDirection, this->cameraDirection));
		}

    }
    
}
