#pragma once
#include "SList.h"

template<typename T>
SList<T>::Node::Node(const T& data, Node* next) : data(data), next(next)
{

}

template<typename T>
SList<T>::SList() : front(nullptr), back(nullptr), size(0)
{

}



template<typename T>
SList<T>::SList(const SList& copyList) : front(nullptr), back(nullptr), size(0)
{
	Node* copyListFront = copyList.front;
	while (copyListFront != nullptr)
	{
		PushBack(copyListFront->data);
		copyListFront = copyListFront->next;
	}
}

template<typename T>
SList<T>::SList(SList&& rhs) : front(std::move(rhs.front)), back(std::move(rhs.back)), size(rhs.size)
{
	rhs.front = nullptr;
	rhs.back = nullptr;
	rhs.size = 0;
}

template<typename T>
SList<T>& SList<T>::operator=(const SList& copyList)
{
	if (this != &copyList)
	{
		Clear();
		Node* copyListFront = copyList.front;
		while (copyListFront != nullptr)
		{
			PushBack(copyListFront->data);
			copyListFront = copyListFront->next;
		}
	}
	return *this;
}

template<typename T>
SList<T>& SList<T>::operator=(SList&& rhs)
{
	if (this != &rhs)
	{
		Clear();
		front = std::move(rhs.front);
		back = std::move(rhs.back);
		size = rhs.size;
		rhs.front = nullptr;
		rhs.back = nullptr;
		rhs.size = 0;
	}
	return *this;
}

template<typename T>
typename SList<T>::Iterator SList<T>::PushFront(const T& data)
{
	Node* tempNode = new Node(data, front);
	front = tempNode;
	if (back == nullptr)
	{
		back = front;
	}
	size++;
	return Iterator(front, *this);
}

template<typename T>
typename SList<T>::Iterator SList<T>::PushBack(const T& data)
{
	Node* tempNode = new Node(data);
	if (back != nullptr)
	{
		back->next = tempNode;
	}
	back = tempNode;
	if(front == nullptr)
	{
		front = back;
	}
	size++;
	return Iterator(back, *this);
}

template<typename T>
T& SList<T>::Front()
{
	if (front == nullptr)
	{
		throw std::exception("List is empty");
	}
	return front->data;
}

template<typename T>
const T& SList<T>::Front() const
{
	if (front == nullptr)
	{
		throw std::exception("The list is empty");
	}
	return const_cast<T&>(front->data);
}

template<typename T>
T& SList<T>::Back()
{
	if (back == nullptr)
	{
		throw std::exception("List is empty");
	}
	return back->data;
}

template<typename T>
const T& SList<T>::Back() const
{
	if (back == nullptr)
	{
		throw std::exception("List is empty");
	}
	return const_cast<T&>(back->data);
}

template<typename T>
unsigned int SList<T>::Size() const
{
	return size;
}

template<typename T>
bool SList<T>::IsEmpty() const
{
	return (front == nullptr);
}

template<typename T>
void SList<T>::PopFront()
{
	if (front != nullptr)
	{
		Node* tempPointer = front;
		if (front == back)
		{
			front = nullptr;
			back = nullptr;
		}
		else
		{
			front = front->next;
		}
		delete tempPointer;
		size--;
	}
}

template<typename T>
void SList<T>::Clear()
{
	Node* tempPointer = front;
	while (front != nullptr)
	{
		front = front->next;
		delete tempPointer;
		tempPointer = front;
	}
	front = nullptr;
	back = nullptr;
	size = 0;
}

template<typename T>
SList<T>::~SList()
{
	Clear();
}

template<typename T>
SList<T>::Iterator::Iterator() : mNode(nullptr), mOwner(nullptr)
{

}

template<typename T>
SList<T>::Iterator::Iterator(Node* node,const SList& owner) : mNode(node), mOwner((const_cast<SList<T>*>(&owner)))
{

}

template<typename T>
bool SList<T>::Iterator::operator==(const Iterator& rhs) const
{
	if (mOwner == rhs.mOwner)
	{
		if (mNode == rhs.mNode)
		{
			return true;
		}
	}
	return false;
}

template<typename T>
bool SList<T>::Iterator::operator!=(const Iterator& rhs) const
{
	return !operator==(rhs);
}

template<typename T>
T& SList<T>::Iterator::operator*()
{
	if (mNode == nullptr)
	{
		throw std::exception("Iterator points to invalid data");
	}
	return mNode->data;
}

template<typename T>
const T& SList<T>::Iterator::operator*() const
{
	if (mNode == nullptr)
	{
		throw std::exception("Iterator points to invalid data");
	}
	return const_cast<T&>(mNode->data);
}

template<typename T>
typename SList<T>::Iterator& SList<T>::Iterator::operator++()
{
	if (mNode == nullptr)
	{
		throw std::exception("Iterator points to a nullptr");
	}
	mNode = mNode->next;
	return *this;
}

template<typename T>
typename SList<T>::Iterator SList<T>::Iterator::operator++(int)
{
	if (mNode == nullptr)
	{
		throw std::exception("Iterator points to a nullptr");
	}
	Iterator tempIterator = *this;
	mNode = mNode->next;
	return tempIterator;
}

template<typename T>
typename SList<T>::Iterator SList<T>::begin() const
{
	return Iterator(front, *this);
}

template<typename T>
typename SList<T>::Iterator SList<T>::end() const
{
	return Iterator(nullptr, *this);
}

template<typename T>
void SList<T>::InsertAfter(const Iterator& it, const T& value)
{
	if (it == begin() && size == 0)
	{
		PushFront(value);
	}
	else if (it == end())
	{
		PushBack(value);
	}
	else if (it.mNode != nullptr)
	{
		Node* tempNode = new Node(value, it.mNode->next);
		it.mNode->next = tempNode;
		size++;
	}
}

template<typename T>
typename SList<T>::Iterator SList<T>::Find(const T& value) const
{
	for (auto it = begin(); it != end(); ++it)
	{
		if (it.mNode->data == value)
		{
			return it;
		}
	}
	return end();
}

template<typename T>
void SList<T>::RemoveAll(const T& value)
{
	if (size == 0U)
	{
		throw std::exception("List is empty");
	}
	while (front != nullptr &&  front->data == value)
	{
		PopFront();
	}
	if (size <= 1U)
	{
		return;
	}
	for (auto it = begin(); it != end(); ++it)
	{
		if (it.mNode->next == back && it.mNode->next->data == value)
		{
			it.mNode->next = back->next;
			delete back;
			size--;
			back = it.mNode;
			if (size == 1U)
			{
				front = back;
			}
			break;
		}
		else if (it.mNode->next == back || it.mNode == back)
		{
			break;
		}
		else if (it.mNode->next != back && it.mNode->next->data == value)
		{
			Node* tempNode = it.mNode->next;
			it.mNode->next = tempNode->next;
			delete tempNode;
			size--;
		}
	}
}

template<typename T>
void SList<T>::Remove(const T& value)
{
	if (size == 0U)
	{
		throw std::exception("List is empty");
	}
	if(front->data == value)
	{
		PopFront();
		return;
	}
	for (auto it = begin(); it != end(); ++it)
	{
		if (it.mNode->next == back && it.mNode->next->data == value)
		{
			it.mNode->next = back->next;
			delete back;
			size--;
			back = it.mNode;
			if (size == 1U)
			{
				front = back;
			}
			break;
		}
		else if (it.mNode->next == back || it.mNode == back)
		{
			break;
		}
		else if (it.mNode->next != back && it.mNode->next->data == value)
		{
			Node* tempNode = it.mNode->next;
			it.mNode->next = tempNode->next;
			delete tempNode;
			size--;
			break;
		}
	}
}

template<typename T>
void SList<T>::Remove(Iterator& it)
{
	if (it.mNode == nullptr)
	{
		throw std::exception("invalid iterator");
	}

	if (it == end())
	{
		throw std::exception("invalid iterator");
	}
	
	if (it.mOwner != this)
	{
		throw std::exception("invalid iterator");
	}
	if (it.mNode == front)
	{
		PopFront();
	}
	else if (it.mNode == back)
	{
		Node* temp = front;
		while (temp->next != back)
		{
			temp = temp->next;
		}
		back = temp;
		delete it.mNode;
		size--;
	}
	else
	{
		it.mNode->data = it.mNode->next->data;
		it.mNode->next = it.mNode->next->next;
		delete it.mNode->next;
	}
	size--;
}