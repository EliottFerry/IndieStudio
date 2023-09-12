/*
** EPITECH PROJECT, 2021
** ECS
** File description:
** File to setup an ECS configuration
*/

#ifndef ECS_HPP
#define ECS_HPP

#include <iostream>
#include <filesystem>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include <list>

namespace Indie {
    class Component;
    class Entity;

    using ComponentID = std::size_t;
    inline ComponentID getComponentTypeID() {
        static ComponentID lastID = 0;
        return lastID++;
    }
    template <typename T>
    inline ComponentID getComponentTypeID() noexcept {
        static ComponentID typeID = getComponentTypeID();
        return typeID;
    }
    constexpr std::size_t maxComponents = 32;
    using ComponentBitSet = std::bitset<maxComponents>;
    using ComponentArray = std::array<Component *, maxComponents>;

    /*! The abstract class for a component.*/
    class Component {
        public:
            Entity *entity;

            virtual void init() {};
            virtual void update(double time) {};
            virtual void draw() {};

            virtual ~Component() = default;

            /*!* Return the path adapted for windows and linux. */
    };
    /*! The class to handle a single entity. */
    class Entity {
        public:
            Entity();
            ~Entity();
            /*! Looping into all the components to update them if they have a update function. */
            void update(double time);
            /*! Looping into all the components to draw them if they have a draw function.*/
            void draw();
            /*! Check if the entity is active. Return true if she is, or false if she is not. */
            bool isActive() const;
            /*! Set the entity to inactive state. */
            void destroy();

            /*! Check if the entity have a certain component. Return true if the entity have the component, and return false if not. 
            EXEMPLE:
                entity.hasComponent<COMPONENT_YOU_WANT_TO_CHECK>(); */
            template <typename TComponent>
            bool hasComponent() const
            {
                return componentsBitSet[getComponentTypeID<TComponent>()];
            }
            /*! Add a component to an entity, and into the array of component. It also call the init function of the component.
            EXEMPLE:
                entity.addComponent<COMPONENT_YOU_WANT_TO_ADD>(OPTIONNAL); */
            template <typename TComponent, typename... Args>
            void addComponent(Args&&... Arg)
            {
                TComponent* c(new TComponent(std::forward<Args>(Arg)...));
                c->entity = this;
                std::unique_ptr<TComponent> uPtr { c };
                components.emplace_back(std::move(uPtr));

                componentsArray[getComponentTypeID<TComponent>()] = c;
                componentsBitSet[getComponentTypeID<TComponent>()] = true;
                c->init();
            }

            /*! Get the wanted component in the entity.
            EXEMPLE:
                entity.getComponent<COMPONENT_YOU_WANT_TO_GET>().FUNCTION_CALL() */
            template <typename TComponent>
            TComponent& getComponent() const
            {
                auto ptr(componentsArray[getComponentTypeID<TComponent>()]);
                return *static_cast<TComponent*>(ptr);
            }
        private:
            /*! The boolean to see if the entity is active or not. */
            bool active = true;
            /*! The vector used to loop over all components in the update and draw function. */
            std::vector<std::unique_ptr<Component>> components;

            /*! The array who store all the components of the entity. */
            ComponentArray componentsArray;
            /*! The bitset, to see if the entity contain a certain component. Store true if she has it, false if not. */
            ComponentBitSet componentsBitSet;
    };
    /*! The class to manage all the entities. */
    class EntityManager
    {
        private:
            /*! The vector to store all the entities. */
            std::vector<std::unique_ptr<Entity>> entities;
        public:
            EntityManager();
            ~EntityManager();
            /*! Call the update function for all the entity. */
            void update(double time);
            /*! Call the draw function for all the entity. */
            void draw();
            /*! Refresh all the entity, and erase the inactive ones. */
            void refresh();
            /*! Return a reference to the camera. */
            Entity &getCamera();
            /*! Destroy all the entity of the entity manager. */
            void clear();
            /*! Return a reference to the model. */
            std::list<std::reference_wrapper<Indie::Entity>> getModel();
            /*! Return a reference to the model. */
            std::list<std::reference_wrapper<Indie::Entity>> get2DModel();
            /*! Return a reference to the text. */
            std::list<std::reference_wrapper<Indie::Entity>> getText();
            /*! Return a reference to the button. */
            std::list<std::reference_wrapper<Indie::Entity>> getButton();
            /*! Return a reference to the shader. */
            std::list<std::reference_wrapper<Indie::Entity>> getShader();
            /*! Return a reference to the 2D component. */
            std::list<std::reference_wrapper<Indie::Entity>> getTwoDComponent();
            /*! Return a reference to the player */
            std::list<std::reference_wrapper<Indie::Entity>> getPlayer();
            /*! Return a reference to the bomb */
            std::list<std::reference_wrapper<Indie::Entity>> getBomb();
            /*! Return a reference to the wall the bomb can break */
            std::list<std::reference_wrapper<Indie::Entity>> getBreakWalls();
            /*! Return a reference to the bomberman ai */
            std::list<std::reference_wrapper<Indie::Entity>> getBombermanAI();
            /*! Return a reference to the audio */
            std::list<std::reference_wrapper<Indie::Entity>> getAudioDevice();
            /*! Return a reference to the box */
            std::list<std::reference_wrapper<Indie::Entity>> getBox();
            /*! Return a reference to all the powerUps */
            std::list<std::reference_wrapper<Indie::Entity>> getPowerUps();
            /*! Return a referance to all score */
            std::list<std::reference_wrapper<Indie::Entity>> getScore();
            /*! Create a new entity.
            EXEMPLE:
                auto &newEntity(manager.addEntity()); */
            Entity &addEntity();
    };
}

#endif /* !ECS_HPP */
