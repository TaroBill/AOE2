#pragma once
#include "Button.h"
#include "../../socket/NetWork.h"


class Military_Button : public Button {

public:
	Military_Button() : Button(90, SIZE_Y - 240 + 40, 40, 40, true)
	{
		loadBitmap();
	}
	~Military_Button()
	{

	}
	void loadBitmap() override {
		Button::texture.LoadBitmap(IDB_MILITARY_BUTTON);
	}

	void onClicked() override {
		//Test
		CMemFile memfile;
		//CSocketFile file(&NetWork::getInstance()->clientsocket);
		CArchive ar(&memfile, CArchive::store);
		int size = World::getInstance()->unit.size();
		ar << size;
		for (int i = 0; i < size; i++) {
			dynamic_cast<Unit::Villager*>(World::getInstance()->unit.at(i))->Serialize(ar);
		}
		ar.Close();
		INT dataLen = (INT)memfile.GetLength();
		BYTE* data = memfile.Detach();

		// Copy serialized data to some buffer, or to Socket, File, etc.
		NetWork::getInstance()->clientsocket.Send(data, dataLen);

		free(data); // after detach and when no longer needed must be freed with free()
	}
};
