#pragma once
#include "HashMap.h"
namespace FieaGameEngine {
	//! Template Abstract Factory Base Class
	template <typename T>
	class AbstractFactory
	{
	public:
		//typedefs to make the syntax easier to write
		typedef HashMap<std::string, AbstractFactory*> HashMapType;
		typedef typename HashMapType::Iterator IteratorType;
		//!Default constructor
		AbstractFactory() = default;
		//!Find function
		/*!
			Given a class name (string), returns the associated concrete factory.
			\param className a string
			\return Pointer to corresponding factory
		*/
		static AbstractFactory* Find(std::string className);
		//!Create Function
		/*!
			Given a class name (string), return a new object of that type.
			\param className a string
			\return Pointer to the create object
		*/
		template <typename... Args>
		static T* Create(std::string className, Args... args);
		//!Add function
		/*!
			 Given a reference to a concrete factory, adds it to the list of factories for this abstract factory.
			 \param a reference to the factory to be added
		*/
		static void Add(AbstractFactory& factory);
		//!Remove function
		/*!
			Given a reference to a concrete factory, removes it from the list of factories for this abstract factory.
			\param a reference to the factory to be removed
		*/
		static void Remove(AbstractFactory& factory);
		//!Classname function
		/*!
			Return the classname of the product it creates
		*/
		virtual std::string ClassName() const = 0;
		AbstractFactory(AbstractFactory& rhs) = delete;
		AbstractFactory(AbstractFactory&& rhs) = default;
		AbstractFactory& operator=(AbstractFactory& rhs) = delete;
		AbstractFactory& operator=(AbstractFactory&& rhs) = default;
		virtual ~AbstractFactory() = default;
		static HashMapType mFactoryMap; /*<!static hashmap that stores the concrete factories pointers.*/
	protected:
		//!Create Function
		/*!
			Return the address of a concrete product associated with this concrete factory class.
			virtual function that is overriden by the child classes
		*/
		virtual T* Create() = 0;

	};

#include "AbstractFactory.inl"

#define ConcreteFactory(ConcreteProductType, AbstractProductType)															\
		class Concrete##ConcreteProductType##Factory : public AbstractFactory<AbstractProductType>							\
		{																													\
			public:																											\
				Concrete##ConcreteProductType##Factory()																	\
				{																											\
					AbstractFactory<AbstractProductType>::Add(*this);														\
				}																											\
				virtual std::string ClassName()	const override																			\
				{																											\
					return #ConcreteProductType;																			\
				}																											\
				Concrete##ConcreteProductType##Factory(Concrete##ConcreteProductType##Factory& rhs) = delete;				\
				Concrete##ConcreteProductType##Factory& operator=(Concrete##ConcreteProductType##Factory& rhs) = delete;	\
				Concrete##ConcreteProductType##Factory(Concrete##ConcreteProductType##Factory&& rhs)						\
				{																											\
					operator=(std::move(rhs));																				\
				}																											\
				Concrete##ConcreteProductType##Factory& operator=(Concrete##ConcreteProductType##Factory&& rhs)				\
				{																											\
					AbstractFactory<AbstractProductType>::Remove(rhs);														\
					AbstractFactory<AbstractProductType>::Add(*this);														\
				}																											\
				~Concrete##ConcreteProductType##Factory()																	\
				{																											\
					AbstractFactory<AbstractProductType>::Remove(*this);													\
				}																											\
			protected:																										\
				virtual AbstractProductType* Create() override																		\
				{																											\
					return new ConcreteProductType();																		\
				}																											\
		};
}