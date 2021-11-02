#pragma once
#include "pch.h"

//A balanced binary search tree so that the parent node is bigger than its left child
// and smaller than its right child.
//How to balance a tree?

template <typename K, typename V>
class KeyValPair
{
    K m_key;
    V m_val;
public:
    bool operator>(const KeyValPair& pair)
    {
        return (m_key > pair.m_key);
    }
    bool operator==(const KeyValPair& pair)
    {
        return (m_key == pair.m_key);
    }
    bool operator<(const KeyValPair& pair)
    {
        return (m_key < pair.m_val);
    }
};
template <typename T>
class Node
{
    T m_value;
    std::shared_ptr<Node> m_lChild;
    std::shared_ptr<Node> m_rChild;

public:
    Node(const T& val):
        m_value(val)
    {
    }
    Node(const Node& node) = delete;
    Node(Node&& node) = default;//calls std::move on every data member
    std::shared_ptr<Node> getLeftChild()
    {
        return m_lChild;
    }
    std::shared_ptr<Node> getRightChild()
    {
        return m_rChild;
    }
    void setLeftChild(std::shared_ptr<Node> node)
    {
        m_lChild = std::move(node);
    }
    void setRightChild(std::shared_ptr<Node> node)
    {
        m_rChild = std::move(node);
    }
    const T& getValue() { return m_value; }
    bool operator>(const Node& rNode)
    {
        return (m_value > rNode.m_value);
    }
    bool operator==(const Node& rNode)
    {
        return (m_value == rNode.m_value);
    }
    bool operator<(const Node& rNode)
    {
        return (m_value < rNode.m_value);
    }
};

//Binary tree: a parent node can have at most two children
//Binary search tree: lChild < parent < rChild, search function, 
template <typename T>
class MyBinarySearchTree
{
    std::shared_ptr<Node<T>> m_root;
    void addNode(const Node<T>& node)
    {
     //if node < curNode, check lChild; if !lChild, node becomes lChild, return; else, curNode = lChild;
     //if node > curNode, check rChild; if !rChild, node becomes rChild, return; else, curNode = rChild;
     //continue until curNode = NULL;
    }
public:
    MyBinarySearchTree(const std::vector<T>& data) 
    {
        for (const T& item : data)
        {
            addNode(Node<T>(item));
        }
    };

};