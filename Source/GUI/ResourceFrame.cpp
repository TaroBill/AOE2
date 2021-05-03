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
	CDC* pDC = CDDraw::GetBackCDC();			// 取得 Back Plain 的 CDC 
	CFont f, * fp;
	f.CreatePointFont(80, "Times New Roman");	// 產生 font f; 160表示16 point的字
	fp = pDC->SelectObject(&f);					// 選用 font f
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
	pDC->SelectObject(fp);						// 放掉 font f (千萬不要漏了放掉)
	CDDraw::ReleaseBackCDC();					// 放掉 Back Plain 的 CDC
}

void ResourceFrame::onClicked(CPoint p) {

}
