#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement 
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW         = -90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  2.5f;
const float SENSITIVITY =  0.1f;
const float ZOOM        =  45.0f;

class Camera
{
    public:
        // camera attributes
        glm::vec3 Position;
        glm::vec3 Front;
        glm::vec3 Up;
        glm::vec3 Right;

        glm::vec3 WorldUp;

        // euler angles
        float Yaw;
        float Pitch;

        // camera options
        float MovementSpeed;
        float MouseSensitivity;
        float Zoom;

        // constructor with vectors
        Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
        {
            Position = position;
            WorldUp = up;
            Yaw = yaw;
            Pitch = pitch;

            updateCameraVectors();
        }

        // constructor with scalar values
        Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
        {
            Position = glm::vec3(posX, posY, posZ);
            WorldUp = glm::vec3(upX, upY, upZ);
            Yaw = yaw;
            Pitch = pitch;

            updateCameraVectors();
        }

        glm::mat4 GetViewMatrix()
        {
            // using glm::lookAt
            return glm::lookAt(Position, Position + Front, Up);

            // constructing the matrix manually
            // method 1
            /*
            glm::mat4 view(1.0f);

            view[0][0] = Right.x;
            view[1][0] = Right.y; 
            view[2][0] = Right.z;
            view[0][1] = Up.x;
            view[1][1] = Up.y;
            view[2][1] = Up.z;
            view[0][2] = -Front.x;
            view[1][2] = -Front.y;
            view[2][2] = -Front.z;
            view[3][0] = -glm::dot(Right, Position);
            view[3][1] = -glm::dot(Up, Position);
            view[3][2] = glm::dot(Front, Position);

            return view;
            */

            // method 2
            /*
            glm::mat4 translation = glm::mat4(1.0f); // translating to camera position

            translation[3][0] = -Position.x;
            translation[3][1] = -Position.y;
            translation[3][2] = -Position.z;

            glm::mat4 rotation = glm::mat4(1.0f); // rotating to camera orientation

            rotation[0][0] = Right.x;
            rotation[1][0] = Right.y;
            rotation[2][0] = Right.z;

            rotation[0][1] = Up.x;
            rotation[1][1] = Up.y;
            rotation[2][1] = Up.z;

            rotation[0][2] = -Front.x;
            rotation[1][2] = -Front.y;
            rotation[2][2] = -Front.z;

            return rotation * translation; // translate then rotate and we have the view matrix
            */
        }

        // processes input received from any keyboard-like input system. 
        void ProcessKeyboard(Camera_Movement direction, float deltaTime)
        {
            float velocity = MovementSpeed * deltaTime;
            glm::vec3 moveDirection(0.0f);

            if(direction == FORWARD)
                moveDirection += Front;
            if(direction == BACKWARD)
                moveDirection -= Front;
            if(direction == LEFT)
                moveDirection -= Right;
            if(direction == RIGHT)
                moveDirection += Right;

            // lock movement to x and z axis by removing the amount of movedirection that is in the up direction
            //moveDirection -= glm::dot(moveDirection, WorldUp) * WorldUp;

            Position += glm::normalize(moveDirection) * velocity;
        }

        // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
        void ProcessMouseMovement(float xOffset, float yOffset)
        {
            xOffset *= MouseSensitivity;
            yOffset *= MouseSensitivity;

            Yaw += xOffset;
            Pitch += yOffset;

            // clamp pitch so camera doesn't flip
            if(Pitch > 89.0f)
                Pitch = 89.0f;
            if(Pitch < -89.0f)
                Pitch = -89.0f;
        
            // update Front, Right and Up Vectors using the updated Euler angles
            updateCameraVectors(); 
        }

        // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
        void ProcessMouseScroll(float yoffset)
        {
            Zoom -= (float)yoffset;
            if (Zoom < 1.0f)
                Zoom = 1.0f;
            if (Zoom > 45.0f)
                Zoom = 45.0f;
        }

    private:
        // calculates the front vector from the Camera's (updated) Euler Angles
        void updateCameraVectors()
        {
            // calculate the new Front vector
            glm::vec3 dir;
            dir.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
            dir.y = sin(glm::radians(Pitch));
            dir.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

            Front = glm::normalize(dir);

            // also re-calculate the Right and Up vector (normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.)
            Right = glm::normalize(glm::cross(Front, WorldUp));
            Up    = glm::normalize(glm::cross(Right, Front));
        }
};
#endif