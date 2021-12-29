#pragma once
#include "CButton.h"
class GenericButton :
    public CButton
{
public:
	GenericButton(FPOINT pos, int size, class Texture* texture);
	~GenericButton() = default;

	void isClicked() override;
};

