#pragma once
#include <string>
#include <memory>
#include <vector>
#include <iostream>

class Human {
public:
	std::string name;
	bool is_alive;
	std::shared_ptr<Human> mother;
	std::shared_ptr<Human> father;
	std::vector<std::weak_ptr<Human>> children;

	Human(const std::string& _name, bool _is_alive = true) : name(_name), is_alive(_is_alive) {}
    
    // ��������� ����� ��� �������� �������
    static std::shared_ptr<Human> child(const std::string& name, const std::shared_ptr<Human>& mother, const std::shared_ptr<Human>& father) {
        auto newChild = std::make_shared<Human>(name);
        newChild->mother = mother;
        newChild->father = father;
        if (mother) mother->children.push_back(newChild);
        if (father) father->children.push_back(newChild);
        return newChild;
    }
    // ������ ���������������� ������
        void printFamilyTree(int generation = 0) const {
        std::string prefix(generation * 2, ' '); // ������ ��� ������������ ���������
        std::cout << prefix << name << (is_alive ? "" : " (deceased)") << std::endl;
        for (auto& child_weak : children) {
            if (auto child = child_weak.lock()) { // ����������� weak_ptr � shared_ptr
                child->printFamilyTree(generation + 1);
            }
        }
    }
        //������ ��������� �����
        void printChildrenParents() const {
            for (auto& child_weak : children) {
                if (auto child = child_weak.lock()) {
                    std::cout << child->name << "'s parents: ";
                    if (child->mother) std::cout << "Mother: " << child->mother->name << ", ";
                    if (child->father) std::cout << "Father: " << child->father->name;
                    std::cout << std::endl;
                }
            }
        }
};