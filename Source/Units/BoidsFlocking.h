#pragma once
/*
Flocking
��Navigator ��Leaf
�@��
�|�]�t Leader
�H�Ψ�L����
Leader�b�@�Ӹs�����u���@��
�DLeader ���Leader
Leader�t�d�M��

�����

��� ���]4�H ABCD �� P�I�AA��Leader

�YLeader�Q�
��Leader�����|�汵���sLeader �A�sLea

Case 1:
	AB�Q��h��Q�I �A����CD�ҷ|���hLeader�A�����M�ݭn�������
	A��Leader���|��CD�����sLeader
	�sLeader�u�ݭn�b�M��List���e��
	�[�W�e����Leader���|�A�N�i�H�L�_���y
	�M��AB����X�sLeader�A�i��M���P���H
Case 2:
	CD�Q��h��Q�I�A����AB Leader���ʡA��CD�ݭn��X�sLeader
*/
#pragma once
#include <vector>
#include <map>
#include <stack>
#include <algorithm>
#include "Navigator.h"
#include "Entity.h"
#include "../World.h"
namespace Unit
{

	class BoidsFlocking :public UnitBase
	{
		//�p������L�H
		vector<Entity>others;
		//�O�_�������A�O���ܫh�i��M���A�ä��ϥκ�k(�ثe)
		bool isLeader;
		//������
		//������V�t�סA�ΥH�קK�P��L���ͤӪ�
		int separation;
		//�����
		//��������L���ͪ��t��
		int alignment;
		//���E��
		//
		int coherence;
		//�P���d��
		//�ΨӰ����d�򤺬O�_����ê��
		int sightRange;
		//��ϥ�
		vector<float>velocity;
		//����
		//�b�s�餺�קK�L�����
		//�]�t�׶}��ê��
		void Separation();
		//���
		//�¦V�s�骺������V����
		void Alignment();
		//���E
		//�V�s�骺������m����
		void Cohesion();
	};
}



