#include <iostream>
#include <string>
#include <fstream>
#include <list>

#include "tinyxml/tinystr.h"
#include "tinyxml/tinyxml.h"

#include "Model/Process/Attribute.hpp"
#include "Model/Process/Process.hpp"

using namespace esc;

int bufferLen = 0;
char* xmlChars = nullptr;

//===============================================================================

//��ȡ�ı��ļ�
void LoadFile(const char* file)
{
	std::ifstream t;
	t.open(file);
	t.seekg(0, std::ios::end);		//�ҵ��ļ�β
	bufferLen = t.tellg();			//����λ�ã����õ��ַ���Ŀ
	t.seekg(0, std::ios::beg);		//�ص��ļ�ͷ
	xmlChars = new char[bufferLen];
	t.read(xmlChars, bufferLen);	//�����ַ�������
	t.close();
}

//===============================================================================

void myPrint(const char* s) {
	std::cout << s << std::endl;
}

void myPrint(const string s) {
	std::cout << s << std::endl;
}

//===============================================================================

//������Process��
void parseProcess(const TiXmlElement* const t) {
	const TiXmlElement* process = t->FirstChildElement("Process");
	while (process != nullptr) {
		const char* name = process->Attribute("name");
		myPrint(name);

		//todo ����Processʵ��

		//��Process������Attribute��
		std::list<Attribute>* attrList = new std::list<Attribute>();
		const TiXmlElement* attribute = process->FirstChildElement("Attribute");
		while (attribute != nullptr) {
			const string name = attribute->Attribute("name");
			myPrint(name);
			const string type = attribute->Attribute("type");
			myPrint(type);
			//todo ����Attributeʵ����������attrList
			attribute = attribute->NextSiblingElement("Attribute");
		}

		//��Process������CommMethod��
		//todo std:list<CommMethod>
		const TiXmlElement* commMethod = process->FirstChildElement("CommMethod");
		while (commMethod != nullptr) {
			const string name = commMethod->Attribute("name");
			myPrint(name);
			const string inout = commMethod->Attribute("inout");
			myPrint(inout);
			const string paramType = commMethod->Attribute("param_type");
			myPrint(paramType);
			//todo ����CommMethodʵ����������cmList
			commMethod = commMethod->NextSiblingElement("CommMethod");
		}

		//��Process������Method��
		//todo std::list<Method>
		const TiXmlElement* method = process->FirstChildElement("Method");
		while (method != nullptr) {
			const string name = method->Attribute("name");
			myPrint(name);
			const string returnType = method->Attribute("return_type");
			myPrint(returnType);
			const string algorithmId = method->Attribute("algorithm_id");
			myPrint(algorithmId);
			//��Method������Param��
			//todo std::list<Param>
			const TiXmlElement* param = method->FirstChildElement("Param");
			while (param != nullptr) {
				const string type = param->Attribute("type");
				myPrint(type);
				const string name = param->Attribute("name");
				myPrint(name);
				//todo ����Paramʵ����������Method
				param = param->NextSiblingElement("Param");
			}
			//��Method��UserCode��
			const TiXmlElement* userCode = method->FirstChildElement("UserCode");
			if (userCode != nullptr) {
				const char* userCodeContent = userCode->GetText();
				if (userCodeContent != nullptr) {
					myPrint(userCodeContent);
					//todo д��
				}
			}
			//todo ����Methodʵ����������methodList
			method = method->NextSiblingElement("Method");
		}

		//������StateMachine��
		//todo ����Ҫʹ��list�������������Ҫƴ��һ��StateMachine
		const TiXmlElement* stateMachine = process->FirstChildElement("StateMachine");
		while (stateMachine != nullptr) {
			const string name = stateMachine->Attribute("name");
			myPrint(name);
			const string initialState = stateMachine->Attribute("initial_state");
			myPrint(initialState);
			//��StateMachine������State��
			//todo std::list<State>
			const TiXmlElement* state = stateMachine->FirstChildElement("State");
			while (state != nullptr) {
				const string name = state->Attribute("name");
				myPrint(name);
				//todo ����Stateʵ����������list
				state = state->NextSiblingElement("State");
			}
			//��StateMachine������Transition��
			//todo std::list<Transition>
			const TiXmlElement* trans = stateMachine->FirstChildElement("Transition");
			while (trans != nullptr) {
				const string from = trans->Attribute("from");
				myPrint(from);
				const string to = trans->Attribute("to");
				myPrint(to);
				//��Transition��Gurad��
				const TiXmlElement* guard = trans->FirstChildElement("Guard");
				if (guard != nullptr) {
					const string content = guard->Attribute("content");
					myPrint(content);
					//����Guradʵ����Ĭ��true
					if (content.length() > 0) {
						//todo д��
						myPrint(content);
					}
				}
				//��Transition������Action��
				//todo std::list<Action>
				const TiXmlElement* action = trans->FirstChildElement("Action");
				while (action != nullptr) {
					const string content = action->Attribute("content");
					myPrint(content);
					//����Actionʵ����Ĭ���޶���
					if (content.length() > 0) {
						//todo ��д��
						myPrint(content);
					}
					action = action->NextSiblingElement("Action");
				}
				trans = trans->NextSiblingElement("Transition");
			}
			stateMachine = stateMachine->NextSiblingElement("StateMachine");
		}
		process = process->NextSiblingElement("Process");
	}
}

//===============================================================================

//������Channel��
void parseChannel(const TiXmlElement* const t) {
	const TiXmlElement* channel = t->FirstChildElement("Channel");
	while (channel != nullptr) {
		const string id = channel->Attribute("id");
		myPrint(id);
		const string fromProcess = channel->Attribute("fromProcess");
		myPrint(fromProcess);
		const string fromMethod = channel->Attribute("fromMethod");
		myPrint(fromMethod);
		const string toProcess = channel->Attribute("toProcess");
		myPrint(toProcess);
		const string toMethod = channel->Attribute("toMethod");
		myPrint(toMethod);
		channel = channel->NextSiblingElement("Channel");
	}
}

//===============================================================================

//������AttackTree��
void parseAttackTree(const TiXmlElement* const t) {
	const TiXmlElement* attackTree = t->FirstChildElement("AttackTree");
	if (attackTree == nullptr)
		return;
	const string name = attackTree->Attribute("name");
	myPrint(name);
	const string rootAttack = attackTree->Attribute("root_attack");
	myPrint(rootAttack);
	//��AttackTree������Attack��
	const TiXmlElement* attack = attackTree->FirstChildElement("Attack");
	while (attack != nullptr) {
		const string name = attack->Attribute("name");
		myPrint(name);
		const string enable = attack->Attribute("enable");
		myPrint(enable);
		//��ǩ������ŵ����û���Attack��Ȼ��������
		const char* attackContent = attack->GetText();
		if (attackContent != nullptr) {
			myPrint(attackContent);
			//todo д��
		}
		attack = attack->NextSiblingElement("Attack");
	}
	//��AttackTree������Relation��
	const TiXmlElement* relation = attackTree->FirstChildElement("Relation");
	while (relation != nullptr) {
		const string type = relation->Attribute("type");
		myPrint(type);
		const string father = relation->Attribute("father");
		myPrint(father);
		//��Relation������Child��
		const TiXmlElement* child = relation->FirstChildElement("Child");
		while (child != nullptr) {
			const string name = child->Attribute("name");
			myPrint(name);
			child = child->NextSiblingElement("Child");
		}
		relation = relation->NextSiblingElement("Relation");
	}
}

//===============================================================================

//������TopoGraph��
void parseTopoGraph(const TiXmlElement* const t) {
	const TiXmlElement* topoGraph = t->FirstChildElement("TopoGraph");
	if (topoGraph == nullptr)
		return;
	const string name = topoGraph->Attribute("name");
	myPrint(name);
	//������Node��
	const TiXmlElement* node = topoGraph->FirstChildElement("Node");
	while (node != nullptr) {
		const string id = node->Attribute("id");
		myPrint(id);
		const string process = node->Attribute("process");
		myPrint(process);
		node = node->NextSiblingElement("Node");
	}
	//������Link��
	const TiXmlElement* link = topoGraph->FirstChildElement("Link");
	while (link != nullptr) {
		const string from = link->Attribute("from");
		myPrint(from);
		const string to = link->Attribute("to");
		myPrint(to);
		link = link->NextSiblingElement("Link");
	}
}


//===============================================================================

//������InitialKnowledge��
void parseInitialKnowledge(const TiXmlElement* const t) {
	const TiXmlElement* ik = t->FirstChildElement("InitialKnowledge");
	while (ik != nullptr) {
		const string process = ik->Attribute("process");
		myPrint(process);
		const string attribute = ik->Attribute("attribute");
		myPrint(attribute);
		ik = ik->NextSiblingElement("InitialKnowledge");
	}
}

//===============================================================================

//������SecurityProperty���������������ǩ
void parseSecurityProperty(const TiXmlElement* const t) {
	//������ConfidentialProperty��
	const TiXmlElement* cp = t->FirstChildElement("ConfidentialProperty");
	while (cp != nullptr) {
		const string process = cp->Attribute("process");
		myPrint(process);
		const string attribute = cp->Attribute("attribute");
		myPrint(attribute);
		cp = cp->NextSiblingElement("ConfidentialProperty");
	}
	//������AuthenticityProperty��
	const TiXmlElement* ap = t->FirstChildElement("AuthenticityProperty");
	while (ap != nullptr) {
		//ÿ��AuthenticityProperty��������Value��һ�����ͷ���һ�����շ�
		//���ͷ�
		const TiXmlElement* sender = ap->FirstChildElement("Value");
		if (sender != nullptr) {
			const string process = sender->Attribute("process");
			myPrint(process);
			const string state = sender->Attribute("state");
			myPrint(state);
			const string attribute = sender->Attribute("attribute");
			myPrint(attribute);
		}
		//���շ�
		const TiXmlElement* receiver = sender == nullptr ? nullptr : sender->NextSiblingElement("Value");
		if (receiver != nullptr) {
			const string process = receiver->Attribute("process");
			myPrint(process);
			const string state = receiver->Attribute("state");
			myPrint(state);
			const string attribute = receiver->Attribute("attribute");
			myPrint(attribute);
		}
		ap = ap->NextSiblingElement("AuthenticityProperty");
	}
}

//===============================================================================

//������SafetyProperty���������������ǩ
void parseSafetyProperty(const TiXmlElement* const t) {
	//������Invariant��
	const TiXmlElement* invariant = t->FirstChildElement("Invariant");
	while (invariant != nullptr) {
		const string expression = invariant->Attribute("expression");
		myPrint(expression);
		invariant = invariant->NextSiblingElement("Invariant");
	}
	//������CTL���ʽ��
	const TiXmlElement* ctl = t->FirstChildElement("CTL");
	while (ctl != nullptr) {
		const string expression = ctl->Attribute("expression");
		myPrint(expression);
		ctl = ctl->NextSiblingElement("CTL");
	}
}

//===============================================================================

int main() {
	//���ó���ĵ�����Ϣ����һ����������LC_ALL��ʾӰ�췶Χ��ȫ�����ڶ���������ʾ����UTF-8����
	setlocale(LC_ALL, "zh_CN.UTF-8");

	//�����ı��ļ���ʽ��ȡ�������ַ�����xmlChars�У�ֱ�Ӷ����������룩
	LoadFile("template.xml");

	//����TinyXml���ݽṹ��
	TiXmlDocument doc;
	doc.Parse(xmlChars);

	//��ȡXml��Ԫ��
	TiXmlElement* root = doc.RootElement();
	if (root == nullptr) {
		std::cerr << "Error: can't find xml root." << std::endl;
		return 0;
	}

	//��������ģ��
	//parseProcess(root);

	//����Channel
	//parseChannel(root);

	//����������
	//parseAttackTree(root);

	//��������ͼ
	parseTopoGraph(root);

	//����InitialKnowledge
	//parseInitialKnowledge(root);

	//����SecurityProperty
	//parseSecurityProperty(root);

	//����SafetyProperty
	//parseSafetyProperty(root);

	//todo ��������

	delete[] xmlChars;
	return 0;
}
