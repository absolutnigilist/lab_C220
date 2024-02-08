#pragma once

//������-�������,��������-�������
//��������� �������� ������������� ����������� ����� � �������� � ��������� �������� ��������, �� ������� �� ������� � �������.
auto noop_deleter = [](std::string*) {};

// ���������� ������������ ������� ��� ����� ����������
auto compare = [](const std::shared_ptr<std::string>& a, const std::shared_ptr<std::string>& b) { return *a < *b; };