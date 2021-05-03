#include "ResourceFrame.h"


ResourceFrame::ResourceFrame() : Frame(0, 0, 26, 1920)
{

}

ResourceFrame::~ResourceFrame()
{

}

void ResourceFrame::loadBitmap() {
	texture.LoadBitmap(IDB_RESOURCEBACKGROUND);
}

void ResourceFrame::OnShow() {
	Frame::OnShow();
	CDC* pDC = CDDraw::GetBackCDC();			// ���o Back Plain �� CDC 
	CFont f, * fp;
	f.CreatePointFont(80, "Times New Roman");	// ���� font f; 160���16 point���r
	fp = pDC->SelectObject(&f);					// ��� font f
	pDC->SetBkColor(RGB(0, 0, 0));
	pDC->SetTextColor(RGB(255, 255, 0));
	char strWood[30];								
	sprintf(strWood, "%d", World::getInstance()->player.wood);
	pDC->TextOut(35, 6, strWood);
	char strFood[30];
	sprintf(strFood, "%d", World::getInstance()->player.food);
	pDC->TextOut(115, 6, strFood);
	char strGold[30];
	sprintf(strGold, "%d", World::getInstance()->player.gold);
	pDC->TextOut(205, 6, strGold);
	char strStone[30];
	sprintf(strStone, "%d", World::getInstance()->player.stone);
	pDC->TextOut(270, 6, strStone);
	char strPopulation[30];
	sprintf(strPopulation, "%d", World::getInstance()->player.population);
	pDC->TextOut(355, 6, strPopulation);
	pDC->SelectObject(fp);						// �� font f (�d�U���n�|�F��)
	CDDraw::ReleaseBackCDC();					// �� Back Plain �� CDC
}

void ResourceFrame::onClicked(CPoint p) {

}
