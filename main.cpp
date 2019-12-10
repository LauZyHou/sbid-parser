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

//读取文本文件
void LoadFile(const char* file)
{
	std::ifstream t;
	t.open(file);
	t.seekg(0, std::ios::end);		//找到文件尾
	bufferLen = t.tellg();			//报告位置，即得到字符数目
	t.seekg(0, std::ios::beg);		//回到文件头
	xmlChars = new char[bufferLen];
	t.read(xmlChars, bufferLen);	//读入字符数组中
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

//【解析Process】
void parseProcess(const TiXmlElement* const t) {
	const TiXmlElement* process = t->FirstChildElement("Process");
	while (process != nullptr) {
		const char* name = process->Attribute("name");
		myPrint(name);

		//todo 创建Process实例

		//【Process的若干Attribute】
		std::list<Attribute>* attrList = new std::list<Attribute>();
		const TiXmlElement* attribute = process->FirstChildElement("Attribute");
		while (attribute != nullptr) {
			const string name = attribute->Attribute("name");
			myPrint(name);
			const string type = attribute->Attribute("type");
			myPrint(type);
			//todo 创建Attribute实例，并放入attrList
			attribute = attribute->NextSiblingElement("Attribute");
		}

		//【Process的若干CommMethod】
		//todo std:list<CommMethod>
		const TiXmlElement* commMethod = process->FirstChildElement("CommMethod");
		while (commMethod != nullptr) {
			const string name = commMethod->Attribute("name");
			myPrint(name);
			const string inout = commMethod->Attribute("inout");
			myPrint(inout);
			const string paramType = commMethod->Attribute("param_type");
			myPrint(paramType);
			//todo 创建CommMethod实例，并放入cmList
			commMethod = commMethod->NextSiblingElement("CommMethod");
		}

		//【Process的若干Method】
		//todo std::list<Method>
		const TiXmlElement* method = process->FirstChildElement("Method");
		while (method != nullptr) {
			const string name = method->Attribute("name");
			myPrint(name);
			const string returnType = method->Attribute("return_type");
			myPrint(returnType);
			const string algorithmId = method->Attribute("algorithm_id");
			myPrint(algorithmId);
			//【Method的若干Param】
			//todo std::list<Param>
			const TiXmlElement* param = method->FirstChildElement("Param");
			while (param != nullptr) {
				const string type = param->Attribute("type");
				myPrint(type);
				const string name = param->Attribute("name");
				myPrint(name);
				//todo 创建Param实例，并存入Method
				param = param->NextSiblingElement("Param");
			}
			//【Method的UserCode】
			const TiXmlElement* userCode = method->FirstChildElement("UserCode");
			if (userCode != nullptr) {
				const char* userCodeContent = userCode->GetText();
				if (userCodeContent != nullptr) {
					myPrint(userCodeContent);
					//todo 写入
				}
			}
			//todo 创建Method实例，并放入methodList
			method = method->NextSiblingElement("Method");
		}

		//【解析StateMachine】
		//todo 可能要使用list，不过这里最后要拼成一个StateMachine
		const TiXmlElement* stateMachine = process->FirstChildElement("StateMachine");
		while (stateMachine != nullptr) {
			const string name = stateMachine->Attribute("name");
			myPrint(name);
			const string initialState = stateMachine->Attribute("initial_state");
			myPrint(initialState);
			//【StateMachine的若干State】
			//todo std::list<State>
			const TiXmlElement* state = stateMachine->FirstChildElement("State");
			while (state != nullptr) {
				const string name = state->Attribute("name");
				myPrint(name);
				//todo 创建State实例，并放入list
				state = state->NextSiblingElement("State");
			}
			//【StateMachine的若干Transition】
			//todo std::list<Transition>
			const TiXmlElement* trans = stateMachine->FirstChildElement("Transition");
			while (trans != nullptr) {
				const string from = trans->Attribute("from");
				myPrint(from);
				const string to = trans->Attribute("to");
				myPrint(to);
				//【Transition的Gurad】
				const TiXmlElement* guard = trans->FirstChildElement("Guard");
				if (guard != nullptr) {
					const string content = guard->Attribute("content");
					myPrint(content);
					//创建Gurad实例，默认true
					if (content.length() > 0) {
						//todo 写入
						myPrint(content);
					}
				}
				//【Transition的若干Action】
				//todo std::list<Action>
				const TiXmlElement* action = trans->FirstChildElement("Action");
				while (action != nullptr) {
					const string content = action->Attribute("content");
					myPrint(content);
					//创建Action实例，默认无动作
					if (content.length() > 0) {
						//todo 并写入
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

//【解析AttackTree】
void parseAttackTree(const TiXmlElement* const t) {
	const TiXmlElement* attackTree = t->FirstChildElement("AttackTree");
	if (attackTree == nullptr)
		return;
	const string name = attackTree->Attribute("name");
	myPrint(name);
	const string rootAttack = attackTree->Attribute("root_attack");
	myPrint(rootAttack);
	//【AttackTree的若干Attack】
	const TiXmlElement* attack = attackTree->FirstChildElement("Attack");
	while (attack != nullptr) {
		const string name = attack->Attribute("name");
		myPrint(name);
		const string enable = attack->Attribute("enable");
		myPrint(enable);
		//标签内容里放的是用户对Attack自然语言描述
		const char* attackContent = attack->GetText();
		if (attackContent != nullptr) {
			myPrint(attackContent);
			//todo 写入
		}
		attack = attack->NextSiblingElement("Attack");
	}
	//【AttackTree的若干Relation】
	const TiXmlElement* relation = attackTree->FirstChildElement("Relation");
	while (relation != nullptr) {
		const string type = relation->Attribute("type");
		myPrint(type);
		const string father = relation->Attribute("father");
		myPrint(father);
		//【Relation的若干Child】
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

//【解析InitialKnowledge】
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

//【解析SafetyProperty】但不设置这个标签
void parseSafetyProperty(const TiXmlElement* const t) {
	//【若干ConfidentialProperty】
	const TiXmlElement* cp = t->FirstChildElement("ConfidentialProperty");
	while (cp != nullptr) {
		const string process = cp->Attribute("process");
		myPrint(process);
		const string attribute = cp->Attribute("attribute");
		myPrint(attribute);
		cp = cp->NextSiblingElement("ConfidentialProperty");
	}
	//【若干AuthenticityProperty】
	const TiXmlElement* ap = t->FirstChildElement("AuthenticityProperty");
	while (ap != nullptr) {
		//每个AuthenticityProperty中有两个Value，一个发送方，一个接收方
		//发送方
		const TiXmlElement* sender = ap->FirstChildElement("Value");
		if (sender != nullptr) {
			const string process = sender->Attribute("process");
			myPrint(process);
			const string state = sender->Attribute("state");
			myPrint(state);
			const string attribute = sender->Attribute("attribute");
			myPrint(attribute);
		}
		//接收方
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

int main() {
	//设置程序的地域信息，第一个参数设置LC_ALL表示影响范围是全部，第二个参数表示中文UTF-8编码
	setlocale(LC_ALL, "zh_CN.UTF-8");

	//先以文本文件方式读取，读到字符数组xmlChars中（直接读会中文乱码）
	LoadFile("template.xml");

	//导入TinyXml数据结构中
	TiXmlDocument doc;
	doc.Parse(xmlChars);

	//获取Xml根元素
	TiXmlElement* root = doc.RootElement();
	if (root == nullptr) {
		std::cerr << "Error: can't find xml root." << std::endl;
		return 0;
	}

	//解析进程模板
	//parseProcess(root);

	//解析攻击树
	//parseAttackTree(root);

	//解析InitialKnowledge
	//parseInitialKnowledge(root);

	//解析SafetyProperty
	parseSafetyProperty(root);

	//todo 解析其它

	delete[] xmlChars;
	return 0;
}
